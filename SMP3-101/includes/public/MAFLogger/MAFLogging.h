//
//  MAFLogging.h
//  MAFLogger
//
//  Copyright (c) 2012 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "asl.h"

/**
 * Defines the Logging levels used throughout Logger APIs
 * @remark remapping ASL log level defines to own enum; thus clients do not have to include asl.h
 * @discussion we enumerate all logging levels supported by OS X / iOS. However, Error, Warning, Info and Debug log levels would normally suffice for client side development
 */
typedef enum ELoggingLevel
{
	MAFEmergencyLoggingLevel = ASL_LEVEL_EMERG,	///< Level 0
	MAFAlertLoggingLevel = ASL_LEVEL_ALERT,		///< Level 1
	MAFCriticalLoggingLevel = ASL_LEVEL_CRIT,		///< Level 2
	MAFErrorLoggingLevel = ASL_LEVEL_ERR,			///< Level 3 -> probably the highest Logging Level which should be used by Apps
	MAFWarningLoggingLevel = ASL_LEVEL_WARNING,	///< Level 4 -> use to log non blocker issues
	MAFNoticeLoggingLevel = ASL_LEVEL_NOTICE,		///< Level 5 -> log a note, might be handy at times, but usually Info level would suffice
	MAFInfoLoggingLevel = ASL_LEVEL_INFO,			///< Level 6 -> log informations of any kind
	MAFDebugLoggingLevel = ASL_LEVEL_DEBUG,		///< Level 7 -> denotes verbose logs used during development only
} MAFLoggingLevel;

@protocol MAFLogging <NSObject>

@required

#pragma mark -
#pragma mark Enable / disable logging

/**
 * Enables logging for non-critical levels, like warning, notice, info, debug.
 */
-(void) enableNonCriticalLogging;

/**
 * Disables logging of non-critical messages, like warning, notice, info, debug.
 */
-(void) disableNonCriticalLogging;


#pragma mark -
#pragma mark Logging status
/**
 * Returns whether non-critical logs are currently enabled
 */
-(BOOL) isNonCriticalLoggingEnabled;


#pragma mark -
#pragma mark Generating Logs

/**
 * Generic logger API
 * @param message_in the message to be logged
 * @param level_in the level of the log message
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 */	
-(void) logMessage:(NSString*) message_in withLevel:(MAFLoggingLevel)level_in andInfo:(NSString*) info_in;

/**
 * Highest (Emergency) level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 */	
-(void) logEmergency:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Alert level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 */			
-(void) logAlert:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Critical level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)  
 */	
-(void) logCritical:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Error level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)  
 */		
-(void) logError:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Warning level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 */		
-(void) logWarning:(NSString*) message_in withInfo:(NSString*) info_in;	

/**
 * Notice level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 */		
-(void) logNotice:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Information level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 */		
-(void) logInfo:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Debug level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 */		
-(void) logDebug:(NSString*) message_in withInfo:(NSString*) info_in;

#pragma mark -
#pragma mark Retrieving Logs

/**
 * Returns all log entries with the given logging level
 * @param level_in the level of the log messages to be retrieved
 */
-(NSArray*) retrieveLogsWithLevel:(MAFLoggingLevel)level_in;


@end
