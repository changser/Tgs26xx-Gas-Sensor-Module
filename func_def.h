//======================================================
// Function and global variables definition
//======================================================

void port_init();             	// initialize ports
void clock_init();            	// initialize operation clock
void ADC_init();              	// initialize A/D convertor
void ADC_start(unsigned char ch);	// start A/D convertor
unsigned int ADC_read();      	// read A/D convertor
void Timer0_init();              	// initialize Basic interval timer
void UART_init();             	// initialize UART interface
void UART_write(unsigned char dat);	// write UART
unsigned char UART_read();    	// read UART
void ADC_process();
void ADC_error(unsigned char n);
void EEI2C_Init(void);
void EEI2C_Start(void);
void EEI2C_Stop(void);
void EEI2C_Write(unsigned char dat);
unsigned char EEI2C_Read(void);
unsigned char EEI2C_GetAck(void);
void EEI2C_PutAck(unsigned char ack);
unsigned char EEI2C_PutChar(unsigned char SubAddr, unsigned char dat);
unsigned char EEI2C_GetChar(unsigned char SubAddr, unsigned char *dat);
//unsigned char EEI2C_Puts(unsigned char SubAddr,unsigned char size,unsigned char *dat);
//unsigned char EEI2C_Gets(unsigned char SubAddr,unsigned char size,unsigned char *dat);
void DelayMicroSeconds(unsigned char nuS);
void EEPROM_process(void);
void UART_FillDataBuffer(void);
void UART_ReceiveData(unsigned char dat);
void UART_RxDatPro(void);




//20170214
code  unsigned int  K10_10[71]=		               // 华工感温包
{
    //3450
//	3915,3904,3894,3882,3871,3858,3845,3832,3818,3804, //"-40","-39","-38","-37","-36","-35","-34","-33","-32","-31"
//	3788,3773,3756,3739,3721,3703,3684,3664,3644,3623, //"-30","-29","-28","-27","-26","-25","-24","-23","-22","-21"
//	3601,3578,3555,3531,3507,3481,3455,3428,3401,3373, //"-20","-19","-18","-17","-16","-15","-14","-13","-12","-11"
//	3344,3314,3284,3253,3221,3189,3156,3123,3089,3054, //"-10","-9","-8","-7","-6","-5","-4","-3","-2","-1",
//	3019,2984,2947,2911,2874,2836,2798,2760,2722,2683, //"0","1","2","3","4","5","6","7","8","9",
//	2644,2605,2565,2525,2486,2446,2406,2366,2326,2286, //"10","11","12","13","14","15","16","17","18","19",
//	2246,2206,2166,2127,2087,2048,2009,1970,1932,1894, //"20","21","22","23","24","25","26","27","28","29",
//	1856,1819,1781,1745,1709,1673,1637,1602,1568,1534, //"30","31","32","33","34","35","36","37","38","39",
//	1500,1467,1435,1403,1371,1340,1310,1280,1251,1222, //"40","41","42","43","44","45","46","47","48","49",
//	1194,1166,1139,1112,1086,1060,1035,1011,986,963,   //"50","51","52","53","54","55","56","57","58","59",
//	940,917,895,874,853,833,812,793,773,755, 		   //"60","61","62","63","64","65","66","67","68","69",
//	736,719,701,684,668,652,636,620,606,591, 		   //"70","71","72","73","74","75","76","77","78","79",
//	577,563,549,536,523,511,498,486,475,463, 		   //"80","81","82","83","84","85","86","87","88","89",
//	452,441,431,421,411,402,392,382,374,365, 		   //"90","91","92","93","94","95","96","97","98","99",
//	356,348,340,332,325,317, 						   //"100","101","102","103","104","105",
	
	1471,1490,1509,1529,1548,1568,1588,1608,1628,1648, //"-10","-9","-8","-7","-6","-5","-4","-3","-2","-1",
	1668,1688,1708,1729,1749,1768,1788,1808,1828,1847, //"0","1","2","3","4","5","6","7","8","9",
	1866,1885,1905,1923,1942,1960,1978,1996,2014,2031, //"10","11","12","13","14","15","16","17","18","19",
	2048,2065,2081,2097,2113,2129,2144,2159,2174,2189, //"20","21","22","23","24","25","26","27","28","29",
	2203,2217,2230,2243,2256,2269,2281,2293,2305,2317, //"30","31","32","33","34","35","36","37","38","39",
	2328,2339,2350,2360,2370,2380,2390,2399,2408,2417, //"40","41","42","43","44","45","46","47","48","49",
	2426,2434,2442,2450,2458,2466,2473,2480,2487,2494,   //"50","51","52","53","54","55","56","57","58","59",
	2500,                                         		   //"60"
};

union UC_BITCHAR{
 unsigned char tmp;
 struct BITS {
     unsigned char bit0 : 1;
     unsigned char bit1 : 1;
     unsigned char bit2 : 1;
     unsigned char bit3 : 1;
     unsigned char bit4 : 1;
     unsigned char bit5 : 1;
     unsigned char bit6 : 1;
     unsigned char bit7 : 1;
 }Bits; 
};

