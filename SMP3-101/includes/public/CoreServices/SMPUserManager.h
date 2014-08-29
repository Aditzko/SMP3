//
//  SMPUserManager.h
//  SMPRestClient
//
//  Created by Chug, Satvindar on 12/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SMPClientConnection.h"
/*!
 @protocol SMPUserManagerDelegate
 @abstract   The protocol to which any class implementing the notification listeners has to ahdhere to
 @discussion  This protocol has to be adhered to by any class that implements the success and failure notification delegates and this class has to be passed to the delegate variable of the user manager class object
 */
@class SMPUserManager;


@protocol SMPUserManagerDelegate<NSObject>
@required

/**
 * The success listener delegate which will be called by the underlying framework when the user registration is successful. This is true in case of asynchronous user registration only.
 * @examples
 * <pre>
 
 *  -(IBAction)buttonsPressed:(UIButton*)button{
 *
 *      [SMPUserManager setDelegate:self];
 *      SMPUserManager* userManager = [SMPUserManager initializeWithConnection:clientConn];
 *
 *  }
 *
 *  -(void)userRegistrationSuccessful:(SMPUserManager*)userManager
 *  {
 *      // Successful post-processing
 *  }
 * </pre>
 */

-(void)userRegistrationSuccessful:(SMPUserManager*)userManager;

/**
 * The failure listener delegate which will be called by the underlying framework when the user registration has failed and the reason for failure will be propagated through an error object. This is true in case of asynchronous user registration only.
 * @examples
 * <pre>
 *  -(IBAction)buttonsPressed:(UIButton*)button{
 
 *      [SMPUserManager setDelegate:self];
 *      SMPUserManager* userManager = [SMPUserManager initializeWithConnection:clientConn];
 *
 *  }
 *
 *  -(void)userRegistrationFailed:(SMPUserManager*)userManager
 *  {
 *      // Error handling using the error object
 *  }
 * </pre>
 */

-(void)userRegistrationFailed:(SMPUserManager*)userManager;


@end

/*!
 @protocol SMPCaptchaChallengeDelegate
 @abstract   The protocol to which any class implementing the Captcha Challenge listeners has to ahdhere to
 @discussion  This protocol has to be adhered to by any class that implements the captcha challenge  delegates.
 */

@protocol SMPCaptchaChallengeDelegate <NSObject>
@required

/**
 * The captcha challenge delegate which will be called by the underlying framework when captcha challenge is required during the user registration. This is supported in case of SAP Mobile Platform, enterprise edition, cloud version onboarding only.
 * @examples
 * <pre>
 *  -(IBAction)buttonsPressed:(UIButton*)button{
 *
 *      [SMPUserManager setCaptchaChallengeDelegate:self];
 *      SMPUserManager* userManager = [SMPUserManager initializeWithConnection:clientConn];
 *
 *  }
 *
 *  -(NSString*)didReceiveCaptchaChallenge:(NSString*)base64ImageString
 *  {
 *      // Return text String input from user.
 *  }
 * </pre>
 */

-(NSString*)didReceiveCaptchaChallenge:(NSString*)base64ImageString;

@end



/*!
 @class SMPUserManager
 @abstract   The class which has all the functions to register/de-register a user
 @discussion  All the function calls in this class have various ways of provisioning settings on to the client and register the user with the help of these settings. We can also check if a user is registered and delete the user as and when necessary
 
 
 
 <br/><br/>
 <b>Settings Exchange Error Codes</b>
 <br/><br/>
 <ul>
 <li>70002   -  Password Policy Not Enabled.</li>
 <li>70003   -  Error Fetching Push End Point.</li>
 <li>70004   -  Empty Parameters Passed.</li>
 <li>70005   -  Non Editable Properties.  This Error is particularly thrown for setConfiguration Property API where properties set are not editable.</li>
 <li>70006   -  Customization Bundle Data Fetch Error.</li>
 <li>70007   -  Customization Bundle Not Available.</li>
 </ul>
 
 <br/><br/>
 <b>User Registration Error Codes</b>
 <br/><br/>
 
 <ul>
 <li>70001	  -	Application Connection Identifier is null. User is not registered.</li>
 <li>70008   -  Parser Error.</li>
 <li>71000   -  SMPInternalError. Error occurred in Rest Client.</li>
 </ul>
 <br/>
 */

@class RequestBuilder;
@class SDMRequestBuilder;
@class Request;
@class SDMHttpRequest;
@class ConnectivityException;
@class SDMConnectivityException;
@class RouteManager;
@class RequestRouteManager;

@interface SMPUserManager : NSObject

@property(retain)SMPClientConnection* clientConnection;
@property(retain)NSString* applicationConnectionID;
@property(retain)NSError* registrationError;

/**
 * Gets the instance/object of the SMPUserManager class.
 * @param clientConn SMPClientConnection object
 * @return Returns the instance of the class SMPUserManager
 * @examples
 * <pre>
 *  SMPUserManager* userManager = [SMPUserManager initializeWithConnection:clientConn];
 * </pre>
 */

+(SMPUserManager*)initializeWithConnection:(SMPClientConnection*)clientConn;

