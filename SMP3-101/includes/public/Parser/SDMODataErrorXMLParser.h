//
//  SDMODataErrorXMLParser.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 05/04/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMGenericParser.h"

@class SDMODataError;


/**
 * @deprecated 
 * Parses an OData error payload and returns an SDMODataError instance with the parsed values.
 * Example error payload:
 * <?xml version="1.0" encoding="utf-8" standalone="yes"?>
 * <error xmlns="http://schemas.microsoft.com/ado/2007/08/dataservices/metadata">
 *    <code></code>
 *    <message xml:lang="en-US">Resource not found for the segment 'Titles'.</message>
 * </error>
 * @see SDMODataError
 */
__attribute((deprecated("Use ODataErrorXMLParser instead")))
@interface SDMODataErrorXMLParser : SDMGenericParser {
}

@property (nonatomic, readonly, retain, getter=getODataError) SDMODataError* odataError;

-(id) init;

@end