//
//  MAFAddressFormatter.h
//  MAFFormatters
//
//  Created by Egresits, David on 9/22/11, based on code by Trottier, Alexandre on 8/5/11.
//  Copyright 2011 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAFFormatting.h"

@class MAFXMLNode;
@class MAFCountryCodeStore;

/*
 * XML element and attribute names
 */
extern NSString* kMAFAFAddressFields;
extern NSString* kMAFAFFormats;
extern NSString* kMAFAFFormat;
extern NSString* kMAFAFLine;
extern NSString* kMAFAFCountry;
extern NSString* kMAFAFId;
extern NSString* kMAFAFLabel;
extern NSString* kMAFAFKeyboard;
extern NSString* kMAFAFWidth;

//File name for the CountryFormats
//extern NSString* sMAFAFCountryFormats;


//
// Address field keys.
//
//#define ADDRESS_FIELD_HOUSE_NO		@"HOUSE_NO"
//#define ADDRESS_FIELD_STREET		@"STREET"
//#define ADDRESS_FIELD_LOCATION		@"LOCATION"		// Street 2
//#define ADDRESS_FIELD_CITY			@"CITY"
//#define ADDRESS_FIELD_REGION		@"REGION"
//#define ADDRESS_FIELD_POSTL_COD1	@"POSTL_COD1"
//#define ADDRESS_FIELD_COUNTRY		@"COUNTRY"

#define MAF_FORMATTER_TEXT_PHONE_EXTENSION_FORMAT		NSLocalizedString(@"%@ Ext. %@",  @"Telephone number and extension")

@interface MAFPhoneNumber : NSObject 
@property (nonatomic, retain) NSString* locale;
@property (nonatomic, retain) NSString* unformattedPhoneNumber;
@property (nonatomic, retain) NSString* localPhoneNumber;
@property (nonatomic, retain) NSString* internationalPhoneNumber;
@property (nonatomic, retain) NSString* internationalPhoneNumberWithCountryOutboundCode;

@end


/**
 * AddressFormatter component is responsible for formatting the addresses and phone numbers to the format specified in the format xml.
 */
@interface MAFAddressFormatter : NSObject {

	MAFXMLNode*					m_RootNode;
	NSMutableDictionary*		m_CountryNodes;
	MAFXMLNode*					m_DefaultCountryNode;
	
	MAFCountryCodeStore* countryCodeStore;
	
	/**
	 * Persistence access mutex object
	 */
	NSRecursiveLock* m_AccessLock;	
	
}

@property (nonatomic, retain) MAFXMLNode* rootNode;
@property (nonatomic, retain) NSMutableDictionary* countryNodes;
@property (nonatomic, retain) MAFXMLNode* defaultCountryNode;
@property (retain) NSRecursiveLock* accessLock;
@property (nonatomic, readonly, getter=getCountryCodeStore) MAFCountryCodeStore* countryCodeStore;

#pragma mark -
#pragma mark Static methods
/**
 * Set the default locale for the MAFAddressFormatter singleton instance
 * @param locale_in the default locale for address formatter
 */
+ (void) setDefaultLocale:(NSString*)locale_in;

/**
 * Get the default locale from the MAFAddressFormatter singleton instance
 * @returns default locale of the singleton instance
 */
+ (NSString*) getDefaultLocale;

/**
 * Get a singleton MAFAddressFormatter instance
 * @returns a singleton MAFAddressFormatter instance
 */
+ (MAFAddressFormatter*) instance;

#pragma mark -
#pragma mark SETTERS
/**
 * Updates the country formats with the specified XML data.
 * @param XMLData the XML data
 * @returns YES if the data was parsed successfully and NO otherwise
 */
- (BOOL)updateCountryFormatsWithXMLData:(NSData *)XMLData;

#pragma mark -
#pragma mark ACCESSORS
/**
 * Returns the node for the specified country code.
 * @param countryCode the country code
 * @returns the node for the specified country code
 */
- (MAFXMLNode *)nodeForCountryCode:(NSString *)countryCode;

#pragma mark -
#pragma mark Address formatter methods
/**
 * Returns the number of rows for the specified country.
 * @param countryCode the country code
 * @returns the number of rows for the specified country
 */
