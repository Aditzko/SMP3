/*
Copyright (c) Sybase, Inc. 2011 All rights reserved. 

In addition to the license terms set out in the Sybase License Agreement for 
the Sybase Unwired Platform ("Program"), the following additional or different 
rights and accompanying obligations and restrictions shall apply to the source 
code in this file ("Code"). Sybase grants you a limited, non-exclusive, 
non-transferable, revocable license to use, reproduce, and modify the Code 
solely for purposes of (i) maintaining the Code as reference material to better 
understand the operation of the Program, and (ii) development and testing of 
applications created in connection with your licensed use of the Program. 
The Code may not be transferred, sold, assigned, sublicensed or otherwise 
conveyed (whether by operation of law or otherwise) to another party without 
Sybase's prior written consent. The following provisions shall apply to any 
modifications you make to the Code: (i) Sybase will not provide any maintenance 
or support for modified Code or problems that result from use of modified Code; 
(ii) Sybase expressly disclaims any warranties and conditions, express or 
implied, relating to modified Code or any problems that result from use of the 
modified Code; (iii) SYBASE SHALL NOT BE LIABLE FOR ANY LOSS OR DAMAGE RELATING 
TO MODIFICATIONS MADE TO THE CODE OR FOR ANY DAMAGES RESULTING FROM USE OF THE 
MODIFIED CODE, INCLUDING, WITHOUT LIMITATION, ANY INACCURACY OF DATA, LOSS OF 
PROFITS OR DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES, EVEN 
IF SYBASE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; (iv) you agree 
to indemnify, hold harmless, and defend Sybase from and against any claims or 
lawsuits, including attorney's fees, that arise from or are related to the 
modified Code or from use of the modified Code.
*/

//
//  DataVault.h
//
//  Class to store given data in a secure manner
//  An application can choose to store multiple items of data withing the vault
//  Each data can be accessed by a name (like storing DB encryption Key and X.509 certificate etc.)
//  The vault is accessed by unique vaultId
//  DataVault is unlocked by a Password

#ifndef __DATAVAULT_H__
#define __DATAVAULT_H__

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

// ID of the standard messaging data vault
// Messaging vault must be unlocked before calling startEngine which will use the key from this vault to decrypt the messaging queue database
extern NSString * const kMessagingDataVaultID;

// Standard password and salt used in "No" security mode
extern NSString * const kDVStandardPassword;
extern NSString * const kDVStandardSalt;

// Use this constant for 'retryLimit' if unlimited failure attempts can be allowed during unlock
#define kDVUnlimitedRetriesAllowed   0

// Use this constant for 'lockTimeout' if application requires user to enter PIN everytime the app is launched
#define kDVNoLockTimeout             0

// Default values for password policy attributes
#define kPwdPolicyDefValueDefPwdAllowed   1
#define kPwdPolicyDefValueMinLength       8
#define kPwdPolicyDefValueHasDigits       0
#define kPwdPolicyDefValueHasUpper        0
#define kPwdPolicyDefValueHasLower        0
#define kPwdPolicyDefValueHasSpecial      0
#define kPwdPolicyDefValueExpirationDays  0
#define kPwdPolicyDefValueMinUniqueChars  0
#define kPwdPolicyDefValueLockTimeout     kDVNoLockTimeout
#define kPwdPolicyDefValueRetryLimit      kDVUnlimitedRetriesAllowed

// Name of the exception thrown for DataVault errors
extern NSString * const DataVaultExceptionName;

