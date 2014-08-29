//
//  ODataPropertyValueBase.h
//  Parser
//
//  Created by Farkas, Zoltan on 04/11/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NSStringConversionExtension.h"
#import "ODataPropertyInfo.h"

/**
 *  Base field value
 */
@interface ODataPropertyValueObject : NSObject {
	NSString*				m_RawValue;
	BOOL					m_ValidationDisabled;
}

@property (nonatomic, retain, getter=getValue, setter=setValue:) NSString* rawValue;
@property (nonatomic, readonly, assign, getter=getEdmType) enum TEN_EDM_TYPES edmType;
@property (nonatomic, readonly, retain, getter=getPropertyInfo) const ODataPropertyInfo* propertyInfo;
@property (nonatomic, assign, getter=isValidationDisabled, setter=setValidationDisabled:) BOOL validationDisabled;

-(id) initWithPropertyInfo:(const ODataPropertyInfo* const)propInfo;
-(id) initWithPropertyInfo:(const ODataPropertyInfo* const)propInfo andValue:(NSString* const)initialValue; 

#pragma mark -
#pragma mark Public API

/**
 * Returns the HTML encoded value of the stored value. Required by the XML serializer.
 */
-(NSString* const) getHTMLEncodedValue;
/**
 * Returns the default value of the given EDM type
 */
-(NSString* const) getDefaultValue;
/**
 * Checks if the object stores a valid value.
 * @remark: When validation is disabled, the return value is always YES!
 */
-(BOOL) isValid;

@end


/**
 * Int field value (Byte, SByte, Int16, Int32, Int64)
 */
@interface ODataPropertyValueInt : ODataPropertyValueObject {
}

-(id) initWithPropertyInfo:(const ODataPropertyInfo* const)propInfo;
-(id) initWithPropertyInfo:(const ODataPropertyInfo* const)propInfo andValue:(NSString* const)initialValue; 

-(NSString* const) getHTMLEncodedValue;
-(void) setValue:(NSString *)newValue;

//access converted value or set the value as converted value>>
-(NSNumber*) getIntValue;
-(void) setIntValue:(NSNumber*)newValue;

@end


/**
 * Complex value
 */
@interface ODataPropertyValueComplex : ODataPropertyValueObject {
	NSMutableDictionary*	m_Children;
}

@property (nonatomic, retain, getter=getChildren, setter=setChildren:) NSMutableDictionary* children;

-(NSString* const) getHTMLEncodedValue;
-(NSString* const) getDefaultValue;
@end

/**
 * String
 */
@interface ODataPropertyValueString : ODataPropertyValueObject {
}
@end


/**
 * DateTime
 */
@interface ODataPropertyValueDateTime : ODataPropertyValueObject {
}

//access converted value or set the value as converted value>>
-(NSDate*) getDateValue;
 -(void) setDateValue:(NSDate*)newValue;

@end

/**
 * Boolean
 */
@interface ODataPropertyValueBoolean : ODataPropertyValueObject {
}

//access converted value or set the value as converted value>>
/**
 * Since OData can define a nullable bool property that means the return type BOOL would not be sufficient.
 * Therefore the function returns a boxed bool value (with values YES/NO) or nil, if the property value is nullable and stores "null".
 */
-(NSNumber*) getBooleanValue;
-(void) setBooleanValue:(NSNumber*)newValue;

@end

/**
 * GUID
 */
@interface ODataPropertyValueGuid : ODataPropertyValueObject {
}
@end

/**
 * Binary
 */
@interface ODataPropertyValueBinary : ODataPropertyValueObject {
}

//access converted value or set the value as converted value>>
/**
 * Decodes the stored base64 string and returns the decoded data (mutable)
 */
-(NSMutableData*) getBinaryData;
/**
 * Base64 encodes the passed data and stores the result as string
 */
-(void) setBinaryData:(NSData*)newValue;

@end

/**
 * Single
 */
@interface ODataPropertyValueSingle : ODataPropertyValueObject {
}

//setValue also accepts: -0, INF, -INF and NaN when validation is on

//access converted value or set the value as converted value>>
/**
 * Since OData can define a nullable single property that means the return type float would not be sufficient.
 * Therefore the function returns a boxed float value or nil, if the property value is nullable and stores "null".
 */
-(NSNumber*) getSingleValue;
-(void) setSingleValue:(NSNumber*)newValue;

@end

/**
 * Double
 */
@interface ODataPropertyValueDouble : ODataPropertyValueObject {
}

//setValue also accepts: -0, INF, -INF and NaN when validation is on

