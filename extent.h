/*======================================================*/
/*======================================================*/
/*									                    */
/*	Name  :  extent.h						            */
/*	Task	:  M8051 data format define			        */
/*									                    */
/*======================================================*/
/*======================================================*/

#ifndef _EXTENT_H
#define _EXTENT_H

#ifndef KEIL_C51
#define KEIL_C51
//#ifndef TASKING_C51
//#define TASKING_C51
//#ifndef ANSI_C
//#define ANSI_C
#endif

/*======================================================*/

#if defined (KEIL_C51)              

typedef  bit             Bit;
typedef  bit             Bool;
typedef  unsigned char   uchar;
typedef  unsigned int    uint;
typedef  unsigned long	 ulong;
typedef  unsigned short  ushort;

/** replacing Address sfr definitions **/
//#define  SFRBIT(  name , add )    sbit  name = add
//#define  SFRBYTE( name , add )    sfr   name = add
/** replacing TASKINGs sfr definitions **/
#define  _sfrbit       sbit
#define  _sfrbyte      sfr

//#define READSFR( name )            (name)
//#define WRITESFR( name , value)     name = value

#define  DATA         data
#define  IDATA        idata
#define  PDATA        pdata
#define  XDATA        xdata
#define  RDATA        code

typedef struct 
{
	uchar bit0 : 1;
	uchar bit1 : 1;
	uchar bit2 : 1;
	uchar bit3 : 1;
	uchar bit4 : 1;
	uchar bit5 : 1;
	uchar bit6 : 1;
	uchar bit7 : 1;
}Register_8bits;



//#define  PLM( return_type, func )          extern alien return_type func
//#define  AT( address )                     _at_  address
//#define  USING( reg_bank, func )           func using reg_bank
//#define  INT_USING( int_level, reg_bank, func )   func interrupt int_level using reg_bank


//#define EXT8BITS( name, v1,v2,v3,v4,v5,v6,v7,v8) \
//           extern bdata unsigned char name;\//bdata表示位寻址
//           extern bit name##v1; extern bit name##v2;\
//           extern bit name##v3; extern bit name##v4;\
//           extern bit name##v5; extern bit name##v6;\
//           extern bit name##v7; extern bit name##v8

//#define DEF8BITS( name, v1,v2,v3,v4,v5,v6,v7,v8) \
//           bdata unsigned char name;\
//           sbit name##v1 = name^0; sbit name##v2 = name^1;\
//           sbit name##v3 = name^2; sbit name##v4 = name^3;\
//           sbit name##v5 = name^4; sbit name##v6 = name^5;\
//           sbit name##v7 = name^6; sbit name##v8 = name^7
//
//#define STAT8BITS( name, v1,v2,v3,v4,v5,v6,v7,v8) \
//           static bdata unsigned char name;\
//           static sbit name##v1 = name^0; static sbit name##v2 = name^1;\
//           static sbit name##v3 = name^2; static sbit name##v4 = name^3;\
//           static sbit name##v5 = name^4; static sbit name##v6 = name^5;\
//           static sbit name##v7 = name^6; static sbit name##v8 = name^7
//
//#define EXT16BITS( name, v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) \
//           extern bdata unsigned int name;\
//           extern bit name##v1; extern bit name##v2;\
//           extern bit name##v3; extern bit name##v4;\
//           extern bit name##v5; extern bit name##v6;\
//           extern bit name##v7; extern bit name##v8;\
//           extern bit name##v9;  extern bit name##v10;\
//           extern bit name##v11; extern bit name##v12;\
//           extern bit name##v13; extern bit name##v14;\
//           extern bit name##v15; extern bit name##v16
//#define DEF16BITS( name, v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) \
//           bdata unsigned int name;\
//           sbit name##v1 = name^0; sbit name##v2 = name^1;\
//           sbit name##v3 = name^2; sbit name##v4 = name^3;\
//           sbit name##v5 = name^4; sbit name##v6 = name^5;\
//           sbit name##v7 = name^6; sbit name##v8 = name^7;\
//           sbit name##v9 = name^8;   sbit name##v10 = name^9; \
//           sbit name##v11 = name^10; sbit name##v12 = name^11;\
//           sbit name##v13 = name^12; sbit name##v14 = name^13;\
//           sbit name##v15 = name^14; sbit name##v16 = name^15
//#define STAT16BITS( name, v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) \
//           static bdata unsigned int name;\
//           static sbit name##v1 = name^0; static sbit name##v2 = name^1;\
//           static sbit name##v3 = name^2; static sbit name##v4 = name^3;\
//           static sbit name##v5 = name^4; static sbit name##v6 = name^5;\
//           static sbit name##v7 = name^6; static sbit name##v8 = name^7;\
//           static sbit name##v9 = name^8;   static sbit name##v10 = name^9; \
//           static sbit name##v11 = name^10; static sbit name##v12 = name^11;\
//           static sbit name##v13 = name^12; static sbit name##v14 = name^13;\
//           static sbit name##v15 = name^14; static sbit name##v16 = name^15

