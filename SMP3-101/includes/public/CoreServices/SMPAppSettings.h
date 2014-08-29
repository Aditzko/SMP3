//
//  SMPAppSettings.h
//  SMPRestClient
//
//  Created by Chug, Satvindar on 12/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SMPClientConnection.h"

// Attributes defining password policy used by DataVault

/**
 * @internal
 The class contains the parameters which defines Data Vault Password Policy and developer can call getPasswordPolicy method to retrieve all the paramters set in SCC. 
 */

@interface DataVaultPasswordPolicy : NSObject {
    BOOL defaultPasswordAllowed;
    NSInteger minLength;
    BOOL hasDigits;
    BOOL hasUpper;
    BOOL hasLower;
    BOOL hasSpecial;
    NSInteger expirationDays;
    NSInteger minUniqueChars;
    NSInteger lockTimeout;
    NSInteger retryLimit;
}

@property (nonatomic, assign, readwrite) BOOL defaultPasswordAllowed;
@property (nonatomic, assign, readwrite) NSInteger minLength;
@property (nonatomic, assign, readwrite) BOOL hasDigits;
@property (nonatomic, assign, readwrite) BOOL hasUpper;
@property (nonatomic, assign, readwrite) BOOL hasLower;
@property (nonatomic, assign, readwrite) BOOL hasSpecial;
@property (nonatomic, assign, readwrite) NSInteger expirationDays;
@property (nonatomic, assign, readwrite) NSInteger minUniqueChars;
@property (nonatomic, assign, readwrite) NSInteger lockTimeout;
@property (nonatomic, assign, readwrite) NSInteger retryLimit;

@end

/*!
 @class SMPAppSettings
 @abstract   Consists of methods used to retrieve setting details required by the application.
 @discussion  This class implements instance methods to fetch settings like end-points for application data access, push endpoint, customizationbundleID and password policy .
 */

@class RequestBuilder;
@class SDMRequestBuilder;
@class Request;
@class SDMHttpRequest;
@class ConnectivityException;
@class SDMConnectivityException;

@interface SMPAppSettings : NSObject

@property(retain)SMPClientConnection* clientConnection;
@property(retain)NSString* username;
@property(retain)NSString* password;

/**
 * Gets the singleton instance/object of the AppSettings class.
 * @param clientConn Object of SMPClientConnection class 
 * @param userName User Name that will be authorised by a predefined security provider
 * @param password Password for that user
 * @return Returns the instance of the class SMPAppSettings
 * @examples
 * <pre>
 *  SMPAppSettings* appSettings = [SMPAppSettings initializeWithConnection:clientConn userName:@"username" password:@"password"];
 * </pre>
 */


+(SMPAppSettings*)initializeWithConnection:(SMPClientConnection *)clientConn userName:(NSString*)userName password:(NSString*)password;

/**
 * Retrieves the password policy set by the administrator in SCC for the application.
 * @param error Double pointer to the error object if the method results in an error.
 * @return Returns the structure containing the password policy.
 * @examples
 * <pre>
 *  SMPAppSettings* appSettings = [SMPAppSettings initializeWithConnection:clientConn userName:@"username" password:@"password"];
 *  NSError* error = nil;
 *  DataVaultPasswordPolicy *dvppStruct = [appSettings getPasswordPolicy:&error];
 *  if (!error)
 *  {
 *      // Further processing
 *  }
 * </pre>
 */

-(DataVaultPasswordPolicy*)getPasswordPolicy:(NSError **)error;

/**
 * Retrieves the application end-point with which the application can access business data.
 * @param error Double pointer to the error object if the method results in an error.
 * @return Returns the end-point as a string object (URL/URN)
 * @examples 
 * <pre>
 * SMPAppSettings* appSettings = [SMPAppSettings initializeWithConnection:clientConn userName:@"username" password:@"password"];
 * NSError *error = nil;
 * NSString *appEndPoint = [appSettings getApplicationEndpointWithError:&error];
 * if (!error)
 * {
 *   //Continue processing
 * }
 * </pre>
 */


