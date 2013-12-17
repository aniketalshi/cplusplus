/******************************************************************************
**	Program to find shortest common superstring given strings
**	Input from file output.txt 
** 	Number of strings - SIZE 
** 	Strings of length LEN
**  Step1 : Construct n x n matrix of overlap among strings
**  Step2 : Construct a overlap graph
**  Step3 : Run Kruskal's Algorithm for Maximal Spanning Tree
**  Step4 : Arrange the edges to form path 
**  Step5 : Traverse on this path and output the superstring
** 	**************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<queue>
#include<list>
#include<iomanip>
#include<string.h>
#include<fstream>
#include<sys/time.h>
#define SIZE 100
#define LEN 5

using namespace std;

typedef struct node{        
    int src;
    int dest;
    int wt;
}node_t;

class compare{
    public:
        bool operator()(node_t &n1, node_t &n2){
            return(n1.wt < n2.wt);
        }
};

typedef struct subset{
    int parent;
    int rank;
}subset_t;


typedef std::vector<node_t> neighbour_t;
typedef std::vector<neighbour_t> graph_t;
typedef std::list<node_t> final_t;
typedef std::priority_queue<node_t, vector<node_t>, compare> queue_t;
typedef std::vector<subset_t> sublist_t;
typedef std::vector<node_t> klist_t;


/* Function creates overlapGraph from the overlapMatrix
** Each node represents a string and wieght on edges
** between nodes represent the overlap between strings 
**/
void createGraph(graph_t &graph, int overlapMatrix[SIZE][SIZE], int size){
	neighbour_t nbrList;

    for(int i=0; i < size; ++i){
        for(int j=0; j < size; ++j){

            if(overlapMatrix[i][j] > 0){
                node_t* nd = (node_t*)malloc(sizeof(struct node));
                nd->src = i;
                nd->dest = j;
                nd->wt = overlapMatrix[i][j];
                nbrList.push_back(*nd);
            }
        }
        if(!nbrList.empty()){
            graph.push_back(nbrList);
            nbrList.clear();
        }
    }
}

/*An auxiallry function to print graph*/
void printGraph(graph_t &graph){
	int i,j;
    
    for(i=0; i<graph.size(); ++i){
        printf("\n");
        for(j=0; j<graph[i].size(); ++j){
            printf("\t\t%d %d %d",graph[i][j].src,graph[i][j].dest, graph[i][j].wt);
        }
    }   
}

/* function used for making descending priority queue of edges 
** to be used in kruskal's algorithm 
**/
void makeQueue(queue_t &queue, graph_t &graph){
	int i, j;

    for(i=0; i<graph.size(); ++i){
        for(j=0; j<graph[i].size(); ++j){
            queue.push(graph[i][j]);
        }
    }
}

/*An auxillary function to print queue*/
void printQueue(queue_t &queue){
    node_t nd;

    while(!queue.empty()){
        nd = queue.top();
        printf("\n%d %d %d", nd.src, nd.dest, nd.wt);
        queue.pop();
    }   
}

/*  function to find set to which given node belongs to */
int find(sublist_t &sublist, int node){
	
    if(sublist[node].parent == node)
        return sublist[node].parent;
    else
        find(sublist, sublist[node].parent);
}

/* A function which does union of two subsets 
** Used in kruskal's algorithm
 **/
void subunion(sublist_t &sublist, int x, int y){
    int xp, yp;
    xp = find(sublist, x);
    yp = find(sublist, y);

    if(sublist[xp].rank == sublist[yp].rank){
        sublist[xp].parent = yp;
        sublist[yp].rank++;
    }else if(sublist[xp].rank > sublist[yp].rank){
        sublist[xp].parent = yp;
    }else{
        sublist[yp].parent = xp;    
    }
}

/*An auxillary function to print maximal spanning tree returned by kruskal*/
void printKlist(klist_t &klist){
    int i;
    for(i = 0; i < klist.size(); ++i)   {
        printf("\t\t%d  %d  %d",klist[i].src, klist[i].dest, klist[i].wt);
    }

}

/*  Kruskal's greedy algorithm generates maximal spanning tree
**  by selecting pairs which has maximum overlap or highest wieigh 
**  on their edges.
**/
void kruskal(graph_t &graph, queue_t &queue, klist_t &klist){

    int i,v,x,y;

    sublist_t sublist;
    node_t nd;

    for(i = 0; i < 2 * graph.size(); ++i){
        subset_t* sub = (subset_t*)malloc(sizeof(struct subset));
        sub->parent = i;
        sub->rank = 0;
        sublist.push_back(*sub);
    }

    klist.clear();
    while(klist.size() < graph.size()){
        nd = queue.top();

        x = find(sublist, nd.src);
        y = find(sublist, nd.dest);

        if(x != y){
            klist.push_back(nd);
            subunion(sublist, x, y);
        }
        queue.pop();        
    }
}

/*Auxiallry function to print final list o/p of kruskal*/
void printFinal(final_t &final){

    for(std::list<node_t>::iterator it = final.begin(); it != final.end(); ++it){
        printf("\t\t%d  %d  %d",(*it).src, (*it).dest, (*it).wt);
    }

}

