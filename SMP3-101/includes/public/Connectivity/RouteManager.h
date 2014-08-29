//
//  RouteManager.h
//  SDMConnectivity
//
//  Created by Chug, Satvindar on 1/8/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMHttpRequest.h"

/**
 * @internal
 */
@interface CookieJar : NSObject 

-(void)setCookie:(id<SDMRequesting>)request;
-(void)storeCookie:(id<SDMRequesting>)response;
-(void)resetCookie;

@end

/**
 * @internal
 */
@interface SUPRoute : NSObject {
    
    NSString *m_domain;
    NSString *m_securityConfig;
    NSString *m_appConnectionId;
    NSString *m_supHostPort;
    NSString *m_realm;
    NSString *m_authSchema;
    
    SecIdentityRef m_secRefID;
    
    NSDictionary *m_authHeaderNwEdge;
    CookieJar *m_cookieJar;
}

@property(nonatomic,retain) NSString *m_domain;
@property(nonatomic,retain) NSString *m_securityConfig;
@property(nonatomic,retain) NSString *m_appConnectionId;
@property(nonatomic,retain) NSString *m_supHostPort;
@property(nonatomic,retain) NSString *m_realm;
@property(nonatomic,retain) NSString *m_authSchema;
@property(nonatomic,retain) CookieJar *m_cookieJar;

@property(nonatomic,retain)  NSDictionary *m_authHeaderNwEdge;

-(void)addHeaders:(id<SDMRequesting>)request;


////For mutual SSL
-(void)setClientCertificateFromRoute:(id<SDMRequesting>)request;
-(void)setSecurityIdenRef:(SecIdentityRef)p_securityIdenRef;


@end

/**
 * @internal
 */
@interface RouteManager : NSObject

+(SUPRoute*)getRoute:(NSString*)url;


@end
