//
//  ZipFileDescriptor.h
//  MAFZipHelper
//
//  Created by Palfi, Andras on 5/8/12.
//  Copyright (c) 2012 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Provides the ability to get the contained files from a zip file.
 */
@interface MAFZipFileDescriptor : NSObject

/**
 Initializes the instance by opening the zip file and loading the file information from it. Doesn't read the compressed data.
 @param filePath the path of the zip file
 @return the initialized object
 */
- (id) initWithFileAtPath:(NSString *)filePath;

/**
 Reads and uncompresses an embedded file from the zip file. The embedded file is identified by its index in the embeddedFileDescriptorList container.
 @param indexOfFile index of the embedded file as it is defined in the embeddedFileDescriptorList container
 @return the uncompressed data on success or nil
 */
- (NSData*) uncompressedEmbeddedFileContentAtIndex:(int)indexOfFile;

/**
 Reads and uncompresses an embedded file from the zip file. The embedded file is identified by the name of the embedded file.
 @param fileName name of the embedded file. If the file is in a folder the fileName should contain the foldername as well.
 @return the uncompressed data on success or nil
 */
- (NSData*) uncompressedEmbeddedFileContentNamed:(NSString *)fileName;

/**
 Uncompresses the embedded file at the index to a folder. The method creates the necessary folders.
 If the file already exists it will be overwritten.
 @param indexOfFile index of the embedded file as it is defined in the embeddedFileDescriptorList container
 @param folder The path of the folder where the file should be created
 */
- (BOOL) unzipEmbeddedFileAtIndex:(int)indexOfFile toFolder:(NSString*)folder;

/**
 Uncompresses every file in the zip file to the specified folder. The zipped file hierarchy will be re-created.
 @param folder The path of the folder where the files should be created
 */
- (BOOL) unzipAllTofolder:(NSString *)folder;

/**
 Returns a list of EmbeddedFileDescriptor. Each descriptor describes an embedded file or a folder in the zip file.
 */
@property (readonly) NSArray* embeddedFileDescriptorList;

/**
 Returns whether the file open was successful and there are embedded files in the zip file
 */
@property (readonly) BOOL isOpen;

@end
