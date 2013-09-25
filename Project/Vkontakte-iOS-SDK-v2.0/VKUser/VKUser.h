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


@class VKAccessToken;
@class VKRequest;
@protocol VKRequestDelegate;

/**
 This class represents VKontakte user, which can issue API requests like
 manipulations with groups, friends, music, video, etc.
 
 You can also switch between active users (users who had been authorized before). It
 is easy to retreive this users list by calling localUsers method.
 
 @warning methods, which require access_token will in request will override
 access token to a current user access token value from self.accessToken.token
 @warning by default each request signature from VKUser instance represents
 a string of selector which initialized request
 */
@interface VKUser : NSObject

/**
 @name Properties
 */
/** VKRequest Delegate
 */
@property (nonatomic, strong, readwrite) id<VKRequestDelegate> delegate;

/** Current active user's access token
 */
@property (nonatomic, readonly) VKAccessToken *accessToken;

/** Delayed request start, by default equals to YES.
 
 For example you want to initialize something before request
 [VKUser currentUser].startAllRequestsImmediately = NO;
 VKRequest *userInfo = [[VKUser currentUser] info];
 
 // ... Something happend
 [userInfo start];
 
 Otherwise if there is no need in delayed request start
 [[VKUser currentUser] info];
 */
@property (nonatomic, assign, readwrite) BOOL startAllRequestsImmediately;

/** Offline mode. In this mode is enabled data will be returned from cache even if
 it expired. By default this mode is turned off
 */
@property (nonatomic, assign, readwrite) BOOL offlineMode;

/**
 @name Available methods
 */
/** Current active user
 
 If there is no active users in the storage nil will be returned.
 
 In case if there is no active user set, random user from the storage will be selected
 and all requests will be issues on his behalf.
 
 Q: When situation like this can appear?
 A: For example two or more users authorized, however method currentUser was not executed.
    // user A authorized
    // user B authorized
    // user C authorized
    [VKUser currentUser] // random user will be activated, or A or B or c
 
    Another example
    // user A authorized
    [VKUser currentUser] // user A will be set as active
    // user B authorized, user A still active
    // user C authorized, user A still active
 */
+ (instancetype)currentUser;

/** Set user with user id as active
 
 If user with user id does not exists in storage, than NO will be returned otherwise YES
 
 @param userID user id
 @return YES if user was activated, otherwise NO
 */
+ (BOOL)activateUserWithID:(NSUInteger)userID;

/** Retreive a list of all available users in storage
 
 @return Array with available user id's
 */
+ (NSArray *)localUsers;

/**
 @name Users
 */
/** Returns detailed information on current user
 
 Following fiends will be requested: nickname,screen_name,sex,bdate,has_mobile,online,last_seen,status,photo100
 
 @see https://vk.com/dev/users.get
 
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)info;

/** Information about user(s) with requested parameters
 
 @see https://vk.com/dev/users.get
 
 @param options parameters which will be requested
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)info:(NSDictionary *)options;

/** Returns a list of users matching the search criteria
 
 @see https://vk.com/dev/users.search
 
 @param options search criteria fields
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)search:(NSDictionary *)options;

/** Returns a list of IDs of users and communities followed by the user
 
 @see https://vk.com/dev/users.getSubscriptions
 
 @param options parameter fields
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)subscriptions:(NSDictionary *)options;

/** Returns a list of IDs of followers of the user in question, sorted by date added, most recent first
 
 @see https://vk.com/dev/users.getFollowers
 
 @param options parameter fields
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)followers:(NSDictionary *)options;

/**
 @name Redefinable methods
 */
/** Current user description
 */
- (NSString *)description;

@end

@interface VKUser (Wall)

/**
 @name Wall Api
 */
/** Returns a list of posts on a user wall or community wall
 
 @see https://vk.com/dev/wall.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallGet:(NSDictionary *)options;

/** Returns a list of posts from user or community walls by their IDs.
 
 @see https://vk.com/dev/wall.getById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallGetByID:(NSDictionary *)options;

/** Saves a post on a user wall. The post can contain a photo previously uploaded to the VK server or any available photo from one of the user's albums.
 When run from the user wall, the application opens in a 607x412-pixel window and receives the parameters described here.
 
 @see https://vk.com/dev/wall.savePost
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallSavePost:(NSDictionary *)options;

/** Adds a new post on a user wall or community wall. Can also be used to publish suggested or scheduled posts.
 
 @see https://vk.com/dev/wall.post
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallPost:(NSDictionary *)options;

/** Reposts (copies) an object to a user wall or community wall
 
 @see https://vk.com/dev/wall.repost
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallRepost:(NSDictionary *)options;

/** Returns information about reposts of a post on user wall or community wall
 
 @see https://vk.com/dev/wall.getReposts
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallGetReposts:(NSDictionary *)options;

/** Edits a post on a user wall or community wall
 
 @see https://vk.com/dev/wall.edit
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallEdit:(NSDictionary *)options;

/** Deletes a post from a user wall or community wall
 
 @see https://vk.com/dev/wall.delete
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallDelete:(NSDictionary *)options;

/** Restores a post deleted from a user wall or community wall
 
 @see https://vk.com/dev/wall.restore
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallRestore:(NSDictionary *)options;

/** Returns a list of comments on a post on a user wall or community wall
 
 @see https://vk.com/dev/wall.getComments
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallGetComments:(NSDictionary *)options;

/** Adds a comment to a post on a user wall or community wall
 
 @see http://vk.com/dev/wall.addComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallAddComment:(NSDictionary *)options;

/** Deletes a comment on a post on a user wall or community wall
 
 @see https://vk.com/dev/wall.deleteComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallDeleteComment:(NSDictionary *)options;

/** Restores a comment deleted from a user wall or community wall
 
 @see https://vk.com/dev/wall.restoreComment
 
 @param options parameters list 
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)wallRestoreComment:(NSDictionary *)options;

@end

@interface VKUser (Photos)

/**
 @name Photos
 */
