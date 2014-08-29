//
//  SDMODataCollection.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 04/15/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMODataEntitySchema.h"

@class SDMODataIconInfo;
@class SDMODataLink;
@class SDMOpenSearchDescription;

//OData4SAP specification v1.02, page 36>>
enum TEN_COLLECTION_SEMANTICS {
	COLLECTION_SEMANTIC_NONE			= 0,
	COLLECTION_SEMANTIC_SUBSCRIPTIONS	= 1,
	COLLECTION_SEMANTIC_NOTIFICATIONS	= 2,
	COLLECTION_SEMANTIC_USERS			= 3, //OData4SAP spec. v1.04, page 43
	COLLECTION_SEMANTIC_UNKNOWN			= 1000
};


//Collection flags (can be combined)>>
enum TEN_COLLECTION_FLAGS {
	COLLECTION_FLAG_CREATABLE			= 0x01,	///< @see isCreatable
	COLLECTION_FLAG_UPDATABLE			= 0x02, ///< @see isUpdatable
	COLLECTION_FLAG_DELETABLE			= 0x04, ///< @see isDeletable
	COLLECTION_FLAG_REQUIRES_FILTER		= 0x08, ///< @see doesRequireFilter
	COLLECTION_FLAG_TOP_LEVEL			= 0x10, ///< @see isTopLevel
	COLLECTION_FLAG_SEARCHABLE			= 0x20, ///< @see isSearchable
	COLLECTION_FLAG_HAS_MEDIA			= 0x40  ///< @see hasMedia
};




/**
 * @deprecated 
 * Collection information
 */
__attribute((deprecated("Use ODataCollection instead")))
@interface SDMODataCollection : NSObject <NSCoding> {
	int								m_ContentVersion;		//default 1
	enum TEN_COLLECTION_SEMANTICS	m_Semantic;				//default none
	uint8_t							m_Flags;				//default 0x1 | 0x2 | 0x4 | 0x10 (creatable, updatable, deletable, top-level)
	//
	NSString*						m_Title;				//plural form
	NSString*						m_MemberTitle;			//singular form of title
	NSMutableArray*					m_Icons;				//0..n icons (for different sizes), nil, if the collection has no icons
	NSMutableArray*					m_Links;				//0..n links, nil, if the collection has no links
	int								m_DisplayOrder;			//if the collection is a top level collection then this is the relative display order 
															//to other top level collections. Top level collections should be ordered and displayed
															//by DisplayOrder
	SDMODataEntitySchema*			m_EntitySchema;			//schema of the collection
	const SDMOpenSearchDescription*	m_OpenSearchDescription;//if present, points to an open search description document
}

@property (nonatomic, assign, getter=getContentVersion, setter=setContentVersion:) int contentVersion;
@property (nonatomic, assign, getter=getSemantic, setter=setSemantic:) enum TEN_COLLECTION_SEMANTICS semantic;
@property (nonatomic, assign, getter=getFlags, setter=setFlags:) uint8_t flags;
@property (nonatomic, readonly, retain, getter=getName) NSString* name;	///< href
@property (nonatomic, retain, getter=getTitle, setter=setTitle:) NSString* title;
@property (nonatomic, retain, getter=getMemberTitle, setter=setMemberTitle:) NSString* memberTitle;
@property (nonatomic, retain, getter=getIcons, setter=setIcons:) NSMutableArray* icons;
@property (nonatomic, retain, getter=getLinks, setter=setLinks:) NSMutableArray* links;
@property (nonatomic, assign, getter=getDisplayOrder, setter=setDisplayOrder:) int displayOrder;
@property (nonatomic, retain, getter=getEntitySchema, setter=setEntitySchema:) SDMODataEntitySchema* entitySchema;
@property (nonatomic, retain, getter=getOpenSearchDescription, setter=setOpenSearchDescription:) const SDMOpenSearchDescription* openSearchDescription;

-(id) initWithName:(NSString* const)newName;

#pragma mark -
#pragma mark Public APIs

/**
 * Queries if a acollection allows creating new entries or not.
 */
-(BOOL) isCreatable;
/**
 * Queries if a collection allows updating its entries.
 */
-(BOOL) isUpdatable;
/**
 * Queries if a collection allows deleting its entries.
 */
-(BOOL) isDeletable;
/**
 * Queries if a collection should appear on the main screen as a starting/root collection.
 */
-(BOOL) isTopLevel;
/**
 * If the return value is not NO, that means the entries of the collection cannot be queried without providing
 * a $filter expression (if accessed without a $filter expression, the server responds with an error message.)
 */
-(BOOL) doesRequireFilter;
/**
 * Checks if the collection supports google-like search, where a search term is matched against several or all properties of each entry.
 */
-(BOOL) isSearchable;
/**
 * Queries if a collection has media links or not.
 */
-(BOOL) hasMedia;

/**
 * if the collection supports subscription, then the returned object will be an SDMODataLink, otherwise nil.
 */
-(SDMODataLink*) getSubscriptionLink;

//For the parser only>>
#pragma mark -
#pragma mark Parser APIs

-(BOOL) addLink:(const SDMODataLink* const)newLink;
-(BOOL) addIcon:(const SDMODataIconInfo* const)newIcon;
@end
