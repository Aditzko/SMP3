//
//  SeedDataAPI.h
//  Afaria
//
//  Created by Corey Mayo on 4/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Security/SecBase.h>

// bundle identifier used by afaria client
// may vary in development versions
#define AFARIA_BUNDLE_ID @"com.sybase.afariaClient"

@class SeedDataAPI;

@protocol SeedDataDelegate <NSObject>
- (void)didRetrieveSeedData:(NSString *)seedFile;
- (void)didNotNeedUpdate;
- (void)didFailWithError:(NSError *)error;
- (void)didUploadFile:(NSString *)filePath;
@end

@interface SeedDataAPI : NSObject {
	NSString *_urlScheme;
	id <SeedDataDelegate> _delegate;
}

- (SeedDataAPI *)initWithURLScheme:(NSString *)urlScheme andDelegate:(id <SeedDataDelegate>)delegate;
- (void)retrieveSeedData;
- (void)updateSeedData;
- (void)updateSettings;
- (void)clearSettings;
- (BOOL)areSettingsConfigured;
- (void)uploadFile:(NSString *)filePath;
- (void)handleUrl:(NSURL *)url;

@end
