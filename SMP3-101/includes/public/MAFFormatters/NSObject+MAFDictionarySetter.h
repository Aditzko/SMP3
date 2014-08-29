//
//  NSObject+MAFDictionarySetter.h
//  MAFFormatters
//
//  Created by Palfi, Andras on 8/6/12.
//
//

#import <Foundation/Foundation.h>

/**
 Provides the method to set properties on a class using a dictionary.
 */
@interface NSObject (MAFDictionarySetter)

@property (nonatomic, retain) NSDictionary* mapping;

/**
 Sets the properties of the class to the values are in the dictionary.
 The keys in the dictionary specifies the name of the property. Works similar to the method setValuesForKeysWithDictionary, except that it won't throw an exception if there is a key in the dictionary which property doesn't exists on the class.
 @param parameters contain the keys to map to
 @param error in case of error, error object will be retrieved
 */
- (BOOL)setValuesFromDictionary:(NSDictionary*)parameters error:(NSError**)error;


@end
