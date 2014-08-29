//
//  MAFCountryCodeStore.h
//  MAFFormatters
//
//  Created by Egresits, David on 10/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * MAFCountryCodeStore component is responsible for retrieving country codes and country names.
 */
@interface MAFCountryCodeStore : NSObject <NSCoding> {
	NSDictionary* m_CountryCodes;
}

@property (nonatomic, retain) NSDictionary* countryCodes;

/**
 * Load default country codes and names from the default plist
 */
- (void) loadCountryCodes ;

/**
 * Get country code for country name
 * @param countryName name of the country
 * @returns code of the county
 */
-(NSString*) countryCodeForCountyName:(NSString*)countryName;
/**
 * Get country name for country code
 * @param countryCode code of the country (2 letters long)
 * @returns name of the country;
 */
-(NSString*) countryNameForCountryCode:(NSString*)countryCode;
/**
 * Get all country name
 * @returns array of country names
 */
-(NSArray*) allCountryNames;
/**
 * Get all country code
 * @returns array of country codes
 */
-(NSArray*) allCountryCodes;

@end
