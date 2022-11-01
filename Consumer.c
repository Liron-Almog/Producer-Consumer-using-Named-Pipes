#include <stdio.h>
#include <stdlib.h> // for exit()
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
//------------define--------------
#define FIFO_NAME "fifo"
#define N 10
//----------prototype------------
void read_numbers(FILE *file);
void open_file(FILE ** file);
void print_array(int array[]);
//------------main---------------
int main() {

	FILE *file;
	srand(time(NULL));

	open_file(&file);
	read_numbers(file);

	return(EXIT_SUCCESS) ;
}
//The function read The numbers using named pipe
//-------read_number------------
void read_numbers( FILE *file){

	int array[N],i;

	for(i = 0 ; i < N ; i++)
		fscanf(file,"%d",&array[i]);

	fclose(file);
	print_array(array);
}
//The function print the numbers that came from the manufacturer
//------print_array-----------
void print_array(int array[]){

	int i;

	puts("The numbers is :");
	for(i = 0 ; i < N; i++)
		printf("%d\n",array[i]);
}
//--------open_file-----------
void open_file(FILE ** file){

	if (!(*file = fopen(FIFO_NAME, "r"))) {
		 perror("cannot open fifo file for r") ;
		 exit(EXIT_FAILURE) ;
		 }
}

