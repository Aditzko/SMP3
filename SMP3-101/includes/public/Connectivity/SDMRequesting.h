//
//  SDMRequesting.h
//  SDMConnectivity library
//
//  Created by Nyisztor Karoly on 5/19/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import "SDMCacheDelegate.h"

#ifndef USE_ODP_INTERFACE
__attribute((deprecated("Use EetagMatchType instead")))
typedef enum {
    
    EtagIfMatch,
    EtagIfNoneMatch,
    EtagIfRange
} EtagMatchType;

#endif

/**
 * @deprecated
 * Defines the connectivity APIs
 * Protocol to be adapted by Connectivity classes
 * @remark Clients might consider using the SDMHttpRequest or SUPRequest
 * <pre>
 * Features:
 * <ul>
 * <li> Synchronous and asynchronous execution
 * <li> Continues downloading and uploading when app is sent to the background (iOS 4.0+ only)
 * <li> Secure connection (iOS 4.0+ only)
 * <li> Progress tracking (optional, not supported by the SUP implementation)
 * </ul>
 * </pre>
 * @discussion The SUP implementation does only support a subset of the functionality provided by SDMHttpRequest, hence only a few APIs are makrked as required
 */
__attribute((deprecated("Use Requesting instead")))
@protocol SDMRequesting <NSObject>

#pragma mark -
#pragma mark Required APIs and Accessors

/* ------------------------------------------------------------------------------------------------------------------------------ */
/* ---------------------------------------------------------- REQUIRED ---------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------ */

@required

#pragma mark -
#pragma mark Required Accessors

// The bare minimum accessor set which should be common for both SUPRequest and SDMHttpRequest
@property (retain) NSString* username; ///< for basic auth
@property (retain) NSString* password; ///< for basic auth
@property (assign, nonatomic) id delegate; ///< client delegate
@property (retain, nonatomic) id queue;	///< NSOperationQueue (our thread pool used for parallel execution of requests)
@property (assign) BOOL shouldAutosetLanguage; ///< controls whether the preferred language has to be passed along the request's header; defaults to YES

#pragma mark -
#pragma mark Initialization and deallocation

/**
 * Should be an HTTP or HTTPS url, may include username and password if appropriate
 */
- (id)initWithURL:(NSURL *)newURL;

/**
 * Convenience constructor with url. Recommend the use against @see initWithURL.
 * <pre>
 * Usage
 * <code>
 * id<SDMRequesting> m_Request = [SDMRequestBuilder requestWithURL:url];
 * ...
 * </code>
 * </pre>
 */

+ (id)requestWithURL:(NSURL *)newURL;
/**
 * Convenience constructor with url and cache. ODPRequest will not have a download cache
 */
+ (id)requestWithURL:(NSURL *)newURL usingCache:(id <SDMCacheDelegate>)cache;
/**
 * Convenience constructor with url, cache and cache policy. ODPRequest will not have a download cache
 */
+ (id)requestWithURL:(NSURL *)newURL usingCache:(id <SDMCacheDelegate>)cache andCachePolicy:(CachePolicy)policy;

/**
 * Sets the maximum number of SDMHTTPRequest threads which can run at once
 * @throws SDMConnectivityException if max allowed parallel thread is exceeded
 */
+ (void) setMaxConcurrentHTTPRequestCount:(const unsigned char) cnt;
/**
 * Returns the maximum number of SDMHTTPRequest threads which can be executed in parallel
 */
+ (NSInteger) getMaxConcurrentHTTPRequestCount;

#pragma mark -
#pragma mark Request Setup

/**
 * Adds a custom header to the request.
 * @see buildRequestHeaders
 * <pre>
 * Usage
 * <code>
 * id<SDMRequesting> m_Request = [SDMRequestBuilder requestWithURL:url];
 * [m_Request addRequestHeader:key value:value];
 * ...
 * </code>
 * </pre>
 */

- (void)addRequestHeader:(NSString *)header value:(NSString *)value;

/**
 * Called during buildRequestHeaders and after a redirect to create a cookie header from request cookies and the global store
 * <pre>
 * Usage
 * <code>
 * id<SDMRequesting> m_Request = [SDMRequestBuilder requestWithURL:url];
 * [m_Request applyCookieHeader];
 * ...
 * </code>
 * </pre>
 */
- (void)applyCookieHeader;

