
// header files
#include<stdlib.h>
#include<conio.h>
#include<PROCESS.h>
#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
#include<alloc.h>
#include<snap.h>
#include<stdio.h>
#include<time.h>

// functions
void about();
void shape();
void color();
int changecolor(int,int);
union REGS in,out,i,o;

// mouse functions
getmouseposi(int *x,int *y,int *button)
{
 in.x.ax=3;
 int86(51,&in,&out);
 *x=out.x.cx;
 *y=out.x.dx;
 *button=out.x.bx;
 return 0;
}
int callmouse()
{
 in.x.ax=1;
 int86(51,&in,&out);
 return 1;
}
void setposi(int &xpos,int &ypos)
{
 in.x.ax=4;
 in.x.cx=xpos;
 in.x.dx=ypos;
 int86(51,&in,&out);
}
void restrictmouseptr( int x1, int y1, int x2, int y2)
{
 i.x.ax = 7;
 i.x.cx = x1;
 i.x.dx = x2;
 int86(0x33,&i,&o);
 i.x.ax = 8;
 i.x.cx = y1;
 i.x.dx = y2;
 int86(0x33,&i,&o);
}
int mousehide()
{
 in.x.ax=2;
 int86(51,&in,&out);
 return 1;
}

// image inserted
struct BMP
{
 char Type[2];           //File type. Set to "BM".
 unsigned long Size;     //Size in BYTES of the file.
 unsigned long Reserved;      //Reserved. Set to zero.
 unsigned long OffSet;   //Offset to the data.
 unsigned long headsize; //Size of rest of header. Set to 40.
 unsigned long Width;     //Width of bitmap in pixels.
 unsigned long Height;     //  Height of bitmap in pixels.
 unsigned int  Planes;    //Number of Planes. Set to 1.
 unsigned int  BitsPerPixel;       //Number of Bits per pixels.
 unsigned long Compression;   //Compression. Usually set to 0.
 unsigned long SizeImage;  //Size in bytes of the bitmap.
 unsigned long XPixelsPreMeter;     //Horizontal pixels per meter.
 unsigned long YPixelsPreMeter;     //Vertical pixels per meter.
 unsigned long ColorsUsed;   //Number of colors used.
 unsigned long ColorsImportant;  //Number of "important" colors.
};
int ShowBMP(int x, int y, char* FileName)
{
 int b,a;
 struct  BMP Obj;
 unsigned char* Datas;
 int in=0;
 unsigned char c=0;
 FILE * fp;
 fp = fopen(FileName,"rb");
 if(!fp)
 {
  printf("Error : Unable to open file ..");
  exit(0);
 }
 fread(&Obj, sizeof(Obj), 1, fp);
 if(Obj.BitsPerPixel!=4)  // This isn't a 16 color bmp we can read;
 {
  fclose(fp);
  printf("Error : File format not supported ..");
  exit(0);
 };
 fseek(fp,Obj.OffSet,SEEK_SET);
 Datas=(unsigned char*) calloc(Obj.Width/2+1, sizeof(unsigned char));
 for(b=Obj.Height;b>=0;b--)
 {
  fread(Datas, sizeof(unsigned char), Obj.Width/2, fp);
  c=0;
  in=0;
  for(a=0;a<=Obj.Width;a+=2)
  {
   c = (Datas[in] | 0x00) >>4;
   putpixel(a+x,b+y,c);
   c = (Datas[in] | 0xF0) & 0x0F;
   putpixel(a+1+x,b+y,c);
   in++;
  }
 }
 free (Datas);
 fclose(fp);
 return 1;
}

