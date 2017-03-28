
#include "map.h"

void MakeMapFromFile(FILE *f, unsigned int map[15][20]){

    unsigned int i, j;
    unsigned int temp[15][20];

    for(i = 0; i < 15; i++){
        for(j = 0; j < 20; j++){
            if(fscanf(f, "%u", &temp[i][j]) == EOF){
                FILE_ERROR(FILE_READ_ERROR, "Error in reading map from file");
            }
        }
    }

    /*can't initialise a 2D array like this after declaration so copying it over*/
    for(i = 0; i < MAP_WIDTH; i++){
        memcpy(&map[i], &temp[i], sizeof(temp[0]));
    }

    return;

}

FILE *OpenFile(char *filename){

    FILE *f_ptr = NULL;

    f_ptr = fopen(filename, "r");

    if (f_ptr == NULL){
        /*fprintf(stderr, "Error in opening file, %s\n", strerror(errno));*/
        FILE_ERROR(FILE_OPEN_ERROR, "File cannot be opened");
    }

    return f_ptr;

}

unsigned int CloseFile(FILE *f_ptr){

    if(fclose(f_ptr) != 0){
        FILE_ERROR(FILE_NOT_CLOSED, "Issue closing file");
    }

    return 0;

}

