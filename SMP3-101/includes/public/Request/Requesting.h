//
//  Requesting.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

#import "CacheDelegate.h"


#ifndef USE_ODP_INTERFACE

/**
 * Consists of supported etag header types.
 */
typedef enum {
    
    IfMatch,
    IfNoneMatch,
    IfRange
} EtagType;

#endif


/**
 * @brief Requesting is the protocol to be adapted by Request classes.
 */
@protocol Requesting <NSObject>

#pragma mark -
#pragma mark Required APIs and Accessors

/* ------------------------------------------------------------------------------------------------------------------------------ */
/* ---------------------------------------------------------- REQUIRED ---------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------ */

@required

#pragma mark -
#pragma mark Required Accessors

// The bare minimum accessor set which should be in Request
@property (retain) NSString* username; ///< for basic auth
@property (retain) NSString* password; ///< for basic auth
@property (nonatomic, assign) BOOL disableDeltaHandling;
@property (assign, nonatomic) id delegate; ///< client delegate
@property (retain, nonatomic) id queue;	///< NSOperationQueue (our thread pool used for parallel execution of requests)
@property (assign) BOOL shouldAutosetLanguage; ///< controls whether the preferred language has to be passed along the request's header; defaults to YES

#pragma mark -
#pragma mark Initialization and deallocation

/**
 * Should be an HTTP or HTTPS URL. It may include username and password (if appropriate).
 */
- (id)initWithURL:(NSURL *)newURL;

/**
 * Convenience constructor with URL. Recommend the use against @see initWithURL.
 */

+ (id)requestWithURL:(NSURL *)newURL;

/**
 * Convenience constructor with url and cache.
 */
+ (id)requestWithURL:(NSURL *)newURL usingCache:(id <CacheDelegate>)cache;

/**
 * Convenience constructor with url, cache and cache policy.
 */
+ (id)requestWithURL:(NSURL *)newURL usingCache:(id <CacheDelegate>)cache andCachePolicy:(ECachePolicy)policy;

/**
 * Sets the maximum number of Request threads which can run at once.
 * @throws ConnectivityException if maximum allowed parallel thread is exceeded.
 */
+ (void) setMaxConcurrentHTTPRequestCount:(const unsigned char) cnt;

/**
 * Returns the maximum number of request threads that can be executed in parallel.
 */
+ (NSInteger) getMaxConcurrentHTTPRequestCount;

#pragma mark -
#pragma mark Request Setup

/**
 * Adds a custom header to the request.
 */
- (void)addRequestHeader:(NSString *)header value:(NSString *)value;

/**
 * Called during buildRequestHeaders and after a redirect to create a cookie header from request cookies and the global store.
 */
- (void)applyCookieHeader;

/**
 * Populates the request headers dictionary. It is called before a request is started, or by a HEAD request that needs to borrow them.
 */
- (void)buildRequestHeaders;

/**
 * Used to apply authorization header to a request before it is sent (when shouldPresentCredentialsBeforeChallenge is YES).
 */
- (void)applyAuthorizationHeader;

/**
 * Adds data to the post body. It appends to post body when shouldStreamPostDataFromDisk is false, or write to postBodyWriteStream when true.
 */
- (void)appendPostData:(NSData *)data;

/**
 * Adds data to the post body from a file. It appends to post body when shouldStreamPostDataFromDisk is false, or write to postBodyWriteStream when true.
 */
- (void)appendPostDataFromFile:(NSString *)file;

/**
 * Creates the post body.
 */
- (void)buildPostBody;

/**
 * Add If-Match or If-None-Match or If-Range header.
 */
- (void)setEtag:(NSString *)etag withMatchType:(EtagType) matchType;

/**
 * Enable XSRF support for the session of the application. It should be set again in case of application restart.
 */
+ (void)enableXCSRF:(BOOL) enable;

#pragma mark -
#pragma mark Request Payload

/**
 * Retrieves the response of a request. It is uncompressed if required.
 * @return returns the response as NSString.
 * @example
 * <pre>
 * id<Requesting> m_Request = [RequestBuilder requestWithURL:url];
 * ...
 * [m_Request startSynchronous];
 * NSString* responseAsString = [m_Request responseString];
 * ...
 * </pre>
 */
- (NSString *)responseString;

