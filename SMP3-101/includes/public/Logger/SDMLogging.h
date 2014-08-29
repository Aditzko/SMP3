//
//  SDMLogging.h
//  SDMSupportability
//
//  Created by Nyisztor Karoly on 6/20/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#include <asl.h>

/**
 * Supported Logging Levels
 * @remark Mirrors OS X / iOS Logging levels
 */

/*
 Logging Message Levels:
 
 Level 0 – “Emergency”
 Level 1 – “Alert”
 Level 2 – “Critical”
 Level 3 – “Error”
 Level 4 – “Warning”
 Level 5 – “Notice”
 Level 6 – “Info”
 Level 7 – “Debug”
 */

/**
 * Defines the Logging levels used throughout Logger APIs
 * @remark remapping ASL log level defines to own enum; thus clients do not have to include asl.h
 * @discussion we enumerate all logging levels supported by OS X / iOS. However, Error, Warning, Info and Debug log levels would normally suffice for client side development
 */
typedef enum ELoggingLevels
{
	EmergencyLoggingLevel = ASL_LEVEL_EMERG,	///< Level 0
	AlertLoggingLevel = ASL_LEVEL_ALERT,		///< Level 1
	CriticalLoggingLevel = ASL_LEVEL_CRIT,		///< Level 2
	ErrorLoggingLevel = ASL_LEVEL_ERR,			///< Level 3 -> probably the highest Logging Level which should be used by Apps
	WarningLoggingLevel = ASL_LEVEL_WARNING,	///< Level 4 -> use to log non blocker issues
	NoticeLoggingLevel = ASL_LEVEL_NOTICE,		///< Level 5 -> log a note, might be handy at times, but usually Info level would suffice
	InfoLoggingLevel = ASL_LEVEL_INFO,			///< Level 6 -> log informations of any kind
	DebugLoggingLevel = ASL_LEVEL_DEBUG,		///< Level 7 -> denotes verbose logs used during development only
} LoggingLevels;

typedef enum EQueryOperations
{
	Equals = ASL_QUERY_OP_EQUAL,				///< value equality
	Greater = ASL_QUERY_OP_GREATER,				///< value greater than
	GreaterEqual = ASL_QUERY_OP_GREATER_EQUAL,  ///< value greater than or equal to
	Less = ASL_QUERY_OP_LESS,					///< value less than
	LessEqual = ASL_QUERY_OP_LESS_EQUAL,		///< value less than or equal to
	NotEqual = ASL_QUERY_OP_NOT_EQUAL,			///< value not equal
} QueryOperations;


/**
 * Declares the logger APIs
 * Protocol to be adapted by Logger classes
 * @remark Clients might consider using the SDMLogger
 * <pre>
 * Features:
 * <ul>
 * <li> convenient logging APIs and macros
 * <li> detailed information (such as filename, method and line#) included in the log
 * <li> 8 logging levels (as supported by the OS: Level 0 – “Emergency”, Level 1 – “Alert”, Level 2 – “Critical”, Level 3 – “Error”, Level 4 – “Warning”, Level 5 – “Notice”, Level 6 – “Info”, Level 7 – “Debug”)
 * <li> built-in log tracking UI
 * <li> possibility to e-mail log entries
 * </ul> 
 * Coming soon:
 * <ul>
 * <li> sensitive data filtering (personal and business data is excluded from the logs)
 * <li> performance logging using high precision timers
 * </ul>
 * </pre>
 */

@protocol SDMLogging

@required

/**
 * Should return all log entries with the given Logging Level
 * @see retrieveLogsWithLevel:(LoggingLevels)level forQueryOperation:(QueryOperations)queryOperation
 */
-(NSArray*) retrieveLogsWithLevel:(LoggingLevels)level_in;

/**
 * Should return all log entries with match the provided Logging Level and query operation
 * @remark Use this API for example to retrieve all messages with a priority level greater than or equal to WarningLoggingLevel 
 * @see retrieveLogsWithLevel
 */
-(NSArray*) retrieveLogsWithLevel:(LoggingLevels)level_in forQueryOperation:(QueryOperations)queryOperation;

#pragma mark -
#pragma mark Generating Logs

/**
 * Generic logger API
 * @remark Added for convenience; consider using the explicit APIs listed below - or even better, the macros provided which 
 * automatically add further information such as the timestamp, file and method name, and the line number from where the logger has been invoked
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
 * @see SDMLogEmergency C-style API counterpart
 */	
-(void) logMessage:(NSString*) message_in withLevel:(LoggingLevels)level_in andInfo:(NSString*) info_in;

/**
 * Highest (Emergency) level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
 * @see SDMLogEmergency C-style API counterpart
 */	
-(void) logEmergency:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Alert level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
 * @see SDMLogAlert C-style API counterpart
 */			
-(void) logAlert:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Critical level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
 * @see SDMLogCritical C-style API counterpart
 */	
-(void) logCritical:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Error level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
 * @see SDMLogError C-style API counterpart
 */		
-(void) logError:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Warning level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
 * @see SDMLogWarning C-style API counterpart
 */		
-(void) logWarning:(NSString*) message_in withInfo:(NSString*) info_in;	

/**
 * Notice level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
 * @see SDMLogNotice C-style API counterpart
 */		
-(void) logNotice:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Information level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
 * @see SDMLogInfo C-style API counterpart
 */		
-(void) logInfo:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Debug level logger API
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
 * @see SDMLogDebug C-style API counterpart
 */		
-(void) logDebug:(NSString*) message_in withInfo:(NSString*) info_in;

@end
