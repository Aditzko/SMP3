//
//  ODataError.h
//  Parser
//
//  Created by Farkas, Zoltan on 05/04/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
  * Stores the parsed data fields of OData error payloads.
  * Example error payload:
  * <?xml version="1.0" encoding="utf-8" standalone="yes"?>
  * <error xmlns="http://schemas.microsoft.com/ado/2007/08/dataservices/metadata">
  *    <code></code>
  *    <message xml:lang="en-US">Resource not found for the segment 'Titles'.</message>
  * </error>
  * The stored values after parsing the example payload are:
  * code = @""
  * message = @"Resource not found for the segment 'Titles'."
  * language = @"en-US"
  */

@interface ODataError : NSObject {
	NSString*	m_ErrorCode;
	NSString*	m_Message;
	NSString*	m_Language;
}

@property (nonatomic, retain, getter=getErrorCode, setter=setErrorCode:) NSString* errorCode;
@property (nonatomic, retain, getter=getMessage, setter=setMessage:) NSString* message;
@property (nonatomic, retain, getter=getLanguage, setter=setLanguage:) NSString* language;

-(id) init;

@end