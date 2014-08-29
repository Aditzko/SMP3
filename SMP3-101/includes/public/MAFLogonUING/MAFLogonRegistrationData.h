//
//  MAFLogonRegistrationData.h
//  MAFLogonManagerNG
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

#import "MAFLogonRegistrationContext.h"

/**
 Registration data that contains application specific properties
 */
@interface MAFLogonRegistrationData : MAFLogonRegistrationContext

/**
 Application Connection Id received after registering the user on server.
 */
@property (nonatomic, retain, readonly) NSString* applicationConnectionId;

@end
