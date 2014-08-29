//
//  SDMSubscriptionXMLBuilder.h
//  SDMParser
//
//  According to OData for SAP specification v1.03
//
//  Created by Farkas, Zoltan on 05/26/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SDMODataCollection;
@class SDMODataEntry;

enum TEN_NOTIFICATION_FORMAT_OPTIONS {
	NOTIFICATION_FORMAT_OPTION_SHORT		= 0, //Short (base) notification without business object sent to subscriber
	NOTIFICATION_FORMAT_OPTION_COMPLETE		= 1  //Complete hierarchy of business object
};


/**
 * @deprecated
 */
__attribute((deprecated("Use ODataSubscriptionInfo instead")))
@interface SDMSubscriptionInfo : NSObject {
	NSString*								m_ID;
	NSString*								m_Title;
	NSString*								m_DeliveryAddress;
	NSString*								m_Filter;
	enum TEN_NOTIFICATION_FORMAT_OPTIONS	m_SelectOption;
}

//read-write properties>>
@property (nonatomic, retain, getter=getID, setter=setID:) NSString* subscriptionID;
@property (nonatomic, retain, getter=getTitle, setter=setTitle:) NSString* title;
@property (nonatomic, retain, getter=getDeliveryAddress, setter=setDeliveryAddress:) NSString* deliveryAddress;
@property (nonatomic, retain, getter=getFilter, setter=setFilter:) NSString* filter;
@property (nonatomic, assign, getter=getSelectOption, setter=setSelectOption:) enum TEN_NOTIFICATION_FORMAT_OPTIONS selectOption;

//read only properties>>
@property (nonatomic, retain, getter=getCollection) const SDMODataCollection* collection;
@property (nonatomic, retain, getter=getEntry) const SDMODataEntry* entry;

/**
 * subscribe to a collection
 */
-(id) initWithCollection:(const SDMODataCollection* const)newCollection; 
/**
 * subscribe to a collection's entry
 */
-(id) initWithCollection:(const SDMODataCollection* const)newCollection andEntry:(const SDMODataEntry* const)newEntry;

@end


/**
 * Contains the xml representation of a subscription info, the http method to be used and the headers that should be added 
 * to the http request when subscribing.
 */
__attribute((deprecated("Use ODataSubscriptionXML instead")))
@interface SDMSubscriptionXML : NSObject {
	NSString*		m_Xml;
	NSString*		m_Method;
	NSDictionary*	m_Headers;
}

@property (nonatomic, retain, getter=getXml, setter=setXml:) NSString* xml;
@property (nonatomic, retain, getter=getMethod, setter=setMethod:) NSString* method;
@property (nonatomic, retain, getter=getHeaders, setter=setHeaders:) NSDictionary* headers;

-(id) init;

@end



/**
 * Creates the xml representation of a SubscriptionInfo instance
 */
SDMSubscriptionXML* sdmBuildSubscriptionXML(const SDMSubscriptionInfo* const info);