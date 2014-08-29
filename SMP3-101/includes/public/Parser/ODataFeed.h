//
//  ODataFeed.h
//  Parser
//
//  Created by M, Pramod on 13/06/13.
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ODataLink;

@interface ODataFeed : NSObject<NSCoding>

@property(nonatomic, retain) NSString* title;
@property(nonatomic, retain) NSString* feedId;
@property(nonatomic, retain) NSString* updated;
@property(nonatomic, retain) NSMutableArray* links;

@property(nonatomic, retain) NSMutableArray* entries;
@property(nonatomic, retain) NSMutableArray* deletedEntries;
@property(nonatomic, retain) NSMutableArray* linkEntries;
@property(nonatomic, retain) NSMutableArray* deletedLinkEntries;

-(ODataLink *)getDeltaLink;

@end