/** Creates an empty photo album
 
 @see https://vk.com/dev/photos.createAlbum
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosCreateAlbum:(NSDictionary *)options;

/** Edits album data for the user's photos.
 
 @see https://vk.com/dev/photos.editAlbum
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosEditAlbum:(NSDictionary *)options;

/** Returns a list of a user's or community's photo albums
 
 @see https://vk.com/dev/photos.getAlbums
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetAlbums:(NSDictionary *)options;

/** Returns a list of a user's or community's photos
 
 @see https://vk.com/dev/photos.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGet:(NSDictionary *)options;

/** Returns the number of albums belonging to a user or community
 
 @see https://vk.com/dev/photos.getAlbumsCount
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetAlbumsCount:(NSDictionary *)options;

/** Returns a list of photos from a user's or community's page
 
 @see https://vk.com/dev/photos.getProfile
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetProfile:(NSDictionary *)options;

/** Returns information about photos by their IDs
 
 @see https://vk.com/dev/photos.getById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetByID:(NSDictionary *)options;

/** Returns the server address for photo upload.
 When uploaded successfully, the photo can be saved with the photos.save method
 
 @see https://vk.com/dev/photos.getUploadServer
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetUploadServer:(NSDictionary *)options;

/** Returns server address for photo upload onto a user's page.
 When uploaded successfully, the photo can be saved with the photos.saveProfilePhoto method
 
 @see https://vk.com/dev/photos.getProfileUploadServer
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetProfileUploadServer:(NSDictionary *)options;

/** Returns an upload link for multichat cover pictures
 
 @see https://vk.com/dev/photos.getChatUploadServer
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetChatUploadServer:(NSDictionary *)options;

/** Saves a user's photo after being uploaded successfully.
 You can get an address for photo upload with photos.getProfileUploadServer method
 
 @see https://vk.com/dev/photos.saveProfilePhoto
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosSaveProfilePhoto:(NSDictionary *)options;

/** Saves a photo after being uploaded successfully. URL obtained with photos.getWallUploadServer method
 
 @see https://vk.com/dev/photos.saveWallPhoto
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosSaveWallPhoto:(NSDictionary *)options;

/** Returns the server address for photo upload onto a user's wall.
 When uploaded successfully, the photo can be saved using the photos.saveWallPhoto method
 
 @see https://vk.com/dev/photos.getWallUploadServer
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetWallUploadServer:(NSDictionary *)options;

/** Returns the server address for photo upload in a private message for a user.
 When uploaded successfully, the photo can be saved using the photos.saveMessagesPhoto method
 
 @see https://vk.com/dev/photos.getMessagesUploadServer
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetMessagesUploadServer:(NSDictionary *)options;

/** Saves a photo after being successfully uploaded. URL obtained with photos.getMessagesUploadServer method
 
 @see https://vk.com/dev/photos.saveMessagesPhoto
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosSaveMessagesPhoto:(NSDictionary *)options;

/** Returns a list of photos by search criteria
 
 @see https://vk.com/dev/photos.search
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosSearch:(NSDictionary *)options;

/** Saves photos after successful uploading
 
 @see https://vk.com/dev/photos.save
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosSave:(NSDictionary *)options;

/** Edits the caption of a photo
 
 @see https://vk.com/dev/photos.edit
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosEdit:(NSDictionary *)options;

/** Moves a photo from one album to another
 
 @see https://vk.com/dev/photos.move
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosMove:(NSDictionary *)options;

/** Makes a photo into an album cover
 
 @see https://vk.com/dev/photos.makeCover
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosMakeCover:(NSDictionary *)options;

/** Reorders the album in the list of user albums
 
 @see https://vk.com/dev/photos.reorderAlbums
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosReorderAlbums:(NSDictionary *)options;

/** Reorders the photo in the list of photos of the user album
 
 @see https://vk.com/dev/photos.reorderPhotos
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosReorderPhotos:(NSDictionary *)options;

/** Returns a list of photos belonging to a user or community, in reverse chronological order
 
 @see https://vk.com/dev/photos.getAll
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetAll:(NSDictionary *)options;

/** Returns a list of photos in which a user is tagged
 
 @see https://vk.com/dev/photos.getUserPhotos
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetUserPhotos:(NSDictionary *)options;

/** Deletes a photo album belonging to the current user
 
 @see https://vk.com/dev/photos.deleteAlbum
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosDeleteAlbum:(NSDictionary *)options;

/** Deletes a photo
 
 @see https://vk.com/dev/photos.delete
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosDelete:(NSDictionary *)options;

/** Confirms a tag on a photo
 
 @see https://vk.com/dev/photos.confirmTag
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosConfirmTagWithCusomOptions:(NSDictionary *)options;

/** Returns a list of comments on a photo
 
 @see https://vk.com/dev/photos.getComments
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetComments:(NSDictionary *)options;

/** Returns a list of comments on a specific photo album or all albums of the user sorted in reverse chronological order
 
 @see https://vk.com/dev/photos.getAllComments
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetAllComments:(NSDictionary *)options;

/** Adds a new comment on the photo
 
 @see https://vk.com/dev/photos.createComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosCreateComment:(NSDictionary *)options;

/** Deletes a comment on the photo
 
 @see https://vk.com/dev/photos.deleteComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosDeleteComment:(NSDictionary *)options;

/** Restores a deleted comment on a photo
 
 @see https://vk.com/dev/photos.restoreComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosRestoreComment:(NSDictionary *)options;

/** Edits a comment on a photo
 
 @see https://vk.com/dev/photos.editComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosEditComment:(NSDictionary *)options;

/** Returns a list of tags on a photo
 
 @see https://vk.com/dev/photos.getTags
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetTags:(NSDictionary *)options;

/** Adds a tag on the photo
 
 @see https://vk.com/dev/photos.putTag
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosPutTag:(NSDictionary *)options;

/** Removes a tag from a photo
 
 @see https://vk.com/dev/photos.removeTag
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosRemoveTag:(NSDictionary *)options;

/** Returns a list of photos with tags that have not been viewed
 
 @see https://vk.com/dev/photos.getNewTags
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)photosGetNewTags:(NSDictionary *)options;

@end

@interface VKUser (Friends)

/**
 @name Friends
 */
