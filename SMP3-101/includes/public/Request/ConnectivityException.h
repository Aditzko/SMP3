//
//  ConnectivityException.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSException.h>

/**
 * @brief Exception propagated from the library
 * @remark clients should handle this when calling the synchronous library APIs
 */
@interface ConnectivityException : NSException {
	NSString		*m_error;
    NSString		*m_detailedError;
    NSInteger		m_statusCode;
}

@property (nonatomic,	retain,	getter=getError,		setter=setError:			) NSString* error;
@property (nonatomic,	retain,	getter=getDetailedError,setter=setDetailedError:	) NSString* detailedError;
@property (nonatomic,	assign,	getter=getStatusCode,	setter=setStatusCode:       ) NSInteger statusCode;

-(id) init;
-(id) initWithError:(NSString *)error_in detailedError:(NSString *)details_in statusCode:(NSInteger)statusCode_in;

@end
