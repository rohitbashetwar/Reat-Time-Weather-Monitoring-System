sbit rs=P3^4;
sbit rw=P3^5;
sbit en=P3^6;
sbit clk=P1^0;
sbit dout=P1^1;
sbit din=P1^2;
sbit cs=P1^3;
sbit sw=P3^7;
sfr lcd=0x80;
unsigned int count=0,n,m=0,m1=0;
unsigned char mr=0xA0;
void delay(unsigned int ms)
{
     unsigned char i;
	 for(;ms>0;ms--)
	 {
	 for(i=250;i>0;i--);
	 for(i=247;i>0;i--);
	 }
}

void lcd_data(unsigned char dta)
{
    lcd=dta;
	  rs=1;
    rw=0;
	  en=1;
	  delay(2);
	  en=0;
}

void lcd_cmd(unsigned char cmd)
{
   lcd=cmd;
   rs=0;
   rw=0;
   en=1;
   delay(2);
   en=0;
}
void lcd_string(char *s)
{
  while(*s)
  {
     lcd_data(*s++);
  }
}
void lcd_init(void)
{
    lcd_cmd(0x2);
	lcd_cmd(0x38);
	lcd_cmd(0xe);
	lcd_cmd(0x6);
	lcd_cmd(0x1);
}

void lcd_integer(unsigned int n)
{
      unsigned char p[8],t;
    int i=0, c=0;
		if(n<0)
	{
		lcd_data('-');
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
	lcd_data(p[i]);
	}
	
}

void lcd_float(float n)
{
    
	int i,c=0;
	i=n;
	lcd_integer(i);
	lcd_data('.');
	i=(n-i)*100;
	lcd_integer(i); 
} 
