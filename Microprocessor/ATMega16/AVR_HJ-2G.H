/*******************************************
  文件：AVR_HJ-2G.H
  功能：定义一些HJ-2G开发板上应用程序用到的常量
/******************************************/

#include <iom16v.h> //包含型号头文件
#include <macros.h> //包含"位"操作头文件

/******************数据类型宏定义******************/
#define uchar unsigned char
#define uint unsigned int

/******************数码管和LED常量******************/
#define LEDLK PA2 // LED锁存器控制端   注意：旧板使用，新版HJ-2G 不需要使用
#define SEGLK PA3 // 数码管段选锁存器控制端
#define BITLK PA4 // 数码管位选锁存器控制端

#define TRUE 1
#define FALSE 0
#define ALLLED 0XFF

// LED三级管开关函数

void LEDON() // 打开LED总开关
{
	DDRA = 0xff;  // 用于打开LED锁存
	PORTA = 0xfb; // 打开LED灯总线 PA2脚输出低电平0，打开三级管开关
}
void LEDOFF() // 关闭LED总开关
{
	DDRA |= BIT(PA2);  // 用于打开LED锁存
	PORTA |= BIT(PA2); // 关闭LED灯总线 PA2脚输出高电平1，关闭LED
}

// 数码管开关函数

void SEGOFF() // 关数码显示管函数 可以自己设计数码管示显什么数字,新手没有学过数码管模块，本函数请暂时不要看
{
	DDRA |= BIT(PA3);	// PA3设置为输出状态
	DDRA |= BIT(PA4);	// PA4设置为输出状态
	DDRB = 0xff;		// PB口设置为输出状态
	PORTB = 0xff;		// 发送模码
	PORTA |= BIT(PA3);	// PA3输出高电平，DU拉高
	PORTA &= ~BIT(PA3); // PA3输出低电平，DU拉低，段选锁存

	PORTB = 0xff;		// 发送为选  关掉数码管显示
	PORTA |= BIT(PA4);	// PA4输出高电平，WE拉高
	PORTA &= ~BIT(PA4); // PA4输出低电平，WE拉低，位选锁存
}

/*******************************************
函数名称: Delayus
功    能: 延时指定微秒（8M晶振）
参    数: US--延时的微秒数(大约，不是很精确，MS越大越准确)
返回值  : 无
/********************************************/
void Delayus(uint US)
{
	uint i;
	US = US * 5 / 4; // 5/4是在8MHz晶振下，通过软件仿真反复实验得到的数值
	for (i = 0; i < US; i++)
		;
}
/*******************************************
函数名称: Delayms
功    能: 延时指定毫秒（8M晶振）
参    数: MS--延时的毫秒数
返回值  : 无
/********************************************/
void Delayms(uint MS)
{
	uint i, j;
	for (i = 0; i < MS; i++)
		for (j = 0; j < 1141; j++)
			; // 1141是在8MHz晶振下，通过软件仿真反复实验得到的数值
}
/*******************************************
函数名称: Board_init
功    能: 初始化实验板，关闭全部功能
参    数: 无
返回值  : 无
/********************************************/
void Board_init(void)
{
	DDRA = 0xFF; // 将四个IO口全部配置为输出
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;

	SPCR = 0x00; // 还原SPI口，使其为正常端口

	PORTA |= BIT(PA6);	 //(BEEP)关闭蜂鸣器
	PORTC &= ~BIT(PC6);	 //(RELAY)初始化继电器为常闭连接状态
	PORTA &= ~BIT(PA1);	 // 关闭SPI总线DA
	PORTB = 0xFF;		 // 关闭LED
	PORTA |= BIT(LEDLK); // 锁存数据，使LED熄灭
	Delayus(5);
	PORTA &= ~BIT(LEDLK);

	PORTB = 0x00; // 输出段选
	PORTA |= BIT(SEGLK);
	Delayus(50);
	PORTA &= ~BIT(SEGLK);

	PORTB = 0xFF; // 输出位选
	PORTA |= BIT(BITLK);
	Delayus(50);
	PORTA &= ~BIT(BITLK);

	PORTD = 0xFF;
	PORTA |= BIT(PA7);
	Delayus(50);
	PORTA &= ~BIT(PA7);
}
/******************1602液晶常量及操作******************/
#define LCDa_CTRL PORTD	   // 1602控制端口定义
#define LCDa_CTRL_DDR DDRD // 控制端口方向寄存器定义
#define LCDa_RS PD4		   // 定义三个控制引脚
#define LCDa_RW PD5
#define LCDa_E PD6

