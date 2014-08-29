//
//  MAFCurrencyCatalog.h
//  MAFFormatters
//
//  Created by Kiri, Gyula on 2012.04.24..
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MAFCurrencyCatalog : NSObject {
}

+(MAFCurrencyCatalog*) currencyCatalog;
-(void) addCurrency:(NSString*)ISO decimals:(NSNumber*)decimals;
-(int) decimalsByISO:(NSString*)ISO;

@end