/** Returns a list of IDs of a user's friends or detailed information about a user's friends
 
 @see https://vk.com/dev/friends.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsGet:(NSDictionary *)options;

/** Returns a list of IDs of a user's friends who are online
 
 @see https://vk.com/dev/friends.getOnline
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsGetOnline:(NSDictionary *)options;

/** Returns a list of IDs of the mutual friends of two users
 
 @see https://vk.com/dev/friends.getMutual
 
 @param options parameters list https://vk.com/dev/friends.getMutual
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsGetMutual:(NSDictionary *)options;

/** Returns a list of IDs of the current's user recently added friends
 
 @see https://vk.com/dev/friends.getRecent
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsGetRecent:(NSDictionary *)options;

/** Returns information about a user's incoming and outgoing friend requests
 
 @see https://vk.com/dev/friends.getRequests
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsGetRequests:(NSDictionary *)options;

/** Approves or creates a friend request.
 If the selected user ID is in the friend request list obtained using the friends.getRequests method, approves the friend request and adds the selected user to the current user's friend list. Otherwise, creates a friend request from the current user for the selected user.
 
 @see https://vk.com/dev/friends.add
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsAdd:(NSDictionary *)options;

/** Edits lists of friends for the selected friend.
 
 @see https://vk.com/dev/friends.edit
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsEdit:(NSDictionary *)options;

/** Deletes a user from the current user's friend list or declines a friend request.
 If the selected user ID is in the friend request list obtained using the friends.getRequests method, declines the friend request for the current user. Otherwise, deletes the selected user from the friend list of the current user obtained using the friends.get method.
 
 @see https://vk.com/dev/friends.delete
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsDelete:(NSDictionary *)options;

/** Returns a friend tag list of the current user
 
 @see https://vk.com/dev/friends.getLists
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsGetLists:(NSDictionary *)options;

/** Creates a new friend list for the current user
 
 @see https://vk.com/dev/friends.addList
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsAddList:(NSDictionary *)options;

/** Edits an existing friend list of the current user
 
 @see https://vk.com/dev/friends.editList
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsEditList:(NSDictionary *)options;

/** Deletes an existing friend list of the current user
 
 @see https://vk.com/dev/friends.deleteList
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsDeleteList:(NSDictionary *)options;

/** Returns a list of IDs of the current user's friends who installed the application
 
 @see https://vk.com/dev/friends.getAppUsers
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsGetAppUsers:(NSDictionary *)options;

/** Returns a list of user's friends whose phone numbers, validated or specified in a profile, are in the list.
 The method can only be used if current user's mobile phone number is validated. To check this condition you can use the users.get method with uids=API_USER and fields=has_mobile parameters where API_USER is equal to current user ID.
 
 @see https://vk.com/dev/friends.getByPhones
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsGetByPhones:(NSDictionary *)options;

/** Marks all incoming friend requests as viewed
 
 @see https://vk.com/dev/friends.deleteAllRequests
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsDeleteAllRequests:(NSDictionary *)options;

/** Returns a list of profiles of users the current user may know.
 For the method to return enough suggestions, method account.importContacts shall be called first.
 
 @see https://vk.com/dev/friends.getSuggestions
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsGetSuggestions:(NSDictionary *)options;

/** Returns information whether the current user is a friend of the specified users.
 Also, returns information whether there is an outgoing or incoming friend request (new follower).
 
 @see https://vk.com/dev/friends.areFriends
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)friendsAreFriends:(NSDictionary *)options;

@end

@interface VKUser (Groups)

/**
 @name Groups
 */
/** Returns information specifying whether a user is a member of a community
 
 @see https://vk.com/dev/groups.isMember
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)groupsIsMember:(NSDictionary *)options;

/** Returns information about communities by their IDs.
 
 @see https://vk.com/dev/groups.getById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)groupsGetByID:(NSDictionary *)options;

/** Returns a list of the communities to which a user belongs
 
 @see https://vk.com/dev/groups.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)groupsGet:(NSDictionary *)options;

/** Returns a list of community members
 
 @see https://vk.com/dev/groups.getMembers
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)groupsGetMembers:(NSDictionary *)options;

/** With this method you can join the group or public page, and also confirm your participation in an event
 
 @see https://vk.com/dev/groups.join
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)groupsJoin:(NSDictionary *)options;

/** With this method you can leave a group, public page, or event
 
 @see https://vk.com/dev/groups.leave
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)groupsLeave:(NSDictionary *)options;

/** Searches for communities by substring
 
 @see https://vk.com/dev/groups.search
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)groupsSearch:(NSDictionary *)options;

/** Returns a list of invitations to join communities and events
 
 @see https://vk.com/dev/groups.getInvites
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)groupsGetInvites:(NSDictionary *)options;

/** Adds a user to a community blacklist
 
 @see https://vk.com/dev/groups.banUser
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)groupsBanUser:(NSDictionary *)options;

/** Deletes a user from a community blacklist
 
 @see https://vk.com/dev/groups.unbanUser
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)groupsUnbanUser:(NSDictionary *)options;

/** Returns a list of users on a community blacklist
 
 @see https://vk.com/dev/groups.getBanned
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)groupsGetBanned:(NSDictionary *)options;

@end

@interface VKUser (Video)

/**
 @name Video
 */
