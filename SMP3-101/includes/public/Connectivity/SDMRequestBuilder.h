//
//  SDMRequestBuilder.h
//  Connectivity
//
//  Created by Nyisztor Karoly on 5/19/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMRequesting.h"
#import "SDMCacheDelegate.h"

typedef enum ERequestType {
	ODPRequestType	= 0xFE,  ///< denotes SUPRequest
	HTTPRequestType = 0xFF ///< denotes SDMHttpRequest
} RequestType;

typedef enum ETraceLevel {
	LOW	= 1,  
	MEDIUM, 
    HIGH,
    NONE
} Level;

@class ODPRequest;
@class SDMHttpRequest;

/**
 * @deprecated
 * Acts as a configuration based runtime switch between SDMHttpRequest or SUPRequest.
 */
__attribute((deprecated("Use RequestBuilder instead")))
@interface SDMRequestBuilder :  NSObject
{
@private
	RequestType m_RequestType;
}

/**
* Factory method with url. Can instantiate SUPRequest or SDMHttpRequest based on the configuration.
* @param newURL Object of NSURL class.
* @examples
* <pre>
* id<SDMRequesting> request = [SDMRequestBuilder requestWithURL:[[NSURL alloc] initWithString:@"http://host:port/context/serviceDoc/"]];
* </pre>
*/
+ (id<SDMRequesting>) requestWithURL:(NSURL *)newURL;

/**
 * Factory method with url and cache. Can instantiate SUPRequest or SDMHttpRequest based on the configuration. The cache parameter gets ignored whenever an SUPRequest is created. SDMHttpRequest supports the download cache feature; clients might pass a valid download cache object; this paramater is ignored whenever an SUPRequest is created.
 * @param newURL Object of NSURL class.
 * @param cache Object of class implementing SDMCacheDelegate protocol.
 * @examples
 * <pre>
 * id<SDMRequesting> request = [SDMRequestBuilder requestWithURL:[[NSURL alloc] initWithString:@"http://host:port/context/serviceDoc/"] usingCache:cache];
 * </pre>
 */
+ (id<SDMRequesting>) requestWithURL:(NSURL *)newURL usingCache:(id <SDMCacheDelegate>)cache;

/**
 * Factory method with url, cache and a cache policy. Can instantiate SUPRequest or SDMHttpRequest based on the configuration. Cache related parameters get ignored whenever an SUPRequest is created. SDMHttpRequest supports the download cache feature; clients might pass a valid download cache object and a cache policy; cache parameters are ignored whenever an SUPRequest is created.
 * @param newURL Object of NSURL class.
 * @param cache Object of class implementing SDMCacheDelegate protocol.
 * @param policy CachePolicy enum value.
 * @examples
 * <pre>
 * id<SDMRequesting> request = [SDMRequestBuilder requestWithURL:[[NSURL alloc] initWithString:@"http://host:port/context/serviceDoc/"] usingCache:cache andCachePolicy:ReloadIfDifferentCachePolicy];
 * </pre>
 */
+ (id<SDMRequesting>) requestWithURL:(NSURL *)newURL usingCache:(id <SDMCacheDelegate>)cache andCachePolicy:(CachePolicy)policy;

/**
 * Helper method to store the request type to be instantiated; the builder decides which class (SDMHttpRequest or SUPRequest) should be instantiated based on this value.
 * @param type_in RequestType enum value.
 */
+ (void) setRequestType:(const enum ERequestType) type_in;

/**
 * Helper method to retrieve the request type.
 * @return ERequest_Type enum value.
 */
+ (enum ERequestType) retrieveRequestType;

/**
 * Switches traceability status, the default is NO. If tracing is enabled, "SAP-PASSPORT" and "X-CorrelationID" headers are set and filled with values to enable SAP Passport functionality.
 * @examples
 * <pre>
 * // set the request type
 * [SDMRequestBuilder setRequestType:HTTPRequestType];
 * // enable tracing before instantiating the request
 * [SDMRequestBuilder enableTracing:YES];
 * // instantiate the request
 * self.request = [SDMRequestBuilder requestWithURL:demoUrl];
 * ...
 * </pre>
 */
+ (void) enableTracing:(BOOL)value_in;

/**
 * Set the trace level, default is MEDIUM.
 * @examples
 * <pre>
 * // enable tracing before instantiating the request
 * [SDMRequestBuilder enableTracing:YES];
 * // set the trace level
 * [SDMRequestBuilder setTraceLevel:HIGH];
 * // instantiate the request
 * self.request = [SDMRequestBuilder requestWithURL:demoUrl];
 * ...
 * </pre>
 */
+ (void) setTraceLevel:(Level)value_in;

/**
 * Helper method to retrieve the trace level.
 */
+ (int) getTraceLevel;

/**
 * Enable XCSRF support. It is disabled by default.
 * @examples
 * <pre>
 * // enable xcsrf before instantiating the request
 * [SDMRequestBuilder enableXCSRF:YES];
 * // instantiate the request
 * self.request = [SDMRequestBuilder requestWithURL:demoUrl];
 * ...
 * </pre>
 */
+ (void) enableXCSRF:(BOOL) enable;

/**
 * Returns tracing status (default is NO).
 */
+ (BOOL) isTracingEnabled;

/**
 * This is an API to help clear the Queue of all queued requests.
 * @examples
 * <pre>
 * [SDMRequestBuilder cancelAllRequestsInQueue];
 * </pre>
 */
+ (void) cancelAllRequestsInQueue;


@end
