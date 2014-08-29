//
//  ClientHub.h
//  ClientHubSLL
//
//  Created by Phaneesh L N on 5/21/13.
//  Copyright (c) 2013 Phaneesh L N. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ConnectionSettings.h"
#import "UserCredentials.h"

/**
 * Consists of methods used to get share credentials and fetch the connection settings.
 */

@interface ClientHub : NSObject{
    /** @internal */
    NSString* applicationID;
    /** @internal */
    NSString* password;
    /** @internal */
    BOOL isValid;
    /** @internal */
    BOOL isSharable;
    /** @internal */
    NSString * secConfig;
}

/**
 * Initializes the ClientHub class.
 * @param newApplicationID Name of the application.
 * @examples
 * <pre>
 *  [ClientHub initInstance:@"com.sap.NewFlight"];
 * </pre>
 */

+(void) initInstance:(NSString*) newapplicationID;

/**
 * Checks whether the ClientHub application is installed and SSO passcode is set.
 * @param None.
 * @return Returns BOOL true only when ClientHub app is installed and SSO passcode is set, false otherwise. 
 * @examples
 * <pre>
 *  if([cis isAvailable]){
 *   showAlertView(@"ClientHub is Available");
 *  }else{
 *  showAlertView(@"ClientHub is not Available");
 *  }
 * </pre>
 */

-(BOOL) isAvailable;

/**
 * Retrives the instance of the ClientHub object.
 * @param None.
 * @return Returns the instance of the class ClientHub.
 * @examples
 * <pre>
 *  ClientHub * cis = [ClientHub getInstance];
 * </pre>
 */

+(id) getInstance;

/**
 * Validates the ClientHub Application pincode. 
 * @param newpincode The pincode to access the credentials.
 * @return Returns true if pincode is valid or false otherwise.
 * @examples
 * <pre>
 *  BOOL isValid = false;
 *  isValid = [cis validatePincode:_pwd.text];
 *  if(isValid){
 *  testOutput.text = @"passcode is valid";
 *  }else{
 *  testOutput.text = @"passcode is invalid";
 *  }
 * </pre>
 */

-(BOOL) validateSSOPasscode:(NSString*) newpasscode;

/**
 * Updates the security configuration of the application. 
 * @param newsecConfig Security configuration name of the application.
 * @param error Error object that will be filled if any error occured.
 * @return Returns false if an error occured or true otherwise, if error occured error object will be populated. 
 * @examples
 * <pre>
 *  NSError *error = nil;
 *  BOOL noError = true;
 *  noError = [cis updateSecurityConfig:@"SSO" withError:&error];
 * </pre>
 */

-(BOOL) updateSecurityConfig:(NSString*) newsecConfig withError:(NSError**) error;

/**
 * Retrieves the connection settings as an object of ConnectionSettings class.
 * @param error Error object that will be filled if any error occured.
 * @return Returns ConnectionSettings object if no error occured or nil otherwise.
 * @examples
 * <pre>
 *  NSError *error = nil;
 *  ConnectionSettings * consettngs = [cis getConnectionSettings:&error];
 *  NSLog(@"%@",[consettngs host]);
 * </pre>
 */

-(ConnectionSettings*) getConnectionSettings:(NSError**) error;

/**
 * Retrieves the user credentials.
 * @param error Error object that will be filled if any error occured.
 * @return Returns Credentials object if no error occured or nil otherwise.
 * @examples
 * <pre>
 *  NSError *error = nil;
 *  Credentials * retcred = [cis getCredentials:&error];
 *  NSLog(@"%@",[retcred username]);
 * </pre>
 */

-(UserCredentials*)getCredentials:(NSError**) error;

/**
 * Sets the user credentials for credential sharing between applications. 
 * @param newcredentials Object of Credentials class.
 * @param error Error object that will be filled if any error occured.
 * @return Returns false if an error occured or true otherwise. If error occured, the error object will be populated. 
 * @examples
 * <pre>
 *  NSError *error = nil;
 *  BOOL noError = true;
 *  Credentials * cred = [[Credentials alloc] init];
 *  [cred setUsername:@"supuser2"];
 *  [cred setPassword:@"s3puser"];
 *  [cred setSSOToken:@"dummytoken"];
 *  [cred setCertificate:@"dummycert"];
 *  [cred setCredentialType:@"SSO"];
 *  noError = [cis setCredentials:cred withError:&error];
 * </pre>
 */

-(BOOL) setCredentials:(UserCredentials*) newcredentials withError:(NSError**) error;

/**
 * Retrieves the user creation policy.
 * @param error Error object that will be filled if any error occured.
 * @return Returns NSString object if no error occured or nil otherwise.
 * @examples
 * <pre>
 *  NSError *error = nil;
 *  NSString *policy = [cis getUserCreationPolicy:&error];
 *  NSLog(@"%@",policy);
 * </pre>
 */

-(NSString*)getUserCreationPolicy:(NSError**) error;

//+(id)sharedInstance:(NSString *) newAppID;

@end
