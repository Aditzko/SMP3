//
//  DownloadCache.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CacheDelegate.h"

@class Request;

/**
 * @brief Download cache to store HTTP responses. Note that the download cache <b>does not</b> work with ODPRequest via SAP Mobile Platform.
 */
@interface DownloadCache : NSObject <CacheDelegate> {
	/**
	 * Requests that store data in the cache should use this cache policy, if their cache policy is set to Default_CachePolicy. The default cache policy for this cache.
	 * Defaults to ReloadIfDifferent_CachePolicy.
	 */
	ECachePolicy defaultCachePolicy;
	
	/**
	 * Directory in which cached data is stored.
	 * Defaults to the HTTPRequestCache directory in the temporary directory.
	 */
	NSString* m_StoragePath;
	
	/**
	 * Cache access mutex object.
	 */
	NSRecursiveLock* m_AccessLock;
	
	/**
	 * Checks whether server prohibits response caching.
	 * If set to YES, the cache looks for cache-control / pragma: no-cache headers, and will not reuse store responses if it finds them.
	 */
	BOOL m_RespectCacheControlHeaders;
}

/**
 * Returns a static DownloadCache instance. Used as a global cache.
 * To make HTTPRequests use it automatically, use [HTTPRequest setDefaultCache:[DownloadCache sharedCache]];
 * <pre>
 * // assign the download cache to the request
 * [m_AsynchRequest setDownloadCache:[DownloadCache instance]];
 * // fine-tune cache settings
 * [m_AsynchRequest setCacheStoragePolicy:CachePermanently_CacheStoragePolicy];
 * <b> Slightly more advanced technique </b>
 * // check for network reachability
 * int reachabilityStatus = [[Reachability reachabilityForInternetConnection] currentReachabilityStatus];
 * // use cached content if no network
 * if (reachabilityStatus == NotReachable) {
 *	[[DownloadCache instance] setDefaultCachePolicy:UseCacheIfLoadFails_CachePolicy];
 * }
 * else {
 *	[[DownloadCache instance] setDefaultCachePolicy:OnlyLoadIfNotCached_CachePolicy];
 * }
 * </pre>
 */
+ (id)instance;

/**
 * A helper function that determines if the server that has requested data should not be cached by looking at the request's response headers.
 */
+ (BOOL)serverAllowsResponseCachingForRequest:(Request *)request;

/**
 * A date formatter to be used to construct an RFC 1123 date.
 * The returned formatter can be used on the calling thread.
 * Do not use this formatter for parsing dates, as the format can vary. It is recommended you use HTTPRequest's dateFromRFC1123String: class method instead.
 */
+ (NSDateFormatter *)rfc1123DateFormatter;

@property (assign, nonatomic) ECachePolicy defaultCachePolicy;
@property (retain, nonatomic) NSString* storagePath;
@property (retain) NSRecursiveLock* accessLock;
@property (assign) BOOL shouldRespectCacheControlHeaders;
@end

