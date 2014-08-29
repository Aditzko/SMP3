//
//  SDMProgressDelegate.h
//
//  SDMConnectivity library
//
//  Created by Karoly Nyisztor on Apr 11, 2011
//  Copyright SAP AG 2011. All rights reserved.
//

@protocol SDMRequesting; 

/**
 * @deprecated
 * Defines default delegate methods for upload and download progress notification
 * Protocol to be adapted by client classes in order to hook in for didReceiveBytes / didSendBytes / incrementDownloadSizeBy / incrementUploadSizeBy delegates
 */
__attribute((deprecated("Use ProgressDelegate instead")))
@protocol SDMProgressDelegate <NSObject>

@optional

/**
 * Delegate method called to update UIProgressViews
 * @remark As an alternative, you might want to consider implementing didReceiveBytes / didSendBytes delegate methods
 */
- (void)setProgress:(float)newProgress;

/**
 * Delegate method called when the request receives data
 * @param request the request object which received data
 * @param bytes number of bytes received
 */
- (void)request:(id<SDMRequesting>)request didReceiveBytes:(long long)bytes;

/**
 * Delegate method called when the request sends data
 * @remark First chunk of data sent (32kB) is not included in this amount (CFNetwork API limitation)
 * @param request the request object which sent the data
 * @param bytes number of bytes sent; it can be a negative value if the request has to remove the upload progress (i.e. it has to run again)
 */
- (void)request:(id<SDMRequesting>)request didSendBytes:(long long)bytes;

/**
 * Delegate method called when the request needs to change the download content size
 * @remark Content-length header might be misleading sometimes (i.e. Apache HEAD requests for dynamically generated content returning the wrong Content-Length when using gzip)
 * @param request the request object which sent the data
 * @param bytes number of bytes sent; it can be a negative value if the request has to remove the upload progress (i.e. it has to run again)
 */
- (void)request:(id<SDMRequesting>)request incrementDownloadSizeBy:(long long)newLength;

/**
 * Delegate method called when the request needs to change the length of the content to upload
 * @param request the request object which sent the data
 * @param bytes number of uploaded bytes; it can be a negative value if the request needs to remove the size of the internal buffer from progress tracking
 */
- (void)request:(id<SDMRequesting>)request incrementUploadSizeBy:(long long)newLength;

@end