#define LCDa_L1 0x80 // 第一行的地址：0x80+addr ,addr为列数
#define LCDa_L2 0xC0 // 第二行的地址：0x80+0x40+addr

#define LCDa_CGRAM_ADDR 0x40 // CGRAM的开始地址
#define LCDa_CGMAX 64		 // CGRAM存储的最大字节数

#define LCDa_SET_RS LCDa_CTRL |= BIT(LCDa_RS) // 三个控制管脚的控制操作
#define LCDa_SET_RW LCDa_CTRL |= BIT(LCDa_RW)
#define LCDa_SET_E LCDa_CTRL |= BIT(LCDa_E)
#define LCDa_CLR_RS LCDa_CTRL &= ~BIT(LCDa_RS)
#define LCDa_CLR_RW LCDa_CTRL &= ~BIT(LCDa_RW)
#define LCDa_CLR_E LCDa_CTRL &= ~BIT(LCDa_E)

#define LCDa_DO PORTB	   // 输出数据总线端口定义
#define LCDa_DI PINB	   // 输入数据总线端口定义
#define LCDa_DATA_DDR DDRB // 数据总线方向寄存器定义

#define LCDa_FUNCTION 0x38 // 液晶模式为8位，2行，5*8字符

#define iDat 1 // 数据标志
#define iCmd 0 // 指令标志

#define LCDa_CLS 0x01	// 清屏
#define LCDa_HOME 0x02	// 地址返回原点，不改变DDRAM内容
#define LCDa_ENTRY 0x06 // 设定输入模式，光标加，屏幕不移动
#define LCDa_C2L 0x10	// 光标左移
#define LCDa_C2R 0x14	// 光标右移
#define LCDa_D2L 0x18	// 屏幕左移
#define LCDa_D2R 0x1C	// 屏幕又移

#define LCDa_ON 0x0C	 // 打开显示
#define LCDa_OFF 0x08	 // 关闭显示
#define LCDa_CURON 0x0E	 // 显示光标
#define LCDa_CURFLA 0x0F // 打开光标闪烁

/******************12864液晶常量及操作******************/
#define LCDb_CTRL PORTD	   // 12864控制端口定义
#define LCDb_CTRL_DDR DDRD // 控制端口方向寄存器定义
#define LCDb_RS PD4		   // 定义四个控制引脚
#define LCDb_RW PD5
#define LCDb_E PD6
#define LCDb_RST PD7

#define LCDb_L1 0x80 // 第一行的地址
#define LCDb_L2 0x90 // 第二行的地址
#define LCDb_L3 0x88 // 第三行的地址
#define LCDb_L4 0x98 // 第四行的地址

#define LCDb_CGRAM_ADDR 0x40 // CGRAM的开始地址
#define LCDb_CGMAX 64		 // CGRAM存储的最大字节数

#define LCDb_SET_RS LCDb_CTRL |= BIT(LCDb_RS) // 四个控制管脚的控制操作
#define LCDb_SET_RW LCDb_CTRL |= BIT(LCDb_RW)
#define LCDb_SET_E LCDb_CTRL |= BIT(LCDb_E)
#define LCDb_SET_RST LCDb_CTRL |= BIT(LCDb_RST)
#define LCDb_CLR_RS LCDb_CTRL &= ~BIT(LCDb_RS)
#define LCDb_CLR_RW LCDb_CTRL &= ~BIT(LCDb_RW)
#define LCDb_CLR_E LCDb_CTRL &= ~BIT(LCDb_E)
#define LCDb_CLR_RST LCDb_CTRL &= ~BIT(LCDb_RST)

#define LCDb_DO PORTB	   // 输出数据总线端口定义
#define LCDb_DI PINB	   // 输入数据总线端口定义
#define LCDb_DATA_DDR DDRB // 数据总线方向寄存器定义

#define LCDb_FUNCTION 0x38 // 液晶模式为8位

