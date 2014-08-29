//
//  MAFXMLNode.h
//  StreamWork
//
//  Created by Alexandre Trottier on 6/14/10.
//  Copyright 2010 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>


@class MAFXMLNode;

//
// XML node class. This class recursively instantiates its own child nodes
// from an XML string.
//
@interface MAFXMLNode : NSObject <NSXMLParserDelegate, NSCoding> {
@private
	NSString			*m_NodeName;
	MAFXMLNode			*m_ParentNode;
	NSMutableDictionary	*m_Attributes;
	NSMutableArray		*m_ChildNodes;
	NSMutableString		*m_InnerText;	
}

// 
// The node's name.
//
@property (retain) NSString *nodeName;

//
// The parent node instance.
//
@property (assign) MAFXMLNode *parentNode;

//
// The node's attributes.
//
@property (retain) NSMutableDictionary *attributes;

// 
// The array of children nodes.
//
@property (retain) NSMutableArray *childNodes;

// 
// The node's inner text string.
//
@property (retain) NSMutableString *innerText;

//
// Instantiates a node and its children from the specified XMLParser instance.
// @param aNodeName the node's name
// @param anAttributeDictionary the node's attributes
// @param aParentNode the parent node instance
// @param aChildNodesArray an array of children nodes
// @param parser the XMLParser instance
// @returns an autoreleased instance of MAFXMLNode
//
+ (id)nodeWithName:(NSString *)aNodeName
		attributes:(NSDictionary *)anAttributeDictionary
		parentNode:(MAFXMLNode *)aParentNode
		childNodes:(NSArray *)aChildNodesArray
		 XMLParser:(NSXMLParser *)parser;

//
// Initializes the current MAFXMLNode instance wit the specified attributes.
// @param aNodeName the node's name
// @param anAttributeDictionary the node's attributes
// @param aParentNode the parent node instance
// @param aChildNodesArray an array of children nodes
// @param parser the XMLParser instance
// @returns the current MAFXMLNode instance
//
- (id)initWithNodeName:(NSString *)aNodeName
			attributes:(NSDictionary *)anAttributeDictionary
			parentNode:(MAFXMLNode *)aParentNode
			childNodes:(NSArray *)aChildNodesArray
			 XMLParser:(NSXMLParser *)parser;

//
// Adds a dictionary of attributes to this node's attributes.
// @param anAttributeDictionary a dictionary of attributes
//
- (void)addAttributes:(NSDictionary *)anAttributeDictionary;

//
// Adds the specified children nodes to this node's children.
// @param aChildNodesArray an array of MAFXMLNode instances
// 
- (void)addChildren:(NSArray *)aChildNodesArray;

// 
// Adds a single child node to this node's children.
// @param aChildNode a MAFXMLNode instance
//
- (void)addChild:(MAFXMLNode *)aChildNode;

//
// Appends the specified string to this node's inner text.
// @param string the node's inner text
//
- (void)appendInnerText:(NSString *)string;

//
// Returns YES if this node has children nodes and NO otherwise.
// @returns YES if this node has children nodes and NO otherwise
//
- (BOOL)hasChildren;

//
// Returns the value of the attribute with the specified name.
// @param aName the name of the attribute to be returned
// @returns the value of the attribute with the specified name
//
- (NSString *)attributeForName:(NSString *)aName;

//
// Recursively searches the node tree starting with this instance
// and returns the first child matching the specified node name.
// @param aNodeName the node name to be matched
// @returns the first child node matching the specified name
//
- (MAFXMLNode *)findChildWithNodeName:(NSString *)aNodeName;

//
// Recursively searches the node tree starting with this instance
// and returns the first child matching the specified node name and containing
// an attribute with the specified name.
// @param aNodeName the node name to be matched
// @param anAttributeName the name of the attribute that must be contained
// @returns the first child node matching the specified name and attribute name
//
- (MAFXMLNode *)findChildWithNodeName:(NSString *)aNodeName
					   attributeName:(NSString *)anAttributeName;

//
// Recursively searches the node tree starting with this instance
// and returns the first child matching the specified node name and containing
// an attribute with the specified name and value.
// @param aNodeName the node name to be matched
// @param anAttributeName the name of the attribute that must be contained
// @param anAttributeValue the value of the attribute that must be contained
// @returns the first child node matching the specified name and attribute name and value
//
- (MAFXMLNode *)findChildWithNodeName:(NSString *)aNodeName
					   attributeName:(NSString *)anAttributeName
					  attributeValue:(NSString *)anAttributeValue;

//
// Returns the XML representation of this node and its children.
// @returns the XML representation of this node and its children
//
- (NSString *)XMLString;

//
// Returns the XML representation of this node and its children as a data object.
// @returns the XML representation of this node and its children as a data object
//
- (NSData *)XMLData;

@end
