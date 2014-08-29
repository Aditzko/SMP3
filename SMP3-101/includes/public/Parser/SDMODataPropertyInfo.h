//
//  SDMODataPropertyInfo.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 04/12/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

/**
 * Property declaration and related attributes
 */
#import <Foundation/Foundation.h>
#import "NSStringConversionExtension.h"

/**
 * Possible EDM types of a property. If the type does not specify an Edm core type (that means the property is a complex property), 
 * the stored type will be set to EDM_TYPE_COMPLEX in the SDMODataPropertyInfo instance.
 */
enum TEN_EDM_TYPES {
	EDM_TYPE_BYTE				= INT_TARGET_TYPE_UINT8,
	EDM_TYPE_SBYTE				= INT_TARGET_TYPE_INT8,
	EDM_TYPE_INT16				= INT_TARGET_TYPE_INT16,
	EDM_TYPE_INT32				= INT_TARGET_TYPE_INT32,
	EDM_TYPE_INT64				= INT_TARGET_TYPE_INT64,
	EDM_TYPE_STRING				= 0x10,
	EDM_TYPE_BINARY				= 0x20,
	EDM_TYPE_BOOLEAN			= 0x30,
	EDM_TYPE_TIME				= 0x40,
	EDM_TYPE_DATETIME			= 0x41,
	EDM_TYPE_DATETIMEOFFSET		= 0x42,
	EDM_TYPE_DECIMAL			= 0x50,
	EDM_TYPE_SINGLE				= 0x51,
	EDM_TYPE_DOUBLE				= 0x52,
	EDM_TYPE_GUID				= 0x60,
	EDM_TYPE_COMPLEX			= 0x100,
	EDM_TYPE_USER				= 0x8000,
};

/**
 * Attributes of a proprety that describe for example if a property is a key. 
 * These attributes can be combined, a valid combination for example: PROPERTY_INFO_FLAG_SEARCHABLE | PROPERTY_INFO_FLAG_VISIBLE_IN_LIST
 */
enum TEN_PROPERTY_INFO_FLAGS {
	PROPERTY_INFO_FLAG_NULLABLE				= 0x01,
	PROPERTY_INFO_FLAG_KEY					= 0x02,
	PROPERTY_INFO_FLAG_CREATABLE			= 0x04,
	PROPERTY_INFO_FLAG_UPDATABLE			= 0x08,
	PROPERTY_INFO_FLAG_FILTERABLE			= 0x10,
	PROPERTY_INFO_FLAG_VISIBLE_IN_LIST		= 0x20,		
	PROPERTY_INFO_FLAG_VISIBLE_IN_DETAIL	= 0x40,
	PROPERTY_INFO_FLAG_SEARCHABLE			= 0x80,		//Set, if the property value can be used in search
	PROPERTY_INFO_FLAG_SERVER_GENERATED		= 0x200,	//The server will supply values for this property --> cannot be changed
	PROPERTY_INFO_FLAG_NOT_IN_CONTENT		= 0x400		//FC_KeepInContent="false" --> this bit is set. [ms-odata].pdf, page 172, chapter: 3.2.5.2.1
};

//Semantics according to specification v1.02>>
enum TEN_PROPERTY_SEMANTICS {
	PROPERTY_SEMANTIC_NONE					= 0x0000,	///< no semantics
	PROPERTY_SEMANTIC_TEL					= 0x0001,	///< Telephone number, or cell number or fax number
	PROPERTY_SEMANTIC_EMAIL					= 0x0004,	///< email address
	PROPERTY_SEMANTIC_URL					= 0x0008,	///< web uri, see subtypes
	PROPERTY_SEMANTIC_NAME					= 0x0010,	///< formatted text of the full name or given name, middle name, family name, nick name (see subtype)
	PROPERTY_SEMANTIC_HONORIFIC				= 0x0020,	///< Title of a person (Ph.D., Dr., ...)
	PROPERTY_SEMANTIC_SUFFIX				= 0x0040,	///< Suffix of the name of a person
	PROPERTY_SEMANTIC_NOTE					= 0x0080,	///< Supplemental information or a comment that is associated with the vCard
	PROPERTY_SEMANTIC_PHOTO					= 0x0100,	///< URI of a photo of a person
	PROPERTY_SEMANTIC_ADDRESS				= 0x0200,	///< address, see subtype for more details (city, street, etc)
	PROPERTY_SEMANTIC_ORG					= 0x0400,	///< organization name, org unit, org role
	PROPERTY_SEMANTIC_TITLE					= 0x0800,	///< job title
	PROPERTY_SEMANTIC_BDAY					= 0x1000,	///< birth date
	PROPERTY_SEMANTIC_CALENDAR				= 0x2000,	///< Calendar, see subtype for details
	PROPERTY_SEMANTIC_GEOLOCATION			= 0x4000,	///< geo location, see subtype for details
	PROPERTY_SEMANTIC_USER					= 0x80000000///< user defined semantics
};

