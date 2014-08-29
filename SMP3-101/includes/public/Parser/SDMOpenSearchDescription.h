//
//  SDMOpenSearchDescription.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 05/13/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 * @deprecated   
 * Open Search template URL
 */
__attribute((deprecated("Use SDMOpenSearchDescriptionURLTemplate instead")))
@interface SDMOpenSearchDescriptionURLTemplate : NSObject<NSCoding> {
}

@property (nonatomic, retain, readonly, getter=getUrlTemplate) NSString* urlTemplate;
@property (nonatomic, retain, readonly, getter=getUrlType) NSString* type;

-(id) initWithUrlTemplate:(NSString* const)newUrlTemplate andType:(NSString* const)newType;

#pragma mark -
#pragma mark Public API
/**
 * Creates an URL from the template URL assigning values to the parameters that appear in the template.
 * The parameters are passed as a dictionary, the key is the parameter name, the value is the value of the parameter.
 * The function URL encodes the parameter values. An exception is thrown if a mandatory parameter cannot be found in the dictionary.
 */
-(NSString*) createUrlWithParameters:(NSDictionary*)parameters;

@end



/**
 * @deprecated   
 * Open Search Description representation
 */
__attribute((deprecated("Use OpenSearchDescription instead")))
@interface SDMOpenSearchDescription : NSObject<NSCoding> {
	NSString*		m_ShortName;
	NSString*		m_Description;
	NSMutableArray*	m_UrlTemplates;
}

@property (nonatomic, retain, getter=getShortName, setter=setShortName:) NSString* shortName;
@property (nonatomic, retain, getter=getDescription, setter=setDescription:) NSString* description;
@property (nonatomic, retain, getter=getUrlTemplates, setter=setUrlTemplates:) NSMutableArray* urlTemplates;

-(id) init;

#pragma mark -
#pragma mark Private API for the OSD Parser
-(void) addUrlTemplate:(const SDMOpenSearchDescriptionURLTemplate* const)newTemplate;

@end