#include <stdio.h>
#include <stdlib.h> // for exit()
#include <sys/types.h>
#include <stdbool.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
//------------define--------------
#define FIFO_NAME "fifo"
#define RANGE_OF_NUMS 10000
#define N 10

//----------prototype------------
bool is_prime(int num);
void send_numbers(FILE *file);
void open_fifo();
int get_prime();
void open_file(FILE ** file);

//------------main---------------
int main() {

	FILE *file;
	srand(time(NULL));

	open_fifo();
	open_file(&file);
	send_numbers(file);

	return(EXIT_SUCCESS) ;
}
//The function sends prime numbers by named pipe.
//-------send_number------------
void send_numbers( FILE *file){

	int i;

	for(i = 0 ; i < N ;i++){
		int num = get_prime();
		fprintf(file, " %d",num) ;
		fflush(file) ;
	}
	sleep(2); // for reader
	fclose(file);
}
//-------get_prime-------------
int get_prime(){

	while(1){
		int num = rand() % RANGE_OF_NUMS +2;
		if(is_prime(num))
			return num;
	}
}
//--------is_prime-------
bool is_prime(int num){

	int i;

	for(i = 2 ; i <= sqrt(num) ;i++)
		if(num % i == 0)
			return false;

	return true;
}
//--------open_file-----------
void open_file(FILE ** file){

	if (!(*file = fopen(FIFO_NAME, "w"))) {
		 perror("cannot open fifo file for w") ;
		 exit(EXIT_FAILURE) ;
		 }
}
//--------open_fifo------------
void open_fifo(){

	if (mkfifo(FIFO_NAME, S_IFIFO | 0644) == -1) {
		 perror("cannot create fifo file") ;
		 exit(EXIT_FAILURE) ;
		 }
}