-(NSString*)getApplicationEndpointWithError:(NSError**)error;
/**
 * Retrieves the push end-point which the enterprise back-end can use to push data to the ODP client via the server.
 * This end-point will be registered with the enterprise back-end during the process of subscription.
 * @param error Double pointer to the error object if the method results in an error.
 * @return Returns the end-point as a string object (URL/URN)
 * @examples
 * <pre>
 * -(void)userRegistrationSuccessful:(SMPUserManager*)userManager
 * {
 *   NSLog(@"userRegistrationSuccessful...");
 *   NSString* appConID= [userManager applicationConnectionID];
 *   SMPAppSettings* appSettings = [SMPAppSettings initializeWithConnection:clientConn userName:@"username" password:@"password"];
 *   NSError *error=nil;
 *   NSString *pushEndpoint = [appSettings getPushEndpointWithError:&error];
 *   if(!error){
 *    NSLog(@"pushEndpoint : %@",pushEndpoint);
 *   }
 * </pre>
 */

-(NSString*)getPushEndpointWithError:(NSError**)error;

/**
 * Returns all the settings in Key-Value pair.
 * @param error Double pointer to the error object if the method results in an error.
 * @return Returns all the settings as NSDictionary object.
 * @examples
 * <pre>
 *  SMPAppSettings* appSettings = [SMPAppSettings initializeWithConnection:clientConn userName:@"username" password:@"password"];
 *  NSError* error = nil;
 *  NSDictionary* configProp = [appSettings getConfigPropertyMapWithError:&error];
 *  if (!error)
 *  {
 *      // Further processing
 *  }
 * </pre>
 */


-(NSDictionary*)getConfigPropertyMapWithError:(NSError**)error;


/**
 * Retrieves the Configuration Property by providing key.
 * @param configKey  Key for the desired configuration property
 * @param error Double pointer to the error object if the method results in an error.
 * @return Returns the Configuration Property as a string object.
 * @examples
 * <pre>
 *  SMPAppSettings* appSettings = [SMPAppSettings initializeWithConnection:clientConn userName:@"username" password:@"password"];
 *  NSError* error = nil;
 *  NSString* configProp = [appSettings getConfigProperty:configKey error:&error];
 *  if (!error)
 *  {
 *      // Further processing
 *  }
 * </pre>
 */


-(NSString*)getConfigProperty:(NSString*)configKey error:(NSError**)error;

/**
 * Updates the config property by providing list of settings as a NSDictionary Object.
 * @param settingsList  List of settings as key-value
 * @param error Double pointer to the error object if the method results in an error.
 * @return Returns BOOL whether successfully updated or not.
 * @examples
 * <pre>
 *  SMPAppSettings* appSettings = [SMPAppSettings initializeWithConnection:clientConn userName:@"username" password:@"password"];
 *  NSDictionary *props = [NSMutableDictionary dictionary];
 *  [props setValue:@"654321" forKey:@"d:ApnsDeviceToken"];
 *  NSError* error = nil;
 *  BOOL isSuccess = [appSettings setConfigProperty:props error:&error];
 *  if (!error)
 *  {
 *      // Further processing
 *  }
 * </pre>
 */

-(BOOL)setConfigProperty:(NSDictionary*)settingsList error:(NSError**)error;

/**
 * Returns or downloads Customization Resources as binary data.
 * @param customizationResource:  Customization Resource name.
 * @param error Double pointer to the error object if the function results in an error.
 * @discussion Returns the Customization Resource(zip or jar file) as binary data.
 * @return Returns the Customization Resource as binary data.
 * @examples
 * <pre>
 *   SMPAppSettings* appSettings = [SMPAppSettings initializeWithConnection:clientConn userName:@"username" password:@"password"];
 *  NSError* error = nil;
 *  NSData* customResourceBundleData = [appSettings getCustomizationResourceBundleWithCustomizationResource:customizationResource error:&error];
 *  if (!error)
 *  {
 *      // Further processing
 *  }
 * </pre>
 */


-(NSData*)getCustomizationResourceBundleWithCustomizationResource:(NSString*) customizationResource error:(NSError**)error;
/**
 * Releases the username and password provided while initializing app settings class.
 * @param error Double pointer to the error object if the method results in an error.
 * @examples 
 * <pre>
 *  SMPAppSettings* appSettings = [SMPAppSettings initializeWithConnection:clientConn userName:@"username" password:@"password"];
 *  NSError* error = nil;
 *  [appSettings releaseStoredCredentialsWithError:&error];
 *  if (!error)
 *  {
 *      // Further processing
 *  }
 * </pre>
 */


-(void)releaseStoredCredentialsWithError:(NSError**)error;

@end
