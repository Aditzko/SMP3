//
//  PerformanceAgent.h
//  StaticPerfLib
//
//  Created by Kirtkow, Sergej on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "PerformanceCounter.h"

/**
 Definition of various interval types
 */
extern NSString * const END_TO_END;/**< End to end interval, should include all other intervals */
extern NSString * const PARSING;/**< Parsing */
extern NSString * const UNZIP;/**< Unzip */
extern NSString * const HTTP_REQUEST;/**< Http request */
extern NSString * const PERSISTENCE_READ;/**< Resistence read */
extern NSString * const PERSISTENCE_WRITE;/**< Resistence write */


/**
 This class is responsible for management of performance counters
 */
@interface PerformanceAgent : NSObject{
@private
    /**
     Flag to activate logging into file
     */
    BOOL useLogFile;
    /**
     Flag to activate console logging
     */
    BOOL useLogConsole;
    /**
     Set size of log file
     */
    int logFileSize;
    
    BOOL counterIsDeactivated;
    NSMutableArray* countersWithSameName;
}

@property (readwrite) BOOL useLogFile;
@property (readwrite) int logFileSize;
@property (readwrite) BOOL useLogConsole;
@property (readwrite) BOOL counterIsDeactivated;
@property (readwrite, retain) NSMutableArray* countersWithSameName;

/**
 Activate console logging
 @param writeToConsole can be true or false 
 */
- (void) writeToConsole:(BOOL)writeToConsole;

/**
 Activate logging into file
 @param writeToConsole can be true or false 
 @param fileSize set size in KiloBytes of log file	
 */
- (void) writeToFile:(BOOL)writeToFile fileSize:(int)fileSize;

/**
 Starts Interaction Step with specified Interactions name
 @param name name of Interaction Step
 */
- (void) startInteractionStep:(NSString*)name;

/**
 Stops Interaction Step with specified Interactions name
 @param name name of Interaction Step
 */
- (void) stopInteractionStep;

/**
 Starts specified Interval
 @param type  Intervals type
 */
- (void) startInterval:(NSString*)type;

/**
 Stops specified Interval
 @param type  Intervals type
 */
- (void) stopInterval:(NSString*)type;
//- (void) writeDataForCounters;


-(void) enablePerformanceCounter;
-(void) disablePerformanceCounter;

- (NSString*) getMeasuredDataAsString;
- (NSString*) getMeasuredDataAsStringDescription;

- (void)saveEntryToFile: (NSString*) entry;
- (NSData*)getHalfFile: (NSString*)file fileSize:(long)fileSize;
- (PerformanceCounter*) getInterval:(NSString*)type;
- (NSString*) getIntervalDescriptionAsString:(NSString*)type;
- (NSString*) getIntervalDataAsString:(NSString*)type;

@end
