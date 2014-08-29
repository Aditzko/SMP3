//
//  SMPClientConnection.h
//  SMPRestClient
//
//  Created by Chug, Satvindar on 12/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef enum E2ETraceLevel {
	E2ELOW	= 1,
	E2EMEDIUM,
    E2EHIGH,
    E2ENONE
} E2ELevel;

extern BOOL isSDM;
extern BOOL needToResetCookies;

@class RequestBuilder;
@class SDMRequestBuilder;
@class Request;
@class SDMHttpRequest;
@class ConnectivityException;
@class SDMConnectivityException;
@class RouteManager;
@class RequestRouteManager;

/*!
 @class SMPClientConnection
 @abstract   Consists of methods used to interact with the underlying client to register connection settings .
 @discussion Using this class the application can initialize/set connection by providing hostname ,port, applicationID,domain and security configuration,
 */

@interface SMPClientConnection : NSObject
{
    
    SecIdentityRef secIdentityRef;
    NSString *applicationConnectionID;
    
}

@property(retain) NSString* applicationID;
@property(retain) NSString* domain;
@property(retain) NSString* securityConfig;
@property(retain) NSString* hostPort;
@property(retain) NSString* applicationConnectionID;        ///////////////////////////////<- war bis zum 28.07 auskommentiert

/**
 * Gets the instance/object of the client connection class.
 * @param applicationID Application Id of the application trying to establish the connection
 * @param domain  server domain
 * @param securityConfig The name of the security configuration authenticating the user against a certain authentication provider
 * @return Returns the instance of the class SMPClientConnection
 * @examples
 * <pre>
 *  SMPClientConnection* clientConn = [SMPClientConnection initializeWithAppID:@"application ID" domain:@"domain" secConfiguration:@"secconfig"];
 * </pre>
 */


+(SMPClientConnection*)initializeWithAppID:(NSString*)applicationID domain:(NSString*)domain secConfiguration:(NSString*)secConfig;
/**
 *  Provides connection properties to the connection class before registration. Provide port as nil if there is no port.
 * @param hostName Host name of the server
 * @param portNumber Port number of the server with which the client talks
 * @param enableHttp Http protocol to be used
 * @return Returns a BOOL indicating if the operation is successful or not.
 * @examples
 * <pre>
 *  SMPClientConnection* clientConn = [SMPClientConnection initializeWithAppID:@"application ID" domain:@"domain" secConfiguration:@"secconfig"];
 * [clientConneciton setConnectionProfileWithHost:@"supServerHost" port:@"supServerPort" farm:nil relayServerUrlTemplate:nil enableHTTP:YES];
 * </pre>
 * @examples
 * In case of relay server
 * <pre>
 *  [clientConneciton setConnectionProfileWithHost:@"relayserver.sybase.com" port:@"80" farm:@"relay.farm" relayServerUrlTemplate:@"/ias_relay_server/client/rs_client.dll" enableHTTP:YES];
 * </pre>
 */

-(BOOL)setConnectionProfileWithHost:(NSString*)hostName port:(NSString*)portNumber farm:(NSString*)farmId relayServerUrlTemplate:(NSString*)urlSuffix enableHTTP:(BOOL)enableHttp;
/**
 * Provides connection properties to the connection class before registration.
 * @param hostPort Host name of the server : Port number of the server with which the client talks
 * @return Returns a BOOL indicating if the operation is successful or not.
 * @examples 
 * <pre>
 *  SMPClientConnection* clientConn = [SMPClientConnection initializeWithAppID:@"application ID" domain:@"domain" secConfiguration:@"secconfig"];
 *  [clientConn setConnectionProfileWithUrl:@"http://supServerHost:supServerPort"];
 * </pre>
 * @examples
 * In case of relay server
 * <pre>
 *  [clientConn setConnectionProfileWithUrl:@"http://relayServerHost:relayServerPort/relay_server_url_suffix/farmId"];
 * </pre>
 */


-(BOOL)setConnectionProfileWithUrl:(NSString*)hostPort;


#pragma mark -
#pragma mark Client Certificate Handling

/**
 * Sets the identity reference (X.509 certificate + private key) for this request; used for secure connections.
 * @param secIdenref identity reference (X.509 certificate + private key)
 * @examples
 * <pre>
 *  SMPClientConnection* clientConn = [SMPClientConnection initializeWithAppID:@"application ID" domain:@"domain" secConfiguration:@"secconfig"];
 *  [clientConn setClientIdentityCertificate:@"secIdenref"];
 *  [clientConneciton setConnectionProfileWithHost:@"supServerHost" port:@"supServerPort" farm:nil relayServerUrlTemplate:nil enableHTTP:YES];
 * </pre>
 */


