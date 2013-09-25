//
// Created by AndrewShmig on 6/28/13.
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

/** List of the possible cache expiration times
 */
typedef enum
{
    
    VKCachedDataLiveTimeNever = 0,
    VKCachedDataLiveTimeOneMinute = 60,
    VKCachedDataLiveTimeThreeMinutes = 3 * 60,
    VKCachedDataLiveTimeFiveMinutes = 5 * 60,
    VKCachedDataLiveTimeOneHour = 1 * 60 * 60,
    VKCachedDataLiveTimeFiveHours = 5 * 60 * 60,
    VKCachedDataLiveTimeOneDay = 24 * 60 * 60,
    VKCachedDataLiveTimeOneWeek = 7 * 24 * 60 * 60,
    VKCachedDataLiveTimeOneMonth = 30 * 24 * 60 * 60,
    VKCachedDataLiveTimeOneYear = 365 * 24 * 60 * 60,
    
} VKCachedDataLiveTime;

/** This interface is intended for storing, retrieving and removing cache requests.
 Data will be stored on local drive and in the directory set during initialization process
 */

@interface VKCachedData : NSObject

/**
 @name Initialization methods
 */
/** Object initialization method
 
 @param path directory where cached data will be stored. If directory does not exist, it will be created
 @return VKCachedData instance
 */
- (instancetype)initWithCacheDirectory:(NSString *)path;

/**
 @name Cache management methods
 */
/** Add data in cache
 Default TTL is one hour
 
 @param cache data to be cached
 @param url url which matches to cached data
 */
- (void)addCachedData:(NSData *)cache forURL:(NSURL *)url;

/** Add data in cache
 
 @param cache data to be cached
 @param url url which matches to cached data
 @param cacheLiveTime cache ttl value. Possible options can be found in VKCachedDataLiveTime interface
 (VKCachedDataLiveTimeOneHour, VKCachedDataLiveTimeOneDay, VKCachedDataLiveTimeForever, etc.)
 */
- (void)addCachedData:(NSData *)cache
               forURL:(NSURL *)url
             liveTime:(VKCachedDataLiveTime)cacheLiveTime;

/** Remove data from cache that is associated with passed url
 
 @param url url which matches to cached data
 */
- (void)removeCachedDataForURL:(NSURL *)url;

/** Remove all cached data from the current objects instance directory
 */
- (void)clearCachedData;

/** Remove current objects directory and all cached data inside
 */
- (void)removeCachedDataDirectory;

/**
 @name Cached data retrieval methods
 */
/** Retrieve cached data which matches to passed url.
 If associated item does not exist nil will be returned
 
 @param url url which matches to cached data
 @return NSData instance
 */
- (NSData *)cachedDataForURL:(NSURL *)url;

/** Retrieve cached data which matches to passed url.
 If associated item does not exist nil will be returned
 
 If offlineMode is passed as "YES" the data will be returned from the cache even if it's expired.
 If offlineMode is equal to "NO" the cached item will be deleted if it's expired
 
 The offlineMode parameter is useful when there is no internet connection
 
 @param url url which matches to cached data
 @param offlineMode cache access offline mode
 @return NSData instance
 */
- (NSData *)cachedDataForURL:(NSURL *)url
                 offlineMode:(BOOL)offlineMode;

@end