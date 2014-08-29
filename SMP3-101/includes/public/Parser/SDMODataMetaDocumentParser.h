//
//  SDMODataMetaDocumentParser.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 04/21/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMGenericParser.h"

@class SDMODataServiceDocument;

/**
 * @deprecated 
 *	Parses and matches the schema with the service document and its collections. 
 *  The parser creates the schema of the input service document's collections.
 * <code>
 * @try {
 *     SDMODataMetaDocumentParser* metaDocParser = [[[SDMODataMetaDocumentParser alloc] initWithServiceDocument: serviceDocument] autorelease];
 *     [metaDocParser parse: content_in];
 * } @catch(SDMParserException* e) {
 *     //error handling code...
 * }
 * </code>
 */
__attribute((deprecated("Use ODataMetaDocumentParser instead")))
@interface SDMODataMetaDocumentParser : SDMGenericParser {
}

@property (nonatomic, retain, readonly, getter=getServiceDocument) SDMODataServiceDocument* serviceDocument;

-(id) initWithServiceDocument:(SDMODataServiceDocument* const)newServiceDocument;

@end
