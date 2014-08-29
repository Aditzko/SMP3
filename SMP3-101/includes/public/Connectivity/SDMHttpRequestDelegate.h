//
//  SDMProgressDelegate.h
//
//  SDMConnectivity library
//
//  Created by Karoly Nyisztor on Apr 11, 2011
//  Copyright SAP AG 2011. All rights reserved.
//

@class SDMHttpRequest;

/**
 * @deprecated
 * Defines default delegate methods for request status related housekeepig
 * Protocol to be adapted by client classes in order to hook in for requestStarted / requestFinished / requestFailed delegates
 * @remark These are the default delegates. Clients might use different ones by setting didStartSelector / didFinishSelector / didFailSelector
 */
__attribute((deprecated("Use RequestDelegate instead")))
@protocol SDMHttpRequestDelegate <NSObject>

@optional

/**
 * Default delegate method called when the request starts
 * @remark implement it to get informed when the request starts
 * You can override this default delegate by setting SDMHttpRequest didStartSelector
 */
- (void)requestStarted:(SDMHttpRequest*) request;
/**
 * Default delegate method called when the request completes
 * @remark It will be called when the request completes sucessfully
 * You can override this default delegate by setting SDMHttpRequest didFinishSelector
 * @see requestFailed
 */
- (void)requestFinished:(SDMHttpRequest*) request;
/**
 * Default delegate method called when the request fails
 * @remark It will be called when the HTP request cannot be performed
 * You can override this default delegate by setting SDMHttpRequest didFinishSelector
 * @see requestFinished
 */
- (void)requestFailed:(SDMHttpRequest*) request;
/**
 * Default delegate method called when the request gets redirected
 */
- (void)requestRedirected:(SDMHttpRequest*) request;

/**
 * Default delegate method invoked when incoming data is available.
 * @remark Implementing this delegate is usually not required; otherwise you have to process all incoming bytes yourself.
 * This means that responseData / responseString are ignored
 * You can override this default delegate by setting SDMHttpRequest didReceiveDataSelector
 */
- (void)request:(SDMHttpRequest*)request didReceiveData:(const NSData* const)data_in;
/**
 * Default delegate method called when credentials must be supplied for authentication
 * @remark As a response, the delegate can either restart the request ([request retryUsingSuppliedCredentials]) once credentials have been set
 * or cancel it ([request cancelAuthentication])
 * @see [request setUsername] and [request setPassword]
 */
- (void)authenticationNeededForRequest:(SDMHttpRequest*)request;
/**
 * Default delegate method called when the proxy requires credentials for authentication
 * @remark As a response, the delegate can either restart the request ([request retryUsingSuppliedCredentials]) once credentials have been set
 * or cancel it ([request cancelAuthentication])
 * @see SDMHttpRequest setUsername, setPassword, setProxyUsername and setProxyPassword APIs
 */
- (void)proxyAuthenticationNeededForRequest:(SDMHttpRequest*)request;

@end