/**
 * Retrieves the response of a request. It is uncompressed if required.
 * @return returns the response as NSData.
 * @example
 * <pre>
 * id<Requesting> m_Request = [RequestBuilder requestWithURL:url];
 * ...
 * [m_Request startSynchronous];
 * NSData* responseAsData = [m_Request responseData];
 * ...
 * </pre>
 */
- (NSData *)responseData;

/**
 * Returns true if the response is gzip compressed.
 * @return returns a BOOL to indicate if response was gzip compressed.
 * @example
 * <pre>
 * id<Requesting> m_Request = [RequestBuilder requestWithURL:url];
 * ...
 * [m_Request startSynchronous];
 * if([m_Request isResponseCompressed])
 * ...
 * </pre>
 */
- (BOOL)isResponseCompressed;

#pragma mark -
#pragma mark Request execution

/**
 * Executes a request synchronously, and returns control when the request completes or fails.
 * @example
 * <pre>
 * id<Requesting> m_Request = [RequestBuilder requestWithURL:url];
 * ...
 * [m_Request startSynchronous];
 * </pre>
 */
- (void)startSynchronous;

/**
 * Executes request asynchronously, in the background.
 * The client should register callback selector to get notified about various events (failure, completion, and so on.)
 * @example
 * <pre>
 * id<Requesting> m_Request = [RequestBuilder requestWithURL:url];
 * [m_Request setDelegate:self];
 * [m_Request setDidFinishSelector:@selector(serviceDocFetchComplete:)];
 * [m_Request setDidFailSelector:@selector(serviceDocFetchFailed:)];
 * [m_Request startAsynchronous];
 * </pre>
 */
- (void)startAsynchronous;

#pragma mark -
#pragma mark Assignable Selectors

/**
 * Clients can choose to register their custom selectors to be invoked after request completes executing.
 * @remark Consider implementing the RequestDelegate as an alternative to this approach.
 * @example
 * <pre>
 * id<Requesting> m_Request = [RequestBuilder requestWithURL:url];
 * [m_Request setDelegate:self];
 * [m_Request setDidStartSelector:@selector(serviceDocFetchStarted:)];
 * ...
 * </pre>
 */
@property (assign) SEL didStartSelector;

/**
 * Clients can choose to register their custom selectors to be invoked after request is executed.
 * @remark Consider implementing the RequestDelegate as an alternative to this approach.
 * @example
 * <pre>
 * id<Requesting> m_Request = [RequestBuilder requestWithURL:url];
 * [m_Request setDelegate:self];
 * [m_Request setDidFinishSelector:@selector(serviceDocFetchComplete:)];
 * ...
 * </pre>
 */
@property (assign) SEL didFinishSelector;

/**
 * Clients can choose to register their custom selectors to be invoked after request is executed.
 * @remark Consider implementing the RequestDelegate as an alternative to this approach.
 * @examples
 * <pre>
 * id<Requesting> m_Request = [RequestBuilder requestWithURL:url];
 * [m_Request setDelegate:self];
 * [m_Request setDidFailSelector:@selector(serviceDocFetchFailed:)];
 * ...
 * </pre>
 */
@property (assign) SEL didFailSelector;

/**
 * Clients can choose to register their custom selectors to be invoked after request is executed.
 * Default delegate method invoked when incoming data is available.
 * @remark Implement this delegate only if you want to manually process all incoming data yourself (usually not required). This means that responseData or responseString are ignored.
 * @example
 * <pre>
 * id<Requesting> m_Request = [RequestBuilder requestWithURL:url];
 * [m_Request setDelegate:self];
 * [m_Request setDidReceiveDataSelector:@selector(dataArrived:)];
 * ...
 * </pre>
 */
@property (assign) SEL didReceiveDataSelector;

/**
 * Clients can chose to register their custom selectors to be invoked after request is executed.
 * @example
 * <pre>
 * id<Requesting> m_Request = [RequestBuilder requestWithURL:url];
 * [m_Request setDelegate:self];
 * [m_Request setDidReceiveResponseHeadersSelector:@selector(headersReceived:)];
 * ...
 * </pre>
 */
@property (assign) SEL didReceiveResponseHeadersSelector;

#pragma  mark Auth Challenge Selector