//7.1.7.2 The "sap:semantics" Attribute
//Semantics subtypes for tel semantic>>
//these flags can be combined, for example: TEL;TYPE=work,voice,pref,msg:+1-213-555--1234 -->http://tools.ietf.org/html/rfc2426#section-3.3.1
enum TEN_PROPERTY_SEMANTIC_TEL_TYPES {
	PROPERTY_SEMANTIC_TEL_TYPE_NONE			= 0x0000,
	PROPERTY_SEMANTIC_TEL_TYPE_HOME			= 0x0001,
	PROPERTY_SEMANTIC_TEL_TYPE_MSG			= 0x0008,
	PROPERTY_SEMANTIC_TEL_TYPE_WORK			= 0x0002,
	PROPERTY_SEMANTIC_TEL_TYPE_PREF			= 0x0004,
	PROPERTY_SEMANTIC_TEL_TYPE_VOICE		= 0x0010,
	PROPERTY_SEMANTIC_TEL_TYPE_FAX			= 0x0020,
	PROPERTY_SEMANTIC_TEL_TYPE_CELL			= 0x0040,
	PROPERTY_SEMANTIC_TEL_TYPE_VIDEO		= 0x0080,
	PROPERTY_SEMANTIC_TEL_TYPE_PAGER		= 0x0100,
	PROPERTY_SEMANTIC_TEL_TYPE_BBS			= 0x0200,
	PROPERTY_SEMANTIC_TEL_TYPE_MODEM		= 0x0400,
	PROPERTY_SEMANTIC_TEL_TYPE_CAR			= 0x0800,
	PROPERTY_SEMANTIC_TEL_TYPE_ISDN			= 0x1000,
	PROPERTY_SEMANTIC_TEL_TYPE_PCS			= 0x2000
};

//Semantic subtypes for email semantic>>
//these flags can be combined
enum TEN_PROPERTY_SEMANTIC_EMAIL_TYPES {
	PROPERTY_SEMANTIC_EMAIL_TYPE_NONE		= 0x0000,
	PROPERTY_SEMANTIC_EMAIL_TYPE_HOME		= PROPERTY_SEMANTIC_TEL_TYPE_HOME,
	PROPERTY_SEMANTIC_EMAIL_TYPE_WORK		= PROPERTY_SEMANTIC_TEL_TYPE_WORK,
	PROPERTY_SEMANTIC_EMAIL_TYPE_PREF		= PROPERTY_SEMANTIC_TEL_TYPE_PREF
};

//Semantic subtypes for url semantic>>
//these flags can be combined, for example: url;type=work,pref
enum TEN_PROPERTY_SEMANTIC_URL_TYPES {
	PROPERTY_SEMANTIC_URL_TYPE_NONE			= 0x0000,
	PROPERTY_SEMANTIC_URL_TYPE_HOME			= PROPERTY_SEMANTIC_TEL_TYPE_HOME,
	PROPERTY_SEMANTIC_URL_TYPE_WORK			= PROPERTY_SEMANTIC_TEL_TYPE_WORK,
	PROPERTY_SEMANTIC_URL_TYPE_ORG			= 0x0008,
	PROPERTY_SEMANTIC_URL_TYPE_PREF			= PROPERTY_SEMANTIC_TEL_TYPE_PREF,
	PROPERTY_SEMANTIC_URL_TYPE_OTHER		= 0x0010
};