/** Returns detailed information about videos
 
 @see https://vk.com/dev/video.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoGet:(NSDictionary *)options;

/** Edits video information on a user's page
 
 @see https://vk.com/dev/video.edit
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoEdit:(NSDictionary *)options;

/** Adds a video to user list
 
 @see https://vk.com/dev/video.add
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoAdd:(NSDictionary *)options;

/** Returns a server address (required for upload) and video data
 
 @see https://vk.com/dev/video.save
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoSave:(NSDictionary *)options;

/** Deletes a video from user's page
 
 @see https://vk.com/dev/video.delete
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoDelete:(NSDictionary *)options;

/** Restores a video after being deleted
 
 @see https://vk.com/dev/video.restore
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoRestore:(NSDictionary *)options;

/**Returns a list of videos under the set search criteria
 
 @see https://vk.com/dev/video.search
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoSearch:(NSDictionary *)options;

/** Returns list of videos in which the user is tagged
 
 @see https://vk.com/dev/video.getUserVideos
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoGetUserVideos:(NSDictionary *)options;

/** Returns a list of video albums owned by the user or community
 
 @see https://vk.com/dev/video.getAlbums
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoGetAlbums:(NSDictionary *)options;

/** Creates an empty album for videos
 
 @see https://vk.com/dev/video.addAlbum
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoAddAlbum:(NSDictionary *)options;

/** Edits the name of a video album
 
 @see https://vk.com/dev/video.editAlbum
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoEditAlbum:(NSDictionary *)options;

/** Deletes a video album
 
 @see https://vk.com/dev/video.deleteAlbum
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoDeleteAlbum:(NSDictionary *)options;

/** Moves videos to an album
 
 @see https://vk.com/dev/video.moveToAlbum
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoMoveToAlbum:(NSDictionary *)options;

/** Returns a list of comments on a video
 
 @see https://vk.com/dev/video.getComments
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoGetComments:(NSDictionary *)options;

/** Adds a new comment on the video
 
 @see https://vk.com/dev/video.createComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoCreateComment:(NSDictionary *)options;

/** Deletes a comment on a video
 
 @see https://vk.com/dev/video.deleteComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoDeleteComment:(NSDictionary *)options;

/** Restores a comment on a video
 
 @see https://vk.com/dev/video.restoreComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoRestoreComment:(NSDictionary *)options;

/** Edits the text of a comment on a video
 
 @see https://vk.com/dev/video.editComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoEditComment:(NSDictionary *)options;

/** Returns a list of tags on a video
 
 @see https://vk.com/dev/video.getTags
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoGetTags:(NSDictionary *)options;

/** Adds a tag on a video
 
 @see https://vk.com/dev/video.putTag
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoPutTag:(NSDictionary *)options;

/** Removes a tag from a video
 
 @see https://vk.com/dev/video.removeTag
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoRemoveTag:(NSDictionary *)options;

/** Returns a list of videos with tags that have not been viewed
 
 @see https://vk.com/dev/video.getNewTags
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoGetNewTags:(NSDictionary *)options;

/** Allows to report a video
 
 @see https://vk.com/dev/video.report
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)videoReport:(NSDictionary *)options;

@end

@interface VKUser (Audio)

/**
 @name Audio
 */
