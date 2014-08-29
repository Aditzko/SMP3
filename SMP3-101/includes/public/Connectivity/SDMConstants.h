//
//  Constants.h
//  SDMConnectivity
//
//  Created by Karoly Nyisztor on 8/6/10.
//  Copyright 2010 SAP AG. All rights reserved.
//

//! fallback if no value provided
extern NSString* const NA;

// constants for SAPOData
extern NSString* const XMLSignature;

#pragma mark -
#pragma mark Exception constants
//! Exception thrown when the client tries to set a concurrent thread count higher than MAX_CONCURRENT_THREADS
extern NSString* const ThreadCountTooHigh;
//! Exception thrown when the client tries to add a request to the SDMNetworkQueue which is not an SDMHttpRequest
extern NSString* const InvalidRequestType;

//! Exception thrown when there is an issue with the SAPPassport
extern NSString* const SAPPassportFailure;

//! Exception thrown when there is an issue while instantiating the SDM Http request
extern NSString* const RequestInitError;
//! Exception thrown when there is an issue while instantiating the SUP Request
extern NSString* const SUPRequestInitError;



#pragma mark -
#pragma mark HTTP Request execution related constants
/**
 * Number of maximum allowed parallel HTTP request count
 * @remark The number of concurrent threads has to be kept low, as threads are expensive
 */
extern const unsigned char MAX_CONCURRENT_THREADS;
extern const NSTimeInterval REQUEST_CHECK_INTERVAL_SECONDS; ///< request's status is checked each time the interval expires 

#pragma mark -
#pragma mark HTTP Request setup constants
// HTTP methods to use (GET / POST / PUT / DELETE / HEAD). Defaults to GET
extern NSString* const HTTP_METHOD_GET;     ///< GET Http method
extern NSString* const HTTP_METHOD_POST;    ///< POST Http method
extern NSString* const HTTP_METHOD_PUT;     ///< PUT Http method
extern NSString* const HTTP_METHOD_DELETE;  ///< DELETE Http method
extern NSString* const HTTP_METHOD_HEAD;    ///< HEAD Http method


extern const NSTimeInterval DEFAULT_PERSISTENT_CONNECTION_TIMEOUT_SECONDS; ///< Default persistent connection timeout value (in seconds)

extern const NSTimeInterval DEFAULT_CONNECTION_TIMEOUT_SECONDS; ///< Default connection timeout value (in seconds)

/**
 * constant which limits the upload and download bandwidth to prevent excessive bandwidth usage 
 */
extern unsigned long const WWANBandwidthThrottleAmount;

/**
 * bitfield storing network event flags
 */
extern const CFOptionFlags NETWORK_EVENTS;// = kCFStreamEventOpenCompleted | kCFStreamEventHasBytesAvailable | kCFStreamEventEndEncountered | kCFStreamEventErrorOccurred;

/**
 * The number of times we will allow requests to redirect before we fail with a redirection error
 */
extern const unsigned short REDIRECTION_LIMIT;
/**
 * Max number of records to be kept in the bandwidth usage array
 */
extern const unsigned short MAX_BANDWIDTH_USAGE_MEASUREMENTS;
/**
 * Proxy authentication retry count
 */
extern const unsigned short AUTHENTICATION_RETRY_COUNT;

#pragma mark -
#pragma mark Request Builder constants
/**
 * Request type key for NSUserDefaults : SDMHttpRequest or SUPRequest
 */
extern NSString* const ConnectivityRequestTypeKey;
extern NSString* const SDMConnectivityRequestTypeKey;
