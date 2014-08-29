//
//  MAFSecureStorePasswordPolicy.
//
//  Copyright (c) 2012 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Describes the password policy.
 */
@interface MAFSecureStorePasswordPolicy:NSObject<NSCopying>

/**
 The password should contain digits.
 */
@property BOOL hasDigits;

/**
 The password should contain lower case letters.
 */
@property BOOL hasLowerCaseLetters;

/**
 The password should contain special letters.
 */
@property BOOL hasSpecialLetters;

/**
 The password should contain upper case letters.
 */
@property BOOL hasUpperCaseLetters;

/**
 The default password is allowed.
 */
@property BOOL isDefaultPasswordAllowed;

/**
 The password policy is in use.
 */
@property BOOL isEnabled;

/**
 The number of days after the password will expires.
 */
@property int expirationDays;

/**
 The password policy will be locked after the this number of seconds.
 */
@property int lockTimeout;

/**
 The password length minimum.
 */
@property int minLength;

/**
 The password should contain minimum these number of unique characters.
 */
@property int minUniqueChars;

/**
 The number of trying giving password.
 */
@property int retryLimit;

@end

