//
//  TraceController.h
//  BusTrans
//
//  Created by Schmidt, Claudia on 04.07.11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SUPE2ETraceTransaction.h"
#import "SUPE2ETraceStep.h"
#import "SUPE2ETraceRequest.h"

/**
 * Class leveraging BusinessTransaction.xml and SAPPassport functionality
 * <pre>
 * <code>
 * SUPE2ETraceController* TraceHandler = [SUPE2ETraceController sharedController];
 * SUPE2ETraceTransaction* Trace = [TraceHandler createTransaction];
 * SUPE2ETraceStep* theStep = [Trace createStep];
 * SUPE2ETraceRequest* theRequest = [theStep createRequest];
 * </code>
 * </pre>
 *
 * <pre>
 * <code>
 * [m_HTTPRequest addRequestHeader:@“SAP-PASSPORT“ value:[theRequest PassportHttpHeader]];
 * [m_HTTPRequest addRequestHeader:@“X-CorrelationID“ value:[theRequest CorrelationIdHttpHeader]];
 * </code>
 * </pre>
 */
@interface SUPE2ETraceController: NSObject {
    
}

@property (readonly, copy) SUPE2ETraceTransaction * mTransaction;
@property (readonly, copy) SUPE2ETraceStep * currentStep;
@property (readonly, copy) SUPE2ETraceRequest * currentRequest;

/** returns a TraceController singleton reference.
 */
+ (SUPE2ETraceController *) sharedController;
/** sets the E2E Tracelevel  with the TraceController 
 @param[in] trcLvl integer representing the tracelevel (LOW=1,MEDIUM=2,HIGH=3)
 */
- (void) setTraceLevel :(NSUInteger)trcLvl;
/** returns a TraceController singleton reference.
 */
- (SUPE2ETraceTransaction *) createTransaction;
/** returns a TraceController singleton reference.
 */
- (SUPE2ETraceTransaction *) createTransactionWithName:(NSString *)transactionName withClientHost:(NSString *)clientHost;

- (SUPE2ETraceRequest *) createRequest;
/** starts a new step with an associated Requestlist container.
 */
- (SUPE2ETraceStep *) createStep;
/** returns a dictionary containing References to Step and Request Object for a given PassportHttpHeader. If developers store the PassportHttpHeader with their own objects they can retrieve the relevant Step and request object references later with PassportHeader as lookup parameter.
 */
- (NSDictionary *) getStepAndRequestByPassportHeader:(NSString *)Passport_in;
/** returns a dictionary containing References to Step and Request Object for a given Key/Value pair within an SUPE2ETraceRequest object. If developers store the Value for a specific Request Key with their own objects they can retrieve the relevant Step and request object references later with the Key and Value as lookup parameter.
 @param[in] Key_in Key field in SUPE2ETraceRequest
 @param[in] Value_in Searchvalue for Key field in SUPE2ETraceRequest
 \par <code>Code Example:</code>
 \snippet BusTransTests.m accessing SUPE2ETraceController
 ...
 \snippet BusTransTests.m searching by key/value pair
 */
- (NSDictionary *) getStepAndRequestForKey:(NSString *)Key_in withSearchString:(NSString *)Value_in;

/** SUPE2ETraceRequest defines a custom searchkey field for use by developers to be set with a application specific value for later retrieval of the SUPE2ETraceRequest and SUPE2ETraceStep object reference. 
 \par <code>Code Example:</code>
 \snippet BusTransTests.m accessing SUPE2ETraceController
 ...
 \snippet BusTransTests.m setting a searchvalue
 */
- (Boolean) setSearchKeyForRequest:(SUPE2ETraceRequest *)theRequest_in WithValue:(NSString *)Value_in;

/** returns a dictionary containing references to Step and SUPE2ETraceRequest object for a given searchvalue within an SUPE2ETraceRequest object. If developers store the value for a specific Request Key with their own objects they can retrieve the relevant Step and request object references later with the Key and Value as lookup parameter.
 @param[in] Value_in Searchvalue for SearchKey field in SUPE2ETraceRequest
 \par <code>Code Example:</code>
 \snippet BusTransTests.m accessing SUPE2ETraceController
 ...
 \snippet BusTransTests.m searching by searchkey value
 */
- (NSDictionary *) getStepAndRequestForSearchValue:(NSString *)Value_in;

/**
 Updates the data for each request and step to form transaction step xml and append it to the business transaction xml
 @param request  current tracerequest
 @param Value  step and tracerequest object value
 @param key  step and tracerequest object key
 */

- (Boolean) updateRequestElementWithValue:(SUPE2ETraceRequest *)theRequest :(NSString *)Value :(NSString *)forKey;

/**
 Updates the data for each request and step to form transaction step xml and append it to the business transaction xml
 @param request  current tracerequest
 @param dictionary  Contains the references to step and traceRequest object with passportheader and co-relationID 
 */
- (Boolean) updateRequestElementsInRequest:(SUPE2ETraceRequest *)theRequest withDictionary:(NSDictionary *)withDictionary;
- (Boolean) endRequest: (SUPE2ETraceRequest *)theRequest;

/** ends step with an associated Requestlist container.
 */
- (Boolean) endStep: (SUPE2ETraceStep *)theStep;
- (Boolean) endTransaction;

/** 
 * returns generated Business Transaction XML.
 * @return String XML
 * <pre>
 * Usage
 * <code>
 * [[SUPE2ETraceController sharedController] getXML];
 * </code>
 * </pre> 
 */
- (NSString *) getXML;

/** 
 * Uploads the generated BTX to provided server URL and returns the response status code 
 * @return Response status code as Integer
 * @param baseUrl  server Url 
 * <pre>
 * Usage
 * <code>
 * [[SUPE2ETraceController sharedController] sendXML:solmanURL];
 * </code>
 * </pre> 
 */


- (NSUInteger) sendXML :(NSURL *)toBaseURL;

@end
