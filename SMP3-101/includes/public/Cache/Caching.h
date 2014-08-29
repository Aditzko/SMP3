//
//  Caching.h
//  Cache
//
//  Created by M, Pramod on 18/06/13.
//  Copyright (c) 2013 M, Pramod. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ODataFeed;
@class ODataEntry;

typedef enum {
    ServiceDocumentType = 0,
    MetaDocumentType = 1
} DocType;


typedef enum {
    UndefinedState = 0, // Usually returned only for server entries
    CreatedState = 100,
    UpdatedState = 101,
    DeletedState = 102
} CacheState;

/**
 * The protocol consists of method definitions for caching parsed OData entries. Cache works against the new parser API <b>(OData*)</b> only. Supports handling delta links and tombstones.
 
 <br/><br/>
 <b>Error codes for caching</b>
 <br/><br/>
 
 600     –  Empty/Nil input parameter(s).
 <br/>
 601     –  No entries match the input.
 <br/>
 602     –  The entry being marked for delete is not a part of the server cache. Cannot perform operation.
 <br/>
 */

@protocol Caching <NSObject>

/**
 * Specifies whether the cache is implicitly persistable. The default value is YES.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  [cacheLocal setIsPersistable:YES];
 *
 *  if ([cacheLocal isPersistable])
 *  {
 *      // Do Stuff;
 *  }
 * </pre>
 */
@property(nonatomic, assign) BOOL isPersistable;

/**
 * Retrieves all the initialized cache metadata. This is the first method called by the application only once during each run of the application.
 * @param error uninitialized error object filled in case of error scenarios.
 * @return Boolean to indicate the outcome of the operation.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  if (![cacheLocal initializeCacheWithError:&error])
 *  {
 *      NSLog(@"Initialize Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */

- (BOOL)initializeCacheWithError:(NSError**)error;

/**
 * Returns an array of <b>ODataEntry*</b> objects stored for the specified URL key. The entries represent the exact state of the back-end and are not touched by the client changes.
 * @param urlKey URL that was originally used to retrieve the entries from the backend and cache it.
 * @param error uninitialized error object filled in case of error scenarios.
 * @return array of <b>ODataEntry*</b> objects that were cached.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSArray* cachedEntries = [cacheLocal readEntriesForUrlKey:urlKey withError:&error];
 *  if (error)
 *  {
 *      NSLog(@"Read Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (NSArray*)readEntriesForUrlKey:(NSString*)urlKey withError:(NSError**)error;

/**
 * Returns an array of <b>ODataEntry*</b> objects stored for the specified entity type and entry ID. These are the local versions of the entry only.
 * @param entityType entity-set to which the entry belongs to. This might mostly be the name of the Collection of the entries. If passed as NIL to the method, it is ignored while querying the cache for entries.
 * @param entryId ID of the entry modified. If passed as NIL to the method, it is ignored while querying the cache for entries.
 * @param error uninitialized error object filled in case of error scenarios.
 * @return array of <b>ODataEntry*</b> objects that were cached.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSArray* localEntries = [cacheLocal readEntriesLocalForEntryId:nil forEntityType:nil withError:&error];
 *  if (error)
 *  {
 *      NSLog(@"Read Local Entry Error: %@@", error);
 *      return;
 *  }
 * </pre>
 */

- (NSArray*)readEntriesLocalForEntryId:(NSString*)entryId forEntityType:(NSString*)entityType withError:(NSError**)error;


/**
 * Merges the entries from the passed feed with the current set of entries (server version only) in the cache. That is, existing entries are updated, and new entries are inserted. Once the merge is complete, a notification is sent to the completion block using the NSNotification format.
 * @param feed feed object containing the array of <b>ODataEntry*</b> objects to be merged into the server version of the cache.
 * @param urlKey URL string which used to get the data from the backend.
 * @param error uninitialized error object which filled in case of error scenarios.
 * @return Boolean to indicate the outcome of the operation.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  ODataDataParser* parser = [[ODataDataParser alloc] initWithEntitySchema:entitySchema andServiceDocument:serviceDoc];
 *  [parser parse:responseData];
 *  [cacheLocal mergeEntriesFromFeed:[parser getFeed] forUrlKey:urlKey withError:&error withCompletionBlock:^(NSNotification *notification) {
 *      NSLog(@"%@", notification);
 *  }];
 *  if(error)
 *  {
 *      NSLog(@"Merge Error: %@@", error);
 *      return;
 *  }
 * </pre>
 */

- (BOOL)mergeEntriesFromFeed:(ODataFeed*)feed forUrlKey:(NSString*)urlKey withError:(NSError**)error withCompletionBlock:(void (^)(NSNotification* notification))block;

/**
 * @deprecated
 */

- (BOOL)mergeEntries:(ODataFeed*)feed forUrlKey:(NSString*)urlKey withError:(NSError**)error withCompletionBlock:(void (^)(NSNotification*))block __attribute((deprecated("Use 'mergeEntriesFromFeed' instead. This will be removed in the next drop")));

