//
//  SDMFunctionImportResultParser.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 05/04/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMGenericParser.h"

@class SDMODataFunctionImport;

/**
 * @deprecated 
 * Parses the result payload xml of a function import.
 * @remark Even if the result is not a feed or entry xml, the parser creates an entity schema out of the return type definition, so
 * application developers can access the returned data in a uniform way. The supported return types are:
 * - none
 * - EDMSimpleType		(for example: ReturnType="Edm.Int32"), the generated "entity" schema will be "element" with type Edm.Int32
 * - ComplexType		(for example: ReturnType="NetflixCatalog.Model.BoxArt")
 * - Collection of an EDMSimpleType (for example: ReturnType="Collection(Edm.String)")
 * - Collection of a ComplexType    (for example: ReturnType="Collection(NetflixCatalog.Model.BoxArt)")    
 * - Entry	(for example ReturnType="NetflixCatalog.Model.Title" EntitySet="Titles")
 * - Feed   (for example ReturnType="Collection(NetflixCatalog.Model.Title)" EntitySet="Titles")
 * The result can accessed via the "entries" property of the parser after parsing.
 * <code>
 * NSMutableArray* fiEntries = nil;
 * @try {
 *     SDMFunctionImportResultParser* fiParser = [[[SDMFunctionImportResultParser alloc] initWithFunctionImport: functionImport] autorelease];
 *     [fiParser parse: content_in];
 *     fiEntries = [fiParser.entries retain];
 * } @catch(SDMParserException* e) {
 *     //error handling code...
 * }
 * </code>
 */
__attribute((deprecated("Use FunctionImportResultParser instead")))
@interface SDMFunctionImportResultParser : SDMGenericParser {
}

@property (nonatomic, retain, readonly, getter=getFunctionImport) const SDMODataFunctionImport* functionImport;
@property (nonatomic, retain, readonly, getter=getEntries) NSMutableArray* entries;

-(id) initWithFunctionImport:(const SDMODataFunctionImport* const)newFunctionImport;

@end