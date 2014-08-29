//
//  RequestBuilder.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Requesting.h"
#import "CacheDelegate.h"
#import "SAPExtendedPassport.h"
#import "SDMRequestBuilder.h"

/**
 * Defines authentication related constants.
 */
//typedef enum Request_Type {
//	ODP_RequestType	= 0xFE,  ///< denotes SUPRequest
//	HTTP_RequestType = 0xFF ///< denotes Request
//} Request_Type;

/**
 * Defines Tracing level related constants.
 */
//typedef enum TraceLevel {
//	Low	= 1,
//	Medium,
//    High,
//    None
//} TraceLevel;

/**
 * String constant to be used by clients to manage the request type
 * <pre>
 * Usage on client side:
 * <code>
 * [RequestBuilder setRequestType:HTTPRequestType];
 * ...
 * // or you can set the value directly, just ensure you are using the proper, unique key
 * NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
 *
 * [defaults setInteger:SUPRequestType forKey:ConnectivityRequestTypeKey];
 * [defaults synchronize];
 * </pre>
 */


@class ODPRequest;
@class Request;

/**
 * @brief Acts as a configuration based runtime switch between Request or ODPRequest.
 * The provided factory methods can return a valid Request, but we cannot guarantee this for ODPRequest.
 * However, as the SUPRequest library and public headers are not bundled with Connectivity lib, we attempt to create the SUPRequest class using NSClassFromString(@"SUPRequest").
 * NSClassFromString will work correctly only if:
 * a) the SUPRequest library and the public header are added to the client project
 * b) the -ObjC value is added to the Other Linker Flags
 */
@interface RequestBuilder :  NSObject
{
@private
	RequestType m_RequestType;
}

/**
 * Clients need to register their custom selectors to be invoked in Offline mode.
 * <pre>
 * // register the client as delegate for this request
 * [RequestBuilder setDelegate:self];
 * </pre>
 */
+(void)setDelegate:(id)delegate;

/**
 * Returns the delegate to be invoked in Offline mode.
 * <pre>
 * // register the client as delegate for this request
 * [RequestBuilder getDelegate];
 * </pre>
 */
+(id)getDelegate;

/**
 * Clients need to register their custom selectors to be invoked in Offline mode.
 * This selector is invoked when request execution is successfully complete.
 * <pre>
 * // register the client as delegate for this request
 * [RequestBuilder setDelegate:self];
 * [RequestBuilder setDidFinishSelector:@selector(offlineRequestFinished:)];
 * </pre>
 */
+(void)setDidFinishSelector:(SEL)selector;

/**
 * Returns the selector registered for Offline mode.
 */
+(SEL)getDidFinishSelector;

/**
 * Clients need to register their custom selectors to be invoked in Offline mode.
 * This selector is invoked when request execution failed.
 * <pre>
 * // register the client as delegate for this request
 * [RequestBuilder setDelegate:self];
 * [RequestBuilder setDidFailSelector:@selector(offlineRequestFailed:)];
 * </pre>
 */
+(void)setDidFailSelector:(SEL)selector;

/**
 * Returns the selector registered for Offline mode.
 */
+(SEL)getDidFailSelector;

/**
 * Returns a BOOL value indicating if Offline mode is enabled.
 * <pre>
 * if([RequestBuilder isOfflineEnabled])
 * {}
 * </pre>
 */
+(BOOL)isOfflineEnabled;

/**
 * Clears all requests in the persistent queue.
 * <pre>
 * NSError *error = nil;
 * [RequestBuilder clearPendingRequestsWithError:&error])
 * </pre>
 */
+(void)clearPendingRequestsWithError:(NSError*)error;

/**
 * Factory method which returns a request object.
 * @remark Can instantiate SUPRequest or Request based on the configuration.
 * @discussion Internally the factory method decides which class to be instantiated based on a setting stored in NSUserDefaults.
 * @param newURL Object of NSURL class.
 * <pre>
 *  [RequestBuilder setRequestType:HTTPRequestType];
 *  id<Requesting> request = [RequestBuilder requestWithURL:[[NSURL alloc] initWithString:applicationEndpoint]];
 * </pre>
 */
+ (id<Requesting>)requestWithURL:(NSURL *)newURL;

/**
 * Factory method which returns a request object created using url and cache.
 * @remark Can instantiate SUPRequest or Request based on the configuration. The cache parameter gets ignored whenever an SUPRequest is created
 * @discussion Request supports the download cache feature; clients might pass a valid download cache object; this paramater is ignored whenever an SUPRequest is created
 * @param newURL Object of NSURL class.
 * @param cache Object of class implementing CacheDelegate protocol.
 * <pre>
 *  [RequestBuilder setRequestType:HTTPRequestType];
 *  id<Requesting> request = [RequestBuilder requestWithURL:[[NSURL alloc] initWithString:applicationEndpoint] usingCache:self];
 * </pre>
 */