//#define EXT2BITS( name, v1, v2 )\
//           extern  bit  name##v1;\
//           extern  bit  name##v2
//#define DEF2BITS( name, v1, v2 )\
//           bit  name##v1;\
//           bit  name##v2
//#define STAT2BITS( name, v1, v2 )\
//           static bit  name##v1;\
//           static bit  name##v2

//#define WRITE1_2(  nbit, the_bit, value )  nbit##the_bit = value
//#define WRITE1_8(  nbit, the_bit, value )  nbit##the_bit = value
//#define WRITE1_16( nbit, the_bit, value )  nbit##the_bit = value
//
//#define READ1_2(   nbit, the_bit )         nbit##the_bit
//#define READ1_8(   nbit, the_bit )         nbit##the_bit
//#define READ1_16(  nbit, the_bit )         nbit##the_bit
//
//#define WRITE8_8( nbit, val)     nbit = val
//#define WRITE16_16( nbit, val)   nbit = val
//#define READ8_8( nbit )       nbit
//#define READ16_16( nbit )     nbit
//
//#define WRITE2_2( nbit, bit0, bit1, val)  \
//                                           nbit##bit0 = ((val & 0x01) > 0);\
//                                           nbit##bit1 = ((val & 0x02) > 0)
//#define READ2_2( nbit, bit0, bit1 )  \
//        ((unsigned char) nbit##bit0 + (unsigned char) nbit##bit1 * 2)

/*########################################################################*/
/*########################################################################*/

#elif defined (TASKING_C51)           

typedef  bit             Bit;
typedef  bit             Bool;
typedef  unsigned char   Byte;
typedef  unsigned int    Word;

/** replacing PHANCI sfr definitions **/
#define  SFRBIT(  name , add )    _sfrbit   name = (add)
#define  SFRBYTE( name , add )    _sfrbyte  name = (add)
/** replacing KEILs  sfr definitions **/
#define  sbit          _sfrbit
#define  sfr           _sfrbyte
        /** NOTE 'sfr16' is intentionally not provided, to flag errors **/

#define READSFR( name )            (name)
#define WRITESFR( name , value)     name = value

#define  DATA         data
#define  IDATA        idat
#define  PDATA        pdat
#define  XDATA        xdat
#define  RDATA        rom

#define  PLM( return_type, func )       plmprocedure return_type func
#define  AT( address )                  _at( address )
#define  USING( reg_bank, func )        using( reg_bank )  func
#define  INT_USING( int_level, reg_bank, func)    interrupt(int_level) using (reg_bank) func

/***************************************************************************
* Macros for external declarations of bit structures
***************************************************************************/

#define EXT2BITS( name, v0,v1 ) \
           typedef struct { \
              bit  v0,v1; \
           } name##_2bit_struct; \
           extern name##_2bit_struct name

#define EXT8BITS( name, v0,v1,v2,v3,v4,v5,v6,v7 ) \
           typedef union { \
              struct { bit v0,v1,v2,v3,v4,v5,v6,v7; } names; \
              struct { bit b0,b1,b2,b3,b4,b5,b6,b7; } nums; \
           } name##_8bit_struct; \
           extern name##_8bit_struct name

