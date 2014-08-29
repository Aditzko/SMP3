//
//  SDMCache.h
//  SDMParser
//
//  Created by Nyisztor Karoly on 4/29/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMCaching.h"

/**
 * @deprecated 
 * In-memory cache, providing additional features like data filtering and serialization
 * <pre>
 * Usage
 * <code>
 * <b>// 1. Initalize Cache</b>
 *
 * SDMCache* cache = [SDMCache cacheWithServiceDoc:SvcDoc];
 * //the cache's UID is generated during the cache's initialization
 *
 * //set the cache that it will be persisted automatically if the application receives a memory warning from the system
 * [SDMCache setShouldAutoSaveOnMemoryWarning:YES];
 * //the default value is NO, because if the user does not care about storing the uid and the library persists the cache, the user can not load the cache in without the uid 
 * 
 * //get the UID from the cache
 * NSString* uid = [cache retrieveUID];
 *
 * //store uid in UserDefaults to make it loadable in case of autoSaveOnMemoryWarning
 * [[NSUserDefaults standardUserDefaults] setObject:uid forKey: UNIQUE_KEY_TO_STORE_AND_LOAD_THE_UID_OF_THE_CACHE ];
 * [[NSUserDefaults standardUserDefaults] synchronize];
 * 
 * <b>// 2. Store Cache</b>
 *
 * //get UID from cache object
 * NSString* uid = [cache retrieveUID];
 * //store cache's uid in the UserDefaults for the UNIQUE_KEY_TO_STORE_AND_LOAD_THE_UID_OF_THE_CACHE
 * [[NSUserDefaults standardUserDefaults] setObject:uid forKey: UNIQUE_KEY_TO_STORE_AND_LOAD_THE_UID_OF_THE_CACHE ];
 * [[NSUserDefaults standardUserDefaults] synchronize];
 * //store cache
 * [[SDMPersistence instance] storeCache: cache];
 *
 * //other (equivalent) solution
 * //store the cache and get the uid of the cache
 * NSString* uid = [[SDMPersistence instance] storeCache: cache];
 * //store cache's uid in the UserDefaults for the UNIQUE_KEY_TO_STORE_AND_LOAD_THE_UID_OF_THE_CACHE
 * [[NSUserDefaults standardUserDefaults] setObject:uid forKey: UNIQUE_KEY_TO_STORE_AND_LOAD_THE_UID_OF_THE_CACHE ];
 * [[NSUserDefaults standardUserDefaults] synchronize];
 *
 * <b>// 3. Load Cache</b>
 *
 * //load the previously persisted serviceDoc
 * NSString* uid = (NSString*)[[NSUserDefaults standardUserDefaults] objectForKey: UNIQUE_KEY_TO_STORE_AND_LOAD_THE_UID_OF_THE_CACHE ];
 *
 * #ifdef DEBUG
 * NSLog(@"Cache's Uid: %@", uid);
 * #endif			
 * if ([NSString isNullOrEmpty: uid]) {
 *		//There is no UID saved for the UNIQUE_KEY_TO_STORE_AND_LOAD_THE_UID_OF_THE_CACHE
 * }else{
 *		//There is a UID saved for the UNIQUE_KEY_TO_STORE_AND_LOAD_THE_UID_OF_THE_CACHE
 *		
 *		//load the previosly persisted cache
 *		cache = [[SDMPersistence instance] loadCache:uid];
 *		
 *		//check whether the cache is empty
 *		if (cache) {
 *			//The cache exists, use it
 *			...
 *		}else {
 *			//The cache is empty, maybe cleared, or wrong UID was provided
 *		}
 * } 
 * </code>
 * </pre>
 * @remark Clients might consider using the SDMPersistence rather than implementing a custom persistence
 *
 * @see SDMCaching 
 */
