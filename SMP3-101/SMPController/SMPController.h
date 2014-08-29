//
//  SMPController.h
//  SMP3-101
//
//  Created by Adalbert Kitzig on 26.08.14.
//  Copyright (c) 2014 PlaceWorkers. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Request.h"
#import "SMPClientConnection.h"
#import "SMPUserManager.h"
#import "SMPDelegate.h"

@interface SMPController : NSObject <SMPUserManagerDelegate, RequestDelegate>

// We have to have a delegate to callback to.
@property (strong, nonatomic) id<smpDelegate> delegate;

// An object representing our connection to the SMP server.
@property (strong, nonatomic) SMPClientConnection *clientConn;

// Username to access the server
@property (strong, nonatomic) NSString *username;

// Password to access the server
@property (strong, nonatomic) NSString *password;

@property (strong, nonatomic) NSString *smpServer;      // hostname for SMP Server
@property (strong, nonatomic) NSString *smpPort;        // port for accessing the SMP server (usually 8080)
@property (strong, nonatomic) NSString *smpSecProvider; // Name of the security provides on the SMP server.
@property (strong, nonatomic) NSString *smpAppId;       // The unique application ID configured on the SMP server.

// Hostname of our Odata endpoint (could be retrieved from the server during registration).
@property (strong, nonatomic) NSString *odataURL;
@property (strong, nonatomic) NSString *entityName;     // Name of the OData entity we are going to access.

// Startup SMP engine and register our user.
- (NSError *)initialiseSMP;

// Once registered we can retrieve the data.
- (void)beginDataRetrieval;

@end