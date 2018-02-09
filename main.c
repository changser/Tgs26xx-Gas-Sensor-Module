//======================================================
// Main program routine
// - Device name  : MC96F8208S
// - Package type : 16SOP
//======================================================
// For XDATA variable : V1.041.00 ~
#define		MAIN	1

// Generated    : Tue, Jul 12, 2016 (17:43:48)
#include	"MC96F8208.h"
#include	"func_def.h"
#include  "math.h"





void main()
{
	cli();          	// disable INT. during peripheral setting
	clock_init();   	// initialize operation clock
	port_init();    	// initialize ports
	ADC_init();     	// initialize A/D convertor
	Timer0_init();     	// initialize Basic interval timer
	UART_init();    	// initialize UART interface
	EEI2C_Init();
	sei();          	// enable INT.
	
	while(1){
		//
		
		//P3 |= 0x20;       //注意：验证定时时间，可通过示波器测试电平翻转来验证
		
		//P35 = 1;
		
		if (b_PowerOnDly_3min == 1) {
			
			//P3   &= 0xDF;     //验证定时时间
			
			//P35 = 0;
			
			ADC_process();  //注意：ADC处理需完善
		}

		EEPROM_process(); //EE处理
		
		UART_RxDatPro();  //接受处理
	}
}

//======================================================
// interrupt routines
//======================================================

void INT_UART_Rx() interrupt 9   //注意：核实有没有使能RX中断
{
	// UART Rx interrupt
	unsigned char c_UartRxDat;
	
	c_UartRxDat = UARTDR;         //读取UART模块中的数据寄存器
	UART_ReceiveData(c_UartRxDat);//对读取的数据进行操作
}

void INT_UART_Tx() interrupt 10  //注意：这里发送中断是用来判断发送是否可以结束，否则就一直反复进入发送中断发送数据
{
	// UART Tx interrupt
	if (c_UartTxNum > c_UartTxLen -1) {  //注意：一定要搞清楚到底要发送多少帧数据
		c_UartTxNum = 0;
		b_UartTxEnd = 1;  //发送结束标志位

		IE1 &= (~0x10);// close interrupt	 //关闭发送中断
	} else {
		UARTDR = c_UartTxBuf[c_UartTxNum];
		c_UartTxNum++;
	}
}

//======================================================
// interrupt routines
//======================================================

void INT_Timer0() interrupt 13
{
	// Timer0 interrupt

	// power on dly 3min count
	if (i_PowerOnDlyCnt < 750) {  //此处暂时改为3s
		i_PowerOnDlyCnt ++;
	} else {
		b_PowerOnDly_3min = 1;
		c_HeatState       = 1;
	}
		
    // 250ms cycle ADC sample
	if(++ADC_SampleCnt >= 125) {
		ADC_SampleCnt   = 0;
		
		b_ADCSample     = 1;
	}

	// cycle 2s send data
	i_UartTxTimeCnt++;
	if (i_UartTxTimeCnt >= 600) {
		i_UartTxTimeCnt  = 0;
		
		// fill data to buffer
		UART_FillDataBuffer();   //10组char数据
		// send the first one
		UARTDR = c_UartTxBuf[0]; //
		c_UartTxNum = 1;
		c_UartTxLen = 10;
		// open tx int
		IE1 |= 0x10; // enable send
		
	}

		
}


//======================================================
// peripheral setting routines
//======================================================
/*
unsigned char UART_read()
{
	unsigned char dat;
	
	while(!(UARTST & 0x20));	// wait
	dat = UARTDR;   	// read
	return	dat;
}
*/

//延时函数
void DelayMicroSeconds(unsigned char nuS)
{
	unsigned char i;
	unsigned char j;
	for(i=0;i<nuS;i++)
	{
		for(j=0;j<20;j++)  NOP;  // 时钟周期 0.5uS*20=1uS
	}
}

//EE初始化
void EEI2C_Init(void)
{				
	SetESDA();        //起始为高电平
	SetESCL();
}


//EE开始
void EEI2C_Start(void)
{

	SetESCL();          //scl high
	SetESDA();
	DelayMicroSeconds(10);
	ClrESDA();          //接管数据总线
	DelayMicroSeconds(5);
	ClrESCL();          //接管时钟总线
}


//EE停止
void EEI2C_Stop(void)
{
	ClrESDA();      //接管数据总线
	DelayMicroSeconds(5);
	SetESCL();//scl high   	//释放时钟总线
    DelayMicroSeconds(5);
	SetESDA();      //释放数据总线
//对于某些器件来说，在下一次产生Start之前，额外增加一定的延时是必须的
	DelayMicroSeconds(15);
}


//EE写数据
void EEI2C_Write(unsigned char dat)
{
	//----------------------------------------------------------------------------------
	//注意：此处的算法思路为：通过dat与0x80中的1相与，实现dat按MSB到LSB顺序一位位得发送出去，
  //同时要注意基准数0x80中的1在每次运算完成后要右移一位
	//----------------------------------------------------------------------------------
    unsigned char i, j=0x80;
	for (i = 0; i < 8; i++) {   
	    ClrESCL();              // scl=0，接管时钟线
		DelayMicroSeconds(5);           
	    if (dat & j) {
		    SetESDA();
		} else { 
		    ClrESDA();
		}
		DelayMicroSeconds(5);
		SetESCL();              // scl=1  注意：此处释放SCL总线
		DelayMicroSeconds(5);   // delay
		j = j>>1;
	}
	ClrESCL();
	SetESDA();
}

