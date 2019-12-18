#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *node_ptr;
struct node{
    char  data;
    char *pass;
    node_ptr *child;
};

node_ptr head;
FILE *out;
int len(char * name){
    int length;
    for(length = 0;;length++)
        if(name[length] == '\0')
            break;
    return length;
}
int addRecursive(char * name,char * pass, node_ptr head){
    int i = 0;
    int reserved = 1;                      
    if(len(name) ==0 && head->pass == NULL){       // Look for values like -cem     
            head->pass = malloc(sizeof(char)*100); // give size for pass
            strcpy(head->pass,pass);                
            fprintf(out,"was added\n");
            return 1;
    }   
    while(head->child[i] != NULL){
        if(head->child[i]->data == '0')
                i++;
        else{
            if(head->child[i]->data == name[0]){   // while the name exist go its path
                addRecursive(name+1,pass,head->child[i]);
                return 1;
            }
            i++;
        }
    }
    if(len(name) == 0 && head->pass != NULL)fprintf(out,"reserved username\n"); // if rserved or not
    reserved = 0;
    (*head).child = realloc((*head).child,(i+2)*sizeof(node_ptr));
    int length;
    for(length = 0;;length++){ // get the legth of it.
        if(name[length] == '\0')
            break;
    }
    int k;
    for(k = 0; k<length;k++){
        node_ptr n = malloc(sizeof(node_ptr));  // create and load the node
        n->data    = name[k];
        n->child   = malloc(sizeof(node_ptr)*2);
        n->pass = NULL;
        head->child[i] = n;
        if(length -1 == k){                     // if it is the last letter also load the password on it 
            head->child[i]->pass = malloc(sizeof(char)*100);
            strcpy(head->child[i]->pass,pass);
            fprintf(out,"was added\n");
        }  
        head = (*head).child[i];
        i=0;
    }
}

void searchRecursive(node_ptr head,char * name,char * pass,int length,char mod){
    if(head){
        if(len(name) == 0 && head->pass != NULL && mod =='s'){
            fprintf(out,"password \"%s\"\n",head->pass);
            return;
        }
        if(len(name) == 0 && head->pass != NULL && mod =='q' && strcmp(head->pass,pass) !=0){
            fprintf(out,"incorrect password\n");
            return;
        }
        if(len(name) == 0 && head->pass != NULL && mod =='q' && strcmp(head->pass,pass) ==0){
            fprintf(out,"successful login\n");
            return;
        }
        if(len(name) == 0 && head->pass == NULL){
            fprintf(out,"not enough username\n");
            return;
        }
        int k = 0;
        while(head->child[k] != NULL){
            if(head->child[k]->data == '0')
                k++;
            else{
                if(head->child[k]->data == name[0]){
                    searchRecursive(head->child[k],name+1,pass,length,mod);
                    return;
                }
                k++;
            }
        }
        if(len(name) == length)
            fprintf(out,"no record\n");
        if(len(name) <  length)
            fprintf(out,"incorrect username\n");
    }
}
void printRecursive(node_ptr head,int v,char str[100]){
    if(head){
        int k  = 0;
        str[v] = head->data;
        v++;
        if(head->pass){
            str[v] = '\0';
            int j;
            for(j = 0;j<v; j++)
               fprintf(out,"%c",str[j]);
            fprintf(out,"\n"); 
        }
        while(head->child[k] != NULL){
            if(head->child[k]->data == '0')
                k++;
            else{
                printRecursive(head->child[k],v,str);
                k++;
            }
        }
    }
}
void deleteRecursive(node_ptr head,char * name,int length,int * bulundu){
    if(head){
        if(len(name) == 0 && head->pass != NULL ){
            free(head);
            fprintf(out,"deletion is successful\n");
            *bulundu = 1;
            return;
        }
        if(len(name) == 0 && head->pass == NULL){
            fprintf(out,"not enough username\n");
            return;
        }
        int k = 0;
        while(head->child[k] != NULL){
            if(head->child[k]->data == '0')
                k++;
                else{
                    if(head->child[k]->data == name[0]){
                        deleteRecursive(head->child[k],name+1,length,bulundu);
                        if(*bulundu ==1 && head->child[1] == NULL )
                            free(head);
                        if(*bulundu ==1 && head->child[1] != NULL){
                            node_ptr n = malloc(sizeof(node_ptr));
                            n->data    = '0';
                            n->child   = malloc(sizeof(node_ptr)*2);
                            n->pass    = NULL;
                            head->child[k] = n;
                            *bulundu   = 0;
                            }
                        return;
                    }
                }
        k++;
        }
        if(len(name) == length)
            fprintf(out,"no record\n");
        if(len(name) <  length)
            fprintf(out,"incorrect username\n");
    }
}
void __a(char * name,char * pass, node_ptr head){
    fprintf(out,"\"%s\" ",name);
    addRecursive(name,pass,head);
}
void __s(node_ptr head,char * name){
    fprintf(out,"\"%s\" ",name);
    searchRecursive(head,name,"",len(name),'s');
}
void __q(node_ptr head,char * name,char * pass){  
    fprintf(out,"\"%s\" ",name);
    searchRecursive(head,name,pass,len(name),'q');
}
void __d(node_ptr head,char * name){
    fprintf(out,"\"%s\" ",name);
    int bulundu = 0;
    deleteRecursive(head,name,len(name),&bulundu);
}
void __l(node_ptr head){
    int  v = 0;
    char str[100];
    printRecursive(head,v,str);
}
int main(int argc, char const *argv[]){
    head          = malloc(sizeof(node_ptr));
    (*head).child = malloc(sizeof(node_ptr)*2);
    head->data = '-';
    head->pass = NULL;
   
    FILE *in = fopen(argv[1],"r");
    out      = fopen("output.txt","w+");
	
    char str[50];
    while(fscanf(in,"%s",str) != EOF){
        char name[50];
        char pass[50];
        if(strcmp(str,"-a") ==0){    
            fscanf(in,"%s",name);
            fscanf(in,"%s",pass);
            __a(name,pass,head);
        }
        if(strcmp(str,"-s") ==0){    
            fscanf(in,"%s",name);
            __s(head,name);
        }
        if(strcmp(str,"-q") ==0){    
            fscanf(in,"%s",name);
            fscanf(in,"%s",pass);
            __q(head,name,pass);
        }
        if(strcmp(str,"-l") ==0){    
            __l(head);
        }
        if(strcmp(str,"-d") ==0){    
            fscanf(in,"%s",name);
            __d(head,name);
        }
    }
    fclose(out);
    fclose(in);
    return 0;
}
