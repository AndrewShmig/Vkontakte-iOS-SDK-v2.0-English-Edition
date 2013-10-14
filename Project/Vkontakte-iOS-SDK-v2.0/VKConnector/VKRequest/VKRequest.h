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
#import "VKCachedData.h"


/** Unknown size of the transmitted data from server
*/
#define NSURLResponseUnknownContentLength 0


/** The prefix of the URL to which requests are made to the social network API
*/
static NSString *const kVKAPIURLPrefix = @"https://api.vk.com/method/";


@class VKRequest;


/** Protocol encapsulates the basic methods for tracking status
of the request.

The only requirement is one method - a method that returns a response, other
are optional.
*/
@protocol VKRequestDelegate <NSObject>

@required
/**
@name Required
*/
/** Returns the server's response in the form of Foundation object

@param request request
@param response the response from the server as a Foundation object
*/
- (void)VKRequest:(VKRequest *)request
         response:(id)response;

@optional
/**
@name Optional
*/
/** Is called if connection error occurred

@param request request
@param error error with a description of the cause of failure
*/
- (void)     VKRequest:(VKRequest *)request
connectionErrorOccured:(NSError *)error;

/** Is called if an error occurred parsing a server response

@param request request
@param error error with a description of the causes of failure
*/
- (void)  VKRequest:(VKRequest *)request
parsingErrorOccured:(NSError *)error;

/** Is called if there is an error in the response

@param request request
@param error server response with error description
*/
- (void)   VKRequest:(VKRequest *)request
responseErrorOccured:(id)error;

/** Is called if you want to enter captcha

Additional information for handling captcha: https://github.com/AndrewShmig/Vkontakte-iOS-SDK-v2.0/issues/11

@param request request
@param captchaSid ID of a captcha
@param captchaImage link to the image you want to show the user that he enters text from
*/
- (void)VKRequest:(VKRequest *)request
       captchaSid:(NSString *)captchaSid
     captchaImage:(NSString *)captchaImage;

/** Called every time a new portion of data (method convenient
use to display the status of loading data)

@param request request
@param totalBytes the total number of bytes to retrieve. If for some
reasons cannot be determined, this number will be transferred to 0
@param downloadedBytes number of loaded bytes
*/
- (void)VKRequest:(VKRequest *)request
       totalBytes:(NSUInteger)totalBytes
  downloadedBytes:(NSUInteger)downloadedBytes;

/** Called every time sent a fresh batch of data (method convenient
use to display the status of the send data, whether it uploads audio file,
video file or document)

@param request request
@param totalBytes the total number of bytes to retrieve. If for some
reasons cannot be determined, this number will be transferred to 0
@param uploadedBytes number of loaded bytes
*/
- (void)VKRequest:(VKRequest *)request
       totalBytes:(NSUInteger)totalBytes
    uploadedBytes:(NSUInteger)uploadedBytes;

@end


/** Class to perform requests to the social network Vkontakte
*/
@interface VKRequest : NSObject <NSURLConnectionDataDelegate, NSCopying>

/**
@name Properties
*/
/** Delegate
*/
@property (nonatomic, weak, readwrite) id <VKRequestDelegate> delegate;

/** Arbitrary signature of the request. Enables you to identify the request if
one delegate performs the process of multiple requests.
*/
@property (nonatomic, strong, readwrite) id signature;

/** Cache lifetime of the current request. By default, the cache lifetime is one hour.
*/
@property (nonatomic, assign, readwrite) VKCachedDataLiveTime cacheLiveTime;

/** Offline request mode. In this mode, the data will be requested from the cache and returned
even in the case of expiration (removal will not happen).
The default mode is turned off.
*/
@property (nonatomic, assign, readwrite) BOOL offlineMode;

/**
@name Class methods
*/
/** Creates and returns a request

@param request request that will be used as the basis
@param delegate delegate to receive notifications/messages
the state of an object and data

@return an instance of the class VKRequest
*/
+ (instancetype)request:(NSURLRequest *)request
               delegate:(id <VKRequestDelegate>)delegate;

/** Creates and returns a request

@param httpMethod GET or POST
@param url the URL that will be implemented request
@param headers request headers
@param body the body of the request
@param delegate delegate to receive notifications/messages
the state of an object and data

@return an instance of the class VKRequest
*/
+ (instancetype)requestHTTPMethod:(NSString *)httpMethod
                              URL:(NSURL *)url
                          headers:(NSDictionary *)headers
                             body:(NSData *)body
                         delegate:(id <VKRequestDelegate>)delegate;

/** Creates and returns a request

@param methodName the name of the API method (users.get, groups.join etc)
@param options dictionary of parameters to be passed to this method
@param delegate delegate to receive notifications/messages
the state of an object and data

@return an instance of the class VKRequest
*/
+ (instancetype)requestMethod:(NSString *)methodName
                      options:(NSDictionary *)options
                     delegate:(id <VKRequestDelegate>)delegate;

/**
@name Instance methods
*/
/** The main methods of object initialization

@param request the request that will be used as the basis

@return an object of type VKRequest
*/
- (instancetype)initWithRequest:(NSURLRequest *)request;

/** The init method of the object

@param httpMethod GET or POST
@param url the URL that will be implemented request
@param headers request headers
@param body the body of the request

@return object type VKRequest
*/
- (instancetype)initWithHTTPMethod:(NSString *)httpMethod
                               URL:(NSURL *)url
                           headers:(NSDictionary *)headers
                              body:(NSData *)body;

/** The init method of the object

Consider this example:

VKRequest *request = [[VKRequest alloc] initWithMethod:@"users.get"
options:@{@"fields": @"nickname,bdate,status"}];

Object will be created VKRequest and subsequently implemented the method call users.get
the social network. Option fields will be equal to "nickname,bdate,status" and therefore
social network will return the nickname, date of birth and the status of the current user.

@param methodName names API method (users.get, groups.join etc)
@param options dictionary of parameters to be passed to this method

@return object class VKRequest
*/
- (instancetype)initWithMethod:(NSString *)methodName
                       options:(NSDictionary *)options;

/** Start request
*/
- (void)start;

/** Cancel request
*/
- (void)cancel;

/**
@name Add files to the body of the request
*/
/** Adding audio file data to the contents of the HTTP request body

@param file byte representation of an audio file
@param name the name of the audio file
@param field names the HTML field that was used to send a file
*/
- (void)appendAudioFile:(NSData *)file
                   name:(NSString *)name
                  field:(NSString *)field;

/** Adding video file data to the contents of the HTTP request body

@param file byte representation of a video file
@param name the name of the video file
@param field name of an HTML field which was used to send a file
*/
- (void)appendVideoFile:(NSData *)file
                   name:(NSString *)name
                  field:(NSString *)field;

/** Adding document data file the contents of the HTTP request body

@param file byte representation of the document
@param name the name of the document file
@param field name of an HTML field which was used to send a file
*/
- (void)appendDocumentFile:(NSData *)file
                      name:(NSString *)name
                     field:(NSString *)field;

/** Add the image data to the contents of the HTTP request body

@param file byte representation of the image
@param name the name of the image file
@param field name of an HTML field which was used to send a file
*/
- (void)appendImageFile:(NSData *)file
                   name:(NSString *)name
                  field:(NSString *)field;
@end