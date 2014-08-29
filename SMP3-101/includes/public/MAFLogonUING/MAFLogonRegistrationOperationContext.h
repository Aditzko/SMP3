//
//  MAFLogonRegistrationOperationContext.h
//  MAFLogonManagerNG
//
//  Copyright (c) 2012 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAFLogonOperationContext.h"
#import "MAFLogonRegistrationOperationContextConstants.h"

@interface MAFLogonRegistrationOperationContext : MAFLogonOperationContext

/**
 Application id
 **/
@property (copy) NSString* applicationId;

/**
 Url of the server
 **/
@property (copy) NSString* serverHost;

/**
 Domain for server
 **/
@property (copy) NSString* domain;

/**
 Resource path on the server
 **/
@property (copy) NSString* resourcePath;

/**
 Port of the server
 **/
@property (assign) int serverPort;

/**
 Whether the server should be accessed in a secure way
 **/
@property (assign) BOOL isHttps;

/**
 Username in the backend
 **/
@property (copy) NSString* backendUserName;

/**
 Password for the backend user
 **/
@property (copy) NSString* backendPassword;

/**
 FarmId of the server
 **/
@property (copy) NSString* farmId;

/**
 Id of the communicator manager which will be used for performing the logon
 **/
@property (copy) NSString* communicatorId;

/**
 Security configuration
 **/
@property (copy) NSString* securityConfig;

/**
 Connection data
 **/
@property (copy) NSMutableDictionary* connectionData;

/**
 Mobile User
 **/
@property (copy) NSString* mobileUser;

/**
 Activation Code
 **/
@property (copy) NSString* activationCode;

/**
 Indentifies the type of the web server: needed for SUP RelayServer mode. Determined automatically during registration if possible
 */
@property (copy) NSString *webServerType;

/**
 Marks whether the selected communicator was detected directly through a response or not.
 */
@property (assign) BOOL communicatorDetectedByResponse;

/**
 The key string which identifies the client on the gateway. The value will be used as adding the parameter: sap-client=<gateway client>
 */
@property (copy) NSString *gatewayClient;

/**
 The custom path of the ping url on the gateway.
 */
@property (copy) NSString *gatewayPingPath;

/**
Indicates automatic Logon needed or not
 */
@property (assign) BOOL automaticLogon;

@end
