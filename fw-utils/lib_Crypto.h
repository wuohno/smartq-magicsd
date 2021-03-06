/** \file
 *  \brief Definitions and declarations for external reference into CrytoMemory
 *  and Companion CryptoMemory Library.
 */
/*
*******************************************************************************
*                 |
*  File Name      | lib_Crypto.h
*------------------------------------------------------------------------------
*  Project        | CryptoMemory and Companion CryptoMemory
*------------------------------------------------------------------------------
*  Created        | October 02, 2006
*-----------------|-----------------------------------------------------------
*  Description    | This file contains all the definitions and function which
*                 | are used to reference to/from CryptoMemory and its
*                 | Companion library.
*-----------------|------------------------------------------------------------
*                 | Copyright (c) 2006 Atmel Corp.
*                 | All Rights Reserved.
*                 |
******************************************************************************
*/
#ifndef  LIB_CRYPTO_H
#define  LIB_CRYPTO_H

typedef unsigned char uchar;
typedef unsigned int uint;

/** \mainpage Crypto-Memory Library Documentation
 *
 * \section intro_sec Introduction
 *
 * The CryptoMemory family is a high performance secure memory devices
 * providing 1K to 256K bits of user memory with advanced security and
 * cryptographic features built in.  The memory is divided into 4, 8 or 16
 * user zones each of which may be individually set with different security
 * access rights or used together to provide space for one or multiple data
 * files.  A configuration zone contains registers to define the security
 * rights for each user zone and space for passwords and secret keys used by
 * the security logic of CryptoMemory.
 *
 * The CryptoRF family integrates a 13.56 MHz RFinterface into a CryptoMemory,
 * resulting in a Contactless Smart Card with advanced security and
 * cryptographic features.  This device is optimized as a contactless secure
 * memory, for multi-application RF smart card, and secure identification for
 * electronic data transfer, without the requirement of an interal
 * microprocessor.  The CryptoRF devices provide 1K to 64K bits of user memory.
 *
 * The CryptoCompanion Chip is designed as the mate to Atmel`s CryptoRF and
 * CryptoMemory chips.
 *
 * This Library supports the synchronous interface most useful in embedded
 * systems.  While similar to the Two Wire Interface, it is not 100% compatable.
 *
 * \section embedded_app Embedded Applications
 *
 * Through dynamic, symmetric-mutual authentication, data encryption, and
 * the use of encrypted checksums, CryptoMemory provides a secure place for
 * storage of sensitive information within an embedded system.
 *
 * A 2-wire serial interface running at 1.0 MHz is used for fast and efficient
 * communications with up to 15 devices that may be individually addressed.
 *
 * \section rf_app RF Applications
 *
 * For communications, the RF interface utilizes the ISO 14443-2 and -3 Type B
 * bit timing and signal modulation schemes, and the ISO 14443-3 Slot-MARKER 
 * Anticollision Protocol.  Data is exchanged half duplex at a 106-kbit/s rate,
 * with a two-byte CRC_B providing error detection capability.  The maximum
 * communication range between the reader antenna and contactless card is
 * approximately 10 cm when used with an RFID reader that transmits the maximum
 * ISO 14443-2 RF power level.
 *
 * \section detail_sec Details
 *
 * To enable the security features of CryptoMemory, the device must first be
 * personalized to set up  registers and load in the appropriate passwords
 * and keys.  This is accomplished though programming the configuration zone
 * of CryptoMemory using simple write and read commands.  To gain access to
 * the configuration zone, the secure code (write 7 password) must
 * be successfully presented.  After writing and verifying data in the
 * configuration zone, the security fuses must be blown to lock this
 * information in the device.
 *
 * \subsection subsection1 Configuration Memory
 *
 * The configuration memory consists of 2048 bits of EEPROM memory used for
 * storing passwords, keys, codes and defining security levels to be used for
 * each User Zone.  Access rights to the configuration memory are defined in
 * the control logic and may not be altered by the user.  These access rights
 * include the ability to program certain portions of the Configuration Zone
 * and then lock the data written through use of the Security Fuses.  The
 * configuration memory for each CryptoMemory device is identical with the
 * exception of the number of Access Registers and Password/Key Registers used.
 *
 * Unused registers become reserved space to ensure the other components of
 * the configuration memory remain at the same address location regardless of
 * the number of User Zones in a device.
 *
 * \subsection subsection2 Communication Security Modes
 *
 * Communication between the device and host operates in three basic modes.
 * Standard mode is the default mode for the device after power-up.
 * Authentication mode is activated by a successful authentication sequence.
 * Encryption mode is activated by a successful encryption activation following
 * a successful authentication.
 *
 * \subsection subsection3 Security Operations
 *
 * \subsubsection subsubsection1 Password Verification
 *
 * Passwords may be used to protect read and write access to the user zones.
 * Any one of 8 password sets may be assigned to any user zone through the
 * access registers.  Separate 24 bit read and write passwords are provided.
 * A read password will only allow data to be read from the protected zone,
 * a write password allows both read and write access.  When a password is
 * successfully presented using the verify password command it remains active
 * until another verify password command is issued or the device is reset.
 * Only one password may be active at a time.  When an incorrect password is
 * presented the password attempts counter (PAC) will decrement.  When the
 * PAC reaches a value of 0x00 the associated password is permanently disabled
 * and the protected user zone(s) cannot be accessed.
 *
 * \subsubsection subsubsection2 Authentication Protocol
 *
 * An authentication protocol may be used to protect access to the user zones.
 * Any one of 4 key sets may be assigned to any user zone through the access
 * registers.  Each key set consists of a secret seed, cryptogram and session
 * key.  When the authentication communication mode is successfully entered
 * with the verify authentication command the specific key set remains active
 * until another verify authentication command is issued or the device is
 * reset.  An unsuccessful verify authentication command will deactivate the
 * key set.  Only one key set may be active at a time.  When an incorrect
 * authentication attempt is made the authentication attempts counter (AAC)
 * will decrement.  When the AAC reaches a value of 0x00 the associated key set
 * is permanently disabled and the protected user zone(s) cannot be accessed.
 *
 * \subsubsection subsubsection3 Data Encryption
 *
 * The data exchanged between the CryptoMemory device and the host logic
 * during read, write and verify password commands may be encrypted to ensure
 * data confidentiality.  This may be accomplished at the option of the host
 * logic by executing the verify encryption command after a successful
 * authentication using the same key set.  Encryption may be required for any
 * data exchange to a specific user zone by the proper setting of the access
 * registers.  In this case the successful completion of verify authentication
 * and verify encryption commands is required before any data may be read
 * from or written to the protected user zone.  Data read from the
 * configuration zone is never encrypted.
 *
 * When the encryption communication mode is successfully entered with the
 * verify encryption command the specific key set remains active until another
 * verify authentication command is issued or the device is reset.  An
 * unsuccessful verify encryption command will deactivate the key set and
 * reset device security.  Only one key set may be active at a time.  When an
 * incorrect encryption attempt is made the authentication attempts counter
 * (AAC) will decrement.  When the AAC reaches a value of 0x00 the associated
 * key set is permanently disabled and the protected user zone(s) cannot be
 * accessed.  The process to activate encryption is very similar to that used
 * to verify authentication, a calculated session key replaces the secret
 * seed in the sequence.
 *
 * \subsubsection subsubsection4 Encrypted Checksum
 *
 * CryptoMemory implements a data validity check function in the form of an
 * encrypted checksum.  This checksum provides a bi-directional data integrity
 * check and data origin authentication capability in the form of a Message
 * Authentication Code (MAC): only the host/device that carried out a valid
 * authentication is capable of computing a valid MAC.  When writing data to
 * the CryptoMemory device in authentication or encryption communication modes
 * a valid checksum must be sent to the device immediately following the write
 * command for data to actually be written.  If the checksum sent is not
 * correct, data will not be written to the device and security will be reset
 * requiring a new verify authentication command to be issued to continue.
 * When reading data the use of a checksum is optional.  The read checksum
 * command will reset device security so it is recommended to only be used
 * after all data has been read from the device.
 *
 * \subsection subsection_default CryptoMemory Default Values
 *
 * \htmlonly
   <TABLE CELLSPACING=10 > <TBODY> <TR>
   <TD><B>Device</B></TD> <TD><B>ATR</B></TD>
   <TD><B>Fab Code</B></TD> <TD><B>Lot History Code</B></TD>
   <TD><B>Write 7 Password (Secure Code)</B></TD> </TR>
   <TR> <TD ALIGN=CENTER>AT88SC0104C</TD>
   <TD ALIGN=CENTER>3B B2 11 00 10 80 00 01</TD>
   <TD ALIGN=CENTER>10 10</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>DD 42 97</TD> </TR>
   <TR> <TD ALIGN=CENTER>AT88SC0204C</TD>
   <TD ALIGN=CENTER>3B B2 11 00 10 80 00 02</TD>
   <TD ALIGN=CENTER>20 20</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>E5 47 47</TD> </TR>
   <TR> <TD ALIGN=CENTER>AT88SC0404C</TD>
   <TD ALIGN=CENTER>3B B2 11 00 10 80 00 04</TD>
   <TD ALIGN=CENTER>40 40</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>60 57 34</TD> </TR>
   <TR><TD ALIGN=CENTER>AT88SC0808C</TD>
   <TD ALIGN=CENTER>3B B2 11 00 10 80 00 08</TD>
   <TD ALIGN=CENTER>80 60</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>22 E8 3F</TD> </TR>
   <TR><TD ALIGN=CENTER>AT88SC1616C</TD>
   <TD ALIGN=CENTER>3B B2 11 00 10 80 00 16</TD>
   <TD ALIGN=CENTER>16 80</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>20 0C E0</TD> </TR>
   <TR><TD ALIGN=CENTER>AT88SC3216C</TD>
   <TD ALIGN=CENTER>3B B3 11 00 00 00 00 32</TD>
   <TD ALIGN=CENTER>32 10</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>CB 28 50</TD> </TR>
   <TR><TD ALIGN=CENTER>AT88SC6416C</TD>
   <TD ALIGN=CENTER>3B B3 11 00 00 00 00 64</TD>
   <TD ALIGN=CENTER>64 40</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>F7 62 0B</TD> </TR>
   <TR><TD ALIGN=CENTER>AT88SC12816C</TD>
   <TD ALIGN=CENTER>3B B3 11 00 00 00 01 28</TD>
   <TD ALIGN=CENTER>28 60</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>22 EF 67</TD> </TR>
   <TR><TD ALIGN=CENTER>AT88SC25616C</TD>
   <TD ALIGN=CENTER>3B B3 11 00 00 00 02 56</TD>
   <TD ALIGN=CENTER>58 60</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>17 C3 3A</TD> </TR>
   <TR></TR> </TBODY> </TABLE> \endhtmlonly
 *
 * \subsection subsection_default1 CryptoRF Default Values
 *
 * \htmlonly
   <TABLE CELLSPACING=10 > <TBODY> <TR> 
   <TD><B>Device</B></TD> <TD><B>Density Code</B></TD>
   <TD><B>RBmax Code</B></TD> <TD><B>Lot History Code</B></TD>
   <TD><B>Write 7 Password (Secure Code)</B></TD> </TR>
   <TR> <TD ALIGN=CENTER>AT88SC0104CRF</TD>
   <TD ALIGN=CENTER>02</TD>
   <TD ALIGN=CENTER>10</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>10 14 7C</TD> </TR>
   <TR> <TD ALIGN=CENTER>AT88SC0204CRF</TD>
   <TD ALIGN=CENTER>12</TD>
   <TD ALIGN=CENTER>10</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>20 C2 8B</TD> </TR>
   <TR> <TD ALIGN=CENTER>AT88SC0404CRF</TD>
   <TD ALIGN=CENTER>22</TD>
   <TD ALIGN=CENTER>10</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>30 1D D2</TD> </TR>
   <TR><TD ALIGN=CENTER>AT88SC0808CRF</TD>
   <TD ALIGN=CENTER>33</TD>
   <TD ALIGN=CENTER>10</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>40 7F AB</TD> </TR>
   <TR><TD ALIGN=CENTER>AT88SC1616CRF</TD>
   <TD ALIGN=CENTER>44</TD>
   <TD ALIGN=CENTER>10</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>50 44 72</TD> </TR>
   <TR><TD ALIGN=CENTER>AT88SC3216CRF</TD>
   <TD ALIGN=CENTER>54</TD>
   <TD ALIGN=CENTER>30</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>60 78 AF</TD> </TR>
   <TR><TD ALIGN=CENTER>AT88SC6416CRF</TD>
   <TD ALIGN=CENTER>64</TD>
   <TD ALIGN=CENTER>30</TD> <TD ALIGN=CENTER>Variable, locked</TD>
   <TD ALIGN=CENTER>70 BA 2E</TD> </TR>
   <TR></TR> </TBODY> </TABLE> \endhtmlonly
 *
 * \section integrate-sec Integration Guide 
 *  The supplied CryptoMemory Library supports the APIs list
 *  below.  The following describes how to build a simple
 *  application using this library.
 *
 *  \subsection subsection5 Files To Include.
 *  Below are files must add to system software.\n
 *
 *  lib_Crypto.h:
 *
 *  In your top level source file (probably the one that
 *  interface to lib_CMC.a or lib_CM.a), you will need to include lib_Crypto.h.
 *  This header file contained all external refernce APIs,
 *  defines and enumerations which are used by library or
 *  application. This file must be retained as is and no
 *  modification should be made.\n
 *
 *  lib_CMC.a or lib_CM.a:
 *
 *  In your IDE or makefile, you need to add lib_CMC.a or lib_CM.a for
 *  linker to link this library into your system software. This
 *  library archived from all object files generated by GNU
 *  compiler for AVR processor.  If you use different
 *  processor other than AVR, you need request Atmel to
 *  generate a library to fit your environment and processor.
 *
 *  lib_Support.c
 *
 *  This file contains all APIs which library refers at compiler
 *  time and calls at run-time. Since this file is used as a
 *  reference file, you might change logic within these API but
 *  must retain all API names, input and output parameters as
 *  defined.  Below are definitions, tables and routines which
 *  defined and implemented by Atmel. You can use them as
 *  implemented or modify to fit your system.  Below are
 *  sections in the lib_Support.c file which needed to examine
 *  to fit your system software environment.
 *
 *  \subsection subsection6 Definitions (lib_Support.c)
 *  Below are defintions must define to fit system enviroment.
 *
 *  CM_NUM_DEVICE\n
 *  This definition is defined how many CM devices are in system
 *  \if CMC_DOXY
 *  CMC_NUM_DEVICE\n
 *  This definition is defined how many CMC devices are in
 *  system
 *  \endif
 *  \subsection subsection7 Tables (lib_Support.c)
 *  Below are tables must define to fit system enviroment.\n
 *
 *  cm_device_addresses[]\n
 *  This table defined all CM device addresses in system with
 *  last entry must be "0". For CM, default address is 0x0B.
 *  Each device on the bus has a unique address programmed into
 *  its DCR register. CryptoMemory device always response to
 *  address "0x0B" no matter what address is programmed into the
 *  DCR. The CM device address is defined to program from bit
 *  0-3 only.
 *  \if CMC_DOXY
 *  cmc_device_addresses[]\n
 *  This table defined all CMC device addresses in system with
 *  last entry must be "0". The CMC device address is defined to
 *  program from bit 1-7.
 *  \endif
 *  sDeviceTypeInfoTBL[]\n
 *  This table defined all possible CM device types which are
 *  supported by Atmel.
 *
 *  \subsection subsection8 Routines (lib_Support.c)
 *  Below are routines that can be used as implemented or
 *  modified to meet system software needed.  These routines
 *  will call by library at run-time.\n
 *  
 *  cm_FindDeviceIndex(uchar ucCmDevAddr)\n
 *  This routine returns a CM index from CM device address table
 *  that based from CM device address.
 *
 *  getCMDevAddr(uchar ucIndex)\n
 *  This rotuine returns a CM device address from CM device
 *  address table that based from CM device index.
 *
 *  getCMDevType(uchar ucIndex)\n
 *  This routine returns a CM device type from CM device type
 *  table that based from CM device index.
 *
 *  cmc_FindDeviceIndex(uchar ucDevAddr)\n
 *  This routine returns a CMC index from CMC device address
 *  table that based from CMC device address.
 *
 *  getCMCDevAddr(uchar ucIndex)\n
 *  This rotuine returns a CMC device address from CMC device
 *  address table that based from CMC device index.
 *
 *  WaitForNotBusy(uchar ucDevAddr)\n
 *  This routine waits for the CMC "BUSY" bit to CLEAR.
 *
 *  WaitForData(uchar ucDevAddr)\n
 *  This routine waits for the CMC "DATA AVAILABLE" bit to SET.
 *
 *  WaitForStartupDone(uchar ucDevAddr)\n
 *  This routine waits for the CMC "STARTUPDONE" bit to SET.
 *
 *  lib_memcpy(puchar pucDesMem, puchar pucSrcMem, uint uiCnt)\n
 *  This routine calls standard C library to copy number of
 *  bytes from source to destination memory.
 *
 *  lib_memcmp(puchar pucMem1, puchar pucMem2, uint ucCnt)\n
 *  This routine calls standard C library to compare two
 *  strings.
 *
 *  lib_malloc(uchar ucBytes)\n
 *  This rouitne calls standard C library to allocate a buffer
 *  from memeory pool.
 *
 *  lib_free(puchar pucBuff)\n
 *  This rouitne calls standard C library to deallocate a buffer
 *  back to memeory pool.
 *
 *  lib_rand(void)\n
 *  This rouitne calls standard C library to get a random
 *  byte.\n
 *
 *  \subsection subsection9 APIs in library (lib_CMC.a or lib_CM.a)
 *  Below are APIs in library which avialable for other layers
 *  to call.\n
 *
 *  getLibVersNum(void)\n
 *  Get library version
 *
 *  cm_Init(void)\n
 *  Initializes Crypto devices.
 *
 *  cm_WriteUserZone(uchar ucDevAddr, uint uiCryptoAddr, puchar pucBuffer, uchar ucCount)\n
 *  Writes data into the (previously set) CM user zone
 *
 *  cm_ReadUserZone(uchar ucDevAddr, uint uiCryptoAddr, puchar pucBuffer, uchar ucCount)\n
 *  Reads data from the (previously set) CM user
 *  zone
 *
 *  cm_WriteConfigZone(uchar ucDevAddr, uchar ucCryptoAddr, puchar pucBuffer, uchar ucCount, uchar ucAntiTearing)\n
 *  Write data into the CM Configuration Memory
 *
 *  cm_WriteFuse(uchar ucDevAddr, uchar ucFuze)\n
 *  Writes Fuse Byte to the specified CM device address
 *
 *  cm_SetUserZone(uchar ucDevAddr, uchar ucZoneNumber, uchar ucAntiTearing)\n
 *  Sets CM user zone
 *
 *  cm_ReadConfigZone(uchar ucDevAddr, uchar ucCryptoAddr, puchar pucBuffer, uchar ucCount)\n
 *  Reads data from the CM Configuration Zone
 *
 *  cm_ReadFuse(uchar ucDevAddr, puchar pucFuze)\n
 *  Reads Fuse Byte from CM device
 *
 *  cm_ReadChecksum(uchar ucDevAddr, puchar pucChkSum)\n
 *  Reads Checksum
 *
 *  cm_SendChecksum(uchar ucDevAddr, puchar pucChkSum)\n
 *  Sends checksum
 *
 *  cm_VerifyCrypto(uchar ucDevAddr, uchar ucKeySet, puchar pucBuff, puchar pucBuff2, uchar ucEncrypt)\n
 *  Activates Authentication and (optionally) Encryption mode
 *
 *  cm_ResetCrypto(uchar ucDevAddr)\n
 *  Reset authentication and encryption and resets the
 *  cryptoengine
 *
 *  cm_VerifyPassword(uchar ucDevAddr, puchar pucPassword, uchar ucSet,  uchar ucRW)\n
 *  Verifies Password.
 *  \if CMC_DOXY
 *  cmc_VerifyFlash(uchar ucCmcDevAddr, puchar pucExtDigest, puchar pucIntDigest)\n
 *  Verifies System Digest
 *
 *  cmc_StartChallenge(uchar ucCmcDevAddr, puchar pucCmcChallenge, puchar pucCmcSeed, puchar pucSystemSeed)\n
 *  Verify Start Challenge
 *
 *  cmc_GetRandom(uchar ucCmcDevAddr, puchar pucData)\n
 *  Gets a 20 byte random number from the Companion Chip
 *
 *  cmc_IncrementCounter(uchar ucCmcDevAddr, uchar ucSelector)\n
 *  Increments the value of the specified counter by 1
 *
 *  cmc_ReadCounter(uchar ucCmcDevAddr, uchar ucSelector, puchar pucData)\n
 *  Reads 32 bits of the specified counter
 *
 *  cmc_WriteMemory(uchar ucCmcDevAddr, uint uiAddress, uchar ucCount, puchar pucData)\n
 *  Writes the contents of the specified address
 *
 *  cmc_WriteMemoryAuthorized(uchar ucCmcDevAddr, uint uiAddress, uchar ucData, puchar pucF0)\n
 *  Authorizes to writes a single byte in the first 16 bytes of
 *  the ReadOnly section at the specified address
 *
 *  cmc_WriteMemoryEncrypted(uchar ucCmcDevAddr, uint uiAddress,puchar pucData, puchar pucNonce)\n
 *  Writes 16 byte page of EEPROM with encryption.
 *
 *  cmc_ReadMemory(uchar ucCmcDevAddr, uint uiAddress, uchar ucCount, puchar pucData)\n
 *  Reads the contents of the specified address.
 *
 *  cmc_ReadMemoryDigest(uchar ucCmcDevAddr, uint uiAddress, puchar pucData)\n
 *  Reads the specified 32 byte block and computes the SHA-1
 *  digest.
 *
 *  cmc_ReadManufID(uchar ucCmcDevAddr, puchar pucData)\n
 *  Reads the contents of the Manufacturing ID and Lock Byte
 *
 *  cmc_Lock(uchar ucCmcDevAddr)\n
 *  Locks the current memory values into the Companion Chip.
 *
 *  cmc_Status(uchar ucCmcDevAddr)\n
 *  Reads Status byte from CMC
 *
 *  cmc_SHA1(puchar pucInData, uchar ucLen, puchar pucOutData)\n
 *  Calculates digest with SHA-1 algorithm\n
 *  \endif
 */