//EE读数据
unsigned char EEI2C_Read(void)
{
    unsigned char i, j, temp;
		
	EESet_SDA_IN();            // set dir in
	DelayMicroSeconds(5);
	for (i = 0; i < 8; i++) 
	{
	    SetESCL();
		DelayMicroSeconds(5);
		if (EE_SDAin==0x20)    // 读取端口状态
		    j = 1;
		else 
		    j = 0;
		temp = (temp<<1) | j;
		ClrESCL();
		DelayMicroSeconds(5);
	}	
	EESet_SDA_OUT();           // set dir out
	DelayMicroSeconds(5);
	
	return temp;	
}

//EE读响应
unsigned char EEI2C_GetAck(void)
{
	unsigned char ack;
	
	SetESDA();
	EESet_SDA_IN();      // input	
	DelayMicroSeconds(5);
	
	SetESCL();
	DelayMicroSeconds(5);
	
	//ack = EE_SDAin;     // 读取端口状态
	if (EE_SDAin == 0x20) ack = 1;
	else ack = 0;
	ClrESCL();	
	DelayMicroSeconds(5);
	
	EESet_SDA_OUT();     // output
	DelayMicroSeconds(5);
	
	return ack;
}


//EE
void EEI2C_PutAck(unsigned char ack)
{	
	if (ack) 
	    SetESDA();
	else 
	    ClrESDA();
	
	DelayMicroSeconds(5);
	SetESCL();
	DelayMicroSeconds(5);
	ClrESCL();	
}

//EE
unsigned char EEI2C_PutChar(unsigned char SubAddr, unsigned char dat)	 
{
	EEI2C_Start();        // 开始
	EEI2C_Write(0xa0);    // 器件地址
    
	if (EEI2C_GetAck())   // 读取应答信号
	{    
		EEI2C_Stop();     // 结束
		return 1;         // 错误处理
	}
	EEI2C_Write(SubAddr); // 写从地址
	
	if (EEI2C_GetAck())   // 读取应答信号
	{
		EEI2C_Stop();     // 结束
		return 1;
	}
	EEI2C_Write(dat);     // 写数据
	
	if (EEI2C_GetAck())   // 读取应答信号
	{
	    EEI2C_Stop();     // 结束
	    return 1;
	}
	EEI2C_Stop();         // 结束
	
    return(0);
}

//EE
unsigned char EEI2C_GetChar(
				unsigned char SubAddr,
				unsigned char *dat
			  )
{
	EEI2C_Start();        // 开始
	EEI2C_Write(0xa0);    // 写器件地址+W  注意：此处用的是AT24C02，实际要在芯片手册查询从机的地址
	
	if (EEI2C_GetAck())   // 读取应答信号
	{
	    EEI2C_Stop();     // 结束
		return 1;         // 错误处理
	}	
	EEI2C_Write(SubAddr); // 写从地址
	
	if (EEI2C_GetAck())   // 读取应答信号
	{
	    EEI2C_Stop();     // 结束
	    return 1;  
	}
		 
	EEI2C_Start();        // 重复开始
    EEI2C_Write(0xa1);    // 写器件地址 + R

	if (EEI2C_GetAck())   // 读取应答信号
	{
	    EEI2C_Stop();     // 结束
	    return 1;
	}
		
    *dat = EEI2C_Read();  // 读取数据
	
    EEI2C_PutAck(1);      // no acknowledge from master
	
	EEI2C_Stop();         // 结束
	
    return(0);
}

