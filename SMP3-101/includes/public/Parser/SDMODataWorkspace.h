//
//  SDMODataWorkspace.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 04/20/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SDMODataCollection;

//OData4SAP specification v1.02, page 36>>
enum TEN_WORKSPACE_SEMANTICS {
	WORKSPACE_SEMANTIC_THINGS						= 0,
	WORKSPACE_SEMANTIC_WORKLISTS					= 1,
	WORKSPACE_SEMANTIC_DATA							= 2,
	WORKSPACE_SEMANTIC_SUBSCRIPTIONS_NOTIFICATIONS	= 3,
	WORKSPACE_SEMANTIC_UNKNOWN						= 1000
};

/**
 * @deprecated
 * OData Workspace
 */
__attribute((deprecated("Use ODataWorkspace instead")))
@interface SDMODataWorkspace : NSObject <NSCoding> {
	enum TEN_WORKSPACE_SEMANTICS	m_Semantic;		//for example "things", "data", etc.
	NSString*						m_Title;
	NSMutableDictionary*			m_Collections;	
}

@property (nonatomic, assign, getter=getSemantic, setter=setSemantic:) enum TEN_WORKSPACE_SEMANTICS semantic;
@property (nonatomic, retain, getter=getTitle, setter=setTitle:) NSString* title;
@property (nonatomic, retain, getter=getCollections, setter=setCollections:) NSMutableDictionary* collections;

-(id) init;

//API for the parser only
#pragma mark -
#pragma mark API for the Parser 

-(BOOL) addCollection:(const SDMODataCollection* const)newCollection;

@end
