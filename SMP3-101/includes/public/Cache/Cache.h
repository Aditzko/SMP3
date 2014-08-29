//  Cache.h
//  Copyright (c) 2013 SAP. All rights reserved.


#import <Foundation/Foundation.h>
#import "Caching.h"

@class ODataEntry;
@class ODataFeed;

/**
 * @brief The class consists of method implementation for caching parsed OData entries. The current implementation uses SQLite Database as the persistence with SQLCipher as the encryption library. It also supports access to the persistence via core data. Cache works against the new parser API <b>(OData*)</b> only. Supports handling delta links and tombstones.
 
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

@interface Cache : NSObject<Caching>

@property(nonatomic, assign) BOOL isPersistable;

- (BOOL)initializeCacheWithError:(NSError**)error;
- (NSArray*)readEntriesForUrlKey:(NSString*)urlKey withError:(NSError**)error;
- (NSArray*)readEntriesLocalForEntryId:(NSString*)entryId forEntityType:(NSString*)entityType withError:(NSError**)error;
- (BOOL)mergeEntriesFromFeed:(ODataFeed*)feed forUrlKey:(NSString*)urlKey withError:(NSError**)error withCompletionBlock:(void (^)(NSNotification* notification))block;
- (BOOL)mergeEntries:(ODataFeed*)feed forUrlKey:(NSString*)urlKey withError:(NSError**)error withCompletionBlock:(void (^)(NSNotification*))block __attribute((deprecated("Use 'mergeEntriesFromFeed' instead. This will be removed in the next drop")));
- (NSString*)addEntry:(ODataEntry*)entry withError:(NSError**)error;
- (BOOL)updateEntry:(ODataEntry*)entry withError:(NSError**)error;
- (BOOL)deleteEntryForEntryId:(NSString*)entryId withError:(NSError**)error;
- (BOOL)clearCacheForUrlKey:(NSString*)urlKey withError:(NSError**)error;
- (BOOL)clearLocalEntryForEntryId:(NSString *)entryId withError:(NSError**)error;
- (NSString *)getDeltaLinkForUrlKey:(NSString*)urlKey withError:(NSError**)error;
- (BOOL)storeDocument:(id)document forDocType:(DocType)type forUrlKey:(NSString*)urlKey withError:(NSError**)error;
- (id)readDocumentForUrlKey:(NSString*)urlKey forDocType:(DocType)type withError:(NSError**)error;
- (void)addNotificationDelegate:(id)delegate withListener:(SEL)listener forUrlKey:(NSString*)urlKey;

@end
