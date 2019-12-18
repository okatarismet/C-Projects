#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string.h>


typedef struct node{
  char futbolName[100];
  char teamName[100];
  node * listHead;
  node* next;
}* nodePtr;

struct listNode  {
	int data;
	struct listNode* next;
	struct listNode* prev;
};



nodePtr head;
nodePtr curr;
nodePtr temp;

struct listNode* GetNewNode(int x) {
	struct listNode* newNode
		= (struct listNode*)malloc(sizeof(struct listNode));
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}
void InsertAtTail(int x,struct listNode** listhead) {
  // printf("1>>>>>|%p|\n",listhead);
	struct listNode** temp = listhead;
	struct listNode* newNode
		= (struct listNode*)malloc(sizeof(struct listNode));
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
  
	if((*listhead) == NULL) {
		(*listhead) = newNode;
     printf(">>>>>|%p|\n",(*listhead));
		return ;
	}
	while((*temp)->next != NULL) (*temp) = (*temp)->next; // Go To last Node
	(*temp)->next = newNode;
	newNode->prev = (*temp);
}
void PrintNodeList(struct listNode** listhead) {
	struct listNode** temp = listhead;
  //  printf("print>>>>>|%p|\n",listhead);
	printf("Forward: ");
	while((*temp) != NULL) {
		printf("|%d| ",(*temp)->data);
		(*temp) = (*temp)->next;
	}
	printf("\n");
}
void AddNode(char futbolName[100],char teamName[100]){

  nodePtr n = new node;
  n->next = NULL;
  strcpy(n->futbolName,futbolName);
  strcpy(n->teamName,teamName);
 

  if(head != NULL){
      curr = head;
      while(curr->next != NULL)
        curr = curr->next;
      curr->next = n;
  }
  else
      head = n;
}
void PrintNode(){
    curr = head;
    while(curr != NULL){
      printf("%s -- %s\n",curr->futbolName,curr->teamName);
      curr = curr->next;
    }
}
int myCompare (const void * a, const void * b ) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;
    return strcmp(pa,pb);
}
bool search(nodePtr head, char * aranan) { 
    nodePtr current = head;  // Initialize current 
    while (current != NULL) 
    { 
        if (strcmp(current->futbolName,aranan) ==0) 
            return true; 
        current = current->next; 
    } 
    return false; 
} 

int main() { 
  char ** lines = (char**)malloc(sizeof(char*)*1000);
  std::ifstream input("input1.txt");
  int lenOfLinesArray = 0;
  int i = 0;
  for( std::string line1; getline( input, line1 ); ){
    const char * line = line1.c_str();
    lines[i] = (char*) malloc(sizeof(char)*200);
    strcpy(lines[i],line);
    i++;
  }
  lenOfLinesArray = i;
   
  qsort(lines,lenOfLinesArray, sizeof(char *), myCompare);
  int count = 0;
  while(count < lenOfLinesArray){
      printf("\n------------------\n");
      int sublineCount = 1;
      char subline[200];
      const char * line = lines[count];
      int counter = 1;
      char name[100];
      char team[100];
      for(int i =0,k = 0;i < i+1;i++,k++){
            if(line[i]==','){
                subline[k] = '\0';
                i++;k=0;
                if(counter ==2){
                    printf("sonuc: %s\n",subline);
                    strcpy(team,subline);
                    printf("kopyaladim team e: %s\n",team);
                    counter++;
                }
                if(counter ==1){
                    printf("sonuc: %s\n",subline);
                    strcpy(name,subline);
                    printf("kopyaladim name e: %s\n",name);
                    counter++;
                }
                
            }
            if(line[i]=='\0' ){
                subline[k] = '\0';
                printf("sonuc: %s\n",subline);
                break;
            }
            subline[k] = line[i];
      }
    if(!search(head,name)){
      AddNode(name,team);
    }
    
    count++;
    }
    // PrintList();


	

  




  
   return 0; 
} 