/*
****************************************************
*  Defintions for CryptoMemory and Companion
****************************************************
*/
// Basic Datatypes
typedef unsigned char   *puchar;
typedef signed char     schar;
typedef signed char     *pschar;
typedef unsigned short  *pushort;
typedef signed short    sushort;
typedef signed short    *pshort;
typedef unsigned int    *puint;
typedef signed int      sint;
typedef signed int      *psint;

#ifdef __AVR__
  #ifdef __GNUC__
    #include <avr/io.h>
    #include <avr/pgmspace.h>
    #define  ROM_READ(addr) pgm_read_word(addr)
///< Read of program space (flash) in AVR is different from RAM read
    #define  ROM_READ_BYTE(addr) pgm_read_byte(addr)
///< Read of program space (flash) in AVR is different from RAM read
    #define  ROM_READ_DWORD(addr) pgm_read_dword(addr)
///< Read of program space (flash) in AVR is different from RAM read
  #else
    #define ROM_READ(addr) *addr
///< Read of program space (flash) in AVR is different from RAM read
    #define ROM_READ_BYTE(addr) *addr
///< Read of program space (flash) in AVR is different from RAM read
    #define ROM_READ_DWORD(addr) *addr
///< Read of program space (flash) in AVR is different from RAM read
    #define PROGMEM   ///< Needed in GCC to differentiate ROM from RAM
  #endif
