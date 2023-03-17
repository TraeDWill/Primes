#include "primesMT.h"

void allinit(void)
{
	int i = (dim/32) + 1;	
	int j = 0;

	//Malloc for primus, the array of data structs
	primus = malloc(sizeof(BitBlock_t) * i); 

	//Itterates through primus and sets each struct bits
	for(j = 0; j < i; j++)
	{
		primus[j].bits = 0;

		//Init mutext #4
		//primus[j].mutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_init(&primus[j].mutex, NULL);
		
	}
}
void dealloc(void)
{
	for(int i = 0; i < ((dim/32) + 1); ++i)
	{
		pthread_mutex_destroy(&primus[i].mutex);
	}
	free(primus);
}

void * SOE(void * vid)
{
	long tid = (long) vid;
	uint32_t mask = 0x0;

	//As long as spot is smaller than ceiling
	for(long i = tid; i < (sqrt(dim) + 1); i += (num_threads * 2))
	{
		for(long j = (i * 2); j <= dim; j += i)
		{
			//Find index
			int current_index = j/32;		

			//Find bit
			int current_bit = j%32;


			//Mask init
			mask = 0x1 << current_bit;

			pthread_mutex_lock(&primus[current_index].mutex);

			//Bit shift
			primus[current_index].bits = primus[current_index].bits | mask;

			//Unlock mutex
			pthread_mutex_unlock(&primus[current_index].mutex);

			//Reset Mask
			mask = 0x0;
		}
	}
	pthread_exit(EXIT_SUCCESS);
		
}

int main(int argc, char *argv[])
{
  		pthread_t * threads = NULL;
		bool isverbose = false;		
		int opt = -1;
		while((opt = getopt(argc, argv, "t:u:h:v")) != -1)
		{
			switch (opt){
			case 't':
				num_threads = atoi(optarg);
				break;
			case 'u':
				dim = atoi(optarg);
				if(dim < DEF_DIM)
				{
					dim = DEF_DIM;
				}
				break;
			case 'h':
				printf("%s: -t # -u # -h -u\n", argv[0]);
				printf("\t-t #: number of threads\n");
				printf("\t-d #: size of matrix\n");
				printf("\t-h #: command help\n");
				printf("\t-v #: triggers verbosity\n");
				exit(0);
				break;
			case 'v':
				//Diagnostics using verbosity
				isverbose = true;
				break;
			default: /* '?' */
				exit(EXIT_FAILURE);
				break;
			}
		}
		//Init
		
		//Allocate memory
		threads = malloc(num_threads * sizeof(pthread_t));
	
		allinit();
		
		//Funception ft threads
		if(isverbose == true)
		{
			if(num_threads <= 5)
				printf("meh\n");
			else if(num_threads <= 10)
				printf("less meh\n");
			else if(num_threads < 30)
				printf("REAL SPEED\n");
			else
				printf("I think we broke it\n");
		}
		for(long tid = 0, start = 3; tid < num_threads; ++tid, start += 2)
		{
			pthread_create(&threads[tid], NULL, SOE, (void *)start);
		}
		for(long tid = 0; tid < num_threads; ++tid)
		{
			pthread_join(threads[tid], NULL);
		}
		
		//Display the work of the funception
		printf("2\n");	
		for(long j = 3; j <= dim; j += 2)
		{
			uint32_t mask = 0;
			int bit = j%32;
			int index = j/32;
			mask = 0x1 << bit;
			if((primus[index].bits & mask) != mask)
				printf("%ld\n", j);
		}

		//de-alloc
		dealloc();
		free(threads);

		return 0;
}