// Error codes for Datavault exception thrown
#define kDataVaultExceptionErrorCodeUnknown           0           // doesn't occur in iOS; included for consistency with other platforms
#define kDataVaultExceptionErrorCodeAlreadyExists     1
#define kDataVaultExceptionErrorCodeConversionError   2           // doesn't occur in iOS; included for consistency with other platforms
#define kDataVaultExceptionErrorCodeDoesNotExist      3
#define kDataVaultExceptionErrorCodeInvalidArg        4
#define kDataVaultExceptionErrorCodeInvalidPassword   5
#define kDataVaultExceptionErrorCodeIOReadError       6           
#define kDataVaultExceptionErrorCodeIOWriteError      7           
#define kDataVaultExceptionErrorCodeLocked            8
#define kDataVaultExceptionErrorCodeNameTooLong       9           // doesn't occur in iOS; included for consistency with other platforms
#define kDataVaultExceptionErrorCodeValueTooLarge     10          // doesn't occur in iOS; included for consistency with other platforms
#define kDataVaultExceptionErrorCodeDataTypeErrror    12
#define kDataVaultExceptionErrorCodeOutOfMemory       13

// Error codes for password policy violations
#define kDataVaultExceptionErrorCodePasswordRequired        50
#define kDataVaultExceptionErrorCodePasswordUnderMinLength  51
#define kDataVaultExceptionErrorCodePasswordRequiresDigit   52
#define kDataVaultExceptionErrorCodePasswordRequiresUpper   53
#define kDataVaultExceptionErrorCodePasswordRequiresLower   54
#define kDataVaultExceptionErrorCodePasswordRequiresSpecial 55
#define kDataVaultExceptionErrorCodePasswordUnderMinUnique  56
#define kDataVaultExceptionErrorCodePasswordExpired         57

// Reasons/Error messages for exception thrown
extern NSString * const kDataVaultExceptionReasonAlreadyExists;
extern NSString * const kDataVaultExceptionReasonDoesNotExist;
extern NSString * const kDataVaultExceptionReasonInvalidArg;
extern NSString * const kDataVaultExceptionReasonInvalidPassword;
extern NSString * const kDataVaultExceptionReasonLocked;
extern NSString * const kDataVaultExceptionReasonDataTypeError;
extern NSString * const kDataVaultExceptionReasonOutOfMemory;

// Reasons/Error messages for password policy violations
extern NSString * const kDataVaultExceptionReasonPasswordRequired;
extern NSString * const kDataVaultExceptionReasonPasswordUnderMinLength;
extern NSString * const kDataVaultExceptionReasonPasswordRequiresDigit;
extern NSString * const kDataVaultExceptionReasonPasswordRequiresUpper;
extern NSString * const kDataVaultExceptionReasonPasswordRequiresLower;
extern NSString * const kDataVaultExceptionReasonPasswordRequiresSpecial;
extern NSString * const kDataVaultExceptionReasonPasswordUnderMinUniqueChars;
extern NSString * const kDataVaultExceptionReasonIORead;
extern NSString * const kDataVaultExceptionReasonIOWrite;
extern NSString * const kDataVaultExceptionReasonPasswordExpired;

typedef enum {
   kDVDataTypeUnknown,
   kDVDataTypeString,
   kDVDataTypeBinary
} DVDataType;


@interface DVPasswordPolicy : NSObject {
   BOOL defaultPasswordAllowed;
   NSInteger minLength;               
   BOOL hasDigits;
   BOOL hasUpper;
   BOOL hasLower;
   BOOL hasSpecial;
   NSInteger expirationDays;               
   NSInteger minUniqueChars;               
   NSInteger lockTimeout;               
   NSInteger retryLimit;               
}

@property (nonatomic, assign, readwrite) BOOL defaultPasswordAllowed;
@property (nonatomic, assign, readwrite) NSInteger minLength;
@property (nonatomic, assign, readwrite) BOOL hasDigits;
@property (nonatomic, assign, readwrite) BOOL hasUpper;
@property (nonatomic, assign, readwrite) BOOL hasLower;
@property (nonatomic, assign, readwrite) BOOL hasSpecial;
@property (nonatomic, assign, readwrite) NSInteger expirationDays;
@property (nonatomic, assign, readwrite) NSInteger minUniqueChars;
@property (nonatomic, assign, readwrite) NSInteger lockTimeout;
@property (nonatomic, assign, readwrite) NSInteger retryLimit;