//Semantic subtypes for name semantic>>
//these values CANNOT/MUST NOT BE combined>>
enum TEN_PROPERTY_SEMANTIC_NAME_TYPES {
	PROPERTY_SEMANTIC_NAME_TYPE_GIVENNAME	= 1,
	PROPERTY_SEMANTIC_NAME_TYPE_MIDDLENAME	= 2,
	PROPERTY_SEMANTIC_NAME_TYPE_FAMILYNAME	= 3,
	PROPERTY_SEMANTIC_NAME_TYPE_NICKNAME	= 4
};

//Semantic subtypes for address>>
//these values CANNOT/MUST NOT BE combined now (later on maybe, for example, street,home)>>
enum TEN_PROPERTY_SEMANTIC_ADDRESS_TYPES {
	//these types will never be combined>>
	PROPERTY_SEMANTIC_ADDRESS_TYPE_CITY		= 256,	///< address: city				0x0100
	PROPERTY_SEMANTIC_ADDRESS_TYPE_STREET	= 272,	///< address: street			0x0110
	PROPERTY_SEMANTIC_ADDRESS_TYPE_COUNTRY	= 288,	///< address: country			0x0120
	PROPERTY_SEMANTIC_ADDRESS_TYPE_REGION	= 304,	///< address: state or province	0x0130
	PROPERTY_SEMANTIC_ADDRESS_TYPE_ZIP		= 320,	///< address: postal code		0x0140
	PROPERTY_SEMANTIC_ADDRESS_TYPE_POBOX	= 336,	///< address: pobox				0x0150
	//lower bits are reserved for masks, for example, street,work,pref --> 0x0110 | 0x0002 | 0x0004, currently not enabled
	//PROPERTY_SEMANTIC_ADDRESS_TYPE_FLAG_NONE = 0x0000,
	//PROPERTY_SEMANTIC_ADDRESS_TYPE_FLAG_HOME = 0x0001,
	//PROPERTY_SEMANTIC_ADDRESS_TYPE_FLAG_WORK = 0x0002,
	//PROPERTY_SEMANTIC_ADDRESS_TYPE_FLAG_PREF = 0x0004
};

//Semantic subtypes for org>>
//these values CANNOT/MUST NOT BE combined
enum TEN_PROPERTY_SEMANTIC_ORG_TYPES {
	PROPERTY_SEMANTIC_ORG_TYPE_NAME			= PROPERTY_SEMANTIC_URL_TYPE_ORG,
	PROPERTY_SEMANTIC_ORG_TYPE_ORG_UNIT		= 1,
	PROPERTY_SEMANTIC_ORG_TYPE_ORG_ROLE		= 2
};

//Semantic subtypes for calendar>>
//these values CANNOT/MUST NOT BE combined
enum TEN_PROPERTY_SEMANTIC_CALENDAR_TYPES {
	PROPERTY_SEMANTIC_CALENDAR_TYPE_SUMMARY			= 1,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_DESCRIPTION		= 2,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_CATEGORIES		= 3,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_DTSTART			= 4,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_DTEND			= 5,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_DURATION		= 6,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_DUE				= 7,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_COMPLETED		= 8,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_PRIORITY		= 9,	//0: undefined, 1: highest ... 9: lowest
	PROPERTY_SEMANTIC_CALENDAR_TYPE_CLASS			= 10,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_STATUS			= 11,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_PERCENT_COMPLETE= 12,	//0..100
	PROPERTY_SEMANTIC_CALENDAR_TYPE_CONTACT			= 13,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_LOCATION		= 14,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_TRANSP			= 15,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_FBTYPE			= 16,
	PROPERTY_SEMANTIC_CALENDAR_TYPE_WHOLEDAY		= 17	
};

//Semantic subtypes for geolocation>>
//these values CANNOT/MUST NOT BE combined
enum TEN_PROPERTY_SEMANTIC_GEOLOCATION_TYPES {
	PROPERTY_SEMANTIC_GEOLOCATION_TYPE_LONGITUDE	= 0,
	PROPERTY_SEMANTIC_GEOLOCATION_TYPE_LATITUDE		= 1
};

/**
 * @deprecated
 * Property information
 * list of attributes: 7.1.5 OData Metadata Document + 3.1.9 Properties
 */
