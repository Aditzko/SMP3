//
//  SDMPersisting.h
//  SDMPersistence
//
//  Created by Nyisztor Karoly on 4/21/11.
//  Copyright 2011 SAP AG. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "SDMCaching.h"
/**
 * Supported Storage Policies
 */
typedef enum EStoragePolicy 
{
	FullProtectionStoragePolicy = 0,///< everything is stored in encrypted form on the filesystem
	NoProtectionStoragePolicy = 1	///< unencrypted storage
} StoragePolicy;

__attribute((deprecated("Use Cache (with implicit persistence) instead")))
/**
 * @deprecated   
 * Declares the Persistence protocol (interface)
 * Protocol to be adapted by client classes in order to achieve the Persistence functionality
 * @remark Clients might consider using the SDMPersistence rather than implementing a custom persistence
 * @see SDMPersistence
 */
@protocol SDMPersisting <NSObject>

@required

#pragma mark -
#pragma mark Persistent Store Management
/**
 * Should wipe out all persisted content.
 */
- (void) clear;
/**
 * Should store the data to the app's sandbox, returning a unique identifier
 * The returned UID has to be managed by the caller in order to retrieve the persisted data or to overwrite the contents using a successive storeCache: call 
 * @param cache_in cache object to be persisted 
 * @return unique identifier (has to be managed by the caller in order to retrieve the persisted data)
 * @see loadCache: 
 */
- (NSString*) storeCache:(id<SDMCaching>)cache_in;
/**
 * Should load a previously persisted data based on it's unique identifier
 * The UID is returned upon succesfully persisting the data; it has to be managed by the caller in order to retrieve the persisted data or to overwrite it later on
 * @param uid_in the unique identifier for the persisted cache object
 * @return valid cache object or nil if none found 
 * @see storeCache: 
 */
- (id<SDMCaching>) loadCache:(NSString*) uid_in;
/**
 * Should store the data to the app's filesystem (sandbox), returning a unique identifier
 * The returned UID has to be managed by the caller in order to retrieve the persisted data or to overwrite the contents using a successive storeData: call
 * @param data_in data to be persisted
 * @param id_in should be nil when storing the data for the first time, or an existing ID to overwrite previously stored content
 * @return unique identifier (has to be managed by the caller in order to retrieve the persisted data)
 * @remark for builds targeting iOS4.0+, the provided NSData is persisted in a secure way by default; use -setStoragePolicy: to change the default behaviour (iOS4.0+ only)
 * @see loadData:
 */
- (NSString*) storeData:(NSData*)data_in withId:(NSString*)uid_in;
/**
 * Should load a previously persisted data based on it's unique identifier
 * The UID is returned upon succesfully persisting the data; it has to be managed by the caller in order to retrieve the persisted data
 * @param uid_in the unique identifier for the persisted data
 * @return valid data or nil if none found 
 * @see storeData:
 */
- (NSData*) loadData:(NSString*) uid_in;
/**
 * Should store serializable data to the app's sandbox, returning a unique identifier
 * The returned UID has to be managed by the caller in order to retrieve the persisted data or to overwrite the contents using a successive storeCache: call 
 * @remark The object to be stored has to implement the NSCoding protocol
 * @param serializable_in object adopting the NSCoding protocol to be persisted 
 * @param id_in should be nil when storing an object adopting the NSCoding protocol for the first time, or an existing ID to overwrite previously stored content
 * @return unique identifier (has to be managed by the caller in order to retrieve the persisted data)
 * @see loadCache: 
 */
- (NSString*) storeSerializable:(id<NSCoding>)serializable_in withId:(NSString*)uid_in;
/**
 * Should load a previously persisted object which adopts the NSCoding protocol based on it's unique identifier
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
 * Should return the default storage policy
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

@end