@end


@interface DVDataName : NSObject {
   NSString * name;
   DVDataType type;
}

@property (nonatomic, retain) NSString * name;
@property (nonatomic, assign, readwrite) DVDataType type;

@end


@interface DataVault : NSObject {
   NSString * vaultId;
   NSData * passwordHash;               
   NSData * standardPasswordHash;       

   BOOL lockTimeoutFeatureEnabled;
}

//
// Public instance methods supported by this class
//

// Class method specific for iPhone implementation
// This method must be called before accessing any DataVault methods
// Access group must be set only if DataVault must be shared by more than one application
// If the DataVault is used only by one application access group should not be set
// This access group in keychain-access-groups property of entitlements plist file is usually in format "<BundleSeedID>.com.yourcompany.DataVault"
+ (void)setAccessGroup:(NSString *)accessGroup;

// Creates a new vault and returns it with unlocked state
// If a vault already exists with same name this will throw exception with kDataVaultExceptionReasonAlreadyExists as reason
+ (DataVault*)createVault:(NSString *)dataVaultID password:(NSString *)aPassword salt:(NSString *)aSalt;

// Returns vault with given ID. This vault is in locked state
// Throws an exception if a vault does not exist with given ID (kDataVaultExceptionReasonDoesNotExist)
// Throws exception (with reason kDataVaultExceptionReasonIORead) if error happens when reading keychain item
+ (DataVault*)getVault:(NSString *)dataVaultID;

// Returns YES if a vault with given ID exists
+ (BOOL)vaultExists:(NSString *)dataVaultID;

// Returns YES if a vault with given ID exists.
// Throws exception (with reason kDataVaultExceptionReasonIORead) if error happens when reading keychain item
+ (BOOL)vaultExists2:(NSString *)dataVaultID;

// Deletes vault with given ID
// Throws an exception if a vault does not exist with given ID (kDataVaultExceptionReasonDoesNotExist)
+ (void)deleteVault:(NSString *)dataVaultID;

// Unlocks the vault with given password
// Should be called before accessing the data stored in the vault
// Throws exception with kDataVaultExceptionReasonInvalidPassword as reason if password given is incorrect
- (void)unlock:(NSString *)curPassword salt:(NSString *)curSalt;

// Locks the vault
// If the vault is already locked calling this method has no effect
- (void)lock;

// Indicates if the vault is currently locked
// Returns YES if vault is locked and NO if vault is unlocked
- (BOOL)isLocked;

// Return YES if default password is used
- (BOOL)isDefaultPasswordUsed;

// Changes the password of vault
// The vault must be unlocked before changing the password
// If newSalt is nil then a salt will be generated
// If newPassword is nil then a default password will be generated if password policy allows it
// Throws exception (with reason kDataVaultExceptionReasonPassword...) if newPassword is not compatible with password policy (if it is set) 
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
- (void)changePassword:(NSString *)newPassword salt:(NSString *)newSalt;

// Overloaded version of changePassword
// When the data vault is locked use this version to unlock and change the password
// Throws exception with kDataVaultExceptionReasonInvalidPassword as reason if current password is incorrect
- (void)changePassword:(NSString *)curPassword currentSalt:(NSString *)curSalt newPassword:(NSString *)newPassword newSalt:(NSString *)newSalt;

// Get the data value for given name
// Throws exception (with reason kDataVaultExceptionReasonInvalidArg) if data with given name does not exist in the vault
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
// Throws exception (with reason kDataVaultExceptionReasonIORead) if keychain item is not accessible
- (NSData *)getValue:(NSString *)name;

// Set the data value for given name
// Throws exception (with reason kDataVaultExceptionReasonInvalidArg) if data with given name does not exist in the vault
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
- (void)setValue:(NSString *)name value:(NSData *)data;

