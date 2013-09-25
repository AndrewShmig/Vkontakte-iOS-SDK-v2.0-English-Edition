//
// Created by AndrewShmig on 5/28/13.
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
//
#import <Foundation/Foundation.h>


/**
 This interface contains data about user access token. It also stores
 access rights (offline, photo, docs, etc.), token expiration date
 and user id in VKontakte network
 */

@interface VKAccessToken : NSObject <NSCopying, NSCoding>

/**
 @name Properties
 */
/**
 Array with access rights granted
 */
@property (nonatomic, copy, readonly) NSArray *permissions;

/**
 Access token creation time
 */
@property (nonatomic, assign, readonly) NSTimeInterval creationTime;

/**
 Access token TTL
 */
@property (nonatomic, assign, readonly) NSTimeInterval liveTime;

/**
 User id in VKontakte network
 */
@property (nonatomic, assign, readonly) NSUInteger userID;

/**
 Access token
 */
@property (nonatomic, copy, readonly) NSString *token;

/**
 Is access token expired
 
 Also NO will be returned if "offline" access has been granted to the application
 */
@property (nonatomic, readonly) BOOL isExpired;

/** Is token valid
 
 Returns YES if token is not empty and not expired
 */
@property (nonatomic, readonly) BOOL isValid;

/**
 @name Initialization methods
 */
/**
 Main initialization method
 
 @param userID user id in VKontakte network.
 @param token access token
 @param liveTime access token ttl
 @param permissions list of granted permissions
 @return VKAccessToken instance
 */
- (instancetype)initWithUserID:(NSUInteger)userID
                   accessToken:(NSString *)token
                      liveTime:(NSTimeInterval)liveTime
                   permissions:(NSArray *)permissions;

/**
 Secondary initialization method
 
 permissions will be equal to  @[]
 
 @see initWithUserID:accessToken:liveTime:permissions:
 
 @param userID user id in VKontakte network.
 @param token access token
 @param liveTime access token ttl
 @return VKAccessToken instance
 */
- (instancetype)initWithUserID:(NSUInteger)userID
                   accessToken:(NSString *)token
                      liveTime:(NSTimeInterval)liveTime;

/**
 Secondary initialization method
 
 permissions will be equal to @[]
 liveTime will be equal to 0
 
 @see initWithUserID:accessToken:liveTime:permissions:
 
 @param userID user id in VKontakte network.
 @param token access token
 @return VKAccessToken instance
 */
- (instancetype)initWithUserID:(NSUInteger)userID
                   accessToken:(NSString *)token;

/**
 @name Overloaded methods
 */
/**
 Describes VKAccessToken instance state
 
 @return A string representation of the current instance
 */
- (NSString *)description;

/** Compares VKAccessTokens
 
 @param token access token which current instance will be compared to
 @return YES if tokens equal (assert the equality of tokens, list of granted accesses and user id)
 */
- (BOOL)isEqual:(VKAccessToken *)token;

/**
 @name Public methods
 */
/**
 Checks if permission has been granted
 
 @param permission permission name
 @return YES if permission was granted, otherwise NO
 */
- (BOOL)hasPermission:(NSString *)permission;

@end