// intro
void intro()
{
 int gdriver=DETECT,gmode;
 initgraph(&gdriver,&gmode,"..\\bgi");
 int i,j;
 cleardevice();
 callmouse();
 ShowBMP(115,30,"LOGO.bmp"); /* Enter File Name Here */
 delay(1500);
 cleardevice();
 setcolor(15);
 settextstyle(10,0,3);
 for(j=0; j<=1500; j++)
 {
  delay(1);
  putpixel(random(getmaxx()),random(getmaxy()),j);
 }
 setcolor(15);
 settextstyle(1,0,7);
 outtextxy(180,50,"WELCOME");
 delay(350);
 outtextxy(300,142,"in");
 delay(350);
 setcolor(14);
 settextstyle(1,0,9);
 outtextxy(12,235,"PAINT BRUSH");
 for(i=1;i<=375;i++)
 {
  setcolor(1);
  settextstyle(1,0,7);
  outtextxy(650-i,400,"WWWWWWWWW");
  setcolor(2);
  settextstyle(1,0,7);
  outtextxy(550-i,350,"WWWWWWWWW");
 }
 setcolor(15);
 settextstyle(4,0,4);
 outtextxy(220,366,"- Developer & Programmer");
 delay(150);
 outtextxy(300,420,"ANKUSH LOKHANDE");
 delay(100);
 settextstyle(1,0,1);
 outtextxy(5,450,"Press any key to proceed...");
 getch();
 sound(3000);
 delay(50);
 nosound();
 setcolor(0);
 cleardevice();
 closegraph();
}

// notice
void notice()
{
 int i,j;
 clrscr();
 callmouse();
 gotoxy(18,13);
 textbackground(WHITE);
 textcolor(RED);
 cprintf(" In case of Mouse-Pad not working Properly, ");
 gotoxy(71,25);
 textbackground(BLACK);
 textcolor(WHITE);
 cprintf("Wait...");
 gotoxy(80,25);
 for(i=1;i<=5;i++)
 {
  delay(50);
  gotoxy(31,15);
  textbackground(WHITE);
  if(i==1)
  {
   textcolor(BLACK);
   cprintf(" ESC - Use Escape Key ");
   gotoxy(80,25);
  }
  if(i==2)
  {
   textcolor(BLUE);
   cprintf(" ESC - Use Escape Key ");
   gotoxy(80,25);
  }
  if(i==3)
  {
   textcolor(RED);
   cprintf(" ESC - Use Escape Key ");
   gotoxy(80,25);
  }
  if(i==4)
  {
   textcolor(GREEN);
   cprintf(" ESC - Use Escape Key ");
   gotoxy(80,25);
  }
  if(i==5)
  {
   textbackground(BLACK);
   textcolor(YELLOW);
   cprintf(" ESC - Use Escape Key ");
   gotoxy(80,25);
  }
 }
 textbackground(BLACK);
 textcolor(WHITE);
 delay(50);
 for(i=1;i<=6;i++)
 {
  if(i>=1 || i<=5)
  {
   gotoxy(39,25);
   textbackground(BLACK);
   textcolor(WHITE);
   cprintf("Wait, Screen initializing in progress");
  }
  if(i==6)
  {
   gotoxy(35,25);
   textbackground(BLACK);
   textcolor(WHITE);
   cprintf("                     Processing completed");
   sound(3000);
   delay(25);
   nosound();
  }
  delay(25);
  gotoxy(77,25);
  printf(".");
  delay(25);
  gotoxy(78,25);
  printf(".");
  delay(25);
  gotoxy(79,25);
  printf(".");
  delay(25);
  gotoxy(77,25);
  printf("   ");
  delay(25);
 }
 for(i=1;i<=6;i++)
 {
  if(i>=1 || i<=5)
  {
   gotoxy(40,25);
   textbackground(BLACK);
   textcolor(WHITE);
   cprintf("Wait, Mouse initializing in progress");
  }
  if(i==6)
  {
   gotoxy(35,25);
   textbackground(BLACK);
   textcolor(WHITE);
   cprintf("                     Processing completed");
   sound(3000);
   delay(25);
   nosound();
  }
  delay(25);
  gotoxy(77,25);
  printf(".");
  delay(25);
  gotoxy(78,25);
  printf(".");
  delay(25);
  gotoxy(79,25);
  printf(".");
  delay(25);
  gotoxy(77,25);
  printf("   ");
  delay(25);
 }
 for(i=1;i<=6;i++)
 {
  if(i>=1 || i<=5)
  {
   gotoxy(40,25);
   textbackground(BLACK);
   textcolor(WHITE);
   cprintf("Wait, Tools initializing in progress");
  }
  if(i==6)
  {
   gotoxy(35,25);
   textbackground(BLACK);
   textcolor(WHITE);
   cprintf("                     Processing completed");
   sound(3000);
   delay(25);
   nosound();
  }
  delay(25);
  gotoxy(77,25);
  printf(".");
  delay(25);
  gotoxy(78,25);
  printf(".");
  delay(25);
  gotoxy(79,25);
  printf(".");
  delay(25);
  gotoxy(77,25);
  printf("   ");
  delay(25);
 }
}

