/* $Revision: 1.4 $ */
/* Copyright $Date: 2008/08/28 23:28:51 $ */  

/******************************************************************************
 *
 * Copyright 2007-2008 NetBurner, Inc.  ALL RIGHTS RESERVED
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
 * 5405 Morehouse Dr.
 * San Diego, Ca. 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is available: E-Mail support@netburner.com
 *
 *****************************************************************************/

#ifndef _NETBIOS_H_
#define _NETBIOS_H_

/*
 ******************************************************************************
 *
 * Reference 
 *    RFC 883 - Domain Names - Implementation and Specification, November 1983
 *
 *    RFC 1001 - Protocol standard for a NetBIOS service on a TCP/UDP 
 *       transport: Concepts and methods, March 1987
 *    RFC 1002 - Protocol standard for a NetBIOS service on a TCP/UDP 
 *       transport: Detailed specifications, March 1987
 *    IANA - WELL KNOWN PORT NUMBERS, July 10, 2008
 *
 *    Microsoft Help and Support - NetBIOS Suffixes (16th Character of NetBIOS 
 *       Name) Article ID: 163409, February 26, 2007 Revision: 4.2
 *
 *    Note: NetBIOS names are described as "compressed" which is a second level
 *       encoding described in RFC 883. All name comparisons are case 
 *       insensitive.
 *
 ******************************************************************************
 */
 
/*
 ******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************
 */
 
/*
 ******************************************************************************
 * Microsoft variant (comment to remove)
 ******************************************************************************
 */
#define NETBIOS_NAME_MICROSOFT_VARIANT       ( 1 )
 
/* NetBIOS Name size in upper case alphanumerics */
#ifdef NETBIOS_NAME_MICROSOFT_VARIANT
   #define NETBIOS_NAME_SIZE_IN_CHARS              ( 15 )
   #define NETBIOS_NAME_MICROSOFT_SUFFIX_IN_CHARS  ( 1 )
#else /* #ifdef NETBIOS_NAME_MICROSOFT_VARIANT */
   #define NETBIOS_NAME_SIZE_IN_CHARS              ( 16 )
#endif /* #ifdef NETBIOS_NAME_MICROSOFT_VARIANT */

/* NetBIOS name suffixes (Microsoft variant ) */
#define NETBIOS_NAME_SUFFIX_WORKSTATION      ( 0x00 )
 
/* Operation specifier */
#define NETBIOS_OPCODE_QUERY                 ( 0 )
#define NETBIOS_OPCODE_REGISTRATION          ( 5 )
#define NETBIOS_OPCODE_RELEASE               ( 6 )
#define NETBIOS_OPCODE_WACK                  ( 7 )
#define NETBIOS_OPCODE_REFRESH               ( 8 )

/* Owner node type */
#define NETBIOS_OWNER_NODE_TYPE_B_NODE       ( 0x0 )
#define NETBIOS_OWNER_NODE_TYPE_P_NODE       ( 0x1 )
#define NETBIOS_OWNER_NODE_TYPE_M_NODE       ( 0x2 )
#define NETBIOS_OWNER_NODE_TYPE_H_NODE       ( 0x3 )

/*
   Name first byte bit patterns
   
      NETBIOS_NAME_LABEL_NAME
      NETBIOS_NAME_LABEL_POINTER
      
 */
#define NETBIOS_NAME_LABEL_NAME              ( 0x20 )       
#define NETBIOS_NAME_LABEL_POINTER           ( 0xC0 )       

/* Compressed name length number of bytes */
#define NETBIOS_COMPRESSED_NAME_LENGTH       ( NETBIOS_NAME_SIZE_IN_CHARS * 2 )

/* 
   Entry Type 
   
      NETBIOS_REQUEST_TYPE_NB             - General name service resource record
      NETBIOS_REQUEST_TYPE_NBSTAT         - Node status resource record
      
 */
#define NETBIOS_REQUEST_TYPE_NB              ( 0x0020 )
#define NETBIOS_REQUEST_TYPE_NBSTAT          ( 0x0021 )
 
/* 
   Entry Class 
   
      NETBIOS_REQUEST_CLASS_IN            - Internet class
      
 */
#define NETBIOS_REQUEST_CLASS_IN            ( 0x0001 )

/* Infinite TTL */
#define NETBIOS_INFINITE_TTL                 ( 0 )
 
/* Node Status Response Statistics unit ID */
#define NETBIOS_UNIT_ID_IN_BYTES             ( 6 )

/*
 ******************************************************************************
 *
 * Enumerations
 *
 ******************************************************************************
 */
/*
 ******************************************************************************
 *
 * Structures
 *
 ******************************************************************************
 */
