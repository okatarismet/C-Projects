#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


struct route{
	char bunun_icin[2];
	char once_burdan[2];
};
typedef struct route newRoute;
struct layer {
    char sender[11];
    char reciever[11];
    char * message_chunk;
    int layer_number;
    int number_of_hops;
};
typedef struct layer newLayer;
struct client {
    char ID[2];
    char IP[8];
    char MAC[11];
    int incoming_front;
    int incoming_tail;
    int outgoing_front;
    int outgoing_tail;
    newRoute * routes;
    newLayer ** incoming_que;
    newLayer ** outgoing_que;
};
typedef struct client newClient;
char * getRoute(int si,char hedef[2],newClient * clients,int client_size);
void kuyruk_dolu();
void kuyruk_bos();
void kuyruk_ekle(int on,int * arka,newLayer *  item,newLayer ** kuyruk,int NOF);
newLayer * kuyruk_al(int *on,int arka,newLayer ** kuyruk,int NOF);
void stack_dolu();
void stack_bos();
void push(newLayer layer,newLayer * layers,int *top);
newLayer pop(newLayer * layers,int *top);
void get_client(char *commands_file,struct client clients[]);
int getByID(char ID[2],newClient * clients);
int get_size(char *commands_file);
void SHOW_Q_INFO(char id[2],char inout[4],newClient * clients, int NOF);
void SHOW_FRAME_INFO(char id[2], char inout[4],int frame_number,newClient * clients,int NOF);
void MESSAGE(char sender[2],char reciever[2],char * message,int client_size,newClient * clients,int NOF,char SPORT[5],char RPORT[5],char nihai_hedef[2],int max_message_size);
char * getRoute(int si,char hedef[2],newClient * clients,int client_size);
void SEND(char sender[2],char nihai_hedef[2],newClient * clients,int client_size,int NOF);
int recursive(char from[2],char to[2],newClient *clients,int NOF);
int load_routing(char *commands_file,newClient * clients);




void kuyruk_dolu(){}
void kuyruk_bos(){}
void kuyruk_ekle(int on,int * arka,newLayer *  item,newLayer ** kuyruk,int NOF){
    *arka = (*arka+1) % NOF;
    if(on == *arka)kuyruk_dolu();
    kuyruk[*arka] = item;}

newLayer * kuyruk_al(int *on,int arka,newLayer ** kuyruk,int NOF){
    if(*on == arka)kuyruk_bos();
    *on = (*on + 1) % NOF;
    return kuyruk[*on];}
void stack_dolu(){printf("Stack Dolu !!!\n");exit(-1);}
void stack_bos(){printf("Stack Bos !!\n");exit(-2);}
void push(newLayer layer,newLayer * layers,int *top){
    if(*top >= 4)
        stack_dolu();
    layers[++*top] = layer;
}
newLayer pop(newLayer * layers,int *top){
    if(*top < 0)
        stack_bos();
    return layers[(*top)--];
}
void get_client(char *commands_file,struct client clients[]){
	FILE *client_file = fopen(commands_file,"r");
	char str[10];
	fscanf(client_file, "%s", str);
	int i=0;
	while(fscanf(client_file, "%s", str) != EOF){
		strcpy(clients[i].ID,str);
		fscanf(client_file, "%s ", str);
    	strcpy(clients[i].IP,str);
		fscanf(client_file, "%s ", str);
		strcpy(clients[i].MAC,str);
		if(feof(client_file))
    		break;
		i++;}
    fclose(client_file);}

int getByID(char ID[2],newClient * clients){
    int index;
    for(index = 0; index < index+1; index++){
        if(strcmp(clients[index].ID,ID)==0)
            return index;}}

int get_size(char *commands_file){
	FILE *client_file = fopen(commands_file,"r");
	if(client_file == NULL){
		printf("Unable to open file %s", commands_file);
		return 0;}
	char str[50] = "a";
	fscanf(client_file, "%s", str);
    if(client_file!=NULL)
        client_file = NULL;
    return atoi(str);}  

