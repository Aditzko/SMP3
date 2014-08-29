//
//  SeedingAPISynchronous.h
//  AfariaSLL
//
//  Created by Corey Mayo on 7/18/11.
//  Copyright 2011 Sybase. All rights reserved.
//

#import <Foundation/Foundation.h>

// bundle identifier used by afaria client
// may vary in development versions
#define AFARIA_BUNDLE_ID @"com.sybase.afariaClient"

// Return codes from seed data and certificate APIs
#define kSeedDataAvailable               1
#define kCertificateAvailable            2
#define kSeedDataAlreadyUpToDate         3

#define kAfariaSettingsRequested         4
#define kAfariaClientNotInstalled        5
#define kSeedDataUnavailable             6
#define kCertificateUnavailable          7
#define kAuthenticationRequired          8
#define kUrlNotFromAfaria                9
#define kCertProvisioningNotImplemented 10
#define kLibraryConfigured              11
#define kUninitialized                  12
#define kUserNotFound                   13
@interface SeedingAPISynchronous : NSObject {
    
}


@property (nonatomic, retain) NSURLCredential *credentials;
//when a third party application is launched for the first time initializeLibrary will be called to get the package server url by passing the NULL value, once this function is called there will be a context switch to afaria client, client will return package server url.
//From the third party applications "OpenURL" function we again call "initializeLibrary" to persist the url returned from the afaria client.
+(NSInteger) initializeLibrary:(NSURL *) url inUrlScheme:(NSString *)inurlscheme;


// Retrieve certificate from Afaria server

//kUnitiatized - package server url is not presisted.
//kCertificateUnavailable - certificate is not available.
//kCertificateAvailable - certificate is available.
+(NSInteger) retrieveUserCertificate:(SecKeyRef)privateKey andPublicKey:(SecKeyRef)publicKey andUserName:(NSString *)userName andPassword:(NSString *) password andChallenge:(NSString *)challengeCode outCertificate:(SecCertificateRef *) userCertificate;

// For each of these methods, the credentials paramet

// Retrieve seed data from Afaria server
// If Afaria settings are available it will used to connect to server
// If not, the settings will be requested from Afaria client and kAfariaSettingsRequested will be returned
// If seed data file is successfully retrieved from server it will be written to a file in application sandbox and file name is returned in seedFile parameter
// Return values:
// kSeedDataAvailable - Seed data is available in seedFile
// kSeedDataUnavailable - Seed data is unable to load either due to network problems or it isn't available on the server
// kAfariaClientNotInstalled - Install Afaria client and try again
// kAfariaSettingsRequested - Afaria information is requested from Afaria client. Use retrieveSeedDataWithUrl:InFile:withCredentials API when the URL is passed by Afaria client
+ (NSInteger)retrieveSeedData:(NSString *)urlScheme InFile:(NSMutableString *)seedFile withCredentials:(NSURLCredential *)credentials;

// Use this API to retrieve seed data from Afaria server when seed info is passed in an url from Afaria client
// If seed data file is successfully retrieved from server it will be written to a file in application sandbox and file name is returned in seedFile parameter
// Return values:
// kSeedDataAvailable - Seed data available in seedFile
// kSeedDataUnavailable - Seed data is unable to load either due to network problems or it isn't available on the server
// kUrlNotFromAfaria - The URL parameters did not match what the library was expecting
+ (NSInteger)retrieveSeedDataWithUrl:(NSURL *)url InFile:(NSMutableString *)seedFile withCredentials:(NSURLCredential *)credentials;



// Retrieve seed data from Afaria server only if an update is available
// If Afaria settings are available it will used to connect to server
// If not, the settings will be requested from Afaria client and kAfariaSettingsRequested will be returned
// If seed data file is successfully retrieved from server it will be written to a file in application sandbox and file name is returned in seedFile parameter
// Return values:
// kSeedDataAvailable - Seed data is available in seedFile
// kSeedDataAlreadyUpToDate - The seed data downloaded is already up to date
// kSeedDataUnavailable - Seed data is unable to load either due to network problems or it isn't available on the server
// kAfariaClientNotInstalled - Install Afaria client and try again
// kAfariaSettingsRequested - Afaria information is requested from Afaria client. Use retrieveSeedDataWithUrl:InFile:withCredentials API when the URL is passed by Afaria client
+ (NSInteger)updateSeedData:(NSString *)urlScheme InFile:(NSMutableString *)seedFile withCredentials:(NSURLCredential *)credentials;

