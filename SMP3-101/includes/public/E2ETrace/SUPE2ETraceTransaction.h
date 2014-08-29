//
//  Transaction.h
//  BusTrans
//
//  Created by Schmidt, Claudia on 29.06.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAPExtendedPassport.h"


@interface SUPE2ETraceTransaction : NSObject {
    NSString * m_name;
    NSString * m_id;
    NSUInteger m_status;
    NSMutableDictionary * m_attributes;
    NSMutableArray * m_Steplist;
}
@property (readwrite, copy) NSString * TrName;
@property (readwrite, copy) NSString * TrId;
@property (readwrite) NSUInteger TrStatus;
@property (readwrite, copy) NSMutableDictionary * TrAttributes;
@property (readwrite, copy) NSMutableArray * TrSteps;

+ (SUPE2ETraceTransaction *) createTransaction;
+ (SUPE2ETraceTransaction *) createTransactionWithName:(NSString *)transactionName withClientHost:(NSString *)clientHost;
- (Boolean) endTransaction;
- (NSString *) getXML;

@end
