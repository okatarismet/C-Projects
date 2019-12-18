// C++ implementation to insert value in sorted way 
// in a sorted doubly linked list 
#include <bits/stdc++.h> 
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string.h>

  
using namespace std; 

struct Node { 
    char awayteam[100];
    int mofgoal; 
    int macId;
    struct Node* prev, *next; 
    
}; 
typedef struct node{
    char futbolName[100];
    char teamName[100];
    struct Node * head;
    node* next;
}* nodePtr;


nodePtr head;
nodePtr curr;
nodePtr temp;


void Addnode(char futbolName[100],char teamName[100]){

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
void Printnode(){
    curr = head;
    while(curr != NULL){
      printf("%s -- %s\n",curr->futbolName,curr->teamName);
      curr = curr->next;
    }
}
nodePtr getnode(int y){
    curr = head;
    int n = 0;
    while(n<y+1){
        if(n==y){
            return curr;
        }
      curr = curr->next;
      n++;
    }
}

int searchnode(nodePtr head, char * aranan) { 
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


int myCompare (const void * a, const void * b ) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;
    return strcmp(pa,pb);
}


struct Node* getNode(char awayteam[100],int mofgoal,int macId) 
{ 
    struct Node* newNode =  (struct Node*)malloc(sizeof(struct Node)); 

    newNode->mofgoal = mofgoal; 
    newNode->macId = macId;
    strcpy(newNode->awayteam,awayteam);
    newNode->prev = newNode->next = NULL; 
    return newNode; 
} 

void sortedInsert(struct Node** head_ref, struct Node* newNode) 
{ 
    struct Node* current; 
    if (*head_ref == NULL) 
        *head_ref = newNode; 
    else if ((*head_ref)->macId >= newNode->macId) { 
        newNode->next = *head_ref; 
        newNode->next->prev = newNode; 
        *head_ref = newNode; 
    } 
  
    else { 
        current = *head_ref; 
        while (current->next != NULL &&  
               current->next->macId < newNode->macId) 
            current = current->next; 
        newNode->next = current->next; 
        if (current->next != NULL) 
            newNode->next->prev = newNode; 
  
        current->next = newNode; 
        newNode->prev = current; 
    } 
} 
void printList(struct Node* head) 
{ 
    while (head != NULL) { 
        printf("%s -- %d -- %d\n",head->awayteam,head->mofgoal,head->macId);
       
        head = head->next; 
    } 
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
      printf("\n%s icin searchnode sonucu %d\n",name,searchnode(head,name));
    if(searchnode(head,name) == -1){
      Addnode(name,team);
      printf("ekledim.\n");
    }
    nodePtr currnode = getnode(searchnode(head,name));
    struct Node* new_node = getNode(awayteam,mofgoal,macId);
    sortedInsert(&(currnode->head),new_node);
   



    count++;
    }
    printf("\n---------\n-------\n");
    Printnode();
    printf("\n---------\n-------\n");
    
    for(size_t i = 0; i < 10; i++)
    {
        printf("\n%d. >>>>>>>>>>>>>>>>>>\n",i);
        nodePtr currnode = getnode(i);
        printList(currnode->head);
    }
    










  
} 
/*
Addnode = ust linked list
sortedInsert = alt linked list
*/