//
//  SDMODataEntryXMLBuilder.h
//  SDMParser
//
//  Created by Farkas, Zoltan on 04/29/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 * @deprecated 
 * Contains the XML representation of an entry
 * and the HTTP method that must be used when 
 * issuing a request with the above mentioned XML against the backend.
 */
__attribute((deprecated("Use ODataEntryBody instead")))
@interface SDMODataEntryXML : NSObject {
	NSString*	m_Xml;
	NSString*	m_Method;
}

@property (nonatomic, retain) NSString* xml;
@property (nonatomic, retain) NSString* method;

-(id)init;
@end


/**
 * @deprecated 
 * Contains the JSON representation of an entry
 * and the HTTP method that must be used when
 * issuing a request with the above mentioned JSON against the backend.
 */
__attribute((deprecated("Use ODataEntryBody instead")))
@interface SDMODataEntryJSON : NSObject {
	NSString*	m_Json;
	NSString*	m_Method;
}

@property (nonatomic, retain) NSString* json;
@property (nonatomic, retain) NSString* method;

-(id)init;
@end

typedef SDMODataEntryXML SDMODataFeedXML;

/**
 * Builder class that creates an XML representation of an entry
 * The builder considers if the entry is used for updating or creating data
 * in the backend.
 */
enum TEN_ENTRY_OPERATIONS {
	ENTRY_OPERATION_CREATE				= 0, ///< From OData4SAP v1.03: "As new entities are created using the POST method, and this method is not idempotent: entity types SHOULD have a key whose values are provided by the client."
	ENTRY_OPERATION_UPDATE_FULL			= 1,
	ENTRY_OPERATION_UPDATE_INCREMENTAL	= 2,
	ENTRY_OPERATION_ARCHIVE				= 3  ///< Used when an entry should be saved as an xml file and is not sent to the server. This causes the builder to add the links and icon url (if present) too to the xml.
};


@class SDMODataServiceDocument;
@class SDMODataEntry;

/**
 * @deprecated 
 * Returns the xml representation of an entry depending on the operation and the HTTP method that must be used when the xml is sent to the SAP server in an HTTP request
 * <pre>
 * Sample usage:
 * Creating an xml from an entry that can be sent to the server to create or update the data in the backend defined by the key values. 
 * The collection must have the sap:creatable or sap:updatable attribute set to true to succeed (depending on the operation).
 * <code>
 * SDMODataEntryXML* entryAsXmlAndHttpMethod = sdmBuildODataEntryXML(entry, ENTRY_OPERATION_UPDATE_FULL, serviceDocument, NO);
 * </code>
 * @return Returns the xml representation of an entry for the given operation and the HTTP method that must be used when sending the entry to a SAP server in an HTTP request.
 * @param entry The entry from which the function creates its xml representation (@see SDMODataEntry)
 * @param operation The operation that should be executed on the server side. Possible values are: <br />
 * <li>ENTRY_OPERATION_CREATE: the xml contains the data of a new entry that should be created in the backend
 * <li>ENTRY_OPERATION_UPDATE_FULL: the xml contains the data of an existing entry in the backend. All the updatable fields will be updated in the backend. 
 * If an updatable field does not appear in the xml, the value in the backend that is assigned to the missing field will be overwritten with its default value. The entry to 
 * be updated is identified by the key fields of the xml.
 * <li>ENTRY_OPERATION_UPDATE_INCREMENTAL: the xml contains the data of an existing entry in the backend. Only those properties are updated in the backend that are 
 * indicated in the xml and leaves anything untouched in the backend.
 * <li>ENTRY_OPERATION_ARCHIVE: Used when an entry should be saved as an xml file and is not sent to the server. This causes the builder to add the links and icon url (if present) too to the xml.
 * @param serviceDocument The service document instance. See @see SDMODataServiceDocument and its getBaseUrl method.
 * @param serializeInlinedEntries If the parameter value is YES, all inline entries and/or feeds will be serialized that belong to the entry being serialized.
 * @see http://www.odata.org/developers/protocols/operations#CreatingnewEntries for further details.
 * </pre>
 */
SDMODataEntryXML* sdmBuildODataEntryXML(const SDMODataEntry* const entry, const enum TEN_ENTRY_OPERATIONS operation, 
									    const SDMODataServiceDocument* const serviceDocument, 
										const BOOL serializeInlinedEntries);

/**
 * Returns the xml representation of a list of entries.
 */
SDMODataFeedXML* sdmBuildODataFeedXML(NSArray* const entries, const enum TEN_ENTRY_OPERATIONS operation, 
									  const SDMODataServiceDocument* const serviceDocument, 
									  const BOOL serializeInlinedEntries);
/**
 * @deprecated 
 * Returns the json representation of an entry depending on the operation and the HTTP method that must be used when the json is sent to the server
 * in an HTTP request.
 * @param entry The entry from which the function creates its json representation. (@see SDMODataEntry)
 * @param operation The operation that should be executed on the server side. Possible values are: <br />
 * <li>ENTRY_OPERATION_CREATE: the json contains the data of a new json that should be created in the backend.
 * <li>ENTRY_OPERATION_UPDATE_FULL: the json contains the data of an existing entry in the backend. All the updatable fields will be updated in the backend.
 * If an updatable field does not appear in the json, the value in the backend that is assigned to the missing field will be overwritten with its default value. The entry to be updated is identified by the key fields of the json.
 * <li>ENTRY_OPERATION_UPDATE_INCREMENTAL: the json contains the data of an existing entry in the backend. Only those properties are updated in the backend that are indicated in the json and leaves anything untouched in the backend.
 * <li>ENTRY_OPERATION_ARCHIVE: Used when an entry should be saved as an json file and is not sent to the server. This causes the builder to add the links (if present) too to the json.
 * @return Returns the json representation of an entry for the given operation and the HTTP method that must be used when sending the entry to a SAP server in an HTTP request.
 * @example Creating an json from an entry that can be sent to the server to create or update the data in the backend defined by the key values.
 * <code>
 *  SDMODataEntryJSON* entryAsJsonAndHttpMethod = sdmBuildODataEntryJSON(entry, ENTRY_OPERATION_UPDATE_FULL);
 *  NSString *jsonBody = entryAsJsonAndHttpMethod.json;
 * </code>
 */

SDMODataEntryJSON* sdmBuildODataEntryJSON(const SDMODataEntry* const entry, const enum TEN_ENTRY_OPERATIONS operation);