/**
 * Populates the request headers dictionary. Called before a request is started, or by a HEAD request that needs to borrow them
 */
- (void)buildRequestHeaders;

/*
 * Used to apply authorization header to a request before it is sent (when shouldPresentCredentialsBeforeChallenge is YES)
 */
- (void)applyAuthorizationHeader;

/**
 * Adds data to the post body. Will append to postBody when shouldStreamPostDataFromDisk is false, or write to postBodyWriteStream when true
 */

/**
 * Adds data to the post body. Will append to postBody when shouldStreamPostDataFromDisk is false, or write to postBodyWriteStream when true
 * <pre>
 * Usage
 * <code>
 * id<SDMRequesting> m_Request = [SDMRequestBuilder requestWithURL:url];
 * NSData* postBody = <data>;
 * [m_Request appendPostData:data];
 * ...
 * </code>
 * </pre>
 */

- (void)appendPostData:(NSData *)data;
/**
 * Adds data to the post body from a file. Will append to postBody when shouldStreamPostDataFromDisk is false, or write to postBodyWriteStream when true
 */
- (void)appendPostDataFromFile:(NSString *)file;

/**
 * Creates the post body
 */
- (void)buildPostBody;

/**
 * Add If-Match or If-None-Match or If-Range header* <pre>
 * Usage
 * <code>
 * id<SDMRequesting> m_Request = [SDMRequestBuilder requestWithURL:url];
 * [m_Request setEtag:@"value" withMatchType:EtagIfMatch];
 * ...
 * </code>
 * </pre>
 */
- (void)setEtag:(NSString *)etag withMatchType:(EtagMatchType) matchType;

/**
 * Enable XSRF support for the session of the application. Need to be set again in case of application restart
 * Usage
 * <code>
 * [SDMRequestBuilder enableXCSRF:YES];
 * id<SDMRequesting> m_Request = [SDMRequestBuilder requestWithURL:url];
 * ...
 * </code>
 * </pre>
 */
+ (void)enableXCSRF:(BOOL) enable;

#pragma mark -
#pragma mark Request Payload
/**
 * Returns the contents of the result as an NSString (not appropriate for binary data - used responseData instead)
 * @see responseData
 * Usage
 * <code>
 * id<SDMRequesting> m_Request = [SDMRequestBuilder requestWithURL:url];
 * ...
 * [m_Request startSynchronous];
 * NSString* responseAsString = [m_Request responseString];
 * ...
 * </code>
 * </pre>
 */

- (NSString *)responseString;

/**
 * Response data, automatically uncompressed where appropriate
 * @see responseString
 * Usage
 * <code>
 * id<SDMRequesting> m_Request = [SDMRequestBuilder requestWithURL:url];
 * ...
 * [m_Request startSynchronous];
 * NSData* responseAsData = [m_Request responseString];
 * ...
 * </code>
 * </pre>
 */

- (NSData *)responseData;

/**
 * Returns true if the response was gzip compressed
 * Usage
 * <code>
 * id<SDMRequesting> m_Request = [SDMRequestBuilder requestWithURL:url];
 * ...
 * [m_Request startSynchronous];
 * If([m_Request isResponseCompressed])
 * ...// Further operations
 * </code>
 * </pre>
 */

- (BOOL)isResponseCompressed;

#pragma mark -
#pragma mark Request execution

/**
 * Runs a request synchronously, and returns control when the request completes or fails
 * Usage
 * <code>
 * id<SDMRequesting> m_Request = [SDMRequestBuilder requestWithURL:url];
 * ...
 * [m_Request startSynchronous];
 * </code>
 * </pre>
 */

- (void)startSynchronous;

/**
 */

/**
 * Runs request in the background
 * The client should register callback selector in order to get notified about various events (failure, completion, etc.)
 * Usage
 * <code>
 * id<SDMRequesting> m_Request = [SDMRequestBuilder requestWithURL:url];
 * [m_Request setDelegate:self];
 * [m_Request setDidFinishSelector:@selector(serviceDocFetchComplete:)];
 * [m_Request setDidFailSelector:@selector(serviceDocFetchFailed:)];
 * [m_Request startAsynchronous];
 * </code>
 * </pre>
 */
- (void)startAsynchronous;

