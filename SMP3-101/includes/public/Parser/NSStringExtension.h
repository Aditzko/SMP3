//
//  NSStringExtension.h
//  ODataTestNyK
//
//  Created by Karoly Nyisztor on 8/13/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

//#import <Foundation/Foundation.h>

/**
 NSString extensions
 */
@interface NSString (NSStringExtensions)

+ (BOOL)isWildcard:(NSString*)str;
+ (BOOL)isAsterisk:(NSString*)str;
+ (BOOL)isNullOrEmpty:(NSString*)str;
- (BOOL)containsSubstring:(NSString*)substring;
- (BOOL) booleanValue;
- (unsigned int) indexOf:(char) searchChar;
+ (NSString *)URLEncodedString:(NSString *)string;
- (BOOL)isNoCasePrefix:(const NSString* const)prefix;
@end
