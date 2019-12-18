#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int findtreasure(int *map, int linelen, int columnlen,  int *keymap, int n, int cursorx, int cursory, char *argv[]){

	int i,j,ki=0,kj,result=0;
	for(i=cursorx;i<(cursorx+n);i++){
		kj=0;
		for(j=cursory;j<cursory+n;j++){
			result+=*(map+(i*linelen)+j) * *(keymap+(ki*n)+kj);
			kj++;
		}
		ki++;
	}
	int resultmod = ((result % 5) + 5) % 5;
	
	// Here we are writing the outputs to the output file
	FILE *outputfile = fopen(argv[5],"a");
	fprintf(outputfile,"%d,%d:%d",cursory+n/2,cursorx+n/2,result);
	if(resultmod){
		fprintf(outputfile,"\n");
	}
	fclose(outputfile);
	
	switch(resultmod){
		case 0:
					//	You found the Treasure!!
			return 0;
		case 1:					//	up
			if(cursorx-n >= 0){
				cursorx -= n;
			}
			else{							//	down
				cursorx += n;
			}	
			break;
		case 2:					//	down
			if(cursorx+n < columnlen){
				cursorx += n;
			}
			else{							//	up
				cursorx -= n;
			}
			
			break;
		case 3:					//	rigt
			if(cursory+n < linelen){
				cursory += n;
			}
			else{							//	left
				cursory -= n;
			}
			
			break;
		case 4:					//	left
			if(cursory-n >= 0){
				cursory -= n;
			}
			else{							//	right
				cursory += n;
			}
			break;
	}
	return findtreasure(map,linelen,columnlen,keymap,n,cursorx,cursory,argv);
	
}

int main(int argc, char *argv[]){
	
	char *token = strtok(argv[1],"x");
	int linelen = atoi(token);
	token = strtok(NULL,"x");
	int columnlen = atoi(token);
	
	
	FILE *mapFile = fopen(argv[3],"r");		// It is opening map file.
	
	if(mapFile == NULL) {					// It will terminate the program if it cannot open file.
		printf("Unable to open map file");
		return 0;
	}
	// we are starting to read file from here.
	int m,counter=0;
	int *map = (int *) malloc (1*sizeof(int));
	char str[1];
	while(fscanf(mapFile, "%s", str) != EOF){
		
		map = realloc(map,(counter+1)*sizeof(int *));
		*(map+counter) = atoi(str);
		
		counter++;
		if(feof(mapFile)){
			break;
		}
	}
	fclose(mapFile);				// Let's close the map file, we don't need it anymore.
	
	columnlen=counter/linelen;
	
	FILE *keymapfile = fopen(argv[4],"r");			//	we gonna read KeyMapMatrix
	
	if(keymapfile == NULL){
		printf("Unable to open key map file");
		return 0;
	}
	
	int keycounter=0,n=atoi(argv[2]);
	int *keymap = (int *) malloc (1 * sizeof(int));
	
	while(fscanf(keymapfile, "%s", str) != EOF){				// read value by value with fscanf
		keymap = realloc(keymap,(keycounter+1)*sizeof(int *));
		*(keymap+keycounter) = atoi(str);
		keycounter++;
	}
	fclose(keymapfile);

	
	int cursorx=0,cursory=0;
	FILE *outputfile = fopen(argv[5],"w+");
	fclose(outputfile);
	int result = findtreasure(map,linelen,columnlen,keymap,n,cursorx,cursory,argv);
	free(keymap);
	free(map);
	return 0;
}