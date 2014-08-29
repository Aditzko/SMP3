//
//  MAFLogonNGPublicAPI.h
//  MAFLogonNG
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAFLogonManagerNGState.h"
#import "MAFLogonRegistrationData.h"

@protocol MAFLogonNGDelegate;


/**
 Defines the methods can be called using the logon component.
 The methods will present the appropriate UI and performs the necessary steps automatically.
 */
@protocol MAFLogonNGPublicAPI <NSObject>

/**
 Called by the logon manager when an asynchronous method call finished.
 */
@property (nonatomic, assign) id<MAFLogonNGDelegate> logonDelegate;


/**
 Unique identifier of the application on servers and identifies the secure store.
 \warning { It should be set before any other call to the logon. Should only set once on application initialization.}
 */
@property (copy) NSString *applicationId;


/**
 Default values for different parameters.
 The structure should be the same as the MAFLogonOperationsDefaultValues.plist
 For the list of usable keys @see MAFLogonRegistrationOperationContextConstants.h and MAFLogonOperationContextConstants.h
 */
@property (nonatomic, retain) NSMutableDictionary* defaultValues;

/**
 Performs steps to until there is an opened secure store. Asynchronous method.
 Performs registration, get app passcode and creates secure store or opens the secure store.
 Calls back the @see logonFinishedWithError: delegate method when finished.
 */
-(void) logon;

/**
 Performs the steps to lock the secure store. Asynchronous method.
 Calls back the @see lockSecureStoreFinishedWithError: delegate method when finished.
 */
-(void) lockSecureStore;

/**
 Performs the steps to change the secure store password (app passcode). Asynchronous method.
 Calls back the @see changeSecureStorePasswordFinishedWithError: delegate method when finished.
 */
-(void) changeSecureStorePassword;

/**
 Performs the steps to change the backend password stored in the secure store. Asynchronous method.
 Calls back the @see changeBackendPasswordFinishedWithError: delegate method when finished.
 */
-(void) changeBackendPassword;

/**
 Performs the steps to delete the user from the server and set the logon to the initial unregistered state. Asynchronous method.
 Calls bavk the @see deleteUserFinishedWithError: delegate method when finished.
 */
-(void) deleteUser;

/**
 Performs the steps to update the applicatino settings from the server (if the server supports it). Asynchronous method.
 Calls back the @see updateApplicationSettingsFinishedWithError: delegate method when finished.
 */
-(void) updateApplicationSettings;

/**
 Performs the steps to upload E2E trace xml to the server (if the server supports it).
 Calls back the @see updateApplicationSettingsFinishedWithError: delegate method when finished.
 */
-(void) uploadTrace;


/**
 Performs the steps to present the registration information screen. Asynchronous method.
 Calls back the @see registrationInfoFinishedWithError: delegate method when finished.
 */
-(void) registrationInfo;

/**
 Write E2E trace to the Documents folder into file BusinessTransaction.xml. Synchronous call.
 @param error If the operation fails specifies the reason of the error
 @return operation success or not
 */
-(BOOL) writeTraceToFileWithError:(NSError**)error;

/**
 Returns an object from the secure store. Synchronous call.
 @param aKey Identifies the data
 @param error If the retrivation fails specifies the reason of the error
 @return a stored object or nil
 */
- (NSObject *) objectFromSecureStoreForKey:(NSString*)aKey error:(NSError**)error;

/**
 Store object in SecureStore for the given key. Synchronous call.
 @param anObject Object to be stored
 @param aKey Key for the object
 @param error If the store fails specifies the reason of the error
 @return operation success or not
 */
-(BOOL) setObjectInSecureStore:(NSObject*)anObject forKey:(NSString*)aKey error:(NSError**)error;

/**
 Read an object from NSUserDefaults for the given key, return nil, if object does not exist. Synchronous call.
 @param aKey Key for the object
 @return object read from NSUserDefaults
 */
-(NSObject*) objectFromUserDefaultsForKey:(NSString*)aKey;

/**
 Store object in NSUserDefaults for the given key. Synchronous call.
 @param anObject Object to be stored
 @param aKey Key for the object
 */
-(void) setObjectInUserDefaults:(NSObject*)anObject forKey:(NSString*)aKey;

/**
 Method for retrieving all the data which is needed for creating a backend request or downloading the customization bundle. Synchronous call.
 @param error The returning error code if the method fails. Caller should pass the address of an NSError* variable.
 @return MAFLogonRegistrationData instance
 **/
-(MAFLogonRegistrationData*) registrationDataWithError:(NSError**)error;

/**
 Call this method if the application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation method is called in the application and Afaria should work. Afaria passes parameters through this API call.
 @param url In the openURL parameter
 */
-(void) setUrl:(NSURL*)url;

/**
 Returns if secure store locked with default password or not. Synchronous call.
 @return BOOL
 **/
-(BOOL) isDefaultPasswordUsed;

/**
 Turn on E2E Tracing. Synchronous call.
**/
-(void) turnOnE2ETrace;

/**
 Turn off E2E Tracing. Synchronous call.
 **/
-(void) turnOffE2ETrace;

/**
 Set E2E Trace level. Synchronous call.
 @param traceLevel Values:
    E2ELOW	= 1,
    E2EMEDIUM = 2,
    E2EHIGH = 3,
    E2ENONE = 4
 **/
-(void) setE2ETraceLevel:(int)traceLevel;

/**
 Turn on Performance Tracing. Synchronous call.
 **/
-(void) turnOnPerformanceTrace;

/**
 Turn off Performance Tracing. Synchronous call.
 **/
-(void) turnOffPerformanceTrace;

/**
 Describes the state of the LogonManager. Synchronous call.
 @see MAFLogonManagerNGState for more in.
 */
@property (readonly) MAFLogonManagerNGState logonState;

/**
 Retrieves the SecIdentityRef in case of successful mutual certificate based registration if the SecureStore is open.
 @param identityRef address of a SecIdentityRef variable, which will store the returning value on success
 @param anError should contain the address of an NSError*. Will contain the address of an error on return or nil on success.
 */
-(BOOL) getClientIdentity:(SecIdentityRef *)identityRef error:(NSError**)anError;


@end
