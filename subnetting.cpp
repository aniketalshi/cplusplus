//code for simple subnetting http://ideone.com/TOWO1

#include <stdio.h>
#include <iostream>
#include <math.h>
 
class subnetting {
 
char class1;
int minsub;
int maxhost;
 
public:
void assign(char a,int b,int c);
void calculate();
void print(int,int);
};
 
int pow1(int a, int b)
{int sum=0;
 int i=7;
  while(b>0)
 { 
  sum=sum+pow(a,i);
  i--;
  b--;
 }
 return sum;
}



void subnetting::assign(char a,int b,int c){
class1 = a;
minsub=b;
maxhost=c;
}
 
void subnetting::calculate(){
 
int availbits;
int count=1;
int sum=2;
int netbits=0;
int value=1;
 
if(class1=='A')
 availbits=24;
else if(class1=='B')
 availbits=16;
else if(class1=='C')
 availbits=8;
 
while(sum<maxhost)
{
 sum=sum*2;
 count++; 
}
 
//value of count is hostbits
 
netbits=availbits-count;
 

printf("class %c, min subnets %d,max host %d \n",class1,minsub,maxhost);
//printf("%d %d\n",netbits,count);
print(netbits,count); 

 
}
 
void subnetting::print(int netbits,int host){
//printf("%c, %d, %d",class1,minsub,maxhost);

int one,two,three,four;

if(class1=='C')
{
 one=255;
 two=255;
 three=255;
 four=pow1(2,netbits);
}else if(class1=='B')
{
 one=255;
 two=255;
  if(netbits>8)
   {three=255;
   four=pow1(2,netbits-8);
  }else
 { three=pow1(2,netbits);
   four=0;
 }
}else if(class1=='A')
{
one=255;
 if(netbits>16)
 {
   two=255;
   three=255;
   four=pow1(2,netbits-16);
 }else if(netbits>8 && netbits<16){
   two=255;
   three=pow1(2,netbits-8);
   four=0;
  }
 else if(netbits<8)
 {
  two=pow1(2,netbits);
  three=0;
  four=0;  

 }
}

 printf("%d . %d . %d . %d\n",one,two,three,four);

}
 
 
 
 
int main()
{
//inputformat- obj.assign(class of ip add,min no of subnets, max no of hosts) 


subnetting s1,s2,s3;
s1.assign('A',200,300);
s1.calculate();
s2.assign('B',300,50);
s2.calculate();
s3.assign('C',30,10);
s3.calculate();

return 0;
}

