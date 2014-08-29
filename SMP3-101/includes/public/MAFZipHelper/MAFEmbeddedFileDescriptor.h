//
//  EmbeddedFileDescriptor.h
//  MAFZipHelper
//
//  Created by Palfi, Andras on 5/9/12.
//  Copyright (c) 2012 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Describes an embedded file in a zip file.
 */
@interface MAFEmbeddedFileDescriptor : NSObject

@property (nonatomic, retain) NSString*     fileName;
@property (nonatomic, assign) unsigned int  compressedSize;
@property (nonatomic, assign) unsigned int  uncompressedSize;

@end
