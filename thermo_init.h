     
 


   void all_init()
	  {
              lcd_init();
	          uart_init();
	          rtc_init();
			  init_ds1621();
			  uart_string("\r\t*********REAL TIME WEATHER MONITORING SYSTEM**********\r\n");
 	          uart_string("______________________________________________________________\n");
	          uart_string("\rSR.NO.\t TIME\t      DATE\t  LIGHT\t    TEMP\r\n");
	          uart_string("--------------------------------------------------------------\r\n");
              IE=0x81;
	          IT0=1;
	  }