/** Returns a list of audio files of a user or community
 
 @see https://vk.com/dev/audio.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioGet:(NSDictionary *)options;

/** Returns information about audio files by their IDs
 
 @see https://vk.com/dev/audio.getById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioGetByID:(NSDictionary *)options;

/** Returns lyrics corresponding to an audio file.
 The lyrics_id parameter is required for text identification and can be received using audio.get, audio.getById or audio.search method
 
 @see https://vk.com/dev/audio.getLyrics
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioGetLyrics:(NSDictionary *)options;

/** Returns a list of audio files
 
 @see https://vk.com/dev/audio.search
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioSearch:(NSDictionary *)options;

/** Returns server address to upload audio files
 
 @see https://vk.com/dev/audio.getUploadServer
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioGetUploadServer:(NSDictionary *)options;

/** Saves audio files after successful uploading
 
 @see https://vk.com/dev/audio.save
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioSave:(NSDictionary *)options;

/** Copies an audio file to a user page or community page
 
 @see https://vk.com/dev/audio.add
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioAdd:(NSDictionary *)options;

/** Deletes an audio file from a user page or community page
 
 @see https://vk.com/dev/audio.delete
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioDelete:(NSDictionary *)options;

/** Edits an audio file on a user or community page
 
 @see https://vk.com/dev/audio.edit
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioEdit:(NSDictionary *)options;

/** Reorders the audio file, placing it between audio files with IDs specified by after and before parameters
 
 @see https://vk.com/dev/audio.reorder
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioReorder:(NSDictionary *)options;

/** Restores a deleted audio file
 
 @see https://vk.com/dev/audio.restore
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioRestore:(NSDictionary *)options;

/** Returns a list of audio albums of a user or community
 
 @see https://vk.com/dev/audio.getAlbums
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioGetAlbums:(NSDictionary *)options;

/** Creates an empty audio album
 
 @see https://vk.com/dev/audio.addAlbum
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioAddAlbum:(NSDictionary *)options;

/** Edits the title of an audio album
 
 @see https://vk.com/dev/audio.editAlbum
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioEditAlbum:(NSDictionary *)options;

/** Deletes an audio album
 
 @see https://vk.com/dev/audio.deleteAlbum
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioDeleteAlbum:(NSDictionary *)options;

/** Moves audio files to an album
 
 @see https://vk.com/dev/audio.moveToAlbum
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioMoveToAlbum:(NSDictionary *)options;

/** Activates an audio broadcast to the status of a user or community
 
 @see https://vk.com/dev/audio.setBroadcast
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioSetBroadcast:(NSDictionary *)options;

/** Returns a list of the user's friends and communities that are broadcasting music in their status messages
 
 @see https://vk.com/dev/audio.getBroadcastList
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioGetBroadcastList:(NSDictionary *)options;

/** Returns a list of suggested audio files based on a user's playlist or a particular audio file
 
 @see https://vk.com/dev/audio.getRecommendations
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioGetRecommendations:(NSDictionary *)options;

/** Returns an audio list from the "Popular"
 
 @see https://vk.com/dev/audio.getPopular
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioGetPopular:(NSDictionary *)options;

/** Returns the total number of audio files on a user or community page
 
 @see https://vk.com/dev/audio.getCount
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)audioGetCount:(NSDictionary *)options;

@end

@interface VKUser (Messages)

/**
 @name Messages
 */
/** Returns a list of incoming or outgoing private messages of the current user
 
 @see https://vk.com/dev/messages.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesGet:(NSDictionary *)options;

/** Returns a list of current user's conversations
 
 @see https://vk.com/dev/messages.getDialogs
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesGetDialogs:(NSDictionary *)options;

/** Returns messages by their id
 
 @see https://vk.com/dev/messages.getById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesGetByID:(NSDictionary *)options;

/** Returns a list of found private messages of the current user by filled-in search bar
 
 @see https://vk.com/dev/messages.search
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesSearch:(NSDictionary *)options;

/** Returns message history for the specified user or group chat
 
 @see https://vk.com/dev/messages.getHistory
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesGetHistory:(NSDictionary *)options;

/** Sends a message
 
 @see https://vk.com/dev/messages.send
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesSend:(NSDictionary *)options;

/** Deletes a message
 
 @see https://vk.com/dev/messages.delete
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesDelete:(NSDictionary *)options;

/** Deletes all private messages in conversation
 
 @see https://vk.com/dev/messages.deleteDialog
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesDeleteDialog:(NSDictionary *)options;

/** Restores deleted message
 
 @see https://vk.com/dev/messages.restore
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesRestore:(NSDictionary *)options;

/** Marks messages as unread
 
 @see https://vk.com/dev/messages.markAsNew
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesMarkAsNew:(NSDictionary *)options;

/** Marks messages as read
 
 @see https://vk.com/dev/messages.markAsRead
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesMarkAsRead:(NSDictionary *)options;

/** Marks and unmarks messages as important (starred)
 
 @see https://vk.com/dev/messages.markAsImportant
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesMarkAsImportant:(NSDictionary *)options;

/** Returns data required for connection to a Long Poll server.
 With Long Poll connection you can immediately know about incoming messages and other events
 
 @see https://vk.com/dev/messages.getLongPollServer
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesGetLongPollServer:(NSDictionary *)options;

/** Returns updates in user's private messages.
 To speed up handling of private messages it can be useful to cache previously loaded messages on a user's mobile device/desktop, to prevent re-receipt at each call. With this method you can synchronize a local copy of the message list with the actual version.
 
 @see https://vk.com/dev/messages.getLongPollHistory
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesGetLongPollHistory:(NSDictionary *)options;

/** Returns information about a chat
 
 @see https://vk.com/dev/messages.getChat
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesGetChat:(NSDictionary *)options;

/** Creates a chat with several participants
 
 @see https://vk.com/dev/messages.createChat
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesCreateChat:(NSDictionary *)options;

/** Changes chat title
 
 @see https://vk.com/dev/messages.editChat
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesEditChat:(NSDictionary *)options;

/** Gets a list of multi-conversation users by its id
 
 @see https://vk.com/dev/messages.getChatUsers
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesGetChatUsers:(NSDictionary *)options;

/** Changes status of a user typing in conversation
 
 @see https://vk.com/dev/messages.setActivity
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesSetActivity:(NSDictionary *)options;

/** Returns a list of found conversations of the current user by filled-in search bar
 
 @see https://vk.com/dev/messages.searchDialogs
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesSearchDialogs:(NSDictionary *)options;

/** Adds new user to a multi-conversation
 
 @see https://vk.com/dev/messages.addChatUser
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesAddChatUser:(NSDictionary *)options;

/** Removes a user from the multi-conversation, if the current user was a chat starter or invited a user to be removed.
 Also it can be used for exit of the current user from the chat he/she participates in
 
 @see https://vk.com/dev/messages.removeChatUser
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesRemoveChatUser:(NSDictionary *)options;

/** Returns current status and date of last activity of the specified user
 
 @see https://vk.com/dev/messages.getLastActivity
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesGetLastActivity:(NSDictionary *)options;

/** Sets a picture as cover picture in a multichat. To upload the picture use photos.getChatUploadServer
 
 @see https://vk.com/dev/messages.setChatPhoto
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesSetChatPhoto:(NSDictionary *)options;

/** Deletes a multichat cover picture
 
 @see https://vk.com/dev/messages.deleteChatPhoto
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)messagesDeleteChatPhoto:(NSDictionary *)options;

@end

@interface VKUser (Newsfeed)

/**
 @name Newsfeed
 */