#define LCDb_BASCMD 0x30 // 基本指令集
#define LCDb_CLS 0x01	 // 清屏
#define LCDb_HOME 0x02	 // 地址返回原点，不改变DDRAM内容
#define LCDb_ENTRY 0x06	 // 设定输入模式，光标加，屏幕不移动
#define LCDb_C2L 0x10	 // 光标左移
#define LCDb_C2R 0x14	 // 光标右移
#define LCDb_D2L 0x18	 // 屏幕左移
#define LCDb_D2R 0x1C	 // 屏幕又移
#define LCDb_ON 0x0C	 // 打开显示
#define LCDb_OFF 0x08	 // 关闭显示

#define LCDb_EXTCMD1 0x34 // 扩充指令集，关闭绘图显示
#define LCDb_EXTCMD2 0x36 // 扩充指令集，打开绘图显示
#define LCDb_EXTCLS 0x01  // 清屏
#define LCDb_REVL1 0x04	  // 反显第1行
#define LCDb_REVL2 0x05	  // 反显第2行
#define LCDb_REVL3 0x06	  // 反显第3行
#define LCDb_REVL4 0x07	  // 反显第4行

/******************按键常量******************/
#define KEY_DDR DDRD	// 按键方向定义
#define KEY_PORTO PORTD // 按键断口输出定义
#define KEY_PORTI PIND	// 按键断口输入定义
#define OUT 0xFF		// 输出常量
#define IN 0xF0			// 输入常量

/******************按键外部中断常量******************/
#define GLOBAL 7  // 全局中断位宏定义
#define EXTINT1 7 // 外部中断1位宏定义
#define EXTINT0 6 // 外部中断0位宏定义

/******************串行DA常量******************/
#define DA_DATA PB5 // 串行数据线
#define DA_CLK PB7	// 串行时钟线
#define DA_CS PA1	// 片选线

/******************DS18B20常量******************/
#define DS18B20 PA5

/******************TWI(IIC)常量******************/
#define START 0x08		   // START信号发送完毕状态
#define MT_SLA_ACK 0x18	   // 从器件地址发送，返回ACK
#define MT_SLA_NOACK 0x20  // 从器件地址发送，但是返回NOACK
#define MT_DATA_ACK 0x28   // 数据已发送，返回ACK
#define MT_DATA_NOACK 0x30 // 数据已发送，返回NOACK

#define Start() (TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN)) // 产生START信号
#define Stop() (TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN))  // 产生STOP信号
#define Wait() while (!(TWCR & (1 << TWINT)))					   // 等待当前操作完成
#define TestACK() (TWSR & 0xF8)									   // 取出状态码
#define SetACK() (TWCR |= (1 << TWEA))							   // 产生ACK
#define Writebyte(twi_d)                   \
	{                                      \
		TWDR = (twi_d);                    \
		TWCR = (1 << TWINT) | (1 << TWEN); \
	} // 发送一个字节（twi_d为写入的数据）

/******************蜂鸣器音乐常量******************/
#define BEEP PA6
//      计时值=65536-8000000/8/2/频率
//      音名     计时值       频率Hz
#define DO_L 63627	// 262
#define DOA_L 63731 // 277
#define RE_L 63835	// 294
#define REA_L 63928 // 311
#define MI_L 64021	// 330
#define FA_L 64103	// 349
#define FAA_L 64185 // 370
#define SO_L 64270	// 392
#define SOA_L 64331 // 415
#define LA_L 64400	// 440
#define LAA_L 64463 // 466
#define TI_L 64524	// 494
#define DO 64580	// 523
#define DOA 64633	// 554
#define RE 64684	// 587
#define REA 64732	// 622
#define MI 64777	// 659
#define FA 64820	// 698
#define FAA 64860	// 740
#define SO 64898	// 784
#define SOA 64934	// 831
#define LA 64968	// 880
#define LAA 65000	// 932
#define TI 65030	// 988
#define DO_H 65058	// 1046
#define DOA_H 65085 // 1109
#define RE_H 65110	// 1175
#define REA_H 65134 // 1245
#define MI_H 65157	// 1318
#define FA_H 65178	// 1397
#define FAA_H 65198 // 1480
#define SO_H 65217	// 1568
#define SOA_H 65235 // 1661
#define LA_H 65252	// 1760
#define LAA_H 65268 // 1865
#define TI_H 65283	// 1976
#define ZERO 0		// 休止符
// 十进制:     0
// 休止符:     0

// 十进制:     1     2     3     4     5     6     7     8     9     10    11     12
// 低音  :     1     #1    2     #2    3     4     #4    5     #5    6     #6     7

