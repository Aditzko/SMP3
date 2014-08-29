//
//  CacheDelegate.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol Requesting;

/**
 * Consists of supported cache policies.
 */
typedef enum
{
	//!
	Default_CachePolicy = 0,
    //! do not use the DownloadCache
	Ignore_CachePolicy = 1,
	//! fetch only if cached content differs from server content
	ReloadIfDifferent_CachePolicy = 2,
	//! fetch only when cache is empty
	OnlyLoadIfNotCached_CachePolicy = 3,
	//! fetch only when network errors occur
	UseCacheIfLoadFails_CachePolicy = 4
} ECachePolicy;

/**
 * Consists of supported cache lifetime policies.
 */
typedef enum 
{
	//! cache is persisted only for this session
	CacheForSessionDuration_CacheStoragePolicy = 0,
	//! cache persists after the session expires
	CachePermanently_CacheStoragePolicy = 1
} ECacheStoragePolicy;

/**
 * @brief Defines default DownloadCache delegate methods.
 * This protocol should be adapted by client classes to use the DownloadCache functionality.
 * @remark Clients might consider using the DownloadCache rather than implementing a custom download cache.
 */
@protocol CacheDelegate <NSObject>

@required

/**
 * Returns the cache policy to be used when requests have their cache policy set to DefaultCachePolicy.
 */
- (ECachePolicy)defaultCachePolicy;

/**
 * Removes cached data for a particular request.
 * @param request object of Request class.
 * @example
 * <pre>
 *  [cacheDelegate removeCachedDataForRequest:request];
 * </pre>
 */
- (void)removeCachedDataForRequest:( id<Requesting> )request;

/**
 * Returns YES if the cache considers its cached response current for the request.
 * Returns NO if the data is not cached, or (for example) if the cached headers state the request has expired.
 * @param request object of Request class.
 * @example
 * <pre>
 *  [cacheDelegate isCachedDataCurrentForRequest:request];
 * </pre>
 */
- (BOOL)isCachedDataCurrentForRequest:(id<Requesting>)request;

/**
 * Stores the response for the passed request in the cache.
 * When a non-zero maxAge is passed, it should be used as the expiry time for the cached response.
 * @param request object of Request class.
 * @param maxAge object of NSTimeInterval class.
 * @example
 * <pre>
 *  [cacheDelegate storeResponseForRequest:request maxAge:5];
 * </pre>
 */
- (void)storeResponseForRequest:(id<Requesting>)request maxAge:(NSTimeInterval)maxAge;

/**
 * Returns an NSDictionary of cached headers for the passed request, if it is stored in the cache.
 * @param request object of Request class.
 * @return Returns object of NSDictionary class.
 * @example
 * <pre>
 *  NSDictionary *headers = [cacheDelegate cachedHeadersForRequest:request];
 * </pre>
 */
- (NSDictionary *)cachedHeadersForRequest:(id<Requesting>)request;

/**
 * Returns the cached body of a response for the passed request, if it is stored in the cache.
 * @param request object of Request class.
 * @return Returns object of NSData class.
 * @example
 * <pre>
 *  NSData *response = [cacheDelegate cachedResponseDataForRequest:request];
 * </pre>
 */
- (NSData *)cachedResponseDataForRequest:(id<Requesting>)request;

/**
 * Returns a path to the cached response body.
 * @param request object of Request class.
 * @return Returns object of NSString class.
 * @example
 * <pre>
 *  NSString *path = [cacheDelegate pathToCachedResponseDataForRequest:request];
 * </pre>
 */
- (NSString *)pathToCachedResponseDataForRequest:(id<Requesting>)request;

/**
 * Clears cached data stored for the passed storage policy.
 * @param cachePolicy ECacheStoragePolicy enum value.
 * @example
 * <pre>
 *  [cacheDelegate clearCachedResponsesForStoragePolicy:CachePermanently_CacheStoragePolicy];
 * </pre>
 */
- (void)clearCachedResponsesForStoragePolicy:(ECacheStoragePolicy)cachePolicy;
@end