/** Returns data required to show newsfeed for the current user
 
 @see https://vk.com/dev/newsfeed.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)newsfeedGet:(NSDictionary *)options;

/** Returns a list of newsfeeds recommended to the current user
 
 @see https://vk.com/dev/newsfeed.getRecommended
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)newsfeedGetRecommended:(NSDictionary *)options;

/** Returns a list of comments in the current user's newsfeed
 
 @see https://vk.com/dev/newsfeed.getComments
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)newsfeedGetComments:(NSDictionary *)options;

/** Returns a list of posts on user walls in which the current user is mentioned
 
 @see https://vk.com/dev/newsfeed.getMentions
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)newsfeedGetMentions:(NSDictionary *)options;

/** Returns a list of users and communities banned from the current user's newsfeed
 
 @see https://vk.com/dev/newsfeed.getBanned
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)newsfeedGetBanned:(NSDictionary *)options;

/** Prevents news from specified users and communities from appearing in the current user's newsfeed
 
 @see https://vk.com/dev/newsfeed.addBan
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)newsfeedAddBan:(NSDictionary *)options;

/** Allows news from previously banned users and communities to be shown in the current user's newsfeed
 
 @see https://vk.com/dev/newsfeed.deleteBan
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)newsfeedDeleteBan:(NSDictionary *)options;

/** Returns search results by statuses
 
 @see https://vk.com/dev/newsfeed.search
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)newsfeedSearch:(NSDictionary *)options;

/** Returns a list of newsfeeds followed by the current user
 
 @see https://vk.com/dev/newsfeed.getLists
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)newsfeedGetLists:(NSDictionary *)options;

/** Unsubscribes the current user from specified newsfeeds
 
 @see https://vk.com/dev/newsfeed.unsubscribe
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)newsfeedUnsubscribe:(NSDictionary *)options;

@end

@interface VKUser (Likes)

/**
 @name Likes
 */
/** Returns a list of IDs of users who added the specified object to their Likes list
 
 @see https://vk.com/dev/likes.getList
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)likesGetList:(NSDictionary *)options;

/** Adds the specified object to the Likes list of the current user
 
 @see https://vk.com/dev/likes.add
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)likesAdd:(NSDictionary *)options;

/** Deletes the specified object from the Likes list of the current user
 
 @see https://vk.com/dev/likes.delete
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)likesDelete:(NSDictionary *)options;

/** Checks if the object is in Likes list of the specified user
 
 @see https://vk.com/dev/likes.isLiked
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)likesIsLiked:(NSDictionary *)options;

@end

@interface VKUser (Account)
/**
 * @name Account
 */
/** Returns non-null values of user counters
 
 @see https://vk.com/dev/account.getCounters
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountGetCounters:(NSDictionary *)options;

/** Sets an application screen name (up to 17 characters), that is shown to the user in the left menu.
 This happens only in case the user added such application in the left menu from application page, from list of applications and settings
 
 @see https://vk.com/dev/account.setNameInMenu
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountSetNameInMenu:(NSDictionary *)options;

/** Marks the current user as online for 15 minutes
 
 @see https://vk.com/dev/account.setOnline
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountSetOnline:(NSDictionary *)options;

/** Gets user's contact list to search VK-registered users with friends.getSuggestions method
 
 @see https://vk.com/dev/account.importContacts
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountImportContacts:(NSDictionary *)options;

/** Subscribes an iOS/Android-based device to receive push notifications
 
 @see https://vk.com/dev/account.registerDevice
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountRegisterDevice:(NSDictionary *)options;

/** Unsubscribes a device from push notifications
 
 @see https://vk.com/dev/account.unregisterDevice
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountUnregisterDevice:(NSDictionary *)options;

/** Mutes in parameters of sent push notifications for the set period of time
 
 @see https://vk.com/dev/account.setSilenceMode
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountSetSilenceMode:(NSDictionary *)options;

/** Gets settings of push notifications
 
 @see https://vk.com/dev/account.getPushSettings
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountGetPushSettings:(NSDictionary *)options;

/** Gets settings of the current user in this application
 
 @see https://vk.com/dev/account.getAppPermissions
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountGetAppPermissions:(NSDictionary *)options;

/** Returns a list of active ads (offers) which executed by the user will bring him/her respective number of votes to his balance in the application.
 To show the user one or all ads you can use showLeadsPaymentBox JS API method. After the user completed one of the campaigns offer to him/her, votes will be automatically entered to user's balance in the application. In this case, the application can write off the required number of votes by converting them into the application's internal currency.
 
 @see https://vk.com/dev/account.getActiveOffers
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountGetActiveOffers:(NSDictionary *)options;

/** Adds user to the banlist
 
 @see https://vk.com/dev/account.banUser
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountBanUser:(NSDictionary *)options;

/** Deletes user from the banlist
 
 @see https://vk.com/dev/account.unbanUser
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountUnbanUser:(NSDictionary *)options;

/** Returns a user's blacklist
 
 @see https://vk.com/dev/account.getBanned
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)accountGetBanned:(NSDictionary *)options;

@end

@interface VKUser (Status)
/**
 * @name Status
 */
