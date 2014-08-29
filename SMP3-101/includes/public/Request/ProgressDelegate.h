//
//  ProgressDelegate.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

@protocol Requesting;

/**
 * @brief Defines default delegate methods for upload and download progress notification.
 * Protocol to be adapted by client classes to hook in for didReceiveBytes, didSendBytes, incrementDownloadSizeBy, and incrementUploadSizeBy delegates.
 */
@protocol ProgressDelegate <NSObject>

@optional

/**
 * Delegate method called to update UIProgressViews.
 * @remark As an alternative, you might want to consider implementing didReceiveBytes / didSendBytes delegate methods.
 */
- (void)setProgress:(float)newProgress;

/**
 * Delegate method called when the request receives data.
 * @param request request object which received data.
 * @param bytes number of bytes received.
 */
- (void)request:(id<Requesting>)request didReceiveBytes:(long long)bytes;

/**
 * Delegate method called when the request sends data.
 * @remark First chunk of data sent (32 KB) is not included in this amount (CFNetwork API limitation).
 * @param request request object which sent the data.
 * @param bytes number of bytes sent. It can be a negative value, if the request has to remove the upload progress (that is, to run again).
 */
- (void)request:(id<Requesting>)request didSendBytes:(long long)bytes;

/**
 * Delegate method called when the request needs to change the download content size.
 * @remark Content-length header might be misleading sometimes (that is, Apache HEAD requests for dynamically generated content returning the wrong Content-Length when using gzip).
 * @param request request object which sent the data.
 * @param bytes number of bytes sent. It can be a negative value if the request has to remove the upload progress (that is, to run again).
 */
- (void)request:(id<Requesting>)request incrementDownloadSizeBy:(long long)newLength;

/**
 * Delegate method called when the request needs to change the length of the content to be uploaded.
 * @param request request object which sent the data.
 * @param bytes number of bytes uploaded. It can be a negative value, if the request needs to remove the size of the internal buffer from progress tracking.
 */
- (void)request:(id<Requesting>)request incrementUploadSizeBy:(long long)newLength;

@end

