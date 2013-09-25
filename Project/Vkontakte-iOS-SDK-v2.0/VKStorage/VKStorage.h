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

/** Основной ключ используемый для хранения информации о токенах доступа содержащихся
в хранилище.
*/
/** Main key which is used for storing access tokens information in local storage
 */
static NSString *const kVKStorageUserDefaultsKey = @"Vkontakte-iOS-SDK-v2.0-Storage";

/** Основная директория для хранения файловых данных используемая в SDK (полный путь представляет
собой конкатенацию директории NSCachesDirectory и этой константы)
*/
/** Main directory which is used for storing file data used by SDK (full path is a concatenation
 of NSCachesDirectory and this constant)
 */
static NSString *const kVKStoragePath = @"/Vkontakte-iOS-SDK-v2.0-Storage/";

/** Основная директория для хранения кэша данных используемая в SDK (полный путь представляет
собой конкатенацию директории NSCachesDirectory и этой констаны)
*/
/** Main directory which is used for storing cache data used by SDK (full path is a concateration
 of NSCachesDirectory and this constant)
 */
static NSString *const kVKStorageCachePath = @"/Vkontakte-iOS-SDK-v2.0-Storage/Cache/";


@class VKStorageItem;
@class VKAccessToken;

/** Класс представляет собой хранилище для пользовательских токенов доступа и
закэшированных данных.
Основным хранимым элементом является элемент типа VKStorageItem, который содержит
пользовательский токен доступа и связанную с ним директорию для кэша.
*/
/** Interface provides access to local storage for user access tokens and cached data. The main stored
 element is the VKStorageItem instance, which contains access token and the associated cache directory
 */
@interface VKStorage : NSObject

/**
@name Properties
*/
/** Is local storage empty
*/
@property (nonatomic, readonly) BOOL isEmpty;

/** Number of elements currently saved in storage
*/
@property (nonatomic, readonly) NSUInteger count;

/** Full path to the main storage folder
 */
@property (nonatomic, readonly) NSString *fullStoragePath;

/** Full path to the main storage cache folder
*/
@property (nonatomic, readonly) NSString *fullCacheStoragePath;

/**
@name Instance initialization
*/
/** Shared storage

@return VKStorage instance
*/
+ (instancetype)sharedStorage;

/**
 @name Create storage elements
 */
/** Create storage element

 @param token user access token for which storage item will be created
 @return VKStorageItem instance
*/
- (VKStorageItem *)createStorageItemForAccessToken:(VKAccessToken *)token;

/**
@name Manipulate with storage data
*/
/** Add a new element in the storage

@param item storage item
*/
- (void)addItem:(VKStorageItem *)item;

/** Remove an element from the storage

@param item storage element
*/
- (void)removeItem:(VKStorageItem *)item;

/** Remove all data from the storage
*/
- (void)clean;

/** Remove all data from the storage cache
*/
- (void)cleanCachedData;

/**
 @name Read storage data
*/
/** Retrieve an element from the storage by userID
 
 @param userID user identification
 @return instance of VKStorageItem or nil if there is no element in storage
 */
- (VKStorageItem *)storageItemForUserID:(NSUInteger)userID;

/** List of all elements in storage

 @return Array with all VKStorageItem elements in storage
*/
- (NSArray *)storageItems;

@end