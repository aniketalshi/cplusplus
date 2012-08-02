//http://ideone.com/Pm6jN
#include<iostream>
#include<stdio.h>
#include<vector>
#include<math.h>

using namespace std;

class Node {
private:
	int content;//content of node
	bool marker;//to mark if its the end node
	vector<Node*> children; //maintains list of all drect child nodes

public:
	Node();
	~Node();
	
	void setcontent(int c);
	void setmarker();
	int getcontent();
	bool getmarker();
	Node* findchild(int c);
	void appendchild(Node* node);
	vector<Node*> returnchildren();
};

Node::Node(){
content=0;
marker=false;
}

void Node::setcontent(int c){
 content=c;
}

void Node::setmarker(){
 marker=true;
}

int Node::getcontent(){
 return content;
}

bool Node::getmarker(){
 return marker;
}

Node* Node::findchild(int c){
 
 for(int i=0;i<children.size();i++)
 {
    Node* tmp=children.at(i); 
	 if(tmp->getcontent()==c){
	  return tmp;
	}
 }
return NULL;

}

void Node::appendchild(Node *child)
{
 children.push_back(child);
}


void assign(vector<int> &v,string s){

int i,j,tmp;
        i=s.length()-1;
        
        while(i>=0){
                j=0;
                tmp=0;
                while(s[i]!='.')
                {
                 tmp=tmp+((s[i]-'0')*pow(10,j));
                 j++;   
                if(i>0)
                 i--;
                else break;
                }
                v.push_back(tmp);
                i--;
        }

}

class Trie {
private:
	Node *root;
public:
	Trie();
	//~Trie();
	void addstring(string s);
	void findstring(string s);
	
};

Trie::Trie(){
root=new Node(); //create a root node for given Trie
}

void Trie::addstring(string s){
 Node *current;
 
 current=root;
 
 //convert this string to integers
  vector<int> nos;
  assign(nos,s);
 
 for(int i=nos.size()-1;i>=0;i--){
   
   Node *tmp=current->findchild(nos.at(i)); //find the child of current node 
   
   if(tmp!= NULL){
		current=tmp;
   } else {
		Node *tmp1=new Node();
		tmp1->setcontent(nos.at(i));
		current->appendchild(tmp1); //set tmp as child of current
	    current=tmp1;
      }
	  
	  if(i==0)
		current->setmarker(); //mark this node as end node
		
 }
 
}

void Trie::findstring(string s){

Node *current=root;
vector<int> pos;
int count=0;

assign(pos,s);
 
 
 for(int i=pos.size()-1;i>=0;i--){
	Node *tmp=current->findchild(pos.at(i));
	
	if(tmp==NULL)
		break;
	else{
		current=tmp;
		count++;
	    }	
  }

//printf("%d\n",count);	
 cout<<endl;
int i=pos.size()-1;
while(i>=0){

if(count){
printf("%d .",pos.at(i));
count--;
}else{
printf("0 .");
}
i--;
}

}

int main()
{
 Trie t1;
 t1.addstring("172.220.10.4");
 t1.addstring("172.220.11.4");
 t1.addstring("172.221.10.4");
 t1.addstring("172.221.11.4");
 t1.addstring("172.221.12.4");
 t1.addstring("173.20.10.4");
 t1.addstring("173.20.10.41");
 t1.addstring("174.22.10.41");
 
 
 
 t1.findstring("172.221.4.4");
 t1.findstring("173.20.10.100");

  
 
 return 0;


}