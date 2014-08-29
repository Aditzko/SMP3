//
//  MAFLogonRegistrationOperationContextConstants.h
//  MAFLogonManagerNG
//
//  Copyright (c) 2012 SAP AG. All rights reserved.
//

#pragma mark Registration keys
/**
 Identifies the ApplicationId field in the operation context. Mandatory field for registration.
 **/
#define keyMAFLogonOperationContextApplicationId        @"keyMAFLogonOperationContextApplicationId"

/**
 Identifies ServerURL field in the operation context. Mandatory field for registration.
 **/
#define keyMAFLogonOperationContextServerHost            @"keyMAFLogonOperationContextServerHost"

/**
 Identifies ServerDomain field in the operation context.
 **/
#define keyMAFLogonOperationContextServerDomain @"keyMAFLogonOperationContextServerDomain"

/**
 Identifies ResourcePath field in the operation context. Optional field for registration.
 **/
#define keyMAFLogonOperationContextResourcePath            @"keyMAFLogonOperationContextResourcePath"

/**
 Identifies the ServerPort field in the operation context. Mandatory field for registration.
 **/
#define keyMAFLogonOperationContextServerPort           @"keyMAFLogonOperationContextServerPort"

/**
 Identifies the Secure ServerPort field in the operation context. Mandatory field for registration.
 **/
#define keyMAFLogonOperationContextServerPortSecure           @"keyMAFLogonOperationContextServerPortSecure"

/**
 Identifies the Non-secure ServerPort field in the operation context. Mandatory field for registration.
 **/
#define keyMAFLogonOperationContextServerPortNonSecure           @"keyMAFLogonOperationContextServerPortNonSecure"

/**
 Identifies the isHttps field in the operation context. Mandatory field for registration.
 **/
#define keyMAFLogonOperationContextIsHttps              @"keyMAFLogonOperationContextIsHttps"

/**
 Identifies the BackendUserName field in the operation context. Mandatory field for registration.
 **/
#define keyMAFLogonOperationContextBackendUserName      @"keyMAFLogonOperationContextBackendUserName"

/**
 Identifies the BackendPassword field in the operation context. Mandatory field for registration.
 **/
#define keyMAFLogonOperationContextBackendPassword      @"keyMAFLogonOperationContextBackendPassword"

/**
 Identifies the AfariaCertificatePassword field in the operation context. Mandatory field for registration.
 **/
#define keyMAFLogonOperationContextAfariaCertificatePassword      @"keyMAFLogonOperationContextAfariaCertificatePassword"

/**
 Identifies the FarmId field in the operation context. Optional in registration.
 **/
#define keyMAFLogonOperationContextFarmId               @"keyMAFLogonOperationContextFarmId"

/**
 Identifies the Certificate field in the operation context
 **/
#define keyMAFLogonOperationContextCertificate          @"keyMAFLogonOperationContextCertificate"

/**
 Identifies the CommunicatorId field in the operation context
 **/
#define keyMAFLogonOperationContextCommunicatorId       @"keyMAFLogonOperationContextCommunicatorId"

/**
 Identifies the SecurityConfig field in the operation context
 **/
#define keyMAFLogonOperationContextSecurityConfig       @"keyMAFLogonOperationContextSecurityConfig"

/**
 Identifies the default PasswordPolicy field in the operation context
 **/
#define keyMAFLogonOperationContextPasswordPolicy       @"keyMAFLogonOperationContextPasswordPolicy"

/**
 Identifies the ConnectionData dictionary in the operation context
 **/
#define keyMAFLogonOperationContextConnectionData       @"keyMAFLogonOperationContextConnectionData"


/**
 Identifies the Mobile User field in the operation context
 **/
#define keyMAFLogonOperationContextMobileUser           @"keyMAFLogonOperationContextMobileUser"

/**
 Identifies the Activation Code field in the operation context
 **/
#define keyMAFLogonOperationContextActivationCode       @"keyMAFLogonOperationContextActivationCode"


#pragma mark ConnectionData keys - filled by the MAFLogonManagerNG after a successful registration

/**
 Identifies the ConnectionId field in ConnectionData
 **/
#define keyMAFLogonConnectionDataConnectionId           @"keyMAFLogonConnectionDataConnectionId"

/**
 Identifies the ChallengeContext dictionary in ConnectionData
 **/
#define keyMAFLogonConnectionDataChallengeContext       @"keyMAFLogonConnectionDataChallengeContext"

/**
 Identifies the Cookies array in ConnectionData
 **/
#define keyMAFLogonConnectionDataCookies                @"keyMAFLogonConnectionDataCookies"


/**
 Identifies the Http Response Headers dictionary in ConnectionData
 **/
#define keyMAFLogonConnectionDataHttpResponseHeaders    @"keyMAFLogonConnectionDataHttpResponseHeaders"

/**
 Identifies the URL field in Connection Data
 **/
#define keyMAFLogonConnectionDataBaseURL        @"keyMAFLogonConnectionDataBaseURL"

/**
 Identifies the Registration URL field in Connection Data
 **/
#define keyMAFLogonConnectionDataRegistrationURL        @"keyMAFLogonConnectionDataRegistrationURL"

/**
 Indentifies the type of the web server: needed for SUP RelayServer mode. Determined automatically during registration if possible
 */
#define keyMAFLogonOperationContextWebServerType    @"keyMAFLogonOperationContextWebServerType"

/**
 Marks whether the selected communicator was detected directly through a response or not.
 */
#define keyMAFLogonOperationContextCommunicatorDetectedByResponse    @"keyMAFLogonOperationContextCommunicatorDetectedByResponse"

/**
 The key string which identifies the client on the gateway. The value will be used as adding the parameter: sap-client=<gateway client>
 */
#define keyMAFLogonOperationContextGatewayClient        @"keyMAFLogonOperationContextGatewayClient"

/**
 The custom path of the ping url on the gateway.
 */
#define keyMAFLogonOperationContextGatewayPingPath      @"keyMAFLogonOperationContextGatewayPingPath"

/**
Indicates automatic Logon needed or not
 */
#define keyMAFLogonOperationContextAutomaticLogon   @"keyMAFLogonOperationContextAutomaticLogon"
