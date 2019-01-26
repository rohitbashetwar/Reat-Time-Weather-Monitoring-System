#include<reg51.h>
#include "thermo_lcd.h"
#include "thermo_i2c.h"
#include "thermo_uart2.h"
#include "ds1621.h"
#include "thermo_rtc.h"
#include "thermo_init.h"

void main()
{
	  all_init();
	  lcd_cmd(0x80);
	  lcd_string("hello");
	while(1)
	  {
			 lcd_cmd(0x80);
	         lcd_string("WEATHER MONITOR");
			 if(sw==0)
			     log_read();
		}	  
}