#else
    #define ROM_READ(addr) *addr
///< Read of program space (flash) in AVR is different from RAM read
    #define ROM_READ_BYTE(addr) *addr
///< Read of program space (flash) in AVR is different from RAM read
    #define ROM_READ_DWORD(addr) *addr
///< Read of program space (flash) in AVR is different from RAM read
    #define PROGMEM  ///< Needed in GCC to differentiate ROM from RAM
#endif



// Basic Definations (if not available elsewhere)
#ifndef FALSE
#define FALSE (0)
#define TRUE  (!FALSE)
#endif
#ifndef NULL
#define NULL ((void *)0)
#endif

/** \brief Status Return Codes */
typedef enum {
   SUCCESS     = 0x00,            ///<  General OK, no error
#ifdef CMC
   CMC_RST_LOCKED  = 0x01,        ///<  CMC Reset Locked, disabled until power or reset cycle
   CMC_BAD_CMD     = 0x02,        ///<  CMC Command format or operand bad
   CMC_TIME_DELAY  = 0x03,        ///<  CMC Disabled for a time delay (Power or Security)
   CMC_AUTH_FAIL   = 0x04,        ///<  CMC Authentication required or failed
   CMC_PERM_LOCKED = 0x07,        ///<  CMC Permanently locked
   CMC_RESPONSE_FAILED = 0x0A,    ///<  CMC and System fail StartUp State
   CMC_BUSY = 0x0B,               ///<  CMC Busy 
   CMC_DATA_NOT_AVAIL = 0x0C,     ///<  CMC Data Not Available 
   CMC_STARTUP_NOT_DONE =0x0D,    ///<  CMC and Ssytem fail Challengence State
#endif
   FAILED = 0x14,                  ///<  General failure
   FAIL_CMDSTART = 0x15,           ///<  Command start failed
   FAIL_CMDSEND = 0x16,            ///<  Failed to send a command
   FAIL_WRDATA = 0x17,             ///<  Failed to write data
   FAIL_RDDATA = 0x18,             ///<  Failed to read data
   UNKNOWN_DEVICE = 0x19,          ///<  Invalid device number
   WRITE_CMD_ERROR = 0x1A,         ///<  Write Command Error
   READ_CMD_ERROR = 0x1B,          ///<  Read Command Error   
   PASSWORD_NOT_ACCEPTED = 0x1C,   ///< Write password not accepted
   INVALID_USER_ZONE = 0x1D,       ///< Wrong user zone
   INVALID_NUM_BYTES_2WRITE = 0x1E,///< Number of bytes to write too large
   INVALID_NUM_BYTES_2READ = 0x1F, ///< Number of bytes to read too large
   ERROR_MAX = 255                 ///< Maximum error

} RETURN_CODE;


