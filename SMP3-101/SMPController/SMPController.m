//
//  SMPController.m
//  SMP3-101
//
//  Created by Adalbert Kitzig on 26.08.14.
//  Copyright (c) 2014 PlaceWorkers. All rights reserved.
//

#import "SMPController.h"
#import "EncryptionKeyManager.h"

#import "ODataServiceDocument.h"
#import "ODataServiceDocumentParser.h"
#import "ODataSchema.h"
#import "ODataParser.h"
#import "ODataCollection.h"

@interface SMPController ()
@property (strong, nonatomic) ODataServiceDocument *serviceDocument;
@property (strong, nonatomic) ODataSchema *schema1;
@end

@implementation SMPController

/*
 * Initialise the SMP3 engine, set our variables and register the user.
 */
- (NSError *)initialiseSMP{
    
    NSError *error = nil; // Generic error object.
    
    // Set username and password
    self.username = @"kitzig";
    self.password = @"ace123wq";
    // testing
    //self.username = @"S0012207428";
    //self.password = @"Sap_85??";
    
    // Setup system access info.
    self.smpAppId = @"com.bluefinsolutions.poc.smp3.101";
    self.smpSecProvider = @"SAPSecurityIOS";
    self.smpServer = @"192.168.0.121";
    self.smpPort = @"8080";                                     //bis hier hin ok
    
    // Setup odata service info
    self.odataURL = @"192.168.0.55:8000/sap/opu/odata/sap/ZSFLIGHT_PROJECT_SRV/";
    // self.odataURL = @"services.odata.org/Northwind/Northwind.svc/";
    // self.odataURL = @"http://sapes1.sapdevcenter.com:8080/sap/opu/odata/iwbep/gwdemo/";
    self.entityName = @"Carriers";
    
    // initialise the SMP connection with the information.
    self.clientConn = [SMPClientConnection
                       initializeWithAppID:self.smpAppId
                       domain:@"default"
                       secConfiguration:self.smpSecProvider];
    
    // Setup the connection profile on the connection.
    [self.clientConn setConnectionProfileWithHost:self.smpServer port:self.smpPort farm:nil relayServerUrlTemplate:nil enableHTTP:YES];
    
    // Set this class to be a delegate for any user-registration related notificaitons.
    [SMPUserManager setDelegate:self];
    
    // Make the user manager aware of the connection.
    SMPUserManager *userManager = [SMPUserManager initializeWithConnection:self.clientConn];
    
    // Finally - register the user.
    [userManager registerUser:self.username password:self.password error:&error isSyncFlag:NO];
    
    // Return any basic errors that have occurred.
    return error;
}

#pragma mark - User Manager Delegate calls
// Callback for when a user registration failed.
-(void)userRegistrationFailed:userManager
{
    NSLog(@"Failed to register user.");
    if (self.delegate && [self.delegate respondsToSelector:@selector(userRegistrationSuccessful)]) {
        [self.delegate userRegistrationFailed:@"Failed to register user - check connection and credentials."];
    }
}

// Callback for when a user registration is successful.
-(void)userRegistrationSuccessful:userManager
{
    
    // Extracting appConID from
    NSString* appConID = [[((SMPUserManager* ) userManager) clientConnection] applicationConnectionID];
    self.clientConn.applicationConnectionID = appConID;
    NSLog(@"AppConId retrieved from registration: %@", self.clientConn.applicationConnectionID);
    NSLog(@"Sucessfully registered user.");
    [EncryptionKeyManager resetEncryptionKey];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(userRegistrationSuccessful)]) {
        [self.delegate userRegistrationSuccessful];
    }
}

#pragma mark - Generic Request method
/*
 *  For requesting a specific URL and giving a specific tag number.
 */
- (void) requestDataForURL:(NSString *)url andTag:(int)tag{
    
    [RequestBuilder setRequestType:HTTPRequestType];
    
    // Enable XCSRF handling for OData requests
    [RequestBuilder enableXCSRF:YES];
    
    // Initialize the Requesting class with the endpoint URL
    id<Requesting> serviceDocRequest = [RequestBuilder requestWithURL:[[NSURL alloc] initWithString:url]];
    
    // Add username and password for the end point
    [serviceDocRequest setUsername:self.username];
    [serviceDocRequest setPassword:self.password];
    
    /// Set our request headers.
    
    NSLog(@"AppConId in request data: %@", self.clientConn.applicationConnectionID);
    NSLog(@"URL:%@", url);
   
    [serviceDocRequest setRequestMethod:@"GET"];

    [serviceDocRequest addRequestHeader:@"X-SUP-APPCID" value: self.clientConn.applicationConnectionID];        ///added 28.07 testing
    [serviceDocRequest addRequestHeader:@"X-Requested-With" value:@"XmlHttpRequest"];
    [serviceDocRequest addRequestHeader:@"Content-Type" value:@"application/xml; charset=UTF-8"];
    [serviceDocRequest addRequestHeader:@"Accept" value:@"application/xml,application/atom+xml"];
    
    // This class is the delegate callback for any notifications (success and failure)
    [serviceDocRequest setDelegate:self];
    [serviceDocRequest setDidFinishSelector:@selector(handleReqSuccess:)];
    [serviceDocRequest setDidFailSelector:@selector(handleReqFailed:)];
    
    // Each request can be tagged with a number - useful later.
    serviceDocRequest.requestTag = tag; // Useful for a change request.
    
    // Start our request.
    [serviceDocRequest startAsynchronous];
}

