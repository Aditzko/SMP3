//
//  OpenSearchDescriptionXMLParser.h
//  Parser
//
//  Created by Farkas, Zoltan on 05/13/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ODataGenericParser.h"

@class OpenSearchDescription;

/**
 * Parses an OpenSearch description document and creates its ObjC representation that can be accessed via
 * the openSearchDescription property of the class instance after parsing.
 * <code>
 * OpenSearchDescription* osd = nil;
 * @try {
 *     OpenSearchDescriptionXMLParser* osdParser = [[[OpenSearchDescriptionXMLParser alloc] init] autorelease];
 *     [osdParser parse: content_in];
 *     osd = [osdParser.openSearchDescription retain];
 * } @catch (ODataParserException* e) {
 *     //error handling...
 * }
 * </code>
 */

@interface OpenSearchDescriptionXMLParser : ODataGenericParser {
}

@property (nonatomic, readonly, retain, getter=getOpenSearchDescription) OpenSearchDescription* openSearchDescription;

-(id) init;

@end