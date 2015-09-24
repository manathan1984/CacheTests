#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "auxiliary.h"

int main (int argc, char ** argv)
{
	my_clock start;	
	my_clock end;
	
	/*
	int arraySize = 50 * 1024 * 1024;
	int* array = (int*) malloc (sizeof(int)*arraySize);


	my_clock_get_time(&start);
	for (int i = 0; i < arraySize; i+=16) array[i] *= 3;
	my_clock_get_time(&end);
	printf ("ms: %lf\n",(double)(getclock_diff_us(start, end))/1000);

	
	my_clock_get_time(&start);
	for (int i = 0; i < arraySize; i++) array[i] *= 3;
	my_clock_get_time(&end);
	printf ("ms: %lf\n",(double)(getclock_diff_us(start, end))/1000);


	for (int K=1; K<=16384 ; K*=2)
	{
		my_clock_get_time(&start);
		for (int i = 0; i < arraySize; i += K) array[i] +=2;
		my_clock_get_time(&end);
		printf ("K: %d, time: %lf ms\n",K,(double)(getclock_diff_us(start, end))/1000);
	}
	*/

	int steps = 64 * 1024 * 1024; // Arbitrary number of steps
	uint minSizeBytes=1024;
	uint maxSizeBytes=2*1024*1024*1024;
	printf("Perform a fixed number of steps (%d) over an array with variable size %ud to %ud KB.\n",steps,minSizeBytes/1024,maxSizeBytes/1024);
	printf("The goal of this experiments is to shows the relative impact of data movement and computation.\n");
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

