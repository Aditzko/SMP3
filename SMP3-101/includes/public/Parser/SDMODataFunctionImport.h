//
//  SDMODataFunctionImport.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 05/04/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SDMODataPropertyInfo;
@class SDMODataEntitySchema;

/**
 * Supported parameter modes
 */

enum TEN_FUNCTION_IMPORT_PARAMETER_MODES {
	FUNCTION_IMPORT_PARAMETER_MODE_IN		= 0x01,
	FUNCTION_IMPORT_PARAMETER_MODE_OUT		= 0x02,
	FUNCTION_IMPORT_PARAMETER_MODE_INOUT	= FUNCTION_IMPORT_PARAMETER_MODE_IN | FUNCTION_IMPORT_PARAMETER_MODE_OUT
};


/**
 * @deprecated 
 * OData Function Import Parameter class
 */
__attribute((deprecated("Use ODataFunctionImportParameter instead")))
@interface SDMODataFunctionImportParameter : NSObject<NSCoding> {
	const SDMODataPropertyInfo*					m_MetaInfo;
	enum TEN_FUNCTION_IMPORT_PARAMETER_MODES	m_Mode;
}

@property (nonatomic, readonly, retain, getter=getMetaInfo) const SDMODataPropertyInfo* metaInfo;
@property (nonatomic, assign, getter=getMode, setter=setMode:) enum TEN_FUNCTION_IMPORT_PARAMETER_MODES mode;

-(id) initWithMetaInfo:(const SDMODataPropertyInfo*)newMetaInfo;

@end


/**
 * OData Function Import flags
 */

enum TEN_FUNCTION_IMPORT_FLAGS {
	FUNCTION_IMPORT_FLAG_NONE				= 0x00,
	FUNCTION_IMPORT_FLAG_RETURNS_COLLECTION	= 0x01, ///< set when the result is a collection
	FUNCTION_IMPORT_FLAG_SIMPLE_TYPE		= 0x02, ///< set when the schema of the returned data is a simple type, or collection of simple types
	FUNCTION_IMPORT_FLAG_ENTITY_SET			= 0x04  ///< set when the schema of the returned data is an entity set! flag SIMPLE_TYPE must be unset!
	//When none of the SIMPLE_TYPE and ENTITY_SET flags are set, the result is a complex type or collection of a complex type!
};

/**
 * @deprecated 
 * OData Function Import class
 */
__attribute((deprecated("Use ODataFunctionImport instead")))
@interface SDMODataFunctionImport : NSObject<NSCoding> {
	NSString*				m_HttpMethod;
	NSMutableDictionary*	m_Parameters;
	SDMODataEntitySchema*	m_ReturnTypeSchema;	///< schema of the return type.
	uint8_t					m_Flags;
	//SAP attributes
	NSString*				m_ActionFor;		///< the entity type name the function import refers to
}

@property (nonatomic, readonly, retain, getter=getName) NSString* name;
@property (nonatomic, retain, getter=getHttpMethod, setter=setHttpMethod:) NSString* httpMethod;  ///< Gets/sets the http method that must be used when sending the request to the server to execute the backend functionality.
@property (nonatomic, retain, getter=getParameters, setter=setParameters:) NSMutableDictionary* parameters;
@property (nonatomic, retain, getter=getReturnTypeSchema, setter=setReturnTypeSchema:) SDMODataEntitySchema* returnTypeSchema;
@property (nonatomic, assign, getter=getFlags, setter=setFlags:) uint8_t flags;
@property (nonatomic, retain, getter=getActionFor, setter=setActionFor:) NSString* actionFor; ///< Gets/sets the "action-for" SAP extension attribute value (if provided) of the given function import.

/**
 * Creates a function import with the name specified
 */
-(id) initWithName:(NSString* const)newName;

#pragma mark -
#pragma mark Public API

/**
 * Creates a dictionary of property values (SDMODataPropertyValue...) that can be used as function import parameters.
 * Set the rawValue property to the value you would like to send as a parameter when executing a function import.
 * for example, the metadata defines the following parameters for the given function import:
 * <Parameter Name="name" Type="Edm.String" Mode="In"/>
 * <Parameter Name="index" Type="Edm.Int32" Mode="In"/>
 * The method will return an NSMutableDictionary of writable parameters as SDMODataPropertyValue.... The name of the
 * SDMODataPropertyValue... instance will be the name of the parameter.
 */
-(NSMutableDictionary*) getWritableParameters;

/**
 * Generates the URL that is required to execute the backend functionality that is mapped to the function import.
 * The method also generates the parameter part of the Function Import URL. For example:
 * http://www.example.com/demo.svc/FunctionImportName?parameter='value'&numeric_param=123
 */
-(NSString*) generateFunctionImportUrl:(NSString* const)baseUrl parameters:(NSDictionary* const)parameters;

@end


