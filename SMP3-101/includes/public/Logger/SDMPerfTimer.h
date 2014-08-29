//
//  SDMPerfTimer.h
//  SDMSupportability library
//
//  Created by Karoly Nyisztor on 2/4/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

/**
 * High Precision Timer Class
 *
 * @discussion The timer class should be used for accurate performance measurements. 
 * SDMPerfTimer uses low level Mach timing functions, therefore it is reliable and lightweight. 
 *
 * <pre>
 * Sample usage:
 * <code>
 * // instantiate the timer and start it 
 * SDMPerfTimer* perfTimer = [[SDMPerfTimer alloc] init];
 * [perfTimer start];
 * ...
 * // invoke when and from wherever needed (must not be the same scope as the start or reset message)
 * double elapsedTime = [perfTimer getTimeElapsedInMillisec];
 * NSLog(@"Time elapsed: [%f ms], [%f s]", elapsedTime, (elapsedTime / 1000.f) );
 * // release the timer when you do not need it anymore
 * [perfTimer release];
 * </code>
 * </pre>
 */

@interface SDMPerfTimer : NSObject
{
	double m_TimerFreq;	
	
	double m_LastTimeHere;	
} 

/**
 * Retrieves the time elapsed after calling startTimer, resetTimer or between two consecutive getTimeElapsedInMillisec calls
 */
-(uint64_t) getTimeElapsedInMillisec;

/**
 * Initializes the timer
 */
-(void) start;

/**
 * Resets the timer
 */
-(void) reset;

@end