/*
unsigned char EEI2C_Puts(
				unsigned char SubAddr,
				unsigned char size,
				unsigned char *dat
			  )
{
    unsigned char i;
	  
    EEI2C_Start();            // 开始
	EEI2C_Write(0xa0);        // 写器件地址 + W
	
	if (EEI2C_GetAck())       // 读取应答信号
	{
	    EEI2C_Stop();         // 结束
	    return 1;             // 错误处理
	}
		
	EEI2C_Write(SubAddr);     // 写从地址
	
	if (EEI2C_GetAck())       // 读取应答信号
	{
	    EEI2C_Stop();         // 结束
	    return 1;             // 错误处理
	}
		
	for (i = 0; i < size; i++)
	{
	    EEI2C_Write(*dat);
		
	    if (EEI2C_GetAck())   // 读取应答信号
		{
		    EEI2C_Stop();     // 结束
	        return 1;         // 错误处理
		}
			
		dat++;
	}
	EEI2C_Stop();             // 结束表示

	return (0);
}

unsigned char EEI2C_Gets(
				unsigned char SubAddr,
				unsigned char size,
				unsigned char *dat
			  )
{

	EEI2C_Start();            // 开始
	EEI2C_Write(0xa0);        // 写器件地址 + W
	
	if (EEI2C_GetAck())       // 读取应答信号
	{
	    EEI2C_Stop();         // 结束
	    return 1;             // 错误处理
	}
		
	EEI2C_Write(SubAddr);
	
	if (EEI2C_GetAck())       // 读取应答信号
	{
	    EEI2C_Stop();         // 结束
	    return 1;           // 错误处理
	}
		
	EEI2C_Start();            // 重复开始
    EEI2C_Write(0xa1);        // 写器件地址 + R 
	
	if (EEI2C_GetAck())       // 读取应答信号
	{
	    EEI2C_Stop();         // 结束通讯
		return 1;             // 错误处理
	}
   
	for (;;)                  // 循环读取数据
	{
		*dat++ = EEI2C_Read();
		if ( --size == 0 )
		{
			NOP;
			EEI2C_PutAck(1);
			break;
		}
		EEI2C_PutAck(0);
	}
	EEI2C_Stop();             // 结束
	
	return 0;
}
*/
/////////////////////////////////////////////////////////
//address:00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
//content:AH AL                55
/////////////////////////////////////////////////////////
void EEPROM_process()
{
	unsigned char i, j, tmp;
	
	switch(EE_RunStep)
	{
		case 0:
			// 读取EEPROM中的数据还原系统设置值
			i = 0;j = 0;
			j = EEI2C_GetChar(0x07,&i);
			if (j == 1) {// 如果出错再来一次
				i = 0;
				DelayMicroSeconds(30);
				b_EEPROMError = EEI2C_GetChar(0x07,&i);
			}
			
			if (i == 0x55) {
				// 读取系统设置参数
				tmp = 0;
				DelayMicroSeconds(30);				
				b_EEPROMError |= EEI2C_GetChar(0x0,&tmp);
				ADC_Datumpoint = tmp;
				ADC_Datumpoint = ADC_Datumpoint<<8;
				tmp = 0;
				DelayMicroSeconds(30);
				b_EEPROMError |= EEI2C_GetChar(0x01,&tmp);
				ADC_Datumpoint = ADC_Datumpoint+tmp;
			} else {
				// 				
			}
			EE_RunStep = 1;
			break;
			
		case 1:
			if((b_EWFlag == 1)&&(b_EEPROMError == 0)) {
				
				b_EWFlag= 0;//清除写入标记
				
				i = 0;j = 0;
				j = EEI2C_GetChar(0x07,&i);
				if (j == 1) {// 如果出错再来一次
					i = 0;
					DelayMicroSeconds(30);
					b_EEPROMError = EEI2C_GetChar(0x07,&i);
				}
				
				if (i != 0x55) {
					// 
					tmp = 0x55;
					DelayMicroSeconds(30);				
					b_EEPROMError|=EEI2C_PutChar(0x07,tmp);
				}
				
				tmp = (unsigned char)ADC_Datumpoint>>8;
				DelayMicroSeconds(30);				
				if(b_EEPROMError==0)b_EEPROMError|=EEI2C_PutChar(0x00,tmp);

				tmp = (unsigned char)ADC_Datumpoint;
				DelayMicroSeconds(30);				
				if(b_EEPROMError==0)b_EEPROMError|=EEI2C_PutChar(0x01,tmp);
			}
			break;
			
		default:
			EE_RunStep = 0;
	}
}

unsigned int ADC_read()  //AD数据读取
{
	// read A/D convertor
	unsigned int adcVal;
	
	while(!(ADCCRL & 0x10));	// wait ADC busy   注意：此处可以增加break，防止转换故障造成死循环
	adcVal = (ADCDRH << 8) | ADCDRL;	// read ADC  
	return	adcVal;
}

void ADC_init()
{
	// initialize A/D convertor
	ADCCRL = 0x80;  	// setting  模块使能，转换未开始，内部参考电压VDD，AN0口
	ADCCRH = 0x05;  	// trigger source, alignment, frequency   中断清零，ADST触发，LSB align (ADCRDH[3:0], ADCDRL[7:0])，4M频率
	ADWCRL = 0x00;  	// Wake-up enable Low   禁唤醒
	ADWCRH = 0x00;  	// Wake-up enable High  禁唤醒
	ADWRCR0 = 0x00; 	// Wake-up R selection  禁唤醒
	ADWRCR1 = 0x00; 	// Wake-up R selection  禁唤醒
	ADWRCR2 = 0x00; 	// Wake-up R selection  禁唤醒
	ADWRCR3 = 0x00; 	// Wake-up R selection  禁唤醒
}

void ADC_start(unsigned char ch)
{
	// start A/D convertor
	ADCCRL = (ADCCRL & 0xf0) | (ch & 0x0f);	// select channel  通道选择
	ADCCRL |= 0x40; 	// start ADC  ADST置1触发转换
}