__attribute((deprecated("Use Cache for libCache instead")))
@interface SDMCache : NSObject <SDMCaching, NSCoding> {
	/**
	 * Root of the metadata tree
	 * As this is the root object in the hierarchy, it should be set before attempting to access any further data in the cache 
	 */
	SDMODataServiceDocument* m_ODataServiceDocument;
	/**
	 * Storage for NSMutableDictionary* < collectionName*, NSMutableDictionary*<id, SDMODataEntry* > >
	 */
	NSMutableDictionary* m_ODataEntriesDict;
	/**
	 * Storage for NSMutableDictionary* < collectionName*, NSMutableArray*<SDMODataPropertyInfo.name* >
	 */
	NSMutableDictionary* m_SearchablePropertiesDict;	
	/**
	 * Entry count which can be kept in memory
	 * @remark There is a 
	 */
	unsigned short m_Capacity;
	/**
	 * Unique ID of the cache to store and load it using the SDMPersistence
	 * @see SDMPersistence
	 */
	NSString* m_CacheUid;
}	

#pragma mark -
#pragma mark Accessors
@property (nonatomic, retain, getter = getODataServiceDocument, setter = setODataServiceDocument:) SDMODataServiceDocument* serviceDocument;
@property (nonatomic, assign, readonly, getter = getODataEntriesDict) NSDictionary* entriesDict;
@property (nonatomic, assign) unsigned short capacity;
@property (nonatomic, readonly, retain, getter = getUid ) NSString* cacheUid;
/**
 * Enables in-cache filtering using regular expressions
 * @remark supports wildcard based search (* and ?) at the cost of some performance hit 
 */
@property (nonatomic, assign, setter = setRegexSearchEnabled:, getter = isRegexSearchEnabled) BOOL regexEnabled;
#if USE_MAXNUMBER_OF_SEARCH_RESULTS
/**
 * Sets the max number of entries returned by filterEntriesOfCollection: forSearchText:
 */
@property (nonatomic, retain, setter = setMaxNumberOfSearchResults:, getter = getMaxNumberOfSearchResults) NSNumber* maxNumberOfSearchResults;
#endif

#pragma mark -
#pragma mark In-memory Cache Management
/**
 * Should wipe out all cached content.
 */
- (void) clear;
/**
 * Inits the SDMCache instance
 */
- (id)initWithServiceDocument:(SDMODataServiceDocument*)serviceDoc_in;
/**
 * Static Factory method
 * @param serviceDoc_in the SDMODataServiceDocument to be cached in memory; required root object, if not set, cache is unusable
 * @return SDMCache* or nil if invalid SDMODataServiceDocument* passed
 */
+ (id)cacheWithServiceDoc:(SDMODataServiceDocument*)serviceDoc_in;

/**
 * Removes the cached SDMODataServiceDocument which acts as a root of the metadata tree
 * @remark Without a valid SDMODataServiceDocument, the cache renders useless. Only invoke this API if you know what you are doing! 
 */
- (BOOL) removeODataServiceDocument;
/**
 * Removes an SDMODataEntry from the cache
 * @param entry_in the SDMODataEntry to be removed
 * @return YES is the entry was successfully removed, NO otherwise
 */
- (BOOL) removeODataEntry:(const SDMODataEntry*) entry_in forCollection:(NSString*)collectionName_in;
/**
 * Removes all SDMODataEntry entries from the cache which belong to the given collection
 * @param collectionName_in the collection href for which we want to remove the entries
 * @return YES is the entries have been successfully removed, NO otherwise
 */
- (BOOL) removeODataEntriesForCollection:(NSString*) collectionName_in;

#pragma mark -
#pragma mark Filtering

/**
 * Filters cached entries with searchable properties according to the search term
 * @remark Currently word start match and minimal regex (wildcard search * and ?) is supported. The search is case insensitive.
 * @remark searching for * or ? is only working with full property values, (not works with one term of a property value, which contains more terms)
 * @discussion We provide a Google-alike search method: during filtering, multiple words are treated as separate search terms. 
 * Filtering for John Appleseed results in a search for "John" and another one for "Appleseed", while "John Appleseed" will match against the exact string.
 *
 * @param collectionName_in - the ID of the collection is needed to lookup metadata description
 * @param searchText_in - the search text 
 * @return filtered array with the SDMODataEntry objects, or empty array if the searchText is nil or empty
 */
- (NSArray*)filterEntriesOfCollection:(NSString*)collectionName_in forSearchText:(NSString*)searchText_in;

