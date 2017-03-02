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
unsigned char* path;
unsigned short pathCounter = 0;
unsigned char* visited;
unsigned short visitedCounter = 0;

unsigned short levelCounter = 0;

unsigned char* toProcess;
char isFound = '0';

unsigned char** bufferChild;
unsigned short* childCounter;
unsigned short* childNumber;

unsigned char* findPath (unsigned char start, unsigned char goal, char isFound);
unsigned char* getChild (unsigned char start);
char isVisited (unsigned char input, unsigned char* list);
short countChild (unsigned char* children);
void removeFromPath(unsigned char start);
// graf:
// 0 1  2 3 4 5 6  7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23
// A 6 12 0 0 0 B 18 0 0  0  0  C  0  0  0  0  0  D  0  0  0  0  0

int main(){
	int i=0;

	bufferChild = (unsigned char**) malloc (length * sizeof(unsigned char*));
	for(i=0; i < length; i++){
		bufferChild[i] = (unsigned char*) malloc (5 * sizeof(unsigned char));
	}
	childCounter = (unsigned short*) malloc (length * sizeof(unsigned short));
	childNumber = (unsigned short*) malloc (length * sizeof(unsigned short));

	array = (unsigned char*) malloc (length * sizeof(unsigned char));
	path = (unsigned char*) malloc (length * sizeof(unsigned char));
	visited = (unsigned char*) malloc (length * sizeof(unsigned char));


	for(i = 0; i<30; i++){
		array[i] = 0;
	}
	array[0] = 'A'; array[1] = 6; array[2] = 12;
	array[6] = 'B'; array[7] = 18; array[12] = 'C'; array[18] = 'D';
	array[24] = 'E';

	// for(i = 0; i<24; i++){
	// 	printf("arr[%d]: %u \n", i, array[i]);
	// }
	unsigned char start = 'A';
	unsigned char goal = 'C';
	// printf("%s \n", findPath(start,goal, '0'));
	path = findPath(start, goal, '0');

	// printf("sizeof(path): %d \n", pathCounter);
	if(pathCounter > 0){
		printf("Path: ", start);
		for(i=0; i<pathCounter-1; i++){
			printf("%c - ", path[i]);
		}
		printf("%c \n", path[pathCounter-1]);
	}
	else{
		printf("Tidak ada jalan dari start ke goal \n");
	}
}

unsigned char* findPath (unsigned char start, unsigned char goal, char isFound){
	printf("start: %c ; goal: %c \n", start, goal);
	path[pathCounter] = start;
	pathCounter++;
	// printf("isFound: %c \n", isFound);
	if(isFound == '1'){
		return path;
	}
	if(start == goal){
		printf("path found \n");
		isFound = '1';
		// printf("isFound: %c \n", isFound);
		// findPath(start, goal, '1');
		// printf("Path: %c - ", start);
		// int i;
		// for(i=0; i<pathCounter-1; i++){
		// 	printf("%c - ", path[i]);
		// }
		// printf("%c \n", path[pathCounter-1]);
		return path;
	}
	else{
		printf("else -- start: %c \n", start);
		if(isFound == '0')
		{
			levelCounter++;
			unsigned char* children = getChild(start);
			printf("else -- start: %c \n", start);

			int i;
			for(i=0; i<5; i++){
				printf("child[%d]: %u \n", i, children[i]);
			}
			printf("Count children: %d \n", countChild(children));
			childNumber[levelCounter] = countChild(children);

			if(countChild(children) == 0){
				printf("zero child \n");
				removeFromPath(start);
				levelCounter--;
				pathCounter--;
				if(levelCounter < 1)
				{
					printf("returning from zero child \n");
					return "";
				}
				else {
					printf("levelCounter: %d \n", levelCounter);
					printf("childCounter[levelCounter]: %d \n", childCounter[levelCounter]);
					printf("childNumber[levelCounter]: %d \n", childNumber[levelCounter]);
					if(childCounter[levelCounter]+1 < childNumber[levelCounter])
					{
						printf("backtrack \n");
						pathCounter--;
						printf("pathCounter:%d \n", pathCounter);
						return findPath(array[bufferChild[levelCounter][childCounter[levelCounter]+1]], goal, isFound);
					} else{
						char stop = '0';
						while (stop == '0'){
							levelCounter--;
							pathCounter--;
							if(levelCounter < 1)
							{
								printf("returning from zero child \n");
								return "";
							}
							else{
								if(childCounter[levelCounter]+1 < childNumber[levelCounter])
								{
									stop = '1';
									printf("backtrack \n");
									pathCounter--;
									return findPath(array[bufferChild[levelCounter][childCounter[levelCounter]+1]], goal, isFound);
								}
							}
						}


					}
				}
			}
			else{
				int i;
				for(i=0; i<countChild(children) && isFound == '0'; i++){
					printf("child: %c ; isFound: %c \n", array[children[i]], isFound);
					if(children[i] != '0'){
						bufferChild[levelCounter] = children;
						path[pathCounter] = array[children[i]];
						pathCounter++;
						visited[visitedCounter] = array[children[i]];
						visitedCounter++;
						childCounter[levelCounter] = i;
						return findPath(array[children[i]], goal, isFound);
					}
				}
			}
		}
	}
}

unsigned char* getChild (unsigned char start){
	unsigned char* children = (unsigned char*) malloc (5 * sizeof(unsigned char));
  int i;
	for(i = 0; i<5; i++){
		children[i] = '0';
	}
	int index = 0;
	char stop = '0';
	while(stop == '0' && index < length){
		if(array[index] != start){
			index+=6;
		}
		else{
			for(i=0; i<5; i++){
				if(isVisited(array[index+i+1], visited) == '0'){
					children[i] = array[index+i+1];
				}
			}
			stop = '1';
		}
	}
	return children;
}

char isVisited (unsigned char input, unsigned char* list){
	int i;
	for(i =0; i<visitedCounter; i++){
		if(list[i] == input)
			return '1';
	}
	return '0';
}

short countChild (unsigned char* children){
	int i;
	int counter = 0;
	for(i=0; i<5; i++){
		if(children[i] != 0)
			counter++;
	}
	return counter;
}

void removeFromPath(unsigned char start){
	pathCounter--;
}
