//
//  RequestDelegate.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

@class Request;

/**
 * @brief Defines default delegate methods for request status related housekeeping.
 * Protocol to be adapted by client classes to hook in for requestStarted, requestFinished, or requestFailed delegates.
 * @remark These are the default delegates. Clients might use different ones by setting didStartSelector, didFinishSelector, or didFailSelector.
 */
@protocol RequestDelegate <NSObject>

@optional

/**
 * Default delegate method called when the request starts.
 * @remark Implement it to get informed when the request starts.
 * You can override this default delegate by setting Request didStartSelector.
 */
- (void)requestStarted:(Request*) request;
/**
 * Default delegate method called when the request is completed.
 * @remark It will be called when the request completes sucessfully.
 * You can override this default delegate by setting Request didFinishSelector.
 * @see requestFailed
 */
- (void)requestFinished:(Request*) request;
/**
 * Default delegate method called when the request fails.
 * @remark It will be called when the HTP request cannot be performed.
 * You can override this default delegate by setting Request didFinishSelector.
 * @see requestFinished
 */
- (void)requestFailed:(Request*) request;
/**
 * Default delegate method called when the request gets redirected.
 */
- (void)requestRedirected:(Request*) request;

/**
 * Default delegate method invoked when incoming data is available.
 * @remark Implementing this delegate is usually not required; otherwise you have to process all incoming bytes yourself.
 * This means that responseData or responseString are ignored.
 * You can override this default delegate by setting Request didReceiveDataSelector.
 */
- (void)request:(Request*)request didReceiveData:(const NSData* const)data_in;
/**
 * Default delegate method called when credentials must be supplied for authentication.
 * @remark As a response, the delegate can either restart the request ([request retryUsingSuppliedCredentials]) once credentials have been set.
 * or cancel it ([request cancelAuthentication]).
 * @see [request setUsername] and [request setPassword]
 */
- (void)authenticationNeededForRequest:(Request*)request;
/**
 * Default delegate method called when the proxy requires credentials for authentication.
 * @remark As a response, the delegate can either restart the request ([request retryUsingSuppliedCredentials]) once credentials have been set
 * or cancel it ([request cancelAuthentication]).
 * @see Request setUsername, setPassword, setProxyUsername and setProxyPassword methods.
 */
- (void)proxyAuthenticationNeededForRequest:(Request*)request;

@end