#pragma mark -
#pragma mark Accessors
/**
 * Sets a valid metadata tree with a SDMODataServiceDocument as root, which will be kept in memory
 * @remark The current SDMParser implementation builds a complete metadata tree based on the OData payloads
 * The metadata tree is built in two phases: first, an incomplete metadata tree is built by parsing the ServiceDocument; 
 * the metadata gets parsed during the second step (as it relies on the results of the svc parsing), and completes the metadata tree
 * @param serviceDocument_in SDMODataServiceDocument to be stored in memory
 */
//- (void) setODataServiceDocument:(const SDMODataServiceDocument*) serviceDocument_in;
/**
 * Stores a data entry (which is the result of data parsing)
 * @param entry_in SDMODataEntry to be stored in memory
 * @param collectionName_in identifies the entry's Collection
 * @param entryId_in unique entry ID
 * @see getODataEntryByCollection: getODataEntriesByCollection:
 */
- (void) setODataEntry:(const SDMODataEntry*) entry_in byCollection:(NSString*)collectionName_in;
/**
 * Stores an array of SDMODataEntry instance pointers
 * @param entries_in SDMODataEntry* array to be cached in memory
 * @param collectionName_in identifying the entries' collection
 * @see getODataEntryByCollection: getODataEntriesByCollection:
 */
- (void) setODataEntries:(NSArray*) entries_in byCollection:(NSString*)collectionName_in;
/**
 * Retrieves the SDMODataServiceDocument 
 * @return pointer to a valid SDMODataServiceDocument object or nil;
 * @remark the returned object is the root of the metadata tree; tree elements can be accessed by traversing the tree or using convenoenece APIs provided by this library
 * @see setODataServiceDocument:
 */
//- (const SDMODataServiceDocument*) getODataServiceDocument;
/**
 * Retrieves the previously cached data entry (which is the result of data parsing)
 * @param collectionName_in identifies the entry's Collection
 * @param entryId_in unique entry ID
 * @return SDMODataEntry stored in memory
 * @see setODataEntry: setODataEntries: 
 */
- (const SDMODataEntry*) getODataEntryByCollection:(NSString*)collectionName_in andEntryId:(NSString*)entryId_in;
/**
 * Retrieves an array of SDMODataEntry instance pointers
 * @param collectionName_in identifying the entries' collection
 * @return array of SDMODataEntry*
 * @see SDMODataEntry setODataEntry: setODataEntries: 
 */
- (NSMutableArray*) getODataEntriesByCollection:(NSString*)collectionName_in;
/**
 * Retrieves all workspaces belonging to the stored SDMODataServiceDocument
 * @remark access via SDMODataServicedocument -> SDMODataSchema -> array<SDMODataWorkspace*>
 * @return array of SDMODataWorkspace* belonging to the stored SDMODataServiceDocument
 * @see SDMODataWorkspace
 */
- (NSArray*) getAllWorkspaces;
/**
 * Retrieves the workspace based on the provided semantics
 * @param semantic_in the semantic for the Workspace to be retrieved
 * @return array of SDMODataWorkspace* for the given semantic, or nil if none found
 * @see SDMODataWorkspace
 */
- (NSArray*) getWorkspacesBySemantic:(enum TEN_WORKSPACE_SEMANTICS) semantic_in;
/**
 * Retrieves all collections for a given workspace
 * @param workspace_in the workspace which 'holds' collections
 * @return collections for the given workspace
 * @see SDMODataCollection
 */
- (NSArray*) getCollectionsByWorkspace:(SDMODataWorkspace*) workspace_in;
/**
 * Retrieves a collection based on it's name
 * @param collectionName_in collection's name to be retrieved
 * @return valid SDMODataCollection* or nil
 * @see SDMODataCollection
 */
- (const SDMODataCollection*) getCollectionByName:(NSString*) collectionName_in;
/**
 * Sets that the cache will be saved automatically if the application receives memory warning
 * @param flag_in if YES the cache will be saved automatically if the application receives memory warning
 */
+ (void) setShouldAutoSaveOnMemoryWarning:(BOOL) flag_in;
/**
 * Get that the cache will be saved automatically if the application receives memory warning
 */
+ (BOOL) shouldAutoSaveOnMemoryWarning;


@end
