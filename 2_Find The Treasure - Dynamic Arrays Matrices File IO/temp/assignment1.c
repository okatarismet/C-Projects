#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[]){
	
	

	
	FILE *mapFile = fopen("mapmatrix1.txt","r");		// It is opening map file.
	
	if(mapFile == NULL) {					// It will terminate the program if it cannot open file.
		printf("Unable to open map file");
		return 0;
	}

	int linel=0;
	int *map = (int *) malloc (1*sizeof(int));
	char str[1];
	while(fscanf(mapFile, "%s", str) != EOF){
		map = realloc(map,(linel+1)*sizeof(int *));
		printf(str);
		linel++;
		if(feof(mapFile)){
			break;
		}
	}
	fclose(mapFile);				// Let's close the map file, we don't need it anymore.
	free(map);
	return 0;
}