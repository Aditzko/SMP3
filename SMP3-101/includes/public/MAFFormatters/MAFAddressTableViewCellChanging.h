//
//  MAFAddressTableViewCellChanging.h
//  MAFFormatters
//
//  Created by Egresits, David on 10/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MAFAddressTableViewCell;

@protocol MAFAddressTableViewCellChanging <NSObject>

- (void) cellValueChangedForCell:(MAFAddressTableViewCell*)changedCell;

@end


//@interface MAFAddressTableViewCellChanging : NSObject {
//
//}
//@end