// 十进制:     13    14    15    16    17    18    19    20    21    22    23     24
//  中音 :     1     #1    2     #2    3     4     #4    5     #5    6     #6     7

// 十进制:     25    26    27    28    29    30    31    32    33    34    35     36
//  高音 :     1     #1    2     #2    3     4     #4    5     #5    6     #6     7

/******************继电器常量******************/
#define RELAY PC6 // 继电器管脚宏定义

/******************异步串口常量******************/
#define MCLK 8000000 // 主时钟频率宏定义

/******************RTC常量******************/
#define RTC_CLK PB7
#define RTC_DATA PB5
#define RTC_CS PC7
// 命令
#define RD 0x01
#define WR 0x00
#define C_SEC 0x80	  // 秒
#define C_MIN 0x82	  // 分
#define C_HR 0x84	  // 时
#define C_DAY 0x86	  // 日
#define C_MTH 0x88	  // 月
#define C_WK 0x8A	  // 星期 DATE
#define C_YR 0x8C	  // 年
#define C_WP 0x8E	  // 控制(写保护)
#define C_CHARGE 0x90 // 涓流充电
#define C_BURST 0xBE  // 时钟多字节
// 配置
#define CLK_HALT 0x80  // 停止时钟控制位    SECOND	bit7
#define CLK_START 0x00 // 启动时钟
#define M12_24 0x80	   // 12/24小时值选择位 HOUR		bit7
#define PROTECT 0x80   // 写保护控制位      CONTROL	bit7
#define UPROTECT 0x00  // 写保护控制位      CONTROL	bit7
// 涓流充电控制常量
#define TC_D1R2 0xA5	 // high 1 Diode +2K Resistors
#define TC_D2R8 0xAB	 // low  2 Diodes+8K Resistors
#define TC_DISABLED 0x00 // Disabled(TCS<>1010 or DS=00 or RS=00)
// RAM 命令
#define C_RAMBASE 0xC0 // RAM0~RAM30<<1 地址需左移一位

/******************USB常量******************/
#define CSUSB PA7
#define D12_INT PD3
#define WR_N PD4
#define RD_N PD5
#define C_D PD6
#define D12_CS PD7
#define USBCTL_DDR DDRD
#define USBCTL_PORT PORTD
#define USBDAT_DDR DDRB
#define USBDAT_PORT PORTB
#define USBDAT_PIN PINB

#define CMD 0x01
#define DAT 0x00

#define UEN_GINT() SREG &= ~BIT(7)
#define EN_GINT() SREG |= BIT(7)

#define MSB(x) (((x) >> 8) & 0xFF)

#define MAX_ENDPOINTS (uchar)0x3

#define NOLAZYCLOCK 0x02
#define CLOCKRUNNING 0x04
#define INTERRUPTMODE 0x08
#define SOFTCONNECT 0x10
#define ENDP_NONISO 0x00
#define ENDP_ISOOUT 0x40
#define ENDP_ISOIN 0x80
#define ENDP_ISOIO 0xC0

#define CLOCK_12M 0x03
#define CLOCK_4M 0x0b
#define SETTOONE 0x40
#define SOFONLY 0x80

#define NORMALPLUSSOF 0x20
#define ENDP4INTENABLE 0x40
#define ENDP5INTENABLE 0x80

#define INT_ENDP0OUT 0x01
#define INT_ENDP0IN 0x02
#define INT_ENDP1OUT 0x04
#define INT_ENDP1IN 0x08
#define INT_ENDP2OUT 0x10
#define INT_ENDP2IN 0x20
#define INT_BUSRESET 0x40
#define INT_SUSPENDCHANGE 0x80

#define SETUPPACKET 0x20
#define BUFFER0FULL 0x20
#define BUFFER1FULL 0x40

#define FULLEMPTY 0x01
#define STALL 0x02

#define USB_IDLE 0
#define USB_TRANSMIT 1
#define USB_RECEIVE 2

#define MAX_CTLDAT_SIZE 8

#define USB_ENDPOINT_DIRECTION_MASK 0x80
#define USB_REQUEST_MASK (uchar)0x0F
#define USB_REQUEST_TYPE_MASK (uchar)0x60
#define USB_STANDARD_REQUEST (uchar)0x00

#define DEVICE_ADDRESS_MASK 0x7F

