//
//  SDMPersistence.h
//  SDMPersistence
//
//  Created by Nyisztor Karoly on 4/21/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#if TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MAX_ALLOWED < __IPHONE_4_0

#warning The SDMPersistence class uses some security features exclusively available in iOS4.0+ \
Unless you *really* need to support older iOS versions, it is recommended to target at least iOS4.0.

#endif

#import <Foundation/Foundation.h>

#import "SDMPersisting.h"

@class SDMCache;

__attribute((deprecated("Use Cache(with implicit persistence) instead")))
/**
 * @deprecated   
 * Default Persistence implementation
 * <pre>
 * Usage
 * <code>
 * <b>// 1. Store some data</b>
 * // retrieve the singleton instance
 * SDMPersistence* persistence = [SDMPersistence instance];
 * // persist some NSData, and store the uid returned by the method
 * NSString* uid = [persistence storeData:data];
 * // if no valid uid is returned, there was a problem while trying to store the data
 * if( !uid )
 * {
 *	NSLog(@"%@", @"Data could not be persisted!");
 *	// error handling goes here
 * ...
 * }
 * else
 * {
 * 	// store the uid
 * 	...
 * }  
 
 * <b>// 2. Retrieve the persisted data</b>
 * // retrieve the singleton instance
 * SDMPersistence* persistence = [SDMPersistence instance];
 *  
 * // retrieve the previously persisted NSData, based on the uid we received when calling the storeData: API 
 * NSData* data = [persistence loadData:uid];
 * 
 * if( !data )
 * {
 * 	NSLog(@"%@", @"Data could not be retrieved!");
 *	// error handling goes here
 * ...
 * }
 * else
 * {
 * 	// proceed
 * 	...
 * } 
 * </code>
 * </pre>
 * @remark Clients might consider using the SDMPersistence rather than implementing a custom persistence
 *
 * @see SDMPersisting 
 */

@interface SDMPersistence : NSObject <SDMPersisting> {
	/**
	 * The default storage policy for this persistence
	 * Defaults to FullProtectionStoragePolicy for iOS4.0+ and NoProtectionStoragePolicy for iOS builds below 4.0
	 */
	StoragePolicy m_StoragePolicy;
	/**
	 * Persistence access mutex object
	 */
	NSRecursiveLock* m_AccessLock;	
	/**
	 * Path to the persistence directory
	 */
	NSString* storagePath;
	/**
	 * Path to the SDMODataEntry persistence directory
	 */
	NSString* entriesPath;
	/**
	 * Path to the SDMCache persistence directory
	 */
	NSString* cachePath;
}

#pragma mark -
#pragma mark Persistent Store Management
/**
 * Wipes out all persisted content.
 * @remark Handle with care. It permanently deletes all stored data from the persistence.
 */
- (void) clear;
/**
 * Wipes out a persisted cache content.
 * @param an existing ID to deletet previously stored content
 * @remark Handle with care. It permanently deletes the stored data from the cache persistence.
 */
- (void) removeCacheWithId:(NSString*)uid_in;
/**
 * Stores the data to the app's sandbox, returning a unique identifier
 * @remark for builds targeting iOS4.0+, the provided NSData is persisted in a secure way by default; use -setStoragePolicy: to change the default behaviour (iOS4.0+ only)
 * @param cache_in cache object to be persisted 
 * @return cache unique identifier
 * @discussion The returned uid has to be managed by the caller in order to retrieve the persisted data  
 * @see loadCache:
 */
- (NSString*) storeCache:(id<SDMCaching>) cache_in;
/**
 * Loads a previously persisted data based on it's unique identifier
 * @param uid_in the unique identifier for the persisted cache object
 * @return valid cache object or nil if none found  
 * @see storeCache:
 */
- (id<SDMCaching>) loadCache:(NSString*) uid_in;
/**
 * Stores the data to the app's sandbox, returning a unique identifier 
 * @remark for builds targeting iOS4.0+, the provided NSData is persisted in a secure way by default; use -setStoragePolicy: to change the default behaviour (iOS4.0+ only)
 * @param data_in data to be persisted  
 * @param id_in should be nil when storing data for the first time, or an existing ID to overwrite previously stored content 
 * @return unique identifier
 * @see loadData:
 */
- (NSString*) storeData:(NSData*) data_in withId:(NSString*)uid_in;
/**
 * Loads a previously persisted data based on it's unique identifier
 * @remark The UID is returned upon succesfully persisting the data; it has to be managed by the caller in order to retrieve the persisted data 
 * @param uid_in the unique identifier for the persisted data
 * @return valid data or nil if none found  
 * @discussion The returned uid has to be managed by the caller in order to retrieve the persisted data or to overwrite the contents using a successive storeData: call
 * @see storeData:
 */
- (NSData*) loadData:(NSString*) uid_in;
/**
 * Stores serializable data to the app's sandbox, returning a unique identifier
 * The returned UID has to be managed by the caller in order to retrieve the persisted data or to overwrite the contents using a successive storeCache: call 
 * @remark The object to be stored has to implement the NSCoding protocol
 * @param serializable_in object adopting the NSCoding protocol to be persisted 
 * @param id_in should be nil when storing an object adopting the NSCoding protocol for the first time, or an existing ID to overwrite previously stored content
 * @return unique identifier (has to be managed by the caller in order to retrieve the persisted data)
 * @see loadCache: 
 */
- (NSString*) storeSerializable:(id<NSCoding>)serializable_in withId:(NSString*)uid_in;
/**
 * Loads a previously persisted object which adopts the NSCoding protocol based on it's unique identifier
 * The UID is returned upon succesfully persisting the data; it has to be managed by the caller in order to retrieve the persisted data or to overwrite it later on
 * @remark The object to be loaded from disk has to implement the NSCoding protocol
 * @param uid_in the unique identifier for the persisted object
 * @return valid object (implementing NSCoding) or nil if none found 
 * @see storeCache: 
 */
- (id<NSCoding>) loadSerializable:(NSString*) uid_in;

#pragma mark -
#pragma mark Secure Storage 

/**
 * Returns the default storage policy
 * For builds targeting iOS4.0+ the default should be FullProtectionStoragePolicy.
 * Lower iOS versions do not have secure storage support, therefore in this case the default storage policy should be NoProtectionStoragePolicy, with no possibility to change this setting
 * @remark Custom SDMPersistence implementations might provide a way to alter the storage policy for iOS4.0+, superceeding the default setting
 */
- (StoragePolicy) storagePolicy;

#if TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_4_0
/**
 * Controls whether the persistence should be secure or not
 * @remark Storage is secure by defualt on iOS4.0+; for builds below this iOS version, the default setting should be unprotected
 */
-(void) setStoragePolicy:(StoragePolicy)storagePolicy;
#endif

#pragma mark -
#pragma mark Singleton instance
/**
* Static Persistence instance
*/
+ (id)instance;

#pragma mark -
#pragma mark Accessors

@property (nonatomic, assign) StoragePolicy storagePolicy;
@property (retain) NSRecursiveLock* accessLock;
@property (nonatomic, retain, readonly) NSString* storagePath;
@property (nonatomic, retain, readonly) NSString* entriesPath;
@property (nonatomic, retain, readonly) NSString* cachePath;


@end