/* Kruskal's just returns minimum spanning tree
** Based on edges returned, we build longest path 
** and final sequence by iterating over this list once.
*/
void buildFinal(final_t &final, klist_t &klist){
    
    int i, flag;
    std::vector<int> temp;

    final.push_back(klist[0]);
    temp.push_back(0);

    while(!klist.empty()){

        flag = 0;
        for(i=1; i < klist.size(); ++i){

            if(final.front().src == klist[i].dest){
                final.push_front(klist[i]); 
                temp.push_back(i);  
                flag = 1;   

            }else if((final.back()).dest == klist[i].src){
                final.push_back(klist[i]);
                temp.push_back(i);
                flag = 1;
            }
        }

        if(flag == 0 && !klist.empty()){
            final.push_back(klist[0]);
            temp.push_back(0);
	    }

        for(i = temp.size()-1; i >= 0; --i){
            klist.erase(klist.begin() + temp[i]);
        }
        temp.clear();   
    }   
}

/*a simple function fo find overlap between given strings*/
int findOverlap(char *p1, char *p2){
    int len1, len2, i, j, m, count;

    len1=0;
    len2=0;

    while(*p1 != '\0'){
        len1++;
        p1++;
    }

    while(*p2 != '\0'){
        len2++;
        p2++;
    }

    p1 -= len1;
    p2 -= len2;


    for(i= ((len1-len2 > 0)?len1-len2:0); i<len1; ++i){ 
        count = 0;
        m = i;

        if(len2 >= len1-i && p1[i]==p2[0] && len1-i <= len2 && p1[len1-1]==p2[(len1-1)-i]){

            for(j=0; j<len2 && m<len1; m++,j++){

                if(p1[m] == p2[j]){
                    count++;
                }else{
                    break;
                }
            }
	    }
        if(m >= len1)
            break;
    }
    return count;
}

/*An auxillary function to print overlap matrix created*/
void printMatrix(int overlapMatrix[SIZE][SIZE]){
    int i,j;
	for(i=0; i<SIZE; ++i){
        for(j=0; j<SIZE; j++){
            printf("\t%d %d %d", i, j, overlapMatrix[i][j]);
        }   
    }
}

/*function to build nxn matrix which [i][j] stores overlap between i and j strings*/
void buildMatrix(int overlapMatrix[SIZE][SIZE], std::string str[], int size){

    int i, j, val;
    int flag[size];
    memset(flag, 0, size);

    for(i=0; i<size; ++i){
        if(flag[i] == 1){
            for(j=0; j<size; ++j){
                overlapMatrix[i][j] = 0;    
            }
		}else{
			for(j=0; j<size; ++j){
                if(i==j){
                    overlapMatrix[i][j] = 0;
                }else if (flag[j] == 1){
                    overlapMatrix[i][j] = 0;
                }else{
                    val = findOverlap(&str[i][0], &str[j][0]);
                    if(val == LEN){
                        val = 0;
                        flag[j] = 1;
                    }
                    overlapMatrix[i][j] = val;
                }
            }
        }
    }
}

/*function generates superstring from final sequence of overlaps*/
void generateSuperstring(final_t &final, std::string str[]){
    

    std::string suprstr;
    std::list<node_t>::iterator it = final.begin();


    suprstr.append(str[(*it).src]);
    suprstr.append(str[(*it).dest], (*it).wt, str[(*it).dest].length() - (*it).wt);
    int temp = (*it).dest;
    ++it;

    for(; it != final.end(); ++it){

        if(temp == (*it).src){
            suprstr.append(str[(*it).dest], (*it).wt, str[(*it).dest].length() - (*it).wt);
            temp = (*it).dest;
        }else{
            suprstr.append(str[(*it).src]);
            suprstr.append(str[(*it).dest], (*it).wt, str[(*it).dest].length() - (*it).wt);
            temp = (*it).dest;
        }

    }

    printf("\nLenght of superstring is: %d\n",suprstr.length());
    std::cout<<endl<<suprstr;

}

/*Get the input from output.txt and populate str array of strings*/
void buildDictionary(std::string str[]){
    int count = 0;
    string line;
	
    ifstream myfile ("output.txt");
    if (myfile.is_open())
    {
        while (getline (myfile,line))
        {
            str[count++].assign(line);
        }
        myfile.close();
    }else{
        printf("File not present");
    } 
}

int main(){
	/*to record running time*/
	struct timeval start, end;
	double seconds;    
	gettimeofday(&start, NULL);

    graph_t graph;
    queue_t queue;
    klist_t klist;
    final_t final;

    int overlapMatrix[SIZE][SIZE];
    
    std::string str[SIZE];
    buildDictionary(str);
	
    buildMatrix(overlapMatrix, str, SIZE);
    createGraph(graph, overlapMatrix, SIZE);    
    makeQueue(queue, graph);

    kruskal(graph, queue, klist);
    buildFinal(final, klist);
    generateSuperstring(final, str);

    gettimeofday(&end, NULL);
    seconds  = (end.tv_sec  - start.tv_sec) * 1000.0;
    seconds += (end.tv_usec - start.tv_usec)/1000.0;

    printf("\nElapsed time: %lf milliseconds\n", seconds);
    return 0;
}