/*
      Packet type code (OPCODE)
         r                       - Response flag, 0 - request, 1 - response
         opcode                  - Operation specifier
         
      Operation flags (NM_FLAGS)
         aa                      - Authorative answer flag,
         tc                      - Truncation flag
         rd                      - Recursion desired flag
         ra                      - Recursion available flag
         b                       - Broadcast flag, 0 - Unicast, 1 - Broadcast
         
      Result codes (RCODE)
         rcode                   - Result code         
                  
         
 */ 
typedef struct _OpCodeNmFlagsRCode
{
   WORD r:1;
   WORD opcode:4;
   WORD aa:1;
   WORD tc:1;
   WORD rd:1;
   WORD ra:1;
   WORD mbz:2;
   WORD b:1;
   WORD rcode:4;

}  __attribute__( ( packed) ) OpCodeNmFlagsRCode;

/*
      Name Service Packet Header
      
         name_trn_id             - Transaction id, unique for requestor
         opcode_nmflags_rcode    - Packet type code, operation flags, results
         qdcount                 - Question entry count
         ancount                 - Resource record count
         nscount                 - Authority record count
         arcount                 - Additional record count
         
*/       
typedef struct _NameServicePacketHeader 
{
   WORD name_trn_id;
   OpCodeNmFlagsRCode opcode_nmflags_rcode;
   WORD qdcount;
   WORD ancount;
   WORD nscount;
   WORD arcount;

}  __attribute__( ( packed) ) NameServicePacketHeader;

/*
      Name Service Name
      
         labelLength             - Label length
         name                    - Compressed name
         zero_termination        - Zero termination
         
*/       
typedef struct _NameServiceName
{
   BYTE label_length_count;
   BYTE name[ NETBIOS_COMPRESSED_NAME_LENGTH ];
#ifdef NETBIOS_NAME_MICROSOFT_VARIANT
   BYTE suffix[ ( NETBIOS_NAME_MICROSOFT_SUFFIX_IN_CHARS * 2  ) ];
#endif /* #ifdef NETBIOS_NAME_MICROSOFT_VARIANT */
   BYTE zero_termination;

}  __attribute__( ( packed) ) NameServiceName;

/*
      Name Service Question Entry
      
         name                    - Name
         question_type           - Request type (rr_type for answer)
         question_class          - Class of request (rr_class for answer)
         
*/       
typedef struct _NameServiceQuestionEntry
{
   NameServiceName name;
   WORD question_type;
   WORD question_class;

}  __attribute__( ( packed) ) NameServiceQuestionEntry;

/*
      Netbios flags
         g                       - Group name flag
                                    0 - Unique name, 1 - Group name
         ont                     - Owner node type

 */ 
typedef struct _NbFlags
{
   WORD g:1;
   WORD ont:2;
   WORD mbz:13;

}  __attribute__(( packed) ) NbFlags;

 
/* 
      Name Service Resource Record Header (Name Pointer) 
      
         rr_type                 - Request type
         rr_class                - Class of request
         
 */         
typedef struct _NameServiceResourceRecordNamePointerHeader
{
   BYTE rr_nameLabel;
   BYTE rr_nameIndex;
   WORD rr_type;
   WORD rr_class;

}  __attribute__( ( packed) ) NameServiceResourceRecordNamePointerHeader;

/*
      Name Service Resource Record Trailer
      
         rr_type                 - Request type
         rr_class                - Class of request
         ttl                     - Time to live for resource name
         rdlength                - Bytes in RDATA field
         nb_flags                - Flags (RDATA)
         nb_address              - Address
         
 */       
typedef struct _NameServiceResourceRecordTrailer 
{
   DWORD ttl;
   WORD rdlength;
   NbFlags nb_flags;
   DWORD nb_address;

}  __attribute__(( packed) ) NameServiceResourceRecordTrailer;


/*
      Node Entry Name Flags
         g                       - Group name flag
                                    0 - Unique name, 1 - Group name
         ont                     - Owner node type
         drg                     - Deregister flag
                                    0 - None, 1 - Name is delete process
         cnf                     - Conflict flag
                                    0 - None, 1 - Name in conflict
         act                     - Active name flag (must be one)
         prm                     - Permanent name flag
                                    1 - permanent node name, 0 - all others

 */ 
typedef struct _NameFlags
{
   WORD g:1;
   WORD ont:2;
   WORD drg:1;
   WORD cnf:1;
   WORD act:1;
   WORD prm:1;
   WORD mbz:9;

}  __attribute__(( packed) ) Name_Flags;

/*
      Node Name Entry
      
         name                    - ASCII name
         question_type           - Request type (rr_type for answer)
         question_class          - Class of request (rr_class for answer)
         
*/       
typedef struct _NodeNameEntry
{
   char name[ NETBIOS_NAME_SIZE_IN_CHARS ];
#ifdef NETBIOS_NAME_MICROSOFT_VARIANT
   char suffix;
#endif /* #ifdef NETBIOS_NAME_MICROSOFT_VARIANT */
   Name_Flags name_flags;

}  __attribute__( ( packed) ) NodeNameEntry;