void ADC_process()
{// AN10 - RTC 气体传感器// AN9 - HEAT// AN2 - RTC 温度传感器
	
	unsigned int  tmp;
	unsigned int  sum, max, min, temp, firstone;
	unsigned char bchange = 0;
	unsigned char i,j;
	unsigned int  dlycnt;
 	
	//////////////////////////////////////////////////////////////////采样AD值	 
	if (b_ADCSample == 1) //判断250ms循环采样到时间
		{  
			b_ADCSample = 0;       //先把标志位置0
			

			//************************采样温度****************************//
			ADC_start(2);		//选择AN2温度采样    
			dlycnt = 0xffff;//计数变量
			while ((ADCCRL & 0x10) != 0x10) { //检测AFLAG是否置1，即检测AD转换是否完成
				dlycnt--;
				if (dlycnt == 0) break;//计数完成强制跳出while，防止AFLAG没有置1，造成死循环
			}
			if ((ADCCRL & 0x10) == 0x10) {  //若检测到AFLAG置1，开始读取寄存器数据
			tmp = ADC_read();  //读取AD寄存器数据
			} else {
				tmp = 0;  //若AFLAG没有置1，tmp清零
			}
			if ((tmp < 50) || (tmp > 0x0FCD)) { //注意：报错区间，不确定
			 ADC_error(0);   //温度传感器报错，报错标志位置1
			} else {
				ADC_RTCBuf[ADC_RTCSampleCnt] = tmp;  //将当前温度数据放入温度数据存储数组中，此数组可以存储5个数据
				ADC_RTCSampleCnt++;  //温度采样计数器
				ADC_RTCErrorCnt = 0; //温度传感器报错计数器清零
				b_RTCError      = 0; //温度传感器报错标志位清零
				
				/////////////////////////////////////////////////////////计算
				max = 0;
				min = 0x0FFF;
				sum = 0;
				if (ADC_RTCSampleCnt >= 8) {  //判断温度采样计数器是否已满
					ADC_RTCSampleCnt  = 0;      //计数器清零
					for (i = 0; i < 8; i++) {   //注意：此处只选取4个值，为什么不取5个值
						if (ADC_RTCBuf[i] > max)max = ADC_RTCBuf[i];  //选出最小温度  RTC电阻
						if (ADC_RTCBuf[i] < min)min = ADC_RTCBuf[i];  //选出最大温度  RTC电阻
					}
					for (i = 0; i < 8; i++) sum += ADC_RTCBuf[i];   
					tmp = (sum - min - max)/6;  //求温度平均值
					
					//20170214
					ADC_Rtc = tmp;
					if(tmp <= K10_10[0]) {      
						ADC_Temp = -10.0;           //注意：根据不同感温包特性曲线确定
						b_RtcOutRange = 1;					//超出传感器测量温度范围
					} else if (tmp  >= K10_10[70]) {
						ADC_Temp = 60.0; 
						b_RtcOutRange = 1;					//超出传感器测量温度范围
					} else {
						for (i = 1, j = 0; i < 70; i++) {   //此处的思想是：用当前AD值与温度特性表比较，找出最接近的温度
							if (K10_10[i] > tmp) break;  
						}
						// 比较
						if ((K10_10[i] - tmp) >= (tmp - K10_10[i-1])) {
							j = i-1;
						} else {
							j = i;
						}
						// 计算温度值
						ADC_Temp = j - 10.0;// 
						b_RtcOutRange = 0;
					}
					
				}
			}
			//************************采样温度****************************//
			
			////////////////////////////////////////////////采样加热丝状态
			ADC_start(9);		 //选择AN9   
			dlycnt = 0xffff; //采样等待计数器
			while ((ADCCRL & 0x10) != 0x10) {  //检测是否转换完成
				dlycnt--;   //等待
				if (dlycnt == 0) break;   //强制跳出防止转换失败
			}
			if ((ADCCRL & 0x10) == 0x10) {  //检测是否转换完成
				tmp = ADC_read();   //读取AD值
			} else {
				tmp = 0;   //若转换未完成，AD值清零
			}
			if ((tmp < 50) || (tmp > 0x0FCD)) {  //注意：核实此处if原因
				ADC_error(1); //加热丝报错
			} else {
				ADC_HEATBuf[ADC_HEATSampleCnt] = tmp;   //AD值装入加热丝数组中
				ADC_HEATSampleCnt++;   //采样计数器
				ADC_HEATErrorCnt = 0;  //加热丝报错计数器清零
				b_HEATError = 0;       //报错标志位清零
				
				/////////////////////////////////////////////////////////计算
				max = 0;
				min = 0x0FFF;
				sum = 0;
				if (ADC_HEATSampleCnt >= 8) {
					ADC_HEATSampleCnt  = 0;	
					for (i = 0; i < 8; i++) {  //注意：此处只用4组数据做比较
						if (ADC_HEATBuf[i] > max)max = ADC_HEATBuf[i];
						if (ADC_HEATBuf[i] < min)min = ADC_HEATBuf[i];
					}
					for (i = 0; i < 8; i++) sum += ADC_HEATBuf[i];
					tmp = (sum - min - max)/6;

									ADC_Heat = tmp;  //注意：此处保留的仍是AD值，注意此值得用法
				}
			}
			
			
			////////////////////////////////////////////////采样气体传感器
			
			if(voc_system_reset_counter >= 1)//计时2分钟
			{
				voc_system_reset_counter = 480;
				ADC_start(10);			//选择AN10
				dlycnt = 0xffff;    //等待计数器
				while ((ADCCRL & 0x10) != 0x10) //检测AFLAG是否置1
					{  
						dlycnt--;
						if (dlycnt == 0) break;  //强制跳出防止转换失败
					}
				if ((ADCCRL & 0x10) == 0x10) //检测AFLAG是否置1
					{  
						tmp = ADC_read();  //读取AD值，注意：此处变量名仍是tmp
					} 
				else //若AFLAG不为1
					{  
						tmp = 0;   //清空传感器数值
					}
				if ((tmp < 10) || (tmp > 0x0FdD)) //若AD值过小或过大
					{  
						ADC_error(2);  //AD故障
					} 
				else //若AD值符合测试要求
					{ 
						ADC_SENSORBuf[ADC_SENSORSampleCnt] = tmp; //AD值装载进数组 
						ADC_SENSORSampleCnt++; //采样计数器
						ADC_SENSORErrorCnt = 0;  //报错计数器
						b_SENSORError = 0;    //气体检测报错标志位
						if (ADC_SENSORSampleCnt >= 30) //此处数据筛选与温度、加热一样
							{
								//*************************求平均值*********************//
								/*
								max = 0;
								min = 0x0FFF;
								sum = 0;
								ADC_SENSORSampleCnt  = 0;
								for (i = 0; i < 8; i++) //找出最大值和最小值
								{
									if (ADC_SENSORBuf[i] > max)max = ADC_SENSORBuf[i];
									if (ADC_SENSORBuf[i] < min)min = ADC_SENSORBuf[i];
								}
								for (i = 0; i < 8; i++) sum += ADC_SENSORBuf[i];
								tmp = (sum - min - max)/6;
								ADC_Sensor = tmp;   //此处是unsigned int AD值
								*/
								//*************************求平均值********************//

								
								//*************************冒泡排序********************//
								ADC_SENSORSampleCnt  = 0;
								firstone = ADC_SENSORBuf[0];
						    for(i = 0;i < 30;i++)
								{
									for(j = 1;j < 30;j++)
									{
										if(ADC_SENSORBuf[j-1] < ADC_SENSORBuf[j])//从大到小排序
										{
											temp = ADC_SENSORBuf[j-1];
											ADC_SENSORBuf[j-1] = ADC_SENSORBuf[j];
											ADC_SENSORBuf[j] = temp;
											bchange = 1;
										}
									}
									if(bchange == 0) break;
								}
								if(firstone > ADC_SENSORBuf[6]) ADC_Sensor = ADC_SENSORBuf[6];//说明气体浓度降低
								else ADC_Sensor = ADC_SENSORBuf[1];//说明气体浓度升高
								//*************************冒泡排序********************//																
								
	              //*************************voc_process****************//
								ADC_Sensor++; //范围为0-4095
								sensor_Rs = 2200*(4096/ADC_Sensor-1);   //单位：Ω
					
								if(sensor_maxr_renewed_reset == 0)//上电初始化
								{
									sensor_maxr_renewed_reset = 1;
									sensor_maxr = 10000; //洁净空气中Rs，或从eeprom读取,单位kΩ
									max_sensor_Rs = sensor_Rs;
									sensor_maxr_time_counter = 0;
									high_operation(sensor_Rs,sensor_maxr);//初始污染等级
								}
								else//上电初始化完成
								{									
									//********************判断等级****************************************//
//									if(high_operation_timer_counter <= 720)//高灵敏度模式保持3min，等级判断
//									{
//										high_operation(sensor_Rs,sensor_maxr);
//										high_operation_timer_counter++;
//									}			
//									else//正常模式,等级判断
//									{
										normal_operation(sensor_Rs,sensor_maxr);
//									}
									//********************判断等级****************************************//
									
																									
									if(pollution_level > 0)
									{
										sensor_maxr_renewed_flag = 0;
										sensor_maxr_renewed_restart_flag = 0;
									}
									else if(last_pollution_level > 0 && pollution_level == 0)//
									{
										sensor_maxr_renewed_flag = 0;//基准值更新标志位清零
										sensor_maxr_renewed_restart_flag = 1;//基准值重新更新标志位清零									
									}
									else if(last_pollution_level == 0 && pollution_level == 0)
									{
										sensor_maxr_renewed_flag = 1;//基准值更新标志位置1
										sensor_maxr_renewed_restart_flag = 0;//基准值重新更新标志位清零
									}
									else
										sensor_maxr_renewed_reset = 0;
								
									if(sensor_maxr_renewed_restart_flag == 1)
										sensor_maxr_renewed_restart(sensor_Rs);
									
									if(sensor_maxr_renewed_flag == 1)
										maxr_renewed(sensor_Rs);														
								}
								
								last_pollution_level = pollution_level;//前一个污染等级
								
							}
					}
			}				
			else//计时不满2分钟
			{
				voc_system_reset_counter++;//计时+1
			}
		}

}
              //*************************voc_process****************//