#pragma mark -
#pragma mark Assignable Selectors
/**
 * Clients can chose to register their custom selectors to be invoked
 * @remark Consider implementing the SDMHttpRequestDelegate as an alternative to this approach
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidStartSelector:@selector(serviceDocFetchStarted:)];
 * ...
 * </code>
 * </pre>
 */
@property (assign) SEL didStartSelector;
/**
 * Clients can chose to register their custom selectors to be invoked
 * @remark Consider implementing the SDMHttpRequestDelegate as an alternative to this approach
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidFinishSelector:@selector(serviceDocFetchComplete:)];
 * ...
 * </code>
 * </pre>
 */
@property (assign) SEL didFinishSelector;
/**
 * Clients can chose to register their custom selectors to be invoked
 * @remark Consider implementing the SDMHttpRequestDelegate as an alternative to this approach
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidFailSelector:@selector(serviceDocFetchFailed:)];
 * ...
 * </code>
 * </pre>
 */
@property (assign) SEL didFailSelector;
/**
 * Clients can chose to register their custom selectors to be invoked
 * Default delegate method invoked when incoming data is available.
 * @remark Implement this delegate only if you want to manually process all incoming data yourself (usually not required). This means that responseData / responseString are ignored
 *
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidReceiveDataSelector:@selector(dataArrived:)];
 * ...
 * </code>
 * </pre>
 */
@property (assign) SEL didReceiveDataSelector;
/**
 * Clients can chose to register their custom selectors to be invoked
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidReceiveResponseHeadersSelector:@selector(headersReceived:)];
 * ...
 * </code>
 * </pre>
 */
@property (assign) SEL didReceiveResponseHeadersSelector;

#pragma  mark Auth Challenge Selector
/**
 * Clients can chose to register their custom selectors to be invoked
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidReceiveAuthChallengeSelector:@selector(authenticationNeededForRequest:)];
 * ...
 * </code>
 * </pre>
 */
@property(assign) SEL didReceiveAuthChallengeSelector;

#pragma mark -
#pragma mark Optional APIs

/* ------------------------------------------------------------------------------------------------------------------------------ */
/* ----------------------------------------------------- OPTIONAL (for SUP) ----------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------ */
// !!! SUPRequest implementation might implement nop stubs or let the runtime throw a DoesNotRespondToSelector exception
// if clients call these APIs / Accessors on a SUPRequest instance

@optional

#pragma mark -
#pragma mark HEAD request

/**
 * Used by NetworkQueue to create a HEAD request appropriate for this request with the same headers (though you can use it yourself)
 */
- (id<SDMRequesting>)HEADRequest;

#pragma mark -
#pragma mark Upload / Download progress

/**
 * Updates the progress delegates
 * @remark Used by SDMNetworkQueue, clients should not invoke them directly
 */
- (void)updateProgressIndicators;

/**
 * Updates upload progress (notifies the queue and/or uploadProgressDelegate of this request)
 */
- (void)updateUploadProgress;

/**
 * Updates download progress (notifies the queue and/or downloadProgressDelegate of this request)
 */
- (void)updateDownloadProgress;

/**
 * Called when authorization is needed, as we only find out we don't have permission to something when the upload is complete
 */
- (void)removeUploadProgressSoFar;

/**
 * Called when we get a content-length header and shouldResetDownloadProgress is true
 */
- (void)incrementDownloadSizeBy:(long long)length;

/**
 * Called when a request starts and shouldResetUploadProgress is true
 * Also called (with a negative length) to remove the size of the underlying buffer used for uploading
 */
- (void)incrementUploadSizeBy:(long long)length;

/**
 * Helper method for interacting with progress indicators to abstract the details of different APIS (NSProgressIndicator and UIProgressView)
 */
+ (void)updateProgressIndicator:(id *)indicator withProgress:(unsigned long long)progress ofTotal:(unsigned long long)total;

/**
 * Helper method used for performing invocations on the main thread (used for progress)
 */
+ (void)performSelector:(SEL)selector onTarget:(id *)target withObject:(id)object amount:(void *)amount;


#pragma mark -
#pragma mark Http Authentication

/**
 * Wakes up (unlocks) the request thread so it can resume the request
 * @remark Should be called by delegates when they have populated the authentication information after an authentication challenge
 */
- (void)retryUsingSuppliedCredentials;