// shapes & structures selection tool
void shape()
{
 int i,j;
 // background screen fill
 setfillstyle(1,8);
 // background style
 bar3d(0,0,getmaxx(),getmaxy(),0,0);
 // shape naming color
 setcolor(0);
 // reset tool
 for(i=550;i<=630;i++)
  for(j=30;j<=50;j++)
   putpixel(i,j,7);
   outtextxy(558,38,"RESET");
 // clear background tool
 for(i=550;i<=630;i++)
  for(j=60;j<=80;j++)
   putpixel(i,j,7);
   outtextxy(558,68,"CLR BK");
 // eraser tool
 for(i=550;i<=630;i++)
  for(j=90;j<=110;j++)
   putpixel(i,j,7);
   outtextxy(558,98,"ERASER");
 // pencil tool
 for(i=550;i<=630;i++)
  for(j=120;j<=140;j++)
   putpixel(i,j,15);
   outtextxy(558,128,"PENCIL");
 // brush tool
 for(i=550;i<=630;i++)
  for(j=150;j<=170;j++)
   putpixel(i,j,15);
   outtextxy(558,158,"BRUSH");
 // pixel tool
 for(i=550;i<=630;i++)
  for(j=180;j<=200;j++)
   putpixel(i,j,15);
   outtextxy(558,188,"PIXEL");
 // line tool
 for(i=550;i<=630;i++)
  for(j=210;j<=230;j++)
   putpixel(i,j,15);
   outtextxy(558,218,"LINE");
 // rectangle tool
 for(i=550;i<=630;i++)
  for(j=240;j<=260;j++)
   putpixel(i,j,15);
   outtextxy(558,248,"RECT.");
 // circle tool
 for(i=550;i<=630;i++)
  for(j=270;j<=290;j++)
   putpixel(i,j,15);
   outtextxy(558,278,"CIRCLE");
 // ellipse tool
 for(i=550;i<=630;i++)
  for(j=300;j<=320;j++)
   putpixel(i,j,15);
   outtextxy(558,308,"ELLIPSE");
 // ring tool
 for(i=550;i<=630;i++)
  for(j=330;j<=350;j++)
   putpixel(i,j,15);
   outtextxy(558,338,"RING");
 // pattern tool
 for(i=550;i<=630;i++)
  for(j=360;j<=380;j++)
   putpixel(i,j,15);
   outtextxy(558,368,"PATTERN");
 // 3d bar tool
 for(i=550;i<=630;i++)
  for(j=390;j<=410;j++)
   putpixel(i,j,15);
   outtextxy(558,400,"FILL");
 // 3d bar tool name
 for(i=550;i<=630;i++)
  for(j=415;j<=425;j++)
  putpixel(i,j,7);
  outtextxy(568,417,"3D BAR");
 // 3d bar tool 'A'
 for(i=552;i<=567;i++)
  for(j=430;j<=450;j++)
   putpixel(i,j,15);
   outtextxy(557,438,"A");
 // 3d bar tool 'B'
 for(i=572;i<=587;i++)
  for(j=430;j<=450;j++)
   putpixel(i,j,15);
   outtextxy(577,438,"B");
 // 3d bar tool 'C'
 for(i=592;i<=607;i++)
  for(j=430;j<=450;j++)
   putpixel(i,j,15);
   outtextxy(597,438,"C");
 // 3d bar tool 'D'
 for(i=612;i<=627;i++)
  for(j=430;j<=450;j++)
   putpixel(i,j,15);
   outtextxy(617,438,"D");
 // 3d bar tool 'E'
 for(i=552;i<=567;i++)
  for(j=455;j<=475;j++)
   putpixel(i,j,15);
   outtextxy(557,460,"E");
 // 3d bar tool 'F'
 for(i=572;i<=587;i++)
  for(j=455;j<=475;j++)
   putpixel(i,j,15);
   outtextxy(577,460,"F");
 // 3d bar tool 'G'
 for(i=592;i<=607;i++)
  for(j=455;j<=475;j++)
   putpixel(i,j,15);
   outtextxy(597,460,"G");
 // 3d bar tool 'H'
 for(i=612;i<=627;i++)
  for(j=455;j<=475;j++)
   putpixel(i,j,15);
   outtextxy(617,460,"H");
}

