//
//  UIAlertView+Additions.h
//  MAFLogonUniversalSample_CR
//
//  Created by  on 7/17/12.
//  Copyright (c) 2012 SAP. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void (^AlertViewResultBlockType)(int buttonIndex);

/**
 Helper categrory to ease the usage of UIAlertView.
 */
@interface UIAlertView (MAFUIHelper)

/**
 Creates a new instance of a UIAlertView and shows it. The UIAlertViewDelegate is implemented inside the category and the resultBlock parameter is called back with the pressed button index.
 @param title: The string that appears in the receiver’s title bar
 @param message: Descriptive text that provides more details than the title
 @param block: the result block which will be called when the user presses one of the buttons
 @param cancelButtonTitle: The title of the cancel button or nil if there is no cancel button
 @param otherButtonTitles: Titles of additional buttons to add to the receiver, terminated with nil
 */
+ (id)alertViewWithTitle:(NSString *)title message:(NSString *)message resultBlock:(AlertViewResultBlockType)block cancelButtonTitle:(NSString *)cancelButtonTitle otherButtonTitles:(NSString *)otherButtonTitles, ... NS_REQUIRES_NIL_TERMINATION;

@end