//! Should be called by delegates when they wish to cancel authentication and stop
- (void)cancelAuthentication;
/**
 * Constructs a basic authentication header from the username and password supplied, and adds it to the request headers
 * Used when shouldPresentCredentialsBeforeChallenge is YES
 */
- (void)addBasicAuthenticationHeaderWithUsername:(NSString *)theUsername andPassword:(NSString *)thePassword;

#pragma mark -
#pragma mark CFnetwork Event Handlers
/**
 * Handles network events as they occur
 * @remark Called from ReadStreamClientCallBack when one of the events requested in NETWORK_EVENTS occurs
 */
- (void)handleNetworkEvent:(CFStreamEventType)type;

#pragma mark -
#pragma mark Request Failure Management

/**
 * Called when a request fails, and lets the delegate know via didFailSelector
 */
- (void)failWithError:(NSError *)theError;


#pragma mark -
#pragma mark Client Certificate Handling
//! Sets the identity reference (X.509 certificate + private key) for this request; used for secure connections
- (void)setClientCertificateIdentity:(SecIdentityRef)anIdentity;


#pragma mark
#pragma mark Keychain Storage

//! Saves credentials for this request to the keychain
- (void)saveCredentialsToKeychain:(NSDictionary *)newCredentials;

//! Saves host credentials to the keychain
+ (void)saveCredentials:(NSURLCredential *)credentials forHost:(NSString *)host port:(int)port protocol:(NSString *)protocol realm:(NSString *)realm;
//! Saves proxy credentials to the keychain
+ (void)saveCredentials:(NSURLCredential *)credentials forProxy:(NSString *)host port:(int)port realm:(NSString *)realm;

//! Returns host credentials from the keychain
+ (NSURLCredential *)savedCredentialsForHost:(NSString *)host port:(int)port protocol:(NSString *)protocol realm:(NSString *)realm;
//! Returns proxy credentials from the keychain
+ (NSURLCredential *)savedCredentialsForProxy:(NSString *)host port:(int)port protocol:(NSString *)protocol realm:(NSString *)realm;

//! Deletes host credentials from the keychain
+ (void)removeCredentialsForHost:(NSString *)host port:(int)port protocol:(NSString *)protocol realm:(NSString *)realm;
//! Deletes proxy credentials from the keychain
+ (void)removeCredentialsForProxy:(NSString *)host port:(int)port realm:(NSString *)realm;

#pragma mark -
#pragma mark Session Management

// Dump all session data (authentication and cookies)
+ (void)clearSession;

#pragma mark -
#pragma mark Reachability

//! Returns YES when an iPhone OS device is connected via WWAN, false when connected via WIFI or not connected
+ (BOOL)isNetworkReachableViaWWAN;

#pragma mark -
#pragma mark Concurrent Request Queue

//! Returns the shared queue
+ (NSOperationQueue *)sharedQueue;

#pragma mark -
#pragma mark Cache Management
/**
 * Configures a default download cache which applies for all requests
 * @see SDMDownloadCache
 */
+ (void)setDefaultCache:(id <SDMCacheDelegate>)cache;
/**
 * Returns the default download cache or nil if none set at class level
 */
+ (id <SDMCacheDelegate>)defaultCache;

#pragma mark -
#pragma mark Network Activity
/**
 * Indicates whether there are running requests
 * @return NO, if no requests are currently executing
 */
+ (BOOL)isNetworkInUse;
/**
 * Controls whether the request should take over updating the network activity indicator
 * @remark enabled by default
 */
+ (void)setShouldUpdateNetworkActivityIndicator:(BOOL)shouldUpdate;

//! Shows the network activity spinner
+ (void)showNetworkActivityIndicator;

//! Hides the network activity spinner
+ (void)hideNetworkActivityIndicator;

#pragma mark -
#pragma mark Bandwidth Measurement / Throttling
/**
 * The maximum number of bytes ALL requests can send / receive in a second
 * This is a rough figure. The actual amount used will be slightly more, this does not include HTTP headers
 */
+ (unsigned long)maxBandwidthPerSecond;
//! Sets the maximum number of bytes ALL requests can send / receive in a second
+ (void)setMaxBandwidthPerSecond:(unsigned long)bytes;

//! Returns a rough average (for the last 5 seconds) of how much bandwidth is being used, in bytes
+ (unsigned long)averageBandwidthUsedPerSecond;
/**
 * Perform bandwidth throttling
 */
