//
//  ODataSchema.h
//  Parser
//
//  Created by Farkas, Zoltan on 04/15/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ODataWorkspace.h"

@class ODataCollection;
@class OpenSearchDescription;
/**
 * OData Schema
 */
@interface ODataSchema : NSObject <NSCoding> {
	NSMutableArray*		m_Workspaces;
}

@property (nonatomic, retain, getter=getWorkspaces, setter=setWorkspaces:) NSMutableArray* workspaces;

-(id) init;

//Public API
#pragma mark -
#pragma mark Public API
/**
 * returns an array of workspaces (ODataWorkspace instances) by semantic, if available, returns nil otherwise
 * @see ODataWorkspace
 */
-(NSArray*) getWorkspacesBySemantic:(const enum TEN_WORKSPACE_SEMANTICS)workspaceSemantic;

/**
 * returns a collection by name (href)
 */
-(ODataCollection*) getCollectionByName:(NSString* const)collectionName;

/**
 * returns a collection by name (href) and its workspace, if required. If not, pass nil.
 */
-(ODataCollection*) getCollectionByName:(NSString* const)collectionName workspaceOfCollection:(ODataWorkspace**)workspaceOfCollection;

/**
 * Adds an OpenSearchDescription instance to the collection
 */
-(void) setOpenSearchDescriptionForCollection:(NSString* const)collectionName openSearchDescription:(const OpenSearchDescription* const)openSearchDescription;

#pragma mark -
#pragma mark API for the Parser

-(BOOL) addWorkspace:(const ODataWorkspace* const)newWorkspace;

@end