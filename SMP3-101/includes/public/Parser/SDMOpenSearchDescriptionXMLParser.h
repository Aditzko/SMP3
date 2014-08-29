//
//  SDMOpenSearchDescriptionXMLParser.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 05/13/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMGenericParser.h"

@class SDMOpenSearchDescription;


/**
 * @deprecated 
 * Parses an OpenSearch description document and creates its ObjC representation that can be accessed via
 * the openSearchDescription property of the class instance after parsing.
 * <code>
 * SDMOpenSearchDescription* osd = nil;
 * @try {
 *     SDMOpenSearchDescriptionXMLParser* osdParser = [[[SDMOpenSearchDescriptionXMLParser alloc] init] autorelease];
 *     [osdParser parse: content_in];
 *     osd = [osdParser.openSearchDescription retain];
 * } @catch (SDMParserException* e) {
 *     //error handling...
 * }
 * </code>
 */
__attribute((deprecated("Use OpenSearchDescriptionXMLParser instead")))
@interface SDMOpenSearchDescriptionXMLParser : SDMGenericParser {
}

@property (nonatomic, readonly, retain, getter=getOpenSearchDescription) SDMOpenSearchDescription* openSearchDescription;

-(id) init;

@end