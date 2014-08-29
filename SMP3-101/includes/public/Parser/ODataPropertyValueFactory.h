//
//  ODataPropertyValueFactory.h
//  Parser
//
//  Created by Farkas, Zoltan on 04/14/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ODataPropertyValues.h"
#import "ODataPropertyInfo.h"

enum TEN_VALUE_FACTORY_FLAGS {
	VALUE_FACTORY_FLAG_NONE				= 0x0000,
	VALUE_FACTORY_FLAG_NO_VALIDATION	= 0x0001,
	VALUE_FACTORY_FLAG_CREATE_EMPTY		= 0x0002 | VALUE_FACTORY_FLAG_NO_VALIDATION,
	VALUE_FACTORY_FLAG_NULL_VALUE		= 0x0004
};

typedef ODataPropertyValueObject*(*PFNCUSTOMPROPERTYVALUEFROMPROPERTYINFOWITHVALUE)(const ODataPropertyInfo* const propInfo, NSString* const initialValue, const uint16_t creationFlags);

/**
 * Property value factory
 * Creates the proper property value object instance based on the incoming property info
 */
@interface ODataPropertyValueFactory : NSObject {
}

/**
 * Creates a property value from its metadata
 * if initial value is nil, the initWith... method of the PropertyValuexxx object will set the default value of the object!
 * the 4th parameter can be NULL, if no custom types/custom semantics are used
 */
+(ODataPropertyValueObject*) createPropertyValueFromPropertyInfoWithValue:(const ODataPropertyInfo* const)propInfo 
																initialValue:(NSString* const)initialValue
															   creationFlags:(const uint16_t)creationFlags
													   customFactoryFunction:(PFNCUSTOMPROPERTYVALUEFROMPROPERTYINFOWITHVALUE)customFactoryFunction;

@end