/** \brief Below are defined of Crypto Memory device type */

typedef enum {
    UNKNOWN_DEVICE_TYPE,
    AT88SC0104C,                /// < 1 KBits User Zone
    AT88SC0204C,                /// < 2 KBits User Zone
    AT88SC0404C,                /// < 4 KBits User Zone
    AT88SC0808C,                /// < 8 KBits User Zone
    AT88SC1616C,                /// < 16 KBits User Zone
    AT88SC3216C,                /// < 32 KBits User Zone
    AT88SC6416C,                /// < 64 KBits User Zone
    AT88SC12816C,               /// < 128 KBits User Zone
    AT88SC25616C,               /// < 256 KBits User Zone
    AT88SCRF,                   /// < CM for RF
    MAX_CM_DEVICE_TYPE          /// < Maximum device type
} CM_DEVICE_TYPE;

/** \brief Maximum of CM device addresses
*/
#define CM_MAX_DEV_ADDR                 0x0F

#ifdef CMC
/** \if CMC_DOXY
 *  \brief Maximum of CMC device addresses
 *  \endif
*/
#define CMC_MAX_DEV_ADDR                0xFE
#endif

/*
****************************************************
*  CryptoMemory Function Prototypes
****************************************************
*/
/** \brief Initializes the CrytpoMemory
 *
 * Resets the crypto engines and parameters associated with them
 * for each device in the cm_device_addresses table.
 * This function should be called immediately after calling the low level
 * function ll_PowerOn().  If the return value is not SUCCESS, use of
 * the CryptoMemory device(s) may not continue.
 * If system runs with CryptoMemory Companion chip then this cm_Init will
 * initialize them in this init state.
 *
 * \return Returns SUCCESS if device_address is in cm_device_addresses,
 * UNKNOWN_DEVICE otherwise.
 *
 * \remarks Example: if (cm_Init() != SUCCESS) return 0; \n
 *  Initializes all devices in the cm_device_addresses table.
 */
extern RETURN_CODE cm_Init (void);

/** \brief Writes data into the (previously set) user zone
 *
 * This function is the main memory write function, and will automatically
 * include encryption or anti-tearing (if enabled).
 *
 *  \param ucDevAddr - Device address (a nibble) corresponding to the default
 *  value (0xb) or the device configuration register lower nibble.
 *  \param uiCryptoAddr - 2 byte address within the zone to write
 *  \param pucBuffer - pointer to the buffer with the write data
 *  \param ucCount - how many bytes to write
 *
 *  \return Returns the results of ll_SendCommand() and ll_SendData().
 *
 *  \remarks Example: ucReturn = cm_WriteUserZone(DEFAULT_ADDRESS, 0, ucData,
 *  16);\n
 *  Writes 16 bytes from ucData at address 0 to device at DEFAULT_ADDRESS.\n
 *  Return SUCCESS or the result of ll_SendCommand() or
 * ll_SendData().
 */
extern RETURN_CODE cm_WriteUserZone(uchar ucDevAddr, uint uiCryptoAddr, \
                                    puchar pucBuffer, uchar ucCount);

