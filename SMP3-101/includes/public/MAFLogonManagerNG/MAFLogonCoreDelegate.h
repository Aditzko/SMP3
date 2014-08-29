//
//  MAFLogonCoreDelegate.h
//  MAFLogonCore
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Describes the methods the MAFLogonCore can call related to logon processes.
 */
@protocol MAFLogonCoreDelegate <NSObject>

/**
 Callback method if the registration finished
 @param anError The returning error code if the method fails. Caller should pass the address of an NSError* variable.
 */
-(void) registerFinished:(NSError*)anError;

/**
 Callback method if the unregister finished
 @param anError The returning error code if the method fails. Caller should pass the address of an NSError* variable.
 */
-(void) unregisterFinished:(NSError*)anError;

/**
 Callback method if the cancel registration finished
 @param anError The returning error code if the method fails. Caller should pass the address of an NSError* variable.
 */
-(void) cancelRegistrationFinished:(NSError*)anError;

/**
 Callback method if the refresh application settings finished
 @param anError The returning error code if the method fails. Caller should pass the address of an NSError* variable.
 */
-(void) refreshApplicationSettingsFinished:(NSError*)anError;

/**
 Callback method if the change password finished
 @param anError The returning error code if the method fails. Caller should pass the address of an NSError* variable.
 */
-(void) changePasswordFinished:(NSError*)anError;

/**
 Callback method if the upload trace finished
 @param anError The returning error code if the method fails. Caller should pass the address of an NSError* variable.
 */
-(void) uploadTraceFinished:(NSError*)anError;

@end