-(void)setClientIdentityCertificate:(SecIdentityRef)secIdenref;

#pragma mark -
#pragma mark ApplicationConnectionID Handling

/**
 * Sets the application Connection ID to ClientConnection.
 * @param appConnectionID application Connection ID
 * @examples
 * <pre>
 *  SMPClientConnection* clientConn = [SMPClientConnection initializeWithAppID:@"application ID" domain:@"domain" secConfiguration:@"secconfig"];
 *  [clientConneciton setConnectionProfileWithHost:@"supServerHost" port:@"supServerPort" farm:nil relayServerUrlTemplate:nil enableHTTP:YES];
 *  [clientConn setApplicationConnectionID:@"application Connection ID"];
 * </pre>
 */


-(void)setApplicationConnectionID:(NSString*)appConnectionID;

/**
 * @internal
 */

-(NSString*)applicationConnectionID;


#pragma mark -
#pragma mark E2E Tracing

/**
 *  Enables the tracing and starts generating Business Transaction XML
 * @examples
 * <pre>
 *  @try{
 *      SMPClientConnection* clientConn = [SMPClientConnection initializeWithAppID:@"application ID" domain:@"domain" secConfiguration:@"secconfig"];
 *      [clientConneciton setConnectionProfileWithHost:@"supServerHost" port:@"supServerPort" farm:nil relayServerUrlTemplate:nil enableHTTP:YES];
 *   //On board user
 *   //...
 *      [clientConn startTrace];
 *   }
 *  @catch(NSException *e){
 *      // catch exception here
 *  }
 * </pre>
 */

-(void)startTrace;
/**
 * Disables the tracing and stops generating BTX.
 * @examples
 * <pre>
 *  @try{
 *      SMPClientConnection* clientConn = [SMPClientConnection initializeWithAppID:@"application ID" domain:@"domain" secConfiguration:@"secconfig"];
 *      [clientConneciton setConnectionProfileWithHost:@"supServerHost" port:@"supServerPort" farm:nil relayServerUrlTemplate:nil enableHTTP:YES];
 *   //On board user
 *   //...
 *      [clientConn startTrace];
 *   //Request response
 *      [clientConn stopTrace];
 *   }
 *  @catch(NSException *e){
 *      // catch exception here
 *  }
 * </pre>
 */
-(void)stopTrace;

/**
 * Uploads the generated BTX to solution manager server via SAP Mobile Platform.
 * @param userName User Name that will be authorised by a predefined security provider
 * @param password Password for that user
 * @param error:      A double pointer to the error object in case the operation results in an error
 * @discussion This API will upload the generated BTX to Solution manager .If fails will throw respective error.
 * @examples
 * <pre>
 *      SMPClientConnection* clientConn = [SMPClientConnection initializeWithAppID:@"application ID" domain:@"domain" secConfiguration:@"secconfig"];
 *      [clientConneciton setConnectionProfileWithHost:@"supServerHost" port:@"supServerPort" farm:nil relayServerUrlTemplate:nil enableHTTP:YES];
 *   //On board user
 *   //...
 *      [clientConn startTrace];
 *   //Request response
 *      [clientConn stopTrace];
 *      NSError* error = nil;
 *      [clientConn uploadTraceWithUserName:@"username" passWord:@"password" error:&error];
 *      if (!error)
 *      {
 *      // Further processing
 *      }
 * </pre>
 */

-(void)uploadTraceWithUserName:(NSString*)username passWord:(NSString*)password error:(NSError**)error;

/**
 * @internal
 */

-(void)dumpToTextFile:(NSString*)xml;

/**
 * Set the trace level, default is E2EMEDIUM.If tracing is enabled, "SAP-PASSPORT" and "X-CorrelationID" headers are set and filled with values to enable SAP Passport functionality.
 * @examples
 * <pre>
 *      SMPClientConnection* clientConn = [SMPClientConnection initializeWithAppID:@"application ID" domain:@"domain" secConfiguration:@"secconfig"];
 *      [clientConneciton setConnectionProfileWithHost:@"supServerHost" port:@"supServerPort" farm:nil relayServerUrlTemplate:nil enableHTTP:YES];
 *   //On board user
 *   //...
 *      [clientConn setTraceLevel:E2EHIGH];
 *      [clientConn startTrace];
 *   //Request response
 *      [clientConn stopTrace];
 *      NSError* error = nil;
 *      [clientConn uploadTraceWithUserName:@"username" passWord:@"password" error:&error];
 *      if (!error)
 *      {
 *      // Further processing
 *      }
 * <pre>
 */
- (void)setTraceLevel:(E2ELevel)value_in;

/**
 * @internal
 */
- (int)getTraceLevel;


@end
