//
//  MAFFormatter.h
//  MAFFormatters
//
//  Created by  on 7/20/12.
//  Copyright (c) 2012 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MAFFormattingFactory.h"

/**
 Responsible to create formatter classes which conforms to MAFFormatting protocol.
 An optional formatter can be set which can extend or overwrite the existing formatters.
 The custom formatter has the precedence to create a formatter.
 */
@interface MAFFormatterFactory : NSObject <MAFFormattingFactory>

/**
 Custom formatter can be set which will be called on any formatter creation before the default factory is called.
 */
@property (retain) NSObject<MAFFormattingFactory>* customFormatterFactory;

/**
 * Factory Method
 * It is not mandatory to use the singleton instance, if want to create the instance another way, you can allocate it.
 * @return The singleton MAFFormatterFactory instance
 */
+ (MAFFormatterFactory*)sharedInstance;


@end
