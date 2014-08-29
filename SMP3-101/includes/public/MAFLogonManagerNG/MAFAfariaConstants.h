//
//  MAFAfariaConstants.h
//
//  Copyright (c) 2013 SAP AG. All rights reserved.
//

/**
 Represents the registration type
 */
typedef NS_ENUM(NSUInteger, AfariaRegistrationType) {
    NoAfariaRegistration = 0, /**< Afaria doesn't provide information related to registration */
    ManualRegistration, /**< manual user registration, the user should provide the activation code and mobile user name provided by the admin */
    AutomaticRegistration, /**< automatic user registration, the user should provide the backedn username and password */
    CertificateRegistration /**< certificate mode registration. The certificate will be downloaded during the registration process */
};

typedef NS_ENUM(NSUInteger, AfariaSecureStoreCreationPolicy) {
    AfariaSecureStoreCreationPolicyIsAfariaPolicyEnabled = 0x01,
    AfariaSecureStoreCreationPolicyDefaultStateIsOn = 0x02,
    AfariaSecureStoreCreationPolicyChangeEnabled = 0x04,
};

/**
 Represents the state of the Afaria initialization
 */
typedef NS_ENUM(NSUInteger, AfariaState) {
    AfariaInitializationNotStarted = 0,         /**< Initialization not started yet */
    AfariaInitializationInProgress,             /**< Initialization in progresss. Waiting for the response of the Afaria client application */
    AfariaInitializationFailed,                 /**< Initialization failed. Afaria will be skipped */
    AfariaInitializationSuccessful,             /**< Afaria successfully initialized */
    AfariaInitializationCredentialNeeded       /**< Afaria credentials needed for getting configuration */
};


