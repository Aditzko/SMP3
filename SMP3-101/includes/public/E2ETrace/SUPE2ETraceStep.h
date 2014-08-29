//
//  Step.h
//  BusTrans
//
//  Created by Schmidt, Claudia on 29.06.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PerformanceCounter.h"
//#import "SUPE2ETraceTransaction.h"
//#import "SUPE2ETraceRequest.h"
//#import "SAPExtendedPassport.h"

@interface SUPE2ETraceStep : NSObject {
    NSMutableDictionary * m_Attributes;
    NSMutableArray * m_ReqList;
    NSMutableArray * m_EventList;
    PerformanceCounter * perfCounter;
    
}
//@property (readwrite, copy) PerformanceCounter * perfCounter;
//@property (readwrite, copy) NSMutableDictionary * StepAttributes;
@property (readonly, copy) NSMutableArray *  Messages;
@property (readonly, copy) NSMutableArray * Events;


+ (SUPE2ETraceStep *) createStep;
- (void) addUIAction;
- (Boolean) endStep;
- (NSString *) getXML;

@end
