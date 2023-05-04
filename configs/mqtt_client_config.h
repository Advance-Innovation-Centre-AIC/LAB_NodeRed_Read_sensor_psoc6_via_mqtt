/******************************************************************************
* File Name:   mqtt_client_config.h
*
* Description: This file contains all the configuration macros used by the
*              MQTT client in this example.
*
* Related Document: See README.md
*
*
*******************************************************************************
* Copyright 2020-2023, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#ifndef MQTT_CLIENT_CONFIG_H_
#define MQTT_CLIENT_CONFIG_H_

#include "cy_mqtt_api.h"

/*******************************************************************************
* Macros
********************************************************************************/

/***************** MQTT CLIENT CONNECTION CONFIGURATION MACROS *****************/
/* MQTT Broker/Server address and port used for the MQTT connection. */
#define MQTT_BROKER_ADDRESS               "test.mosquitto.org"
#define MQTT_PORT                         8884

/* Set this macro to 1 if a secure (TLS) connection to the MQTT Broker is  
 * required to be established, else 0.
 */
#define MQTT_SECURE_CONNECTION            ( 1 )

/* Configure the user credentials to be sent as part of MQTT CONNECT packet */
#define MQTT_USERNAME                     ""
#define MQTT_PASSWORD                     ""


/********************* MQTT MESSAGE CONFIGURATION MACROS **********************/
/* The MQTT topics to be used by the publisher and subscriber. */
#define MQTT_PUB_TOPIC                    "PSoC6Status/temperature,pressure"
#define MQTT_SUB_TOPIC                    "PSoC6Status/led"

/* Set the QoS that is associated with the MQTT publish, and subscribe messages.
 * Valid choices are 0, 1, and 2. Other values should not be used in this macro.
 */
#define MQTT_MESSAGES_QOS                 ( 1 )

/* Configuration for the 'Last Will and Testament (LWT)'. It is an MQTT message 
 * that will be published by the MQTT broker if the MQTT connection is 
 * unexpectedly closed. This configuration is sent to the MQTT broker during 
 * MQTT connect operation and the MQTT broker will publish the Will message on 
 * the Will topic when it recognizes an unexpected disconnection from the client.
 * 
 * If you want to use the last will message, set this macro to 1 and configure
 * the topic and will message, else 0.
 */
#define ENABLE_LWT_MESSAGE                ( 0 )
#if ENABLE_LWT_MESSAGE
    #define MQTT_WILL_TOPIC_NAME          MQTT_PUB_TOPIC "/will"
    #define MQTT_WILL_MESSAGE             ("MQTT client unexpectedly disconnected!")
#endif

/* MQTT messages which are published on the MQTT_PUB_TOPIC that controls the
 * device (user LED in this example) state in this code example.
 */
#define MQTT_DEVICE_ON_MESSAGE            "TURN ON"
#define MQTT_DEVICE_OFF_MESSAGE           "TURN OFF"


/******************* OTHER MQTT CLIENT CONFIGURATION MACROS *******************/
/* A unique client identifier to be used for every MQTT connection. */
#define MQTT_CLIENT_IDENTIFIER            "psoc6-mqtt-client"

/* The timeout in milliseconds for MQTT operations in this example. */
#define MQTT_TIMEOUT_MS                   ( 5000 )

/* The keep-alive interval in seconds used for MQTT ping request. */
#define MQTT_KEEP_ALIVE_SECONDS           ( 60 )

/* Every active MQTT connection must have a unique client identifier. If you 
 * are using the above 'MQTT_CLIENT_IDENTIFIER' as client ID for multiple MQTT 
 * connections simultaneously, set this macro to 1. The device will then
 * generate a unique client identifier by appending a timestamp to the 
 * 'MQTT_CLIENT_IDENTIFIER' string. Example: 'psoc6-mqtt-client5927'
 */
#define GENERATE_UNIQUE_CLIENT_ID         ( 1 )

/* The longest client identifier that an MQTT server must accept (as defined
 * by the MQTT 3.1.1 spec) is 23 characters. However some MQTT brokers support 
 * longer client IDs. Configure this macro as per the MQTT broker specification. 
 */
#define MQTT_CLIENT_IDENTIFIER_MAX_LEN    ( 23 )