//access converted value or set the value as converted value>>
/**
 * Since OData can define a nullable double property that means the return type double would not be sufficient.
 * Therefore the function returns a boxed double value or nil, if the property value is nullable and stores "null".
 */
-(NSNumber*) getDoubleValue;
-(void) setDoubleValue:(NSNumber*)newValue;

@end

/**
 * Decimal
 * See the following for more details on certain limitations: http://social.msdn.microsoft.com/Forums/en/adodotnetdataservices/thread/832edcc7-d6ef-4551-bc81-98efb15d9ac0
 * XMLSCHEME2: http://www.w3.org/TR/2001/REC-xmlschema-2-20010502/#decimal
 * The Library limitations since it uses NSDecimalNumber:
 *      An instance can represent any number that can be expressed as mantissa x 10^exponent where mantissa is a decimal integer up to 38 digits long, 
 *      and exponent is an integer from –128 through 127.
 * That means Precision and Scale attributes are limited to 38. That is because Precision is defined as:
 * "a positive integer that specifies the maximum number of decimal digits that an instance of the decimal type can have, 
 * <b>both to the left and to the right</b> of the decimal point.
 */
@interface ODataPropertyValueDecimal : ODataPropertyValueObject {
}

-(NSDecimalNumber*) getDecimalValue;
-(void) setDecimalValue:(NSDecimalNumber*)newValue;

@end



/**
 * Duration, Edm.Time ([+/-]P[nYnMnD][T[nH][nM][x.yS]])
 */

/**
 * Duration flags, can be combined
 */
enum TEN_DURATION_FLAGS {
	DURATION_FLAG_YEARS_PRESENT		= 0x0001, ///< if set, years should be interpreted and the m_Years variable contains valid data
	DURATION_FLAG_MONTHS_PRESENT	= 0x0002,
	DURATION_FLAG_DAYS_PRESENT		= 0x0004,
	DURATION_FLAG_HOURS_PRESENT		= 0x0008,
	DURATION_FLAG_MINUTES_PRESENT	= 0x0010,
	DURATION_FLAG_SECONDS_PRESENT	= 0x0020, ///< if set, seconds should be interpreted and the m_Seconds variable contains valid data
	DURATION_FLAG_NEGATIVE			= 0x0040  ///< if set, that means the duration is a negative duration
};

/**
 * Duration data class
 */
@interface ODataDuration : NSObject {
	uint32_t	m_Years, m_Months, m_Days;
	uint32_t	m_Hours, m_Minutes;
	double		m_Seconds;
	uint8_t		m_Flags;
}

/**
 * Assigning a value to any of the following properties (years, months, days, hours, minutes, seconds) will 
 * adjust the fields mask appropriately.
 */
@property (nonatomic, assign, getter=getYears,	 setter=setYears:) uint32_t years;
@property (nonatomic, assign, getter=getMonths,  setter=setMonths:) uint32_t months;
@property (nonatomic, assign, getter=getDays,	 setter=setDays:) uint32_t days;
@property (nonatomic, assign, getter=getHours,	 setter=setHours:) uint32_t hours;
@property (nonatomic, assign, getter=getMinutes, setter=setMinutes:) uint32_t minutes;
@property (nonatomic, assign, getter=getSeconds, setter=setSeconds:) double seconds;
/**
 * Use setFieldMask to override the automatic behavior of determining the available fields for serialization
 * For example, if the required output is PT00H12M then use DURATION_FLAG_HOURS_PRESENT | DURATION_FLAG_MINUTES_PRESENT for parameters
 */
@property (nonatomic, assign, getter=getFieldMask, setter=setFieldMask:) uint8_t mask;

-(id) init;
-(BOOL) isNegative;
-(BOOL) isYearsFieldPresent;
-(BOOL) isMonthsFieldPresent;
-(BOOL) isDaysFieldPresent;
-(BOOL) isHoursFieldPresent;
-(BOOL) isMinutesFieldPresent;
-(BOOL) isSecondsFieldPresent;
/**
 * Sets the duration sign. If YES is passed the duration will be a negative duration, otherwise positive. 
 */
-(void) setSign:(const BOOL)negativeDuration;

@end

/**
 * Edm.Time
 */
@interface ODataPropertyValueTime : ODataPropertyValueObject {
}

/**
 * Gets the time duration value
 */
-(ODataDuration*) getTimeValue;
/**
 * Sets the time duration value using ODataDuration
 */
-(void) setTimeValue:(const ODataDuration*)newValue;

@end

/**
 * Edm.DateTimeOffset
 */
@interface ODataPropertyValueDateTimeOffset : ODataPropertyValueDateTime {
}

@end


