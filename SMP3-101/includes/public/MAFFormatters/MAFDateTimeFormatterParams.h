//
//  MAFDateParams.h
//  MAFFormatters
//
//  Created by Kiri, Gyula on 2012.07.25..
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#define MAFDateTimeFormatterParamsUTCFormatString @"yyyy'-'MM'-'dd'T'HH':'mm':'ss"

@interface MAFDateTimeFormatterParams : NSObject <NSCopying> {
    BOOL toUTC;
    NSLocale* locale;
    NSString* dateFormat;
    NSTimeZone* timeZone;
    NSDateFormatterStyle dateStyle;
    NSDateFormatterStyle timeStyle;
}

+ (MAFDateTimeFormatterParams*) dateTimeFormatterParamsWithDateStyle:(NSDateFormatterStyle)aDateStyle timeStyle:(NSDateFormatterStyle)aTimeStyle locale:(NSLocale*)aLocale toUTC:(BOOL)utc dateFormat:(NSString*)aDateFormat timeZone:(NSTimeZone*)aTimeZone;

@property BOOL toUTC;
@property (retain) NSLocale* locale;
@property (retain) NSString* dateFormat;
@property (retain) NSTimeZone* timeZone;
@property NSDateFormatterStyle dateStyle;
@property NSDateFormatterStyle timeStyle;

@end
