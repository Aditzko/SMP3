//
//  MAFCurrencyFormatter.h
//  FormatterTests
//
//  Created by Farkas, Zoltan on 10/03/11.
//  Copyright 2011 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAFFormatting.h"


enum TEN_CURRENCY_FORMATTER_FLAGS {
	CURRENCY_FORMATTER_FLAG_NONE			= 0x00,
	CURRENCY_FORMATTER_FLAG_ALLOWS_NULL		= 0x01,
	CURRENCY_FORMATTER_FLAG_SIGNED			= 0x02,
	CURRENCY_FORMATTER_FLAG_MINIMUM			= 0x04, //set when a minimum value is set
	CURRENCY_FORMATTER_FLAG_MAXIMUM			= 0x08  //set when upper limit is set
};

#pragma mark -
#pragma mark MAFCurrencyFormatterSettings

@interface MAFCurrencyFormatterSettings : NSObject<NSCoding> {
	uint8_t				m_Length;					//storage
	uint8_t				m_DecimalPlaces;			//storage
	uint8_t				m_DisplayedDecimalPlaces;	//display
	uint8_t				m_Flags;
	
	NSDecimalNumber*	m_MinimumValue;				//if nil, no lower limit is set
	NSDecimalNumber*	m_MaximumValue;				//if nil, no upper limit is set
}
//comment: if getter is set then the getter can be called from the debugger, otherwise not!
@property (nonatomic, readonly, assign, getter=getLength) uint8_t length;
@property (nonatomic, readonly, assign, getter=getDecimalPlaces) uint8_t decimalPlaces;
@property (nonatomic, readonly, assign, getter=getDisplayedDecimalPlaces) uint8_t displayedDecimalPlaces;
@property (nonatomic, readonly, assign, getter=getFlags) uint8_t flags;

//if nil is set that means no lower limit is defined
@property (nonatomic, retain, getter=getMinimumValue, setter=setMinimumValue:) NSDecimalNumber* minimumValue;
//if nil is set that means no upper limit is defined
@property (nonatomic, retain, getter=getMaximumValue, setter=setMaximumValue:) NSDecimalNumber* maximumValue;


//sets the backend defaults (?), length = 17, 4 decimal places, unsigned value
-(id) init;
-(id) initWithLength:(const uint8_t)newLength andDecimalPlaces:(const uint8_t)newDecimalPlaces;

/*
	If flags are provided, only the NONE, ALLOWS_NULL and SIGNED values will be saved. MINIMUM and MAXIMUM is not set by default.
    The MINIMUM and MAXIMUM flags are set if Minimum and Maximum values are provided via the published properties!
*/
-(id) initWithLength:(const uint8_t)newLength andDecimalPlaces:(const uint8_t)newDecimalPlaces andFlags:(const uint8_t)newFlags;

@end

#pragma mark -
#pragma mark MAFDefaultCurrencySettings

/**
 * MAFDefaultCurrencySettings class stores the formatter settings for the currency codes.
 */
@interface MAFDefaultCurrencySettings : NSObject<NSCoding> {
}

#pragma mark Public API
+(MAFDefaultCurrencySettings*) defaultCurrencySettings;

/**
 * @param isoCurrencyCode the currency code for which the formatter settings will be returned
 */
-(MAFCurrencyFormatterSettings*) getSettingsForISOCurrencyCode:(NSString*)isoCurrencyCode;

/**
 * Adds new settings for a currency code or if the currency code exists, overrides the default settings
 * @param isoCurrencyCode the currency code to set the settings for
 * @param settings the setting to be set
 */
-(BOOL) setSettingsForISOCurrencyCode:(NSString*)isoCurrencyCode settings:(MAFCurrencyFormatterSettings*)settings;

+(void) loadCurrencies;

@end


#pragma mark -
#pragma mark MAFCurrencyFormatter

@interface MAFCurrencyFormatter : NSObject <MAFFormatting> {
	MAFCurrencyFormatterSettings*	m_Settings;
	NSDecimalNumber*				m_Value;
}

@property (nonatomic, readonly, retain, getter=getSettings) MAFCurrencyFormatterSettings* settings;
@property (nonatomic, retain, getter=getValue, setter=setValue:) NSDecimalNumber* value;

//if settings is nil, the formatter creates the settings object with default value
-(id) initWithDecimalNumber:(NSDecimalNumber*)newValue andSettings:(MAFCurrencyFormatterSettings*)newSettings andISOCurrencyCode:(NSString*)isoCurrencyCode;

#pragma mark Public API

-(BOOL) appendDigit:(const uint8_t)digit;
//Trims the rightmost digit
-(BOOL) rtrimDigit;
//clears the value
-(void) clear;

-(BOOL) appendSeparator;
//NO = positive, YES = negative, returns false, if the signed values are not allowed and YES is passed
-(BOOL) setSign:(const BOOL)sign; 

-(BOOL) isNegativeValue;

//Gets formatted value for editing>> (terminating zeros are displayed)
-(NSString*) getFormattedValue;
//Gets formatted value for displaying or editing>>
-(NSString*) getFormattedValue:(const BOOL)returnTerminatingZeroFractionDigits;
@end
