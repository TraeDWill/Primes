#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>
#include <stdbool.h>

#ifndef NORM
# define NORM 10240
#endif // NORM
       //
#ifndef DEF_DIM 
# define DEF_DIM 2 
#endif // DEF_DIM

 
static int dim = NORM;
static int num_threads = 1;


typedef struct BitBlock_s{
	uint32_t bits;
	pthread_mutex_t mutex;
} BitBlock_t;

BitBlock_t * primus = NULL;

void allinit(void);
void * SOE(void * vid);
void dealloc(void);
