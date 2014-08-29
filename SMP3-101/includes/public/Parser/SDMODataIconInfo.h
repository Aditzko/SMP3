//
//  SDMODataIconInfo.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 04/26/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @deprecated 
 *	icon information
 */
__attribute((deprecated("Use ODataIconInfo instead")))
@interface SDMODataIconInfo : NSObject <NSCoding> {
}

@property (nonatomic, readonly, retain, getter=getIconUrl) NSString* iconUrl;	//gets the absolute url of the icon
@property (nonatomic, readonly, assign, getter=getWidth) size_t width;			//icon width in pixels, default: 48
@property (nonatomic, readonly, assign, getter=getHeight) size_t height;		//icon height in pixels, default: 48

-(id) initWithUrl:(NSString* const)newUrl;
-(id) initWithUrl:(NSString* const)newUrl andWidth:(const size_t)newWidth andHeight:(const size_t)newHeight;

@end