#define EXT16BITS( name, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15 ) \
           typedef union { \
              struct { bit v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15; } names; \
              struct { bit b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15; } nums; \
           } name##_16bit_struct; \
           extern name##_16bit_struct name

/***************************************************************************
* Macros for definitions of bit structures
* (Note: The declaration must have been seen for the definition to work !)
* Macros for external declarations of bit structures
***************************************************************************/

#define DEF2BITS( name, v0,v1 ) \
           name##_2bit_struct name

#define DEF8BITS( name, v0,v1,v2,v3,v4,v5,v6,v7 ) \
           name##_8bit_struct name

#define DEF16BITS( name, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15 ) \
           name##_16bit_struct name

/***************************************************************************
* Macros for static definitions of bit structures
***************************************************************************/

#define STAT2BITS( name, v0,v1 ) \
           static struct { \
              bit  v0,v1; \
           } name

#define STAT8BITS( name, v0,v1,v2,v3,v4,v5,v6,v7 ) \
           static union { \
              struct { bit v0,v1,v2,v3,v4,v5,v6,v7; } names; \
              struct { bit b0,b1,b2,b3,b4,b5,b6,b7; } nums; \
           } name

#define STAT16BITS( name, v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15 ) \
           static union { \
              struct { bit v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15; } names; \
              struct { bit b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15; } nums; \
           } name

/***************************************************************************
* Macros for reading single bits of bit structures
***************************************************************************/

#define READ1_2(  name, the_bit ) name##.the_bit
#define READ1_8(  name, the_bit ) name##.names.the_bit
#define READ1_16( name, the_bit ) name##.names.the_bit

/***************************************************************************
* Macros for reading bit structures
* (Note: These are very inefficient !)
***************************************************************************/

