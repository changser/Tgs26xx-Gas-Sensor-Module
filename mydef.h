/*======================================================*/
/*======================================================*/
/*									                    */
/*	Name  :  mydef.h						            */
/*	Task	:  M8051 data format define/		        */
/*									                    */
/*======================================================*/
/*======================================================*/

#ifndef _MYDEF_H
#define _MYDEF_H

#ifndef KEIL_C51
#define KEIL_C51
//#ifndef RENESAS_RL78
//#define RENESAS_RL78
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



#define  DATA         data
#define  IDATA        idata
#define  PDATA        pdata
#define  XDATA        xdata
#define  RDATA        code

typedef union
{
	uchar byte;
	struct
	{
		uchar bit0 : 1;
		uchar bit1 : 1;
		uchar bit2 : 1;
		uchar bit3 : 1;
		uchar bit4 : 1;
		uchar bit5 : 1;
		uchar bit6 : 1;
		uchar bit7 : 1;
	}Bits;
}Field_8bits;

typedef union
{
	uint word;
	struct
	{
		uchar bit0 : 1;
		uchar bit1 : 1;
		uchar bit2 : 1;
		uchar bit3 : 1;
		uchar bit4 : 1;
		uchar bit5 : 1;
		uchar bit6 : 1;
		uchar bit7 : 1;
		uchar bit8 : 1;
		uchar bit9 : 1;
		uchar bit10 : 1;
		uchar bit11 : 1;
		uchar bit12 : 1;
		uchar bit13 : 1;
		uchar bit14 : 1;
		uchar bit15 : 1;
		
	}Bits;
}Field_16bits;


typedef union
{
	uint W;
	struct
	{
		uchar L;
		uchar H;
	}HL;
}Uint_16bits;

typedef union
{
	ulong L;
	struct
	{
		uint H;
		uint L;
	}W;
	struct
	{
		uchar HH;
		uchar HL;
		uchar LH;
		uchar LL;
	}HL;
}Ulong_32bits;



#define   FALSE   (Bool)0
#define   TRUE    (Bool)!FALSE

/*======================================================*/

#elif defined (RENESAS_RL78)

typedef  bit             Bool;
typedef  unsigned char   uchar;
typedef  unsigned int    uint;
typedef  unsigned long	 ulong;
typedef  unsigned short  ushort;


typedef union
{
	uchar byte;
	struct
	{
		uchar bit0 : 1;
		uchar bit1 : 1;
		uchar bit2 : 1;
		uchar bit3 : 1;
		uchar bit4 : 1;
		uchar bit5 : 1;
		uchar bit6 : 1;
		uchar bit7 : 1;
	}Bits;
}Field_8bits;

typedef union
{
	uint word;
	struct
	{
		uchar bit0 : 1;
		uchar bit1 : 1;
		uchar bit2 : 1;
		uchar bit3 : 1;
		uchar bit4 : 1;
		uchar bit5 : 1;
		uchar bit6 : 1;
		uchar bit7 : 1;
		uchar bit8 : 1;
		uchar bit9 : 1;
		uchar bit10 : 1;
		uchar bit11 : 1;
		uchar bit12 : 1;
		uchar bit13 : 1;
		uchar bit14 : 1;
		uchar bit15 : 1;
		
	}Bits;
}Field_16bits;


typedef union
{
	uint W;
	struct
	{
		uchar L;
		uchar H;
	}HL;
}Uint_16bits;

typedef union
{
	ulong L;
	struct
	{
		uint L;
		uint H;
	}W;
	struct
	{
		uchar LL;
		uchar LH;
		uchar HL;
		uchar HH;
	}HL;
}Ulong_32bits;

#define   FALSE   (Bool)0
#define   TRUE    (Bool)!FALSE

#endif    /* KEIL_C51 */

/*########################################################################*/
/*########################################################################*/

#endif   /* _MYDEF_H  */