#define USB_FEATURE_ENDPOINT_STALL (uint)0x0000
#define USB_FEATURE_REMOTE_WAKEUP (uint)0x0001

#define EP0_PACKET_SIZE 16
#define EP1_PACKET_SIZE 16
#define EP2_PACKET_SIZE 64

#define USB_RECIPIENT (uchar)0x1F
#define USB_RECIPIENT_DEVICE (uchar)0x00
#define USB_RECIPIENT_INTERFACE (uchar)0x01
#define USB_RECIPIENT_ENDPOINT (uchar)0x02

#define USB_DEVICE_DESCRIPTOR_TYPE 0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE 0x02
#define USB_STRING_DESCRIPTOR_TYPE 0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE 0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE 0x05
#define USB_POWER_DESCRIPTOR_TYPE 0x06

/* 设备描述符: 测试设备类型 */
#define USB_CLASS_CODE_TEST_CLASS_DEVICE 0xdc
/*****   D12 配置描述符长度  ******/
#define CONFIG_DESCRIPTOR_LENGTH sizeof(USB_CONFIGURATION_DESCRIPTOR) + sizeof(USB_INTERFACE_DESCRIPTOR) + (NUM_ENDPOINTS * sizeof(USB_ENDPOINT_DESCRIPTOR))
/*****   D12 接口描述符中: 除端点0的端点索引数目  ******/
#define NUM_ENDPOINTS 4
/* 设备描述符: 测试设备类型 */
#define USB_CLASS_CODE_TEST_CLASS_DEVICE 0xdc

/* 接口描述符: 子类代码 */
#define USB_SUBCLASS_CODE_TEST_CLASS_D12 0xA0

/* 接口描述符: 协议代码 */
#define USB_PROTOCOL_CODE_TEST_CLASS_D12 0xB0
/*******************************************************
** USB 端点描述符结构体: 端点属性
********************************************************/
#define USB_ENDPOINT_TYPE_MASK 0x03

#define USB_ENDPOINT_TYPE_CONTROL 0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS 0x01
#define USB_ENDPOINT_TYPE_BULK 0x02
#define USB_ENDPOINT_TYPE_INTERRUPT 0x03

/******************通用子函数******************/
void Delayms(uint MS);

/******************LED子函数******************/
void One_led(uchar number, uchar light);
void All_led(uchar light);
void Flow_LED(uchar MS);
void Flash_LED(uchar number, uchar MS);

/******************数码管子函数******************/
void One_smg_display(uchar data, uchar number);
void All_smg_display(uchar *pdata);
void Cycle_smg_display(uchar *pdata);

/******************1602液晶管子函数******************/
void LCD1602_portini(void);
uchar LCD1602_readbyte(uchar DatCmd);
void LCD1602_sendbyte(uchar DatCmd, uchar dByte);
void LCD1602_sendstr(uchar *ptString);
void LCD1602_clear(void);
uchar LCD1602_readBF(void);
void LCD1602_gotoXY(uchar Row, uchar Col);
void LCD1602_initial(void);

/******************USB函数******************/
void D12_init(void);
void OutB(uchar cmd, uchar dat);
uchar InB(void);
void Set_addren(uchar addr, uchar enable);
void Set_EPen(uchar enable);
void Set_mode(uchar config, uchar clkdiv);
void Set_DMA(uchar bMode);
uint Read_IntR(void);
uchar Sel_EP(uchar endp);
uchar Read_EPsta(uchar endp);
uchar Read_LttransSta(uchar endp);
void Set_EPsta(uchar endp, uchar stall);
void Set_Sresume(void);
uchar Read_EP(uchar endp, uchar len, uchar *buf);
uchar Write_EP(uchar endp, uchar len, uchar *buf);
void Ack_EP(uchar endp);
void Clear_buf(uchar endp);
void Stall_ep0(void);
void S_trans(uchar *buf, uchar len);

void Ep0_rxdone(void);
void Ep0_txdone(void);
void Ep1_txdone(void);
void Ep1_rxdone(void);
void Ep2_txdone(void);
void Ep2_rxdone(void);

void Reserved(void);
void Get_status(void);
void Clr_feature(void);
void Set_feature(void);
void Set_addr(void);
void Get_descriptor(void);
void Get_config(void);
void Set_config(void);
void Get_interface(void);
void Set_interface(void);
void USB_reconnect(void);
void Control_handler(void);
void Uart_sendB(uchar sendB);
