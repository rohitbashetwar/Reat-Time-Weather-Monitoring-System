
    unsigned char temp,t;	
          void rtc_init()
		  {
		   i2c_device_write(0xd0,0x2,0x51);
           i2c_device_write(0xd0,0x1,0x59);
           i2c_device_write(0xd0,0x0,0x40);
	       i2c_device_write(0xd0,0x4,0x31);
           i2c_device_write(0xd0,0x5,0x23);
           i2c_device_write(0xd0,0x6,0x2018);
		  }


         void rtc_read()
		 {
			 lcd_cmd(0x1);
            temp=i2c_device_read(0xd0,0x2);
			   t=temp&(0x1f);
			   lcd_cmd(0x80);
			   uart_tx(count/10+48);
			   uart_tx(count%10+48);
			   uart_string(")    ");
			   i2c_string_write(")    ");
			   lcd_string("TIME:");
			   lcd_data(t/16+48);
			   lcd_data(t%16+48);
			   i2c_word_write(t/16+48);
			   i2c_word_write(t%16+48);
			   i2c_word_write(':');
			   lcd_data(':');
			   uart_tx(t/16+48);
			   uart_tx(t%16+48);
			   uart_tx(':');


		 temp=i2c_device_read(0xd0,0x1);
			   lcd_data(temp/16+48);
			   lcd_data(temp%16+48);
			   lcd_data(':');
			   i2c_word_write(temp/16+48);
			   i2c_word_write(temp%16+48);
			   i2c_word_write(':');
			   uart_tx(temp/16+48);
			   uart_tx(temp%16+48);
			   uart_tx(':');


		 temp=i2c_device_read(0xd0,0x0);
			   lcd_data(temp/16+48);
			   lcd_data(temp%16+48);
			   i2c_word_write(temp/16+48);
			   i2c_word_write(temp%16+48);
			   uart_tx(temp/16+48);
			   uart_tx(temp%16+48);
		
			   i2c_string_write("\t    ");
			   uart_string("\t    ");
		   //for setting date
			   lcd_cmd(0xc0);
			   lcd_string("DATE:");
		 temp=i2c_device_read(0xd0,0x4);
			   lcd_data(temp/16+48);
			   lcd_data(temp%16+48);
			   lcd_data('/');
			   i2c_word_write(temp/16+48);
			   i2c_word_write(temp%16+48);
			   i2c_word_write('/');
			   uart_tx(temp/16+48);
			   uart_tx(temp%16+48);
			   uart_tx('/');


		 temp=i2c_device_read(0xd0,0x5);
			   lcd_data(temp/16+48);
			   lcd_data(temp%16+48);
			   lcd_data('/');
		       i2c_word_write(temp/16+48);
			   i2c_word_write(temp%16+48);
			   i2c_word_write('/');
			   uart_tx(temp/16+48);
			   uart_tx(temp%16+48);
			   uart_tx('/');


	     temp=i2c_device_read(0xd0,0x6);
			   lcd_data(temp/16+48);
			   lcd_data(temp%16+48);
			   i2c_word_write(temp/16+48);
			   i2c_word_write(temp%16+48);
			   i2c_string_write("\t  ");
			   uart_tx(temp/16+48);
			   uart_tx(temp%16+48);
			   uart_string("\t  ");
		 }
		
		 
	   void ldr_read()
        {
		    unsigned int tp;
			float v;
			lcd_cmd(0x1);
			lcd_string("Light Intensity...");
			lcd_cmd(0xc0);
			     tp=read_adc(1,0);
			     v=((4095.0-tp)/4095.0)*100.0;
					lcd_float(v);
					lcd_data('%');
					uart_float(v);
					uart_tx('%');
					i2c_string_write("% \t");
			     uart_string(" \t");
		}
		/* For setting time*/ 
		
		 
void ds1621_read()
{
	  unsigned char ch,cnt,slp;
	  float temp;
    ch=i2c_device_read(0x90,0xAA);
    cnt=i2c_device_read(0x90,0xA8);
	slp=i2c_device_read(0x90,0xA9);
	temp= (ch-0.25)+((slp-cnt)/slp);
	lcd_string("Temperature");
	lcd_cmd(0xc0);
	lcd_float(temp);
	lcd_string(" c");
	uart_float(temp);
	uart_string(" c\r\n");
	i2c_string_write(" c\r\n");
	delay(1000);
	lcd_cmd(0x1);

}

        void log_read()
		{
		    unsigned char temp,mr=0xA0,j;
		    int t=m-1,i;
			  uart_string("\x1b[2J");
 			//  uart_string("\r\t*********REAL TIME WEATHER MONITORING SYSTEM**********\r\n");
  	          uart_string("____________________________LAST ENTRIES____________________________\n\n");
 	          uart_string("\rSR.NO.\t TIME\t      DATE\t  LIGHT\t    TEMP\r\n");
 	          uart_string("--------------------------------------------------------------\r\n");
			  for(i=0,j=0;i<=t;i++,j++)
			  {
				
			    temp=i2c_device_read(mr,0x0+j);
				  uart_tx(temp);
						if(j==255)
						   mr|=0x02;
							 
			  }
		}


		void ext_interrupt(void)interrupt 0
		{
			   
			   if(count==10)
				 {
					 m=0;
					 count=0;
			         uart_string("\x1b[2J");
			         uart_string("\r\t*********REAL TIME WEATHER MONITORING SYSTEM**********\r\n");
 	                 uart_string("______________________________________________________________\n");
	                 uart_string("\rSR.NO.\t TIME\t      DATE\t  LIGHT\t    TEMP\r\n");
	                 uart_string("--------------------------------------------------------------\r\n");
				 }
			  count++;
			  i2c_word_write(count/10+48);
			  i2c_word_write(count%10+48);
			  rtc_read();
		      delay(1000);
			  ldr_read();
			  delay(1000);
			  lcd_cmd(0x1);
			  ds1621_read();
		}		
  