/**
 * Adds a new entry cache. This method is called when the application is trying to create entries in the backend using a HTTP POST request.
 * @param entry locally created entry used to invoke a POST request to the backend.
 * @param error uninitialized error object filled in case of error scenarios.
 * @return string that indicates a temporary entry ID assigned to the locally created entry in cache.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSString* tempEntryId = [cacheLocal addEntry:entry withError:&error];
 *  if (error) {
 *      NSLog(@"Add Entry Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (NSString*)addEntry:(ODataEntry*)entry withError:(NSError**)error;

/**
 * This method call is associated with a HTTP PUT request, that is, a modification on the existing resource of a collection. This creates an entry in the ODataEntryLocal cache and mark it as ‘UpdatedState’.
 * @param entry locally modified entry used to invoke a PUT request to the backend.
 * @param error uninitialized error object filled in case of error scenarios.
 * @return Boolean to indicate the outcome of the operation.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  ODataEntry* updateEntry = updateEntryWithChangedValues();
 *  if ([cacheLocal updateEntry:updateEntry withError:&error]) {
 *      NSLog(@"Update Entry Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (BOOL)updateEntry:(ODataEntry*)entry withError:(NSError**)error;

/**
 * Marks an entry from cache for deletion. This is associated with a HTTP DELETE request called to delete a resource for a collection in the backend.
 * @param entryId ID of the entry to be deleted using HTTP DELETE request.
 * @param error uninitialized error object filled in case of error scenarios.
 * @return Boolean to indicate the outcome of the operation.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSString* deletedEntryId = [deletedEntry getEntryID[;
 *  if ([cacheLocal deleteEntryForEntryId:deletedEntryId withError:&error]) {
 *      NSLog(@"Delete Entry Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (BOOL)deleteEntryForEntryId:(NSString*)entryId withError:(NSError**)error;

/**
 * Clears the cache for the URL key passed from all the caches, including the delta token and document cache.
 * @param urlKey URL string against which the entries are cached.
 * @param error uninitialized error object filled in case of error scenarios.
 * @return Boolean to indicate the outcome of the operation.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  if ([cacheLocal clearCacheForUrlKey:urlKey withError:&error]) {
 *      NSLog(@"Clear Cache Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (BOOL)clearCacheForUrlKey:(NSString*)urlKey withError:(NSError**)error;

/**
 * Clears the local entry present in the local cache based on the entry ID passed.
 * @param entryID ID for which the entry should be removed from the local cache.
 * @param error uninitialized error object filled in case of error scenarios.
 * @return Boolean to indicate the outcome of the operation.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSString* deleteEntryId = [deleteEntry getEntryID];
 *  if ([cacheLocal clearLocalEntryForEntryId:deleteEntryId withError:&error]) {
 *      NSLog(@"Clear Local Entry Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (BOOL)clearLocalEntryForEntryId:(NSString *)entryId withError:(NSError**)error;

/**
 * Returns the delta token or delta link for the URL key passed.
 * @param urlKey URL string against which the entries are cached.
 * @param error uninitialized error object filled in case of error scenarios.
 * @return delta token or delta link as a string.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSString* deltaLink = [cacheLocal getDeltaLinkForUrlKey:urlKey withError:&error]
 *  if (error) {
 *      NSLog(@"Delta Token Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */

- (NSString *)getDeltaLinkForUrlKey:(NSString*)urlKey withError:(NSError**)error;

/**
 * Stores the service document or the meta data document for further reuse since they are the base on which data parsing can be performed.
 * @param document document object to be cached.
 * @param type type of the document to be stored. Refer to the Enum DocType.
 * @param urlKey URL string that refers to the base URL of the documents.
 * @param error uninitialized error objectfilled in case of error scenarios.
 * @return Boolean to indicate the outcome of the operation.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  if ([cacheLocal storeDocument:servDoc forDocType:ServiceDocumentType forUrlKey:urlKey withError:&error]) {
 *      NSLog(@"Store Document Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (BOOL)storeDocument:(id)document forDocType:(DocType)type forUrlKey:(NSString*)urlKey withError:(NSError**)error;

/**
 * Reads the service document or the meta data document for further reuse since they are the base on which data parsing can be performed.
 * @param urlKey URL string that refers to the base URL of the documents.
 * @param type type of the document to be stored. Refer to the Enum DocType.
 * @param error uninitialized error object filled in case of error scenarios.
 * @return document object that is cached.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  id document = [cacheLocal readDocumentForUrlKey:urlKey forDocType:ServiceDocumentType withError:&error];
 *  if (error) {
 *      NSLog(@"Read Document Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (id)readDocumentForUrlKey:(NSString*)urlKey forDocType:(DocType)type withError:(NSError**)error;

/**
 * Registers for notifications in case of change in the cached data when the merge is performed.
 * @see <b>-mergeEntriesFromFeed:forUrlKey:withError:withCompletionBlock:</b> for registering completion notification block.
 * @param delegate class object that implements the notification listener method.
 * @param listener name of the listener method.
 * @param urlKey URL string against which the application chooses to listen to notifications.
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  [cacheLocal addNotificationDelegate:self withListener:@selector(notifListener:) forUrlKey:urlKey];
 * </pre>
 */
- (void)addNotificationDelegate:(id)delegate withListener:(SEL)listener forUrlKey:(NSString*)urlKey;
@end