/* As per Internet Assigned Numbers Authority (IANA) the port numbers assigned 
 * for MQTT protocol are 1883 for non-secure connections and 8883 for secure
 * connections. In some cases there is a need to use other ports for MQTT like
 * port 443 (which is reserved for HTTPS). Application Layer Protocol 
 * Negotiation (ALPN) is an extension to TLS that allows many protocols to be 
 * used over a secure connection. The ALPN ProtocolNameList specifies the 
 * protocols that the client would like to use to communicate over TLS.
 * 
 * This macro specifies the ALPN Protocol Name to be used that is supported
 * by the MQTT broker in use.
 * Note: For AWS IoT, currently "x-amzn-mqtt-ca" is the only supported ALPN 
 *       ProtocolName and it is only supported on port 443.
 * 
 * Uncomment the below line and specify the ALPN Protocol Name to use this 
 * feature.
 */
// #define MQTT_ALPN_PROTOCOL_NAME           "x-amzn-mqtt-ca"

/* Server Name Indication (SNI) is extension to the Transport Layer Security 
 * (TLS) protocol. As required by some MQTT Brokers, SNI typically includes the 
 * hostname in the Client Hello message sent during TLS handshake.
 * 
 * Uncomment the below line and specify the SNI Host Name to use this extension
 * as specified by the MQTT Broker.
 */
//#define MQTT_SNI_HOSTNAME                 "SNI_HOST_NAME"
#define MQTT_SNI_HOSTNAME                 "test.mosquitto.org"
/* A Network buffer is allocated for sending and receiving MQTT packets over 
 * the network. Specify the size of this buffer using this macro.
 * 
 * Note: The minimum buffer size is defined by 'CY_MQTT_MIN_NETWORK_BUFFER_SIZE' 
 * macro in the MQTT library. Please ensure this macro value is larger than 
 * 'CY_MQTT_MIN_NETWORK_BUFFER_SIZE'.
 */
#define MQTT_NETWORK_BUFFER_SIZE          ( 2 * CY_MQTT_MIN_NETWORK_BUFFER_SIZE )

/* Maximum MQTT connection re-connection limit. */
#define MAX_MQTT_CONN_RETRIES            (150u)

/* MQTT re-connection time interval in milliseconds. */
#define MQTT_CONN_RETRY_INTERVAL_MS      (2000)


/**************** MQTT CLIENT CERTIFICATE CONFIGURATION MACROS ****************/

/* Configure the below credentials in case of a secure MQTT connection. */
/* PEM-encoded client certificate */
#define CLIENT_CERTIFICATE      \
"-----BEGIN CERTIFICATE-----\n"\
"MIID1DCCArygAwIBAgIBADANBgkqhkiG9w0BAQsFADCBkDELMAkGA1UEBhMCR0Ix\n"\
"FzAVBgNVBAgMDlVuaXRlZCBLaW5nZG9tMQ4wDAYDVQQHDAVEZXJieTESMBAGA1UE\n"\
"CgwJTW9zcXVpdHRvMQswCQYDVQQLDAJDQTEWMBQGA1UEAwwNbW9zcXVpdHRvLm9y\n"\
"ZzEfMB0GCSqGSIb3DQEJARYQcm9nZXJAYXRjaG9vLm9yZzAeFw0yMzAzMjkwOTE5\n"\
"MjVaFw0yMzA2MjcwOTE5MjVaMIGtMQswCQYDVQQGEwJ0aDEzMDEGA1UECAwqY2h1\n"\
"bmJ1cmkbW0QbW0QbW0QbW0QbW28bW0MbW0MbW0MbW0MbW0MbW0MbMREwDwYDVQQH\n"\
"DAhjaG9uYnVyaTEMMAoGA1UECgwDYmRoMQwwCgYDVQQLDANybmQxETAPBgNVBAMM\n"\
"CHNvb250cmVlMScwJQYJKoZIhvcNAQkBFhhzb29udHJlZS4xMS5lZUBnbWFpbC5j\n"\
"b20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDPhFYFElRkGJael3Uu\n"\
"pl5d8lrbewIjoOa9sap2MSqN3d9ewZZ/ZpX03ho/dXMWyKgXc5MoZE/DFMJob9nq\n"\
"lwqjp1koGaAIUyhqei5DOXWUrgimxOO7eGBTJQICXSlaqGNvDlNfc9Id9dSi5YUV\n"\
"NEVMsz5j/x9+xAuG+Jka8dz1UGRBYh66lbp1ISI04gh6Rmdile2eWdeQIsLkkmwT\n"\
"5gyWlnOw5bk0GccgnUGn5fGCZ5Y2jz20NoniMaNa252NraYJIRhiAKI/vVp25ORx\n"\
"fl6bfot5jpZ6SfP7KYyWQEI/eD3yh1lWtmH65CQiEwj+Fnbw5Z6ZL9YgvuLdApJW\n"\
"wTQTAgMBAAGjGjAYMAkGA1UdEwQCMAAwCwYDVR0PBAQDAgXgMA0GCSqGSIb3DQEB\n"\
"CwUAA4IBAQBsb8Z7yea6gPLlEFjVInUix+1Fi3C4bdPdCx02btN9nF9h2/54oZew\n"\
"qx2U8a/7ACRGwmIp+Ohmm1BrLnFRNbVsf5q24lvobFEdW2bkfTx3kI/liredwN0h\n"\
"fsJxfltV0NFoMxF30JbTr+NAaxq3NLgEyT+wG6GjIsTzRvrWu8lmj/Q6ADnkKGsL\n"\
"pSnuZmZcXYynOQLHpnCNBUvRcanu3Jj0ewGvQBWQx4rQGFoqRwWOTv6lJm+l7YeV\n"\
"rPO6DU8w7drpQ9zOGXkFr4ZObFJG0F4q4/W/UuwBdWwcEha+kaWfr91qwhW+bSDX\n"\
"sGz7KEMd1bUYb36nNKQRNX65tup215eY\n"\
"-----END CERTIFICATE-----"

