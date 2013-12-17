/* A program to compute smith-waterman Algorithm
** computes optimal alignment along with gap penalty and extension penalty
**	
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define MATCH 10
#define MISMATCH -4
#define GAPP 10
#define GAPE 8

#define LEN1 12
#define LEN2 12

using namespace std;

/*Global variables*/
int cont = 1, acount = 0, bcount = 0;
int blosum[20][20] = {
	{ 4, -1, -2, -2,  0, -1, -1,  0, -2, -1, -1, -1, -1, -2, -1,  1,  0, -3, -2,  0},
	{-1,  5,  0, -2, -3,  1,  0, -2,  0, -3, -2,  2, -1, -3, -2, -1, -1, -3, -2, -3},
	{-2,  0,  6,  1, -3,  0,  0,  0,  1, -3, -3,  0, -2, -3, -2,  1,  0, -4, -2, -3},
	{-2, -2,  1,  6, -3,  0,  2, -1, -1, -3, -4, -1, -3, -3, -1,  0, -1, -4, -3, -3},
	{ 0, -3, -3, -3,  9, -3, -4, -3, -3, -1, -1, -3, -1, -2, -3, -1, -1, -2, -2, -1},
	{-1,  1,  0,  0, -3,  5,  2, -2,  0, -3, -2,  1,  0, -3, -1,  0, -1, -2, -1, -2},
	{-1,  0,  0,  2, -4,  2,  5, -2,  0, -3, -3,  1, -2, -3, -1,  0, -1, -3, -2, -2},
	{ 0, -2,  0, -1, -3, -2, -2,  6, -2, -4, -4, -2, -3, -3, -2,  0, -2, -2, -3, -3},
	{-2,  0,  1, -1, -3,  0,  0, -2,  8, -3, -3, -1, -2, -1, -2, -1, -2, -2,  2, -3},
	{-1, -3, -3, -3, -1, -3, -3, -4, -3,  4,  2, -3,  1,  0, -3, -2, -1, -3, -1,  3},
	{-1, -2, -3, -4, -1, -2, -3, -4, -3,  2,  4, -2,  2,  0, -3, -2, -1, -2, -1,  1},
	{-1,  2,  0, -1, -3,  1,  1, -2, -1, -3, -2,  5, -1, -3, -1,  0, -1, -3, -2, -2},
	{-1, -1, -2, -3, -1,  0, -2, -3, -2,  1,  2, -1,  5,  0, -2, -1, -1, -1, -1,  1},
	{-2, -3, -3, -3, -2, -3, -3, -3, -1,  0,  0, -3,  0,  6, -4, -2, -2,  1,  3, -1},
	{-1, -2, -2, -1, -3, -1, -1, -2, -2, -3, -3, -1, -2, -4,  7, -1, -1, -4, -3, -2},
	{ 1, -1,  1,  0, -1,  0,  0,  0, -1, -2, -2,  0, -1, -2, -1,  4,  1, -3, -2, -2},
	{ 0, -1,  0, -1, -1, -1, -1, -2, -2, -1, -1, -1, -1, -2, -1,  1,  5, -2, -2,  0},
	{-3, -3, -4, -4, -2, -2, -3, -2, -2, -3, -2, -3, -1,  1, -4, -3, -2, 11,  2, -3},
	{-2, -2, -2, -3, -2, -1, -2, -3,  2, -1, -1, -2, -1,  3, -3, -2, -2,  2,  7, -1},
	{ 0, -3, -3, -3, -1, -2, -2, -3, -3,  3,  1, -2,  1, -1, -2, -2,  0, -3, -1,  4}};
	
char blosumstr[20] = {'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V'};
 
struct element {
	int val;
	int parent;
};

typedef struct element ELEMENT;

/*Initialize the Matrix*/
ELEMENT** init_matrix(int alen, int blen) {
	ELEMENT **mmatrix;
	int i;
	
	mmatrix = (ELEMENT**) malloc(sizeof(ELEMENT) * alen);
	for(i = 0; i < alen; ++i){
		mmatrix[i] = (ELEMENT*) calloc(sizeof(ELEMENT), blen);
	}
	return mmatrix;
}

/*Helper function to print the matrix*/
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

int getindex(char t){
	int i;
	for(i=0; i<20; ++i){
		if(blosumstr[i] == t)
			return i;
	}
	
	return -1;
}

