/* Program generates random Strings 
** Length of strings - LEN
** Number of strings to generate TOTAL
** 
*/
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#include<time.h>
#define TOTAL 100
#define LEN 5
using namespace std;

int main(){
	int i, no, pos;
	std::string final, temp;
	ofstream fp ("output.txt");
	char str[] = "ATGC";
	int count = 0;
	
	srand(time(NULL));
	
	for(i=0; i < TOTAL*LEN; ++i){
		
		//pick random char from str and append it to final
		no = rand()%4;		
			
		final.append(&str[no]);
	}
		
	pos = 0;
	while(count < TOTAL){
		
		temp.clear();
		temp.assign(final, pos, LEN);
		fp << temp <<endl;
		count++;
		pos += rand()%(LEN - 1);
		
	}
	
	printf("\nLength of actual superstring: %d", pos + LEN);
	fp.close();
	return 0;
}
