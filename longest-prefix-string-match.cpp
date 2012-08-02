//trie you can find compiled code at http://ideone.com/fQHFN
#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

class Node {
private:
	char content;//content of node
	bool marker;//to mark if its the end node
	vector<Node*> children; //maintains list of all drect child nodes

public:
	Node();
	~Node();
	
	void setcontent(char c);
	void setmarker();
	char getcontent();
	bool getmarker();
	Node* findchild(char c);
	void appendchild(Node* node);
	vector<Node*> returnchildren();
};

Node::Node(){
content='\0';
marker=false;
}

void Node::setcontent(char c){
 content=c;
}

void Node::setmarker(){
 marker=true;
}

char Node::getcontent(){
 return content;
}

bool Node::getmarker(){
 return marker;
}

Node* Node::findchild(char c){
 
 for(int i=0;i<children.size();i++)
 {
    Node* tmp=children.at(i); 
	 if(tmp->getcontent()==c)
	  return tmp;
 }

}

void Node::appendchild(Node *child)
{
 children.push_back(child);
}

class Trie {
private:
	Node *root;
public:
	Trie();
	//~Trie();
	void addstring(string s);
	bool findstring(string s);
	
};

Trie::Trie(){
root=new Node(); //create a root node for given Trie
}

void Trie::addstring(string s){
 Node *current;
 
 current=root;
 
 for(int i=0;i<s.length();i++){
   
   Node *tmp=current->findchild(s[i]); //find the child of current node 
   
   if(tmp!= NULL){
		current=tmp;
   } else {
		Node *tmp1=new Node();
		tmp1->setcontent(s[i]);
		current->appendchild(tmp1); //set tmp as child of current
	    current=tmp1;
      }
	  
	  if(i==s.length()-1)
		current->setmarker(); //mark this node as end node
		
 }
 
}

bool Trie::findstring(string s){

Node *current=root;
 
 while(current!=NULL){
 for(int i=0;i<s.length();i++){
	Node *tmp=current->findchild(s[i]);
	
	if(tmp==NULL)
		return false;
	else
		current=tmp;
  }
  if(current->getmarker()) 
	 return true;
  else
	 return false;
  
 }

 return false;
}

int main()
{
 Trie t1;
 t1.addstring("Missipi");
  
 
 if(t1.findstring("Miss"))
  printf("found 1");
 else
  printf("notfound 1");
  
 t1.addstring("Missing");
 
 if(t1.findstring("Missing"))
  printf("found 2");
 else
  printf("notfound 2");
 
 //delete t1;
 return 0;


}