/*
      Name Service Node Status Response Trailer
      
         ttl                     - Time to live for resource name
         rdlength                - Bytes in RDATA field
         num_names               - Number of names
         
 */       
typedef struct _NameServiceNodeStatusResponseTrailer 
{
   DWORD ttl;
   WORD rdlength;
   BYTE num_names;

}  __attribute__(( packed) ) NameServiceNodeStatusResponseTrailer;

/*
      Name Service Node Status Response Statistics
      
         unit_id                       - Unique unit id
         jumpers                       - jumpers
         test_result                   - Test results
         version_number                - Version
         period_of_statistics          - Period
         number_of_crc                 - CRCs
         number_alignment_errors       - Alignment errors
         number_of_collisions          - Collisions
         number_send_aborts            - Send aborts
         number_good_sends             - Good sends
         number_good_receives          - Good receives
         number_retransmits            - Re-transmits
         number_of_conditions          - Resource conditions
         number_free_command_blocks    - Number of free command blocks
         total_number_command_blocks   - Number of command blocks
         nax_total_command_blocks      - Maxmimum number of command blocks
         number_pending_sessions       - Pending sessions
         max_number_pending_sessions   - Maximum pending sessions
         max_total_pending_sessions    - Maximum total pending sessions
         session_data_packet_size      - Session packet size
         
 */       
typedef struct _NameServiceNodeStatusResponseStatistics 
{
   BYTE unit_id [ NETBIOS_UNIT_ID_IN_BYTES ];
   BYTE jumpers;
   BYTE test_result;
   WORD version_number;
   WORD number_of_crc;
   WORD period_of_statistics;
   WORD number_alignment_errors;
   WORD number_of_collisions;
   WORD number_send_aborts;
   DWORD number_good_sends;
   DWORD number_good_receives;
   WORD number_retransmits;
   WORD number_of_conditions;
   WORD number_free_command_blocks;
   WORD total_number_command_blocks;
   WORD nax_total_command_blocks;
   WORD number_pending_sessions;
   WORD max_number_pending_sessions;
   WORD max_total_pending_sessions;
   WORD session_data_packet_size;

}  __attribute__(( packed) ) NameServiceNodeStatusResponseStatistics;



/*
 ******************************************************************************
 *
 * NetBIOS callback declaration
 *
 ******************************************************************************
 */
typedef void ( UdpNetbiosNameServiceFunc )( PoolPtr poolPtr );
extern UdpNetbiosNameServiceFunc* UdpNetbiosNameServicePtr;

/*
 ******************************************************************************
 *
 * netbios "C" Library Interface
 *
 ******************************************************************************
 */
#ifdef __cplusplus 
extern "C" {
#endif

/*
 *****************************************************************************
 *
 * Runtime Library Routines
 *
 *****************************************************************************
 */
 
/*
 ******************************************************************************
 
   Convert string into NETBIOS name
   
   Parameters:
      netBIOSnamePtr          - Correctly formed name
      namePtr                 - Name to convert
      netBIOSnameSize         - NetBIOS name (netBIOSnamePtr) size in bytes
      
   Return:
      None
      
   Notes:
      Name can contain any alphanumeric character except spaces 
      and \ : / * ? ; | . and it will be truncated if greater than 15 
      characters. The resulting name is all uppercase all excepted characters
      will be set to '0'.
      
 ******************************************************************************
 */
void NetbiosConvertName( char* netBIOSnamePtr, const char* namePtr, 
      int netBIOSnameSize );

/*
 ******************************************************************************
 
   Get NETBIOS name in ASCII formatted IAW RFC 883
   
   Parameters:
      netBIOSnamePtr          - Correctly formed name
      netBIOSnameSize         - NetBIOS name size capacity in bytes
                                    should be at least 
                                    NETBIOS_NAME_SIZE_IN_CHARS + 1
      
   Return:
      Number of bytes in name
      
   Notes:
      Name can contain any alphanumeric character except spaces 
      and \ : / * ? ; | . and it will be truncated if greater than 15 
      characters. The resulting name is all uppercase all excepted characters
      will be set to '0'.
      
 ******************************************************************************
 */
int NetbiosGetNetbiosName( char* netBIOSnamePtr, int netBIOSnameSize );

/*
 ******************************************************************************
 
   Enable the NETBIOS name service
   
   Parameters:
      name                    - Name to register, NULL pointer disables service
      initialRegister         - Send registration packet upon enabling.
      
   Return:
      None
      
   Notes:
      Enable name service responding to name service queries.
      Name can contain any alphanumeric character except spaces 
      and \ : / * ? ; | . and it will be truncated if greater than 15 
      characters.
      
 ******************************************************************************
 */
void NetbiosEnableNameService( const char* name, BOOL initialRegister );

 
#ifdef __cplusplus
};
#endif
#endif