void SHOW_Q_INFO(char id[2],char inout[4],newClient * clients, int NOF){
    int si = getByID(id,clients);
    int biggest = 0;
        int cur;
        if(strcmp(inout,"in") == 0)
            cur = clients[si].incoming_tail - clients[si].incoming_front;
        if(strcmp(inout,"out") == 0)
            cur = clients[si].outgoing_tail - clients[si].outgoing_front;
        if(cur+1 > biggest)
            biggest = cur;
    if(biggest == 1)
        biggest = -1;
    if(strcmp(inout,"in") == 0)
        printf("--------------------------\nCommand: SHOW_Q_INFO %s %s\n--------------------------\nClient %s Incoming Queue Status\nCurrent total number of frames: %d\n",id,inout,id,biggest);
    if(strcmp(inout,"out") == 0)
        printf("--------------------------\nCommand: SHOW_Q_INFO %s %s\n--------------------------\nClient %s Outgoing Queue Status\nCurrent total number of frames: %d\n",id,inout,id,biggest);
}
void SHOW_FRAME_INFO(char id[2], char inout[4],int frame_number,newClient * clients,int NOF){
    printf("--------------------------------\n");
    printf("Command: SHOW_FRAME_INFO %s %s %d\n",id,inout,frame_number);
    printf("--------------------------------\n");
    int si = getByID(id,clients);
    if(strcmp(inout,"in") == 0){
            int top = 3;
            int location = clients[si].incoming_front;
            location = frame_number;
            int kuyruk_durum = clients[si].outgoing_tail-clients[si].outgoing_front;
            if( kuyruk_durum< 1 || kuyruk_durum < location-1 || location >4){
                printf("No such frame.\n");
                return;
            }else{
            newLayer curLayer4 = pop(clients[si].incoming_que[location-1],&top);    
            newLayer curLayer3 = pop(clients[si].incoming_que[location-1],&top); 
            newLayer curLayer2 = pop(clients[si].incoming_que[location-1],&top); 
            newLayer curLayer1 = pop(clients[si].incoming_que[location-1],&top); 

            printf("Current Frame #%d on the incoming queue of client %s\n",location,id);
            printf("Carried Message: \"%s\"\n",curLayer1.message_chunk);

            printf("Layer 0 info: Sender ID: %s, Receiver ID: %s\n",curLayer1.sender,curLayer1.reciever);

            printf("Layer 1 info: Sender port number: %s, Receiver port number: %s\n",curLayer2.sender,curLayer2.reciever);

            printf("Layer 2 info: Sender IP address: %s,Receiver IP address: %s\n",curLayer3.sender,curLayer3.reciever);

            printf("Layer 3 info: Sender MAC address: %s, Receiver MAC address: %s\n",curLayer4.sender,curLayer4.reciever);
            printf("Number of hops so far: %d\n",curLayer4.number_of_hops);
            push(curLayer1,clients[si].incoming_que[location-1],&top);
            push(curLayer2,clients[si].incoming_que[location-1],&top);
            push(curLayer3,clients[si].incoming_que[location-1],&top);
            push(curLayer4,clients[si].incoming_que[location-1],&top);
            }
    }
      if(strcmp(inout,"out") == 0){
            
            int top = 3;
            int location = clients[si].outgoing_front;
            location = frame_number;
            int kuyruk_durum = clients[si].outgoing_tail-clients[si].outgoing_front;
            if( kuyruk_durum< 1 || kuyruk_durum < location-1 || location >4){
                printf("No such frame.\n"); 
                return;
            }else{

            newLayer curLayer4 = pop(clients[si].outgoing_que[location-1],&top);    
            newLayer curLayer3 = pop(clients[si].outgoing_que[location-1],&top); 
            newLayer curLayer2 = pop(clients[si].outgoing_que[location-1],&top); 
            newLayer curLayer1 = pop(clients[si].outgoing_que[location-1],&top); 

            printf("Current Frame #%d on the outgoing queue of client %s\n",location,id);
            printf("Carried Message: \"%s\"\n",curLayer1.message_chunk);

            printf("Layer 0 info: Sender ID: %s,Receiver ID: %s\n",curLayer1.sender,curLayer1.reciever);

            printf("Layer 1 info: Sender port number: %s, Receiver port number: %s\n",curLayer2.sender,curLayer2.reciever);

            printf("Layer 2 info: Sender IP address: %s,Receiver IP address: %s\n",curLayer3.sender,curLayer3.reciever);

            printf("Layer 3 info: Sender MAC address: %s, Receiver MAC address: %s\n",curLayer4.sender,curLayer4.reciever);
            printf("Number of hops so far: %d\n",curLayer4.number_of_hops);
            push(curLayer1,clients[si].outgoing_que[location-1],&top);
            push(curLayer2,clients[si].outgoing_que[location-1],&top);
            push(curLayer3,clients[si].outgoing_que[location-1],&top);
            push(curLayer4,clients[si].outgoing_que[location-1],&top);
            }
    }else
        printf("No such frame.\n");
}