/** \brief Reads data from the (previously set) user zone
 *
 * This function is the main memory read function, and will automatically
 * include encryption (if enabled).
 *
 *  \param ucDevAddr - Device address (a nibble) corresponding to the default
 *  value (0xb) or the device configuration register lower nibble.
 *  \param uiCryptoAddr - 2 byte address within the zone to read
 *  \param pucBuffer - pointer to a buffer to receive data
 *  \param ucCount - the number of bytes to read
 *
 *  \return Returns the results of ll_SendCommand() and ll_ReceiveData().
 *
 *  \remarks Example: ucReturn = cm_ReadUserZone(DEFAULT_ADDRESS, 0, ucData, 16);\n
 *  Reads 16 bytes into ucData from address 0 in device at DEFAULT_ADDRESS.\n
 *  Return SUCCESS or the result of ll_SendCommand() or
 * ll_ReceiveData().
 */
extern RETURN_CODE cm_ReadUserZone(uchar ucDevAddr, uint uiCryptoAddr, \
                                   puchar pucBuffer, uchar ucCount);

/** \brief Write data into the Configuration Memory
 *
 *  The input parameters determine which device address to write, which
 *  starting address in the configuration memory to write to, how many
 *  bytes to write, where the data to write is, and whether to use
 *  the anti-tearing option.
 *
 *  \param ucDevAddr- Device Address (a nibble) corresponding to the
 *  default value (0xb) or the device configuration register lower
 *  nibble.
 *  \param ucCryptoAddr - Configuration Memory address - see the Configuration
 *  Memory map for the specific CryptoMemory Device to determine the address
 *  of the appropriate parameter.
 *  \param pucBuffer    - Pointer to buffer containing write data.
 *  \param ucCount      - the number of bytes to write
 *  \param ucAntiTearing - antitearing flag.  If TRUE, anti-tearing is
 *  enabled.  Anti-tearing should not be used unless required, as it
 *  causes more write cycles than necessary.
 *
 *  \return Return value of ll_SendCommand() or ll_SendData().
 *
 * \remarks
 * Example: \n
 * ucReturn = cm_WriteConfigZone(DEFAULT_ADDRESS, 0x0A, ucData, 2, FALSE);\n
 * Writes 2 bytes from ucData at CryptoMemory address 0x0A to the CryptoMemory 
 * device at DEFAULT_ADDRESS (0xb).
 * Anti-tearing is not enabled.  \n
 * Return SUCCESS or the result of ll_SendCommand() or
 * ll_SendData().
 *
 */
extern RETURN_CODE cm_WriteConfigZone(uchar ucDevAddr, uchar ucCryptoAddr, \
                                      puchar pucBuffer, uchar ucCount, \
                                      uchar ucAntiTearing);

/** \brief Writes Fuse Byte to the specified device address
 *
 *  Fuse values are (in bit order from 3 to 0):
 *  - SEC (blown by Atmel before shipment, locks Lot History Code)
 *  - FAB (locks Answer to Reset and Fab Code)
 *  - CMA (locks Card Manufacturer Code)
 *  - PER (locks the remaining portions of the System Zone)
 *
 *  \param ucDevAddr - Device Address (a nibble) corresponding to the
 *  default value (0xb) or the device configuration register lower
 *  nibble.
 *  \param ucFuze  - A byte holding the fuse data
 *  \return SUCCESS or ll_SendCommand() result.
 *
 *  \remarks Example:  ucReturn = WriteFuse(DEFAULT_ADDRESS, ucData);\n
 *  Writes fuse data in ucData to device at DEFAULT_ADDRESS.
 *  Return SUCCESS or the result of ll_SendCommand()
 */
extern RETURN_CODE cm_WriteFuse(uchar ucDevAddr, uchar ucFuze);

/** \brief System Write to set the user zone for following commands
 *
 *  When reading or writing the main EEPROM memory of the CryptoMemory device,
 *  the supplied address refers to an offset within a user zone (refer to
 *  the User Zone map for the specific CryptoMemory Device to determine the
 *  number of zones and zone size.) This function sets the user zone.
 *
 *  \param ucDevAddr - Device address (a nibble) corresponding to the default
 *  value (0xb) or the device configuration register lower nibble.
 *  \param ucZoneNumber - user zone number to set
 *  \param ucAntiTearing - antitearing flag. If TRUE, anti-tearing is enabled.
 *  Anti-tearing should not be used unless required, as it causes more write
 *  cycles than necessary.
 *
 *  \return Result of ll_SendCommand().
 *
 *  \remarks Example:  ucReturn = cm_SetUserZone(DEFAULT_ADDRESS, 3, FALSE);\n
 *  Sets the device at the default address (0xb) to user zone 3; anti-tearing
 *  is not enabled.
 *  Return SUCCESS or the result of ll_SendCommand()
 */
extern RETURN_CODE cm_SetUserZone(uchar ucDevAddr, uchar ucZoneNumber, \
                                  uchar ucAntiTearing);

/** \brief Read data from the Configuration Zone
 *
 *  The input parameters determine which device address to read, which
 *  starting address in the configuration zone to read from, how many
 *  bytes to read, and where to place the returned data.
 *
 *  \param ucDevAddr - Device Address (a nibble) corresponding to the
 *  default value (0xb) or the device configuration register lower
 *  nibble.
 *  \param ucCryptoAddr - Configuration Zone address - see the Configuration
 *  Zone map for the specific CryptoMemory Device to determine the address
 *  of the appropriate parameter.
 *  \param pucBuffer    - Pointer to buffer to contain returned data,
 *   which must be large enough to hold ucCount bytes.
 *  \param ucCount      - the number of bytes to read
 *  \return  SUCCESS or the result of ll_SendCommand() or ll_ReceiveData()
 *
 * \remarks
 * Example: ucReturn = cm_ReadConfigZone(DEFAULT_ADDRESS, 0x0A, ucData, 2);\n
 * Reads 2 bytes at address 0x0A from the DEFAULT_ADDRESS (0xb) into ucData.\n
 * Return SUCCESS or the result of ll_SendCommand() or
 * ll_ReceiveData().
 */
extern RETURN_CODE cm_ReadConfigZone(uchar ucDevAddr, uchar ucCryptoAddr, \
                                     puchar pucBuffer, uchar ucCount);

/** \brief Read Fuse Byte from the device specified by ucDevAddr
 *
 *  Fuse values are (in bit order from 3 to 0):
 *  - SEC (blown by Atmel before shipment, locks Lot History Code)
 *  - FAB (locks Answer to Reset and Fab Code)
 *  - CMA (locks Card Manufacturer Code)
 *  - PER (locks the remaining portions of the Configuration Zone)
 *
 *  \param ucDevAddr - Device Address (a nibble) corresponding to the
 *  default value (0xb) or the device configuration register lower
 *  nibble.
 *  \param pucFuze  - A pointer to a byte to hold the fuse data
 *  \return SUCCESS or ll_SendCommand() or ll_ReceiveData() result.
 *
 *  \remarks Example:  ucReturn = ReadFuse(DEFAULT_ADDRESS, ucData);\n
 *  Reads fuse data from device at DEFAULT_ADDRESS into
 *  ucData.
 *  Return SUCCESS or the result of ll_SendCommand() or
 * ll_ReceiveData().
 */
extern RETURN_CODE cm_ReadFuse(uchar ucDevAddr, puchar pucFuze);