+ (id<Requesting>)requestWithURL:(NSURL *)newURL usingCache:(id <CacheDelegate>)cache;

/**
 * Factory method which returns a request object created using url, cache and a cache policy.
 * @remark Can instantiate SUPRequest or Request based on the configuration. Cache related parameters get ignored whenever an SUPRequest is created.
 * @discussion Request supports the download cache feature; clients might pass a valid download cache object and a cache policy; cache parameters are ignored whenever an SUPRequest is created
 * @param newURL Object of NSURL class.
 * @param cache Object of class implementing CacheDelegate protocol.
 * @param policy ECachePolicy enum value.
 * <pre>
 *  [RequestBuilder setRequestType:HTTPRequestType];
 *  id<Requesting> request = [RequestBuilder requestWithURL:[[NSURL alloc] initWithString:applicationEndpoint] usingCache:self andCachePolicy:Default_CachePolicy];
 * </pre>
 */
+ (id<Requesting>)requestWithURL:(NSURL *)newURL usingCache:(id <CacheDelegate>)cache andCachePolicy:(ECachePolicy)policy;

/**
 * Helper method to store the request type to be instantiated; the builder decides which class (Request or SUPRequest) should be instantiated based on this value
 * @param type_in RequestType enum value.
 * <pre>
 *  [RequestBuilder setRequestType:HTTPRequestType];
 * </pre>
 */
+ (void)setRequestType:(const enum ERequestType) type_in;

/**
 * Helper method to retrieve the request type to be instantiated from NSUserDefaults
 * @return Request_Type enum value.
 * <pre>
 *  [RequestBuilder retrieveRequestType];
 * </pre>
 */
+ (enum ERequestType)retrieveRequestType;

/**
 * Switches traceability status, the default is NO.
 * @discussion If tracing is enabled, "SAP-PASSPORT" and "X-CorrelationID" headers are set and filled with values to enable SAP Passport functionality.
 * <pre>
 * // set the request type
 * [RequestBuilder setRequestType:HTTPRequestType];
 * // enable tracing *before* instantiating the request
 * [RequestBuilder enableTracing:YES];
 * // instantiate the request
 * self.request = [RequestBuilder requestWithURL:demoUrl];
 * <pre>
 */
+ (void)enableTracing:(BOOL)value_in;

/**
 * Set the trace level, default is MEDIUM.
 * @discussion If tracing is enabled, "SAP-PASSPORT" and "X-CorrelationID" headers are set and filled with values to enable SAP Passport functionality.
 * <pre>
 * // enable tracing *before* instantiating the request
 * [RequestBuilder enableTracing:YES];
 * // set the trace level
 * [RequestBuilder setTraceLevel:High];
 * // instantiate the request
 * self.request = [RequestBuilder requestWithURL:demoUrl];
 * <pre>
 */
+ (void)setTraceLevel:(TraceLevel)value_in;

/**
 * Returns the trace level set.
 * @return int value indicating the trace level.
 * <pre>
 * int level = [RequestBuilder getTraceLevel];
 * <pre>
 */
+ (int)getTraceLevel;

/**
 * Enable XCSRF support. It is disabled by default.
 * <pre>
 * // enable xcsrf *before* instantiating the request
 * [RequestBuilder enableXCSRF:YES];
 * // instantiate the request
 * self.request = [RequestBuilder requestWithURL:demoUrl];
 * <pre>
 */
+ (void)enableXCSRF:(BOOL) enable;

/**
 * Enable performance logging support. It is disabled by default.
 * @param enable BOOL value.
 * <pre>
 * [RequestBuilder enablePerformanceLogging:YES];
 * <pre>
 */
+ (void)enablePerformanceLogging:(BOOL) enable;

/**
 * Returns performance logging status (default is NO).
 * <pre>
 * if([RequestBuilder isPerformanceLoggingEnabled])
 * {}
 * <pre>
 */
+ (BOOL)isPerformanceLoggingEnabled;

/**
 * Returns tracing status (default is NO).
 * <pre>
 * if([RequestBuilder isTracingEnabled])
 * {}
 * <pre>
 */
+ (BOOL)isTracingEnabled;

/**
 * This is an API to help clear the Queue of all queued requests.
 * <pre>
 * [RequestBuilder cancelAllRequestsInQueue];
 * <pre>
 */
+ (void)cancelAllRequestsInQueue;


@end

