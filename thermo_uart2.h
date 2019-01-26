void uart_init()
{
     SCON=0X50;
  	 TMOD=0X20;
     TH1=253;
	   TR1=1;
}

void uart_tx(unsigned char ch)
{
    SBUF=ch;
	while(TI==0);
	TI=0;
}


void uart_string(char *s)
{
	  while(*s)
			uart_tx(*s++);
}

void uart_integer(unsigned int n)
{
      unsigned char p[5],t;
    int i=0, c=0;
		if(n<0)
	{
		uart_tx('-');
		n=-n;
	}
	for(;n;n=n/10,i++)
	{
	t=n%10+48;
	p[i]=t;
		c++;
	}
	
	for(i=c-1;i>=0;i--)
	{
	 uart_tx(p[i]);
	 i2c_word_write(p[i]);
	}
	
}

void uart_float(float n)
{
    
 	int i,c=0;
	i=n;
	uart_integer(i);
    i2c_word_write('.');
	uart_tx('.');
	i=(n-i)*100;
	uart_integer(i); 
} 
