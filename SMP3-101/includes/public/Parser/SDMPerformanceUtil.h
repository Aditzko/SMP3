//
//  SDMPerformanceUtil.h
//  SDMParser
//
//  Created by Chug, Satvindar on 8/16/12.
//  Copyright (c) 2012 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @deprecated
 */
__attribute((deprecated("Use PerformanceUtil instead")))
@interface SDMPerformanceUtil : NSObject

+(void)enableParserPerformanceLog:(BOOL)value_in;
+(BOOL)isParserPerfLogEnabled;

@end
