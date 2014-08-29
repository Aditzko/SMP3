//
//  MAFLogEntry.h
//  MAFLogger
//
//  Copyright (c) 2012 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAFLogging.h"

@interface MAFLogEntry : NSObject

{}

@property (nonatomic, retain) NSString* logEntryMessage;
@property (nonatomic, assign) MAFLoggingLevel logEntryLevel;

- (NSString *)description;

-(id)initWithMessage:(NSString*)message andLevel:(MAFLoggingLevel)level;

@end