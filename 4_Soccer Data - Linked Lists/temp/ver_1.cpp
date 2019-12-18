#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string.h>



typedef struct listNode{
  char awayTeam[100];
  int mofgoal;
  int macId;
  listNode * next;
}* listNodePtr;
typedef struct node{
  char futbolName[100];
  char teamName[100];
  listNode * listHead;
  listNode * listCurr;
  listNode * listTemp;
  node * next;
}* nodePtr;


nodePtr head;
nodePtr curr;
nodePtr temp;


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
void AddListNode(char awayTeam[100],int mofgoal, int macId,nodePtr curNode){
  listNodePtr n = new listNode;
  n->next = NULL;
  strcpy(n->awayTeam,awayTeam);
  n->mofgoal = mofgoal;
  n->macId = macId;
 
  if(curNode->listHead != NULL){
      curNode->listCurr = curNode->listHead;
      while(curNode->listCurr->next != NULL)
        curNode->listCurr = curNode->listCurr->next;
      curNode->listCurr->next = n;
  }
  else
      curNode->listHead = n;
}
void PrintListNode(nodePtr curNode){
  
    curNode->listCurr = curNode->listHead;
    while(curNode->listCurr != NULL){
      printf("%s -- %d\n",curNode->listCurr->awayTeam,curNode->listCurr->mofgoal);
      curNode->listCurr = curNode->listCurr->next;
    }
}
void PrintNode(){
    curr = head;
    while(curr != NULL){
      printf("%s -- %s\n",curr->futbolName,curr->teamName);
      curr = curr->next;
    }
}
nodePtr getNode(int n){
    curr = head;
    int y = 0;
    while(y < n+1){
      
      curr = curr->next;
      if(y == n)
        return curr;
      y++;
    }
}
int myCompare (const void * a, const void * b ) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;
    return strcmp(pa,pb);
}
int search(nodePtr head, char * aranan) { 
    nodePtr current = head;  // Initialize current 
    int count = 0;
    while (current != NULL) 
    { 
        if (strcmp(current->futbolName,aranan) ==0) 
            return count; 
        current = current->next; 
        count++;
    } 
    return -1; 
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
      char awayteam[100];
      int mofgoal;
      int macId;
      for(int i =0,k = 0;i < i+1;i++,k++){
            if(line[i]==','){
                subline[k] = '\0';
                i++;k=0;
                if(counter ==4){
                    
                    mofgoal = atoi(subline);
                    // printf("mofgoal: %s\n",subline);
                    counter++;
                }
                if(counter ==3){
                    // printf("awayteam: %s\n",subline);
                    strcpy(awayteam,subline);
                    // printf("kopyaladim team e: %s\n",team);
                    counter++;
                }
                if(counter ==2){
                    
                    strcpy(team,subline);
                      // printf("team: %s\n",subline);   
                    // printf("kopyaladim team e: %s\n",team);
                    counter++;
                }
                if(counter ==1){
                    strcpy(name,subline);
                    // printf("name: %s\n",subline);

                    // printf("kopyaladim name e: %s\n",name);
                    counter++;
                }
               
                
            }
            if(line[i]=='\0' ){
                subline[k] = '\0';
                if(counter ==5){
                    macId = atoi(subline);
                    //  printf("macid: %s\n",subline);

                }
                
                break;
            }
            subline[k] = line[i];
      }
    if(search(head,name) == -1){
      AddNode(name,team);
      // printf("ekledim.\n");
    }
    nodePtr curr = getNode(search(head,name));
    // printf("%d|\n",search(head,name));
    AddListNode(awayteam,mofgoal,macId,curr);



    count++;
    }
    // PrintList();
  

//   nodePtr curr = getNode(7);
// printf("%s -- %s\n",curr->futbolName,curr->teamName);

  
   return 0; 
} 