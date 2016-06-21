//
//  OrderedDictionary.h
//
//  Version 1.2
//
//  Created by Nick Lockwood on 21/09/2010.
//  Copyright 2010 Charcoal Design
//
//  Distributed under the permissive zlib license
//  Get the latest version from here:
//
//  https://github.com/nicklockwood/OrderedDictionary
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source distribution.
//

#import <Foundation/Foundation.h>

/**
 * Ordered subclass of NSDictionary.
 * Supports all the same methods as NSDictionary, plus a few
 * new methods for operating on entities by index rather than key.
 */
@interface OrderedDictionary : NSDictionary

+ (instancetype)dictionaryWithContentsOfFile:(NSString *)path;
+ (instancetype)dictionaryWithContentsOfURL:(NSURL *)url;

/** Returns the nth key in the dictionary. */
- (id)keyAtIndex:(NSUInteger)index;
/** Returns the nth object in the dictionary. */
- (id)objectAtIndex:(NSUInteger)index;
- (id)objectAtIndexedSubscript:(NSUInteger)index;
/** Returns the index of the specified key, or NSNotFound if key is not found. */
- (NSUInteger)indexOfKey:(id)key;
/** Returns an enumerator for backwards traversal of the dictionary keys. */
- (NSEnumerator *)reverseKeyEnumerator;
/** Returns an enumerator for backwards traversal of the dictionary objects. */
- (NSEnumerator *)reverseObjectEnumerator;
/** Enumerates keys ands objects with index using block. */
- (void)enumerateKeysAndObjectsWithIndexUsingBlock:(void (^)(id key, id obj, NSUInteger idx, BOOL *stop))block;

@end

/**
 * Mutable subclass of OrderedDictionary.
 * Supports all the same methods as NSMutableDictionary, plus a few
 * new methods for operating on entities by index rather than key.
 * Note that although it has the same interface, MutableOrderedDictionary
 * is not a subclass of NSMutableDictionary, and cannot be used as one
 * without generating compiler warnings (unless you cast it).
 */
@interface MutableOrderedDictionary : OrderedDictionary

+ (instancetype)dictionaryWithCapacity:(NSUInteger)count;
- (instancetype)initWithCapacity:(NSUInteger)count;

- (void)addEntriesFromDictionary:(NSDictionary *)otherDictionary;
- (void)removeAllObjects;
- (void)removeObjectForKey:(id)key;
- (void)removeObjectsForKeys:(NSArray *)keyArray;
- (void)setDictionary:(NSDictionary *)otherDictionary;
- (void)setObject:(id)object forKey:(id)key;
- (void)setObject:(id)object forKeyedSubscript:(id <NSCopying> )key;

/** Replace an object at a specific index in the dictionary. */
- (void)replaceObjectAtIndex:(NSUInteger)index withObject:(id)object;
- (void)setObject:(id)object atIndexedSubscript:(NSUInteger)index;
/** Swap the indexes of two key/value pairs in the dictionary. */
- (void)exchangeObjectAtIndex:(NSUInteger)idx1 withObjectAtIndex:(NSUInteger)idx2;
/** Removes the nth object in the dictionary. */
- (void)removeObjectAtIndex:(NSUInteger)index;

#pragma mark -
#pragma mark - Nativ Additions

/**
 *  Nativ Additions
 *
 *  @discussion
 *
 *  Preservation-based advanced methods haven't been tested or updated. The following methods
 *  below are safe. Use the original implementation with caution.
 */

/**
 *  Inserts the Object at the Index Specified and Preserves it while
 *  other modifications are made to the table.
 *
 *  @param object The Object
 *  @param key    The Key
 *  @param index  The Index
 *
 *  @discussion If the index is out of bounds, it will be shifted down until a
 *              a valid insertable index is available.
 */
- (void)insertObject:(id)object forKey:(id)key atIndex:(NSUInteger)index;

/**
 *  Inserts the Object at the Index Specified and Preserves it while
 *  other modifications are made to the table.
 *
 *  @param object The Object
 *  @param key    The Key
 *  @param index  The Preserved Index
 *
 *  @discussion Attempts to preserve an already preserved index will be ignored.
 */
- (void)insertObject:(id)object forKey:(id)key atPreservableIndex:(NSUInteger)index;

/**
 *  Adds the pair to next available slot, incrementing already preserved locations.
 *
 *  @param object The Object
 *  @param key    The Key
 */
- (void)addObject:(id)object forKey:(id)key;

/**
 *  Adds a list of paired objects to next available slot, incrementing already preserved locations.
 *
 *  @param object The Object
 *  @param key    The Key
 */
- (void)addObjects:(NSArray <id> *)objects withKeys:(NSArray <id> *)keys;

@end