// shape & structure change tool
char changeshape(int x1,int y1)
{
 // reset tool
 if((x1>550)&&(x1<630)&&(y1>30)&&(y1<50))
  return 'x';
 // clear screen tool
 if((x1>550)&&(x1<630)&&(y1>60)&&(y1<80))
  return 'o';
 //  eraser tool
 if((x1>550)&&(x1<630)&&(y1>90)&&(y1<110))
  return 'm';
 // pencil tool
 if((x1>550)&&(x1<630)&&(y1>120)&&(y1<140))
  return 'h';
 // brush tool
 if((x1>550)&&(x1<630)&&(y1>150)&&(y1<170))
  return 'y';
 // pixel tool
 if((x1>550)&&(x1<630)&&(y1>180)&&(y1<200))
  return 'z';
 // line tool
 if((x1>550)&&(x1<630)&&(y1>210)&&(y1<230))
  return 'l';
 // rectangle tool
 if((x1>550)&&(x1<630)&&(y1>240)&&(y1<260))
  return 'r';
 // circle tool
 if((x1>550)&&(x1<630)&&(y1>270)&&(y1<290))
  return 'c';
 // eclipse tool
 if((x1>550)&&(x1<630)&&(y1>300)&&(y1<320))
  return 'e';
 // ring tool
 if((x1>550)&&(x1<630)&&(y1>330)&&(y1<350))
  return 'u';
 // pattern tool
 if((x1>550)&&(x1<630)&&(y1>360)&&(y1<380))
  return 'p';
 // fill tool
 if((x1>550)&&(x1<630)&&(y1>390)&&(y1<410))
  return 'v';
 // 3dbar tool 'A'
 if((x1>552)&&(x1<567)&&(y1>430)&&(y1<450))
  return 'a';
 // 3dbar tool 'B'
 if((x1>572)&&(x1<587)&&(y1>430)&&(y1<450))
  return 'b';
 // 3dbar tool 'C'
 if((x1>592)&&(x1<607)&&(y1>430)&&(y1<450))
  return 'd';
 // 3dbar tool 'D'
 if((x1>612)&&(x1<627)&&(y1>430)&&(y1<450))
  return 'f';
 // 3dbar tool 'E'
 if((x1>552)&&(x1<567)&&(y1>455)&&(y1<475))
  return 'g';
 // 3dbar tool 'F'
 if((x1>572)&&(x1<587)&&(y1>455)&&(y1<475))
  return 'j';
 // 3dbar tool 'G'
 if((x1>592)&&(x1<607)&&(y1>455)&&(y1<475))
  return 'n';
 // 3dbar tool 'H'
 if((x1>612)&&(x1<627)&&(y1>455)&&(y1<475))
  return 's';
 else
  return 'i';
}

// coloring
void color()
{
 int i,j;
 // black
 for(i=10;i<35;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,0);
 // blue
 for(i=45;i<70;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,1);
 // green
 for(i=80;i<105;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,2);
 // cyan
 for(i=115;i<140;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,3);
 // red
 for(i=150;i<175;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,4);
 // magenta
 for(i=185;i<210;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,5);
 // brown
 for(i=220;i<245;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,6);
 // lightgray
 for(i=255;i<280;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,7);
 // lightblue
 for(i=290;i<315;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,9);
 // lightgreen
 for(i=325;i<350;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,10);
 // lightcyan
 for(i=360;i<385;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,11);
 // lightred
 for(i=395;i<420;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,12);
 // lightmagenta
 for(i=430;i<455;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,13);
 // yellow
 for(i=465;i<490;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,14);
 // white
 for(i=500;i<525;i++)
  for(j=30;j<60;j++)
   putpixel(i,j,15);
}

