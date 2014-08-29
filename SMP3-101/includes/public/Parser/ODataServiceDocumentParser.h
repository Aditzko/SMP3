//
//  ODataServiceDocumentParser.h
//  Parser
//
//  Created by Farkas, Zoltan on 04/20/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ODataGenericParser.h"

@class ODataServiceDocument;

/**
 * Parses the service document xml and converts it to an Obj-C service document object.
 * The service document instance can be accessed via the "serviceDocument" property of the parser after parsing.
 * <code>
 * ODataServiceDocument* svcDoc = nil;
 * @try {
 *     ODataServiceDocumentParser* svcDocParser = [[[ODataServiceDocumentParser alloc] init] autorelease];
 *     [svcDocParser parse: content_in];
 *     svcDoc = [svcDocParser.serviceDocument retain];
 * } @catch(ODataParserException* e) {
 *     //error handling code...
 * }
 * </code>
 */
@interface ODataServiceDocumentParser : ODataGenericParser {
}

@property (nonatomic, retain, readonly, getter=getServiceDocument) ODataServiceDocument* serviceDocument;

-(id) init;

@end
