//
//  SDMProgressDelegate.h
//
//  SDMConnectivity library
//
//  Created by Karoly Nyisztor on Apr 11, 2011
//  Copyright SAP AG 2011. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDMHttpRequestDelegate.h"
#import "SDMProgressDelegate.h"

/**
 * @deprecated
 * Manages multiple SDMHttpRequest objects 
 * Used to manage batched http requests, i.e. track their overall progress, cancel them all, etc.
 * @example
 * <pre>
 * // instantiate the shared network queue
 * <b>SDMNetworkQueue* networkQueue = [SDMNetworkQueue queue];</b>
 * // set various delegates and selectors
 * [networkQueue setDownloadProgressDelegate:self]; // subscribe for download progress notifications
 * [networkQueue setShowAccurateProgress:YES];      // we want accurate progress tracking
 * [networkQueue setDelegate:self];                 // register ourselves as delegate
 * [networkQueue setRequestDidFailSelector:@selector(downloadFailed:)];     // we want to receive requestDidFail messages
 * [networkQueue setRequestDidFinishSelector:@selector(downloadFinished:)]; // we want to receive requestDidFinish messages
 
 * [networkQueue setQueueDidFinishSelector:@selector(queueFinished:)];	// we want to receive requestDidFinish messages (no, there is no queueFailed selector: the queue is always finished even if some or all the belonging requests fail)
 *
 * // create and add the requests (internally an NSOperationQueue is used to store and concurrently handle the requests)
 * // Request#1
 * SDMHttpRequest* request = [SDMHttpRequest requestWithUrl:[NSURL URLWithString:@"http://www.yahoo.com"]];
 * <b>[networkQueue addOperation:request];</b>
 *
 * // Request#2
 * SDMHttpRequest* request2 = [SDMHttpRequest requestWithUrl:[NSURL URLWithString:@"http://www.google.com"]];
 * <b>[networkQueue addOperation:request2];</b>
 *
 * // start the queue (all operations are on hold when added)
 * <b>[networkQueue startBatch];</b>
 * </pre>
 */
__attribute((deprecated("Use NetworkQueue instead")))
@interface SDMNetworkQueue : NSOperationQueue <SDMProgressDelegate, SDMHttpRequestDelegate, NSCopying> {
	
    /**
     * Delegate which receives request didFail and didFinish, furthermore network queue didFinish messsages
     */
	id delegate;

	/**
     * Called when a request starts with the request as the argument
     */
	SEL requestDidStartSelector;
	
	/**
     * Called when a request receives response headers
	 * @remark Should take the form request:didRecieveResponseHeaders:, where the first argument is the request, and the second the headers dictionary
     */
	SEL requestDidReceiveResponseHeadersSelector;
	
	/**
     * Called when a request is about to redirect
	 * Should take the form request:willRedirectToURL:, where the first argument is the request, and the second the new url
     */
	SEL requestWillRedirectSelector;

	/**
     * Called when a request completes with the request as the argument
     */
	SEL requestDidFinishSelector;
	
	/**
     * Called when a request fails with the request as the argument
     */
	SEL requestDidFailSelector;
	
	/** 
     * Called when the queue finishes with the queue as the argument
     */
	SEL queueDidFinishSelector;
	
	/**
     * Upload progress indicator, probably an NSProgressIndicator or UIProgressView
     */
	id uploadProgressDelegate;
	
	/**
     * Total amount uploaded so far for all requests in this queue
     */
	unsigned long long bytesUploadedSoFar;
	
	/**
     * Total amount to be uploaded for all requests in this queue - requests add to this figure as they work out how much data they have to transmit
     */
	unsigned long long totalBytesToUpload;

	/**
     * Download progress indicator, probably an NSProgressIndicator or UIProgressView
     */
	id downloadProgressDelegate;
	
	/**
     * Total amount downloaded so far for all requests in this queue
     */
	unsigned long long bytesDownloadedSoFar;
	
	/**
     * Total amount to be downloaded for all requests in this queue - requests add to this figure as they receive Content-Length headers
     */
	unsigned long long totalBytesToDownload;
	
	/**
     * When YES, the queue will cancel all requests when a request fails. Default is YES
     */
	BOOL shouldCancelAllRequestsOnFailure;
	
	/**
     * Number of real requests (excludes HEAD requests created to manage showAccurateProgress)
     */
	int requestsCount;
	
    /**
     * This flag controls whether the dpwnload / update progress is tracked accurately or only whenever a request completes
     * if set to YES, the queue will first perform HEAD requests for all GET requests in the queue, so it can calculate the total download size before it starts
     * The default setting is NO, which means better performance, by skipping the HEAD requests for each GET request, and won't update the progress indicator until a request completes
     */
	BOOL showAccurateProgress;

	/**
     * Stores additional queue information
     */
	NSDictionary *userInfo;
	
}

/**
 * Convenience constructor
 */
+ (id)queue;

/**
 * Resets the queue; it cancels all operations, clears delegates, and suspends operations
 */
- (void)reset;

/**
 * Starts the queue
 * @remark SDMNetworkQueues are paused when created so that total size can be calculated before the queue starts
 */
- (void)startBatch;

@property (assign, nonatomic, setter=setUploadProgressDelegate:) id uploadProgressDelegate;
@property (assign, nonatomic, setter=setDownloadProgressDelegate:) id downloadProgressDelegate;

@property (assign) SEL requestDidStartSelector;
@property (assign) SEL requestDidReceiveResponseHeadersSelector;
@property (assign) SEL requestWillRedirectSelector;
@property (assign) SEL requestDidFinishSelector;
@property (assign) SEL requestDidFailSelector;
@property (assign) SEL queueDidFinishSelector;
@property (assign) BOOL shouldCancelAllRequestsOnFailure;
@property (assign) id delegate;
@property (assign) BOOL showAccurateProgress;
@property (assign, readonly) int requestsCount;
@property (retain) NSDictionary *userInfo;

@property (assign) unsigned long long bytesUploadedSoFar;
@property (assign) unsigned long long totalBytesToUpload;
@property (assign) unsigned long long bytesDownloadedSoFar;
@property (assign) unsigned long long totalBytesToDownload;

@end
