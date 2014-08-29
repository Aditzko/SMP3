//
//  ODataSubscriptionXMLBuilder.h
//  Parser
//
//  According to OData for SAP specification v1.03
//
//  Created by Farkas, Zoltan on 05/26/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ODataCollection;
@class ODataEntry;

enum TEN_NOTIFICATION_FORMAT_OPTIONS {
	NOTIFICATION_FORMAT_OPTION_SHORT		= 0, //Short (base) notification without business object sent to subscriber
	NOTIFICATION_FORMAT_OPTION_COMPLETE		= 1  //Complete hierarchy of business object
};

@interface ODataSubscriptionInfo : NSObject {
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
@property (nonatomic, retain, getter=getCollection) const ODataCollection* collection;
@property (nonatomic, retain, getter=getEntry) const ODataEntry* entry;

/**
 * subscribe to a collection
 */
-(id) initWithCollection:(const ODataCollection* const)newCollection; 
/**
 * subscribe to a collection's entry
 */
-(id) initWithCollection:(const ODataCollection* const)newCollection andEntry:(const ODataEntry* const)newEntry;

@end


/**
 * Contains the xml representation of a subscription info, the http method to be used and the headers that should be added 
 * to the http request when subscribing.
 */
@interface ODataSubscriptionXML : NSObject {
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
ODataSubscriptionXML* buildSubscriptionXML(const ODataSubscriptionInfo* const info);