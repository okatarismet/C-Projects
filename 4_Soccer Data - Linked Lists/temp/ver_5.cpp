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

struct Node { // struct of second linked list
    char awayteam[100];
    int  mofgoal; 
    int  macId;
    struct Node* prev, *next;   
}; 

typedef struct node{ // struct of first linked list
    char   futbolName[100];
    char   teamName[100];
    struct Node * head;
    node * next;
}* nodePtr;


nodePtr head; // first linked lists head
nodePtr curr;
nodePtr temp;


void Addnode(char futbolName[100],char teamName[100]){ // Add node to first linked list
    nodePtr n = new node;
    n->next   = NULL;
    strcpy(n->futbolName,futbolName);         // Adding the datas
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
void Printnode(){ // Print nodes of first linked list
    curr = head;
    while(curr != NULL){
        printf("%s -- %s\n",curr->futbolName,curr->teamName);
        curr = curr->next;
    }
}
nodePtr getnode(int y){ // get a node type of first linked list
    curr  = head;
    int n = 0;
    while(n<y+1){
        if(n==y)
            return curr;
      curr = curr->next;
      n++;
    }
}
int searchnode(nodePtr head, char * aranan) {  // search for a node`s place in the linked list
    nodePtr current = head;  // Initialize current 
    int count = 0;
    while (current != NULL) 
    { 
        if (strcmp(current->futbolName,aranan) ==0)  // if equal return the location of it
            return count; 
        current = current->next; 
        count++;
    } 
    return -1; 
} 
int myCompare (const void * a, const void * b ) { // i write my own compare function
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;
    return strcmp(pa,pb);
}
struct Node* getNode(char awayteam[100],int mofgoal,int macId) {  // It gets the data and creates a node for the second linked list
    struct Node* newNode =  (struct Node *) malloc(sizeof(struct Node)); 
    newNode->mofgoal = mofgoal; 
    newNode->macId   = macId;
    strcpy(newNode->awayteam,awayteam);
    newNode->prev = newNode->next = NULL; 
    return newNode; 
} 

void sortedInsert(struct Node** head_ref, struct Node* newNode) { // it inserts sorted to second linked list
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
void printList(struct Node* head) { // prints the second linked list
    while (head != NULL) { 
        printf("%s -- %d -- %d\n",head->awayteam,head->mofgoal,head->macId);
        head = head->next; 
    } 
} 
int main() { 
    FILE *fp;
    fp = fopen("output234234.txt","w");
    char ** lines = (char**)malloc(sizeof(char*)*1000); // allocate memory
    std::ifstream input("input1.txt");                  // open the input.txt
    int lenOfLinesArray = 0;                    
    int i = 0;
    for( std::string line1; getline( input, line1 ); ){ // get the lines
        const char * line = line1.c_str();
        lines[i] = (char*) malloc(sizeof(char)*200);
        strcpy(lines[i],line);
        i++;
    }
    lenOfLinesArray = i;                                // get the size of lines
   
  qsort(lines,lenOfLinesArray, sizeof(char *), myCompare); // sort the lines for some reason
  int count = 0;
  int totalGamer = 0;                                      // keep the total gamer size
  while(count < lenOfLinesArray){
      int sublineCount = 1;
      char subline[200];
      const char * line = lines[count];
      int counter = 1;
      char name[100];
      char team[100];
      char awayteam[100];
      int mofgoal;
      int macId;
      for(int i =0,k = 0;i < i+1;i++,k++){     // i have written my own splitting function that`s why it a bit weird. 
            if(line[i]==','){
                subline[k] = '\0';
                i++;k=0;
                if(counter ==4){               //if fourth word
                    mofgoal = atoi(subline);
                    counter++;
                }
                if(counter ==3){               //if third word
                    strcpy(awayteam,subline);
                    counter++;
                }
                if(counter ==2){               //if second word  
                    strcpy(team,subline);
                    counter++;
                }
                if(counter ==1){
                    strcpy(name,subline);
                    counter++;
                }
            }
            if(line[i]=='\0' ){               //if get the last of the array
                subline[k] = '\0';
                if(counter ==5){
                    macId = atoi(subline);
                }
                break;
            }
            subline[k] = line[i];
      }
    //   printf("\n%s icin searchnode sonucu %d\n",name,searchnode(head,name));
    if(searchnode(head,name) == -1){        // if not created a node correspond to the futboller name creat a new one.
        Addnode(name,team);
        totalGamer++;
    }
    nodePtr currnode      = getnode(searchnode(head,name));          //for the current futboller get the created node
    struct Node* new_node = getNode(awayteam,mofgoal,macId);    //create a new node (which will be second linked lists node)for the given data
    sortedInsert(&(currnode->head),new_node);                   //insert it
    count++;                                              
    }       //end of while loop
    /////////////////////
    // 1.
    /////////////////////

    int mostScoredHalf = 0;
   
    fprintf(fp,"1)THE MOST SCORED HALF\n");

    for(int i = 0; i < totalGamer; i++)
    {
        Node * head = (Node *)(getnode(i)->head);
        while (head != NULL) { 
            if(head->mofgoal > 45)          // if second half increment the counter
                mostScoredHalf++;
            if(head->mofgoal <=45)          // if first half decrement the counter
                mostScoredHalf--;
            head = head->next; 
        } 
    }
    if(mostScoredHalf > 0)                  // print due to the counter data
        fprintf(fp,"1\n");
    else    
        fprintf(fp,"0\n");

    /////////////////////
    // 2.
    /////////////////////

   fprintf(fp,"2)GOAL SCORER\n");
    char topScorer[100];
    int topScorerGoal = 0;
    int * goalArray = (int *) malloc(sizeof(int)*totalGamer);
    for(size_t i = 0; i < totalGamer; i++){
        int count = 0;
        Node * head = (Node *)(getnode(i)->head);
        while (head != NULL) { 
            count++;
            head = head->next; 
        } 
        goalArray[i] = count;
    }
   
    int mostGoaler = 0;
    for(int o = 0; o+1 < totalGamer ;o++)
        if(goalArray[o] > goalArray[o+1])
            mostGoaler = o;
    if(goalArray[totalGamer-1] > goalArray[mostGoaler])
            mostGoaler = totalGamer;
    
    
    for(int i = 0; i < totalGamer; i++)
        if(goalArray[mostGoaler] == goalArray[i])
            fprintf(fp,"%s\n",getnode(i)->futbolName);
    
   
    /////////////////////
    // 3.
    /////////////////////
    fprintf(fp,"3)THE NAMES OF FOOTBALLERS WHO SCORED HAT-TRICK\n");
    for(size_t i = 0; i < totalGamer; i++)
    {
        int goalNumber = 0;
        Node * head    = (Node *)(getnode(i)->head);
        int curMacId   = head->macId;
        while (head != NULL) { 
            if(head->macId == curMacId )    //if in same match 
                goalNumber++;
            else
                curMacId = head->macId;
            head = head->next; 
        } 
        if(goalNumber > 2)
            fprintf(fp,"%s\n",getnode(i)->futbolName);
    }
    /////////////////////
    // 4.
    /////////////////////
    fprintf(fp,"4)LIST OF TEAMS\n");
    char * listOfTeams = (char *)malloc(sizeof(char)* totalGamer* 100);
    for(size_t i = 0; i < totalGamer; i++){
        if(strstr(listOfTeams,getnode(i)->teamName) == NULL){
            fprintf(fp,"%s\n",getnode(i)->teamName);
            strcat(listOfTeams,getnode(i)->teamName);
        }
    }
    /////////////////////
    // 5.
    /////////////////////
    fprintf(fp,"5)LIST OF FOOTBALLERS\n");
    char * listOfFutbol = (char *)malloc(sizeof(char)* totalGamer* 100);
    for(size_t i = 0; i < totalGamer; i++){
        if(strstr(listOfTeams,getnode(i)->futbolName) == NULL){
           fprintf(fp,"%s\n",getnode(i)->futbolName);
            strcat(listOfTeams,getnode(i)->futbolName);
        }
    }
    /////////////////////
    // 6.
    /////////////////////
   fprintf(fp,"6)MATCHES OF GIVEN FOOTBALLER\n");
    std::ifstream input1("operations1.txt");
    std::string line1;
    getline( input1, line1 );
    char  curLine[2][100];
  
    const char * line = line1.c_str();
    sscanf(line,"%[^,],%[^,]", curLine[0], curLine[1]);    

 
    for(int uu=0; uu<2; uu++){
        for(size_t i = 0; i < totalGamer; i++){
            Node * head = (Node *)(getnode(i)->head);
            if(strcmp(curLine[uu],getnode(i)->futbolName) == 0){
                nodePtr cn = getnode(i);
                fprintf(fp,"Matches of %s\n",cn->futbolName);
                while (head != NULL) { 
                    fprintf(fp,"Footballer Name: %s,Away Team: %s,Min of Goal: %d,Match ID: %d\n",
                        cn->futbolName,head->awayteam,head->mofgoal,head->macId);
                    head = head->next; 
                } 
            }
        }
    }
/////////////////////
// 7. 
/////////////////////
fprintf(fp,"7)ASCENDING ORDER ACCORDING TO MATCH ID\n");
getline(input1,line1);
line = line1.c_str();
sscanf(line,"%[^,],%[^,]", curLine[0], curLine[1]);    
 
// printf("|%s| |%s|\n",curLine[0],curLine[1]);
for(int uu=0; uu<2; uu++){
     for(size_t i = 0; i < totalGamer; i++){
        Node * head = (Node *)(getnode(i)->head);
        if(strcmp(curLine[uu],getnode(i)->futbolName) == 0){
            nodePtr cn = getnode(i);
            int curMacId = -1;
            while (head != NULL) { 
                if(curMacId != head->macId){
                fprintf(fp,"footballer Name: %s,Match ID:%d\n",
                    cn->futbolName,head->macId);
                curMacId = head->macId;
                }
                head = head->next; 
            } 
        }
    }
}
/////////////////////
// 8.
/////////////////////
fprintf(fp,"8)DESCENDING ORDER ACCORDING TO MATCH ID\n");
getline(input1,line1);
line = line1.c_str();
sscanf(line,"%[^,],%[^,]", curLine[0], curLine[1]);    
for(int uu=0; uu<2; uu++){
     for(size_t i = 0; i < totalGamer; i++){
        Node * head = (Node *)(getnode(i)->head);
        if(strcmp(curLine[uu], getnode(i)->futbolName) == 0){
            nodePtr cn = getnode(i);
            int curMacId = -1;
            while (head->next != NULL)
                head = head->next; 
            while (head != NULL) { 
                if(curMacId != head->macId){
                fprintf(fp,"footballer Name: %s,Match ID:%d\n",
                    cn->futbolName,head->macId);
                curMacId = head->macId;
                }
                head = head->prev; 
            } 
        }
    }
}



fclose(fp);


  
} // end of main
