   sbit SDA=P2^0;
	 sbit SCL=P2^1;
	 void i2c_start()
	 {
	    SCL=1;
		SDA=1;
		SDA=0;
	 }

	 void i2c_stop()
	 {
	    SCL=0;
		SDA=0;
		SCL=1;
		SDA=1;
	 }

	 void i2c_write(unsigned char dta)
	 {
	     signed char i;
		 for(i=7;i>=0;i--)
		 {
		     SCL=0;
			 SDA=(dta&(1<<i))?1:0;
			 SCL=1;
		 }
	 }

     unsigned char i2c_read()
	 {
	     unsigned char temp=0;
		 signed char i;
		 for(i=7;i>=0;i--)
		 {
		     SCL=1;
			 if(SDA==1)
			 temp|=1<<i;
			 SCL=0;
		 }
		 return temp;
	 }

	void i2c_ack()
	{
	   SCL=0;
	   SDA=1;
	   SCL=1;
	   while(SDA==1);
	   SCL=0;
	}

	void i2c_noack()
	{
	   SCL=0; 
	   SDA=1;
	   SCL=1;
	}
	
	 void i2c_device_write(unsigned char sa,unsigned char mr,unsigned char dta)
 {
      i2c_start();
	  i2c_write(sa);
	  i2c_ack();
	  i2c_write(mr);
	  i2c_ack();
	  i2c_write(dta);
	  i2c_ack();
	  i2c_stop();
	  delay(10);
 }

 unsigned char i2c_device_read(unsigned char sa,unsigned char mr)
 {
    unsigned char temp;
	i2c_start();
	i2c_write(sa);
	i2c_ack();
	i2c_write(mr);
	i2c_ack();
	i2c_start();
	i2c_write(sa|1);
	i2c_ack();
	temp=i2c_read();
	i2c_noack();
	i2c_stop();
	return temp;
 }
 
 void i2c_word_write(char ch)
  {
		  if(m==255)
				mr|=0x02;
		  i2c_device_write(mr,0x0+m++,ch);
	}

 void i2c_string_write(char *s)
 {
     while(*s++)
		 {    
			   if(m==255)
					 mr+=0x02;
      	 i2c_device_write(mr,0x0+m++,*s);
		 }
 }


 unsigned int read_adc(bit d1,bit d0)
{
	   unsigned int temp=0x0;
	   signed char i;
	   cs=0;
	   clk=0;din=1;clk=1;
	   clk=0;din=1;clk=1;
	   clk=0;din=1;clk=1;
	//selecting adc channel
	   clk=0;din=d1;clk=1;
	   clk=0;din=d0;clk=1;
	   clk=0;din=1;clk=1;
	   clk=0;din=1;clk=1;
	   for(i=11;i>=0;i--)
	   {
			    clk=0;
			    if(dout==1)
						 temp|=1<<i;
					clk=1;
		 }
		 cs=1;
		 return temp;
}
