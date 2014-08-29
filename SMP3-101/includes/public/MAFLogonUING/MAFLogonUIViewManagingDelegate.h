//
//  MAFLogonUIViewManagingDelegate.h
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

@class MAFLogonContext;

typedef enum {
    MAFLogonViewActionStart = 1,
    MAFLogonViewActionCancel = 2,
    MAFLogonViewActionForgotPasscode = 3,
    MAFLogonViewActionSkip = 4,
    MAFLogonViewActionTurnOnPasscode = 5,
    MAFLogonViewActionTurnOffPasscode = 6,
    MAFLogonViewActionChangePasscode = 7,
} MAFLogonViewAction;

/**
 Protocolt to UI related operations
 */
@protocol MAFLogonUIViewManagingDelegate <NSObject>

- (void) splashViewExecuteAction:(MAFLogonViewAction)selectedAction;

- (void) registrationViewExecuteAction:(MAFLogonViewAction)selectedAction logonContext:(MAFLogonContext*)aContext;

- (void) passcodeCreationViewExecuteAction:(MAFLogonViewAction)selectedAction password:(NSString*)aPassword logonContext:(MAFLogonContext*)aContext;

- (void) unlockViewExecuteAction:(MAFLogonViewAction)selectedAction password:(NSString*)aPassword;

- (void) passcodeChangeViewExecuteAction:(MAFLogonViewAction)selectedAction oldPasscode:(NSString*)oldPasscode passcode:(NSString*)newPasscode;

- (void) backendPasswordChangeViewExecuteAction:(MAFLogonViewAction)selectedAction newPassword:(NSString *)newPassword;

- (void) registrationInfoViewExecuteAction:(MAFLogonViewAction)selectedAction;

- (void) ssoSetPasscodeViewExecuteAction:(MAFLogonViewAction)selectedAction passcode:(NSString*)aPasscode;
- (void) ssoChangePasscodeViewExecuteAction:(MAFLogonViewAction)selectedAction passcode:(NSString*)aPasscode;

- (void) enterCredentialsExecuteAction:(MAFLogonViewAction)selectedAction userName:(NSString*)aUserName password:(NSString*)aPassword;

- (void) enterAfariaCredentialsExecuteAction:(MAFLogonViewAction)selectedAction username:(NSString*)username password:(NSString*)password;

@end