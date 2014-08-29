//
//  MAFFormatting.h
//  MAFFormatters
//
//  Created by  on 7/20/12.
//  Copyright (c) 2012 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Defines the methods a formatter should implement.
 */
@protocol MAFFormatting <NSObject>

/**
 Parameter object which can change the behavior of the formatter.
 Can be a nil, a string or any other object based on the formatter.
 */
@property (copy) NSObject<NSCopying> *formatterParameter;

/**
 Initializes a formatter object
 @param aParameter the same as the parameter property
 @return an initialized formatter object or nil on any error
 */
- (id)initWithFormatterParameter:(NSObject<NSCopying> *)aParameter;

/**
 Creates a formatter string based on the parameter and the value.
 @param aValue formatter uses this value to create the formatted string
 @return the formatted string
    Example:
 NSDate* date = [NSDate date];
 MAFDateTimeFormatterParams* mafDateTimeFormatterParams = [[MAFDateTimeFormatterParams alloc] init];
 mafDateTimeFormatterParams.toUTC = NO;
 mafDateTimeFormatterParams.locale = nil;
 mafDateTimeFormatterParams.dateStyle = kCFDateFormatterShortStyle;
 mafDateTimeFormatterParams.timeStyle = kCFDateFormatterShortStyle;
 NSObject<MAFFormattingFactory>* mafFormatterFactory = [MAFFormattingSampleServiceLocator formatterFactory];
 MAFDateTimeFormatter* mafDateTimeFormatter = (MAFDateTimeFormatter*)[mafFormatterFactory createFormatterWithType:MAFFormatterTypeDateTime formatterParameter:mafDateTimeFormatterParams];
 mafDateTimeFormatter.formatterParameter = mafDateTimeFormatterParams;
 NSString* localizedDateString = [mafDateTimeFormatter formatValue:date];
 */
- (NSString *)formatValue:(NSObject*)aValue;

@end
