#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "auxiliary.h"

int main (int argc, char ** argv)
{
	my_clock start;	
	my_clock end;
	
	int option;
	if (argc>1)
	{
		option=atoi(argv[1]);
		if (option<0 || option >2)
			option = 0;
		printf ("Option %d\n",option);
	}
	

	if (option == 2)
	{
		int arraySize = 50 * 1024 * 1024;
		int* array = (int*) malloc (sizeof(int)*arraySize);
		int step = 16;

		printf("This experiment updates the values an array of %d elements.\n",arraySize);
		printf("The first run updates 1 every %d values, and the second all values.\n",step);
		//This tests touches 1 out of 16 values
		my_clock_get_time(&start);
		for (int i = 0; i < arraySize; i+=step) array[i] *= 3;
		my_clock_get_time(&end);
		long diff1 = getclock_diff_us(start,end);
		printf ("1 out of every %d values, overall time %0.2lf ms\n",step,(double)(diff1)/1000);
		//This tests touches every values
		my_clock_get_time(&start);
		for (int i = 0; i < arraySize; i++) array[i] *= 3;
		my_clock_get_time(&end);
		long diff2 = getclock_diff_us(start,end);
		printf ("Update all values, overall time %0.2lf ms\n",(double)(diff2)/1000);
		//The goal here is to compare the two which should not be 16 times different because the main cost is data movement.
		printf ("The 2nd run touches %d times more elements, yet it is %0.2lf times slower!\n",step,(double)diff2/(double)diff1);
	}
	else if (option == 1)
	{
		int arraySize = 50 * 1024 * 1024;
		int* array = (int*) malloc (sizeof(int)*arraySize);

		//This experiment shows that as long as we touch every cacheline the cost remains roughly the same 
		//But when we start skipping entire cachelines (and multiple of them) things are becoming faster
		printf("This experiment shows the time of updating an array every K values.\n");
		for (int K=1; K<=16384 ; K*=2)
		{
			my_clock_get_time(&start);
			for (int i = 0; i < arraySize; i += K) array[i] +=2;
			my_clock_get_time(&end);
			long diff=getclock_diff_us(start,end);
			printf ("K: %d, time: %lf ms, time per update: %lf ns\n",K,(double)(diff)/1000, 1000*(double)(diff)/(double)(arraySize/K));
		}
	}
	else if (option == 0)
	{
		int steps = 64 * 1024 * 1024; // Arbitrary number of steps
		uint minSizeBytes=1024;
		uint maxSizeBytes=2*1024*1024*1024;
		printf("Perform a fixed number of steps (%d) over an array with variable size %u to %u KB.\n",steps,minSizeBytes/1024,maxSizeBytes/1024);
		printf("The goal of this experiments is to show the relative impact of data movement and computation.\n");
		for (uint newArraySize = minSizeBytes/(uint)(sizeof(uint)) ; newArraySize <= (maxSizeBytes/(uint)(sizeof(uint))) ; newArraySize*=2)
		{
			int* newArray = (int*) malloc(sizeof(int)*newArraySize);
			int lengthMod = newArraySize - 1;
			my_clock_get_time(&start);
			for (int i = 0; i < steps; i++)
			{
    				newArray[(i * 16) & lengthMod]++; // (x & lengthMod) is equal to (x % arr.Length)
			}
			my_clock_get_time(&end);
			printf ("Arraysize: %lu KB (%lu MB), time: %lf ms, time per step: %lf ns\n",newArraySize*sizeof(int)/1024,newArraySize*sizeof(int)/1024/1024,(double)(getclock_diff_us(start, end))/1000,(double)(getclock_diff_us(start, end))*1000/(double)steps);
		}
	}
	return 0;
}

