//
//  MAFLogger.h
//  MAFLogger
//
//  Copyright (c) 2012 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>
//#include <asl.h>

#import "MAFLogging.h"

typedef enum {
    MAFLoggerSDM = 1,
    MAFLoggerConsole = 2,
    MAFLoggerFile = 4,
    MAFLoggerDelegate = 8
} MAFLoggerTypes;

#pragma mark -
#pragma mark Logger Macros

/**
 * Logging Macros
 * @remark The MAFLOGx macros automatically enhance the log entry with useful information like FILE, FUNCTION and LINE
 *
 * @discussion all logging levels supported by OS X / iOS are covered. 
 * Normally Error, Warning, Info and Debug log levels would suffice for client side development
 */

/*
 * Level 0 – “Emergency”
 */
#ifndef MAFLOGEMERGENCY
#define MAFLOGEMERGENCY(msg) \
{ \
[[MAFLogger sharedInstance] logEmergency:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 1 – “Alert”
 */
#ifndef MAFLOGALERT
#define MAFLOGALERT(msg) \
{ \
[[MAFLogger sharedInstance] logAlert:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 2 – “Critical”
 */
#ifndef MAFLOGCRITICAL
#define MAFLOGCRITICAL(msg) \
{ \
[[MAFLogger sharedInstance] logCritical:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 3 – “Error”
 */
#ifndef MAFLOGERROR
#define MAFLOGERROR(msg) \
{ \
[[MAFLogger sharedInstance] logError:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 4 – “Warning”
 */
#ifndef MAFLOGWARNING
#define MAFLOGWARNING(msg) \
{ \
[[MAFLogger sharedInstance] logWarning:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 5 – “Notice”
 */
#ifndef MAFLOGNOTICE
#define MAFLOGNOTICE(msg) \
{ \
[[MAFLogger sharedInstance] logNotice:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 6 – “Info”
 */
#ifndef MAFLOGINFO
#define MAFLOGINFO(msg) \
{ \
[[MAFLogger sharedInstance] logInfo:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif

/*
 * Level 7 – “Debug”
 */
#ifndef MAFLOGDEBUG
#define MAFLOGDEBUG(msg) \
{ \
[[MAFLogger sharedInstance] logDebug:msg withInfo:[NSString stringWithFormat:@"File: %@ Function: %@ Line: %d", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent], \
[NSString stringWithUTF8String:__PRETTY_FUNCTION__], \
__LINE__]]; \
} 
#endif



@interface MAFLogger : NSObject <MAFLogging>

+ (MAFLogger*) sharedInstance;

/**
 Specifies which loggers are used by the MAFLogger. The values van be used together using bitwise OR.
 
 */
@property (assign) MAFLoggerTypes usedLoggers;

#pragma mark -
#pragma mark Logger delegate

/**
 * Sets the logger delegate. The object will be retained.
 * @param delegate_in: the delegate must implement the MAFLogging protocol
 */
+(void)setLoggerDelegate:(NSObject<MAFLogging>*)delegate_in DEPRECATED_ATTRIBUTE;

/**
 * Sets the logger delegate. The object will be retained.
 * @param aLogger: the delegate must implement the MAFLogging protocol
 */
- (void) setLoggerDelegate:(NSObject<MAFLogging>*)aLogger;

#pragma mark -
#pragma mark Enable / disable logging

/**
 * Enables logging. Deprecated, use the instance method instead.
 * @discussion Logging can be disabled by default for non-critical logging levels, 
 * meaning Warning, Notice, Info and Debug level messages won't be logged - unless you call +enableLogging API explicitly.
 * Call this API to enable all log levels. Handle with care, since verbose logging might affect your applications performance.
 * Note: NSLog counts as a WarningLoggingLevel log message
 * @remark Critical log messages are always logged: Emergency, Alert, Critical and Error level
 */
+(void) enableNonCriticalLogging DEPRECATED_ATTRIBUTE;

/**
 * Enables logging
 * @discussion Logging can be disabled by default for non-critical logging levels,
 * meaning Warning, Notice, Info and Debug level messages won't be logged - unless you call enableLogging API explicitly.
 * Call this API to enable all log levels. Handle with care, since verbose logging might affect your applications performance.
 * Note: NSLog counts as a WarningLoggingLevel log message
 * @remark Critical log messages are always logged: Emergency, Alert, Critical and Error level
 */
-(void) enableNonCriticalLogging;

/**
 * Disables logging of non-critical messages. Deprecated, use the instance method instead.
 * @discussion Call this API to disable logging of low prio messages if you previously enabled them via +enableLogging API. 
 * Note: NSLog counts as a WarningLoggingLevel log message
 * @remark Critical log messages are always logged: Emergency, Alert, Critical and Error level 
 */
+(void) disableNonCriticalLogging DEPRECATED_ATTRIBUTE;

/**
 * Disables logging of non-critical messages
 * @discussion Call this API to disable logging of low prio messages if you previously enabled them via +enableLogging API.
 * Note: NSLog counts as a WarningLoggingLevel log message
 * @remark Critical log messages are always logged: Emergency, Alert, Critical and Error level
 */
-(void) disableNonCriticalLogging;


#pragma mark -
#pragma mark Logging status
/**
 * Returns whether non-critical logs are currently enabled.  Deprecated, use the instance method instead.
 */
+(BOOL) isNonCriticalLoggingEnabled DEPRECATED_ATTRIBUTE;

/**
 * Returns whether non-critical logs are currently enabled.  Deprecated, use the instance method instead.
 */
-(BOOL) isNonCriticalLoggingEnabled;


#pragma mark -
#pragma mark Generating Logs

/**
 * Generic logger API.  Deprecated, use the instance method instead.
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logMessage:@"This line will be logged with Warning Level" withLevel:WarningLoggingLevel andInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param level_in: log entry level
 * @param info_in: additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API
 * @see MAFLogMessage C-style API counterpart
 */	
+(void) logMessage:(NSString*) message_in withLevel:(MAFLoggingLevel)level_in andInfo:(NSString*) info_in DEPRECATED_ATTRIBUTE;

/**
 * Generic logger API
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logMessage:@"This line will be logged with Warning Level" withLevel:WarningLoggingLevel andInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param level_in: log entry level
 * @param info_in: additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message should be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the conveniene C-style logger API; one may choose to rather invoke the Objective-C counterpart API
 * @see MAFLogMessage C-style API counterpart
 */
-(void) logMessage:(NSString*) message_in withLevel:(MAFLoggingLevel)level_in andInfo:(NSString*) info_in;

/**
 * Highest (Emergency) level logger API.  Deprecated, use the instance method instead.
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logEmergency:@"This line will be logged with Emergency Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged, deprecated (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogEmergency C-style API counterpart
 */	
+(void) logEmergency:(NSString*) message_in withInfo:(NSString*) info_in DEPRECATED_ATTRIBUTE;

/**
 * Highest (Emergency) level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logEmergency:@"This line will be logged with Emergency Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogEmergency C-style API counterpart
 */
-(void) logEmergency:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Alert level logger API.  Deprecated, use the instance method instead.
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logAlert:@"This line will be logged with Alert Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged, deprecated (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogAlert C-style API counterpart
 */			
+(void) logAlert:(NSString*) message_in withInfo:(NSString*) info_in DEPRECATED_ATTRIBUTE;

/**
 * Alert level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logAlert:@"This line will be logged with Alert Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogAlert C-style API counterpart
 */
-(void) logAlert:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Critical level logger API.  Deprecated, use the instance method instead.
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logCritical:@"This line will be logged with Critical Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged, deprecated (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogCritical C-style API counterpart
 */	
+(void) logCritical:(NSString*) message_in withInfo:(NSString*) info_in DEPRECATED_ATTRIBUTE;

/**
 * Critical level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logCritical:@"This line will be logged with Critical Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogCritical C-style API counterpart
 */
-(void) logCritical:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Error level logger API.  Deprecated, use the instance method instead.
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logError:@"This line will be logged with Error Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged, deprecated (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogError C-style API counterpart
 */		
+(void) logError:(NSString*) message_in withInfo:(NSString*) info_in DEPRECATED_ATTRIBUTE;

/**
 * Error level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logError:@"This line will be logged with Error Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogError C-style API counterpart
 */
-(void) logError:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Warning level logger API.  Deprecated, use the instance method instead.
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logWarning:@"This line will be logged with Warning Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged, deprecated (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogWarning C-style API counterpart
 */		
+(void) logWarning:(NSString*) message_in withInfo:(NSString*) info_in DEPRECATED_ATTRIBUTE;	

/**
 * Warning level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logWarning:@"This line will be logged with Warning Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in the message to be logged
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogWarning C-style API counterpart
 */
-(void) logWarning:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Notice level logger API.  Deprecated, use the instance method instead.
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logNotice:@"This line will be logged with Notice Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged, deprecated (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogNotice C-style API counterpart
 */		
+(void) logNotice:(NSString*) message_in withInfo:(NSString*) info_in DEPRECATED_ATTRIBUTE;

/**
 * Notice level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logNotice:@"This line will be logged with Notice Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogNotice C-style API counterpart
 */
-(void) logNotice:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Information level logger API.  Deprecated, use the instance method instead.
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logInfo:@"This line will be logged with Info Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged, deprecated (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogInfo C-style API counterpart
 */		
+(void) logInfo:(NSString*) message_in withInfo:(NSString*) info_in DEPRECATED_ATTRIBUTE;

/**
 * Information level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logInfo:@"This line will be logged with Info Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogInfo C-style API counterpart
 */
-(void) logInfo:(NSString*) message_in withInfo:(NSString*) info_in;

/**
 * Debug level logger API.  Deprecated, use the instance method instead.
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logDebug:@"This line will be logged with Debug Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged, deprecated (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogDebug C-style API counterpart
 */		
+(void) logDebug:(NSString*) message_in withInfo:(NSString*) info_in DEPRECATED_ATTRIBUTE;

/**
 * Debug level logger API
 * <pre>
 * Sample usage:
 * <code>
 * [MAFLogger logDebug:@"This line will be logged with Debug Logging level" withInfo:@"Additional information"];
 * </code>
 * </pre>
 * @param message_in: the message to be logged
 * @param info_in: additional info to be logged (i.e. __FILE__, __PRETTY_FUNCTION__, __LINE__)
 * @remark the message will be logged along with further data such as the timestamp, file and method name, and the line number from where the API has been invoked
 * @discussion this is the Obj-C logger API; one may choose to rather invoke the C-style counterpart (less typing)
 * @see MAFLogDebug C-style API counterpart
 */
-(void) logDebug:(NSString*) message_in withInfo:(NSString*) info_in;

#pragma mark -
#pragma mark Retrieving Logs

/**
 * Returns all log entries with the given logging level.  Deprecated, use the instance method instead.
 * <pre>
 * Sample usage:
 * <code>
 * NSArray* messages = [MAFLogger retrieveLogsWithLevel:MAFWarningLoggingLevel];
 * </code>
 * </pre>  
 * @param level_in: log level, deprecated
 */
+(NSArray*) retrieveLogsWithLevel:(MAFLoggingLevel)level_in DEPRECATED_ATTRIBUTE;

/**
 * Returns all log entries with the given logging level
 * <pre>
 * Sample usage:
 * <code>
 * NSArray* messages = [MAFLogger retrieveLogsWithLevel:MAFWarningLoggingLevel];
 * </code>
 * </pre>
 * @param level_in: log level
 */
-(NSArray*) retrieveLogsWithLevel:(MAFLoggingLevel)level_in;

#pragma mark -
#pragma mark NSError Helper Methods

/**
 * This method helps logging NSError structure with any number of NSUnderlyingError.  Deprecated, use the instance method instead.
 *
 * @usage: [MAFLogger logError fullStack:NO rootCause:NO]; will only print the structure of the recieved NSError Object
 *
 *         [MAFLogger logError fullStack:YES rootCause:NO]; will print the full linked chain of underlying errors and the top most error
 *
 *         [MAFLogger logError fullStack:NO rootCause:YES]; will print the structure of the recieved NSError Object and 
 *                                                          the lovest Underlying Error object
 *         [MAFLogger logError fullStack:YES rootCause:YES];will print the full linked chain of underlying errors and the root cause 
 *                                                          underlying NSError structure after each other.
 *
 * @param error: NSError Object you want to log
 * @param fullStack: BOOL Whether to log the full stack of the NSError Chain or just the top error structure.
 * @param rootCause: BOOL Whether to print the deepest NSUnderlyingError, deprecated
 *
 */
+(void) logError:(NSError*) error fullStack:(BOOL) fullStack rootCause:(BOOL) rootCause DEPRECATED_ATTRIBUTE;

/**
 * This method helps logging NSError structure with any number of NSUnderlyingError
 *
 * @usage: [MAFLogger logError fullStack:NO rootCause:NO]; will only print the structure of the recieved NSError Object
 *
 *         [MAFLogger logError fullStack:YES rootCause:NO]; will print the full linked chain of underlying errors and the top most error
 *
 *         [MAFLogger logError fullStack:NO rootCause:YES]; will print the structure of the recieved NSError Object and
 *                                                          the lovest Underlying Error object
 *         [MAFLogger logError fullStack:YES rootCause:YES];will print the full linked chain of underlying errors and the root cause
 *                                                          underlying NSError structure after each other.
 *
 * @param error: NSError Object you want to log
 * @param fullStack: BOOL Whether to log the full stack of the NSError Chain or just the top error structure.
 * @param rootCause: BOOL Whether to print the deepest NSUnderlyingError
 *
 */
-(void) logError:(NSError*) error fullStack:(BOOL) fullStack rootCause:(BOOL) rootCause;

@end
