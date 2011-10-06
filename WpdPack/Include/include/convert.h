/* $Revision: 1.4 $ */
/* Copyright $Date: 2009/01/19 17:13:16 $ */  

/******************************************************************************
 *
 * Copyright 2008-2009 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non-NetBurner Hardware.
 *   Please contact Licensing@Netburner.com for more information.
 *
 *   NetBurner makes no representation or warranties
 *   with respect to the performance of this computer program, and
 *   specifically disclaims any responsibility for any damages,
 *   special or consequential, connected with the use of this program.
 *
 *---------------------------------------------------------------------
 * NetBurner, Inc.
 * 5405 Morehouse Drive
 * San Diego, California 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is available: E-Mail support@netburner.com
 *
 *****************************************************************************/
#ifndef _CONVERT_H_
#define _CONVERT_H_
 
/*
 ******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************
 */
/* Minimum data buffer length in bytes */
#define CONVERT_BUFFER_LENGTH_MAX            ( ( 4 * 1024 ) - 1 )
 
/* Converted PEM data type */
#define CONVERT_NONE                         ( 0 ) 
#define CONVERT_RSA_PRIVATE_KEY              ( 1 )
#define CONVERT_DSA_PRIVATE_KEY              ( 2 )
#define CONVERT_CERTIFICATE                  ( 3 ) 

/* PEM data headers and footers */
#define CONVERT_CERTIFICATE_HEADER     "-----BEGIN CERTIFICATE-----"
#define CONVERT_RSA_PRIVATE_KEY_HEADER "-----BEGIN RSA PRIVATE KEY-----"
#define CONVERT_DSA_PRIVATE_KEY_HEADER "-----BEGIN DSA PRIVATE KEY-----"
#define CONVERT_CERTIFICATE_FOOTER     "-----END CERTIFICATE-----"
#define CONVERT_RSA_PRIVATE_KEY_FOOTER "-----END RSA PRIVATE KEY-----"
#define CONVERT_DSA_PRIVATE_KEY_FOOTER "-----END DSA PRIVATE KEY-----"

/*
 ******************************************************************************
 *
 * "C" Library Interface
 *
 ******************************************************************************
 */
#ifdef __cplusplus 
extern "C" {
#endif
/*
 ******************************************************************************
 
   Convert data from Privacy-enhanced Electronic Mail (PEM) format to binary.
   
   Parameters:
      dataPtr                 - Buffer for converted data
      pemEncodedData          - PEM encoded data
      dataSize                - Buffer size in bytes
      convertedDataLength     - Set to length of converted data
                                 
   Return:
      CONVERT_NONE            - Malformed data or calling parameters
      CONVERT_CERTIFICATE
      CONVERT_RSA_PRIVATE_KEY
      CONVERT_DSA_PRIVATE_KEY
      
   Notes:
      dataSize should be at least CONVERT_BUFFER_LENGTH_MAX and NULL 
            terminated.
      Limited to file formats used for RSA & DSA keys and X.509 certificates.
      
 ******************************************************************************
 */
int ConvertPEMFormattedData( PBYTE dataPtr, const char* pemEncodedData, 
      DWORD dataSize, PDWORD convertedDataLength );
 
/*
 ******************************************************************************
 
   Convert multibyte host format data to/from little endian
   
   Parameters:
      data                    - Multibyte data to convert
                                 
   Return:
      Data in little-endian format
      
   Notes:
      none
      
 ******************************************************************************
 */
WORD convertLittleEndianWord( WORD hData ); 
DWORD convertLittleEndianDword( DWORD hData );
 
#ifdef __cplusplus
};
#endif

#endif /* #ifdef _CONVERT_H_ */
