//
//  Request.h
//  BusTrans
//
//  Created by Schmidt, Claudia on 29.06.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "SUPE2ETraceStep.h"
#import "SAPExtendedPassport.h"

@interface SUPE2ETraceRequest : NSObject {
    
}

@property (readonly, copy) NSMutableDictionary * mRequest;
@property (readonly, copy) NSData * mTransID;
@property (readonly, copy) SAP_ExtendedPassport * mSAPPassport;

/** Standard initialization. The request created receives default attributes. 
 Request timestamp is set to the time of initialization.
 SAP-PASSPORT and X-CorrelationID http headers are created.
 */
+ (SUPE2ETraceRequest *) createRequest: (NSString *) WithId;
/**
 * Retrieves the @“SAP-PASSPORT“ header value.
 * <pre>
 * Usage
 * <code>
 * [m_HTTPRequest addRequestHeader:@“SAP-PASSPORT“ value:[theRequest PassportHttpHeader]];
 * </code>
 * </pre>
 */
- (NSString *) PassportHttpHeader;
/**
 * Retrieves the @“X-CorrelationID“ header value.
 * <pre>
 * Usage
 * <code>
 * [m_HTTPRequest addRequestHeader:@“X-CorrelationID“ value:[theRequest CorrelationIdHttpHeader]]; 
 * </code>
 * </pre>
 */
- (NSString *) CorrelationIdHttpHeader;
/**
 * Should be called before the request is sent out.
 * @return void
 * <pre>
 * Usage
 * <code>
 * SUPE2ETraceController* TraceHandler = [SUPE2ETraceController sharedController];
 * SUPE2ETraceTransaction* Trace = [TraceHandler createTransaction];
 * SUPE2ETraceStep* theStep = [Trace createStep];
 * SUPE2ETraceRequest* theRequest = [theStep createRequest];
 * [theRequest markSending];
 * </code>
 * </pre> 
 */
- (void) markSending;
/**
 * Should be called as soon as the data is being sent.
 * @return void
 * <pre>
 * Usage
 * <code>
 * SUPE2ETraceController* TraceHandler = [SUPE2ETraceController sharedController];
 * SUPE2ETraceTransaction* Trace = [TraceHandler createTransaction];
 * SUPE2ETraceStep* theStep = [Trace createStep];
 * SUPE2ETraceRequest* theRequest = [theStep createRequest];
 * [theRequest markSent];
 * </code>
 * </pre> 
 */
- (void) markSent;
/**
 * When the first data is being received.  
 * @return void
 * <pre>
 * Usage
 * <code>
 * SUPE2ETraceController* TraceHandler = [SUPE2ETraceController sharedController];
 * SUPE2ETraceTransaction* Trace = [TraceHandler createTransaction];
 * SUPE2ETraceStep* theStep = [Trace createStep];
 * SUPE2ETraceRequest* theRequest = [theStep createRequest];
 * [theRequest markReceiving];
 * </code>
 * </pre> 
 */
- (void) markReceiving;
/**
 * When all data from the response have been received call this.
 * @return void
 * <pre>
 * Usage
 * <code>
 * SUPE2ETraceController* TraceHandler = [SUPE2ETraceController sharedController];
 * SUPE2ETraceTransaction* Trace = [TraceHandler createTransaction];
 * SUPE2ETraceStep* theStep = [Trace createStep];
 * SUPE2ETraceRequest* theRequest = [theStep createRequest];
 * [theRequest markReceived];
 * </code>
 * </pre> 
 */
- (void) markReceived;
- (Boolean) updateRequestWithValue: (NSString *)withValue : (NSString *)forKey;
- (Boolean) updateRequestElementsWithDictionary: (NSDictionary *)withDictionary;
/**
 * At the end when response is received.
 * @return Boolean
 * <pre>
 * Usage
 * <code>
 * SUPE2ETraceController* TraceHandler = [SUPE2ETraceController sharedController];
 * SUPE2ETraceTransaction* Trace = [TraceHandler createTransaction];
 * SUPE2ETraceStep* theStep = [Trace createStep];
 * SUPE2ETraceRequest* theRequest = [theStep createRequest];
 * [theRequest markReceived];
 * </code>
 * </pre> 
 */
- (Boolean) endRequest;
- (NSString *) getXML;
@end