/** Returns text of the status of a user or community
 
 @see https://vk.com/dev/status.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)statusGet:(NSDictionary *)options;

/** Sets a new status for the current user
 
 @see https://vk.com/dev/status.set
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)statusSet:(NSDictionary *)options;

@end

@interface VKUser (Pages)
/**
 * @name Pages
 */
/** Returns information about a wiki page
 
 @see https://vk.com/dev/pages.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)pagesGet:(NSDictionary *)options;

/** Saves the text of a wiki page
 
 @see https://vk.com/dev/pages.save
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)pagesSave:(NSDictionary *)options;

/** Saves modified read and edit access settings for a wiki page
 
 @see https://vk.com/dev/pages.saveAccess
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)pagesSaveAccess:(NSDictionary *)options;

/** Returns a list of all previous versions of a wiki page
 
 @see https://vk.com/dev/pages.getHistory
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)pagesGetHistory:(NSDictionary *)options;

/** Returns a list of wiki pages in a group
 
 @see https://vk.com/dev/pages.getTitles
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)pagesGetTitles:(NSDictionary *)options;

/** Returns the text of one of the previous versions of a wiki page
 
 @see https://vk.com/dev/pages.getVersion
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)pagesGetVersion:(NSDictionary *)options;

/** Returns HTML representation of the wiki markup
 
 @see https://vk.com/dev/pages.parseWiki
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)pagesParseWiki:(NSDictionary *)options;

@end

@interface VKUser (Board)
/**
 * @name Board
 */

/** Returns a list of topics within the discussion board of the specified group
 
 @see https://vk.com/dev/board.getTopics
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardGetTopics:(NSDictionary *)options;

/** Returns a list of comments in the specified topic
 
 @see https://vk.com/dev/board.getComments
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardGetComments:(NSDictionary *)options;

/** Creates a new topic in the list of the group discussion board
 
 @see https://vk.com/dev/board.addTopic
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardAddTopic:(NSDictionary *)options;

/** Adds a new comment in the community topic
 
 @see https://vk.com/dev/board.addComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardAddComment:(NSDictionary *)options;

/** Deletes a topic form a group board
 
 @see https://vk.com/dev/board.deleteTopic
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardDeleteTopic:(NSDictionary *)options;

/** Edits topic title in the list of the group discussion board
 
 @see https://vk.com/dev/board.editTopic
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardEditTopic:(NSDictionary *)options;

/** Edits one of the comments in the group topic
 
 @see https://vk.com/dev/board.editComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardEditComment:(NSDictionary *)options;

/** Restores a deleted comment of the topic in the group discussion board
 
 @see https://vk.com/dev/board.restoreComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardRestoreComment:(NSDictionary *)options;

/** Deletes comment in the topic of the group discussion board
 
 @see https://vk.com/dev/board.deleteComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardDeleteComment:(NSDictionary *)options;

/** Opens a topic which was earlier closed (it will be possible to post new messages in this topic)
 
 @see https://vk.com/dev/board.openTopic
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardOpenTopic:(NSDictionary *)options;

/** Closes a topic in the list of group threads (no messages can be posted in this topic)
 
 @see https://vk.com/dev/board.closeTopic
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardCloseTopic:(NSDictionary *)options;

/** Fixes a topic in the list of group threads (when sorting, this topic will always be shown in the top)
 
 @see https://vk.com/dev/board.fixTopic
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardFixTopic:(NSDictionary *)options;

/** Unfixes a topic in the list of group threads (this topic will be shown in accordance with the chosen type of sorting)
 
 @see https://vk.com/dev/board.unfixTopic
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)boardUnfixTopic:(NSDictionary *)options;

@end

@interface VKUser (Notes)
/**
 * @name Notes
 */

/** Returns a list of notes created by a user
 
 @see https://vk.com/dev/notes.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notesGet:(NSDictionary *)options;

/** Returns a note by its ID
 
 @see https://vk.com/dev/notes.getById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notesGetByID:(NSDictionary *)options;

/** Returns a list of a user's friends' notes
 
 @see https://vk.com/dev/notes.getFriendsNotes
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notesGetFriendsNotes:(NSDictionary *)options;

/** Creates a new note for the current user
 
 @see https://vk.com/dev/notes.add
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notesAdd:(NSDictionary *)options;

/** Edits a note of the current user
 
 @see https://vk.com/dev/notes.edit
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notesEdit:(NSDictionary *)options;

/** Deletes a note of the current user
 
 @see https://vk.com/dev/notes.delete
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notesDelete:(NSDictionary *)options;

/** Returns a list of comments on a note
 
 @see https://vk.com/dev/notes.getComments
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notesGetComments:(NSDictionary *)options;

/** Adds a new comment on a note
 
 @see https://vk.com/dev/notes.createComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notesCreateComment:(NSDictionary *)options;

/** Edits a comment on a note
 
 @see https://vk.com/dev/notes.editComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notesEditComment:(NSDictionary *)options;

/** Deletes a comment on a note
 
 @see https://vk.com/dev/notes.deleteComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notesDeleteComment:(NSDictionary *)options;

/** Restores a deleted comment on a note
 
 @see https://vk.com/dev/notes.restoreComment
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notesRestoreComment:(NSDictionary *)options;

@end

@interface VKUser (Places)
/**
 * @name Places
 */

