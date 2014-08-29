//
//  PerformanceCounter.h
//  XmlParsingBenchmark
//
//  Created by Dahl, Stephan on 3/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <mach/mach.h>
#include <mach/mach_time.h>

extern NSString * const TRAFFIC_SENT;
extern NSString * const TRAFFIC_RECEIVED;
extern NSString * const NETWORK_TIME; //networkTime
extern NSString * const ROUND_TRIPS; //roundTrips
extern NSString * const TOTAL_BYTES; //totalBytes
extern NSString * const MEM_ALLOCATED; //memAllocated
/*
 1) Network time
 
 2) Roundtrip
 
 3) total bytes
 
 4) memory allocated

 */

@interface PerformanceCounter : NSObject {
@private
	uint64_t startTime;
	long startUserTime;
	long startSystemTime;
	long startMaxMemory;
	uint64_t elapsedTime;
	long userTime;
	long systemTime;		
	float maxMemory;
    NSString *stepName;
    NSString *intervalType;
    BOOL isStopped;
    NSMutableDictionary *kpisMap; 
}

@property (readonly) uint64_t startTime;
@property (readonly) uint64_t elapsedTime;
@property (readonly) long cpuTime;
@property (readonly) long userTime;
@property (readonly) long systemTime;
@property (readonly) float maxMemory;
@property (readwrite, copy) NSString* intervalType;
@property (readwrite, copy) NSString* stepName;
@property (readwrite) BOOL isStopped;
@property (readwrite, retain) NSMutableDictionary *kpisMap;


- (void)startMeasurement: (NSString*) step;
- (void)stopMeasurement;
- (void)setCounterValue: (NSString*) kpiName kpiValue:(NSString*) kpiValue;
- (NSString*)getCounterValue:(NSString*) kpiName; 

//- (NSString*) shortDescription;
- (NSString*) getCurrentTime;
//- (NSString*) getStringConsoleLog;

- (NSString*) getIntervalDataAsString;
- (NSString*) getIntervalDescriptionAsString;
- (NSString*) getUserReadableResult;




@end