void MESSAGE(char sender[2],char reciever[2],char * message,int client_size,newClient * clients,int NOF,char SPORT[5],char RPORT[5],char nihai_hedef[2],int max_message_size){

    printf("---------------------------------------------------------------------------------------\nCommand: MESSAGE %s %s #%s#\n---------------------------------------------------------------------------------------\nMessage to be sent: %s\n\n",sender,reciever,message,message);
    int si = getByID(sender,clients);    
     if (strcmp(getRoute(si,reciever,clients,client_size),"-")==0){
            printf("Error: Unreachable destination. Packets are dropped after %d hops!\n",0);
            return;
        }
    int riMAC = getByID(getRoute(si,reciever,clients,client_size),clients);
    int ri = getByID(reciever,clients);
     
    strcpy(nihai_hedef,reciever);

    int i;
    for(i = 0; i < NOF; i++){
        int top = -1;
        newLayer *layers  = (newLayer *)malloc((NOF+10)*sizeof(newLayer));
        
        newLayer layer;
        
        strcpy(layer.sender,clients[si].ID);
        strcpy(layer.reciever,clients[ri].ID);
        layer.message_chunk = malloc(sizeof(char)*(10+max_message_size));
        strncpy(layer.message_chunk,message+(i*((max_message_size)*sizeof(char))),max_message_size);
        layer.message_chunk[max_message_size] = '\0';
        push(layer,layers,&top);

        strcpy(layer.sender,SPORT);
        strcpy(layer.reciever,RPORT);
        push(layer,layers,&top);

        strcpy(layer.sender,clients[si].IP);
        strcpy(layer.reciever,clients[ri].IP);
        push(layer,layers,&top);

        strcpy(layer.sender,clients[si].MAC);
        strcpy(layer.reciever,clients[riMAC].MAC);
        layer.number_of_hops = 0;
        push(layer,layers,&top);

        kuyruk_ekle(clients[si].outgoing_front,&clients[si].outgoing_tail,layers,clients[si].outgoing_que,NOF);
        printf("Frame #%d\nSender MAC address: %s, Receiver MAC address: %s\n",i+1,clients[si].MAC,clients[riMAC].MAC);
        printf("Sender IP address: %s, Receiver IP address: %s\n",clients[si].IP,clients[ri].IP);
        printf("Sender port number: %s, Receiver port number: %s\n",SPORT,RPORT);
        printf("Sender ID: %s, Receiver ID: %s\nMessage chunk carried: %s\n--------\n",clients[si].ID,clients[ri].ID,layer.message_chunk);
        
    }    
}
char * getRoute(int si,char hedef[2],newClient * clients,int client_size){
    int i;
    for(i = 0; i < client_size; i++){
        if(clients[si].routes[i].bunun_icin[0] == hedef[0]){  
            return clients[si].routes[i].once_burdan;
       }
    }
}
int recursive(char from[2],char to[2],newClient *clients,int NOF){
    int si = getByID(from,clients);
    int ri = getByID(to,clients);
    int top = 4;
    int u;
    for(u = 0; u < NOF; u++){
        newLayer * tempFrame = kuyruk_al(&clients[si].outgoing_front,clients[si].outgoing_tail,clients[si].outgoing_que,NOF);
        strcpy(tempFrame[3].sender,clients[si].MAC);
        strcpy(tempFrame[3].reciever,clients[ri].MAC);
        tempFrame[3].number_of_hops++;
        printf("\tFrame #%d MAC address change: New sender MAC %s, new receiver MAC %s\n",u+1,tempFrame[3].reciever,tempFrame[3].reciever);
        kuyruk_ekle(clients[si].outgoing_front,&clients[si].outgoing_tail,tempFrame,clients[si].outgoing_que,NOF);
    }
    int t;
    for(t = 0; t < NOF; t++){
        newLayer * tempFrame =kuyruk_al(&clients[si].outgoing_front,clients[si].outgoing_tail,clients[si].outgoing_que,NOF);
        kuyruk_ekle(clients[ri].outgoing_front,&clients[ri].outgoing_tail,tempFrame,clients[ri].outgoing_que,NOF);
    }
}
void SEND(char sender[2],char nihai_hedef[2],newClient * clients,int client_size,int NOF){
    printf("----------------\n");
    printf("Command: SEND %s\n",sender);
    printf("----------------\n");
    int si = getByID(sender,clients);
    int top = 3;
    int on = clients[si].outgoing_front;
    newLayer * curframe = kuyruk_al(&on,clients[si].outgoing_tail,clients[si].outgoing_que,NOF);
    newLayer curlay  = pop(curframe,&top);
    
    int ri;
    int i;
    for(i = 0; i < client_size; i++)
        if (strcmp(clients[i].MAC,curlay.reciever)==0) 
            ri = i;
    char curReciever[2];
    char curSender[2];
    
    int t;
    for(t = 0; t < NOF; t++){
        newLayer * tempFrame =kuyruk_al(&clients[si].outgoing_front,clients[si].outgoing_tail,clients[si].outgoing_que,NOF);
       
        kuyruk_ekle(clients[ri].outgoing_front,&clients[ri].outgoing_tail,tempFrame,clients[ri].outgoing_que,NOF);
    }
    strcpy(curReciever,clients[ri].ID);
    strcpy(curSender,sender);
    i = 0;
    while(1){
        if(strcmp(nihai_hedef,curReciever)==0){
           
            printf("A message received by client %s from client %s after a total of %d hops.\n",nihai_hedef,sender,i+1);
           
           
           
           
           




int ti = getByID(nihai_hedef,clients);
int top = 3;
printf("Message: ");
int y;
for(y = 0; y < NOF; y++){

    newLayer * tempFrame = kuyruk_al(&clients[ti].outgoing_front,clients[ti].outgoing_tail,clients[ti].outgoing_que,NOF);

    newLayer curLayer4 = pop(tempFrame,&top);    
    newLayer curLayer3 = pop(tempFrame,&top); 
    newLayer curLayer2 = pop(tempFrame,&top); 
    newLayer curLayer1 = pop(tempFrame,&top); 

    printf("%s",curLayer3.message_chunk);
   
    push(curLayer1,tempFrame,&top);
    push(curLayer2,tempFrame,&top);
    push(curLayer3,tempFrame,&top);
    push(curLayer4,tempFrame,&top);
    kuyruk_ekle(clients[ti].incoming_front,&clients[ti].incoming_tail,tempFrame,clients[ti].incoming_que,NOF);
}

printf("\n");
                      
           
           
            return;
        }
        printf("A message received by client %s, but intended for client %s. Forwarding...\n",curReciever,nihai_hedef);
        strcpy(curSender,curReciever);
        
        strcpy(curReciever,getRoute(getByID(curSender,clients),nihai_hedef,clients,client_size));
        if (strcmp(curReciever,"-")==0){
            printf("Error: Unreachable destination. Packets are dropped after %d hops!",i+1);
            return;
        }

        si = getByID(curSender,clients);
        ri = getByID(curReciever,clients);
        int u;
        for(u = 0; u < 4; u++) 
        printf("\tFrame #%d MAC address change: New sender MAC %s, new receiver MAC %s\n",u+1,clients[si].MAC,clients[ri].MAC);
        
        int t;
        for(t = 0; t < NOF; t++){

            newLayer * tempFrame =kuyruk_al(&clients[si].outgoing_front,clients[si].outgoing_tail,clients[si].outgoing_que,NOF);
            kuyruk_ekle(clients[ri].outgoing_front,&clients[ri].outgoing_tail,tempFrame,clients[ri].outgoing_que,NOF);
        }
        i++;    
    }
}

