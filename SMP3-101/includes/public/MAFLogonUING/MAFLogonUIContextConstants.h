//
//  MAFUIContextKeys.h
//
//  Copyright (c) 2012 SAP. All rights reserved.
//


#pragma mark - MAFUIContext
#pragma mark Keys

/**
 The title of the UIContext. Should be presented in the header.
 */
#define keyMAFLogonUIContextTitle @"keyMAFLogonUIContextTitle"

/**
 The key of the localizable text. Usable for custom localization.
 */
#define keyMAFLogonUIContextTitleKey @"keyMAFLogonUIContextTitleKey"

/**
 The title of the header section in the view.
 */
#define keyMAFLogonUIContextHeaderTitle @"keyMAFLogonUIContextHeaderTitle"

/**
 The switchable title of the header section in the view.
 */
#define keyMAFLogonUIContextHeaderTitleSwitchable @"keyMAFLogonUIContextHeaderTitleSwitchable"

/**
 The description text of the header section in the view.
 */
#define keyMAFLogonUIContextHeaderDescription @"keyMAFLogonUIContextHeaderDescription"

/**
 The switchable description text of the header section in the view.
 */
#define keyMAFLogonUIContextHeaderDescriptionSwitchable @"keyMAFLogonUIContextHeaderDescriptionSwitchable"

/**
 The description of the footer section in the view.
 */
#define keyMAFLogonUIContextFooterDescription @"keyMAFLogonUIContextFooterDescription"

/**
 Contains array of MAFLogonUIActionItemDescriptor
 */
#define keyMAFLogonUIContextActionItems @"keyMAFLogonUIContextActionItems"

/**
 Key-value store, contains all necessary data field for the current action in MAFLogonOperationContext
 */
#define keyMAFLogonUIContextOperationContext @"keyMAFLogonUIContextOperationContext"

/**
 Key-value store, contains all necessary data field for the current action in MAFLogonOperationContext
 */
#define keyMAFLogonUIContextChallengeContext @"keyMAFLogonUIContextChallengeContext"


/**
 Contains view related information and array of MAFLogonUIGroupDescriptor
 */
#define keyMAFLogonUIContextGroupDescriptors @"keyMAFLogonUIContextGroupDescriptors"


#pragma mark - MAFLogonUIGroupDescriptor
#pragma mark Keys

/**
 Uniquely identifies the data field in the OperationContext. The value of the "hidden state" of the group should be set in the operation context with this key. Should be YES if the group is hidden.
 */
#define keyMAFLogonUIGroupDescriptorOperationContextKeyName     @"keyMAFLogonUIGroupDescriptorOperationContextKeyName"

/**
 The group can be hidden
 */
#define keyMAFLogonUIGroupDescriptorIsHideable @"keyMAFLogonUIGroupDescriptorIsHideable"

/**
 The switch is enabled which performs the hide of the group
 */
#define keyMAFLogonUIGroupDescriptorIsHiddenByDefault @"keyMAFLogonUIGroupDescriptorIsHiddenByDefault"

/**
 Array which contains all the fields (MAFLogonUIFieldDescriptor) should be presented in the group
 */
#define keyMAFLogonUIGroupDescriptorFieldDescriptors @"keyMAFLogonUIGroupDescriptorFieldDescriptors"

/**
 Array which contains all the fields (MAFLogonUIFieldDescriptor) should be presented in the group when the default fieldDescriptor is hidden
 */
#define keyMAFLogonUIGroupDescriptorFieldDescriptorsWhenHidden @"keyMAFLogonUIGroupDescriptorFieldDescriptorsWhenHidden"

/**
 Label for the switch
 */
#define keyMAFLogonUIGroupDescriptorGroupLabel @"keyMAFLogonUIGroupDescriptorGroupLabel"

#define keyMAFLogonUIGroupDescriptorGroupLabelKey @"keyMAFLogonUIGroupDescriptorGroupLabelKey"

/**
 Label for the group header title
 */
#define keyMAFLogonUIGroupDescriptorGroupTitleLabel @"keyMAFLogonUIGroupDescriptorGroupTitleLabel"

#define keyMAFLogonUIGroupDescriptorGroupTitleLabelKey @"keyMAFLogonUIGroupDescriptorGroupTitleLabelKey"


#pragma mark - MAFLogonUIFieldDescriptor

#pragma mark Field Descriptor Values of UI Types

/**
 URL Type: string
 */
#define idMAFLogonFieldDescriptorValueUITypeURL                 @"idMAFLogonFieldDescriptorValueUITypeURL"

/**
 Port type: integer
 */
#define idMAFLogonFieldDescriptorValueUITypePort                @"idMAFLogonFieldDescriptorValueUITypePort"

/**
 Username type: string
 */
#define idMAFLogonFieldDescriptorValueUITypeUsername            @"idMAFLogonFieldDescriptorValueUITypeUsername"

/**
 Password type: string
 */
