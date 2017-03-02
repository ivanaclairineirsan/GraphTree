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
void insertStreet (unsigned short start, unsigned short end);

int main(int argc, char** argv) {
  array = (unsigned char*) malloc (length * sizeof(unsigned char));

  int i;
  for(i=0; i<length; i++){
    array[i] = 0;
  }


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

void insertStreet (unsigned char start, unsigned char end){
    int idxStart = searchIdx(start);
    int idxEnd = searchIdx(end);

    if(idxStart == -1){
      initializeNode();
      idxStart = currFree;
      array[currFree] = start;
      currFree += 11;

      //node end sudah ada di graf
      if(idxEnd > -1)
        putIndex(idxEnd, idxStart+1);
      else{ //node end belum ada di fraf
          initializeNode();
          array[currFree] = end;
          putIndex(end, currFree+1);
          currFree += 11;
      }
    } else{ //1. cari letak start, cari posisi anak, masukkan
      if(childCount(idxStart) > 5)
        printf("Maskimal jumlah tetangga adalah 5 \n");
      else{ //anak masih bisa masuk
        putIndex(end, getChildPosition(idxStart));
      }
    }
}

int childCount(int idxStart){
  int i; int childCounter = 0;
  for(i=idxStart+1; i<11; i+=2){
    if(array[i] != 'a')
      childCounter++;
  }
  return childCounter;
}

unsigned short getChildPosition(int idxStart){
  int i;
  for(i=idxStart+1; i<11; i+=2){
    if(array[i] == 'a')
      return i;
  }
}

void initializeNode(){
  if(currFree+11 >= length){
    length = length*2;
    printf("Re-alloc! size now: %d\n", length);
    array = (unsigned char *) realloc(array, length);
  }
  int i;
  for(i = currFree; i<currFree+11; i++){
    array[i] = 'a';
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
