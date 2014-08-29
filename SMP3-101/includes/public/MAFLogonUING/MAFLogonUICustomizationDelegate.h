//
//  MAFLogonUICustomizationDelegate.h
//  MAFLogonUING
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAFLogonUIContext.h"
#import "MAFLogonUICustomizationContext.h"
#import "MAFUIView.h"


@protocol MAFLogonUICustomizationDelegate <NSObject>

@optional

/**
 This delegate will be called before a new screen is shown. You can change the context here
*/
- (void) willRenderUIFromUIContext:(MAFLogonUIContext*)aUIContext;

/**
 This delegate will be called before a new screen is shown. You can change the header and the footer view here.
 */
- (void) willRenderHeaderFooterFromCustomContext:(MAFLogonUICustomizationContext*)aCustomContext;


@end
