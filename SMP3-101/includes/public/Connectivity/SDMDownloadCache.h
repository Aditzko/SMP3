//
//  SDMDownloadCache.h
//
//  SDMConnectivity library
//
//  Created by Karoly Nyisztor on Apr 11, 2011
//  Copyright SAP AG 2011. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SDMCacheDelegate.h"

@class SDMHttpRequest;

/**
 * @deprecated
 * Download cache to store http responses.Please note that the download cache <b>does not</b> work with ODPRequest via SUP.
 * <br/>
 * [[DownloadCache instance] setDefaultCachePolicy:OnlyLoadIfNotCachedCachePolicy];
 * @examples
 * <pre>
 * // assign the download cache to our request
 * [m_AsynchRequest setDownloadCache:[SDMDownloadCache instance]];
 * // fine-tune cache settings
 * [m_AsynchRequest setCacheStoragePolicy:CachePermanentlyCacheStoragePolicy];
 * // ...
 * 
 * <b> Slightly more advanced technique </b>
 * // check for network reachability
 * int reachabilityStatus = [[Reachability reachabilityForInternetConnection] currentReachabilityStatus];
 * // use cached content if no network
 * if (reachabilityStatus == NotReachable) {
 *	[[SDMDownloadCache instance] setDefaultCachePolicy:UseCacheIfLoadFailsCachePolicy];
 * }
 * else {
 *	[[SDMDownloadCache instance] setDefaultCachePolicy:OnlyLoadIfNotCachedCachePolicy];
 * }
 * </pre>
 */
__attribute((deprecated("Use DownloadCache instead")))
@interface SDMDownloadCache : NSObject <SDMCacheDelegate> {	
	/**
	 * The default cache policy for this cache
	 * Requests that store data in the cache will use this cache policy if their cache policy is set to DefaultCachePolicy
	 * Defaults to ReloadIfDifferentCachePolicy
	 */
	CachePolicy defaultCachePolicy;
	
	/**
	 * The directory in which cached data will be stored
	 * Defaults to a directory called 'HTTPRequestCache' in the temporary directory
	 */
	NSString* m_StoragePath;
	
	/**
	 * Cache access mutex object
	 */
	NSRecursiveLock* m_AccessLock;
	
	/**
	 * Check whether server prohibits response caching
	 * When YES, the cache will look for cache-control / pragma: no-cache headers, and won't reuse store responses if it finds them
	 */ 
	BOOL m_RespectCacheControlHeaders;
}

/**
 * Static DownloadCache instance 
 * Used as a global cache
 * To make HTTPRequests use it automatically, use [HTTPRequest setDefaultCache:[DownloadCache sharedCache]];
 */
+ (id)instance;

/**
 * A helper function that determines if the server has requested data should not be cached by looking at the request's response headers
 */
+ (BOOL)serverAllowsResponseCachingForRequest:(SDMHttpRequest *)request;

// A date formatter that can be used to construct an RFC 1123 date
// The returned formatter is safe to use on the calling thread
// Do not use this formatter for parsing dates because the format can vary slightly - use HTTPRequest's dateFromRFC1123String: class method instead
+ (NSDateFormatter *)rfc1123DateFormatter;

@property (assign, nonatomic) CachePolicy defaultCachePolicy;
@property (retain, nonatomic) NSString* storagePath;
@property (retain) NSRecursiveLock* accessLock;
@property (assign) BOOL shouldRespectCacheControlHeaders;
@end
