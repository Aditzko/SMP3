//
//  ODataEntry.h
//  Parser
//
//  Created by Farkas, Zoltan on 04/21/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ODataEntitySchema;
@class ODataLink;
@class ODataRelatedLink;
@class ODataIconInfo;
@class ODataPropertyValueObject;
/**
 * Represents one entry in memory
 */
@interface ODataEntry : NSObject<NSCoding> {
	NSString*				m_EntryID;
	NSMutableArray*			m_Links;
	NSMutableArray*			m_Icons;
	NSMutableDictionary*	m_InlinedRelatedEntries;
	NSString*				m_Title;
	NSString*				m_Updated;
	BOOL					m_IsDetailed;
	NSMutableArray*			m_ReadOnlyMediaLinks;
    NSString*               m_Etag;
}

@property (nonatomic, retain, getter=getEntryID, setter=setEntryID:) NSString* entryID;
@property (nonatomic, retain, readonly, getter=getEntitySchema) const ODataEntitySchema* entitySchema;
@property (nonatomic, retain, getter=getLinks, setter=setLinks:) NSMutableArray* links;
@property (nonatomic, retain, getter=getIcons, setter=setIcons:) NSMutableArray* icons;
@property (nonatomic, retain, readonly, getter=getFields) NSMutableDictionary* fields;
/**
 * The structure of the inlineRelatedEntries variable will be as described below. The same structure holds good while building the post body too.
 *
 *{
 *  "RelatedLink(1)" =     [
 *                          "ODataEntry(1)",
 *                          "ODataEntry(2)",
 *                          "ODataEntry(3)"
 *                          ]
 *  "RelatedLink(2)" =     [
 *                          "ODataEntry(4)",
 *                          "ODataEntry(5)",
 *                          "ODataEntry(6)"
 *                          ]
 *}
 */
@property (nonatomic, retain, getter=getInlinedRelatedEntries, setter=setInlinedRelatedEntries:) NSMutableDictionary* inlinedRelatedEntries;
@property (nonatomic, retain, getter=getTitle, setter=setTitle:) NSString* title;
@property (nonatomic, assign, getter=getIsDetailed, setter=setIsDetailed:) BOOL isDetailed;
@property (nonatomic, retain, getter=getReadOnlyMediaLinks, setter=setReadOnlyMediaLinks:) NSMutableArray* readOnlyMediaLinks;
@property (nonatomic, retain, getter=getUpdatedString, setter=setUpdatedString:) NSString* updatedString; //for the data parser and persistency only
@property (nonatomic, retain, getter=getEtag, setter=setEtag:) NSString* etag;

// Enhancements in SMP 3.0
@property (nonatomic, assign, getter = getEntryStateInCache, setter = setEntryStateInCache:) int cacheState;
@property (nonatomic, assign, getter = isLocalEntryInCache, setter = setIsLocalEntryInCache:) BOOL isLocalEntry;
@property (nonatomic, retain, getter = getTimeStampInCache, setter = setTimeStampInCache:) NSDate* timeStamp;
@property (nonatomic, retain) NSString* collectionId;


-(id) initWithEntitySchema:(const ODataEntitySchema* const)newEntitySchema;

#pragma mark -
#pragma mark Public API
/**
  * Returns a pointer to a writable property value object by path>> example: items\\description\\lang_code
  */
-(ODataPropertyValueObject* const) getPropertyValueByPath:(NSString* const)path;

/**
  * Returns an array of ODataRelatedLink objects. The links are absolute links and the targetCollection property of the
  * ODataRelatedLink class defines the name of the collection of the related data. When the data is downloaded, use this
  * collection name to retrieve its entitySchema and pass that schema to the data parser along with the downloaded data.
  */
-(NSArray* const) getRelatedLinks;

/**
 * Returns a related link that matches the given navigation property name or nil, if link is not found
 */
-(const ODataRelatedLink* const) getRelatedLinkByNavigationPropertyName:(NSString* const)navigationPropertyName;

/**
 * Returns an array of ODataActionLink objects. If a collection has no action links the method returns an array with 0 elements.
 * @see ODataActionLink
 */
-(NSArray* const) getActionLinks;

/**
 * Gets an inlined related list of entries for a related link.
 * The related entries are present only if they appear in the original payload as inline.
 */
-(NSArray* const) getInlinedRelatedEntriesForRelatedLink:(NSString* const)relatedUrl;

/**
 * Gets the visible property value objects in lists ordered by the display order attribute value 
 */
-(NSArray* const) getVisibleListPropertiesInOrder;

/**
 * Gets the visible property value objects in details ordered by the display order attribute value 
 */
-(NSArray* const) getVisibleDetailPropertiesInOrder;

/**
 * if the entry supports subscription, then the returned object will be an ODataLink, otherwise nil.
 */
-(ODataLink*) getSubscriptionLink;

/**
 * Returns all the media entry links for editing that are associated with the entry or an empty array, if no media links are available.
 */
-(NSArray*) getMediaLinksForEditing;

/**
 * Returns all the read-only media entry links that are associated with the entry or an empty array, if no media links are available.
 */
-(NSArray*) getMediaLinksForReading;

/**
 * Returns the date when the entry was updated. The return value is nil if the entry has an invalid "updated" value.
 */
-(NSDate*) getUpdated;

/**
 * Checks if all of the stored values are valid
 */
-(BOOL) isValid;

#pragma mark -
#pragma mark API for the Parser
-(void) addLink:(const ODataLink* const)link;
-(void) addIcon:(const ODataIconInfo* const)icon;

@end

