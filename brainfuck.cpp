//http://ideone.com/mF124
#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include <vector>
#include <ctype.h>
#define SIZE 40000

using namespace std;

class Brainfuck{

	int cells[SIZE];
	vector <char> data;
	vector<int>pos;
	int currptr;
	int dataptr;
	int loopCount;
	int stoppos;
	
	public:
	Brainfuck(){
	for(int i=0;i<SIZE;i++){
	cells[i]=0;
	}
	currptr=0;
	dataptr=0;
	loopCount=0;
	stoppos=0;
	}
	
	void parseInput(string s);
	void checkSyntax();
	void print();
	void exec();
	void incr();
	void getInput();
	void getOutput();
	void nxtCell();
	void prvCell();
	void decr();
	void startLoop();
	void stopLoop();
	
};


void Brainfuck::parseInput(string s){
	int flag=0;
	
	for(int i=0;i<s.length();i++){
		if(s[i]=='+' || s[i]=='-' || s[i]=='>' || s[i]=='<' || s[i]==',' || s[i]=='.' || s[i]=='[' || s[i]==']'){
		data.push_back(s[i]);
		}else{
		printf("\n %c is unrecognized character ",s[i]);
		flag=1;
		break ;
		}
	
	}

	if(flag==0){
	checkSyntax();
	}
}

void Brainfuck::checkSyntax(){

	int count=0;
	vector<char>::iterator it;
	for(it=data.begin();it!=data.end();++it){
	
		if((*it)=='[')
		 count++;
		else if((*it)==']')
		 count--;
		 
	}
	
	if(count==0){
	//print();
	exec();
	}else{
		printf("Loop mismatched");
	}
}

void Brainfuck::print(){
		cout<<endl;
		vector<char>::iterator it;
	for(it=data.begin();it!=data.end();++it){
	cout<<*it;
	}
}

void Brainfuck::exec(){
char curr;

//vector<char>::iterator it;

	//for(it=data.begin();it!=data.end();it++){
	
	while(dataptr!=(int)data.size()){
	
	curr=data[dataptr];
	//cout<<endl<<curr<<endl;
	if(curr==','){
		getInput();
		dataptr++;
	}else if(curr=='.'){
		getOutput();
		dataptr++;
	}else if(curr=='+'){
		incr();
		dataptr++;
	}else if(curr=='>'){
		nxtCell();
		dataptr++;
	}else if(curr=='<'){
		prvCell();
		dataptr++;
	}else if(curr=='-'){
		decr();
		dataptr++;
	}else if(curr=='['){
		startLoop();
	}else if(curr==']'){
		stopLoop();
	}


		

}

}
void Brainfuck::getInput(){

char c;
cin>>c;

cells[currptr]=toascii(c);

}

void Brainfuck::getOutput(){

printf("%c",cells[currptr]);

}

void Brainfuck::incr(){
cells[currptr]++;

}

void Brainfuck::nxtCell(){
currptr=currptr+1;
}

void Brainfuck::prvCell(){
currptr=currptr-1;

}
void Brainfuck::decr(){
cells[currptr]--;
}

void Brainfuck::startLoop(){

loopCount++;

if(loopCount==100000){
printf("Maximum loop count exceeded");
dataptr=(int)data.size();
}
if(cells[currptr]!=0){

pos.push_back(dataptr);
dataptr++;
}else{

dataptr=stoppos;
  
  dataptr++;

}



}

void Brainfuck::stopLoop(){
stoppos=dataptr;
dataptr=pos.back();
//cout<<endl<<"dataptr"<<dataptr;
pos.pop_back();
}

int main(){

Brainfuck bf1;
Brainfuck bf2;
//bf.parseInput("++++++++++[->+++++<]>.");
bf1.parseInput("++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++<<+++++++++++++++.>.+++.------.--------.>+.>.");
bf2.parseInput("+++++[->+++++[->++++<]<]>>.");


return 0;

}