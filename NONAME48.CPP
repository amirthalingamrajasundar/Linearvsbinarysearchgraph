#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>



#if !defined( __TIMER_H )
#include <Timer.h>
#endif  // __TIMER_H

#if !defined( __DOS_H )
#include <Dos.h>
#endif  // __DOS_H

const unsigned long far * const dosTime =
    (const unsigned long far * const)MK_FP( 0x40, 0x6C );

unsigned Timer::adjust = calibrate();

Timer::Timer() : time_(0), running(0)
{
}

void Timer::start()
{
    if( !running )
	{
	outportb( 0x43, 0x34 );
	asm jmp __1;
    __1:
	outportb( 0x40, 0 );
	asm jmp __2;
    __2:
	outportb( 0x40, 0 );
	startTime.dosCount = *dosTime;
	startTime.timerCount = 0;
	running = 1;
	}
}

void Timer::stop()
{
    outportb( 0x43, 0 );
    unsigned char temp = inportb( 0x40 );

    TIME stopTime;
    stopTime.timerCount = (inportb( 0x40 ) << 8) + temp;
    stopTime.dosCount = *dosTime;

    TIME elapsedTime;
    elapsedTime.dosCount = stopTime.dosCount - startTime.dosCount;
    elapsedTime.timerCount = -( stopTime.timerCount - adjust );

    const double fudge = 83810.0/100000.0;
    time_ += ((elapsedTime.dosCount << 16) + elapsedTime.timerCount)*fudge;

    running = 0;

}

void Timer::reset()
{
    time_ = 0;
    if( running )
	start();
}

unsigned Timer::calibrate()
{
    adjust = 0;
    unsigned long sum = 0;
    Timer w;
    for( int i = 0; i < 100; i++ )
	{
	w.start();
	w.stop();
	sum += w.time();
	w.reset();
	}
    return (unsigned)((sum+5)/100);
}

#if defined( TEST_TIMER )
#include <iostream.h>
#include <stdio.h>

int main( void )
{
    delay( 0 );
    cout << "Resolution: " << Timer::resolution() << endl;
    Timer w;
    for( unsigned del = 0; del < 10; del++ )
	{
	unsigned d1 = del*100;
	w.start();
	delay( d1 );
	w.stop();
	printf( "%4u ms., actual time = %6f seconds.\n", d1, w.time() );
	w.reset();
	}
    return 0;
}
#endif /* TEST_TIMER */



Timer t;
int bubblesort(long int *a,long int n){
for(long int i=0;i<n-1;i++){
for(long int j=i+1;j<n;j++){
if(a[i]>a[j]){
int temp=a[i];
a[i]=a[j];
a[j]=temp;
}
}
}
return 1;
}
int linearsearch(long int *a,long int n,long int key){
for(long int i=0;i<n;i++){
if(a[i]==key){
return 1;
}
}
return 0;
}
int binarysearch(long int *a,long int n,long int key){
long int p=0;
long int r=n;
long int q;
while(p<=r){
q=(p+r)/2;
if(a[q]>key){
r=q-1;
}else if(a[q]<key){
p=q+1;
}else{
return 1;
}
}
return 0;
}

int binarysearch(long int *a,long int p,long int r,long int key){

if(p==r){
if(a[p]!=key){
return 0;
}
}
long int q=(p+r)/2;

if(a[q]>key){
binarysearch(&a[0],p,q-1,key);
}else if(a[q]<key){
binarysearch(&a[0],q+1,r,key);
}else{
return 1;
}
}


void main(){
clrscr();



long int arr[10000];
long int n=100;


long int key;
cin>>key;

int gdriver = DETECT, gmode, errorcode;
initgraph(&gdriver, &gmode, "");
errorcode = graphresult();
if (errorcode != grOk)
{
   getch();
   exit(1);
}

for(int i=0;i<=700;i++){
if((440-i)%20==0){
char *c;
sprintf(c,"%d",440-i);
outtextxy(10,i,c);
}
if(i%20==0){
char *c;
sprintf(c,"%d",(i/2)*4);
outtextxy(i,450,c);
}
putpixel(i,440,15);
putpixel(20,i,15);
}
settextstyle(1,1,1);
outtextxy(0,200,"time in micro seconds");

settextstyle(0,0,0);
outtextxy(50,450,"input size");

long int prevx=0,prevy=0;
long int prevx1=0,prevy1=0,prevy2=0;
long int prevx2=0;
for(long int x=1;x<=n;x++){
for(long int i=0;i<x;i++){
arr[i]=random(32768);
}
t.start();
linearsearch(&arr[0],x,key);
t.stop();
long int x1=x/2;
long int y1=10000000 * t.time();
setcolor(13);
line(prevx+20,440-prevy,x1+20,440-y1);
setcolor(15);
prevx=x1;
prevy=y1;
putpixel(x1+20,440-y1,15);

t.reset();


bubblesort(&arr[0],x);
t.start();
if(binarysearch(&arr[0],x,key)){
//cout<<"the number is found";
}else{
//cout<<"the number is not found";
}
t.stop();
x1=x/2;
y1=10000000 * t.time();
setcolor(2);
line(prevx1+20,440-prevy1,x1+20,440-y1);
setcolor(15);
prevx1=x1;
prevy1=y1;
t.reset();

bubblesort(&arr[0],x);
t.start();
if(binarysearch(&arr[0],0,x,key)){
//cout<<"the number is found";
}else{
//cout<<"the number is not found";
}
t.stop();
x1=x/2;
y1=10000000 * t.time();
setcolor(5);
line(prevx2+20,440-prevy2,x1+20,440-y1);
setcolor(15);
prevx2=x1;
prevy2=y1;

t.reset();
}

getch();
}







