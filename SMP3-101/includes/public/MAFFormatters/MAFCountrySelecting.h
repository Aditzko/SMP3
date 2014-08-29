//
//  MAFCountrySelecting.h
//  MAFFormatters
//
//  Created by Egresits, David on 10/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MAFCountrySelecting <NSObject>

@required

- (void)countrySelected:(NSString*)countryCode;

@end


//@interface MAFCountrySelecting : NSObject {
//
//}
//@end
