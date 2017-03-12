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
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//representasi graf:
// 0 1 2  3 4 5 6 7 8 9 10 11
// A 0 11 _ _ _ _ _ _ _  _  B _ _ _ _ _


struct street {
  unsigned char start;
  unsigned char end;
  char* streetName;
} ;

int length=100;
int streetLength = 200;
#define COUNT 10
struct street* streetData;
unsigned char* streetConnection;
unsigned short streetConnCounter = 0;
unsigned char* array;
unsigned char* read;
unsigned char comparator[1];
unsigned short currFree = 1;
int streetInfoCounter = 0;
unsigned short currPrint = 0;

int isValidTree = 1;

unsigned short getIndex (unsigned short idx);

void putIndex (unsigned short idx, unsigned short start);
void writeArrayToFile();
void readFile();
void printArray ();
void printTree(unsigned short index, int space);
void insertStreet (unsigned short start, unsigned short end);
int childCount(unsigned short idxStart);
unsigned short getChildPosition(unsigned short idxStart);
void initializeNode();
unsigned short searchIdx (unsigned short input);
void insertGraphFromFile();
void insertStreetData (unsigned short start, unsigned short end, char streetName[30]);
void writeStreetConnection();

int main(int argc, char** argv) {
  array = (unsigned char*) malloc (length * sizeof(unsigned char));
  streetData = (struct street*) malloc (streetLength * sizeof(struct street));

  int i;
  for(i=0; i<length; i++){
    array[i] = 0;
  }

  for(i=0; i<streetLength; i++){
    streetData[i].start = 0;
    streetData[i].end = 0;
    streetData[i].streetName = 0;
  }

  printf(" ---------------------------------- \n");
  insertGraphFromFile();

  FILE *fp = fopen("arrayLiteral.txt","w");

  for(i=0; i<length; i++){
    fprintf (fp, "arr[%d]: %u\n", i, array[i]);
    // printf("arr[%d]: %u\n", i, array[i]);
  }
  fclose(fp);
  //
  // insertStreetData(62, 63, "ivana");
  writeArrayToFile();
  writeStreetConnection();

  readFile();
  // printf("GetIndex array[239]: %d \n", getIndex(239));
  return (EXIT_SUCCESS);
}

void writeStreetConnection(){
  unsigned char* streetConnectionData = (unsigned char*) malloc (streetLength*3 * sizeof(unsigned char));

  int i;
  for(i=0; i<streetLength*3; i++){
    streetConnectionData[i] = 0;
  }

  unsigned short scdataCounter = 0;
  FILE *fp = fopen("connectionNode.txt","wb");

  i = 0;
  // for(i=0; i<streetInfoCounter; i++){
  //   printf("StreetData - before write: %u, %u, %s \n", streetData[i].start, streetData[i].end, streetData[i].streetName);
  // }

  i = 0;
  while(streetData[i].start != 0){
    printf("StreetData - writeConnection: %u, %u, %s \n", streetData[i].start, streetData[i].end, streetData[i].streetName);
    streetConnectionData[scdataCounter] = streetData[i].start;
    streetConnectionData[scdataCounter+1] = streetData[i].end;
    streetConnectionData[scdataCounter+2] = scdataCounter/3;
    // printf("streetConnectionData[%d]: %u, ",  scdataCounter, streetConnectionData[scdataCounter]);
    // printf("streetConnectionData[%d]: %u, ",  scdataCounter, streetConnectionData[scdataCounter+1]);
    // printf("streetConnectionData[%d]: %u \n",  scdataCounter, streetConnectionData[scdataCounter+2]);
    char* tempPrint = streetData[i].streetName;
    // printf("nama jalan: %s \n", tempPrint);
    scdataCounter += 3;
    i++;
  }
  printf("File saved! File name: connectionStreet.txt \n");

  fwrite(streetConnectionData, sizeof(unsigned char), scdataCounter, fp);
  printf("File saved! File name: connectionNode.txt \n");
  fclose(fp);

}

void insertStreetData (unsigned short _start, unsigned short _end, char* _streetName){
	if(streetInfoCounter < streetLength)
	{
		streetData[streetInfoCounter].start = _start;
		streetData[streetInfoCounter].end = _end;
    streetData[streetInfoCounter].streetName = (unsigned char*) malloc (30 * sizeof(unsigned char));
		streetData[streetInfoCounter].streetName = _streetName;
		streetInfoCounter++;
		printf("StreetData - insert: %u, %u, %s \n", streetData[streetInfoCounter-1].start, streetData[streetInfoCounter-1].end, streetData[streetInfoCounter-1].streetName);
	}
	else{
		streetLength = streetLength*2;
	    printf("Re-alloc! StreetData size now: %d\n", streetLength);
	    streetData = (struct street*) realloc(streetData, streetLength);
      int i;
      for(i=streetLength/2; i<streetLength; i++){
        streetData[i].start = 0;
        streetData[i].end = 0;
        streetData[i].streetName = "";
      }
	    insertStreetData(_start, _end, _streetName);
	}
}