/**
 * Clients can choose to register their custom selectors to be invoked.
 * @example
 * <pre>
 * id<Requesting> m_Request = [RequestBuilder requestWithURL:url];
 * [m_Request setDelegate:self];
 * [m_Request setDidReceiveAuthChallengeSelector:@selector(authenticationNeededForRequest:)];
 * ...
 * </pre>
 */
@property(assign) SEL didReceiveAuthChallengeSelector;

#pragma mark -
#pragma mark Optional APIs

@optional

#pragma mark -
#pragma mark Optional factory methods

///**
// * Convenience constructor with URL and cache.
// */
//+ (id)requestWithURL:(NSURL *)newURL usingCache:(id <CacheDelegate>)cache;
//
///**
// * Convenience constructor with URL, cache, and cache policy.
// */
//+ (id)requestWithURL:(NSURL *)newURL usingCache:(id <CacheDelegate>)cache andCachePolicy:(ECachePolicy)policy;

#pragma mark -
#pragma mark HEAD request

/**
 * Used by NetworkQueue to create a HEAD request appropriate for this request with the same headers.
 */
- (id<Requesting>)HEADRequest;

#pragma mark -
#pragma mark Upload / Download progress

/**
 * Updates the progress delegates.
 * @remark Used by NetworkQueue, clients should not invoke them directly.
 */
- (void)updateProgressIndicators;

/**
 * Updates upload progress (notifies the queue and/or uploadProgressDelegate of this request).
 */
- (void)updateUploadProgress;

/**
 * Updates download progress (notifies the queue and/or downloadProgressDelegate of this request).
 */
- (void)updateDownloadProgress;

/**
 * Called when authorization is needed, as you can only find out that you do not have permission, when the upload is complete.
 */
- (void)removeUploadProgressSoFar;

/**
 * Called when we get a content-length header and shouldResetDownloadProgress is true.
 */
- (void)incrementDownloadSizeBy:(long long)length;

/**
 * Called when a request starts and shouldResetUploadProgress is true.
 * It is also called (with a negative length) to remove the size of the underlying buffer used for uploading.
 */
- (void)incrementUploadSizeBy:(long long)length;

/**
 * Helper method for interacting with progress indicators to abstract the details of different APIS (NSProgressIndicator and UIProgressView).
 */
+ (void)updateProgressIndicator:(id *)indicator withProgress:(unsigned long long)progress ofTotal:(unsigned long long)total;

/**
 * Helper method used for performing invocations on the main thread (used for progress).
 */
+ (void)performSelector:(SEL)selector onTarget:(id *)target withObject:(id)object amount:(void *)amount;


#pragma mark -
#pragma mark Http Authentication

/**
 * Wakes up (unlocks) the request thread so it can resume the request.
 * @remark It should be called by delegates when they have populated the authentication information after an authentication challenge.
 */
- (void)retryUsingSuppliedCredentials;

//! Should be called by delegates to cancel authentication and stop.
- (void)cancelAuthentication;

/**
 * Constructs a basic authentication header from the username and password provided, and adds it to the request headers.
 * Used when shouldPresentCredentialsBeforeChallenge is set to YES.
 */
- (void)addBasicAuthenticationHeaderWithUsername:(NSString *)theUsername andPassword:(NSString *)thePassword;

#pragma mark -
#pragma mark CFnetwork Event Handlers
/**
 * Handles network events as they occur.
 * @remark Called from ReadStreamClientCallBack when one of the events requested in NETWORK_EVENTS occurs.
 */
- (void)handleNetworkEvent:(CFStreamEventType)type;

#pragma mark -
#pragma mark Request Failure Management

/**
 * Called when a request fails, and lets the delegate know via didFailSelector.
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
 * Configures a default download cache that applies for all requests.
 * @see DownloadCache
 */
+ (void)setDefaultCache:(id <CacheDelegate>)cache;

/**
 * Returns the default download cache or nil if none is set at class level.
 */
+ (id <CacheDelegate>)defaultCache;

#pragma mark -
#pragma mark Network Activity
/**
 * Indicates whether there are running requests.
 * @return NO, if no requests are being executed.
 */
+ (BOOL)isNetworkInUse;

/**
 * Controls whether the request should take over updating the network activity indicator.
 * @remark Enabled by default.
 */
+ (void)setShouldUpdateNetworkActivityIndicator:(BOOL)shouldUpdate;

