#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define MATCH 10
#define MISMATCH -4
#define GAPP 10
#define GAPE 8

using namespace std;

struct element {
	int val;
	int parent;
};

typedef struct element ELEMENT;



ELEMENT** init_matrix(int alen, int blen) {
	ELEMENT **mmatrix;
	int i;
	
	mmatrix = (ELEMENT**) malloc(sizeof(ELEMENT) * alen);
	
	for(i = 0; i < alen; ++i){
	
		mmatrix[i] = (ELEMENT*) calloc(sizeof(ELEMENT), blen);
		//memset(matrix[i], 0, blen);
	}
	return mmatrix;
}

void print_matrix(ELEMENT** mmatrix, int alen, int blen, char* astring, char* bstring) {
	int i, j;
	
	printf("\t\t");
	for(j = 0; j < blen-1; ++j)
		printf("\t %c", bstring[j]);
		
	printf("\n");
	
	for(j = 0; j < blen; ++j)
		printf("\t 0");
		
	printf("\n");
	
	for(i = 2; i< alen; ++i) {		
		for(j = 0; j< blen; ++j){
			 if(j==0)
			 	 printf("\t %c", astring[i-2]);
			 else if(j==1)
			 	 printf("\t 0");
		     else
				printf("\t %d", mmatrix[i][j].val);		
		}
		printf("\n");
	}
}
/*
void init_mat(char **mat, int flen, int jlen) {
	
}
void build_matrix(char* frst, char* scnd, char **mat, int flen, int slen) {
	
	init_mat(mat, flen, jlen);
}
*/

void populate_matrix(ELEMENT **mmatrix, char *astring, char *bstring, int M, int N) {
	
	int i, j, k, val=0;
	
	for(i = 2; i < M; ++i) {
		for(j = 2; j < N; ++j) {
			
			/*if chars match*/
			if(astring[i-2] == bstring[j-2]) {
				val = mmatrix[i-1][j-1].val + MATCH; 
				mmatrix[i][j].parent = 0;
			}
			
			for(k = i-1; k>0; k--){
				if(val < (mmatrix[i-k][j].val - (GAPP + (GAPE * k)))) {
					val = mmatrix[i-k][j].val - (GAPP + (GAPE * k));
					mmatrix[i][j].parent = -1;
				}
			}
			
			for(k = j-1; k>0; k--){
				if(val < (mmatrix[i][j-k].val - (GAPP + (GAPE * k)))) {
					val = mmatrix[i][j-k].val - (GAPP + (GAPE * k));
					mmatrix[i][j].parent = -1;
				}
			}
			
			if(val<0){
				val = 0;
			}
			
			/*if mismatch*/
			if(astring[i-2] != bstring[j-2]) {
				if(val < (mmatrix[i-1][j-1].val + MISMATCH));
				matrix[i][j].parent = 0;
			}
			
			if(val < 0) {
				val = 0;
			}
			
			
			mmatrix[i][j].val = val;
			val=0;
		}
	}
	
	
}
int main() {
	
	ELEMENT **mmatrix = init_matrix(20, 18);
	char *astring = "CGATCGATCGATATAGTG";
	char *bstring = "TAGCTAGATCCGAGAT";
	
	populate_matrix(mmatrix, astring, bstring, 20, 18);
	
	print_matrix(mmatrix, 20, 18, astring, bstring);
	
	/*
	ELEMENT **mmatrix = init_matrix(7, 8);
	char *astring  = "AACTT";
	char *bstring = "ATCTTX";
	
	populate_matrix(mmatrix, astring, bstring, 7, 8);
	print_matrix(mmatrix, 7, 8, astring, bstring);
	*/
	return 0;
}

