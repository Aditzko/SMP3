//
//  SDMConnectivityException.h
//  SDMConnectivity
//
//  Created by Karoly Nyisztor on 4/6/11.
//  Copyright 2010 - 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSException.h>

/**
 * @deprecated
 * Exception propagated from the library
 * @remark clients should handle this when calling the synchronous library APIs
 */
__attribute((deprecated("Use ConnectivityException instead")))
@interface SDMConnectivityException : NSException {
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