//*********************************adc_process************************************//


void ADC_error(unsigned char n)  //ADC报错，此处有三种报错：温度、加热丝、气体传感器
{
	switch (n) {
	 	case 0:
			if (ADC_RTCErrorCnt < 250) {  //温度传感器报错计数
				ADC_RTCErrorCnt++;
			} else {

				b_RTCError = 1;	  				//温度传感器报错标志位置1
			}	
			break;

  		case 1:
			if (ADC_HEATErrorCnt < 250) {  //加热丝报错计数
				ADC_HEATErrorCnt++;
			} else {

			 	b_HEATError = 1;       //加热丝报错标志位置1
			}
		 	break;

		case 2:
			if (ADC_SENSORErrorCnt < 250) {    //气体传感器报错计数
				ADC_SENSORErrorCnt++;
			} else {
				b_SENSORError = 1;     //气体传感器报错标志位置1
			}
			break;

		default:
		    NOP;   //延时一个机器周期，此IC一个机器周期包含两个时钟周期
	}
}

//======================================================
// peripheral setting routines
//======================================================

void Timer0_init()
{
	// initialize Timer0
	// 8bit timer, period = 4.000000mS  8位计数器
	T0CR = 0x88;    	// timer setting  fx/128
	T0DR = 0xF9;    	// period count   溢出位
	IE2 |= 0x02;    	// Enable Timer0 interrupt  采用匹配中断方式
	T0CR |= 0x01;   	// clear counter   清除定时器0计数器
}


