#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[]){
	
	
	int lineLen, numofLine,m;
	
	FILE *mapFile = fopen("mapmatrix1.txt","r");		// It is opening map file.
	
	if(mapFile == NULL) {					// It will terminate the program if it cannot open file.
		printf("Unable to open map file");
		return 0;
	}
	// we are starting to read file from here.
	int counter=0,isLine=0,linelen=0,columnlen=0;
	int *map = (int *) malloc (1*sizeof(int));
	char str[1];
	while(fscanf(mapFile, "%s", str) != EOF){
		
		map = realloc(map,(counter+1)*sizeof(int *));
		*(map+counter) = atoi(str);
		
 		if(isLine == 0){ // Program learn the line number capacity. After that program will never execute that if block again
			if( atoi(str) == 0){
				linelen++;
			}
			else{
				linelen--;
				isLine = 1;
			}
			
		}
		
		counter++;
		if(feof(mapFile)){
			break;
		}
	}
	fclose(mapFile);				// Let's close the map file, we don't need it anymore.
	
	columnlen=counter/linelen;
	
	for(m=0;m<counter;m++){			// draw map
		printf("%d ",*(map+m));
		if(m%linelen==linelen-1){
			printf("\n");
		}
	}
	printf("succeed %d %d\n",linelen,counter);
	
	FILE *keymapfile = fopen("keymatrix1.txt","r");			//	we gonna read KeyMapMatrix
	
	if(keymapfile == NULL){
		printf("Unable to open key map file");
		return 0;
	}
	
	int keycounter=0,n;
	int *keymap = (int *) malloc (1 * sizeof(int));
	
	while(fscanf(keymapfile, "%s", str) != EOF){				// read value by value with fscanf
		keymap = realloc(keymap,(keycounter+1)*sizeof(int *));
		*(keymap+keycounter) = atoi(str);
		keycounter++;
	}
	fclose(keymapfile);
	for(m=0;m<keycounter/2;m++){					// evalute keymatrix's n value
		if(keycounter == (m*m)){
			break;
		}
	}
	n = m;
	printf("succeed %d %d",n,keycounter);
	for(m=0;m<keycounter;m++){						//draw keymap
		printf("%d ",*(keymap+m));
		if(m%n==n-1){
			printf("\n");
		}
	}
	
	int cursorx=0,cursory=0,result=0;
	while(1){
		int i,j;
		for(i=cursorx;i<(cursorx+n);i++){
			for(j=cursory;j<cursory+n;j++){
				result+=*(map+(i*linelen)+j) * *(keymap+(i*n)+j);
				printf("%d	%d\n",*(map+(i*linelen)+j),*(keymap+((i*n)%n)+(j%n)));
			}
		}
		result %= 5;
		if(result==0){
			printf("You found the Treasure!!");
			break;
		}
		else if(result==1){			//	Go up.
			printf("Up\n");
			cursorx += n;
		}
		else if(result==2){			//	Go down.
			printf("Down\n");
			cursorx -= n;
		}
		else if(result==3){			//	Go right.
			printf("Right\n");
			cursory += n;
		}
		else if(result==4){			//	Go left.
			printf("Left\n");
			cursory -= n;
		}
	}
	
		
	
	
	free(keymap);
	free(map);
	return 0;
}
