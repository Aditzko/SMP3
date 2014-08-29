//
//  MAFLogonDictionaryHelper.h
//
//  Helper class to provide typed access to dictinary.
//
//  Copyright (c) 2012 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class MAFLogonMutableArrayHelper;

/**
 Helper to handle typeless object as an typed object
 */
@interface MAFLogonDictionaryHelper : NSObject

/** 
 Public property which stores the values
**/
@property (retain) NSMutableDictionary* rawValue;


#pragma mark Lifecycle methods
/**
 Initializes the MAFLogonDictionaryHelper with the provided dictionary object
 @param aRawValue NSMutableDictionary instance
 @return initialized MAFLogonDictionaryHelper instance
**/
-(id) initWithRawValue:(NSMutableDictionary*)aRawValue;

#pragma mark Accessor methods

/**
 Stores provided value in the dictionary, which later can be accessed using the key parameter
 @param aValue Value as int
 @param aKey Key of the value
**/
-(void) setIntValue:(int)aValue forKey:(NSString*)aKey;

/**
 Returns the stored value for the given key parameter.
 @param aKey Key of the stored object
 @return stored object as int, nil if not exists
 **/
-(int) intValueForKey:(NSString*)aKey;

/**
 Stores provided value in the dictionary, which later can be accessed using the key parameter
 @param aValue Value as CGRect
 @param aKey Key of the value
 **/
-(void) setCGRectValue:(CGRect)aValue forKey:(NSString *)aKey;

/**
 Returns the stored value for the given key parameter.
 @param aKey Key of the stored object
 @return stored object as CGRect, nil if not exists
 **/
-(CGRect) CGRectValueForKey:(NSString *)aKey;

/**
 Stores provided value in the dictionary, which later can be accessed using the key parameter
 @param aValue Value as NSString
 @param aKey Key of the value
 **/
-(void) setStringValue:(NSString*)aValue forKey:(NSString*)aKey;

/**
 Returns the stored value for the given key parameter.
 @param aKey Key of the stored object
 @return stored object as NSString, nil if not exists
 **/
-(NSString*) stringValueForKey:(NSString*)aKey;

/**
 Stores provided value in the dictionary, which later can be accessed using the key parameter
 @param aValue Value as BOOL
 @param aKey Key of the value
 **/
-(void) setBoolValue:(BOOL)aValue forKey:(NSString*)aKey;

/**
 Returns the stored value for the given key parameter.
 @param aKey Key of the stored object
 @return stored object as BOOL, nil if not exists
 **/
-(BOOL) boolValueForKey:(NSString*)aKey;

/**
 Stores provided value in the dictionary, which later can be accessed using the key parameter
 @param aValue Value as NSMutableArray
 @param aKey Key of the value
 **/
-(void) setMutableArrayValue:(MAFLogonMutableArrayHelper*)aValue forKey:(NSString*)aKey;

/**
 Returns the stored value for the given key parameter.
 @param key Key of the stored object
 @param aClassForItems The class which handles the native items. Should be a MAFLogonDictionaryHelper subclass.
 @return stored object as NSMutableArray, nil if not exists
 **/
-(MAFLogonMutableArrayHelper*) mutableArrayValueForKey:(NSString*)key withClassForItems:(Class)aClassForItems;

/**
 Sets a typed object for the key.
 @param anObject Object that need to store
 @param aKey Key of the value
 */
- (void) setDictionaryHelperObject:(MAFLogonDictionaryHelper*)anObject forKey:(NSString*)aKey;

/**
 Returns a typed object for the key.
 @param aKey Key of the stored object
 @param aClass The specific class what the helper should contain.
 */
- (MAFLogonDictionaryHelper*)dictionaryHelperObjectForKey:(NSString*)aKey withClass:(Class)aClass;

/**
 Stores provided value in the dictionary, which later can be accessed using the key parameter
 @param aValue Value as NSMutableDictionary
 @param aKey Key of the value
 **/
-(void) setMutableDictionaryValue:(NSMutableDictionary*)aValue forKey:(NSString*)aKey;

/**
 Returns the stored value for the given key parameter.
 @param aKey Key of the stored object
 @return stored object as NSMutableDictionary, nil if not exists
 **/
-(NSMutableDictionary*) mutableDictionaryValueForKey:(NSString*)aKey;

/**
 Stores provided value in the dictionary, which later can be accessed using the key parameter
 @param aValue Value as NSError
 @param aKey Key of the value
 **/
-(void) setErrorValue:(NSError*)aValue forKey:(NSString*)aKey;

/**
 Returns the stored value for the given key parameter.
 @param aKey Key of the stored object
 @return stored object as NSError, nil if not exists
 **/
-(NSError*) errorValueForKey:(NSString*)aKey;

@end