/** \brief Read Checksum
 *
 * If the UCR bit in the Device Configuration Register is 1, the cryptographic
 * engine will be reset.  If UCR = 0, it will not be reset.\n
 * This function provides a method to check on the synchronicity of the host
 * and device cryptoengines without affecting the attempts counters.
 *
 *  \param ucDevAddr - Device Address (a nibble) corresponding to the
 *  default value (0xb) or the device configuration register lower
 *  nibble.
 *  \param pucChkSum - pointer to 2 bytes to store calculated CheckSum
 *  \return SUCCESS or the results of ll_SendCommand() or ll_ReceiveData().
 *
 *  \remarks Example: ucReturn = cm_ReadChecksum(DEFAULT_ADDRESS, ucData);\n
 *  Reads the checksum value into ucData for the device at
 *  DEFAULT_ADDRESS.
 *  Return SUCCESS or the result of ll_SendCommand() or or
 *  ll_ReceiveData().
 */
extern RETURN_CODE cm_ReadChecksum(uchar ucDevAddr, puchar pucChkSum);

/** \brief Send checksum.
 *
 *  If device is in authentication mode, any user zone write must be followed
 *  with a cm_SendChecksum command with the proper checksum.  Otherwise the
 *  device will not complete the write.  An invalid checksum will also clear
 *  authentication.
 *
 *  \param ucDevAddr - Device Address (a nibble) corresponding to the
 *  default value (0xb) or the device configuration register lower
 *  nibble.
 *  \param pucChkSum - pointer to 2 byte array holding checksum.
 *  Always pass NULL so that function will calculate the appropriate checksum.
 *
 *  \return Results of ll_SendCommand() or ll_SendData()
 *
 *  \remarks Example: ucReturn = cm_SendChecksum(DEFAULT_ADDRESS, NULL);\n
 *  Sends the correct checksum to the device at the DEFAULT_ADDRESS.
 *  Return SUCCESS or the result of ll_SendCommand() or or
 *  ll_SendData().
 */
extern RETURN_CODE cm_SendChecksum(uchar ucDevAddr, puchar pucChkSum);

/** \brief This routine activates Authentication and (optionally)
 *  Encryption modes.
 *
 * When called the function:
 * - reads the current cryptogram (C<SUB>i</SUB>) of the specified key set,
 * \if CMC_DOXY
 * - computes the next cryptogram (C<SUP>A</SUP>) based on the secret
 * KID pucKey (KID) and the random number (Q).
 * \else
 * - computes the next cryptogram (C<SUP>A</SUP>) based on the secret
 * seed pucKey (G) and the random number (Q).
 * \endif
 * - sends the (CH<SUP>A</SUP>) (crypto challenge) and the random number to the
 * CryptoMemory device,
 * - Reads the chip's newly calculated cryptogram (C<SUB>i</SUB><SUP>A</SUP>)
 * and compares it with C<SUP>A</SUP>.
 *
 * If C<SUP>A</SUP> matches C<SUB>i</SUB><SUP>A</SUP> then
 * authentication is successful AND:
 * - both host (function) and device save the new Cryptogram and
 *   calculate new Session Keys.
 *
 * In addition, if ucEncrypt is TRUE the function, using the new Session Key
 * and a new random number
 * - computes a new challenge (CH<SUP>E</SUP>), a new cryptogram
 *   (C<SUP>E</SUP>) and a new Session Key (S<SUP>E</SUP>),
 * - sends the challenge (CH<SUP>E</SUP>) and random number (Q) to the
 *   CryptoMemory device,
 * - reads the device's newly calculated cryptogram (C<SUB>i</SUB><SUP>E</SUP>)
 *   and compares it with C<SUP>E</SUP>.
 *
 * If the two match then encryption is activated.
 *
 * \param ucDevAddr - Device Address (a nibble) corresponding to the
 * default value (0xb) or the device configuration register lower
 * nibble.
 * \if CMC_DOXY
 * \param ucKeySet - index number of the current key set to be used for
 * authentication / encryption.  Upper nible is contained F index and lower
 * is contained G index.
 * \param pucBuff1 - pointer to 16 bytes Secret KID.
 * \param pucBuff2 - pointer to 8 bytes uniqui serial or
 *        identification number of CM.
 * \else
 * \param ucKeySet - index number of the current key set to be used for
 * authentication / encryption.  Upper nible is ignored and
 * lower is contained G index.
 * \param pucBuff1 - pointer to the Secret Seed (G) associated
 *        with this key set.
 * \param pucBuff2 - random number.  If NULL, the function will
 * calculate new random numbers for both actions.)
 * \endif
 * \param ucEncrypt - if TRUE command the device to enter encryption mode also
 * (with the same key set).
 *
 * \return SUCCESS or the results of ll_SendCommand(), ll_ReceiveData()
 * or ll_SendData() result.
 *
 * \remarks Example: \n
 * ucReturn = cm_VerifyCrypto(DEFAULT_ADDRESS, 1, ucData, NULL, TRUE);\n
 * Enter authentication mode with key set 1, secret seed in ucData,
 * calculate a random number for the user, and enter the encryption mode.\n
 * Return SUCCESS or the result of ll_SendCommand() or
 *  ll_SendData() or ll_ReceiveData().
 */
extern RETURN_CODE cm_VerifyCrypto(uchar ucDevAddr, uchar ucKeySet, \
                                   puchar pucBuff1, puchar pucBuff2, \
                                   uchar ucEncrypt);

/** \brief This routine reset active password 
 *
 * When called the function:
 * - sends the Verify Password Command with the second byte set to 0xFF.
 *
 *  \param ucDevAddr - Device Address (a nibble) corresponding to the
 *  default value (0xb) or the device configuration register lower
 *  nibble.
 *
 * \return SUCCESS or the results of ll_SendCommand() or ll_SendData().
 *
 * \remarks Example: \n
 * ucReturn = cm_ResetPassword(DEFAULT_ADDRESS);\n
 * Reset active password for device at address 
 * DEFAULT_ADDRESS.
 * Return SUCCESS or the result of ll_SendCommand() or or
 *  ll_SendData().
 */
extern RETURN_CODE cm_ResetPassword(uchar ucDevAddr);

/** \brief This routine reset authentication and encryption
 *   and resets the cryptoengine.
 *
 * When called the function:
 * - sends the Verify Crypto Command with no arguments and
 * - Resets the CryptoEngine in firmware.
 *
 *  \param ucDevAddr - Device Address (a nibble) corresponding to the
 *  default value (0xb) or the device configuration register lower
 *  nibble.
 *
 * \return SUCCESS or the results of ll_SendCommand() or ll_SendData().
 *
 * \remarks Example: \n
 * ucReturn = cm_ResetCrypto(DEFAULT_ADDRESS);\n
 * Leave authentication and encryption mode for device at address
 * DEFAULT_ADDRESS.
 * Return SUCCESS or the result of ll_SendCommand() or or
 *  ll_SendData().
 */
extern RETURN_CODE cm_ResetCrypto(uchar ucDevAddr);

/** \brief Verifies Password.
 *
 * Using the verify password command, send either the "write" or "read"
 * password to the appropriate address.  Then read the password location
 * in the config zone and see if the password attempts counter = 0xff
 * (passed).\n
 * If Authentication mode is active, then this function encrypts passwords
 * automatically.
 *
 *  \param ucDevAddr - Device Address (a nibble) corresponding to the
 *  default value (0xb) or the device configuration register lower
 *  nibble.
 * \if CMC_DOXY
 * \param pucPassword - pointer to password to verify and only valid if authentication
 *                      is not required.
 * \param ucSet - index number of the password set
 *                system with Companion devie: bit 0-3: CM password index
 *                                             bit 4-7: companion pwd index.
 * \else
 * \param pucPassword - pointer to password to verify.
 * \param ucSet - index number of the password set
 *                system without Companion device, bit 0-3: CM password index
 *                                                 bit 4-7 are ignore.
 *                system with Companion devie: bit 0-3: CM password index
 *                                             bit 4-7: companion pwd index.
 * \endif
 * \param ucRW  - whether it's the read or write password.  Read = 1, Write = 0.
 *
 * \return SUCCESS or the results of ll_SendCommand() or ll_SendData() or
 * ll_ReceiveData()
 *
 * \remarks
 * Example: ucReturn = cm_VerifyPassword(DEFAULT_ADDRESS, ucData, 7, 0);\n
 * Verify the write password number 7 at the DEFAULT_ADDRESS.\n
 * Return SUCCESS or the result of ll_SendCommand() or
 *  ll_SendData() or ll_ReceiveData(). 
 */ 
