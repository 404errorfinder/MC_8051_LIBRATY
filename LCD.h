void Lcd_Setup();
void Lcd_Delay(int a);
void Insert_Dataline(char a);
void Insert_Cmd(char a);
void Insert_Char(char a);
void Insert_String(char *a);
void Insert_Num(unsigned int i) ;
void Lcd_Clear();
void Set_Cursor(char a, char b);
void Shift_Right(int a,int b);
void Shift_Left(int a, int b);

extern bit RS;                                                                   
extern bit EN;                           
extern bit D0;
extern bit D1;
extern bit D2;
extern bit D3;
extern bit D4;
extern bit D5;
extern bit D6;
extern bit D7;

// LCD initialisation:
void Lcd_Setup()
{
	Insert_Dataline(0x00);  //clearing dataline
	RS = 0;
	Lcd_Delay(200);
	Insert_Cmd(0x38);  			// 8-Bit mode 2 line,5x7 pixel
	Insert_Cmd(0x0C);				// Display ON,Cursor OFF
	Insert_Cmd(0x80);				// Force cursor to 1st row
	Insert_Cmd(0x01);				// Clear display
	Insert_Cmd(0x06);				// Entry mode
}


// DELAY FUNCTION:
void Lcd_Delay(int a)
{
    int j;
    int i;
    for(i=0;i<a;i++)
    {
        for(j=0;j<125;j++)
        {
        }
    }
}

// 8-Bit Data Line Porting or sending ASCII value:
void Insert_Dataline(char a)
{
	if(a & 1)
		D0 = 1;
	else 
		D0 = 0;
	
	if(a & 2)
		D1 = 1;
	else
		D1 = 0;
	
	if(a & 4)
		D2 = 1;
	else
		D2 = 0;
	
	if(a & 8)
		D3 = 1;
	else
		D3 = 0;
	
	if(a & 16)
		D4 = 1;
	else
		D4 = 0;

	if(a & 32)
		D5 = 1;
	else
		D5 = 0;
	
	if(a & 64)
		D6 = 1;
	else 
		D6 = 0;
	
	if(a & 128)
		D7 = 1;
	else
		D7 = 0;
}

// Inserting LCD commamds:
void Insert_Cmd(char a)
{ 
  RS = 0;            
  Insert_Dataline(a);          
  EN  = 1;            
  Lcd_Delay(5);
  EN  = 0;             
}
// Clearing LCD:
void Lcd_Clear()
{
	  Insert_Cmd(1);
}
// Setting cursor position:
void Set_Cursor(char a, char b)
{
	if(a == 1)
	  Insert_Cmd(0x80 + b);
	else if(a == 2)
		Insert_Cmd(0xC0 + b);
}
// Writting charater:
void Insert_Char(char a)
{
   RS = 1;             
   Insert_Dataline(a);             
   EN  = 1;             
   Lcd_Delay(5);
   EN  = 0;             
}

// Writing String:
void Insert_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	 Insert_Char(a[i]);
}

// Writing Number:
void Insert_Num(unsigned int i)     
{   
	int p;
	int k=0;
	int num[10];
	int c;
	while(i>0)
	{
		num[k]=i%10;
		i=i/10;
		k++;
	}
	k--;
	for (p=k;p>=0;p--)
	{
		c=num[p] + 48;
		RS = 1;
		Insert_Dataline(c);
		EN = 1;
		Lcd_Delay(1);
		EN = 0;
	}
}

void Shift_Right(int a,int b)
{
	int i;
	for(i=0;i<a;i++)
	{
		Insert_Cmd(0x1C);
		Lcd_Delay(b);
	}
}

void Shift_Left(int a, int b)
{
	int i;
	for(i=0;i<a;i++)
	{
		Insert_Cmd(0x18);
		Lcd_Delay(b);
	}
}