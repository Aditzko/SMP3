//
//  NetworkQueue.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RequestDelegate.h"
#import "ProgressDelegate.h"

/**
 * @brief Manages multiple Request objects.
 * Manages batched HTTP requests, to track their overall progress, cancel them, and so on.
 */
@interface NetworkQueue : NSOperationQueue <ProgressDelegate, RequestDelegate, NSCopying> {
	
    /**
     * Delegate which receives request didFail and didFinish, furthermore network queue didFinish messsages.
     */
	id delegate;
    
	/**
     * Called when a request starts with the request as the argument.
     */
	SEL requestDidStartSelector;
	
	/**
     * Called when a request receives response headers.
	 * @remark Should take the form request:didRecieveResponseHeaders:, where the first argument is the request, and the second is the headers dictionary.
     */
	SEL requestDidReceiveResponseHeadersSelector;
	
	/**
     * Called when a request is about to redirect.
	 * Should take the form request:willRedirectToURL:, where the first argument is the request, and the second is the new URL.
     */
	SEL requestWillRedirectSelector;
    
	/**
     * Called when a request completes with the request as the argument.
     */
	SEL requestDidFinishSelector;
	
	/**
     * Called when a request fails with the request as the argument.
     */
	SEL requestDidFailSelector;
	
	/**
     * Called when the queue finishes with the queue as the argument.
     */
	SEL queueDidFinishSelector;
	
	/**
     * Upload progress indicator, probably an NSProgressIndicator or UIProgressView.
     */
	id uploadProgressDelegate;
	
	/**
     * Total amount uploaded so far for all requests in this queue.
     */
	unsigned long long bytesUploadedSoFar;
	
	/**
     * Total amount to be uploaded for all requests in this queue - requests add to this figure as they work out how much data they have to transmit.
     */
	unsigned long long totalBytesToUpload;
    
	/**
     * Download progress indicator, probably an NSProgressIndicator or UIProgressView.
     */
	id downloadProgressDelegate;
	
	/**
     * Total amount downloaded so far for all requests in this queue.
     */
	unsigned long long bytesDownloadedSoFar;
	
	/**
     * Total amount to be downloaded for all requests in this queue - requests add to this figure as they receive Content-Length headers.
     */
	unsigned long long totalBytesToDownload;
	
	/**
     * When set to YES, the queue cancels all requests when a request fails. The default value is YES.
     */
	BOOL shouldCancelAllRequestsOnFailure;
	
	/**
     * Number of real requests. This excludes HEAD requests created to manage showAccurateProgress.
     */
	int requestsCount;
	
    /**
     * This flag controls whether the download or update progress is tracked accurately or only when a request is completed.
     * If it is set to YES, the queue performs HEAD requests for all GET requests in the queue, so it can calculate the total download size before it starts.
     * The default value is NO, which means better performance, by skipping the HEAD requests for each GET request, and will not update the progress indicator until a request is completed.
     */
	BOOL showAccurateProgress;
    
	/**
     * Stores additional queue information
     */
	NSDictionary *userInfo;
	
}

/**
 * Convenience constructor.
 * @param None
 * @return Returns the instance of the NetworkQueue class.
 * <pre>
 * NetworkQueue* networkQueue = [NetworkQueue queue];
 * </pre>
 */
+ (id)queue;

/**
 * Resets the queue; it cancels all operations, clears delegates, and suspends operations.
 * @param None
 * <pre>
 * NetworkQueue* networkQueue = [NetworkQueue queue];
 * [networkQueue reset];
 * </pre>
 */
- (void)reset;

/**
 * Starts the queue.
 * @remark NetworkQueues are paused when created, so that total size can be calculated before the queue starts.
 * @param None
 * <pre>
 * // instantiate the shared network queue
 * NetworkQueue* networkQueue = [NetworkQueue queue];
 * // set various delegates and selectors
 * // subscribe for download progress notifications
 * [networkQueue setDownloadProgressDelegate:self]; 
 * // for accurate progress tracking
 * [networkQueue setShowAccurateProgress:YES];
 * // register ourselves as delegate
 * [networkQueue setDelegate:self];
 * [networkQueue setRequestDidFailSelector:@selector(downloadFailed:)];
 * [networkQueue setRequestDidFinishSelector:@selector(downloadFinished:)];
 * [networkQueue setQueueDidFinishSelector:@selector(queueFinished:)];	//there is no queueFailed selector: the queue is always finished even if some or all the belonging requests fail
 * // create and add the requests (internally an NSOperationQueue is used to store and concurrently handle the requests)
 * // Request#1
 * Request* request = [Request requestWithUrl:[NSURL URLWithString:@"http://www.yahoo.com"]];
 * [networkQueue addOperation:request];
 *
 * // Request#2
 * Request* request2 = [Request requestWithUrl:[NSURL URLWithString:@"http://www.google.com"]];
 * [networkQueue addOperation:request2];
 *
 * // start the queue (all operations are on hold when added)
 * [networkQueue startBatch];
 * </pre>
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