- (void)performThrottling;

//! Returns YES is bandwidth throttling is currently in use
+ (BOOL)isBandwidthThrottled;

//! Used internally to record bandwidth use, and by InputStreams when uploading. It's probably best if you don't mess with this.
+ (void)incrementBandwidthUsedInLastSecond:(unsigned long)bytes;

/**
 * SDMHTTPRequest can automatically turn throttling on and off as the connection type changes between WWAN and WiFi
 * Set to YES to automatically turn on throttling when WWAN is connected, and automatically turn it off when it isn't
 */
+ (void)setShouldThrottleBandwidthForWWAN:(BOOL)throttle;

//! Turns on throttling automatically when WWAN is connected using a custom limit, and turns it off automatically when it isn't
+ (void)throttleBandwidthForWWANUsingLimit:(unsigned long)limit;

//! Returns the maximum amount of data we can read as part of the current measurement period, and sleeps this thread if our allowance is used up
+ (unsigned long)maxUploadReadLength;

#pragma mark
#pragma mark Mime-type Detection

// Return the mime type for a file
+ (NSString *)mimeTypeForFileAtPath:(NSString *)path;

#pragma mark -
#pragma mark Secure File Storage
/**
 * Controls whether the download cache should store files using protection
 * @remark Enabled by default, applies to all instances; only available for builds targeting iOS 4.0 or above
 */
+(void) setProtectionEnabled:(BOOL)flag_in;

/**
 * Returns a attributes dictionary used for encrypted file storage or nil is file protection has been explicitely disabled
 * @remark File protection is enabled by default for builds targeting iOS4.0+; change using via SDMHttpRequest +setProtectionEnabled
 * @see setProtectionEnabled:
 */
+(NSDictionary*) fileProtectionAttributes;

/**
 * Returns a mask which determines whether the data should be stored in encrypted form
 * @remark Data will be stored in encrypted form by by default
 */
+(const NSDataWritingOptions) dataWritingOptions;

#pragma mark -
#pragma mark SAP Tracing and Business Transaction XML support
/**
 * Switches traceability status, the default is NO
 * @discussion If tracing is enabled, "SAP-PASSPORT" and "X-CorrelationID" headers are set and filled with values to enable SAP Passport functionality
 * data is gathered to compose the Business Transaction XML, which can be uploaded via SUPE2ETraceController sendXML API
 * @see SUPE2ETraceController
 */
- (void) enableTracing:(BOOL)value_in;

/**
 * Returns tracing status (default is NO)
 * @see setTracingEnabled:
 */
- (BOOL) isTracingEnabled;

/**
 * Posts the SAP E2E Trace XML to the given url
 */
-(void) sendE2ETraceXML:(NSURL*)toBaseURL;

#pragma mark -
#pragma mark Utility Methods

//! Base64 encodes the provided NSData*
+ (NSString*) base64forData:(NSData*)theData;
//! Decodes a base64 encoded string
+ (NSString*) decodeBase64:(NSString*)string_in;

//! Returns a date from a string in RFC1123 format
+ (NSDate *)dateFromRFC1123String:(NSString *)string;

#pragma mark -
#pragma mark Accessors

// !!! private properties
@property (retain, readonly) NSString* authenticationRealm;
@property (retain, readonly) NSString* proxyAuthenticationRealm;
@property (assign, readonly) BOOL complete;
@property (retain, readonly) NSArray* responseCookies;
@property (assign, readonly) int responseStatusCode; ///< HTTP status code, i.e. 200 = OK, 404 = Not found etc
@property (retain, readonly) NSString* responseStatusMessage;
@property (assign, readonly) unsigned long long contentLength;
@property (assign, readonly) unsigned long long partialDownloadSize;
@property (assign, readonly) unsigned long long totalBytesRead;
@property (assign, readonly) unsigned long long totalBytesSent;
@property (assign, readonly) int authenticationRetryCount;
@property (assign, readonly) int proxyAuthenticationRetryCount;
@property (assign, readonly) BOOL inProgress;
@property (assign, readonly) int retryCount;
@property (assign, readonly) BOOL connectionCanBeReused;
@property (retain, readonly) NSNumber* requestID;
@property (assign, readonly) BOOL didUseCachedResponse;
// private properties end


// moved to *required* section
//@property (retain) NSString* username;
//@property (retain) NSString* password;

