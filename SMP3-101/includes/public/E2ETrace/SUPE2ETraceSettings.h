//
//  TraceSettings.h
//  BusTrans
//
//  Created by Schmidt, Claudia on 25.07.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface SUPE2ETraceSettings : NSObject {
    //    NSUInteger m_TraceLevel;
    //    NSUInteger m_StepNo;
    //    NSUInteger m_ReqNo;
    //    NSData * m_RootId;
    //    NSData * m_TermId;
    //    Byte m_TraceFlags[2];
}
@property (readonly) NSUInteger StepCount;
@property (readonly) NSUInteger RequestCount;
@property (readwrite) NSUInteger TraceLevel;
@property (readwrite, copy) NSData * RootContext;
@property (readonly, copy) NSData * TerminalId;

+ (SUPE2ETraceSettings *)sharedManager;
- (void) incrementStep;
- (void) incrementRequest;
- (void) resetStep;
- (void) resetRequest;
- (NSData *) TraceFlags;
- (NSString *) TraceFlagsAsString;
- (void) setTraceFlags:(Byte)Byte0 :(Byte)Byte1;
@end
