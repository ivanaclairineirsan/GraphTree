#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//representasi graf: 
// 0 1 2  3 4 5 6 7 8 9 10 11
// A 0 11 _ _ _ _ _ _ _  _  B _ _ _ _ _ 

int length=100;
#define COUNT 10
unsigned char* array;
unsigned char* read;


// graf: 
// 0 1  2 3 4 5 6  7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23
// A 6 12 0 0 0 B 18 0 0  0  0  C  0  0  0  0  0  D  0  0  0  0  0

int main(){
	array = (unsigned char*) malloc (length * sizeof(unsigned char));
	int i=0;
	for(i = 0; i<24; i++){
		array[i] = 0;
	}
	array[0] = 'A'; array[1] = 6; array[2] = 12;
	array[6] = 'B'; array[7] = 18; array[12] = 'C'; array[18] = 'D';

	for(i = 0; i<24; i++){
		printf("arr[%d]: %u \n", i, array[i]);
	}
}