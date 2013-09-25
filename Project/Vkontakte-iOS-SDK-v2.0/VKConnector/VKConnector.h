//
//  VKConnector.h
//
//  Created by Andrew Shmig on 18.12.12.
//
//
// Copyright (c) 2013 Andrew Shmig
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#import <Foundation/Foundation.h>
#import "VKMethods.h"
#import "VKModal.h"


@class VKAccessToken;
@class VKConnector;
@class VKModal;
@class VKStorageItem;


/** This protocol defines callback methods for tracking access token
 status updates. Access token is being stored in VKConnector class.
 */
@protocol VKConnectorDelegate <NSObject>

@optional
/**
 @name Modal view
 */
/** This callback will be executed before authorization modal window is shown
 
 @param connector instance of VKConnector class which will send a message
 @param view modal window
 */
- (void)VKConnector:(VKConnector *)connector
  willShowModalView:(VKModal *)view;

/** This callback will be executed before authorization modal window is hidden
 
 @param connector instance of VKConnector class which will send a message
 @param view modal window
 */
- (void)VKConnector:(VKConnector *)connector
  willHideModalView:(VKModal *)view;

/**
 @name Access token
 */
/** This callback will be executed when access token expires
 
 @param connector instance of VKConnector class which will send a message
 @param accessToken expired access token
 */
- (void)   VKConnector:(VKConnector *)connector
accessTokenInvalidated:(VKAccessToken *)accessToken;

/** This callback will be executed after successful access token renewal
 
 @param connector instance of VKConnector class which will send a message
 @param accessToken renewed access token
 */
- (void)        VKConnector:(VKConnector *)connector
accessTokenRenewalSucceeded:(VKAccessToken *)accessToken;

/** This callback will be executed if a token update was not successful.
 It is possible that internet connection was lost or user denied authorizing application
 
 @param connector instance of VKConnector class which will send a message
 @param accessToken access token will be equal to nil
 */
- (void)     VKConnector:(VKConnector *)connector
accessTokenRenewalFailed:(VKAccessToken *)accessToken;

/**
 @name Connection & Parsing
 */
/** This callback will be executed if a connection problem occurs during a request
 
 @param connector instance of VKConnector class which will send a message
 @param error object with errors description
 */
- (void)   VKConnector:(VKConnector *)connector
connectionErrorOccured:(NSError *)error;

/** This callback will be executed if there is an invalid json response
 
 @param connector instance of VKConnector class which will send a message
 @param error object with errors description
 */
- (void)VKConnector:(VKConnector *)connector
parsingErrorOccured:(NSError *)error;

@end

/** This interface is intended for retrieving user profile access token and
 issuing requests for VK API using GET/POST methods 
 
 - (void)applicationDidFinishLaunching:(UIApplication *)application
 {
    [[VKConnector sharedInstance] startWithAppID:@"YOUR_APP_ID"
                                    permissons:@[@"friends",@"wall"]];
 }
 */
@interface VKConnector : NSObject <UIWebViewDelegate, KGModalDelegate>

/**
 @name Properties
 */
/** VKConnector delegate
 
 @see https://en.wikipedia.org/wiki/Delegation_pattern
 */
@property (nonatomic, weak, readwrite) id <VKConnectorDelegate> delegate;

/** VKontakte application identifier generated during registration process
 */
@property (nonatomic, strong, readonly) NSString *appID;

/** Permissions list
 */
@property (nonatomic, strong, readonly) NSArray *permissions;

/**
 @name Methods
 */
/** Class methods for retrieving singleton instance
 If onject is missing it will be created.
 */
+ (id)sharedInstance;

/**
 @name User authorization for application
 */
/** Initializes connection with passed parameters
 
 @param appID VKontakte application identifier generated during registration process
 @param permissions Array with permission flags that the application needs to request
 */
- (void)startWithAppID:(NSString *)appID
            permissons:(NSArray *)permissions;

/**
 @name Authorization cookies management methods
 */
/** Removes cookies that are received during the authorization process of the last application user.
 Might be needed if the user wants to use different profiles or for authorization of a different person.
 
 tip: UIWebView saves authorization cookies
 */
- (void)clearCookies;

@end
