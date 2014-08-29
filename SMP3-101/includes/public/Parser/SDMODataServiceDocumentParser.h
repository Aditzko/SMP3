//
//  SDMODataServiceDocumentParser.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 04/20/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMGenericParser.h"

@class SDMODataServiceDocument;


/**
 * @deprecated 
 * Parses the service document xml and converts it to an Obj-C service document object.
 * The service document instance can be accessed via the "serviceDocument" property of the parser after parsing.
 * <code>
 * SDMODataServiceDocument* svcDoc = nil;
 * @try {
 *     SDMODataServiceDocumentParser* svcDocParser = [[[SDMODataServiceDocumentParser alloc] init] autorelease];
 *     [svcDocParser parse: content_in];
 *     svcDoc = [svcDocParser.serviceDocument retain];
 * } @catch(SDMParserException* e) {
 *     //error handling code...
 * }
 * </code>
 */
__attribute((deprecated("Use ODataServiceDocumentParser instead")))
@interface SDMODataServiceDocumentParser : SDMGenericParser {
}

@property (nonatomic, retain, readonly, getter=getServiceDocument) SDMODataServiceDocument* serviceDocument;

-(id) init;

@end