@property (retain) NSString* domain;
@property (retain) NSString* proxyUsername;
@property (retain) NSString* proxyPassword;
@property (retain) NSString* proxyDomain;
@property (retain) NSString* proxyHost;
@property (assign) int proxyPort;
@property (retain) NSString* proxyType;
@property (retain) NSURL* url;
@property (retain) NSURL* originalURL;

// moved to *required* section
//@property (assign, nonatomic) id delegate;
//@property (retain, nonatomic) id queue;

@property (assign, nonatomic) id uploadProgressDelegate;
@property (assign, nonatomic) id downloadProgressDelegate;
@property (assign) BOOL useKeychainPersistence;
@property (assign) BOOL useSessionPersistence;
@property (retain) NSString* downloadDestinationPath;
@property (retain) NSString* temporaryFileDownloadPath;

@property (retain) NSError* error;
@property (retain) NSDictionary* responseHeaders;
@property (retain) NSMutableDictionary* requestHeaders;
@property (retain) NSMutableArray* requestCookies;
@property (assign) BOOL useCookiePersistence;
@property (retain) NSDictionary* requestCredentials;
@property (retain) NSDictionary* proxyCredentials;
@property (retain) NSMutableData* rawResponseData;
@property (assign) NSTimeInterval timeOutSeconds;
@property (retain) NSString* requestMethod;
@property (retain) NSMutableData* postBody;
@property (assign) unsigned long long postLength;
@property (assign) BOOL shouldResetDownloadProgress;
@property (assign) BOOL shouldResetUploadProgress;
@property (assign) id<SDMRequesting> mainRequest;
@property (assign) BOOL showAccurateProgress;
@property (assign) NSStringEncoding defaultResponseEncoding;
@property (assign, readonly) NSStringEncoding responseEncoding;
@property (assign) BOOL allowCompressedResponse;
@property (assign) BOOL allowResumeForFileDownloads;
@property (retain) NSDictionary *userInfo;
@property (retain) NSString *postBodyFilePath;
@property (assign) BOOL shouldStreamPostDataFromDisk;
@property (assign) BOOL didCreateTemporaryPostDataFile;
@property (assign) BOOL useHTTPVersionOne;
@property (assign) BOOL shouldRedirect;
@property (assign) BOOL validatesSecureCertificate;
@property (assign) BOOL shouldCompressRequestBody;
@property (retain) NSURL* PACurl;
@property (retain) NSString* authenticationScheme;
@property (retain) NSString* proxyAuthenticationScheme;
@property (assign) BOOL shouldPresentAuthenticationDialog;
@property (assign) BOOL shouldPresentProxyAuthenticationDialog;
@property (assign) BOOL shouldPresentCredentialsBeforeChallenge;
@property (assign) BOOL haveBuiltRequestHeaders;
@property (assign, nonatomic) BOOL haveBuiltPostBody;
@property (assign) int retryCountOnTimeout;
@property (assign) BOOL shouldAttemptPersistentConnection;
@property (assign) NSTimeInterval persistentConnectionTimeoutSeconds;
@property (assign) BOOL shouldUseRFC2616RedirectBehaviour;
/**
 * Configures a default download cache
 * The download cache that will be used for this request
 *
 * <pre>
 * Sample usage
 * <code>
 * // assign a download cache instance to the request
 * <b>[m_Request setDownloadCache:[SDMDownloadCache instance]];</b>
 * // apply cache settings as required (see SDMDownloadCache)
 * [[SDMDownloadCache instance] setDefaultCachePolicy:OnlyLoadIfNotCachedCachePolicy];
 *
 * [m_Request setCacheStoragePolicy:CachePermanentlyCacheStoragePolicy];
 * </code>
 * </pre>
 * @see +setDefaultCache, SDMDownloadCache
 */
@property (assign) id <SDMCacheDelegate> downloadCache;
@property (assign) CachePolicy cachePolicy;
@property (assign) CacheStoragePolicy cacheStoragePolicy;
@property (assign) NSTimeInterval secondsToCache;
@property (retain) NSArray* clientCertificates;

#if TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_4_0
/**
 * Controls background download/uplod behavior (enabled by default) for builds targeting iOS4.0+
 * @remark Will not work for iOS versions below 4.0
 */
@property (assign, nonatomic) BOOL shouldContinueInBackground;
#endif


@end
