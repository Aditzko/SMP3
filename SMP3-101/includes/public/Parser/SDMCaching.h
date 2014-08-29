//
//  SDMCaching.h
//  SDMCache
//
//  Created by Nyisztor Karoly on 4/28/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

@class SDMODataSchema;
@class SDMODataServiceDocument;
@class SDMODataCollection;
@class SDMODataEntry;
#import "SDMODataWorkspace.h"

#ifndef USE_MAXNUMBER_OF_SEARCH_RESULTS
#define USE_MAXNUMBER_OF_SEARCH_RESULTS 0
#endif

/**
 * @deprecated 
 * Declares the In-memory Cache protocol
 * Protocol to be adapted by client classes in order to achieve the in-memory storage and filtering functionality
 * @remark Clients might consider using the SDMCache rather than implementing a custom cache
 * @see SDMCache, SDMParser
 */
__attribute((deprecated("Use Caching from libCache instead")))
@protocol SDMCaching <NSObject>

@required

#pragma mark -
#pragma mark In-memory Cache Management
/**
 * Should wipe out all cached content.
 */
- (void) clear;

/**
 * Should set a valid metadata tree with a SDMODataServiceDocument as root, which will be kept in memory
 * @remark The current SDMParser implementation builds a complete metadata tree based on the OData payloads
 * The metadata tree is built in two phases: first, an incomplete metadata tree is built by parsing the ServiceDocument; 
 * the metadata gets parsed during the second step (as it relies on the results of the svc parsing), and completes the metadata tree
 * @param serviceDocument_in SDMODataServiceDocument to be stored in memory
 */
- (void) setODataServiceDocument:(SDMODataServiceDocument*) serviceDocument_in;

/**
 * Removes the cached SDMODataServiceDocument which acts as a root of the metadata tree
 * @remark Without a valid SDMODataServiceDocument, the cache renders useless 
 */
- (BOOL) removeODataServiceDocument;
/**
 * Should store data entry (which is the result of data parsing)
 * @param entry_in SDMODataEntry to be stored in memory
 * @param collectionName_in identifies the entry's Collection
 * @param entryId_in unique entry ID
 * @see getODataEntryByCollection: getODataEntriesByCollection:
 */
- (void) setODataEntry:(const SDMODataEntry*) entry_in byCollection:(NSString*)collectionName_in;
/**
 * Removes an SDMODataEntry from the cache
 * @param entry_in the SDMODataEntry to be removed
 * @return YES is the entry was successfully removed, NO otherwise
 */
- (BOOL) removeODataEntry:(const SDMODataEntry*) entry_in forCollection:(NSString*)collectionName_in;
/**
 * Should store an array of SDMODataEntry instance pointers
 * @param entries_in SDMODataEntry* array to be cached in memory
 * @param collectionName_in identifying the entries' collection
 * @see getODataEntryByCollection: getODataEntriesByCollection:
 */
- (void) setODataEntries:(NSArray*) entries_in byCollection:(NSString*)collectionName_in;
/**
 * Removes all SDMODataEntry entries from the cache which belong to the given collection
 * @param collectionName_in the collection href for which we want to remove the entries
 * @return YES is the entries have been successfully removed, NO otherwise
 */
- (BOOL) removeODataEntriesForCollection:(NSString*) collectionName_in;
/**
 * Should retrieve the SDMODataServiceDocument 
 * @return pointer to a valid SDMODataServiceDocument object or nil;
 * @remark the returned object is the root of the metadata tree; tree elements can be accessed by traversing the tree or using convenoenece APIs provided by this library
 * @see setODataServiceDocument:
 */
- (SDMODataServiceDocument*) getODataServiceDocument;
/**
 * Should retrieve the previously cached data entry (which is the result of data parsing)
 * @param collectionName_in identifies the entry's Collection
 * @param entryId_in unique entry ID
 * @return SDMODataEntry stored in memory
 * @see setODataEntry: setODataEntries: 
 */
- (const SDMODataEntry*) getODataEntryByCollection:(NSString*)collectionName_in andEntryId:(NSString*)entryId_in;
/**
 * Should retrieve an array of SDMODataEntry instance pointers
 * @param collectionName_in identifying the entries' collection
 * @return array of SDMODataEntry*
 * @see SDMODataEntry setODataEntry: setODataEntries: 
 */
- (NSMutableArray*) getODataEntriesByCollection:(NSString*)collectionName_in;
/**
 * Should retrieve all workspaces belonging to the stored SDMODataServiceDocument
 * @remark access via SDMODataServicedocument -> SDMODataSchema -> array<SDMODataWorkspace*>
 * @return array of SDMODataWorkspace* belonging to the stored SDMODataServiceDocument
 * @see SDMODataWorkspace
 */
- (NSArray*) getAllWorkspaces;
/**
 * Should retrieve the workspace based on the provided semantics
 * @param semantic_in the semantic for the Workspace to be retrieved
 * @return array of SDMODataWorkspace* for the given semantic, or nil if none found
 * @see SDMODataWorkspace
 */
- (NSArray*) getWorkspacesBySemantic:(enum TEN_WORKSPACE_SEMANTICS) semantic_in;
/**
 * Should retrieve all collections for a given workspace
 * @param workspace_in the workspace which 'holds' collections
 * @return collections for the given workspace
 * @see SDMODataCollection
 */
- (NSArray*) getCollectionsByWorkspace:(SDMODataWorkspace*) workspace_in;
/**
 * Should retrieve a collection based on it's name
 * @param collectionName_in collection's name to be retrieved
 * @return valid SDMODataCollection* or nil
 * @see SDMODataCollection
 */
- (const SDMODataCollection*) getCollectionByName:(NSString*) collectionName_in;
/**
 * Returns with the unique id of the cache
 * @return uid of the cache
 */
- (NSString*) getUid;

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

/**
 * Enables in-cache filtering using regular expressions
 * @remark supports wildcard based search (* and ?) at the cost of some performance hit 
 */
- (void)setRegexSearchEnabled:(BOOL)flag_in;

#if USE_MAXNUMBER_OF_SEARCH_RESULTS
/**
 * Sets the max number of entries returned by filterEntriesOfCollection: forSearchText:
 */
- (void)setMaxNumberOfSearchResults:(NSNumber*)maxNumber;
#endif


@end