//
//  MAFLogonNGDelegate.h
//  MAFLogonUING
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Protocol to describe the operation method callbacks
 */
@protocol MAFLogonNGDelegate <NSObject>

/**
 Called when the logon finished either with success or error.
 @param anError If nil the operation was successful otherwise contains the error occured
 */
-(void) logonFinishedWithError:(NSError*)anError;

/**
 Called when the lockSecureStore method call finished either with success or error.
 @param anError If nil the operation was successful otherwise contains the error occured
 */
-(void) lockSecureStoreFinishedWithError:(NSError*)anError;

/**
 Called when the updateApplicationSettings method call finished either with success or error.
 @param anError If nil the operation was successful otherwise contains the error occured
 */
-(void) updateApplicationSettingsFinishedWithError:(NSError*)anError;

/**
 Called when the changeBackendPassword method call finished either with success or error.
 @param anError If nil the operation was successful otherwise contains the error occured
 */
-(void) changeBackendPasswordFinishedWithError:(NSError*)anError;

/**
 Called when the deleteUser method call finished either with success or error.
 @param anError If nil the operation was successful otherwise contains the error occured
 */
-(void) deleteUserFinishedWithError:(NSError*)anError;

/**
 Called when the changeSecureStorePassword method call finished either with success or error.
 @param anError If nil the operation was successful otherwise contains the error occured
 */
-(void) changeSecureStorePasswordFinishedWithError:(NSError*)anError;

/**
 Called when the registrationInfo method call finished either with success or error.
 @param anError If nil the operation was successful otherwise contains the error occured
 */
-(void) registrationInfoFinishedWithError:(NSError*)anError;

/**
 Called when the uploadTrace method call finished either with success or error.
 @param anError If nil the operation was successful otherwise contains the error occured
 */
-(void) uploadTraceFinishedWithError:(NSError*)anError;

/**
 Called when 'Try Out' (demo mode) button has been clicked on splash screen.
 */
-(void) startDemoMode;

@end