extern RETURN_CODE cm_VerifyPassword(uchar ucDevAddr, puchar pucPassword, \
                                     uchar ucSet, uchar ucRW);

#ifdef CMC
/*
****************************************************
*  CryptoMemory Companion (CMC) Function Prototypes
****************************************************
*/

/**\if CMC_DOXY
 *  \brief Verifies System Digest
 *
 * If Mode bit 0 = 0, simply verifies that *pucDigest matches FlashDigest.
 * If Mode bit 0 = 1, verifies that SHA-1(Digest, FlashDigest) = *pucSignature.
 *
 * \param ucCmcDevAddr - CMC device address
 * \param pucExtDigest - pointer to 20 bytes of external Digest
 * \param pucIntDigest - pointer to 20 bytes of internal EEPROM Flash Digest.
 *
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_VerifyFlash(uchar ucCmcDevAddr, puchar pucExtDigest, \
                                   puchar pucIntDigest);

/** \if CMC_DOXY
 *  \brief Start Challenge
 *
 *  This API will use to verify the mutually authenticate between system processor and
 *  compnaion device.  If either CMC or System secret seeds is not the same as in EEPROM,
 *  then CMC will return FAIL.  If both secret seeds are the same as in EEPROM, CMC will
 *  return SUCCESS.
 *
 * \param ucCmcDevAddr - CMC device address
 * \param pucCmcChallenge - pointer to 20 bytes of CMC Challenge
 * \param pucCmcSeed - pointer to 16 bytes of CMC secret seed. This CMC secret seed bytes
 *                      must be the same as CMCSeed in EEPROM
 * \param pucSystemSeed - pointer to 16 bytes of System secret seed. This System secret
 *                      seed bytes must be the same as SystemSeed in EEPROM.
 *
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_StartChallenge(uchar ucCmcDevAddr, puchar pucCmcChallenge, \
                                      puchar pucCmcSeed, puchar pucSystemSeed);

/** \if CMC_DOXY
 *  \brief Gets a 20 byte random number from the Companion Chip
 *
 * \param ucCmcDevAddr - CMC device address
 * \param pucData - pointer to returned 20 byte random number.
 *
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_GetRandom(uchar ucCmcDevAddr, puchar pucData) ;

/** \if CMC_DOXY
 *  \brief Increments the value of the specified counter by 1
 *
 * \param ucCmcDevAddr - CMC device address
 * \param ucSelector - Counter to increment (0 - 3).
 *
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_IncrementCounter(uchar ucCmcDevAddr, uchar ucSelector) ;

/** \if CMC_DOXY
 *  \brief Returns the least 32 bits of the specified counter.
 *
 * \param ucCmcDevAddr - CMC device address
 * \param ucSelector - Counter to read (0 - 3).
 * \param pucData - pointer to least significant 4 bytes of counter data.
 *
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_ReadCounter(uchar ucCmcDevAddr, uchar ucSelector, \
                                   puchar pucData) ;

/** \if CMC_DOXY
 *  \brief Writes the contents of the specified address.
 *
 * Writes up to the end of the read/write memory space.
 * After locking, only the read/write space can be written.
 * Up to 16 bytes may be written with a single operation
 *
 * \param ucCmcDevAddr - CMC device address
 * \param uiAddress - Address of first byte to write.  7 most sig. bits ignored.
 * \param ucCount - Write ucCount bytes to EEPROM (data
 *        follows).
 * \param pucData - pointer to clear text data to write.
 *
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_WriteMemory(uchar ucCmcDevAddr, uint uiAddress, \
                                   uchar ucCount, puchar pucData) ;

/** \if CMC_DOXY
 *  \brief Authorize to writes a single byte in the first 16
 *   bytes of the ReadOnly section at the specified address.
 *
 * Address must point to one of the first 16 bytes within the ReadOnly
 * section of memory. This command only works if Mode:Bit2 = 1.
 * Only one byte may be written with a each operation
 *
 * \param ucCmcDevAddr - CMC ddevice address
 * \param uiAddress - Address of byte to write.  7 most sig. bits ignored.
 * \param ucData    - clear text data to write.
 * \param pucF0     - pointer to buffer that contained 8 bytes
 *                      of F0
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_WriteMemoryAuthorized(uchar ucCmcDevAddr, uint uiAddress, \
                                             uchar ucData, puchar pucF0) ; 

/** \if CMC_DOXY
 *  \brief Writes 16 byte page of EEPROM with encryption.
 *
 * Writes 16 byte pages up to the end of the read/write memory space.
 * Uses the SHA-1 of (Address || EncKey || Nonce).
 * Smaller blocks than 16 bytes cannot be written with this command.
 * Cannot be executed after Companion Chip is locked.
 *
 * \param ucCmcDevAddr - CMC ddevice address
 * \param uiAddress - Address of the 16 byte page to write.  7 most significant
 *  and 4 least significant bits ignored.
 * \param pucData - pointer to 16 bytes of clear data to write.
 * \param pucNonce - Random value encryption seed.
 *
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_WriteMemoryEncrypted(uchar ucCmcDevAddr, uint uiAddress, \
                                            puchar pucData, puchar pucNonce) ;

/** \if CMC_DOXY
 *  \brief Read the contents of the specified address.
 *
 * Reads up to the end of the read/write memory space.
 * After locking, only the read only and the read/write space can be read.
 * Up to 16 bytes may be read with a single operation
 *
 * \param ucCmcDevAddr - CMC ddevice address
 * \param uiAddress - Address of first byte to read.  7 most sig. bits ignored.
 * \param ucCount - Read ucCount+1 bytes from EEPROM.
 * \param pucData - pointer to clear text data read from Companion Chip.
 *
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_ReadMemory(uchar ucCmcDevAddr, uint uiAddress, \
                                  uchar ucCount, puchar pucData) ;

/** \if CMC_DOXY
 *  \brief Read the specified 32 byte block and computes the
 *         SHA-1 digest.
 *
 * Provides a mechanism of verifying that the personalization of the chip
 * completed correctly before locked.
 * Note that verifying the digest of 0 requires knowing EncKey.
 * Cannot be executed after Companion Chip is locked.
 *
 * \param ucCmcDevAddr - CMC ddevice address
 * \param uiAddress - Address of the 32 byte page to read.  7 most significant
 *  and 5 least significant bits ignored.
 * \param pucData - pointer to 20 byte digest
 *
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_ReadMemoryDigest(uchar ucCmcDevAddr, uint uiAddress, \
                                        puchar pucData) ;

/** \if CMC_DOXY
 *  \brief Read the contents of the Manufacturing ID and Lock
 *         Byte.
 *
 * \param ucCmcDevAddr - CMC ddevice address
 *
 * \param pucData - pointer to 16 byte Manufacturing ID and Lock Byte.
 *
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_ReadManufID(uchar ucCmcDevAddr, puchar pucData) ;

/** \if CMC_DOXY
 *  \brief Lock the current memory values.
 *
 * \param ucCmcDevAddr - CMC ddevice address.
 *
 * \return SUCCESS or the result of cmc_Status()
 * \endif
 */