int load_routing(char *commands_file,newClient * clients){
	FILE *command_file = fopen(commands_file,"r");
	if(command_file==NULL){
		printf("Unable to open file %s",commands_file);
		return 0;
	}
	char str[50];
	int i=0;
    int j = 0;
	while(fscanf(command_file,"%s",str) != EOF){
		if(strcmp(str,"-") == 0){
            i++;
            j= 0;
            fscanf(command_file,"%s",str);
        }
        strcpy(clients[i].routes[j].bunun_icin,str);
        fscanf(command_file,"%s",str);
        strcpy(clients[i].routes[j].once_burdan,str);
        j++;
		if(feof(command_file))
			break;
	}
	fclose(command_file);
    return 1;
}
int main(int argc, char const *argv[]){
    
    char client_file[30] = "a";
    strcpy(client_file,argv[1]);
    char routing_file[30] = "a";
    strcpy(routing_file,argv[2]);
    char commands_file[30] = "a";
    strcpy(commands_file,argv[3]);
    char SPORT[5] ;
    strcpy(SPORT,argv[5]);
    char RPORT[5] = "a";
    strcpy(RPORT,argv[6]);

    int client_size = get_size(client_file);
    newClient *clients  = (newClient *)malloc(client_size*sizeof(newClient));
    int max_message_size = atoi(argv[4]); 
    int cur_line_size;
    char * message;
    int devam;
    int i;
    int NOF;
    char nihai_hedef[2];

	FILE *command_file = fopen(commands_file,"r");
	if(command_file==NULL){
		printf("Unable to open file %s",commands_file);
		return 0;
	}
	char str[50];
	int i44=0;
    int j = 0;
    fscanf(command_file,"%s",str);
	while(fscanf(command_file,"%s",str) != EOF){
		
        i44++;
        if(strcmp(str,"MESSAGE")==0){
            char sender[2] = "a";
            char reciever[2] = "a";
            char * curmessage = malloc(sizeof(char)*10);
            fscanf(command_file,"%s",str);
            strcpy(sender,str);
            fscanf(command_file,"%s",str);
            strcpy(reciever,str);
            int tt = 0;
            int sayac =1;
            char character = fgetc(command_file);
            fgetc(command_file);
            while(1){
            
                character = fgetc(command_file);
                if(character == '#'){
                    curmessage[tt]='\0';
                    break;
                }
                curmessage[tt] = character;               
                curmessage = realloc(curmessage,(sizeof(char)*(tt+2)));       
                tt++;    
           }
            cur_line_size = 0;
    devam = 1;
    i = 0;
    while(devam){
        if(curmessage[i] == '\0'){
            cur_line_size = i;
            devam = 0;}
        i++;}
    NOF = cur_line_size/(sizeof(char)*max_message_size);
   
    if(NOF*max_message_size < cur_line_size)
        NOF++;
    
    for(i = 0; i < client_size; i++){
        clients[i].incoming_front = -1;
        clients[i].incoming_tail = -1;
        clients[i].outgoing_front = -1;
        clients[i].outgoing_tail = -1;
        clients[i].routes = (newRoute *)malloc(client_size* sizeof(newRoute));
        clients[i].incoming_que = (newLayer **)malloc(NOF*sizeof(newLayer*));
        int x;
        for(x = 0; x < NOF; x++)
           clients[i].incoming_que[x] = (newLayer*)malloc (4 * sizeof(newLayer));

        clients[i].outgoing_que = (newLayer **)malloc(NOF*sizeof(newLayer*));
        for(x = 0; x < NOF; x++)
           clients[i].outgoing_que[x] = (newLayer*)malloc (4 * sizeof(newLayer));
    }
        if(client_size == 0)
            return 1;
        get_client(client_file,clients);
        load_routing(routing_file,clients);
        MESSAGE(sender,reciever,curmessage,client_size,clients,NOF,SPORT,RPORT,nihai_hedef,max_message_size);
        free(curmessage);
        }
        else if(strcmp(str,"SHOW_FRAME_INFO")==0){
           char aaa[2] = "a";
           char bbb[2] = "a";
           fscanf(command_file,"%s",str);
           char id[2] = "a";
           strcpy(id,str);
           fscanf(command_file,"%s",aaa);
           char inout[4] = "a";
           strcpy(inout,aaa);
           fscanf(command_file,"%s",bbb);
           int frame_number;
           frame_number = atoi(bbb);
           SHOW_FRAME_INFO(id,inout,frame_number,clients,NOF);    
        }
        else if(strcmp(str,"SHOW_Q_INFO")==0){
            char ccc[2] = "a";
            char qqq[2] = "a";
            fscanf(command_file,"%s",qqq);

            char id[2] = "a";
            strcpy(id,qqq);
            fscanf(command_file,"%s",ccc);
                
            char inout[4] = "a";
            strcpy(inout,ccc);
            SHOW_Q_INFO(id,inout,clients,NOF);
        }
        else if(strcmp(str,"SEND")==0){
            char sender[2] = "a";
            fscanf(command_file,"%s",sender);
            SEND(sender,nihai_hedef,clients,client_size,NOF);
        }
        else if(strcmp(str,"PRINT_LOG")==0){
           
        }
        else{
           printf("Invalid command\n");
        }

		if(feof(command_file))
			break;
	}
    free(clients);
    
	fclose(command_file);
    return 0;}
