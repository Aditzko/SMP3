//
//  SAPExtendedPassport.h
//  SDMConnectivityAndParserTest
//
//  Created by Schmidt, Claudia on 14.06.11.
//
//  Modified by Karoly, Nyisztor on 19.07.11
//
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>

/**
 * Defines the Tracing levels
 */
typedef enum ETraceLevels
{
	TraceLevelLow = 1,	///< Trace Level Low
	TraceLevelMedium,	///< Trace Level Medium
	TraceLevelHigh,		///< Level High
	TraceLevelNone,    //= 0xffffffff
} TraceLevel;

//! comment the following lines out if you do not have the required exception classes
/*
#ifndef USE_SDMEXCEPTION
#define USE_SDMEXCEPTION
#endif
*/

/**
 * Class leveraging SAPPassport functionality
 * <pre>
 * <code>
 * SAP_ExtendedPassport* passport = [SAP_ExtendedPassport createPassport];
 *
 * [m_HTTPRequest addRequestHeader:@“SAP-PASSPORT“ value:[passport passportHttpHeader]];
 * [m_HTTPRequest addRequestHeader:@“X-CorrelationID“ value:[passport corrrelationIdHttpHeader]];
 * </code>
 * </pre>
 */
@interface SAP_ExtendedPassport : NSObject {
}

/**
 * Factory method
 * Returns an autoreleased SAPExtendedPassport instance initialized with defaults (medium trace level and auto generated UID)
 */
+ (SAP_ExtendedPassport*) createPassport;

/**
 * Factory method
 * Returns an autoreleased SAPExtendedPassport instance
 */
+ (SAP_ExtendedPassport*) createPassportWithRootId:(NSData *)rootId_in andTraceLevel:(TraceLevel)traceLevel_in;

/**
 * Initializes a Passport object
 * @remark transportId and terminalId will be set to nil
 * @see initWithRootId:(NSData *)rootId_in andTraceLevel:(NSUInteger)traceLevel_in andTransportId:(NSData *)transportId_in andTerminalId:(NSData *)terminalId_in
 */
- (id) initWithRootId:(NSData*)RootId
		andTraceLevel:(TraceLevel)traceLevel_in;

/**
 * Initializes a Passport object
 */
- (id) initWithRootId:(NSData *)rootId_in
		andTraceLevel:(TraceLevel)traceLevel_in 
	   andTransportId:(NSData *)transportId_in
		andTerminalId:(NSData *)terminalId_in;

/**
 * Retrieves the @“SAP-PASSPORT“ header value
 */
- (NSString*) passportHttpHeader;

/**
 * Retrieves the @“X-CorrelationID“ header value
 */
- (NSString*) correlationIdHttpHeader;

/**
 * Factory method
 * Returns an autoreleased UUID instance
 */
+ (NSData*) getuuidAsData;

/**
 * Factory method
 * Returns an autoreleased UUID instance as HEXASCII-String
 */
+ (NSString*) getuuidAsString;

@end