//! Shows the network activity spinner
+ (void)showNetworkActivityIndicator;

//! Hides the network activity spinner
+ (void)hideNetworkActivityIndicator;

#pragma mark -
#pragma mark Bandwidth Measurement / Throttling
/**
 * The maximum number of bytes all requests can send or receive in a second.
 * This is a rough figure. The actual amount used will be slightly more, this does not include HTTP headers.
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
 * Request can automatically turn throttling on and off, as the connection type changes between WWAN and WiFi.
 * Set to YES to automatically turn on throttling when WWAN is connected, and automatically turn it off when it is not connected.
 */
+ (void)setShouldThrottleBandwidthForWWAN:(BOOL)throttle;

//! Turns on throttling automatically when WWAN is connected using a custom limit, and turns it off automatically when it is not connected.
+ (void)throttleBandwidthForWWANUsingLimit:(unsigned long)limit;

//! Returns the maximum amount of data you can read as part of the current measurement period, and closes this thread if the allowance is used up.
+ (unsigned long)maxUploadReadLength;

#pragma mark
#pragma mark Mime-type Detection

// Return the mime type for a file
+ (NSString *)mimeTypeForFileAtPath:(NSString *)path;

#pragma mark -
#pragma mark Secure File Storage
/**
 * Controls whether the download cache should store files using protection.
 * @remark Enabled by default, applies to all instances; only available for builds targeting iOS 4.0 or above.
 */
+(void) setProtectionEnabled:(BOOL)flag_in;

/**
 * Returns a attributes dictionary used for encrypted file storage or nil if file protection has been explicitely disabled.
 * @remark File protection is enabled by default for builds targeting iOS4.0+; change using via Request +setProtectionEnabled.
 * @see setProtectionEnabled:
 */
+(NSDictionary*) fileProtectionAttributes;

/**
 * Returns a mask that determines whether the data should be stored in an encrypted form.
 * @remark Data will be stored in encrypted form by default.
 */
+(const NSDataWritingOptions) dataWritingOptions;

#pragma mark -
#pragma mark SAP Tracing and Business Transaction XML support
/**
 * Switches traceability status. The default value is NO.
 * @discussion If tracing is enabled, the "SAP-PASSPORT" and "X-CorrelationID" headers are set and filled with values to enable SAP Passport functionality.
 * Data is gathered to compose the Business Transaction XML, that can be uploaded via SUPE2ETraceController sendXML method.
 * @see SUPE2ETraceController
 */
- (void) enableTracing:(BOOL)value_in;

/**
 * Returns tracing status. The default value is NO.
 * @see setTracingEnabled:
 */
- (BOOL) isTracingEnabled;

/**
 * Posts the SAP E2E Trace XML to the specified URL.
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

// Cache related stuff
@property (nonatomic, retain) NSString* cacheUrlKey; //--> URL key of the cache for which this request is being fired
@property (nonatomic, retain) NSMutableArray* cacheEntryIdList; // --> Entry ID List associated with the request (in case of batch)
@property (nonatomic) int requestTag;//--> Tag to correlate the request to the response in an offline call.


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
@property (assign) id<Requesting> mainRequest;
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
 * Configures a default download cache, used for this request.
 * @example
 * <pre>
 * Sample usage
 * <code>
 * // assign a download cache instance to the request
 * <b>[m_Request setDownloadCache:[DownloadCache instance]];</b>
 * // apply cache settings as required (see DownloadCache)
 * [[DownloadCache instance] setDefaultCachePolicy:OnlyLoadIfNotCached_CachePolicy];
 *
 * [m_Request setCacheStoragePolicy:CachePermanently_CacheStoragePolicy];
 * </code>
 * </pre>
 * @see +setDefaultCache, DownloadCache
 */
@property (assign) id <CacheDelegate> downloadCache;
@property (assign) ECachePolicy cachePolicy;
@property (assign) ECacheStoragePolicy cacheStoragePolicy;
@property (assign) NSTimeInterval secondsToCache;
@property (retain) NSArray* clientCertificates;

#if TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_4_0
/**
 * Controls background download or upload behavior (enabled by default) for builds targeting iOS version 4.0 and above.
 * @remark It will not work for iOS versions below 4.0.
 */
@property (assign, nonatomic) BOOL shouldContinueInBackground;
#endif


@end
