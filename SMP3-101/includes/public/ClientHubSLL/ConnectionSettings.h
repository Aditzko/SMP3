//
//  ConnectionSettings.h
//  ClientHub
//
//  Created by Phaneesh L N on 25/04/13.
//  Copyright (c) 2013 Phaneesh L N. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 * Consists of connection setting details as a number of properties.
 */
@interface ConnectionSettings : NSObject

/*
 * The host property.
 * @param None
 * @return host
 */
@property(nonatomic, retain) NSString* host;
/*
 * The port property.
 * @param None
 * @return port
 */
@property(nonatomic, retain) NSString* port;
/*
 * The farm property.
 * @param None
 * @return farm
 */
@property(nonatomic, retain) NSString* farm;
/*
 * The domain property.
 * @param None
 * @return domain
 */
@property(nonatomic, retain) NSString* domain;
/*
 * The isHttps property indicates if the connection is http or https.
 * @param None
 * @return isHTTPS.
 */
@property(nonatomic, assign) BOOL isHTTPS;
/*
 * The rsUrlSuffix property.
 * @param None
 * @return rsUrlSuffix.
 */
@property(nonatomic, retain) NSString* rsUrlSuffix;
/*
 * The security configuration property.
 * @param None
 * @return securityConfig
 */
@property(nonatomic, retain) NSString* securityConfig;

@end
