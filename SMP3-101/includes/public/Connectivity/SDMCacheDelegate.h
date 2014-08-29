//
//  SDMCacheDelegate.h
//
//  SDMConnectivity library
//
//  Created by Karoly Nyisztor on Apr 11, 2011
//  Copyright SAP AG 2011. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SDMRequesting;

/**
 * Supported cache policies
 */
__attribute((deprecated("Use ECachePolicy instead")))
typedef enum ECachePolicy 
{
	//!
	DefaultCachePolicy = 0,
    //! do not use the DownloadCache 
	IgnoreCachePolicy = 1,
	//! fetch only if cached content differs from server content
	ReloadIfDifferentCachePolicy = 2,
	//! fetch only when cache is empty
	OnlyLoadIfNotCachedCachePolicy = 3,
	//! fetch only when network errors occur
	UseCacheIfLoadFailsCachePolicy = 4
} CachePolicy;

/**
 * Supported cache lifetime policies
 */
__attribute((deprecated("Use ECacheStoragePolicy instead")))
typedef enum ECacheStoragePolicy 
{
	//! cache is persisted only for this session
	CacheForSessionDurationCacheStoragePolicy = 0,
	//! cache persists after the session expires
	CachePermanentlyCacheStoragePolicy = 1
} CacheStoragePolicy;

/**
 * @deprecated
 * Defines default DownloadCache delegate methods
 * Protocol to be adapted by client classes in order to achieve the DownloadCache functionality
 * @remark Clients might consider using the SDMDownloadCache rather than implementing a custom download cache
 */
__attribute((deprecated("Use CacheDelegate instead")))
@protocol SDMCacheDelegate <NSObject>

@required

/**
 * Should return the cache policy that will be used when requests have their cache policy set to DefaultCachePolicy
 */
- (CachePolicy)defaultCachePolicy;

/**
 * Should Remove cached data for a particular request
 */
- (void)removeCachedDataForRequest:( id<SDMRequesting> )request;

/**
 * Should return YES if the cache considers its cached response current for the request
 * Should return NO if the data is not cached, or (for example) if the cached headers state the request should have expired
 */
- (BOOL)isCachedDataCurrentForRequest:(id<SDMRequesting>)request;

/**
 * Should store the response for the passed request in the cache
 * When a non-zero maxAge is passed, it should be used as the expiry time for the cached response
 */
- (void)storeResponseForRequest:(id<SDMRequesting>)request maxAge:(NSTimeInterval)maxAge;

/**
 * Should return an NSDictionary of cached headers for the passed request, if it is stored in the cache
 */
- (NSDictionary *)cachedHeadersForRequest:(id<SDMRequesting>)request;

/**
 * Should return the cached body of a response for the passed request, if it is stored in the cache
 */
- (NSData *)cachedResponseDataForRequest:(id<SDMRequesting>)request;

/**
 * Same as the above, but returns a path to the cached response body instead
 */
- (NSString *)pathToCachedResponseDataForRequest:(id<SDMRequesting>)request;

/**
 * Clear cached data stored for the passed storage policy
 */
- (void)clearCachedResponsesForStoragePolicy:(CacheStoragePolicy)cachePolicy;
@end