__attribute((deprecated("Use ODataPropertyInfo instead")))
@interface SDMODataPropertyInfo : NSObject <NSCoding> {
	//OData property info>>
	NSString*						m_Name;
	enum TEN_EDM_TYPES				m_EdmType;
	int								m_MaxLength;
	uint8_t							m_Scale;		//Valid for Decimal only
	uint8_t							m_Precision;	//Valid for Edm.DateTime, Edm.Time, Edm.DateTimeOffset, Edm.Decimal only
	//OData & SDP Flags>>
	uint16_t						m_Flags;		//key, nullable, creatable, updatable, filterable, 
	//Semantics>>
	enum TEN_PROPERTY_SEMANTICS		m_Semantic;		//for example: TEL
	uint32_t						m_SemanticTypes;//for example:    ;TYPE=work,pref,...
	//Label
	NSString*						m_Label;
	NSString*						m_Description;	//OData4SAP spec v1.02 -> 3.1.9 Properties
	NSString*						m_GroupName;	//group name, nil, if the property is not member of a group, otherwise the group name
	NSString*						m_GroupLabel;	//group label, nil, if the property is not member of a group, otherwise the group label
	//Display orders>>
	int32_t							m_ListDisplayOrder;
	int32_t							m_DetailDisplayOrder;
	//not yet used by SAP --> sap:text-for="field name ref"
	//not yet used by SAP --> sap:unit="field name ref" --> 7.1.7.4
	//Child nodes, if any, in case of no children: nil>>
	NSMutableDictionary*			m_ChildrenByName;
    
    /* Enhancement in 2.1 ESD3 to incorporate non standard attributes */
    NSMutableDictionary*            m_NonStandardProperties; // Properties that are not defined as a standard oData property or a standard oData4SAP property
}

@property (nonatomic, retain, getter=getName, setter=setName:) NSString* name;
@property (nonatomic, assign, getter=getType, setter=setType:) enum TEN_EDM_TYPES type;
@property (nonatomic, assign, getter=getFlags, setter=setFlags:) uint16_t flags;
@property (nonatomic, assign, getter=getMaxLength, setter=setMaxLength:) int maxLength;
@property (nonatomic, assign, getter=getSemantic, setter=setSemantic:) enum TEN_PROPERTY_SEMANTICS semantic;
@property (nonatomic, assign, getter=getSemanticTypes, setter=setSemanticTypes:) uint32_t semanticTypes;
@property (nonatomic, retain, getter=getLabel, setter=setLabel:) NSString* label;
@property (nonatomic, retain, getter=getDescription, setter=setDescription:) NSString* description;
@property (nonatomic, retain, getter=getGroupName, setter=setGroupName:) NSString* groupName;
@property (nonatomic, retain, getter=getGroupLabel, setter=setGroupLabel:) NSString* groupLabel;
@property (nonatomic, assign, getter=getListDisplayOrder, setter=setListDisplayOrder:) int32_t listDisplayOrder;
@property (nonatomic, assign, getter=getDetailDisplayOrder, setter=setDetailDisplayOrder:) int32_t detailDisplayOrder;
@property (nonatomic, assign, getter=getScale, setter=setScale:) uint8_t scale;
@property (nonatomic, assign, getter=getPrecision, setter=setPrecision:) uint8_t precision;
@property (nonatomic, retain, getter=getChildren, setter=setChildren:) NSMutableDictionary* children;

/* Enhancement in 2.1 ESD3 to incorporate non standard attributes */
@property (nonatomic, retain, getter=getNonStandardProps, setter=setNonStandardProps:) NSMutableDictionary* nonStandardProperties;

-(id) initWithName:(NSString* const)propName andPropEdmType:(const enum TEN_EDM_TYPES)propEdmType;

//Public API
#pragma mark -
#pragma mark Public API
-(BOOL) isNullable;
-(BOOL) isKey;
-(BOOL) isCreatable;
-(BOOL) isUpdatable;
-(BOOL) isFilterable;
-(BOOL) isVisibleInList;
-(BOOL) isVisibleInDetail;
-(BOOL) isSearchable;
-(BOOL) isServerGenerated;
/**
 * Returns a pointer to a writable property info by path
 * example path: @"items\\description\\lang_code"
 */
-(SDMODataPropertyInfo* const) getPropertyInfoByPath:(NSString* const)path;

#pragma mark -
#pragma mark Private API
//Adds child property info objects>>
-(void) addChildPropertyInfo:(const SDMODataPropertyInfo* const)child;

@end
