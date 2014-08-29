//
//  ODataServiceDocument.h
//  Parser
//
//  Created by Farkas, Zoltan on 04/20/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ODataSchema.h"

/**
 * Data model built based on OData XML (Service document and Metadata definition)
 * <pre>
 * SVC
 * - Workspace
 *	- Collection
 *		{			
 *			int								m_ContentVersion;		//default 1
 *			enum TEN_COLLECTION_SEMANTICS	m_Semantic;				//default none
 *			uint8_t							m_Flags;				//default 0x1 | 0x2 | 0x4 | 0x10 (creatable, updatable, deletable, top-level)
 *			NSString*						m_Title;				//plural form
 *			NSString*						m_MemberTitle;			//singular form of title
 *			NSMutableArray*					m_Icons;				//0..n icons (for different sizes), nil, if the collection has no icons
 *			NSMutableArray*					m_Links;				//0..n links, nil, if the collection has no links
 *			int								m_DisplayOrder;			//if the collection is a top level collection then this is the relative display order 
 *																	//to other top level collections. Top level collections should be ordered and displayed
 *																	//by DisplayOrder
 *			ODataEntitySchema*			m_EntitySchema;			//schema of the collection
 *			const OpenSearchDescription*	m_OpenSearchDescription;//if present, points to an open search description document
 *		}
 *		- EntitySet / EntityType
 *			- Property
 *				Edm.type
 *			- ComplexTypes
 * </pre>	
 */
enum TEN_SERVER_TYPES {
	SERVER_TYPE_ODATA	= 0x0,		///< pure OData or non SAP OData server
	SERVER_TYPE_LMS		= 0x1,		///< SAP - LMS server using OData4SAP v0.75+
	SERVER_TYPE_GW		= 0x2		///< SAP - Gateway server using the latest OData4SAP version
};

/**
 * Service Document class
 */
@interface ODataServiceDocument : NSObject <NSCoding> {
	enum TEN_SERVER_TYPES	m_ServerType;
	NSString*				m_DocumentLanguage;
	NSString*				m_BaseUrl;
	ODataSchema*			m_Schema;
	NSMutableDictionary*	m_FunctionImports; //contains the parsed function imports
}

@property (nonatomic, assign, getter=getServerType, setter=setServerType:) enum TEN_SERVER_TYPES serverType;
@property (nonatomic, retain, getter=getDocumentLanguage, setter=setDocumentLanguage:) NSString* documentLanguage;
@property (nonatomic, retain, getter=getBaseUrl, setter=setBaseUrl:) NSString* baseUrl;
@property (nonatomic, retain, getter=getSchema, setter=setSchema:) ODataSchema* schema;
@property (nonatomic, retain, getter=getFunctionImports, setter=setFunctionImports:) NSMutableDictionary* functionImports;

-(id) init;

@end
