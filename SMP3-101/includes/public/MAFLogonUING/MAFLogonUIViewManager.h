//
//  MAFNavigationManager.h
//  MAFLogonUING
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

//#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol MAFLogonNGPublicAPI;
@protocol MAFLogonUICustomizationDelegate;

/**
 This class handles the navigation between the screens
 */
@interface MAFLogonUIViewManager : NSObject

/**
 The logonManager where the operations can be initiated. One has to set up the @see logonDelegate to be notified about the result of the operations
 */
@property (readonly) NSObject<MAFLogonNGPublicAPI> *logonManager;

/**
 The actually presented viewController of the application. This will be used to present the logon related screens.
 */
@property (nonatomic, retain) UIViewController* parentViewController;

/**
 An optional delegate which will be called during the creation of the views in the logon.
 The application has the ability to change different parts of the UI using this delegate
 */
@property (nonatomic, assign) NSObject<MAFLogonUICustomizationDelegate> *logonUICustomizationDelegate;


@end
