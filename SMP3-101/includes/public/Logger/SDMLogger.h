//
//  SDMLogger.h
//  SDMSupportability
//
//  Created by Nyisztor Karoly on 6/20/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMLogging.h"
#import "asl.h"

/**
 * Supported skin types
 */
typedef enum ELogSkinType {
	NativeLogs = 0, ///< iOS native colors (default value)
    WelterLogs = 1,	///< SAP Welter skin - coming soon
	//	Custom		///< custom colors coming soon
} LogSkinType;

@interface LogEntry : NSObject
{
	NSString* m_LogMessage;
}

@property (nonatomic, retain) NSString* logMessage;
@property (nonatomic, assign) BOOL isSendable;
@property (nonatomic, assign) LoggingLevels logLevel;

@end


#pragma mark -
#pragma mark Logger Macros

/**
 * Logging Macros
 * @remark The SDMLOGx macros automatically enhance the log entry with useful information like FILE, FUNCTION and LINE
 *
 * @discussion all logging levels supported by OS X / iOS are covered. 
 * Normally Error, Warning, Info and Debug log levels would suffice for client side development
 */

/*
 * Level 0 – “Emergency”
 */
#ifndef SDMLOGEMERGENCY
#define SDMLOGEMERGENCY(msg) \
{ \
[[SDMLogger instance] logEmergency:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 1 – “Alert”
 */
#ifndef SDMLOGALERT
#define SDMLOGALERT(msg) \
{ \
[[SDMLogger instance] logAlert:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 2 – “Critical”
 */
#ifndef SDMLOGCRITICAL
#define SDMLOGCRITICAL(msg) \
{ \
[[SDMLogger instance] logCritical:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 3 – “Error”
 */
#ifndef SDMLOGERROR
#define SDMLOGERROR(msg) \
{ \
[[SDMLogger instance] logError:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 4 – “Warning”
 */
#ifndef SDMLOGWARNING
#define SDMLOGWARNING(msg) \
{ \
[[SDMLogger instance] logWarning:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
															[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
															[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
															__LINE__]]; \
} 
#endif

/*
 * Level 5 – “Notice”
 */
#ifndef SDMLOGNOTICE
#define SDMLOGNOTICE(msg) \
{ \
[[SDMLogger instance] logNotice:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 6 – “Info”
 */
#ifndef SDMLOGINFO
#define SDMLOGINFO(msg) \
{ \
[[SDMLogger instance] logInfo:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 7 – “Debug”
 */
#ifndef SDMLOGDEBUG
#define SDMLOGDEBUG(msg) \
{ \
[[SDMLogger instance] logDebug:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/**
 * Defines the Logging APIs
 * @remark You should use the SDMLOGx macros as they automatically enhance the log entry with useful information like FILE, FUNCTION and LINE 
 * @discussion all logging levels supported by OS X / iOS are covered. 
 * Normally Error, Warning, Info and Debug log levels would suffice for client side development
 */
@interface SDMLogger : NSObject <SDMLogging> {
	//! the ASL Message object responsible for logging
	aslmsg m_Message;	
}

/**
 * Logging is enabled 
 */
//@property (nonatomic, assign) BOOL isLoggingEnabled;

#pragma mark -
#pragma mark Enable / disable logging

/**
 * Enables logging
 * @discussion Logging is disabled by default for non-critical logging levels, 
 * meaning WarningLoggingLevel, NoticeLoggingLevel, InfoLoggingLevel and DebugLoggingLevel messages won't be logged - unless you call +enableLogging API explicitely.
 * Call this API to enable all log levels. Handle with care, since verbose logging might affect your applications performance.
 * Note: NSLog counts as a WarningLoggingLevel log message
 * @remark Critical log messages are always logged: EmergencyLoggingLevel, AlertLoggingLevel, CriticalLoggingLevel and ErrorLoggingLevel
 */
+(void) enableLogging;

/**
 * Disables logging of non-critical messages
 * @discussion Call this API to disable logging of low prio messages if you previously enabled them via +enableLogging API. 
 * Logging is disabled by default for non-critical logging levels; WarningLoggingLevel, NoticeLoggingLevel, InfoLoggingLevel and DebugLoggingLevel messages 
 * won't be logged - unless you call +emableLogging API explicitely.
 * Note: NSLog counts as a WarningLoggingLevel log message
 * @remark Critical log messages are always logged: EmergencyLoggingLevel, AlertLoggingLevel, CriticalLoggingLevel and ErrorLoggingLevel
 */
+(void) disableLogging;

/**
 * Set the number of log entries that can be read at a time. This is set to 500 by default. 
 * @discussion Call this API only when you want to read a greater no of log entries from the ASL
 * won't be logged - unless you call +emableLogging API explicitely.
 */
+(void)setDeviceLogEntries:(unsigned int)noOfLogs;

#pragma mark -
#pragma mark Logging status
/**
 * Returns whether non-critical logs are currently enabled
 */
+(BOOL) isLoggingEnabled;


#pragma mark -
#pragma mark Displaying Logs

/**
 * Displays all log entries with the given Logging Level
 * <pre>
 * Sample usage:
 * <code>
 * NSArray* messages = [[SDMLogger instance] displayLogsWithLevel:WarningLoggingLevel];
 * </code>
 * </pre>  
 * @see displayLogsWithLevel:(LoggingLevels)level forQueryOperation:(QueryOperations)queryOperation
 */
-(void) displayLogsWithLevel:(LoggingLevels)level_in __attribute((deprecated("This method will be deprecated soon. Please use the method provided by MAF")));

/**
 * Displays all log entries with the given Logging Level and Skin Type
 * <pre>
 * Sample usage:
 * <code>
 * NSArray* messages = [[SDMLogger instance] displayLogsWithLevel:WarningLoggingLevel];
 * </code>
 * </pre>  
 * @see displayLogsWithLevel:(LoggingLevels)level forQueryOperation:(QueryOperations)queryOperation
 */
-(void) displayLogsWithLevel:(LoggingLevels)level_in withSkinType:(LogSkinType)skinType_in __attribute((deprecated("This method will be deprecated soon. Please use the method provided by MAF")));

/**
 * Displays all log entries which match the provided Logging Level and query operation
 * @remark Use this API for example to display all messages with a priority level greater than or equal to a given logging level 
 * <pre>
 * Sample usage:
 * <code>
 * // display all messages with a priority level greater than or equal to a Warning logging level
 * NSArray* messages = [[SDMLogger instance] retrieveLogsWithLevel:WarningLoggingLevel forQueryOperation:GreaterEqual];
 * </code>
 * </pre> 
 * @see retrieveLogsWithLevel
 */
-(void) displayLogsWithLevel:(LoggingLevels)level_in forQueryOperation:(QueryOperations)queryOperation_in __attribute((deprecated("This method will be deprecated soon. Please use the method provided by MAF")));

 /**
  * Displays all log entries which match the provided Logging Level and query operation
  * @remark Use this API for example to display all messages with a priority level greater than or equal to a given logging level 
  * <pre>
  * Sample usage:
  * <code>
  * // display all messages with a priority level greater than or equal to a Warning logging level
  * NSArray* messages = [[SDMLogger instance] retrieveLogsWithLevel:WarningLoggingLevel forQueryOperation:GreaterEqual];
  * </code>
  * </pre> 
  * @see retrieveLogsWithLevel
  */
 -(void) displayLogsWithLevel:(LoggingLevels)level_in forQueryOperation:(QueryOperations)queryOperation_in withSkinType:(LogSkinType) skinType_in __attribute((deprecated("This method will be deprecated soon. Please use the method provided by MAF")));
	 
#pragma mark -
#pragma mark Retrieving Logs

/**
 * Returns all log entries with the given Logging Level
 * <pre>
 * Sample usage:
 * <code>
 * NSArray* messages = [[SDMLogger instance] retrieveLogsWithLevel:WarningLoggingLevel];
 * </code>
 * </pre>  
 * @see retrieveLogsWithLevel:(LoggingLevels)level forQueryOperation:(QueryOperations)queryOperation
 */
-(NSArray*) retrieveLogsWithLevel:(LoggingLevels)level_in;

/**
 * Returns all log entries with match the provided Logging Level and query operation
 * @remark Use this API for example to retrieve all messages with a priority level greater than or equal to WarningLoggingLevel 
 * <pre>
 * Sample usage:
 * <code>
 * NSArray* messages = [[SDMLogger instance] retrieveLogsWithLevel:WarningLoggingLevel forQueryOperation:GreaterEqual];
 * </code>
 * </pre> 
 * @see retrieveLogsWithLevel
 */

-(NSArray*) retrieveLogsWithLevel:(LoggingLevels)level_in forQueryOperation:(QueryOperations)queryOperation;

#pragma mark -
#pragma mark Generating Logs

/**
 * Generic logger API
 * @remark Added for convenience; consider using the explicit APIs listed below - or even better, the macros provided which 
 * automatically add further information such as the timestamp, file and method name, and the line number from where the logger has been invoked
 * <pre>
 * Sample usage:
 * <code>
 * [[SDMLogger instance] logMessage:@"This line will be logged with Warning Level" withLevel:WarningLoggingLevel andInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in the message to be logged
 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
 * @see SDMLogEmergency C-style API counterpart
 */	
-(void) logMessage:(NSString*) message_in withLevel:(LoggingLevels)level_in andInfo:(NSString*) info_in;

/**
 * Highest (Emergency) level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [[SDMLogger instance] logEmergency:@"This line will be logged with Emergency Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in the message to be logged
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see SDMLogEmergency C-style API counterpart
 */	
-(void) logEmergency:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Alert level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [[SDMLogger instance] logAlert:@"This line will be logged with Alert Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in the message to be logged
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see SDMLogAlert C-style API counterpart
 */			
-(void) logAlert:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Critical level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [[SDMLogger instance] logCritical:@"This line will be logged with Critical Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in the message to be logged
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see SDMLogCritical C-style API counterpart
 */	
-(void) logCritical:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Error level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [[SDMLogger instance] logError:@"This line will be logged with Error Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in the message to be logged
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see SDMLogError C-style API counterpart
 */		
-(void) logError:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Warning level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [[SDMLogger instance] logWarning:@"This line will be logged with Warning Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in the message to be logged
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see SDMLogWarning C-style API counterpart
 */		
-(void) logWarning:(NSString*) message_in withInfo:(NSString*) info_in;	

/**
 * Notice level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [[SDMLogger instance] logNotice:@"This line will be logged with Notice Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in the message to be logged
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see SDMLogNotice C-style API counterpart
 */		
-(void) logNotice:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Information level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [[SDMLogger instance] logInfo:@"This line will be logged with Info Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in the message to be logged
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see SDMLogInfo C-style API counterpart
 */		
-(void) logInfo:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Debug level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [[SDMLogger instance] logDebug:@"This line will be logged with Debug Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in the message to be logged
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see SDMLogDebug C-style API counterpart
 */		
-(void) logDebug:(NSString*) message_in withInfo:(NSString*) info_in;

#pragma mark -
#pragma mark Singleton instance
/**
 * Static Persistence instance
 */
+ (id)instance;

#pragma mark -
#pragma mark Accessors

@end


#pragma mark -
#pragma mark C-style APIs

#ifdef SDMLOGGER_H
#ifdef __OBJC__ 

#import <objc/objc.h>

@class NSString;

#ifdef __cplusplus
extern "C" {
#endif	

	/**
	 * Highest (Emergency) level logger API
	 * <pre>
	 * Sample usage:
	 * <code>
	 * SDMLogEmergency(@"This line will be logged with Emergency Logging level", @"Additional information");
	 * </code>
	 * </pre>
	 * @param message_in the message to be logged
	 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
	 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
	 * @discussion this is the convenience C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
	 * @see logEmergency
	 */	
	void SDMLogEmergency(NSString* message_in, NSString* info_in);

	/**
	 * Alert level logger API
	 * <pre>
	 * Sample usage:
	 * <code>
	 * SDMLogAlert(@"This line will be logged with Alert Logging level", @"Additional information");
	 * </code>
	 * </pre>
	 * @param message_in the message to be logged
	 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
	 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
	 * @discussion this is the convenience C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
	 * @see logAlert
	 */			
	void SDMLogAlert(NSString* message_in, NSString* info_in);
	
	/**
	 * Critical level logger API
	 * <pre>
	 * Sample usage:
	 * <code>
	 * SDMLogCritical(@"This line will be logged with Critical Logging level", @"Additional information");
	 * </code>
	 * </pre>
	 * @param message_in the message to be logged
	 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
	 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
	 * @discussion this is the convenience C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
	 * @see logCritical
	 */	
	void SDMLogCritical(NSString* message_in, NSString* info_in);
	
	/**
	 * Error level logger API
	 * <pre>
	 * Sample usage:
	 * <code>
	 * SDMLogError(@"This line will be logged with Error Logging level", @"Additional information");
	 * </code>
	 * </pre>
	 * @param message_in the message to be logged
	 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
	 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
	 * @discussion this is the convenience C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
	 * @see logError
	 */		
	void SDMLogError(NSString* message_in, NSString* info_in);
	
	/**
	 * Warning level logger API
	 * <pre>
	 * Sample usage:
	 * <code>
	 * SDMLogWarning(@"This line will be logged with Warning Logging level", @"Additional information");
	 * </code>
	 * </pre>
	 * @param message_in the message to be logged
	 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
	 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
	 * @discussion this is the convenience C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
	 * @see logWarning
	 */		
	void SDMLogWarning(NSString* message_in, NSString* info_in);
	
	/**
	 * Notice level logger API
	 * <pre>
	 * Sample usage:
	 * <code>
	 * SDMLogNotice(@"This line will be logged with Notice Logging level", @"Additional information");
	 * </code>
	 * </pre>
	 * @param message_in the message to be logged
	 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
	 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
	 * @discussion this is the convenience C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
	 * @see logNotice
	 */		
	void SDMLogNotice(NSString* message_in, NSString* info_in);
	
	/**
	 * Information level logger API
	 * <pre>
	 * Sample usage:
	 * <code>
	 * SDMLogInfo(@"This line will be logged with Info Logging level", @"Additional information");
	 * </code>
	 * </pre>
	 * @param message_in the message to be logged
	 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
	 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
	 * @discussion this is the convenience C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
	 * @see logInfo
	 */		
	void SDMLogInfo(NSString* message_in, NSString* info_in);
	
	/**
	 * Debug level logger API
	 * <pre>
	 * Sample usage:
	 * <code>
	 * SDMLogDebug(@"This line will be logged with Debug Logging level", @"Additional information");
	 * </code>
	 * </pre>
	 * @param message_in the message to be logged
	 * @param info_in additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__) 
	 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
	 * @discussion this is the convenience C-style logger API; one may choose to rather invoke the Objective-C counterpart API via the singleton class instance
	 * @see logDebug
	 */		
	void SDMLogDebug(NSString* message_in, NSString* info_in);
#ifdef __cplusplus
}

#endif
#endif
#endif