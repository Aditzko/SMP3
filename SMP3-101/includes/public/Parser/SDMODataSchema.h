//
//  SDMODataSchema.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 04/15/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMODataWorkspace.h"

@class SDMODataCollection;
@class SDMOpenSearchDescription;
/**
 * @deprecated 
 * OData Schema
 */
__attribute((deprecated("Use ODataSchema instead")))
@interface SDMODataSchema : NSObject <NSCoding> {
	NSMutableArray*		m_Workspaces;
}

@property (nonatomic, retain, getter=getWorkspaces, setter=setWorkspaces:) NSMutableArray* workspaces;

-(id) init;

//Public API
#pragma mark -
#pragma mark Public API
/**
 * returns an array of workspaces (SDMODataWorkspace instances) by semantic, if available, returns nil otherwise
 * @see SDMODataWorkspace
 */
-(NSArray*) getWorkspacesBySemantic:(const enum TEN_WORKSPACE_SEMANTICS)workspaceSemantic;

/**
 * returns a collection by name (href)
 */
-(SDMODataCollection*) getCollectionByName:(NSString* const)collectionName;

/**
 * returns a collection by name (href) and its workspace, if required. If not, pass nil.
 */
-(SDMODataCollection*) getCollectionByName:(NSString* const)collectionName workspaceOfCollection:(SDMODataWorkspace**)workspaceOfCollection;

/**
 * Adds an OpenSearchDescription instance to the collection
 */
-(void) setOpenSearchDescriptionForCollection:(NSString* const)collectionName openSearchDescription:(const SDMOpenSearchDescription* const)openSearchDescription;

#pragma mark -
#pragma mark API for the Parser

-(BOOL) addWorkspace:(const SDMODataWorkspace* const)newWorkspace;

@end