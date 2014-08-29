//
//  ODataMetaDocumentParser.h
//  Parser
//
//  Created by Farkas, Zoltan on 04/21/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ODataGenericParser.h"

@class ODataServiceDocument;

/**
 *	Parses and matches the schema with the service document and its collections. 
 *  The parser creates the schema of the input service document's collections.
 * <code>
 * @try {
 *     ODataMetaDocumentParser* metaDocParser = [[[ODataMetaDocumentParser alloc] initWithServiceDocument: serviceDocument] autorelease];
 *     [metaDocParser parse: content_in];
 * } @catch(ODataParserException* e) {
 *     //error handling code...
 * }
 * </code>
 */
@interface ODataMetaDocumentParser : ODataGenericParser {
}

@property (nonatomic, retain, readonly, getter=getServiceDocument) ODataServiceDocument* serviceDocument;

-(id) initWithServiceDocument:(ODataServiceDocument* const)newServiceDocument;

@end
