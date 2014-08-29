//
//  MAFLogonManagerState.h
//  MAFLogonManagerNG
//
//  Copyright (c) 2012 SAP AG. All rights reserved.
//

#import "MAFAfariaConstants.h"

/**
 Describes the state of the logon manager.
 */
typedef union {
    struct {
        BOOL isUserRegistered : 1;
        BOOL hasSecureStore : 1;
        BOOL isSecureStoreOpen : 1;
        BOOL isExecutionInProgress : 1;
        BOOL isSplashUsed : 1;
        AfariaSecureStoreCreationPolicy afariaSecureStoreCreationPolicy : 3;
        AfariaState afariaState : 2;
        AfariaRegistrationType afariaRegistrationType : 2;
    };
    uint32_t rawValue;
} MAFLogonManagerNGState;
