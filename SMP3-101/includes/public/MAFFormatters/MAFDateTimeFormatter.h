//
//  MAFDateTimeFormatter.h
//  MAFCurrencyFormatterProto3
//
//  Created by Nyisztor Karoly on 10/25/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAFFormatting.h"

/**
 * This component can localize dates to several date formats defined in the native NSDateFormatterStyle both in NSDate and NSString format with different locales.
 */
@interface MAFDateTimeFormatter : NSObject <MAFFormatting>

/**
 * Converts an NSDate to UTC format
 * @remark should be used to convert a date to UTC format string for SAP backend compatibility
 * @param date_in date to be converted, might be in any timezone
 * @deprecated in version 1.0 - Use -(NSString *)formatValue:(NSObject*)aValue
 */
+(NSString*) toUTCDateTimeString:(NSDate *)date_in DEPRECATED_ATTRIBUTE;

/**
 * Localizes a Date/Time value based on the provided locale; if locale is nil, the iPhone's locale will be used for the conversion
 * @param date_in date to be formatted
 * @param locale_in the locale which the returned date will have
 * @deprecated in version 1.0 - Use - (NSString *)formatValue:(NSObject*)aValue of MAFFormatting protocol
 */
+(NSString*) toLocalizedDateTimeString:(NSDate *)date_in usingLocale:(NSLocale*)locale_in DEPRECATED_ATTRIBUTE;

/**
 * Returns a user-visible, localized date time string that corresponds to the specified RFC 3339 date time string
 * Should be used to convert from SAP backend DateTime format to user visible, localized format
 * @remarks For details see http://developer.apple.com/library/ios/#qa/qa1480/_index.html and http://www.ietf.org/rfc/rfc3339.txt
 * @param utcDateTimeString the date string in utc time zone which will be formatted
 * @param locale_in the locale for the retrieved/formatted date 
 * @discussion Note that this does not handle all possible RFC 3339 date time strings, just one of the most common styles.
 * @deprecated in version 1.0 - Use - (NSString *)formatValue:(NSObject*)aValue of MAFFormatting protocol
 */
+(NSString *)toLocalizedDateTimeStringFromUTCDateTimeString:(NSString *)utcDateTimeString usingLocale:(NSLocale*)locale_in DEPRECATED_ATTRIBUTE;

/**
 * Returns a user-visible, localized date time string that corresponds to the specified RFC 3339 date time string
 * Should be used to convert from SAP backend DateTime format to user visible, localized format
 * @param utcDateTimeString date string to be formatted for the string required format
 * @remarks For details see http://developer.apple.com/library/ios/#qa/qa1480/_index.html and http://www.ietf.org/rfc/rfc3339.txt 
 * @discussion Note that this does not handle all possible RFC 3339 date time strings, just one of the most common styles.
 * @deprecated in version 1.0 - Use - (NSString *)formatValue:(NSObject*)aValue of MAFFormatting protocol
 */
+ (NSString*) toUTCDateTimeStringFormattedFromUTCDateTimeString:(NSString*)utcDateTimeString DEPRECATED_ATTRIBUTE;

/**
 * Sets a specific Date / Time formating style
 * For possible values and their meanings check out the NSDateFormatterStyle documentation
 * @param dateStyle_in the style for the date part of the formatted date;
 * @param timeStyle_in the style for the time part of the formatted date
 * @remarks Set @param dateStyle_in and/or timeStyle_in to nil to reset to default behaviour - which is 
 * kCFDateFormatterMediumStyle for both the date and the time)
 * @deprecated in version 1.0 - Don't need it. Use the formatterParameters.
 */
+(void) applyDateFormaterStyle:(NSDateFormatterStyle)dateStyle_in andTimeFormatterStyle:(NSDateFormatterStyle)timeStyle_in DEPRECATED_ATTRIBUTE;

/**
 * Sets a specific Date / Time formating style and localizes a Date/Time value based on the provided locale; if locale is nil, the iPhone's locale will be used for the conversion; 
 * Results the same as if 
 * applyDateFormaterStyle:(NSDateFormatterStyle)dateStyle_in andTimeFormatterStyle:(NSDateFormatterStyle)timeStyle_in
 * and
 * toLocalizedDateTimeString:(NSDate *)date_in usingLocale:(NSLocale*)locale_in
 * @param date_in the date to be formatted to localizedformat
 * @param locale_in the locale for which the date has to be formatted
 * @param dateStyle_in the date style which the formatted result will have
 * @param timeStyle_in the time style which the formatted result will have
 * @deprecated in version 1.0 - Use - (NSString *)formatValue:(NSObject*)aValue of MAFFormatting protocol
 */
+(NSString*) toLocalizedDateTimeString:(NSDate *)date_in usingLocale:(NSLocale *)locale_in withDateFormaterStyle:(NSDateFormatterStyle)dateStyle_in andTimeFormatterStyle:(NSDateFormatterStyle)timeStyle_in DEPRECATED_ATTRIBUTE;

@end
