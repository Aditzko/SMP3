//
//  MAFLogonFileManager.h
//  MAFLogonManagerNG
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Interface to read plist files from file
 */
@interface MAFLogonFileManager : NSObject

/**
 Reads file content from bundle
 @param aFileName Filename that contains the plist
 @param aBundle Bundle that contains the file
 */
+(NSDictionary*) dictionaryFromPlistFile:(NSString*)aFileName bundle:(NSString*)aBundle;

/**
 Reads the first url scheme from the info.plist configuration file
 */
+ (NSString *)firstUrlSchemeFromInfoPlist;

@end