/**
 * Registers the client with the server by automatically creating a user with the help of a pre-defined authentication mechanism
 * @param userName User Name that will be authorised by a predefined security provider
 * @param loginPassword Password for that user
 * @param error A double pointer to the error object that the application will pass to the function call and which will be populated by the function call in case of any errors within.
 * @param isSynchronous A flag indicating whether the user registration has to happen synchronously or in an asynchronous manner
 * @return Returns a BOOL indicating if the user registration has been successful. Significant in case of synchronous registration only.
 * @examples
 * Synchronous Registration
 * <pre>
 *  SMPUserManager* userManager = [SMPUserManager initializeWithConnection:clientConn];
 *  NSError* error = nil;
 *  if([userManager registerUser:@"username" password:@"password" error:&error isSyncFlag:YES])
 *  {
 *      // Further processing
 *  } else
 *  {
 *      // Error handling using the error object defined above
 *  }
 * </pre>
 *  <br/>
 * @examples
 * Asynchronous Registration
 * <pre>
 *  SMPUserManager* userManager = [SMPUserManager initializeWithConnection:clientConn];
 *  NSError* error = nil;
 *  [SMPUserManager setDelegate:self]; // The class implementing the listener methods should adhere to <SMPUserManagerDelegate> protocol
 *  [userManager registerUser:@"username" password:@"password" error:&error isSyncFlag:NO];
 * </pre>
 */


-(BOOL)registerUser:(NSString*)userName password:(NSString*)loginPassword error:(NSError**)error isSyncFlag:(BOOL)isSynchronous;

/**
 * Static method which registers the client with the server by automatically creating a user with the help of a pre-defined authentication mechanism along with Captcha Text
 * @param userName User Name that will be authorised by a predefined security provider
 * @param loginPassword Password for that user
 * @param captchaText  Captcha Text provided by the user shown in the image
 * @param error A double pointer to the error object that the application will pass to the function call and which will be populated by the function call in case of any errors within.
 * @param isSynchronous A flag indicating whether the user registration has to happen synchronously or in an asynchronous manner
 * @return Returns a BOOL indicating if the user registration has been successful. Significant in case of synchronous registration only.
 * @examples
 * <pre>
 *  NSError* error = nil;
 *  [userManager registerUser:@"username" password:@"password" captchaText:@"captchText" error:&error isSyncFlag:NO])
 * </pre>
 */


-(BOOL)registerUser:(NSString*)userName password:(NSString*)loginPassword captchaText:(NSString*)captchaText error:(NSError**)error isSyncFlag:(BOOL)isSynchronous;

/**
 * Static Method which deletes the application connection/user with which the application has established a connection
 * @param appConID Application Connection Id of the user to be deleted
 * @param userName User Name that will be authorised by a predefined security provider
 * @param password Password for that user
 * @param error A double pointer to the error object that the application will pass to the function call and which will be populated by the function call in case of any errors within.
 * @return A BOOL is returned indicating if the user has been deleted or not.
 * @examples
 * <pre>
 *  NSError* error = nil;
 *  if([userManager deleteUser:@"username" password:@"password" error:&error];)
 *  {
 *      // Further Processing
 *  }
 *  else
 *  {
 *      // Further Error processing using error object
 *  }
 * </pre>
 */


-(BOOL)deleteUser:(NSString*)userName password:(NSString*)passWord error:(NSError**)error;

/**
 * Setter for the user manager listener.This is a class method to register the user manager listener .
 * @param listener A listener object whose definition adheres to the  <SMPUserManagerDelegate> protocol that has to be implemented by the client to get the pushed data
 * @examples 
 * <pre>
 * // register the client as delegate for this request
 * [SMPUserManager setDelegate:self];
 * SMPUserManager* userManager = [SMPUserManager initializeWithConnection:clientConn];
 * [userManager registerUser:@"username" password:@"password" error:&error isSyncFlag:NO];
 * ...
 * }
 * </pre>
 */
+(void)setDelegate:(id<SMPUserManagerDelegate>)delegate;

/**
 * Getter for the user manager listener.This is a class method to fetch the user manager listener object.
 * @return Instance of the listener object.
 */

+(id<SMPUserManagerDelegate>)getDelegate;


/**
 * Setter for the Captcha Challenge listener.This is a class method to register for the Captcha Challenge Listener
 * @param listener A listener object whose definition adheres to the  <SMPCaptchaChallengeDelegate> protocol that has to be implemented by the application to receive Captcha Challenge
 * @examples
 * <pre>
 * // register the client as delegate for this request
 * [SMPUserManager setCaptchaChallengeDelegate:self];
 * SMPUserManager* userManager = [SMPUserManager initializeWithConnection:clientConn];
 * [userManager registerUser:@"username" password:@"password" error:&error isSyncFlag:NO];
 * ...
 * }
 *  -(NSString*)didReceiveCaptchaChallenge:(NSString*)base64ImageString
 *  {
 *      // Return text String input from user.
 *  }
 * </pre>
 */


+(void)setCaptchaChallengeDelegate:(id<SMPCaptchaChallengeDelegate>)delegate;

/**
 * Getter for the  Captcha Challenge Listener. This is a class method to fetch the delegate object.
 * @return Instance of the listener object.
 */

+(id<SMPCaptchaChallengeDelegate>)getCaptchaChallengeDelegate;

/**
 * Setter For the Authentication Challenge. Clients can chose to register their custom selectors to be invoked.
 * @examples
 * <pre>
 * // register the client as delegate for this request
 * [SMPUserManager setAuthChallengeSelector:@selector(authenticationNeededForRequest:)];
 * SMPUserManager* userManager = [SMPUserManager initializeWithConnection:clientConn];
 * [userManager registerUser:@"username" password:@"password" error:&error isSyncFlag:NO];
 * ...
 * }
 * -(void)authenticationNeededForRequest:(SDMHttpRequest*)request
 * {
 *   //
 * }
 * </pre>
 */
+(void)setAuthChallengeSelector:(SEL)selector;

/**
 * Getter for Authentication Challenge Selector. This is a class method to fetch the Authentication Challenge Selector.
 * @return Custom Selector set by client as as SEL object.
 */

+(SEL)getAuthChallengeSelector;

/**
 * @internal
 * This API has been deprecated as application developer can determine with the APPlication Connection Id to know whether user is registered or not.
 */

+(BOOL)isUserRegistered __attribute__((deprecated));


@end