- (NSUInteger)numberOfAddressRowsWithCountryCode:(NSString *)countryCode;

/**
 * Returns the rows for the specified country code. For country codes,
 * see the helper class. For values, see the header file.
 * @param the country code
 * @returns the rows for the specified country code
 * @remark Probably, you doesn't need to call this, because it's automatically stored when you create the instance or set an other locale and used in getAddressRowsWithValues:.
 */
- (NSArray *)addressRowsWithCountryCode:(NSString *)countryCode;

/**
 * Returns with the array of address rows with the specified values
 * @param valuesDict the values that make up the address to be displayed (unspecified values will show the placeholder)
 * @param countyCode_in the country code which we will format for
 * @returns the array of the address rows
 */
- (NSArray*)addressRowsWithValues:(NSDictionary*)valuesDict forCountryCode:(NSString*)countryCode_in;

///**
// * Returns the formatted string of the specified address for the previously setted
// * locale. The returned string will likely contain newline characters.
// * @param values the values that make up the address to be displayed
// * @returns the formatted string of the specified address for the specified country code
// */
//- (NSString *)formattedAddressWithValues:(NSDictionary *)values;

/**
 * Returns the formatted string of the specified address for the specified
 * country code. The returned string will likely contain newline characters.
 * @param values the values that make up the address to be displayed
 * @param countryCode the country code
 * @returns the formatted string of the specified address for the specified country code
 */
- (NSString *)formattedAddressWithCountryCode:(NSString *)countryCode
									   values:(NSDictionary *)values;

#pragma mark -
#pragma mark Phone number formatter methods

/**
 * Returns the formatted string of the specified phone number with the default country code.
 * @param number the phone number, as a string
 * @param extension the extension, as a string
 * @returns the formatted string of the specified phone number with the default country code
 */
//- (NSString *)formattedPhoneNumberWithNumber:(NSString *)number
//								   extension:(NSString *)extension;

/**
 * Returns the formatted string of the specified phone number for the specified
 * country code.
 * @param countryCode the country code
 * @param number the phone number, as a string
 * @param extension the extension, as a string
 * @returns the formatted string of the specified phone number for the specified country code
 */
- (NSString *)formattedPhoneNumberWithCountryCode:(NSString *)countryCode
										   number:(NSString *)number
										extension:(NSString *)extension;


/**
 * Returns the formatted phone numbers of the specified phone number for the specified
 * country code.
 * @param countryCode the country code
 * @param number the phone number, as a string
 * @param extension the extension, as a string
 * @returns the formatted string of the specified phone number for the specified country code
 */
- (MAFPhoneNumber*)formattedLocalAndInternationalPhoneNumbersWithCountryCode:(NSString *)countryCode
										   number:(NSString *)number
										extension:(NSString *)extension;

/**
 * Returns the local trunk prefix (e.g. 0) for the specified country code.
 * @param countryCode the country code
 * @returns the local trunk prefix (e.g. 0) for the specified country code
 */
- (NSString *)localTrunkPrefixWithCountryCode:(NSString *)countryCode;

/**
 * Returns the international dial code (including the + sign) for the specified country code.
 * @param countryCode the country code
 * @returns the international dial code (including the + sign) for the specified country code
 */
- (NSString *)internationalDialCodeWithCountryCode:(NSString *)countryCode;

/**
 * Returns the outbound code for the specified country code.
 * @param countryCode the country code
 * @returns the outbound code for the specified country code
 */
- (NSString*) outboundCodeWithCountryCode:(NSString*)countryCode;

/**
 * Returns the URL for a phone call with the specified number and country code.
 * @param countryCode the country code
 * @param number the phone number, as a string
 * @param extension the extension, if any (a pause will be inserted between the number and the extension)
 * @returns the URL for a phone call with the specified number and country code
 */
- (NSURL *)phoneCallURLWithCountryCode:(NSString *)countryCode
								number:(NSString *)number
							 extension:(NSString *)extension;

/**
 * Returns the localized string for the pattern with key. Key must be in format {key}.
 * @param localizable_in the pattern with the key
 */
- (NSString*) localizeStringWithPattern:(NSString*) localizable_in;


@end
