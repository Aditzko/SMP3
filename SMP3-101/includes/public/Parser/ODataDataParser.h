//
//  ODataDataParser.h
//  Parser
//
//  Created by Farkas, Zoltan on 04/21/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ODataGenericParser.h"

@class ODataEntitySchema;
@class ODataServiceDocument;
@class ODataFeed;

/**
 * Parses a feed or an entry xml.
 * The array of parsed entry/entries can be accessed via the "entries" property of the parser after parsing. 
 * Any "inlined"entries or feed(s) will be parsed when service document is passed to the "initWithEntitySchema" variant that accepts service
 * document as input. If "inlined" feed(s) or entries should not be returned pass nil as the service document parameter or use the other
 * "initWithEntitySchema" that does not have a service document parameter.
 * <code>
 * NSMutableArray* entries = nil;
 * @try {
 *     ODataDataParser* dataParser = [[[ODataDataParser alloc] initWithEntitySchema: entitySchema andServiceDocument: serviceDocument] autorelease];
 *     [dataParser parse: content_in];
 *     entries = [dataParser.entries retain];
 * @catch (ODataParserException* e) {
 *     //error handling...
 * }
 * </code>
 */
@interface ODataDataParser : ODataGenericParser {
}

@property (nonatomic, retain, readonly, getter=getEntitySchema) const ODataEntitySchema* entitySchema;
@property (nonatomic, retain, readonly, getter=getEntries) NSMutableArray* entries;
@property (nonatomic, retain, readonly, getter=getFeed) ODataFeed* feed;

-(id) initWithEntitySchema:(const ODataEntitySchema* const)newEntitySchema;
-(id) initWithEntitySchema:(const ODataEntitySchema* const)newEntitySchema andServiceDocument:(const ODataServiceDocument* const)newServiceDocument;
-(void) parse:(NSData* const)content;


@end
