//
//  MAFLogonCoreState.h
//  MAFLogonCore
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

//#import <Foundation/Foundation.h>

#import "MAFAfariaConstants.h"

/**
 Represents the current state of the MCIM/ClientHub
 */
typedef enum MCIMState{
    MCIMNotAvailable                = 1, /**< MCIM application is not available */
    MCIMSkipped                     = 2, /**< MCIM application is available, but user skipped it, the logon won't use it */
    MCIMAvailableNoSSOPin           = 3, /**< MCIM application is available, but SSO Pin is not set in the logon */
    MCIMAvailableInvalidSSOPin      = 4, /**< MCIM application is available, but SSO Pin set in the logon is invalid */
    MCIMAvailableValidSSOPin        = 5  /**< MCIM application is available, SSO Pin set in the logon is valid */
} MCIMState;

/**
 Contains the current state flags depending of the current state of the logon
 */
@interface MAFLogonCoreState : NSObject

/**
 The application identifier which the logon was created with
 */
@property (nonatomic, copy) NSString*       applicationId;

/**
 Shows whether the logon is registered on a server
 */
@property (nonatomic, assign) BOOL          isRegistered;

/**
 Shows whether the logon has a secure store. True only if logon is registered too.
 */
@property (nonatomic, assign) BOOL          hasSecureStore;

/**
 Shows whether the secure store is open. Can be true only if hasSecureStore is true.
 */
@property (nonatomic, assign) BOOL          isSecureStoreOpen;

/**
 Shows the logon should be updated. For this the logon needs a passcode for the existing secure store.
 Unlock method should be called!
 */
@property (nonatomic, assign) BOOL          shouldMigrate;

/**
 Shows the state of the Afaria
 */
@property (nonatomic, assign) AfariaState   afariaState;

/**
 Shows if an execution is in progress.
 */
@property (nonatomic, assign) BOOL          isExecutionInProgress;

/**
 Shows if default passcode used for secure store manager.
 */
@property (nonatomic, assign) BOOL          isDefaultPasscodeUsed;

/**
 Shows if default passcode usage is enabled for secure store manager.
 */
@property (nonatomic, assign) BOOL          isDefaultPasscodeAllowed;

/**
 Shows the state of the MCIM
 */
@property (nonatomic, assign) MCIMState     mcimState;

@end
