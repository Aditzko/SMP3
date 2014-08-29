//
//  MAFLogonUIContext.h
//
//  Copyright (c) 2012 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MAFLogonDictionaryHelper.h"
#import "MAFLogonUIContextConstants.h"
#import "MAFLogonRegistrationOperationContext.h"
#import "MAFLogonViewScreenType.h"
#import <UIKit/UIKit.h>

/**
 Contains all the information which is necessary to present a UI and get information from the user for the required operation.
 Using this object the MAFLogonManagerNG can transition from one state to other.
 The object contains at least the following fields:
 */
@interface MAFLogonUIContext : MAFLogonDictionaryHelper

/**
 The title of the view. Should be presented in a header.
 */
@property (copy) NSString* title;

/**
 The title of the header section in the view.
 */
@property (copy) NSString* headerTitle;

/**
 The switchable title of the header section in the view.
 */
@property (copy) NSString* headerTitleSwitchable;

/**
 The description of the header section in the view
 */
@property (copy) NSString* headerDescription;

/**
 The switchable description of the header section in the view
 */
@property (copy) NSString* headerDescriptionSwitchable;

/**
 The description of the footer section of the view.
 */
@property (copy) NSString* footerDescription;

/**
 Contains array of MAFLogonUIActionItemDescriptor
 */
@property (retain) MAFLogonMutableArrayHelper *actionItems;

/**
 Contains view related information and array of MAFLogonUIGroupDescriptor
 */
@property (retain) MAFLogonMutableArrayHelper *groupDescriptors;

/**
 Key-value store, contains all necessary data field for the current action in MAFLogonOperationContext
 */
@property (retain) MAFLogonOperationContext *operationContext;

@property (assign) MAFLogonViewScreenType screenType;

@end
