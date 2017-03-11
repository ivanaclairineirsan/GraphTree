// C++ program to print all paths from a source to destination.
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct street {
  unsigned char start;
  unsigned char end;
  char streetName[30];
} ;

// A directed graph using adjacency list representation
// Prints all paths from 's' to 'd'
unsigned char* array;
unsigned char** alternativePath;
street* streetData;
unsigned short length = 100;
unsigned short pathLength = 50;
unsigned short altPathIdx = 0;
unsigned short getIndex (unsigned short idx);

int fsize(char* file);
void readFile();
unsigned short countNode(unsigned char* input);
unsigned short* getChild (unsigned char start);
void printAllPaths(unsigned char s, unsigned char d);
void printAllPathsUtil(unsigned char u, unsigned char d, bool visited[],
							unsigned char path[], unsigned short &path_index);


// Driver program
int main()
{
  // streetData = (street*) malloc (100 * sizeof(street));
  readFile();
	unsigned char start = 16; unsigned char goal = 61;
	// printf("GetIndex array[299]: %d \n", getIndex(299));
	cout << "Following are all different paths from ";
  printf("%u to %u \n", start, goal);
	printAllPaths(start, goal);

  for(int i=0; i<altPathIdx; i++){
    // cout << "alternativePath[" << i << "].sizeof: " << sizeof(alternativePath[i]) << endl;
    for (int j = 1; j<=alternativePath[i][0]; j++)
      printf("%u ", alternativePath[i][j]);
    cout << endl;
  }
	return 0;
}

unsigned short getIndex (unsigned short idx){
    return ((array[idx] << 8) | array[idx+1]);
}

void readFile(){
    char* filePath = (char*) "arrayFile.txt";
    printf("fileSize (read): %d\n", fsize(filePath));
    length = fsize(filePath);
    FILE *file = fopen(filePath, "rb");
    int fileSize = fsize(filePath);
    array = (unsigned char*) malloc (sizeof(unsigned char) * fileSize);
    fread(array, sizeof(unsigned char), fileSize, file );
    fclose(file);
    // cout << "Node: " << countNode(array) << endl;
    // printf("--- READ FILE --- \n--- Print isi file --- \n");

    // printArray();
}

int fsize(char* file)
{
    FILE * f = fopen(file, "r");
    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    fclose(f);
    return len;
}

unsigned short countNode(unsigned char* input){
  unsigned short counter = 0;
  unsigned short idx = 1;
  while(idx < length){
    if(input[idx] != 0){
      counter++;
      idx+=11;
    } else return counter+1;
  }
  return counter+1;
}

unsigned short* getChild (unsigned char start){
	// printf("masuk getChild, start: %u \n", start);
	unsigned short* children = (unsigned short*) malloc (5 * sizeof(unsigned short));
  int i;
	for(i = 0; i<5; i++){
		children[i] = '0';
	}
	unsigned short index = 1;
	char stop = '0';
	while(stop == '0' && index < length){
		if(array[index] != start){
			index+=11;
		}
		else{
			// printf("index %u: %d \n", start, index);
			for(i=0; i<5; i++){
					children[i] = getIndex(index+(i*2)+1);
					// printf("getIndex(%d): %d \n", index+(i*2)+1,  getIndex(index+(i*2)+1));
			}
			stop = '1';
		}
	}
	return children;
}

void printAllPaths(unsigned char s, unsigned char d) {
  unsigned short V = countNode(array);
	// Mark all the vertices as not visited
	bool *visited = new bool[V];

	// Create an array to store paths
	unsigned char *path = new unsigned char[V];

  alternativePath = (unsigned char**) malloc(pathLength * sizeof(unsigned char*));
  for (int i = 0; i < pathLength; i++ )
  {
    alternativePath[i] = (unsigned char*) malloc(sizeof (unsigned char) * V);
  }

	unsigned short path_index = 0; // Initialize path[] as empty

	// Initialize all vertices as not visited
	for (int i = 1; i <= V; i++)
		visited[i] = false;

	// Call the recursive helper function to print all paths
	printAllPathsUtil(s, d, visited, path, path_index);
}

void printAllPathsUtil(unsigned char u, unsigned char d, bool visited[],
							unsigned char path[], unsigned short &path_index)
{
  // printf("printAllPathsUtil -- u: %u, d: %u \n", u, d);
	// Mark the current node and store it in path[]
	visited[u] = true;
	path[path_index] = u;
	path_index++;
	// If current vertex is same as destination, then print
	// current path[]
	if (u == d)
	{
    if(altPathIdx == pathLength){
      pathLength = pathLength*2;
      printf("Re-alloc pathLength! size now: %d\n", pathLength);
      alternativePath = (unsigned char **) realloc(alternativePath, pathLength);
      int V = countNode(array);
      for(int i=pathLength/2; i<pathLength; i++){
        alternativePath[i] = (unsigned char*) malloc(sizeof (unsigned char) * (V+1));
      }
    }

    for(int i=1; i<=path_index; i++){
      alternativePath[altPathIdx][i] = path[i-1];
    }
    alternativePath[altPathIdx][0] = path_index;

    altPathIdx++;
    //
  //   for (int i = 1; i<=alternativePath[altPathIdx-1][0]; i++)
		// 	printf("-- %u ", alternativePath[altPathIdx-1][i]);
		// cout << endl;

		// for (int i = 0; i<path_index; i++)
		// 	printf("%u ", path[i]);
		// cout << endl;
	}
	else // If current vertex is not destination
	{
		// printf("vertex is not destination, start: %u \n", u);
    unsigned short* children = getChild(u);
		// Recur for all the vertices adjacent to current vertex
    unsigned short i;
		for (i = 0; i < 5; ++i)
		{
      // printf("node: %u, child[%d]: %d \n", u, i, children[i]);
      if (!visited[array[children[i]]] && children[i]!=0 && path_index < 10)
  			{
          printAllPathsUtil(array[children[i]], d, visited, path, path_index);
        }
    }
	}

	// Remove current vertex from path[] and mark it as unvisited
	path_index--;
	visited[u] = false;
}
