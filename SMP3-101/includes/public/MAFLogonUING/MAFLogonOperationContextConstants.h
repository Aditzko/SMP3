//
//  MAFLogonOperationKeys.h
//
//  Contains key and value definitions for the operations used in LogonManager
//
//  Copyright (c) SAP AG. All rights reserved.
//

#pragma mark - Operation context keys

#pragma mark General keys

/**
 The operation code. Mandatory field for every operation.
 */
#define keyMAFLogonOperationContextOperationId          @"keyMAFLogonOperationContextOperationId"

/**
 Identifies the specific type of context. Mandatory field for very operation.
 Querying a UIContext declares which context type is necessary to execute the operation based on the operationid and the state of the LogonManager
 */
#define keyMAFLogonOperationContextType                 @"keyMAFLogonOperationContextType"

/**
 Which action should be performed for the current operation. Mandatory field for every operation.
 Two main action:
 - MAFLogonActionItemStart
 - MAFLogonActionItemCancel
 */
#define keyMAFLogonOperationContextActionItemId         @"keyMAFLogonOperationContextActionItemId"


#pragma mark - Operations Ids

/**
 Value for Logon Operation key
 **/
#define idMAFLogonOperationIdLogon                      @"idMAFLogonOperationIdLogon"

/**
 Value for Delete Operation key
 **/
#define idMAFLogonOperationIdDeleteUser                 @"idMAFLogonOperationIdDeleteUser"

/**
 Value for LockSecureStore Operation key
 **/
#define idMAFLogonOperationIdLockSecureStore            @"idMAFLogonOperationIdLockSecureStore"

/**
 Value for ChangeSecureStorePassword Operation key
 **/
#define idMAFLogonOperationIdChangeSecureStorePassword  @"idMAFLogonOperationIdChangeSecureStorePassword"

/**
 Value for ChangeBackendPassword Operation key
 **/
#define idMAFLogonOperationIdChangeBackendPassword      @"idMAFLogonOperationIdChangeBackendPassword"

/**
 Value for Update Application settings Operation key
 **/
#define idMAFLogonOperationIdUpdateApplicationSettings  @"idMAFLogonOperationIdUpdateApplicationSettings"

/**
 Value for Registration Info Operation key
 */
#define idMAFLogonOperationIdRegistrationInfo           @"idMAFLogonOperationIdRegistrationInfo"

/**
 Value for Upload Trace key
 */
#define idMAFLogonOperationIdUploadTrace           @"idMAFLogonOperationIdUploadTrace"


#pragma mark Operation Context Types

#define idMAFLogonOperationContextTypeSplash                    @"idMAFLogonOperationContextTypeSplash"
#define idMAFLogonOperationContextTypeRegister                  @"idMAFLogonOperationContextTypeRegister"
#define idMAFLogonOperationContextTypeRegistrationInfo          @"idMAFLogonOperationContextTypeRegistrationInfo"
#define idMAFLogonOperationContextTypeUploadTrace               @"idMAFLogonOperationContextTypeUploadTrace"
#define idMAFLogonOperationContextTypeCreateSecureStore         @"idMAFLogonOperationContextTypeCreateSecureStore"
#define idMAFLogonOperationContextTypeUnlockSecureStore         @"idMAFLogonOperationContextTypeUnlockSecureStore"
#define idMAFLogonOperationContextTypeChangeSecureStorePassword @"idMAFLogonOperationContextTypeChangeSecureStorePassword"
#define idMAFLogonOperationContextTypeLockSecureStore           @"idMAFLogonOperationContextTypeLockSecureStore"
#define idMAFLogonOperationContextTypeDeleteUser                @"idMAFLogonOperationContextTypeDeleteUser"
#define idMAFLogonOperationContextTypeChangeBackendPassword     @"idMAFLogonOperationContextTypeChangeBackendPassword"
#define idMAFLogonOperationContextTypeUpdateApplicationSettings @"idMAFLogonOperationContextTypeUpdateApplicationSettings"
#define idMAFLogonOperationContextTypeSSOPasscode               @"idMAFLogonOperationContextTypeSSOPasscode"
#define idMAFLogonOperationContextTypeEnterCredentials          @"idMAFLogonOperationContextTypeEnterCredentials"

#pragma mark Action Item Ids

/**
 Identifies an action realted to the operation and action type
 */
#define idMAFLogonActionItemStart     @"idMAFLogonActionItemStart"

#define idMAFLogonActionItemCancel    @"idMAFLogonActionItemCancel"


/**
 Identifies the different default value dictionaries in the plist file
*/
#define keyMAFLogonOperationContextDefaultValues                    @"keyMAFLogonOperationContextDefaultValues"
#define keyMAFLogonOperationContextDefaultValuesForEmptyFields      @"keyMAFLogonOperationContextDefaultValuesForEmptyFields"
#define keyMAFLogonOperationContextHideRegistrationFields  @"keyMAFLogonOperationContextHideRegistrationFields"




