//
//  NSStringConversionExtension.h
//  SAPODataLib
//
//  Created by Farkas, Zoltan on 03/19/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Supported int types during conversion from string
 */
enum TEN_INT_TARGET_TYPES {
	INT_TARGET_TYPE_UINT8		= 0,
	INT_TARGET_TYPE_INT8		= 1,
	INT_TARGET_TYPE_INT16		= 2,
	INT_TARGET_TYPE_INT32		= 3,
	INT_TARGET_TYPE_INT64		= 4,
};

@interface NSString (ConversionExtension)
/**
 * Converts the stored string to a specific int value. The function checks for invalid characters and range errors. 
 * <pre>
 * Sample usage:
 * Converting a string to unsigned 8 bit integer:
 * <code>
 * NSString* str = [[[NSString alloc] initWithString: @"123"] autorelease];
 * signed long long result = 0;
 * if ([str toIntWithTargetType: INT_TARGET_TYPE_UINT8 result:&result]) {
 *    //add error handling code here
 *    //...
 *    //@throw ...
 * }
 * //in case of no error, cast the result value to the desired int type
 * unsigned char byteValue = (unsigned char)result;
 * </code>
 * @return Returns the index of the first character on which the conversion failed (either because of invalid character or overflow), or 0, if the conversion was successful.
 * @param targetType Defines the integer type that is considered during conversion. For example if UINT8 is defined and the string holds the "-1" value then it causes the 
 * conversion to stop with an error, while if target type is INT16 the conversion succeeds and return -1 in the result parameter.
 * @param result Pointer to a 64 bit signed integer that receives the converted integer value. In case of a conversion error the pointed integer's value will be set to 0.
 * If the conversion succeeds, the value should be casted to the target type (see example code above).
 * </pre>
 */
-(int)toIntWithTargetType:(const enum TEN_INT_TARGET_TYPES)targetType result:(signed long long*)result;

/**
 *	Converts the stored string to float value. The function checks for invalid characters and range errors.
 * @return Returns YES if the conversion was successful and NO otherwise.
 * @param result Pointer to a float that receives the float value after conversion.
 * @remark NULL can be passed as a result parameter, so the string can be checked if it stores a valid float, but the float value itself is not required by the caller.
 * If the parameter is not NULL and the conversion fails, the method writes 0 into the memory pointed by the result parameter and returns NO.  
 */
-(BOOL)toFloat:(float*)result;

/**
 *	Converts the stored string to double value. The function checks for invalid characters and range errors.
 * @return Returns YES if the conversion was successful and NO otherwise.
 * @param result Pointer to a double that receives the double value after conversion.
 * @remark NULL can be passed as a result parameter, so the string can be checked if it stores a valid double, but the double value itself is not required by the caller.
 * If the parameter is not NULL and the conversion fails, the method writes 0 into the memory pointed by the result parameter and returns NO.  
 */
-(BOOL)toDouble:(double*)result;

/**
 * Converts the stored string to BOOL.
 * @return Returns YES if the conversion was successful and NO otherwise.
 * @param result Pointer to a BOOL that receives the BOOL value after conversion.
 * @remark NULL can be passed as a result parameter, so the string can be checked if it stores a valid boolean value, but the BOOL value itself is not required by the caller.
 * If the parameter is not NULL and the conversion fails, the method writes NO into the memory pointed by the result parameter and returns NO.
 * The string must contain either "true", "1", "false" or "0" for successful conversion.
 * The method is incase sensitive.
 */
-(BOOL)toBool:(BOOL*)result;

@end

@interface NSMutableString (ConversionExtensions)
/**
 * HTML escapes the current mutable string.
 */
-(void)htmlEscape;
@end