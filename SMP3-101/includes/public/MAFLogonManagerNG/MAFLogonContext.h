//
//  MAFLogonContext.h
//  MAFLogonCore
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAFAfariaConstants.h"

@class MAFLogonRegistrationContext;
@class MAFSecureStorePasswordPolicy;

/**
 Generic context for multiple purposes. 
 Used as input and output on different methods.
 */
@interface MAFLogonContext : NSObject<NSCopying>

/**
 Contains registration related parameters.
 */
@property (nonatomic, copy) MAFLogonRegistrationContext*  registrationContext;

/**
 Contains the password policy for the secure store
 */
@property (nonatomic, copy) MAFSecureStorePasswordPolicy* passwordPolicy;

/**
 Marks whether the password policy was downloaded from the server
 */
@property (assign) BOOL isPasswordPolicyFromServer;

/**
 Contains the registration type specified using afaria
 */
@property (assign) AfariaRegistrationType afariaRegistrationType;

/**
 Contains the secure store policy specified using afaria
 */
@property (assign) AfariaSecureStoreCreationPolicy afariaSecureStorePolicy;

@property (assign) BOOL hasConfigurationDataFromMCIM;

@property (assign) BOOL hasCredentialsFromMCIM;

@end
