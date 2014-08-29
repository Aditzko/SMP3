//
//  SDMParserException.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 05/05/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSException.h>

/**
 * @deprecated 
 *	SDMParserException
 */
__attribute((deprecated("Use ODataParserException instead")))
@interface SDMParserException : NSException {
}

@property (nonatomic, readonly, retain, getter=getError) NSString* error;
@property (nonatomic, readonly, retain, getter=getDetailedError) NSString* detailedError;
@property (nonatomic, readonly, assign, getter=getStatusCode) NSInteger statusCode;

-(id) init;
-(id) initWithError:(NSString*)error_in detailedError:(NSString*)details_in;
-(id) initWithError:(NSString*)error_in detailedError:(NSString*)details_in statusCode:(NSInteger)statusCode_in;

@end