// ----------------------ADC variable -----------------
data union UC_BITCHAR systemflag1;
#define b_ADCSample   systemflag1.Bits.bit0   // 允许采样标记

#define b_RTCError    systemflag1.Bits.bit1   // 
#define b_HEATError   systemflag1.Bits.bit2   //
#define b_SENSORError systemflag1.Bits.bit3   //

#define b_EWFlag      systemflag1.Bits.bit4   // EEPROM写入标记
#define b_EEPROMError systemflag1.Bits.bit5   

#define b_RtcOutRange systemflag1.Bits.bit6   //20170214
#define b_SensorOutRange systemflag1.Bits.bit7//20170214

unsigned int          ADC_RTCBuf[8];          // RTC采样缓存
unsigned int          ADC_HEATBuf[8];         // HEAT采样缓存
unsigned int          ADC_SENSORBuf[30];       // SENSOR采样缓存

data unsigned char    ADC_RTCSampleCnt;
data unsigned char    ADC_HEATSampleCnt;
data unsigned char    ADC_SENSORSampleCnt;
data unsigned char    ADC_RTCErrorCnt;
data unsigned char    ADC_HEATErrorCnt;
data unsigned char    ADC_SENSORErrorCnt;

data unsigned char    ADC_SampleCnt;          // 采样计数器

data float            ADC_Temp;               //20170214
data float            ADC_Rtc;                //20170214
data float            ADC_Heat;
data float            ADC_Sensor;
//20170214
data float            ADC_Sensor;            
data unsigned int     Concentration;
data unsigned char    Concentration_H;
data unsigned char		Concentration_L;
data float            R_Concentration;

unsigned int          ADC_DatumpointBuf[21];  // 基准值缓存
data unsigned int     ADC_Datumpoint;         // 基准值
data unsigned char    ADC_DatumSampleCnt;   
data unsigned char    ADC_DatumSampleCnt2; 
data int  						RL;
data int              R_ConcentrationDatum;



// ----------------------EEPROM variable -----------------
// EESCL - P16
// EESDA - P15
#define SetESDA()        (P1 = P1 |  0x20)
#define ClrESDA()        (P1 = P1 &  0xDF)
#define SetESCL()        (P1 = P1 |  0x40)
#define ClrESCL()        (P1 = P1 &  0xBF)
#define EESet_SDA_IN()   (P1IO &= 0xDF)
#define EESet_SDA_OUT()  (P1IO |= 0x20)
#define EE_SDAin         (P1 & 0x20)  	      //EESDA 输入数据

data unsigned char    EE_RunStep;
// ----------------------UART  variable -----------------
data unsigned int     i_UartTxTimeCnt;
data unsigned char    c_UartTxStep;
data unsigned char    c_UartTxNum;
data unsigned char    c_UartTxLen;
unsigned char         c_UartTxBuf[12];

data union UC_BITCHAR systemflag3;
#define b_UartTxEnd   systemflag3.Bits.bit0
#define b_UartError   systemflag3.Bits.bit1
#define b_UartRxEnd   systemflag3.Bits.bit2

data unsigned char    c_UartRxStep;
data unsigned char    c_UartRxLen;
data unsigned char    c_UartRxChk;
data unsigned char    c_UartRxNum;
data unsigned char    c_UartRxRespond;
unsigned char         c_UartRxBuf[5];

data unsigned char    c_Datumpoint;
data unsigned char    c_SensorValue;
data unsigned char    c_AirQualityLevel;
data unsigned char    c_HeatState;
data unsigned char    c_HeatError;
// ----------------------basic variable -----------------
data union UC_BITCHAR systemflag2;
#define b_PowerOnDly_3min systemflag2.Bits.bit0

data unsigned int     i_PowerOnDlyCnt;



data unsigned char    c_testCnt;


//-----------------voc_process------------------
data unsigned char sensor_maxr_renewed_flag;//基准更新标志位
data unsigned char sensor_maxr_renewed_restart_flag;//基准值重新更新标志位
data unsigned char sensor_maxr_renewed_reset;//上电初始化标志位


void maxr_renewed(float Rs);
void high_operation(float Rs,float maxr);
void normal_operation(float Rs,float maxr);
void sensor_system_reset(float Rs);
void sensor_system_reset(float Rs);
void sensor_maxr_renewed_restart(float Rs);


data unsigned long sensor_Rs;//当前值
data unsigned long max_sensor_Rs;//周期内最大值
data unsigned long sensor_maxr;//基准值
data unsigned int sensor_maxr_time_counter;//周期计数器
xdata unsigned char pollution_level;//污染等级
xdata unsigned char last_pollution_level;
data unsigned int high_operation_timer_counter;
data unsigned int voc_system_reset_counter;
data char debug_a;
data char debug_b;
data char debug_c;
data char debug_d;
data char debug_e;
data char debug_f;
data char debug_g;
data char level_may_reduce;