/*Function to compute the matrix*/
void populate_matrix(ELEMENT **mmatrix, char *astring, char *bstring, int M, int N) {
	
	int i, j, k, val=0, indx;
	char temp;
	
	for(i = 2; i < M; ++i) {
		for(j = 2; j < N; ++j) {
			
			/*if chars match*/
			if(astring[i-2] == bstring[j-2]) {
				temp = astring[i-2];
				indx = getindex(temp);
				val = mmatrix[i-1][j-1].val + blosum[indx][indx]; 
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
				if(val < (mmatrix[i-1][j-1].val + blosum[getindex(astring[i-2])][getindex(bstring[j-2])]));
				mmatrix[i][j].parent = 0;
			}
			
			if(val < 0) {
				val = 0;
			}
			
			
			mmatrix[i][j].val = val;
			val=0;
		}
	}
	
	
}

/*Function which aligns the two strings which recursively traverses the matrix and finds
** best possible alignment
**/
int align_strings(ELEMENT **mmatrix, int xpos, int ypos, char* maxa, char* maxb, char *astring, char *bstring) {
	int i,j;
	 
	int max = -1;		
	int maxpos[2];		

	if(mmatrix[xpos][ypos].val == 0) {
		cont = 0;
	}

	while(cont == 1) {	
		
		
		for(i=xpos; i>0; --i) {
	
			if(max < mmatrix[i-1][ypos-1].val) {
				
				max = mmatrix[i-1][ypos-1].val;
				maxpos[0]=i-1;
				maxpos[1]=ypos-1;
			}
		}

		for(j=ypos; j>0; --j) {

			if(max < mmatrix[xpos-1][j-1].val) {

				max = mmatrix[xpos-1][j-1].val;
				maxpos[0]=xpos-1;
				maxpos[1]=j-1;
			}
		}

		
		if((maxpos[0] == xpos-1) && (maxpos[1] == ypos-1)) {	

			maxa[acount] = astring[maxpos[0]-1];
			++acount;
			maxb[bcount] = bstring[maxpos[1]-1];
			++bcount;

		}

		else {

			if((maxpos[1] == ypos-1) && (maxpos[0] != xpos-1)) {	
				
				for(i=xpos-1; i>maxpos[0]-1; --i) {	
				
						maxa[acount] = astring[i-1];
						++acount;
				}
				maxb[bcount] = bstring[maxpos[1]-1];	
				++bcount;
				
				for(j=xpos-1; j>maxpos[0]; --j) {	

					maxb[bcount] = '-';
					++bcount;
				}	
			}

			if((maxpos[0] == xpos-1) && (maxpos[1] != ypos-1)) {	

				for(j=ypos-1; j>maxpos[1]-1; --j) {	

					maxb[bcount] = bstring[j-1];
					++bcount;
				}
				maxa[acount] = astring[maxpos[0]-1];
				++acount;
				
				for(i=ypos-1; i>maxpos[1]; --i) {		

					maxa[acount] = '-';
					++acount;
				}				
			}
		}

		align_strings(mmatrix,maxpos[0],maxpos[1], maxa, maxb, astring, bstring);
	}

	return(cont);
	
}

/*Auxially function to calculate largest value cell*/
int find_max_pos(ELEMENT **mmatrix, int* xpos, int* ypos, int alen, int blen) {
	int i, j, maxval = 0;
	for(i = 2; i<alen; ++i) {
		for (j=2; j<blen; ++j){
			if(mmatrix[i][j].val > maxval) {
				maxval = mmatrix[i][j].val;
				*xpos = i;
				*ypos = j;
			}
		}
	}	
}

int main() {
	
	ELEMENT **mmatrix = init_matrix(LEN1, LEN2);
	char *astring  = "ARCQHWVSMF";
	char *bstring = "MRCQSWTSMF";
	
	int xpos, ypos, maxval, check;
	char *maxa, *maxb;
	
	maxa = (char*)malloc(sizeof(char)*LEN1);
	maxb = (char*)malloc(sizeof(char)*LEN2);	
		
	
	populate_matrix(mmatrix, astring, bstring, LEN1, LEN2);
	
	print_matrix(mmatrix, LEN1, LEN2, astring, bstring);
	
	maxval = find_max_pos(mmatrix, &xpos, &ypos, LEN1, LEN2);	
	maxa[0] = astring[xpos-1];
	maxb[0] = bstring[ypos-1];
		
	check = align_strings(mmatrix, xpos, ypos, maxa, maxb, astring, bstring);

	printf("\n%s \n %s",maxa, maxb);
	return 0;
}

