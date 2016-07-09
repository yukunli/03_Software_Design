
#include "DS18B20.h"
/********************************
 * CODE
 */
 
inline void TEM_18B20_IOinit(void)
{
	EALLOW;
	GpioCtrlRegs.GPBMUX2.bit.TEM_IO=0;
	GpioCtrlRegs.GPBDIR.bit.TEM_IO=0;
	EDIS;
}
//******************复位DS18B20函数*****************************
//主控制器（dsPIC30F6014A）先拉低总线480us，然后释放总线回到高电平
//18B20检测到上升沿后先等待15-60us，然后拉低总线做为复位的应答信号
//主控制器释放总线后到复位结束时间应为480US
char reset(void)
{
    char presence;
    DQ_LOW();                                //主机拉至低电平                            
    DELAY_US(480);        					//以上5条共延时480us
    DQ_HIGH();                                //释放总线等电阻拉高总线,并保持15~60us
    DELAY_US(44);                                 
    if(DQ ==0 ) 
    {
    	presence = 1;           //接收到应答信号 
    }         
    else 
    {
    	presence = 0;             //没有接收到应答信号，继续复位
    }
    DELAY_US(210);                                 
    DQ_HIGH(); 
	return presence;
  }
//****************写18b20写字节函数*****************************
//主控制器写数据1：先把总线拉低，然后在15us内释放总线
//主控制器写数据0：把总线拉低至少60us
//写一位数据至少需要60us
//两位数据之间至少延时1us
void write_byte(unsigned char val)
{
 unsigned char  i = 0;
 unsigned char  temp = 0;
 DQ_HIGH(); 
 DELAY_US(2); 
 for(i=8;i>0;i--)
 {
   temp = val & 0x01;                            //最低位移出
   DQ_LOW(); 
   DELAY_US(8);                                 //保持拉低5us
   if(temp == 1)
   {
		DQ_HIGH();                   //如果写1,拉高电平
   }
   DELAY_US(60);                                //延时60us
   DQ_HIGH(); 
   DELAY_US(3);                    //在两位之间插入3us延时
   val = val>>1;                               //右移一位
  }
}
//****************18b20读字节函数********************************
//主控制器把总线拉低至少1US，然后释放
//主控制器读数据1：18B20保持总线状态不变
//主控制器读数据0：18B20检测到总线拉低后继续拉低总线至少60ms
//主控制器在拉低总线后的15us读取总线上的状态
//读取1位数据至少需要60us
unsigned char read_byte()
{
	 unsigned char  i = 0;
	 unsigned char value = 0;                                //读出温度
	 DQ_HIGH();     
	 DELAY_US(2);
	 for(i = 8;i > 0; i--)
	 {
	   value >>= 1; 
	   DQ_LOW();
	   DELAY_US(3);                                     //保持总线拉低3us
	   DQ_HIGH();                               //拉至高电平
	   DELAY_US(7);                                //释放总线后保持7us再读取数据
	   if(DQ)
	   {
	   	  value |= 0x80;
	   }
	   DELAY_US(60);                               //延时50us，保证每1位的60us延时
	  }
	  return(value);
}

void TEM_Getinit(void)
{
	TEM_18B20_IOinit();
}
//-------------------------------------------------
//启动温度转换函数
float  get_temp(void)
{ 
	char state = 0;
	char i = 0;
	unsigned char  TLV = 22;   //采集到的温度高8位
	unsigned char  THV = 22;   //采集到的温度低8位
	float temp = 0;

	for(i = 0; i <= 5; i++)
	{
		state = reset();    //复位等待从机应答,if run 5 times,it means the  reset failed
		if(state == 1)
			break;
		else if(i == 5)
			return temp = 55.55;     
	} 
	DELAY_US(20); 
	write_byte(0XCC);                        //忽略ROM匹配 
	write_byte(0X44);                        //发送温度转化命令  

	DELAY_US(400000);                         //确保温度转换完成所需要的时间
	DELAY_US(400000);                             
	for(i = 0;i<= 5; i++)		//再次复位，等待从机应答 
	{
		state = reset();    //复位等待从机应答,if run 5 times,it means the  reset failed
		if(state == 1)
			break;
		else if(i == 5)
			return temp = 44.44;     
	}
	DELAY_US(20);
	write_byte(0XCC);                        //忽略ROM匹配 
	write_byte(0XBE);                        //发送读温度命令
	 
	TLV=read_byte();                         //读出温度低8 
	THV=read_byte();                         //读出温度高8位 
	DQ_HIGH();                               //释放总线
	temp=((THV*256)+TLV)*0.0625;       
	return(temp);							//返回真实温度值
}
 
  
//**********************
