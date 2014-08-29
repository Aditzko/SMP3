//
//  ODataParser.h
//  Parser
//
//  Created by Farkas, Zoltan on 04/21/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

/**
 *	Public header -> C-style APIs for parsing
 */

#ifndef SDMCSTYLE_API
#define SDMCSTYLE_API

#ifdef __OBJC__ 

#import <objc/objc.h>
@class NSData;
@class NSMutableArray;
@class ODataServiceDocument;
@class ODataSchema;
@class ODataEntitySchema;
@class ODataError;
@class ODataFunctionImport;
@class OpenSearchDescription;


/*!
 @method
 @abstract Parse Service Document XML.
 @discussion Parses the service document xml and converts it to an Obj-C service document object.
 @result This returns a ODataServiceDocument object.
 @param content_in The content which needs to be parsed.
 */
ODataServiceDocument* parseODataServiceDocumentXML(NSData* const content_in);

/*!
 @method
 @abstract Parse OData Schema XML
 @discussion Parses and matches the schema with the service document and its collections.\n The function returns the same schema pointer as it can already be found in the serviceDocument.
 @result This returns a ODataSchema object.
 @param content_in The content which needs to be parsed.
 @param serviceDocument The ODataServiceDocument object which needs to be parsed.
 */
ODataSchema* parseODataSchemaXML(NSData* const content_in, ODataServiceDocument* const serviceDocument);

/**
 * Parses a feed or entry xml/json and returns an array of parsed entry/entries. 
 * Any "inlined"entries or feed(s) will be parsed when service document is passed to the function. If "inlined" feed(s) or entries 
 * should not be returned pass nil in the service document parameter.
 */
NSMutableArray* parseODataEntriesXML(NSData* const content_in, const ODataEntitySchema* const entitySchema, const ODataServiceDocument* const serviceDocument) __attribute((deprecated("Use parseODataEntries instead")));

NSMutableArray* parseODataEntries(NSData* const content_in, const ODataEntitySchema* const entitySchema, const ODataServiceDocument* const serviceDocument);

/**
 * Parses an OData error payload xml
 * @see ODataError
 */
ODataError* parseODataErrorXML(NSData* const content_in);
	
/**
 * Parses the result payload xml of a function import.
 * @returns Returns an array of entries.
 * @remark Even if the result is not a feed or entry xml, the parser creates an entity schema out of the return type definition, so
 * application developers can access the returned data in a uniform way. The supported return types are:
 * - none
 * - EDMSimpleType		(for example: ReturnType="Edm.Int32"), the generated "entity" schema will be "element" with type Edm.Int32
 * - ComplexType		(for example: ReturnType="NetflixCatalog.Model.BoxArt")
 * - Collection of an EDMSimpleType (for example: ReturnType="Collection(Edm.String)")
 * - Collection of a ComplexType    (for example: ReturnType="Collection(NetflixCatalog.Model.BoxArt)")    
 * - Entry	(for example ReturnType="NetflixCatalog.Model.Title" EntitySet="Titles")
 * - Feed   (for example ReturnType="Collection(NetflixCatalog.Model.Title)" EntitySet="Titles")
 */
NSMutableArray* parseFunctionImportResult(NSData* const content_in, const ODataFunctionImport* const functionImport);
	
/**
 * Parses an XML that contains Open Search Description
 * The parsed data is returned in an OpenSearchDescription typed object.
 */
OpenSearchDescription* parseOpenSearchDescriptionXML(NSData* const content_in);

#endif

#endif