void UART_init()
{
	// initialize UART interface
	// ASync. 4807bps N 8 1
	UARTCR2 = 0x02; 	// activate UART  开启UART模块
	UARTCR1 = 0x06; 	// bit count, parity  无校验，8bit
	UARTCR2 |= 0x6C;	// 20170214,interrupt, speed
	UARTCR3 = 0x00; 	// stop bit  1位停止位
	UARTBD = 0x67;  	// baud rate   4800bps
	IE1 |= 0x18;    	// 20170214,enable UART interrupt 使能RX中断，禁止TX中断 // 0x18  使能RX中断，使能TX中断
}

void UART_FillDataBuffer()  //注意：此处只有10组，可以根据协议修改数量
{
	unsigned char i, k;

	c_UartTxBuf[0] = 0x7E;
	c_UartTxBuf[1] = 0x7E;
	c_UartTxBuf[2] = 0x06;  //帧长
	c_UartTxBuf[3] = 0x31;  //20170214
	
	c_UartTxBuf[4] = Concentration_H;  //20170214
	
	c_UartTxBuf[5] = Concentration_L; //02170214


	c_UartTxBuf[6] = pollution_level;  //当前空气品质
	
	c_UartTxBuf[7] = c_HeatState;  //加热丝状态
	
	if (b_HEATError == 1){
		c_HeatError = 1;
	} else {
		c_HeatError = 0;
	}
	c_UartTxBuf[8] = c_HeatError;  //加热丝故障
	for(i=2,k=0;i<9;i++){
		k+=c_UartTxBuf[i];
	}
	c_UartTxBuf[9] = k;  //校验
}

void UART_ReceiveData(unsigned char dat)
{

	switch (c_UartRxStep){
		case 0:
			if (dat == 0x7E) c_UartRxStep = 1;
			break;
			
		case 1:
			if (dat == 0x7E){
				c_UartRxStep = 0x02;
			} else {
				c_UartRxStep = 0x00;
			}
			break;
			
		case 2:
			if (dat == 0x06) {
			 	c_UartRxLen = dat;    //帧长3，
				c_UartRxStep = 3;     //接收进程
				c_UartRxChk = dat;    //校验运算 
			}else if (dat == 0x7E) {
			 	c_UartRxStep = 2;
			}else {
			 	c_UartRxStep = 0;
			}
			break;
			
		case 3:
			if (dat == 0x31) {     //查询是否是数据帧
				c_UartRxStep   = 4;  //接收进程
				c_UartRxChk   += dat;//校验运算
				c_UartRxNum    = 0;  //接收数据编号
			} else if (dat == 0x7E) {
				c_UartRxStep   = 1;
			} else {
				c_UartRxStep   = 0;
			}
			break;

		case 4:
			if (c_UartRxNum < c_UartRxLen - 1) {//帧长等于接收数据量+2，检验数据是否接收完
				c_UartRxBuf[c_UartRxNum] = dat;//装载接收数据
				c_UartRxChk             += dat;//校验运算
				c_UartRxNum++;//接收数据编号递增
			} else {//
				if (c_UartRxChk == dat) {
					//check ok and set end flag  校验
					b_UartError = 0;  // clear fualt flag  错误帧标志位

					b_UartRxEnd = 1;  //接收结束标志位
				}
				c_UartRxStep   = 0;
			}
			break;
		default:
			c_UartRxStep = 0;
		
		break;
						
	}
}
void UART_RxDatPro()
{
	if (b_UartRxEnd == 1) {
		b_UartRxEnd  = 0;

		// add new code
		c_UartRxRespond = c_UartRxBuf[0];
	}
}

/*
void UART_write(unsigned char dat)
{
	while(!(UARTST & 0x80));	// wait
	UARTDR = dat;   	// write
}
*/
//时钟设置
void clock_init()
{
	// internal RC clock (8.000000MHz)
	OSCCR = 0x20;   	// Set Int. OSC
	SCCR = 0x00;    	// Use Int. OSC
}

