 void init_ds1621()
{
    	  i2c_start();
		  i2c_write(0x90);
		  i2c_ack();
		  i2c_write(0xAC);
		  i2c_ack();
		  i2c_write(0x02);
		  i2c_ack();
		  i2c_start();
		  i2c_write(0x90);
		  i2c_ack();
		  i2c_write(0xA1);
		  i2c_ack();
		  i2c_write(0x28);
		  i2c_ack();
		  i2c_write(0x00);
		  i2c_ack();
		  i2c_start();
		  i2c_write(0x90);
		  i2c_ack();
		  i2c_write(0xA2);
		  i2c_ack();
		  i2c_write(0x0A);
		  i2c_ack();
		  i2c_write(0x00);
		  i2c_ack();
		  i2c_start();
		  i2c_write(0x90);
		  i2c_ack();
		  i2c_write(0xEE);
			//delay(10);
		  i2c_ack();
		  i2c_stop();

}

	