/* PEM-encoded client private key */
#define CLIENT_PRIVATE_KEY          \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEpAIBAAKCAQEAz4RWBRJUZBiWnpd1LqZeXfJa23sCI6DmvbGqdjEqjd3fXsGW\n"\
"f2aV9N4aP3VzFsioF3OTKGRPwxTCaG/Z6pcKo6dZKBmgCFMoanouQzl1lK4IpsTj\n"\
"u3hgUyUCAl0pWqhjbw5TX3PSHfXUouWFFTRFTLM+Y/8ffsQLhviZGvHc9VBkQWIe\n"\
"upW6dSEiNOIIekZnYpXtnlnXkCLC5JJsE+YMlpZzsOW5NBnHIJ1Bp+XxgmeWNo89\n"\
"tDaJ4jGjWtudja2mCSEYYgCiP71aduTkcX5em36LeY6Weknz+ymMlkBCP3g98odZ\n"\
"VrZh+uQkIhMI/hZ28OWemS/WIL7i3QKSVsE0EwIDAQABAoIBAF9huVQNb8KuVpTA\n"\
"kvkFOTy/R6m4KWyM6WHphqtav++DOsdH/c/DLEvnxnLCnkqroi9dTRd0vACzywPL\n"\
"3YLpN9eu9NjsplUNO/ds/1Sg1X2oXIui1fX2R3gP+5NwlLB503JZSFMIXlytALZ6\n"\
"/qeXZf7yKEw4GJbgr1ezblQnNWN/YvwcILY+I0/Y1HOQ1QLa+c5QpF8KK3BrpQnU\n"\
"LmX0M61a73RQjG6lbATeenCiSQsL6YtEdtqzp7YV8FcO0drCFZmKMdIK6+eHWTDK\n"\
"wv4Mzhj4i8j3nksRN25mb0E46GHZ2gwBdR47XPtUB0oTDu1WOlhhiDW+j6cxjCkr\n"\
"bWwRLEECgYEA73IXv5ILjzLHSkIhJX55+mWB+z7TcsVsmG/Dv+IJeHHaxY+7Rq85\n"\
"TOIlcPu9Z18svpodLit9DSMkLmDxDjCH+2RmqKWeTA3ICU6dAtYYX/T3SmzTzQiv\n"\
"g4VmfS1mF+qJufQRSuc/uyGoG1iRuC82g5hNZql1sYq3hEgeHzFG7WECgYEA3d0k\n"\
"YGEFny/szi4c7cvb0cLeMk0uPknmNmApoUpBdXnohRRo2Gw7hCRsp2t8uEpDh/qO\n"\
"yNecmPAgNaDm1qLCP4pKjQCuIG4Mh142bV3E4zpPxQBcZFcEAwUMMVAexushy93u\n"\
"4wlINKgwjDCdRpKTowe5WV39DFMvu/lSkXTQgfMCgYB4FwvMG85KWphTKQmAyYcZ\n"\
"y3E+dksMg/GsHlnZ0d8YFlo3vZeaouUlJ0LKAKgEwVoqmhbKgissvJQ34ozjpfl9\n"\
"XuSR7saOtFbAPDpJIuGEttKT9DLh4VpNp0k4vN04X3wF1GAb5hEzpHSwimJDMwKv\n"\
"S2J+e704dy8FXDonQMqm4QKBgQCGwLNAao1ck2I0FGPztpbrv3zvdls47++IZT3D\n"\
"vfMmJAYrFitcD9jSOMFZqnpVAJ4lr/QbXoG5jlcx22l5Qd/Tce432ArqnYy0h29t\n"\
"W7+i957Nm5uCQiuond868FvRG60qQsC+WrvlZ6Yc78YGwC41nhJgiiqQ2tGqTRNu\n"\
"T1H5KwKBgQDsmDkJ2+if0FJAcMt1Pnvvhw/OqPQU4BxynkewY45AHmSZzpfQJgcf\n"\
"c+dCTChfrxGOAtjoGy+NeALBLoq8FbylzVUc0F+0k7xKYwCX1KZLVRoqeR9lA/Ox\n"\
"YE1PckFIUaM5M1nlMD5R+uddJhJzP+ZWvLSOSLaEhGlZbd4W8++JiQ==\n"\
"-----END RSA PRIVATE KEY-----"

