//
//  SDMODataEntitySchema.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 04/15/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMODataProperty.h"

/**
 * Entity Schema flags
 * The flags can be combined
 */ 
//OData4SAP v1.02, page 38, EntitySet attributes and default values
enum TEN_ENTITY_SCHEMA_FLAGS {
	ENTITY_SCHEMA_FLAG_NONE				= 0x00,
	ENTITY_SCHEMA_FLAG_CREATABLE		= 0x01,
	ENTITY_SCHEMA_FLAG_UPDATABLE		= 0x02,
	ENTITY_SCHEMA_FLAG_DELETABLE		= 0x04,
	ENTITY_SCHEMA_FLAG_SEARCHABLE		= 0x08,
	ENTITY_SCHEMA_FLAG_QUERYABLE		= 0x10,
	ENTITY_SCHEMA_FLAG_REQUIRES_FILTER	= 0x20,
	ENTITY_SCHEMA_FLAG_HAS_MEDIA		= 0x40
};


/**
 * @deprecated
 */
__attribute((deprecated("Use ODataEntitySchema instead")))
@interface SDMODataEntitySchema : NSObject <NSCoding> {
	//entity set names are never prefixed with the schema namespace and are equal to the collection href values! An entity set's type is fully qualified!
	//name should not be stored here, because this class is referenced from SDMODataCollection and that stores the name 
	int						m_ContentVersion;
	uint16_t				m_Flags;
	SDMODataPropertyInfo*	m_Root;
	NSMutableDictionary*	m_NavigationMap;
	NSArray*				m_VisibleInListPaths;   //Persistence: this array is never persisted, it can be rebuilt at runtime on demand!
	NSArray*				m_VisibleInDetailPaths; //Persistence: this array is never persisted, it can be rebuilt at runtime on demand!
}

@property (nonatomic, assign, getter=getContentVersion, setter=setContentVersion:) int contentVersion;
@property (nonatomic, assign, getter=getFlags, setter=setFlags:) uint16_t flags;
@property (nonatomic, retain, getter=getRoot, setter=setRoot:) SDMODataPropertyInfo* root;
@property (nonatomic, retain, getter=getNavigationMap, setter=setNavigationMap:) NSMutableDictionary* navigationMap;

-(id) init;

#pragma mark -
#pragma mark Public API
/**
 * Gets the property paths of those properties that are visible on list screens. 
 * These paths can be used on entry instances to get the property values in visibility order.
 */
-(NSArray* const) getVisibleInListPathsInOrder;
/**
 * Gets the property paths of those properties that are visible on detail screens.
 * These paths can be used on entry instances to get the property values in visibility order.
 */
-(NSArray* const) getVisibleInDetailPathsInOrder;

@end