// Use this API to retrieve seed data from Afaria server when seed info is passed in an url from Afaria client
// Data will be downloaded only if an update is available
// If seed data file is successfully retrieved from server it will be written to a file in application sandbox and file name is returned in seedFile parameter
// Return values:
// kSeedDataAvailable - Seed data available in seedFile
// kSeedDataAlreadyUpToDate - The seed data downloaded is already up to date
// kSeedDataUnavailable - Seed data is unable to load either due to network problems or it isn't available on the server
// kUrlNotFromAfaria - The URL parameters did not match what the library was expecting
+ (NSInteger)updateSeedDataWithUrl:(NSURL *)url InFile:(NSMutableString *)seedFile withCredentials:(NSURLCredential *)credentials;


// Retrieve certificate from Afaria server
// If Afaria settings are available it will used to connect to server
// If not, the settings will be requested from Afaria client and kAfariaSettingsRequested will be returned
// If certificate is successfully retrieved from server it will be returned in certData parameter
// Return values:
// kAuthenticationRequired - User authenication is enabled on server
// kCertificateAvailable - Certificate is available in seedFile
// kCertificateUnavailable - Certificate is not available due to server misconfiguration or network issues
// kAfariaClientNotInstalled - Install Afaria client and try again
// kAfariaSettingsRequested - Afaria information is requested from Afaria client. Use retrieveCertificateWithUrl:forPublicKey:InData: API when the URL is passed by Afaria client
// kCertProvisioningNotImplemented - Feature is implemented on devices only, not simulator
+ (NSInteger)retrieveCertificateWithPrivateKey:(SecKeyRef)privateKey andPublicKey:(SecKeyRef)publicKey andCommonName:(NSString *)commonName andChallenge:(NSString *)challengeCode forUrlScheme:(NSString *)urlScheme inCertificate:(SecCertificateRef *)certificate;
// Same return values as sibling API call, but includes additional entrires to supply authentication credentials.
+ (NSInteger)retrieveCertificateWithPrivateKey:(SecKeyRef)privateKey andPublicKey:(SecKeyRef)publicKey andUserName:(NSString *)useName andPassword:(NSString *)password andCommonName:(NSString *)commonName andChallenge:(NSString *)challengeCode forUrlScheme:(NSString *)urlScheme inCertificate:(SecCertificateRef *)certificate;


// Use this API to retrieve certificate from Afaria server when certificate info is passed in an url from Afaria client
// If this URL is not from Afaria client kUrlNotFromAfaria will be returned 
// If certificate is successfully retrieved from server it will be returned in certData parameter
// Return values:
// kAuthenticationRequired - User authenication is enabled on server
// kCertificateAvailable - Seed data available in seedFile
// kCertificateUnavailable - Certificate is not available due to server misconfiguration or network issues
// kUrlNotFromAfaria - The URL parameters did not match what the library was expecting
// kCertProvisioningNotImplemented - Feature is implemented on devices only, not simulator
+ (NSInteger)retrieveCertificateWithUrl:(NSURL *)url andPrivateKey:(SecKeyRef)privateKey andPublicKey:(SecKeyRef)publicKey andCommonName:(NSString *)commonName andChallenge:(NSString *)challengeCode inCertificate:(SecCertificateRef *)certificate;
// Same return values as sibling API call, but includes additional entrires to supply authentication credentials.
+ (NSInteger)retrieveCertificateWithUrl:(NSURL *)url andPrivateKey:(SecKeyRef)privateKey andPublicKey:(SecKeyRef)publicKey andUserName:(NSString *)useName andPassword:(NSString *)password andCommonName:(NSString *)commonName andChallenge:(NSString *)challengeCode inCertificate:(SecCertificateRef *)certificate;


// Use this method to force an openUrl call to Afaria to retrieve a configuration url
// Return values:
// kAfariaClientNotInstalled - Install Afaria client and try again
// kAfariaSettingsRequested - Afaria information is requested from Afaria client.
+ (NSInteger)getAfariaServerSettingsForUrlScheme:(NSString *)urlScheme;


// Use this method to configure the library without performing any additional actions.
// Return values:
// kUrlNotFromAfaria - The URL parameters did not match what the library was expecting
// kLibraryConfigured - The library was successfully configured
+ (NSInteger)setAfariaServerSettings:(NSURL *)url;


// Determines whether the library has already received afaria server settings
+ (BOOL)areSettingsConfigured;


// Use this API to clear Afaria settings
// Next call to retrieveSeedData or retrieveCertificate will fetch new settings from Afaria client
+ (void)clearSettings;

@end