/** Adds a new location into the location database.
 Created location will be shown in search by locations only for the user who added it.
 
 @see https://vk.com/dev/places.add
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesAdd:(NSDictionary *)options;

/** Returns information about locations by their IDs.
 
 @see https://vk.com/dev/places.getById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesGetByID:(NSDictionary *)options;

/** Returns a list of locations, found under the specified search criteria.
 Locations, added by website moderators and the current user, are searched. Locations are shown in the list sorted by increase of the distance from the initial search point.
 
 @see https://vk.com/dev/places.search
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesSearch:(NSDictionary *)options;

/** Checks a user in at the specified location
 
 @see https://vk.com/dev/places.checkin
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesCheckIn:(NSDictionary *)options;

/** Returns a list of user check-ins at locations according to the set parameters
 
 @see https://vk.com/dev/places.getCheckins
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesGetCheckins:(NSDictionary *)options;

/** Returns a list of all types of locations
 
 @see https://vk.com/dev/places.getTypes
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesGetTypes:(NSDictionary *)options;

/** Returns a list of countries
 
 @see https://vk.com/dev/places.getCountries
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesGetContries:(NSDictionary *)options;

/** Returns a list of regions
 
 @see https://vk.com/dev/places.getRegions
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesGetRegions:(NSDictionary *)options;

/** Returns an information about streets by their IDs
 
 @see https://vk.com/dev/places.getStreetById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesGetStreetByID:(NSDictionary *)options;

/** Returns information about countries by their IDs
 
 @see https://vk.com/dev/places.getCountryById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesGetCountryByID:(NSDictionary *)options;

/** Returns a list of cities
 
 @see https://vk.com/dev/places.getCities
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesGetCities:(NSDictionary *)options;

/** Returns information about cities by their IDs
 
 @see https://vk.com/dev/places.getCityById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)placesGetCityByID:(NSDictionary *)options;

@end

@interface VKUser (Polls)
/**
 * @name Polls
 */
/** Returns detailed information about a poll by its ID
 
 @see https://vk.com/dev/polls.getById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)pollsGetByID:(NSDictionary *)options;

/** Adds the current user's vote to the selected answer in the poll
 
 @see https://vk.com/dev/polls.addVote
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)pollsAddVote:(NSDictionary *)options;

/** Deletes the current user's vote from the selected answer in the poll
 
 @see https://vk.com/dev/polls.deleteVote
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)pollsDeleteVote:(NSDictionary *)options;

/** Returns a list of IDs of users who selected specific answers in the poll
 
 @see  https://vk.com/dev/polls.getVoters
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)pollsGetVoters:(NSDictionary *)options;

@end

@interface VKUser (Docs)
/**
 * @name Docs
 */
/** Returns detailed information about user or community documents
 
 @see https://vk.com/dev/docs.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)docsGet:(NSDictionary *)options;

/** Returns information about documents by their IDs
 
 @see https://vk.com/dev/docs.getById
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)docsGetByID:(NSDictionary *)options;

/** Returns server address to upload documents
 
 @see https://vk.com/dev/docs.getUploadServer
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)docsGetUploadServer:(NSDictionary *)options;

/** Returns a server address to upload documents to Sent folder, so the document can be posted on the wall or sent as a private message later
 
 @see https://vk.com/dev/docs.getWallUploadServer
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)docsGetWallUploadServer:(NSDictionary *)options;

/** Saves a document after uploading it to a server
 
 @see https://vk.com/dev/docs.save
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)docsSave:(NSDictionary *)options;

/** Deletes user or community documents
 
 @see https://vk.com/dev/docs.delete
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)docsDelete:(NSDictionary *)options;

/** Copies a document to a user's document list
 
 @see https://vk.com/dev/docs.add
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)docsAdd:(NSDictionary *)options;

@end

@interface VKUser (Fave)
/**
 * @name Fave
 */

/** Returns a list of users who are added to Bookmarks by the current user
 
 @see https://vk.com/dev/fave.getUsers
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)faveGetUsers:(NSDictionary *)options;

/** Returns a list of photos marked as Liked by the current user
 
 @see https://vk.com/dev/fave.getPhotos
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)faveGetPhotos:(NSDictionary *)options;

/** Returns a list of wall posts marked as Liked by the current user
 
 @see https://vk.com/dev/fave.getPosts
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)faveGetPosts:(NSDictionary *)options;

/** Returns a list of videos marked as Liked by the current user
 
 @see https://vk.com/dev/fave.getVideos
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)faveGetVideos:(NSDictionary *)options;

/** Returns a list of links who are added to Bookmarks by the current user
 
 @see https://vk.com/dev/fave.getLinks
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)faveGetLinks:(NSDictionary *)options;

@end

@interface VKUser (Notifications)
/**
 * @name Notifications
 */
/** Returns a list of notifications about feedback of other users to the current user's wall posts
 
 @see https://vk.com/dev/notifications.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notificationsGet:(NSDictionary *)options;

/** Resets the counter of new notifications about feedback of other users to the current user's entries
 
 @see https://vk.com/dev/notifications.markAsViewed
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)notificationsMarkeAsViewed:(NSDictionary *)options;

@end

@interface VKUser (Stats)
/**
 * @name Stats
 */

/** Returns statistics of a community or an application
 
 @see https://vk.com/dev/stats.get
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)statsGet:(NSDictionary *)options;

@end

@interface VKUser (Search)
/**
 * @name Search
 */

/** Returns quick search results with a random substring
 
 @see https://vk.com/dev/search.getHints
 
 @param options parameters list
 @return VKRequest instance which incapsulates all required parameters for requesting
 user information. Delayed execution and request canceling also available.
 */
- (VKRequest *)searchGetHints:(NSDictionary *)options;

@end