unsigned short getIndex (unsigned short idx){
    return ((array[idx] << 8) | array[idx+1]);
}

void insertGraphFromFile(){
   FILE* file;
   FILE *fp1 = fopen("connectionStreet.txt", "w");
   char line[25];
   char start[3]; start[0] = ' '; start[1] = 'a'; start[2] = 'a';
   char end[3]; end[0] = ' '; end[1] = 'a'; end[2] = 'a';
   size_t len = 0;
   ssize_t read;
   char streetName[30];

   file = fopen("connection.txt", "r");

   while (!feof (file)) {
     unsigned short startS = 0;
     unsigned short endS = 0;
     fscanf(file,"%s %s %s \n",&start,&end, &streetName);
     // printf("read File: %s, %s, %s \n", start, end, streetName);
     int i=0;

       if((int) start[1] == 0){
        //  printf("here, 1 digit start \n");
         startS = start[0] - '0';
       } else{
         startS = (start[0]-'0') * 10 + (start[1]-'0');
       }
       if( (int) end[1] == 0) {
        //  printf("here, 1 digit end \n");
         endS = end[0] - '0';
       }
       else{
         endS = (end[0]-'0') * 10 + (end[1]-'0');
       }

       printf("Inserting %d to %d \n", startS, endS);
       insertStreet(startS, endS);
       insertStreetData(startS, endS, streetName);

       fprintf (fp1, streetName);
       fprintf(fp1, "\n");
   }
 fclose(file);
 fclose(fp1);
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

void insertStreet (unsigned short start, unsigned short end){
    // printf("start: %d; end: %d \n", start, end);
    unsigned short idxStart = searchIdx(start);
    unsigned short idxEnd = searchIdx(end);
    // printf("IdxStart: %d; IdxEnd: %d \n", idxStart, idxEnd);
    // printf("currFree before insert: %d \n", currFree);

    if(idxStart == 0){
      initializeNode();
      // printf("inserting new point: %d \n", start);
      idxStart = currFree;
      array[currFree] = start;
      currFree += 11;

      //node end sudah ada di graf
      if(idxEnd > 0)
        putIndex(idxEnd, idxStart+1);
      else{ //node end belum ada di graf
          // printf("inserting new point: %d \n", end);
          initializeNode();
          array[currFree] = end;
          putIndex(currFree, idxStart+1);
          currFree += 11;
      }
    } else{ //1. cari letak start, cari posisi anak, masukkan
      // printf("childCount: %d \n", childCount(idxStart));
      if(childCount(idxStart) >= 5)
      {
        printf("Maskimal jumlah tetangga adalah 5! \n");
      }
      else{ //anak masih bisa masuk
        // printf("here, end: %d ; idxEnd: %d \n", end, idxEnd);
        if(idxEnd > 0)
        {
          //  printf("inserting end: %d, getchildPostition: %d , inserting at: %d \n", end, getChildPosition(idxStart));
           putIndex(idxEnd, getChildPosition(idxStart));
        }
        else{ //node end belum ada di graf
            // printf("inserting new point: %d \n", end);
            initializeNode();
            array[currFree] = end;
            // printf("idxStart: %d; getChildPosition: %d \n", idxStart, getChildPosition(idxStart));
            putIndex(currFree, getChildPosition(idxStart));
            currFree += 11;
        }
      }
    }

    // printf("currFree after insert: %d \n", currFree);
}

int childCount(unsigned short idxStart){
  int i; int childCounter = 0;
  for(i=idxStart+1; i<idxStart+11; i+=2){
    if(getIndex(i) != 0)
      childCounter++;
  }
  return childCounter;
}

unsigned short getChildPosition(unsigned short idxStart){
  // printf("getChildPosition; idxStart: %d \n", idxStart);
  unsigned short i;
  // for(i=idxStart; i<idxStart+11; i++){
  //   printf("array[%d]: %u \n", i, array[i]);
  // }
  for(i=idxStart+1; i<idxStart+11; i+=2){
    // printf("getIndex(array[%d]): %d \n", i, getIndex(i));
    if(getIndex(i) == 0)
      return i;
  }
}

void initializeNode(){
  if(currFree+11 >= length){
    length = length*2;
    printf("Re-alloc! size now: %d\n", length);
    array = (unsigned char *) realloc(array, length);
    int i;
    for(i=length/2; i<length; i++){
      array[i] = 0;
    }
  }
  int i;
  for(i = currFree; i<currFree+11; i++){
    array[i] = 0;
  }
}

unsigned short searchIdx (unsigned short input){
  char stop = '0';
  comparator[0] = input;
  unsigned short checker = 1;

  while(stop == '0' && checker < length){
     if(array[checker] != comparator[0]){
       checker += 11;
     } else{
       stop = '1';
     }
   }

  if(checker >= length)
    return 0;
  else return checker;
}
