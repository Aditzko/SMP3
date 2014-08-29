//
//  Credentials.h
//  ClientHubSLL
//
//  Created by Phaneesh L N on 5/21/13.
//  Copyright (c) 2013 Phaneesh L N. All rights reserved.
//

/*
 * Consists of credential details as a number of properties.
 */

#import <Foundation/Foundation.h>

@interface UserCredentials : NSObject

/*
 * The backend username property.
 * @param None
 * @return username
 */
@property(nonatomic, retain) NSString* username;
/*
 * The backend password property.
 * @param None
 * @return password
 */
@property(nonatomic, retain) NSString* password;
/*
 * The base64 encoded certificate property.
 * @param None
 * @return certificate
 */
@property(nonatomic, retain) NSString* certificate;
/*
 * The backend SSOToken property.
 * @param None
 * @return SSOToken
 */
@property(nonatomic, retain) NSString* SSOToken;
/*
 * The CredentialType property.
 * @param None
 * @return CredentialType.
 */
@property(nonatomic, retain) NSString* CredentialType;

@end
