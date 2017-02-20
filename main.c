#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* array;
unsigned char comparator[1];
unsigned short currFree = 0;
unsigned short currPrint = 0;

int main(int argc, char** argv){

  array = (unsigned char *) malloc (30);


  int i = 0;

  for(int i=0; i<30; i++){
    array[i] = 0;
  }

  array[0] = 'a';
  array[1] = 6;
  array[2] = 12;
  array[3] = 0;

  for(i = 0; i<30; i++){
    printf("%u ", array[i]);
  }


  return 0;
}

void insertNode (unsigned char node[5]){

}

unsigned char* findPath (unsigned char start, unsigned char end){

  return 0;
}