// change coloring (return color code)
int changecolor(int x1,int y1)
{
 int i,j;
 // black
 if((x1>10)&&(x1<35)&&(y1>30)&&(y1<60))
  return 0;
 // blue
 else if((x1>45)&&(x1<70)&&(y1>30)&&(y1<60))
  return 1;
 // green
 else if((x1>80)&&(x1<105)&&(y1>30)&&(y1<60))
  return 2;
 // cyan
 else if((x1>115)&&(x1<140)&&(y1>30)&&(y1<60))
  return 3;
 // red
 else if((x1>150)&&(x1<175)&&(y1>30)&&(y1<60))
  return 4;
 // magenta
 else if((x1>185)&&(x1<210)&&(y1>30)&&(y1<60))
  return 5;
 // brown
 else if((x1>220)&&(x1<245)&&(y1>30)&&(y1<60))
  return 6;
 // lightgray
 else if((x1>255)&&(x1<280)&&(y1>30)&&(y1<60))
  return 7;
 // lightblue
 else if((x1>290)&&(x1<315)&&(y1>30)&&(y1<60))
  return 9;
 // lightgreen
 else if((x1>325)&&(x1<350)&&(y1>30)&&(y1<60))
  return 10;
 // lightcyan
 else if((x1>360)&&(x1<385)&&(y1>30)&&(y1<60))
  return 11;
 // lightred
 else if((x1>395)&&(x1<420)&&(y1>30)&&(y1<60))
  return 12;
 // lightmagenta
 else if((x1>430)&&(x1<455)&&(y1>30)&&(y1<60))
  return 13;
 // yellow
 else if((x1>465)&&(x1<490)&&(y1>30)&&(y1<60))
  return 14;
 // white
 else if((x1>500)&&(x1<525)&&(y1>30)&&(y1<60))
  return 15;
 else return 15;
}
// exit animation
void exite()
{
 int gdriver=DETECT,gmode;
 initgraph(&gdriver,&gmode,"");
 callmouse();
 setviewport(0,0,getmaxx(),getmaxy(),1);
 settextstyle(BOLD_FONT,HORIZ_DIR,1);
 settextjustify(CENTER_TEXT,CENTER_TEXT);
 outtextxy(getmaxx()/2,getmaxy()/2,"Thanks for Visiting");
 outtextxy(getmaxx()/2,getmaxy()/2+50,"Credit : Ankush Lokhande ");
 delay(500);
 setcolor(14);
 outtextxy(getmaxx()/2,getmaxy()/2+150,"Open \"Capture folder\" on \"Desktop\" to see image of drawing/painting.");
 getch();
 clrscr();
 ShowBMP(120,40,"A1.bmp"); /* Enter File Name Here */
 delay(500);
 ShowBMP(120,40,"A2.bmp"); /* Enter File Name Here */
 delay(500);
 exit(1);
}