#define READ2_2( nbit, bit0, bit1 )  \
           ((unsigned char) nbit##.bit0 + (unsigned char) nbit##.bit1 * 2)

#define READ8_8( name ) (unsigned char)( (name##.nums.b0 ? 0x0001u : 0) | \
                                         (name##.nums.b1 ? 0x0002u : 0) | \
                                         (name##.nums.b2 ? 0x0004u : 0) | \
                                         (name##.nums.b3 ? 0x0008u : 0) | \
                                         (name##.nums.b4 ? 0x0010u : 0) | \
                                         (name##.nums.b5 ? 0x0020u : 0) | \
                                         (name##.nums.b6 ? 0x0040u : 0) | \
                                         (name##.nums.b7 ? 0x0080u : 0) )

#define READ16_16( name ) (unsigned short)( (name##.nums.b0  ? 0x0001u : 0) | \
                                            (name##.nums.b1  ? 0x0002u : 0) | \
                                            (name##.nums.b2  ? 0x0004u : 0) | \
                                            (name##.nums.b3  ? 0x0008u : 0) | \
                                            (name##.nums.b4  ? 0x0010u : 0) | \
                                            (name##.nums.b5  ? 0x0020u : 0) | \
                                            (name##.nums.b6  ? 0x0040u : 0) | \
                                            (name##.nums.b7  ? 0x0080u : 0) | \
                                            (name##.nums.b8  ? 0x0100u : 0) | \
                                            (name##.nums.b9  ? 0x0200u : 0) | \
                                            (name##.nums.b10 ? 0x0400u : 0) | \
                                            (name##.nums.b11 ? 0x0800u : 0) | \
                                            (name##.nums.b12 ? 0x1000u : 0) | \
                                            (name##.nums.b13 ? 0x2000u : 0) | \
                                            (name##.nums.b14 ? 0x4000u : 0) | \
                                            (name##.nums.b15 ? 0x8000u : 0) )

/***************************************************************************
* Macros for writing single bits of bit structures
***************************************************************************/

#define WRITE1_2(  name, the_bit, value ) ( name##.the_bit = value )
#define WRITE1_8(  name, the_bit, value ) ( name##.names.the_bit = value )
#define WRITE1_16( name, the_bit, value ) ( name##.names.the_bit = value )

/***************************************************************************
* Macros for writing entire bit structures
* (Note: These are very inefficient !)
***************************************************************************/

#define WRITE2_2( nbit, bit0, bit1, val) ( nbit##.##bit0 = ((val & 0x01) != 0), \
                                           nbit##.##bit1 = ((val & 0x02) != 0)  )

#define WRITE8_8( name, value ) ( name##.nums.b0 = ((value & 0x01u) != 0), \
                                  name##.nums.b1 = ((value & 0x02u) != 0), \
                                  name##.nums.b2 = ((value & 0x04u) != 0), \
                                  name##.nums.b3 = ((value & 0x08u) != 0), \
                                  name##.nums.b4 = ((value & 0x10u) != 0), \
                                  name##.nums.b5 = ((value & 0x20u) != 0), \
                                  name##.nums.b6 = ((value & 0x40u) != 0), \
                                  name##.nums.b7 = ((value & 0x80u) != 0)  )

#define WRITE16_16( name, value ) ( name##.nums.b0  = ((value & 0x0001u) != 0), \
                                    name##.nums.b1  = ((value & 0x0002u) != 0), \
                                    name##.nums.b2  = ((value & 0x0004u) != 0), \
                                    name##.nums.b3  = ((value & 0x0008u) != 0), \
                                    name##.nums.b4  = ((value & 0x0010u) != 0), \
                                    name##.nums.b5  = ((value & 0x0020u) != 0), \
                                    name##.nums.b6  = ((value & 0x0040u) != 0), \
                                    name##.nums.b7  = ((value & 0x0080u) != 0), \
                                    name##.nums.b8  = ((value & 0x0100u) != 0), \
                                    name##.nums.b9  = ((value & 0x0200u) != 0), \
                                    name##.nums.b10 = ((value & 0x0400u) != 0), \
                                    name##.nums.b11 = ((value & 0x0800u) != 0), \
                                    name##.nums.b12 = ((value & 0x1000u) != 0), \
                                    name##.nums.b13 = ((value & 0x2000u) != 0), \
                                    name##.nums.b14 = ((value & 0x4000u) != 0), \
                                    name##.nums.b15 = ((value & 0x8000u) != 0)  )

/*########################################################################*/
/*########################################################################*/

#elif defined(ANSI_C)

typedef  unsigned int    Bit;   /* to be used when speed or code efficiency is a  MUST   */
typedef  unsigned int    Bool;  /* to be used when speed or code efficiency is   USEFUL  */
typedef  unsigned char   Byte;
typedef  unsigned int    Word;

/***************************************************************************
* PHANCI  sfr solution
* USAGE : two possible style options :
*      1- the compilers own syntax  eg. sfr a = 0x90; for Keil
*         Note that the use of the above is generally discouraged.
*      2- The prefered PHANCI option    SFRBIT( a , 0x90 );
*         the 1st option avoids modification to old C51 codes &
*         converted PLM code.
*         The use of the second parameterised option is encouraged since
*         it is better suited to future enhancement like enabling H/W
*         simulation etc.
*         NOTE: when in ANSI_C, include processor.c in the link. This uses
*         SFR_DEFINE to "define" sfrs as unsigned global integers instead.
***************************************************************************/

#ifndef SFR_DEFINE
      /**** SFR declarations
       ****/
      #define SFRBIT(  name , add )  extern unsigned int name
      #define SFRBYTE( name , add )  extern unsigned int name
      /** replacing TASKINGs sfr definitions **/
      #define  _sfrbit               extern unsigned int
      #define  _sfrbyte              extern unsigned int
      /** replacing KEILs sfr definitions **/
      #define  sbit                  extern unsigned int
      #define  sfr                   extern unsigned int
      #define  sfr16                 extern unsigned int
#else
      /**** SFR definitions
       ****/
      #define SFRBIT(  name , add )         unsigned int name = 0
      #define SFRBYTE( name , add )         unsigned int name = 0
      /** replacing TASKINGs sfr definitions **/
      #define  _sfrbit                      unsigned int
      #define  _sfrbyte                     unsigned int
      /** replacing KEILs sfr definitions **/
      #define  sbit                         unsigned int
      #define  sfr                          unsigned int
      #define  sfr16                        unsigned int
#endif
#define READSFR( name )            (name)
#define WRITESFR( name , value)     name = value

/***************************************************************************
* USAGE  eg.  extern int MAIN z; 
*             z is an integer in main memory
***************************************************************************/

#define  DATA
#define  IDATA
#define  PDATA
#define  XDATA
#define  RDATA

/***************************************************************************
* USAGE  eg.   PLM( int, func_a (int x, char y) );
*              Allows declaration of plm functions
*
* NOTE: When in ANSI_C, link with a file (eg. stubs.c) instead of all non-C
*       source files (eg. .asm files) that require the PLM macro to declare
*       their functions. The stubs.c file must #define PLM_DEFINE and then
*       #include all the .h files containing the PLM macro; the action of
*       the PLM macro will be changed from declaring an external function to
*       defining a dummy function, hence preventing "undefined external"
*       errors during linking.
***************************************************************************/

#ifndef PLM_DEFINE
         /* Make the PLM macro declare an external function */
         #define  PLM( return_type, func ) extern return_type func
#else
         /* Make the PLM macro define a dummy "stub" function and tolerate a following semicolon */
         #define  PLM( return_type, func ) return_type func { return (return_type)0; } extern int swallowcolon
#endif

/***************************************************************************
* USAGE eg.  int IDATA * DATA z AT( 0x70 ); 
*            when ANSI_C it turns to   int * z; 
*            z is in main memory at address 0x70, and points to an idata
*            integer
***************************************************************************/

#define  AT( address )  

/***************************************************************************
* USAGE  eg.   extern USING( 2 , int func_a (int x, char y) );
*              func_a (int x, char y) uses register bank 2 and is
*              external to the module. Note keil doesn't allow external
*              functions having the using attribute
***************************************************************************/

#define  USING(  reg_bank, func )   func

/***************************************************************************
* USAGE  eg.   INT_USING( 3, 2, void int_func (void) ) 
*              int_func () is a level 3 interrupt routine which uses
*              register bank 2. Note keil doesn't allow external
*              functions having the using or the interrupt attributes
***************************************************************************/

#define  INT_USING( int_level, reg_bank, func )   func

/***************************************************************************
* The following allow efficient use of bit structures, using 8051 bit memory
* space. The size of bit structures provided for are 2,8,16 bits but other
* sizes could be added if required.
* NOTE : bit structures can not be used as passed parameters (actual/formal data)
* In the case of Keil only !!! these are overlayed with bytes allowing
* efficient access.
* The macros always follow the same format shown below :
*
* EXTnBITS   declare an external 'n' bit structure
* DEFnBITS   define an 'n' bit structure at current scope level
*            (module/function)
* STATnBITS  define a static 'n' bit structure at current scope level
*            (module/function) 
*
* Access to these structure (byte wide or bit wide) is only allowed via
* the following
*
* READ1_n    read 1 bit of the 'n' bit structure
* READn_n    read all bits (as n/8 bytes) of the 'n' bit structure
*
* WRITE1_n   write 1 bit of the 'n' bit structure
* WRITEn_n   write to all bits of the 'n' bit structure
*
* If 'n' is not a multiple of 8, the macro will require the name of each
* bit in the same order as when they were defined/declared
* READ2_2    read all bits of the 'n' bit structure and returns a byte or word
*
* USAGE  examples : 
********
*    DEF8BITS( PgHeader, Erase, NewsFlash, Subtitle, Suppres, Update,
*              IntSeq, Inhibit, MagSerial );
*    Here an 8 bit structure "PgHeader" is defined (as a byte) with bits
*    "Erase", "NewsFlash" etc. where Erase is located in the least
*    significant bit of "PgHeader" & "MagSerial" in the most sig. bit.  
*
*    MyBit  =  READ1_8( PgHeader, NewsFlash ); read the NewsFlash bit
*    WRITE1_8( PgHeader, NewsFlash, MyBit ); assign the NewsFlash bit with MyBit
*
*    MyByte = READ8_8( PgHeader ); Byte wide read of PgHeader
*    WRITE8_8( PgHeader, 0x80 ); set MagSerial & clear all other bits
********
*    DEF2BITS( PgHeader, Erase, NewsFlash );
*    Here a 2 bit structure "PgHeader" is defined with bits "Erase" and
*    "NewsFlash". where Erase is located in the least significant bit of
*    "PgHeader".
*
*    MyBit  =  READ1_2( PgHeader, NewsFlash );     read the NewsFlash bit
*    WRITE1_2( PgHeader, NewsFlash, 1 );         assign the NewsFlash bit
*    WRITE1_2( PgHeader, Erase,     0 );         assign the Erase     bit
*
*    MyByte = READ2_2( PgHeader, Erase, NewsFlash  ); MyByte will be set to 2
*    WRITE2_2( PgHeader, Erase, NewsFlash , 1 ); set Erase & clear NewsFlash
***************************************************************************/

#define EXT8BITS(name,v1,v2,v3,v4,v5,v6,v7,v8) \
           extern unsigned int name [8];\
           extern const unsigned int name##v1; extern const unsigned int name##v2;\
           extern const unsigned int name##v3; extern const unsigned int name##v4;\
           extern const unsigned int name##v5; extern const unsigned int name##v6;\
           extern const unsigned int name##v7; extern const unsigned int name##v8
#define DEF8BITS(name,v1,v2,v3,v4,v5,v6,v7,v8) \
           unsigned int name [8] = {0,0,0,0, 0,0,0,0} ; \
           const unsigned int name##v1 = 0; const unsigned int name##v2 = 1;\
           const unsigned int name##v3 = 2; const unsigned int name##v4 = 3;\
           const unsigned int name##v5 = 4; const unsigned int name##v6 = 5;\
           const unsigned int name##v7 = 6; const unsigned int name##v8 = 7
#define STAT8BITS(name,v1,v2,v3,v4,v5,v6,v7,v8) \
           static unsigned int name [8] = {0,0,0,0, 0,0,0,0} ; \
           static const unsigned int name##v1 = 0; static const unsigned int name##v2 = 1;\
           static const unsigned int name##v3 = 2; static const unsigned int name##v4 = 3;\
           static const unsigned int name##v5 = 4; static const unsigned int name##v6 = 5;\
           static const unsigned int name##v7 = 6; static const unsigned int name##v8 = 7


#define EXT16BITS( name, v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) \
           extern unsigned int name [16];\
           extern const unsigned int name##v1; extern const unsigned int name##v2;\
           extern const unsigned int name##v3; extern const unsigned int name##v4;\
           extern const unsigned int name##v5; extern const unsigned int name##v6;\
           extern const unsigned int name##v7; extern const unsigned int name##v8;\
           extern const unsigned int name##v9;  extern const unsigned int name##v10;\
           extern const unsigned int name##v11; extern const unsigned int name##v12;\
           extern const unsigned int name##v13; extern const unsigned int name##v14;\
           extern const unsigned int name##v15; extern const unsigned int name##v16
#define DEF16BITS( name, v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) \
           unsigned int name [16] = {0,0,0,0,   0,0,0,0,   0,0,0,0,   0,0,0,0} ; \
           const unsigned int name##v1 = 0;  const unsigned int name##v2 = 1;\
           const unsigned int name##v3 = 2;  const unsigned int name##v4 = 3;\
           const unsigned int name##v5 = 4;  const unsigned int name##v6 = 5;\
           const unsigned int name##v7 = 6;  const unsigned int name##v8 = 7;\
           const unsigned int name##v9 = 8;   const unsigned int name##v10 = 9;\
           const unsigned int name##v11 = 10;  const unsigned int name##v12 = 11;\
           const unsigned int name##v13 = 12;  const unsigned int name##v14 = 13;\
           const unsigned int name##v15 = 14;  const unsigned int name##v16 = 15
#define STAT16BITS( name, v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) \
           static unsigned int name [16] = {0,0,0,0,   0,0,0,0,   0,0,0,0,   0,0,0,0} ; \
           static const unsigned int name##v1 = 0;  static const unsigned int name##v2 = 1;\
           static const unsigned int name##v3 = 2;  static const unsigned int name##v4 = 3;\
           static const unsigned int name##v5 = 4;  static const unsigned int name##v6 = 5;\
           static const unsigned int name##v7 = 6;  static const unsigned int name##v8 = 7;\
           static const unsigned int name##v9 = 8;   static const unsigned int name##v10 = 9;\
           static const unsigned int name##v11 = 10;  static const unsigned int name##v12 = 11;\
           static const unsigned int name##v13 = 12;  static const unsigned int name##v14 = 13;\
           static const unsigned int name##v15 = 14;  static const unsigned int name##v16 = 15

#define EXT2BITS(name,v1,v2) \
           extern  unsigned int name [2];\
           extern  const unsigned int name##v1;\
           extern  const unsigned int name##v2
#define DEF2BITS( name,v1,v2) \
           unsigned int name [2] = {0, 0};\
           const unsigned int name##v1 = 0;\
           const unsigned int name##v2 = 1
#define STAT2BITS( name,v1,v2) \
           static unsigned int name [2] = {0,0};\
           static const unsigned int name##v1 = 0;\
           static const unsigned int name##v2 = 1

#define WRITE1_2(  name , the_bit, value )        name [name##the_bit] = value
#define WRITE1_8(  name , the_bit, value )        name [name##the_bit] = value
#define WRITE1_16( name , the_bit, value )        name [name##the_bit] = value

#define READ1_2(  name, the_bit )                 name [name##the_bit]
#define READ1_8(  name, the_bit )                 name [name##the_bit]
#define READ1_16( name, the_bit )                 name [name##the_bit]

#define WRITE8_8( name, val) \
           name [0] = ((val & 0x01) > 0); name [1] = ((val & 0x02) > 0);\
           name [2] = ((val & 0x04) > 0); name [3] = ((val & 0x08) > 0);\
           name [4] = ((val & 0x10) > 0); name [5] = ((val & 0x20) > 0);\
           name [6] = ((val & 0x40) > 0); name [7] = ((val & 0x80) > 0)
#define WRITE16_16( name, val) \
           name [0]  = ((val & 0x01) > 0);   name [1]  = ((val & 0x02) > 0);\
           name [2]  = ((val & 0x04) > 0);   name [3]  = ((val & 0x08) > 0);\
           name [4]  = ((val & 0x10) > 0);   name [5]  = ((val & 0x20) > 0);\
           name [6]  = ((val & 0x40) > 0);   name [7]  = ((val & 0x80) > 0);\
           name [8]  = ((val & 0x0100) > 0); name [9]  = ((val & 0x0200) > 0);\
           name [10] = ((val & 0x0400) > 0); name [11] = ((val & 0x0800) > 0);\
           name [12] = ((val & 0x1000) > 0); name [13] = ((val & 0x2000) > 0);\
           name [14] = ((val & 0x4000) > 0); name [15] = ((val & 0x8000) > 0)

#define READ8_8( name )  \
          (name [0]     + name [1] *2  + name [2] *4  + name [3] *8  +\
           name [4] *16 + name [5] *32 + name [6] *64 + name [7] *128 )
#define READ16_16( name )  \
          (name [0]      + name [1] *2    + name [2] *4      + name [3] *8  +\
           name [4] *16  + name [5] *32   + name [6] *64     + name [7] *128+\
           name [8] *256 + name [9] *512  + name [10] *1024  + name [11] *2048  +\
           name [12] *4096 + name [13] *8192 + name [14] *16384 + name [15] *32768 )


#define WRITE2_2( name, bit0, bit1, val )  \
           name [0] = ((val & 0x01) > 0); \
           name [1] = ((val & 0x02) > 0)
#define READ2_2( name, bit0, bit1 )  \
           ( name [name##bit0]  + name [name##bit1] *2 )


#endif    /* ANSI_C */

/*########################################################################*/
/*########################################################################*/

#define   FALSE   (Bool)0
#define   TRUE    (Bool)!FALSE

#endif   /* _EXTENT_H  */