extern RETURN_CODE cmc_Lock(uchar ucCmcDevAddr) ;

/** \if CMC_DOXY
 *  \brief Returns the status byte from a CMC device.
 *
 * \param ucCmcDevAddr - CMC ddevice address
 *
 * \return uchar    - status from a CMC device
 * \endif
*/
extern uchar cmc_Status(uchar ucCmcDevAddr) ;

#endif   /* CMC */

/**
 *  \brief Send command bytes to a device.
 *
 *  This routine is external reference by library
 *
 *  \param pucInsBuf   - pointer to buffer of command bytes to
 *         send.
 *  \param ucLen        - number of command bytes to send.
 *
 *  \return SUCCESS or the result of cmc_Status()
 */
extern RETURN_CODE ll_SendCommand(puchar pucInsBuf, uchar ucLen);

/** \if CMC_DOXY
 *  \brief Receive data bytes from a CMC device.
 *
 *  This routine is external reference by library.
 *
 *  \param pucRecBuf            - pointer to buffer of receving data bytes
 *  \param ucLen                - number of data bytes to receive
 *
 *  \return SUCCESS or the result of cmc_Status()
 *  \endif
 */
#ifdef CMC
extern  RETURN_CODE ll_CmcReceiveData(puchar pucRecBuf, uchar ucLen);
#endif

/** \brief Receive data bytes from a CM device.
 *
 *  This routine is external reference by library.
 *
 *  \param pucRecBuf            - pointer to buffer of receving data bytes
 *  \param ucLen                - number of data bytes to receive
 *
 *  \return SUCCESS or the result of cmc_Status()
 */
extern	RETURN_CODE ll_ReceiveData(puchar pucRecBuf, uchar ucLen);

/** \brief Send data bytes to a device.
 *
 *  This routine is external reference by library.
 *
 *  \param pucSendBuf           - pointer to buffer of data bytes to send
 *  \param ucLen                - number of data bytes to send
 *
 *  \return SUCCESS or the result of cmc_Status()
 */
extern	RETURN_CODE ll_SendData(puchar pucSendBuf, uchar ucLen);

/**
 *  \brief Wait for number of clock ticks
 *  This routine is external reference by library.
 *
 *  \param ucLoop           - number of (Start + 15 clocks + Stop) to loop
 */
extern	void        ll_WaitClock(uchar ucLoop);

/**
 *  \brief Copy number of bytes from source to destination
 *         locations.
 *
 *  This routine is external reference by library.
 *
 *  \param pucDestMem       - destination buffer
 *  \param pucSrcMem        - source buffer
 *  \param uiCnt            - number of bytes to copy
 */
extern  void        lib_memcpy(puchar pucDestMem, puchar pucSrcMem, uint uiCnt);

/**
 *  \brief Compare two strings.
 *
 *  This routine is external reference by library.
 *
 *  \param pucMem1          - string 1  buffer
 *  \param pucMem2          - string 2  buffer
 *  \param uiCnt            - number of bytes to compare
 */
extern  uchar       lib_memcmp(puchar pucMem1, puchar pucMem2, uint uiCnt);

/**
 *  \brief Allocate memory from memory pool.
 *
 *  This routine is external reference by library.
 *
 *  \param ucBytes              - number of bytes to allocate
 *
 *  \return puchar              - pointer to allocated buffer
 *
 */
extern  puchar       lib_malloc(uchar ucBytes);

/** \brief Deallocate memory back to memory pool.
 *
 *  This routine is external reference by library.
 *
 *  \param pucBuff            - pointer to deallocated buffer
 */
extern  void        lib_free(puchar pucBuff);

/** \brief Get random byte.
 *
 *  This routine is external reference by library.
 *
 *  \return  uchar          - random byte
 */
extern  uchar       lib_rand(void);

/** \brief Get CM device address based from device index.
 *
 *  This routine is external reference by library.
 *
 *  \param ucIndex          - CM device index
 *
 *  \return  uchar          - CM device address
 */
extern  uchar       getCMDevAddr(uchar ucIndex);

/** \brief Get CM device index based from device address.
 *
 *  This routine is external reference by library.
 *
 *  \param  ucCmDevAddr           - CM device address
 *
 *  \return uchar               - CM device index
 */
extern  uchar       cm_FindDeviceIndex(uchar ucCmDevAddr);

/** \brief Get CM device type based from device index.
 *
 *  This routine is external reference by library.
 *
 *  \param  ucIndex           - CM device index
 *
 *  \return CM_DEVICE_TYPE    - CM device type
 */
extern  CM_DEVICE_TYPE       getCMDevType(uchar ucIndex);

/** \brief Get number CM device.
 *
 *  This routine is external reference by library.
 * 
 *  \return uchar             - number of CM devices
 */
extern  uchar       getNumCmDev(void);


/** \brief Get library version number.
 * 
 *  \return  puchar     - pointer to string of characters
 */
extern puchar getLibVersNum(void);

#ifdef CMC

/** \if CMC_DOXY
 *  \brief Wait for BUSY bit from CMC status to CLEAR.
 *
 *  This routine is external reference by library.
 *
 *  \param ucCmcDevAddr     - CMC device address
 *
 *  \return SUCCESS or the result of cmc_Status()
 *  \endif
 */
extern  uchar       WaitForNotBusy(uchar ucCmcDevAddr);

/** \if CMC_DOXY
 *  \brief Wait for DATA bit from CMC status to SET.
 *
 *  This routine is external reference by library.
 *
 *  \param ucCmcDevAddr     - CMC device address
 *
 *  \return SUCCESS or the result of cmc_Status()
 *  \endif
 */
extern  uchar       WaitForData(uchar ucCmcDevAddr);

/** \brief Wait for STARTUPDONE bit from CMC status to SET.
 *
 *  This routine is external reference by library.
 *
 *  \param ucCmcDevAddr     - CMC device address
 *
 *  \return SUCCESS or the result of cmc_Status()
 */
extern  uchar       WaitForStartupDone(uchar ucCmcDevAddr);

/** \if CMC_DOXY
 *  \brief Get CMC device index based from device address.
 *
 *  This routine is external reference by library.
 *
 *  \param  ucCmcDevAddr           - CMC device address
 *
 *  \return uchar               - CMC device index
 *  \endif
 */
extern  uchar       cmc_FindDeviceIndex(uchar ucCmcDevAddr);

/** \if CMC_DOXY
 *  \brief Get CMC device address based from device index.
 *
 *  This routine is external reference by library.
 *
 *  \param ucIndex          - CMC device index
 *
 *  \return  uchar          - CMC Cdevice address
 *  \endif
 */
extern  uchar       getCMCDevAddr(uchar ucIndex);


/** \if CMC_DOXY
 *  \brief Reset CMC device.
 *
 *  This routine is external reference by library.
 *  \endif
 */
extern  void       cmc_Reset(void);

/** \if CMC_DOXY
 *  \brief SHA-1 processing
 *  
 *  \param pucChallenge - First input to SHA-1 algorithm
 *  \param ucLen        - Length of pucChallenge
 *  \param pucResponse  - Output from SHA-1 algorithm
 *  \endif
 */
extern void        cmc_SHA1(puchar pucInData, uchar ucLen, puchar pucOutData);
#endif

#endif

