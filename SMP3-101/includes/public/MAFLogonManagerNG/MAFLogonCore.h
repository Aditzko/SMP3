//
//  MAFLogonCore.h
//  MAFLogonCore
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAFLogonCoreDelegate.h"

@class MAFLogonContext;
@class MAFLogonCoreState;

#define keyMAFLogonApplicationId                        @"keyMAFLogonApplicationId"

/**
 Main component for logon related activities.
 */
@interface MAFLogonCore : NSObject

/**
 Called by the logon core when an asynchronous method call finished.
 */
@property (nonatomic, assign) id<MAFLogonCoreDelegate> logonCoreDelegate;
/**
 Marks whether the trace should be enabled.
 */
@property (assign) BOOL traceEnabled;
/**
 Marks whether the performanc trace should be enabled.
 */
@property (assign) BOOL performanceTraceEnabled;
/**
 Describes the level of the trace
 */
@property (assign) int traceLevel;

/**
 Desigated initializer. 
 @param applicationId the applicationId identifies the app on the SUP server and also used to identify the SecureStore used by the logon. If nil the keyMAFApplicationId set in the info.plist will be used.
 */
-(id) initWithApplicationId:(NSString*)applicationId;

/**
 Registeres using the context parameter.
 Only the registrationContext field will be used.
 Long running operation, calls delegate method when finished
 @param logonContext the caller can pass the registration context as part of the context
*/
-(void) registerWithContext:(MAFLogonContext*)logonContext;

/**
 Long running operation, calls delegate method when finished
 */
-(void) unregister;

/**
 Long running operation, calls delegate method when finished
 */
-(void) cancelRegistration;

/**
 Creates a secure store and saves the registration information to it.
 Only the passwordPolicy field will be used from the context in the parameter but only in case if the server didn't provide a policy.
 @param aPasscode a passcode which will protect the secure store. Nil for default passcode. Should match to the PasswordPolicy
 @param logonContext the caller can pass a password policy as part of the context but it will be used if the server didn't provide a policy
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
*/
-(BOOL) persistRegistration:(NSString*)aPasscode logonContext:(MAFLogonContext*)logonContext error:(NSError**)anError;

/**
 Returns the current state of the Logon
*/
-(MAFLogonCoreState*) state;

/**
 Downloads the settings from the server and stores it in the context - accessible with getContext.
 Long running operation, calls delegate method when finished
 */
-(void) refreshApplicationSettings;

/**
 Retrieves the context for the current state of the Logon.
 The context contains default data before registration. Contains the context which was used during registration after a successful registration. This context is stored in the secure store during the persistRegistration method.
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
*/
-(MAFLogonContext*) getContext:(NSError**)anError;

/**
 Locks the secure store.
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
*/
-(BOOL) lockSecureStore:(NSError**)anError;

/**
 Opens the secure store
 @param aPasscode passcode to open the store with
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
*/
-(BOOL) unlockSecureStore:(NSString*)aPasscode error:(NSError**)anError;

/**
 Changes the passcode of the secure store which protects the store.
 @param oldPasscode the current passcode of the store. Nil for default password.
 @param newPasscode the new passcode for the store. Nil for default passcode. Should match to the PasswordPolicy applied on the store.
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
*/
-(BOOL) changePasscode:(NSString*)oldPasscode newPasscode:(NSString*)newPasscode error:(NSError**)anError;

/**
 Checks the registered server with the new password and stores it in the secure store.
 Long running operation, calls delegate method when finished
 @param newPassword the new password that will be stored
 */
-(void) changeBackendPassword:(NSString*)newPassword;

/**
 Saves an object to the secure store with the given key.
 @param anObject the object to save in the secure store. Should implement the NSCoding protocol.
 @param aKey the key for which the object will be stored.
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
*/
-(BOOL) setObjectInSecureStore:(NSObject<NSCoding>*)anObject key:(NSString*)aKey error:(NSError**)anError;

/**
 Retrieves an object from the secure store
 @param aKey the key for which the object was stored.
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
*/
-(NSObject<NSCoding>*) objectFromSecureStore:(NSString*)aKey error:(NSError**)anError;

/**
 Uploads the trace to the registered server.
 Long running operation, calls delegate method when finished
 */
-(void) uploadTrace;

/**
 Saves the trace to a local file.
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
*/
-(BOOL) saveTrace:(NSError**)anError;

/**
 Call this method if the application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation method is called in the application and the application should use afaria.
 @param url In the openURL parameter
 */
-(void) setUrl:(NSURL*)url;

/**
 Set the SSO pin code. Return true if the passcode is correct
 @param aPin The pin code
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
 */
-(BOOL)setMCIMSSOPin:(NSString*)aPin error:(NSError**)anError;

/**
 At registration process the user could skip the MCIM usage.
 Decouple from MCIM if the user is registered.
 */
-(void)skipMCIM;

/**
 Retrieves the SecIdentityRef in case of successful mutual certificate based registration if the SecureStore is open.
 @param identityRef address of a SecIdentityRef variable, which will store the returning value on success
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
 */
-(BOOL) getClientIdentity:(SecIdentityRef *)identityRef error:(NSError**)anError;

/**
 Set username and password for Afaria configuration downloading.
 @param username
 @param password
**/

-(BOOL) setAfariaCredentialWithUser:(NSString*)user password:(NSString*)password error:(NSError**)anError;

/**
 Retrieves the SecIdentityRef in case of successful mutual certificate based registration if the SecureStore is open.
 Designed for very special cases where the MAFLogonCore instance is unaccessble - for example if used with a Cordova plugin.
 @param identityRef address of a SecIdentityRef variable, which will store the returning value on success
 @param anAppId application identifier which was used during the registration
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
 */
+(BOOL) getClientIdentity:(SecIdentityRef *)identityRef applicationID:(NSString*)anAppId error:(NSError**)anError;

/**
 Call this method if the application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation method is called in the application and the application should use afaria.
 Designed for very special cases where the MAFLogonCore instance is unaccessble - for example if used with a Cordova plugin.
 @param url In the openURL parameter
 @param anAppId application identifier which was used during the registration
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success. 
 */
+(BOOL) setUrl:(NSURL*)url applicationId:(NSString*)anAppId error:(NSError**)anError;

@end
