//
//  BatchRequest.h
//  Connectivity
//
//  Created by Prathap, Sujith on 4/22/13.
//
//

#import <Foundation/Foundation.h>
#import "Request.h"

/**
 * @brief Consists of methods related to batch request. Batch request allows users to combine multiple requests into a single request for processing. Batch request should be used when more than one request is to be retrieved or modifying requests are to be combined.
 */

@interface BatchRequest : Request<NSCoding>

{
    //Array that represents the requests that make up the current change list.
    NSMutableArray *currentChangeSet;
    
    //Flag to check if there is an existing changeset.
    //BOOL isChangestCreated; //This is now moved to .m
    
    //A array with keys which are stored in
    //the orderedArray and an array of requests
    //corresponding to each Retrieve Request
    //or Changelist.
    NSMutableArray *requestArray;
    
    
    
}

@property(nonatomic,retain)NSMutableArray *currentChangeSet;
@property(nonatomic) BOOL isChangestCreated;
@property(nonatomic,retain,readonly)NSMutableArray *requestArray;

#pragma mark -
#pragma mark Batch Request

/**
 * Initializes the BatchRequest object.
 * @param url Object of NSURL class.
 * @return Returns the instance of the BatchRequest class.
 * <pre>
 *  BatchRequest *batch = [[BatchRequest alloc] initWithURL:[[NSURL alloc] initWithString:[NSString stringWithFormat:@"%@$batch",applicationEndpoint]]];
 * </pre>
 */
- (id)initWithURL:(NSURL *)url;

/**
 * Adds a retrieve request to the BatchRequest class.
 * @param request Object of Request class.
 * @param error Object of NSError class.
 * <pre>
 * NSError *error = nil;
 * [RequestBuilder enableXCSRF:YES];
 * id<Requesting> request = [RequestBuilder requestWithURL:[[NSURL alloc] initWithString:@"TravelagencyCollection"]];
 * [request setRequestMethod:@"GET"];
 * BatchRequest *batch = [[BatchRequest alloc] initWithURL:[[NSURL alloc] initWithString:[NSString stringWithFormat:@"%@$batch",applicationEndpoint]]];
 * [batch setUsername:user];
 * [batch setPassword:pass];
 * [batch addRetrieveRequestToBatch:request withError:&error];
 * if(!error){
 * [batch startSynchronous];
 * }
 * </pre>
 */
- (void)addRetrieveRequestToBatch:(id<Requesting>)request withError:(NSError**)error;

/**
 * Adds a modifying request such as POST/PUT/DELETE to the BatchRequest class.
 * @param request Object of Request class.
 * NSError *error = nil;
 * <pre>
 * [RequestBuilder enableXCSRF:YES];
 * id<Requesting> postRequest = [RequestBuilder requestWithURL:[[NSURL alloc] initWithString:@"TravelagencyCollection"]];
 * [postRequest setRequestMethod:@"POST"];
 * [postRequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
 * [postRequest addRequestHeader:@"Content-Length" value:@"1005"];
 * [postRequest setPostBody:data];
 * BatchRequest *batch = [[BatchRequest alloc] initWithURL:[[NSURL alloc] initWithString:[NSString stringWithFormat:@"%@$batch",applicationEndpoint]]];
 * [batch addRequestToChangeset:postRequest withError:&error];
 * [batch setUsername:user];
 * [batch setPassword:pass];
 * [batch startSynchronous];
 * </pre>
 */
- (void)addRequestToChangeset:(id<Requesting>)request withError:(NSError**)error;

/**
 * Closes a changeSet and adds requests to new changeSet.
 * @param None
 * <pre>
 * BatchRequest *batch = [[BatchRequest alloc] initWithURL:[[NSURL alloc] initWithString:[NSString stringWithFormat:@"%@$batch",applicationEndpoint]]];
 * [batch addRequestToChangeset:postRequest1];
 * [batch closeExistingChangeSet];
 * [batch addRequestToChangeset:postRequest2];
 * [batch setUsername:user];
 * [batch setPassword:pass];
 * [batch startSynchronous];
 * </pre>
 */
- (void)closeExistingChangeSet;

@end
