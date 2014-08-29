//
//  MAFLogonOperationContext.h
//
//  Contains all the logon related information.
//
//  Copyright (c) 2012 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAFLogonDictionaryHelper.h"
#import "MAFLogonOperationContextConstants.h"

/**
 Context for operations e.g. type, id, action items.
 */
@interface MAFLogonOperationContext : MAFLogonDictionaryHelper

/**
 Identifies the context type
 */
@property (copy) NSString *contextType;

/**
 The operation which this context was created for
 */
@property (copy) NSString *operationId;

/**
 Which action should be performed for the current operation.
 Basic actions:
 - MAFLogonActionItemStart
 - MAFLogonActionItemCancel
 */
@property (copy) NSString *actionItemId;


@end
