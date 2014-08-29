//
//  MAFFormatterFactory.h
//  MAFFormatters
//
//  Created by  on 7/20/12.
//  Copyright (c) 2012 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MAFFormatting;

/**
 Declares the methods a formatter factory should implement.
 A formatter factory has the responsibility to create formatter classes which conform to the MAFFormatting protocol.
 */
@protocol MAFFormattingFactory <NSObject>

/**
 Creates a formatter with the given type by passing the parameter object to it.
 If the factory cannot create a formatter with the given type returns nil.
 @param formatterType the type name of the formatter to create
 @param aParameter the parameter object will be passed to the created class on init. Can be nil or can be a pattern string or any other object; depends on the formatter.
 @return A formatter instance with the given type or nil. The returned value is autoreleased.
 */
- (NSObject<MAFFormatting> *) createFormatterWithType:(NSString *)formatterType formatterParameter:(NSObject<NSCopying> *)aParameter;

/**
 Creates an returns an object to store parameters of the formatter with the given type.
 If the type is unknown nil is returned.
 @param formatterType the type name of the formatter using the parameters
 @return A formatter context with the given type or nil. The returned value is autoreleased.
 */
- (NSObject<NSCopying>*) createFormatterContextWithType:(NSString*)formatterType;

@end