#define idMAFLogonFieldDescriptorValueUITypePassword            @"idMAFLogonFieldDescriptorValueUITypePassword"

/**
 New password type: string
 */
#define idMAFLogonFieldDescriptorValueUITypeNewPassword         @"idMAFLogonFieldDescriptorValueUITypeNewPassword"

/**
 New password confirmation type: string
 */
#define idMAFLogonFieldDescriptorValueUITypeNewPasswordAgain    @"idMAFLogonFieldDescriptorValueUITypeNewPasswordAgain"

/**
 Simple string type: editable
 */
#define idMAFLogonFieldDescriptorValueUITypeSimpleString        @"idMAFLogonFieldDescriptorValueUITypeSimpleString"

/**
 Simple string type: readonly
 */
#define idMAFLogonFieldDescriptorValueUITypeStaticString        @"idMAFLogonFieldDescriptorValueUITypeStaticString"

/**
 Bool value type
 */
#define idMAFLogonFieldDescriptorValueUITypeBOOL                @"idMAFLogonFieldDescriptorValueUITypeBOOL"


#pragma mark Keys

/**
 Uniquely identifies the data field in the OperationContext. The value specified by the user set in the operation context with this key
 */
#define keyMAFLogonUIFieldDescriptorOperationContextKeyName @"keyMAFLogonUIFieldDescriptorOperationContextKeyName"

/**
 Specifies what kind of field will be presented: url, phone number, number, password, email, BOOL (switch), button etc
 */
#define keyMAFLogonUIFieldDescriptorValueUIType @"keyMAFLogonUIFieldDescriptorValueUIType"

/**
 The label text of the field.
 */
#define keyMAFLogonUIFieldDescriptorLabel @"keyMAFLogonUIFieldDescriptorLabel"

/**
 The localization keyname fo the label. Can be used for custom localization.
 */
#define keyMAFLogonUIFieldDescriptorLabelKey @"keyMAFLogonUIFieldDescriptorLabelKey"

/**
 Hint text for the field.
 */
#define keyMAFLogonUIFieldDescriptorHintText @"keyMAFLogonUIFieldDescriptorHintText"

/**
 Marks whether a filed should be filled out to accept data
 */
#define keyMAFLogonUIFieldDescriptorIsMandatory @"keyMAFLogonUIFieldDescriptorIsMandatory"

/**
 Marks whether a field is enabled: helps to present non modifiable data
 */
#define keyMAFLogonUIFieldDescriptorEnabled @"keyMAFLogonUIFieldDescriptorEnabled"



#pragma mark - MAFLogonUIActionItemDescriptor
#pragma mark Keys

#define keyMAFLogonUIActionItemDescriptorLabel @"keyMAFLogonUIActionItemDescriptorLabel"

#define keyMAFLogonUIActionItemDescriptorLabelKey @"keyMAFLogonUIActionItemDescriptorLabelKey"

#define keyMAFLogonUIActionItemDescriptorActionItemId @"keyMAFLogonUIActionItemDescriptorActionItemId"

#define keyMAFLogonUIActionItemDescriptorActionItemIsLongOperation @"keyMAFLogonUIActionItemDescriptorActionItemIsLongOperation"

#define keyMAFLogonUIActionItemDescriptorExecutesOperation @"keyMAFLogonUIActionItemDescriptorExecutesOperation"

#define keyMAFLogonUIConfirmationDescriptor @"keyMAFLogonUIConfirmationDescriptor"
#define keyMAFLogonUIConfirmationMessage @"keyMAFLogonUIConfirmationMessage"
#define keyMAFLogonUIConfirmationMessageKey @"keyMAFLogonUIConfirmationMessageKey"
#define keyMAFLogonUIConfirmationTitle @"keyMAFLogonUIConfirmationTitle"
#define keyMAFLogonUIConfirmationTitleKey @"keyMAFLogonUIConfirmationTitleKey"
#define keyMAFLogonUIConfirmationCancelButtonLabel @"keyMAFLogonUIConfirmationCancelButtonLabel"
#define keyMAFLogonUIConfirmationCancelButtonLabelKey @"keyMAFLogonUIConfirmationCancelButtonLabelKey"
#define keyMAFLogonUIConfirmationOKButtonLabel @"keyMAFLogonUIConfirmationOKButtonLabel"
#define keyMAFLogonUIConfirmationOKButtonLabelKey @"keyMAFLogonUIConfirmationOKButtonLabelKey"

#define keyMAFLogonUIConfirmationEnterSSOAlertViewTitle @"keyMAFLogonUIConfirmationEnterSSOAlertViewTitle"
#define keyMAFLogonUIConfirmationEnterSSOAlertViewMessage @"keyMAFLogonUIConfirmationEnterSSOAlertViewMessage"
#define keyMAFLogonUIConfirmationEnterSSORelaunchSkipAlertViewMessage @"keyMAFLogonUIConfirmationEnterSSORelaunchSkipAlertViewMessage"