// main screen
int mainscreen()
{
 int i,k=0;
 textcolor(0);
 int gdriver=DETECT,gmode;
 initgraph(&gdriver,&gmode,"");
 a:
 clrscr();
 int p,q,l=15,r,s,x,y,cl,b,j,d,x1,x2,y1,y2,button=0,fz;
 char ch,f;
 shape();
 // rectangles
 setcolor(BLUE);
 rectangle(1,1,getmaxx()-1,getmaxy()-1);
 setcolor(BLUE);
 rectangle(0,0,getmaxx(),getmaxy());
 // darwing area
 setfillstyle(1,0);
 bar3d(2,70,540,460,0,0);
 setcolor(BLUE);
 rectangle(0,68,542,462);
 color();
 // header
 for(i=0;i<getmaxx()-22;i++)
  for(j=0;j<20;j++)
   putpixel(i,j,BLUE);
 for(i=getmaxx()-21;i<getmaxx();i++)
  for(j=0;j<20;j++)
   putpixel(i,j,RED);
 setcolor(15);
 outtextxy(getmaxx()-15,7,"X");
 // about us
 for(i=getmaxx()-145;i<getmaxx()-23;i++)
  for(j=0;j<20;j++)
   putpixel(i,j,1);
 outtextxy(getmaxx()-140,7,"Screen Saver ");
 setcolor(YELLOW);
 settextstyle(2,0,0);
 outtextxy(10,8,"P A ! N T   B R U S H   E D I T  R");
 setcolor(15);
 settextstyle(8,0,5);
 outtextxy(320,467,"Developer : ANKUSH LOKHANDE");
 // run time timing
 for(i=90;i<250;i++)
  for(j=463;j<475;j++)
   putpixel(i,j,8);
 time_t t;
 time(&t);
 outtextxy(8,467,ctime(&t));
 for(i=90;i<250;i++)
  for(j=463;j<475;j++)
   putpixel(i,j,8);
 outtextxy(90,467," 2020");
 setcolor(0);
 setviewport(2,71,540,458,1); //setview
 char esc;
 unsigned int size;
 void *pic;
 // default pencil tool selected for drawing
 ch='y';
 // default color is white
 setcolor(changecolor(512,50));
 callmouse();
 while(1)
 {
  callmouse();
  if(kbhit())
  {
   esc=getch();
    if(esc==27)
     exit(1);
  }
  callmouse();
  restrictmouseptr(0,0,getmaxx(),getmaxy());
  getmouseposi(&x1,&y1,&button);
  // mouse pointing
  gotoxy(58,5);
  printf("  %d,%d  ",x1,y1);
  // button pointing
  if(button>0)
  {
   // clicked
   gotoxy(68,5);
   printf("%c",127);
  }
  // show cursor point
/*
  if((x1>=0)&&(x1<=540)&&(y1>=70)&&(y1<=460))
  {
    setcolor(LIGHTGREEN);
    circle(460,2,2);
    circle(460,2,1);
    setcolor(changecolor(512,50));
    callmouse();
    getmouseposi(&x1,&y1,&button);
  }
  else
  {
   if((x1>=618)&&(x1<=638)&&(y1>=0)&&(y1<=19))
   {
    setcolor(RED);
    circle(460,2,2);
    circle(460,2,1);
    setcolor(changecolor(512,50));
    callmouse();
    getmouseposi(&x1,&y1,&button);
   }
   else
   {
    setcolor(YELLOW);
    circle(460,2,2);
    circle(460,2,1);
    setcolor(changecolor(512,50));
    callmouse();
    getmouseposi(&x1,&y1,&button);
   }
  }
*/
  // change shape
  if((x1>550)&&(x1<630)&&(y1>30)&&(y1<627)&&(button==1))
  {
   ch=changeshape(x1,y1);
   sound(5000);
   delay(50);
   nosound();
  }
  // change color
  if((x1>10)&&(x1<525)&&(y1>30)&&(y1<60)&&(button==1))
  {
   l=changecolor(x1,y1);
   setcolor(changecolor(x1,y1));
   sound(10000);
   delay(50);
   nosound();
  }
  //exit
  if(button==1)
  {
   if((x1>getmaxx()-145)&&(x1<getmaxx()-23)&&(y1>0)&&(y1<20))
   {
    sound(10000);
    delay(50);
    nosound();
    about();
   }
   if((x1>getmaxx()-21)&&(x1<getmaxx())&&(y1>0)&&(y1<20))
   {
    sound(1000);
    delay(50);
    nosound();
    setcolor(14);
    outtextxy(getmaxx()-470,1,"Saving processing, Wait!!!");
    capture("C:\\TURBOC3\\Capture\\Capture.jpg");
    capture("C:\\Users\\Lenovo\\Desktop\\Capture\\Capture.jpg");
    setfillstyle(1,0);
    bar3d(2,70,540,460,0,0);
    clearviewport();
    exite();
   }
   f=ch;
  }
  // reset screen
  if(f=='x')
  {
   ch='l';
   mainscreen();
  }
  // clr bk
  if((ch=='o')&&(button==1))
  {
   setfillstyle(1,l);
   bar3d(0,0,540,460,0,0);
   k=l;
  }
  // erasor
  if(ch=='m')
  {
   callmouse();
   while(button==1)
   {
    mousehide();
    restrictmouseptr(1,70,488,412);
    setcolor(k);
    setfillstyle(1,k);
    bar3d(x1,y1-71,x1+50,y1+71-95,0,0);
    getmouseposi(&x1,&y1,&button);
    setcolor(k);
    setfillstyle(1,k+1);
    bar3d(x1-1,y1-71,x1+49,y1+71-95,0,0);
    setcolor(k);
    setfillstyle(1,k);
    bar3d(x1-1,y1-71,x1+49,y1+71-95,0,0);
   }
  }
  // pencil
  if(f=='h')
  {
   callmouse();
   restrictmouseptr(0,0,getmaxx(),getmaxy());
   if(button==1)
   {
    while(button==1)
    {
     setcolor(l);
     mousehide();
     restrictmouseptr(3,72,537,458);
     x2=x1;
     y2=y1;
     getmouseposi(&x1,&y1,&button);
     line(x1-1,y1-71,x2-1,y2-71);
    }
   }
  }
  // brush
  if(f=='y')
  {
   if(button==1)
   {
    while(button==1)
    {
     outtextxy(getmaxx()-15,25,"X");
     restrictmouseptr(8,78,531,452);
     getmouseposi(&x2,&y2,&button);
     setcolor(l);
     mousehide();
     circle(x2-1,y2-71,5);
     circle(x2-1,y2-71,4);
     circle(x2-1,y2-71,3);
     circle(x2-1,y2-71,2);
     circle(x2-1,y2-71,1);
    }
    restrictmouseptr(8,78,531,452);
   }
  }
  // pixel
  if(f=='z')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(3,73,536,458);
     getmouseposi(&x2,&y2,&button);
     setcolor(l);
     mousehide();
     putpixel(x2-1,y2-71,l);
    }
    restrictmouseptr(3,73,536,458);
   }
  }
  // line
  if(f=='l')
  {
   if(button==1)
   {
    restrictmouseptr(0,0,getmaxx(),getmaxy());
    while(button==1)
    {
     mousehide();
     restrictmouseptr(2,72,535,457);
     getmouseposi(&x2,&y2,&button);
     setcolor(l);
     mousehide();
     line(x1-1,y1-71,x2,y2-71);
     setcolor(k);
     line(x1-1,y1-71,x2,y2-71);
    }
    setcolor(l);
    line(x1-1,y1-71,x2,y2-71);
   }
  }
  // rectangle
  if(f=='r')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(4,74,536,457);
     getmouseposi(&x2,&y2,&button);
    }
    setcolor(l);
    mousehide();
    rectangle(x1-1,y1-71,x2-1,y2-71);
   }
  }
  // circle
  if(f=='c')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(2,72,538,458);
     getmouseposi(&x2,&y2,&button);
    }
    setcolor(l);
    restrictmouseptr(2,72,540,458);
    mousehide();
    circle(x1-1,y1-71,sqrt( (pow(x2-x1,2)) + (pow(y2-y1,2))) );
   }
  }
  // ellipse
  if(f=='e')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(2,73,538,459);
     getmouseposi(&x2,&y2,&button);
    }
    setcolor(l);
    mousehide();
    ellipse(x1-1,y1-71,0,360,abs(x2-x1),abs(y2-y1));
   }
  }
  // ring
  if(f=='u')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(3,73,536,456);
     getmouseposi(&x2,&y2,&button);
     setcolor(l);
     mousehide();
     circle(x2-1,y2-71,29);
     circle(x2-1,y2-71,27);
     circle(x2-1,y2-71,25);
     circle(x2-1,y2-71,23);
     circle(x2-1,y2-71,2);
    }
    restrictmouseptr(3,73,536,456);
   }
  }
  // pattern
  if(f=='p')
  {
   if(button==1)
   {
    while(button==1)
    {
     setcolor(l);
     restrictmouseptr(2,72,538,458);
     getmouseposi(&x2,&y2,&button);
     line(x1-1,y1-71,x2-1,y2-71);
    }
   }
  }
  // fill
  if(f=='v')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(2,70,540,460);
     getmouseposi(&x2,&y2,&button);
    }
    mousehide();
    floodfill(x2-1,y2-71,WHITE);
    setcolor(l);
    setfillstyle(1,l);

   }
  }
  // 3d bar 'A'
  if(f=='a')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(3,73,537,457);
     getmouseposi(&x2,&y2,&button);
    }
    setfillstyle(1,l);
    mousehide();
    bar3d(x1-1,y1-71,x2-1,y2-71,10,10);
   }
  }
  // 3d bar 'B'
  if(f=='b')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(3,73,537,457);
     getmouseposi(&x2,&y2,&button);
    }
    setfillstyle(2,l);
    mousehide();
    bar3d(x1-1,y1-71,x2-1,y2-71,10,10);
   }
  }
  // 3d bar 'C'
  if(f=='d')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(3,73,537,457);
     getmouseposi(&x2,&y2,&button);
    }
    setfillstyle(3,l);
    mousehide();
    bar3d(x1-1,y1-71,x2-1,y2-71,10,10);
   }
  }
  // 3d bar 'D'
  if(f=='f')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(3,73,537,457);
     getmouseposi(&x2,&y2,&button);
    }
    setfillstyle(4,l);
    mousehide();
    bar3d(x1-1,y1-71,x2-1,y2-71,10,10);
   }
  }
  // 3d bar 'E'
  if(f=='g')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(3,73,537,457);
     getmouseposi(&x2,&y2,&button);
    }
    setfillstyle(7,l);
    mousehide();
    bar3d(x1-1,y1-71,x2-1,y2-71,10,10);
   }
  }
  // 3d bar 'F'
  if(f=='j')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(3,73,537,457);
     getmouseposi(&x2,&y2,&button);
    }
    setfillstyle(9,2);
    mousehide();
    bar3d(x1-1,y1-71,x2-1,y2-71,10,10);
   }
  }
  // 3d bar 'G'
  if(f=='n')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(3,73,537,457);
     getmouseposi(&x2,&y2,&button);
    }
    setfillstyle(10,l);
    mousehide();
    bar3d(x1-1,y1-71,x2-1,y2-71,10,10);
   }
  }
  // 3d bar 'H'
  if(f=='s')
  {
   if(button==1)
   {
    while(button==1)
    {
     restrictmouseptr(3,73,537,457);
     getmouseposi(&x2,&y2,&button);
    }
    setfillstyle(11,l);
    mousehide();
    bar3d(x1-1,y1-71,x2-1,y2-71,10,10);
   }
  }
 }
}