// Get the string form of data value for given name
// Throws exception (with reason kDataVaultExceptionReasonInvalidArg) if data with given name does not exist in the vault
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
// Throws exception (with reason kDataVaultExceptionReasonConversionError) if unable to convert the data to string
// Throws exception (with reason kDataVaultExceptionReasonIORead) if keychain item is not accessible
- (NSString *)getString:(NSString *)name;

// Set the string form of data value for given name
// Throws exception (with reason kDataVaultExceptionReasonInvalidArg) if data with given name does not exist in the vault
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
// Throws exception (with reason kDataVaultExceptionReasonConversionError) if unable to convert the data from string
- (void)setString:(NSString *)name value:(NSString *)strData;

// Deletes the value from the vault
// Throws exception (with reason kDataVaultExceptionReasonInvalidArg) if data with given name is nil or empty
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
- (void)deleteValue:(NSString *)name;

// Fetches the name of all the data stored in the vault
// Returns array of DVDataName objects
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
// Throws exception (with reason kDataVaultExceptionReasonIORead) if keychain item is not accessible
- (NSArray *)getDataNames;

// Fetches the password policy if it is already set
// If password policy is not set, returns DVPasswordPolicy object with default values in each of its attribute
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
- (DVPasswordPolicy *)getPasswordPolicy;

// Allows the application to set a password policy
// If nil is passed as pwdPolicy, then default values for each attribute is use
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
- (void)setPasswordPolicy:(DVPasswordPolicy *)pwdPolicy;

// Resets the lock timeout effectively extending the timeout period from now
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
- (void)resetLockTimeout;

// Get the lock timeout value
// kDVNoLockTimeout is returned if no lock timeout is specified
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
// Note: This API will be deprecated. Instead use lockTimeout member in DVPasswordPolicy object
- (NSInteger)getLockTimeout DEPRECATED_ATTRIBUTE;

// Set the lock timeout value
// kDVNoLockTimeout can be passed to remove any existing lock timeout
// Throws exception (with reason kDataVaultExceptionReasonInvalidArg) if invalid timeout (like negative) value is passed
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
// Note: This API will be deprecated. Instead use lockTimeout member in DVPasswordPolicy object
- (void)setLockTimeout:(NSInteger)timeout DEPRECATED_ATTRIBUTE;

// Get retry limit value
// kDVUnlimitedRetriesAllowed indicates unlimited retries are allowed
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
// Note: This API is deprecated. Instead use retryLimit member in DVPasswordPolicy object
- (NSInteger)getRetryLimit DEPRECATED_ATTRIBUTE;

// Set the retry limit value
// kDVUnlimitedRetriesAllowed can be passed to remove any existing retry limits
// Throws exception (with reason kDataVaultExceptionReasonInvalidArg) if invalid retry limit (like negative) value is passed
// Throws exception (with reason kDataVaultExceptionReasonLocked) if vault is locked
// Note: This API is deprecated. Instead use retryLimit member in DVPasswordPolicy object
- (void)setRetryLimit:(NSInteger)retryLimitValue DEPRECATED_ATTRIBUTE;

@end


@interface DataVaultException : NSException {

}

// If errorCode, errorMessage and nativeErrorCode are provided when throwing DataVaultException, they are stored in
// [NSException userInfo] NSDictionary. Using the following key to retrieve their value from the dictionary:
// key for errorCode:         "ErrorCode"
// key for errorMessage:      "ErrorMessage"
// key for nativeErrorCode:   "NativeErrorCode"
- (id)initWithReason: (NSString *)reason;
- (id)initWithErrorAndMessage: (int)errorCode message:(NSString *)errorMessage;
- (id)initWithErrorAndMessage: (int)errorCode message:(NSString *)errorMessage nativeError:(int)nativeErrorCode;
@end

#endif // __DATAVAULT_H__