//端口初始化
void port_init()
{
	unsigned char i;
	
	// initialize ports
	//   1 : P32      out 
	//   2 : RXD      in  
	//   3 : TXD      out 
	//   4 : P16      out 
	//   5 : P15      out 
	//   6 : P14      out 
	//   7 : AN10     in  
	//   8 : AN9      in  
	//   9 : AN2      in  
	//  10 : P01      out 
	//  11 : P00      out 
	//  14 : P37      out 
	//  15 : P36      out 
	//  16 : P35      out 
	P0IO = 0xFB;    	// direction
	P0PU = 0x00;    	// pullup
	P0OD = 0x00;    	// open drain
	P03DB = 0x00;   	// bit7~6(debounce clock), bit5~0=P35,P06~02 debounce
	P0   = 0xc0;    	// port initial value

	P1IO = 0xF3;    	// direction
	P1PU = 0x00;    	// pullup
	P1OD = 0x00;    	// open drain
	P12DB = 0x00;   	// debounce : P23~20, P13~10
	P1   = 0x00;    	// port initial value

	P2IO = 0xFF;    	// direction
	P2PU = 0x00;    	// pullup
	P2OD = 0x00;    	// open drain
	P2   = 0x00;    	// port initial value

	P3IO = 0xFD;    	// direction
	P3PU = 0x00;    	// pullup
	P3OD = 0x00;    	// open drain
	P3   = 0x00;    	// port initial value

	// Set port functions
	P0FSR = 0x08;   	// P0 selection
	P1FSRH = 0x00;  	// P1 selection High
	P1FSRL = 0x50;  	// P1 selection Low
	P2FSR = 0x00;   	// P2 selection
	P3FSR = 0x01;   	// P3 selection

	// init variable for all
	b_ADCSample = 0;
	b_RTCError  = 0;
	b_HEATError = 0;
	b_SENSORError = 0;
	b_EWFlag    = 0;   //EE可写标志位
	b_EEPROMError = 0;
	b_RtcOutRange = 0;

	for(i=0;i<5;i++)ADC_RTCBuf[i]=0;
	for(i=0;i<5;i++)ADC_HEATBuf[i]=0;
	for(i=0;i<5;i++)ADC_SENSORBuf[i]=0;

	ADC_RTCSampleCnt = 0;
	ADC_HEATSampleCnt = 0;
	ADC_SENSORSampleCnt = 0;
	ADC_RTCErrorCnt = 0;
	ADC_HEATErrorCnt = 0;
	ADC_SENSORErrorCnt = 0;
	ADC_SampleCnt = 0;
	ADC_Temp = 0;
	ADC_Heat = 0;
	ADC_Sensor = 0;
	ADC_Rtc = 0;

	for(i=0;i<21;i++)ADC_DatumpointBuf[i]=0;
	ADC_Datumpoint = 0;
	ADC_DatumSampleCnt = 0;
	ADC_DatumSampleCnt2 = 0;
	EE_RunStep = 0;
	b_PowerOnDly_3min = 0;
	i_PowerOnDlyCnt = 0;

	i_UartTxTimeCnt = 0;
	c_UartTxStep = 0;
	c_UartTxNum = 0;
	c_UartTxLen = 0;
	for(i=0;i<12;i++)c_UartTxBuf[i] = 0; //根据通讯协议，一帧包含12个int
	b_UartTxEnd = 0;
	b_UartError = 0;
	b_UartRxEnd = 0;
	c_UartRxStep = 0;
	c_UartRxLen = 0;
	c_UartRxChk = 0;
	c_UartRxNum = 0;
	c_UartRxRespond = 0;
	for(i=0;i<5;i++)c_UartRxBuf[i] = 0;
	c_HeatError = 0;
	c_HeatState = 0;
	c_AirQualityLevel = 0;
	c_SensorValue = 0;
	c_Datumpoint = 0;
	
	c_testCnt = 0;
	RL = 2260;
  R_ConcentrationDatum = 2260;
	//20170214
	Concentration = 0x00ff;
	Concentration_H = 0x00;
	Concentration_L = 0xff;
	sensor_Rs = 0;
	max_sensor_Rs = 0;
	sensor_maxr = 0;
	sensor_maxr_time_counter = 0;
	pollution_level = 0;
	last_pollution_level = 0;
	high_operation_timer_counter = 0;
	voc_system_reset_counter = 0;
	debug_a = 0;
	debug_b = 0;
	debug_c = 0;
	debug_e = 0;
	debug_f = 0;
	debug_d = 0;
	debug_g = 0;
	
}


//上电初始化
//void sensor_system_reset(float Rs)
//{
//	sensor_maxr = 18000; //洁净空气中Rs，或从eeprom读取,单位kΩ
//	max_sensor_Rs = sensor_Rs;
//	sensor_maxr_time_counter = 0;
//	pollution_level = high_operation(sensor_Rs,sensor_maxr);//初始污染等级
//	pollution_level_previous = pollution_level;//前一个污染等级
//}


//基准值重新更新
void sensor_maxr_renewed_restart(float Rs)
{
	sensor_maxr = Rs; 
	max_sensor_Rs = Rs;
	sensor_maxr_time_counter = 0;
}