#pragma mark - Data Retrieval

/*
 * Public method to start the data retirval.
 */
- (void)beginDataRetrieval{
    
    // Set our class to be the offline delegate (not used but needed later)
    [RequestBuilder setDelegate:self];
    [RequestBuilder setDidFinishSelector:@selector(handleReqSuccess:)];
    [RequestBuilder setDidFailSelector:@selector(handleReqFailed:)];
    
    /*
     * In order to retrieve the data you need 3 components:
     * 1) The service document (the top level of the service with the collection list)
     * 2) The metadata information (service/$metadata)
     * 3) The actual data you want (service/collectionName)
     * So we start with number 1.
     */
    [self requestServiceDocument];
    [self requestMetadata];
    [self requestData];
    
}
- (void) requestServiceDocument{ // Make a request for the service document
    
    [self requestDataForURL:self.odataURL andTag:1];
    NSLog(@"%@", self.odataURL);
}

- (void) requestMetadata{ // Make a request for the metadata of the service.
    [self requestDataForURL:[self.odataURL stringByAppendingString:@"$metadata"] andTag:2];
    NSLog(@"%@", [self.odataURL stringByAppendingString:@"$metadata"]);
}

- (void) requestData{  // Make a request for the actual data.
    [self requestDataForURL:[self.odataURL stringByAppendingString:self.entityName] andTag:3];
    NSLog(@"[self.odataURL stringByAppendingString:self.entityName]");
}

#pragma mark - request callbacks
// Generic failure method once a request fails.
- (void) handleReqFailed:(id)sender{
    
    NSLog(@"Request Failed");
    
    // Tell any listening delegate that there has been a failure.
    if (self.delegate && [self.delegate respondsToSelector:@selector(userRegistrationSuccessful)]) {
        [self.delegate dataRetrievalFailed];
    }
}

// Generic success method once a request is complete.
- (void) handleReqSuccess:(Request *)request{
    
    // Based on which request it is (each request was tagged)
    // Call the correct response parser.
    switch ([request requestTag]) {
        case 1: // This is the service Document
            [self parseServiceDocumentRequest:request];
            break;
        case 2: // This is the metadata.
            [self parseMetadataRequest:request];
            break;
        case 3: // this is the actual data.
            [self parseDataRequest:request];
            break;
        default:
            break;
    }
    NSLog(@"Request number %i Successful", [request requestTag]);
}

#pragma mark - response parsers
- (void) parseServiceDocumentRequest:(Request *)request{
    //Parse the service document
    ODataServiceDocumentParser *svcDocParser = [[ODataServiceDocumentParser alloc] init];
    NSData *svc = [request responseData];   // Retrieve the raw data.
    [svcDocParser parse: svc];              // Parse the data
    self.serviceDocument = [svcDocParser getServiceDocument];   // store in a variable.
    
    [self requestMetadata]; // Finally proceed to stage 2 - get the metadata.
}

// Parse the metadata.
- (void) parseMetadataRequest:(Request *)request{
    
    NSData *metadata = [request responseData]; // Retrieve the raw data.
    
    self.schema1 = parseODataSchemaXML(metadata, self.serviceDocument); // Parse the data.
    
    [self requestData]; // Now we have 1 and 2 - we can get our data.
}

// Parse the data using the service doc and the metadata (AKA the entitySchema).
- (void) parseDataRequest:(Request *)request{
    
    NSData *entriesData = [request responseData]; // Retrieve the raw data.
    
    // Parse the response by passing in the raw data, the schema of the entity we retrieved and the service doc.
    NSMutableArray *results = parseODataEntries(entriesData,
                                                [[[self.serviceDocument getSchema] getCollectionByName:self.entityName] getEntitySchema],
                                                self.serviceDocument);
    
    // Now we are done - so we tell the delegate and pass the response back.
    if (self.delegate && [self.delegate respondsToSelector:@selector(userRegistrationSuccessful)]) {
        [self.delegate dataRetrievalComplete:results];
    }
}

@end
