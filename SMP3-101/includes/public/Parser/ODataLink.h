//
//  ODataLink.h
//  Parser
//
//  Created by Farkas, Zoltan on 04/26/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Link semantics, the values cannot be combined based on OData4SAP specification v1.02, 7.1.7.2 The "sap:semantics" Attribute
 */
enum TEN_LINK_SEMANTICS {
	LINK_SEMANTIC_NONE				= 0, ///< no semantic is defined for the link
	LINK_SEMANTIC_ACTION			= 1, ///< the linked resource is an action
	LINK_SEMANTIC_CALLABLE_ENTITIES = 2, ///< the linked resource is a collection of callable entities
	LINK_SEMANTIC_SUBSCRIPTIONS		= 3	 ///< the linked resource is a collection containing subscription definitions
};

/**
 *	OData Link (base)
 */
@interface ODataLink : NSObject <NSCoding> {
}

@property (nonatomic, readonly, retain, getter=getHRef) NSString* href;
@property (nonatomic, readonly, retain, getter=getRel)	NSString* rel;
@property (nonatomic, readonly, retain, getter=getType) NSString* type;
@property (nonatomic, readonly, retain, getter=getTitle) NSString* title;
@property (nonatomic, readonly, assign, getter=getSemantic) enum TEN_LINK_SEMANTICS semantic;

-(id) initWithHRef:(NSString* const)newHRef;
-(id) initWithHRef:(NSString* const)newHRef andLinkRel:(NSString* const)newRel;
-(id) initWithHRef:(NSString* const)newHRef andLinkRel:(NSString* const)newRel andLinkType:(NSString* const)newType;
-(id) initWithHRef:(NSString* const)newHRef andLinkRel:(NSString* const)newRel andLinkType:(NSString* const)newType andLinkTitle:(NSString* const)newTitle;
-(id) initWithHRef:(NSString* const)newHRef andLinkRel:(NSString* const)newRel andLinkType:(NSString* const)newType andLinkTitle:(NSString* const)newTitle andSemantic:(const enum TEN_LINK_SEMANTICS)newSemantic;

@end


/**
 * OData Related Link
 * When the payload is downloaded from the address stored by the href property, parse the entries with the entity schema that belongs to the
 * collection stored by the targetCollection property of this class!
 */
@interface ODataRelatedLink : ODataLink {
	NSString*	m_TargetCollection;
}

@property (nonatomic, retain, getter=getTargetCollection, setter=setTargetCollection:) NSString* targetCollection;

-(id) initWithHRef:(NSString* const)newHRef andLinkRel:(NSString* const)newRel;
-(id) initWithHRef:(NSString* const)newHRef andLinkRel:(NSString* const)newRel andLinkType:(NSString* const)newType;
-(id) initWithHRef:(NSString* const)newHRef andLinkRel:(NSString* const)newRel andLinkType:(NSString* const)newType andLinkTitle:(NSString* const)newTitle;
-(id) initWithHRef:(NSString* const)newHRef andLinkRel:(NSString* const)newRel andLinkType:(NSString* const)newType andLinkTitle:(NSString* const)newTitle andSemantic:(const enum TEN_LINK_SEMANTICS)newSemantic;

@end

/**
 * OData Media Resource Link
 * Contains the media link resource and the concurrency token (m:etag) if present.
 */
@interface ODataMediaResourceLink : ODataLink {
	NSString*	m_ConcurrencyToken;	//aka m:etag
}

@property (nonatomic, retain, getter=getConcurrencyToken, setter=setConcurrencyToken:) NSString* concurrencyToken;

@end

/**
 * SAP Action Link
 * Contains the optional parameters of the action and helper method to assemble the final URL that is required to execute the action
 */
@interface ODataActionLink : ODataLink {
	NSString*				m_HttpMethod;
	NSMutableDictionary*	m_DefaultParameterValues;
}

@property (nonatomic, retain, getter=getHttpMethod, setter=setHttpMethod:) NSString* httpMethod;
@property (nonatomic, retain, getter=getDefaultParameterValues, setter=setDefaultParameterValues:) NSMutableDictionary* defaultParameterValues; //gets/sets action link default parameter values

/**
 * Gets the action link parameters whose values should be set by the user. 
 * The dictionary contains ODataPropertyValue... instances. The actual type depends on the edm type of the action link parameter.
 * For example, if the type is Edm.String, the parameter is typed as ODataPropertyValueString. Use ODataPropertyValueObject 
 * provides generic, but only string based access to values for reading and writing.
 */
-(NSDictionary*) getParameters;
/**
 * Creates the final action link URL that can be used in an HTTP request to execute the action in the backend.
 * If the action link has parameters, they will be URL encoded and concatenated to the URL. The returned URL is always
 * an absolute URL. Pass nil, if the action link has no parameters. If the "parameters" value is nil, but the action link
 * has parameters the method adds the parameters with their default values to the final URL.
 */
-(NSString*) createActionLinkURL:(NSDictionary*)parameters;

@end

