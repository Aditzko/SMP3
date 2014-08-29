//
//  SDMGenericParser.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 04/20/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMParserDelegate.h"
#import "SDMParserException.h"


/**
 * @deprecated
 */
__attribute((deprecated("Use ODataGenericParser instead")))
@interface SDMGenericParser : NSObject<NSXMLParserDelegate, SDMParserDelegate> {
	NSMutableString*	m_Path;
	int					m_Level;
	NSMutableString*	m_LastValue;
	BOOL				m_HasBufferedValue;
	NSXMLParser*		m_Parser;
	SDMParserException*		m_Exception;
	NSDictionary*		m_AttributesOfLastElement;
}

@property (nonatomic, retain, getter=getPath, setter=setPath:) NSMutableString* path;
@property (nonatomic, assign, getter=getLevel, setter=setLevel:) int level;
@property (nonatomic, retain, getter=getLastValue, setter=setLastValue:) NSMutableString* lastValue;
@property (nonatomic, assign, getter=hasBufferedValue, setter=setHasBufferedValue:) BOOL hasBufferedValue;
@property (nonatomic, assign, getter=getParser, setter=setParser:) NSXMLParser* parser; //Must be assign and not retain! cross-reference!
// removed for status codes @property (nonatomic, retain, getter=getException, setter=setException:) NSException* exception;
@property (nonatomic, retain, getter=getException, setter=setException:) SDMParserException* exception;
@property (nonatomic, assign, readonly, getter=getFoundPrefix) BOOL foundPrefix;
@property (nonatomic, retain, readonly, getter=getPrefix) NSString* prefix;
@property (nonatomic, retain, getter=getAttributesOfLastElement, setter=setAttributesOfLastElement:) NSDictionary* attributesOfLastElement;

-(id) init;

#pragma mark -
#pragma mark Public API

/**
  * Parses the passed data as XML
  */
-(void) parse:(NSData* const)content;

/**
  * Parses the data that will be downloaded from the passed URL as XML
  */
-(void) parseContentsOfURL:(NSURL* const)url;

#pragma mark -
#pragma mark Private API
-(void) parserDidStartDocument:(NSXMLParser*)parser;
-(void) parserDidEndDocument:(NSXMLParser*)parser;
-(void) parser:(NSXMLParser*)parser didStartElement:(NSString*)elementName namespaceURI:(NSString*)namespaceURI qualifiedName:(NSString*)qualifiedName attributes:(NSDictionary*)attributeDict;
-(void) parser:(NSXMLParser*)parser didEndElement:(NSString*)elementName namespaceURI:(NSString*)namespaceURI qualifiedName:(NSString*)qName;
-(void) parser:(NSXMLParser*)parser foundCharacters:(NSString*)string;

//API for the specific parsers>>
-(void) setDoProcessPrefixes:(BOOL)processPrefixes;
-(void) abortParsing;
//Redefine only these methods in the specific parser>>
-(void) startDocument;
-(void) endDocument;
-(void) startElement:(NSString* const)elementName namespaceURI:(NSString* const)namespaceURI attributes:(NSDictionary* const)attributes;
-(void) endElement:(NSString* const)elementName namespaceURI:(NSString* const)namespaceURI;
-(void) characters:(NSString* const)string;
@end
