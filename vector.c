
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
//TODO debug malloc(): corrupted top size

//given memory size and vector, make vector.
void init(Vector *vector, int memorySize) {
    vector->memorySize = memorySize;
    vector->size = 0;
    vector->array = malloc(vector->memorySize*sizeof(int));
}

void print(Vector *vector){
    for (int i = 0; i < vector->size; i++) {
        int printed_num = vector->array[i];
        printf("%i",printed_num);
    }
    printf("\n");
}


int insert(Vector *vector, int location, int value) {

    //test for invalid location
    if(location < 0 || location > vector->size){
        return 0;
    }

    //If future size is bigger
    if((sizeof(value) + sizeof(*vector)) > vector->memorySize){
        //update the recorded memory size.
        vector->memorySize = vector->memorySize*2;

        //allocate a new array in memory with updated memorySize and name the pointer newArray.
        int* newArray = (int*) malloc(vector->memorySize*sizeof(int));

        //copy over from old to new.
        for(int i = 0; i<vector->size; i++){
            newArray[i] = vector->array[i];
        }
        
        //now that it's copied over, free it.
        free(vector->array);

        //update pointer to the new array.
        vector->array = newArray;
    }

    //actual insert with correct input AND memory size.
    //from the last one + 1 = size, copy over the previous value.
    //when j = location, stop.
    for(int j = vector->size; j > location; j--){
        vector->array[j]=vector->array[j-1];
    }
    //then, set the location to the value.
    vector->array[location] = value;

    //update size.
    vector->size++;
    return 1;
}

int get(Vector *vector, int location, int *value){
    if(location == 0 || location >= vector->size){
        return 0;
    }
    *value = vector->array[location];
    return 1;
}

void cleanup(Vector *vector){
    free(vector->array);
}

int delete(Vector *vector, int location){
    if(location < 0 || location >= vector->size){
        return 0;
    }
    for(int i = location; i < vector->size-1; i++){
        vector->array[i]=vector->array[i+1];
    }
    vector->size--;
    return 1;
}   