//基准值更新
void maxr_renewed(float Rs)
{
	if(sensor_maxr_time_counter >= 960)//8分钟更新一次
	{
		sensor_maxr = max_sensor_Rs;
		max_sensor_Rs = Rs;
		sensor_maxr_time_counter = 0;
	}
	else if(Rs >= sensor_maxr)
	{
		sensor_maxr = Rs;
		max_sensor_Rs = Rs;
		sensor_maxr_time_counter++;
	}
	else if(Rs >= max_sensor_Rs)
	{
		max_sensor_Rs = Rs;
		sensor_maxr_time_counter++;
	}
	else 
	{
		sensor_maxr_time_counter++;
	}		
	
}



//正常模式：等级判断
void normal_operation(float Rs,float maxr)
{
	int rs_ratio_maxr;
	
	rs_ratio_maxr = (Rs/maxr)*100;
	
	switch(last_pollution_level)
	{
		case 0:
			if(rs_ratio_maxr > 58 && rs_ratio_maxr <= 68)
			{
				pollution_level = 1;
				debug_a = 1;

			}
			else if(rs_ratio_maxr > 48 && rs_ratio_maxr <= 58)
			{
				pollution_level = 2;
				debug_a = 1;
			}
			else if(rs_ratio_maxr <= 48)
			{
				pollution_level = 3;
				debug_a = 1;
			}
			else 
			{
				pollution_level = 0;
				debug_a = 1;
			}
			
			break;
			
		case 1:
			if(rs_ratio_maxr > 58 && rs_ratio_maxr <= 71)
			{
				pollution_level = 1;
				debug_b = 1;
			}
			else if(rs_ratio_maxr > 48 && rs_ratio_maxr <= 58)
			{
				pollution_level = 2;
				debug_b = 1;
			}
			else if(rs_ratio_maxr <= 48)
			{
				pollution_level = 3;
				debug_b = 1;
			}
			else 
			{
				pollution_level = 0;
				debug_b = 1;
			}
			
			break;
			
		case 2:
			if(rs_ratio_maxr > 61 && rs_ratio_maxr <= 71)
			{
				pollution_level = 1;
				debug_c = 0;
			}
			else if(rs_ratio_maxr > 48 && rs_ratio_maxr <= 61)
			{
				pollution_level = 2;
				debug_c = 0;
			}
			else if(rs_ratio_maxr <= 48)
			{
				pollution_level = 3;
				debug_c = 0;
			}
			else 
			{
				pollution_level = 0;
				debug_c = 0;
			}
			
			break;
			
		case 3:
			if(rs_ratio_maxr > 61 && rs_ratio_maxr <= 71)
			{
				pollution_level = 1;
				debug_d = 0;
			}
			else if(rs_ratio_maxr > 51 && rs_ratio_maxr <= 61)
			{
				pollution_level = 2;
				debug_d = 0;
			}
			else if(rs_ratio_maxr <= 51)
			{
				pollution_level = 3;
				debug_d = 0;
			}
			else 
			{
				pollution_level = 0;
				debug_d = 0;
			}
			
			break;
			
		default:
			break;						
	}
}

	




//高灵敏度模式：等级判断
void high_operation(float Rs,float maxr)
{
	int rs_ratio_maxr;

	
	rs_ratio_maxr = (Rs/maxr)*100;
	
	switch(last_pollution_level)
	{
		case 0:
			if(rs_ratio_maxr > 81 && rs_ratio_maxr <= 88)
			{
				pollution_level = 1;
				debug_a = 0;
			}
			else if(rs_ratio_maxr > 73 && rs_ratio_maxr <= 81)
			{
				pollution_level = 2;
				debug_a = 0;
			}
			else if(rs_ratio_maxr <= 73)
			{
				pollution_level = 3;
				debug_a = 0;
			}
			else 
			{
				pollution_level = 0;
				debug_a = 0;
			}
			
			break;
			
		case 1:
			if(rs_ratio_maxr > 81 && rs_ratio_maxr <= 90)
			{
				pollution_level = 1;
				debug_b = 0;
			}
			else if(rs_ratio_maxr > 73 && rs_ratio_maxr <= 81)
			{
				pollution_level = 2;
				debug_b = 0;
			}
			else if(rs_ratio_maxr <= 73)
			{
				pollution_level = 3;
				debug_b = 0;
			}
			else 
			{
				pollution_level = 0;
				debug_b = 0;
			}
			
			break;
			
		case 2:
			if(rs_ratio_maxr > 83 && rs_ratio_maxr <= 88)
			{
				pollution_level = 1;
				debug_c = 0;
			}
			else if(rs_ratio_maxr > 73 && rs_ratio_maxr <= 83)
			{
				pollution_level = 2;
				debug_c = 0;
			}
			else if(rs_ratio_maxr <= 73)
			{
				pollution_level = 3;
				debug_c = 0;
			}
			else 
			{
				pollution_level = 0;
				debug_c = 0;
			}
			
			break;
			
		case 3:
			if(rs_ratio_maxr > 81 && rs_ratio_maxr <= 88)
			{
				pollution_level = 1;
				debug_d = 0;
			}
			else if(rs_ratio_maxr > 75 && rs_ratio_maxr <= 81)
			{
				pollution_level = 2;
				debug_d = 0;
			}
			else if(rs_ratio_maxr <= 75)
			{
				pollution_level = 3;
				debug_d = 0;
			}
			else 
			{
				pollution_level = 0;
				debug_d = 0;
			}
			
			break;
			
		default:
			break;		
	}
}