/* PEM-encoded Root CA certificate */
#define ROOT_CA_CERTIFICATE     \
"-----BEGIN CERTIFICATE-----\n"\
"MIIEAzCCAuugAwIBAgIUBY1hlCGvdj4NhBXkZ/uLUZNILAwwDQYJKoZIhvcNAQEL\n"\
"BQAwgZAxCzAJBgNVBAYTAkdCMRcwFQYDVQQIDA5Vbml0ZWQgS2luZ2RvbTEOMAwG\n"\
"A1UEBwwFRGVyYnkxEjAQBgNVBAoMCU1vc3F1aXR0bzELMAkGA1UECwwCQ0ExFjAU\n"\
"BgNVBAMMDW1vc3F1aXR0by5vcmcxHzAdBgkqhkiG9w0BCQEWEHJvZ2VyQGF0Y2hv\n"\
"by5vcmcwHhcNMjAwNjA5MTEwNjM5WhcNMzAwNjA3MTEwNjM5WjCBkDELMAkGA1UE\n"\
"BhMCR0IxFzAVBgNVBAgMDlVuaXRlZCBLaW5nZG9tMQ4wDAYDVQQHDAVEZXJieTES\n"\
"MBAGA1UECgwJTW9zcXVpdHRvMQswCQYDVQQLDAJDQTEWMBQGA1UEAwwNbW9zcXVp\n"\
"dHRvLm9yZzEfMB0GCSqGSIb3DQEJARYQcm9nZXJAYXRjaG9vLm9yZzCCASIwDQYJ\n"\
"KoZIhvcNAQEBBQADggEPADCCAQoCggEBAME0HKmIzfTOwkKLT3THHe+ObdizamPg\n"\
"UZmD64Tf3zJdNeYGYn4CEXbyP6fy3tWc8S2boW6dzrH8SdFf9uo320GJA9B7U1FW\n"\
"Te3xda/Lm3JFfaHjkWw7jBwcauQZjpGINHapHRlpiCZsquAthOgxW9SgDgYlGzEA\n"\
"s06pkEFiMw+qDfLo/sxFKB6vQlFekMeCymjLCbNwPJyqyhFmPWwio/PDMruBTzPH\n"\
"3cioBnrJWKXc3OjXdLGFJOfj7pP0j/dr2LH72eSvv3PQQFl90CZPFhrCUcRHSSxo\n"\
"E6yjGOdnz7f6PveLIB574kQORwt8ePn0yidrTC1ictikED3nHYhMUOUCAwEAAaNT\n"\
"MFEwHQYDVR0OBBYEFPVV6xBUFPiGKDyo5V3+Hbh4N9YSMB8GA1UdIwQYMBaAFPVV\n"\
"6xBUFPiGKDyo5V3+Hbh4N9YSMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQEL\n"\
"BQADggEBAGa9kS21N70ThM6/Hj9D7mbVxKLBjVWe2TPsGfbl3rEDfZ+OKRZ2j6AC\n"\
"6r7jb4TZO3dzF2p6dgbrlU71Y/4K0TdzIjRj3cQ3KSm41JvUQ0hZ/c04iGDg/xWf\n"\
"+pp58nfPAYwuerruPNWmlStWAXf0UTqRtg4hQDWBuUFDJTuWuuBvEXudz74eh/wK\n"\
"sMwfu1HFvjy5Z0iMDU8PUDepjVolOCue9ashlS4EB5IECdSR2TItnAIiIwimx839\n"\
"LdUdRudafMu5T5Xma182OC0/u/xRlEm+tvKGGmfFcN0piqVl8OrSPBgIlb+1IKJE\n"\
"m/XriWr/Cq4h/JfB7NTsezVslgkBaoU=\n"\
"-----END CERTIFICATE-----"
/******************************************************************************
* Global Variables
*******************************************************************************/
extern cy_mqtt_broker_info_t broker_info;
extern cy_awsport_ssl_credentials_t  *security_info;
extern cy_mqtt_connect_info_t connection_info;


#endif /* MQTT_CLIENT_CONFIG_H_ */
