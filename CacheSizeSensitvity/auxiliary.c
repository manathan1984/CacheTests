/*
 * auxiliary.cpp
 *
 *  Created on: Jul 3, 2012
 *      Author: Manos Athanassoulis
 *
 *
 *  You should have received a license file with this code: license.txt
 */


#include "auxiliary.h"
#include <stdlib.h>


int my_clock_get_time(my_clock *clk)
{
	int ret = -1;
	
	ret=clock_gettime(CLOCK_REALTIME, clk);
	
	return ret;

}

void my_print_clock(my_clock clk)
{
	printf("CLK: %ld s + %ld ns = %lf sec\n",clk.tv_sec,clk.tv_nsec,(double)clk.tv_sec+(double)clk.tv_nsec/1000000000);
}

long getclock_diff_us(my_clock clk1, my_clock clk2)
{
	return 1000000*(clk2.tv_sec-clk1.tv_sec)+(clk2.tv_nsec-clk1.tv_nsec)/1000;
}

long getclock_diff_ns(my_clock clk1, my_clock clk2)
{
	return 1000000000*(clk2.tv_sec-clk1.tv_sec)+(clk2.tv_nsec-clk1.tv_nsec);
}

double getclock_diff_s(my_clock clk1, my_clock clk2)
{
	return (double)(clk2.tv_sec-clk1.tv_sec)+(double)(clk2.tv_nsec-clk1.tv_nsec)/1000000000;
}
