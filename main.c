/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c 
 * Author: ivana
 *
 * Created on February 8, 2017, 11:33 AM
 */

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
unsigned char comparator[1];
unsigned short currFree = 0;
unsigned short currPrint = 0;

int isValidTree = 1;

unsigned short getIndex (unsigned short idx);

void putIndex (unsigned short idx, unsigned short start);
void writeArrayToFile();
void readFile();
void printArray ();
void printTree(unsigned short index, int space);
void insertChar (char key, int lastMatch);
void insertString(char* input);

int main(int argc, char** argv) {
  array = (unsigned char*) malloc (length * sizeof(unsigned char));

  int i;
  for(i=0; i<length; i++){
    array[i] = 0;
  }
    
    insertString("uda");
    // printf("sizeOf(array): %d\n", sizeof(array));
    insertString("udin");
    // printf("sizeOf(array): %d\n", sizeof(array));
    insertString("abah");
    insertString("saya");
    insertString("makan");
    insertString("lala");

    if(isValidTree)
    {
      writeArrayToFile();
      readFile();

      // printTree(0,0);
  }

  return (EXIT_SUCCESS);
}

unsigned short getIndex (unsigned short idx){
    return (array[idx] << 8) | array[idx+1];
}

void putIndex (unsigned short idx, unsigned short start){
    array[start] = idx >> 8;
    array[start+1] = idx;
}

void writeArrayToFile(){
    FILE *file = fopen("arrayFile.txt", "wb");
    fwrite(array, sizeof(unsigned char), length, file);
    fclose(file);
    printf("File saved! File name: arrayFile.txt \n");
    printf("fileSize (write): %d\n", fsize("arrayFile.txt"));
}

void readFile(){
    // printf("fileSize (read): %d\n", fsize("arrayFile.txt"));
    FILE *file = fopen("arrayFile.txt", "rb");
    int fileSize = fsize("arrayFile.txt");
    read = (unsigned char*) malloc (sizeof(unsigned char) * fileSize);
    fread(read, sizeof(unsigned char), fileSize, file );
    fclose(file);
    printf("--- READ FILE --- \n--- Print isi file --- \n");
    printArray();
}

int fsize(char* file)
{
    FILE * f = fopen(file, "r");
    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    fclose(f);
    return len;
}

void printArray(){
    int i;
    for(i=0; i< currFree; i++)
    {
      printf("arr[%d]: %u \n", i, read[i]);
    }   
}

void printTree(unsigned short index, int space){
   // // Base case
   //  printf("arrayTree[%d]: %u \n", index, array[index]);
    if (array[index] == 0)
        printf("");
 
    // Increase distance between levels
    space += COUNT;
    // Process right child first
    if(getIndex(index+3) > 0)
      printTree(getIndex(index+3), space);
    else {
      printf("");
    }
    // Print current node after space
    // count
    printf("|");
    int i;
    for (i = COUNT; i < space; i++)
        printf("-");
    printf("%c\n", (char) array[index]);
 

    // Process left child
    if(getIndex(index+1) > 0)
      printTree(getIndex(index+1), space);
    else {
      printf("");
    }
 
}

void insertChar(char key, int neighborIdx){
    // printf("free before: %d \n", currFree);
    if(currFree < length)
    {
      array[currFree] = key;
      putIndex(0, (neighborIdx*2)+1);
      currFree += 11;
   }
   else{
     length = length*2;
     printf("Re-alloc! size now: %d\n", length);
     array = (unsigned char *) realloc(array, length);
     insertChar(key, neighborIdx);
   }
    // printf("free after: %d \n", currFree);
}

void insertString(char* input){
    int idxInput = searchIdx(input[0]);
    if(idxInput == -1){
      int inputSize = (int) strlen(input);
      int i;

      int currHead = currentFree;
      insertNewPoint(input[i]);

      for(i=1; i<inputSize; i++){
        int idxChild = searchIdx(input[i]);
        if(idxChild == -1){
          insertNewPoint(input[i]);
        }
        else{
          insertChild(currHead, idxChild);
        }
      }
    } else{
      int inputSize = (int) strlen(input);
      int i;

      for(i=1; i<inputSize; i++){
        int idxChild = searchIdx(input[i]);
        if(idxChild == -1){
          insertNewPoint(input[i]);
        }
        else{
          insertChild(idxInput, idxChild);
        }
      }
    }
}

void insertChild(unsigned short idxInput, unsigned short childAddress){
  char stop = '0';
  unsigned short childIdx = 1; //{1,3,5,7,9}

  while (stop == '0' && childIdx < 10){
    unsigned short neighbor = getIndex(idxInput+childIdx);
    if(neighbor == 0){
      stop = '1';
    }
    else childIdx+2;
  }
  putIndex(childAddress, idxInput+childIdx);
}

void insertNewPoint(char input){
  if(currFree < length)
    {
      array[currFree] = key;
      int i;
      for(int i=1; i<10; i+=2)
      {
        putIndex(0, currFree+i);
      }
      currFree += 11;
   }
   else{
     length = length*2;
     printf("Re-alloc! size now: %d\n", length);
     array = (unsigned char *) realloc(array, length);
     insertNewPoint(input);
   }
}

int searchIdx (unsigned char input){
  char stop = '0';
  comparator[0] = input;
  unsigned short checker = 0;

  while(stop == '0' && checker < length){
     if(array[checker] != comparator[0]){
       checker += 11;
     } else{
       stop = '1';
     }
   }

  if(checker > length)
    return -1;
  else return checker;
}