// about
void about()
{
 int driver = DETECT,mode;
 int x[10],y[10];
 int x_center = 540, y_center = 350, rad = 100;
 int i,j;
 int color;
 initgraph(&driver,&mode,"c:\\tc\\bgi");
 cleardevice();
 callmouse();
 printf("\n\n");
 printf("         ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ \r\n");
 printf("      ÜÜßÛ ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ» Û \r\n");
 printf("   ÜÜÜß  Û º               º Û \r\n");
 printf("   Û     Û º    Û      Û   º Û \r\n");
 printf("   Û     Û º               º Û \r\n");
 printf("   Û     Û º    ßÜ    Üß   º Û \r\n");
 printf("   ÛÜÜ   Û º      ßßßß     º Û \r\n");
 printf("      ÛÜ Û ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼ Û \r\n");
 printf("        ßÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ \r\n\n\n");
 printf("Thankyou for work with me... - Ankush Lokhande\r\nTaking a break can lead to breakthroughs, Take a rest man.");
 outtextxy(280,460,"Press any key for back to the work...");
 while(!kbhit())
 {
  color=rand()%16;
  if(color==0)
   continue;
  setcolor(color);
  for ( i = 0; i < 10; i++ )
  {
   x[i] =  x_center + rad *  cos(36*i*3.14159/180);
   y[i] =  y_center + rad *  sin(36*i*3.14159/180);
  }
  for ( i = 0; i < 10; i++ )
   for ( j = 0; j < 10; j++ )
    line(x[i],y[i],x[j],y[j]);
    //delay(100);
 }
 getch();
 closegraph();
 mainscreen();
}

//main function
int main()
{
 intro();
 notice();
 mainscreen();
 return 0;
}

// Guidelines:
// 'k' stores the value of background color and
// 'l' stores the value of selected color of shapes
// hit 'esc' to exit
// drawing area --> rectangle(0,70,540,460);
// ch=changeshape(x1,y1);
// setfillstyle(int pattern, int color);
// bar3d(int left, int top, int right, int bottom, int depth, int topflag);
// putpixel(int x, int y, int color);
// outtextxy(int x, int y, char*string);
// setviewport(int left, int top, int right, int bottom, int clip);