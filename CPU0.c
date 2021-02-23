#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <stdlib.h>
#include <sleep.h>
#include "xil_mmu.h"

int * defineImage()
{
	int matrix[128][128];
		for (int i = 0; i <128; i++)
		    {
		        for (int j = 0; j < 128; j++)
		        {
		            matrix[i][j] = rand() % 256;
		        }
		    }
	return matrix;
}

#define COMM_VAL (*(volatile unsigned long *)(0xFFFF0000))
#define ARR_VAL (*(volatile int *)(0xFFFF1000))
#define MY_MATRIX (volatile int[3][3])(0xFFFF000)) = [-1,-1,-1,-1,9,-1,-1,-1,-1]
#define MY_IMAGE (*(volatile long *)(0xFFFFF00))



int main()
{
	MY_IMAGE = defineImage();
	print("CPU0: Initialize platform\n\r");
	init_platform(); //frfg
    //Disable cache on OCM
    Xil_SetTlbAttributes(0xFFFF0000, 0x14de2);			// S=b'1 TEX=b'100 Domain=b'1111 C=b'0 B=b'0
    ARR_VAL = 0;
    while(1)
    {
    	while (COMM_VAL == 0);
    	//printf("Counter is %ls" , &COUNTER_VAL);
    	COMM_VAL = 0;
    	int counter = 0;
    	for ( long i = (ARR_VAL * 128) ; i < ARR_VAL * 128 + 128; i++ )
    		{
    			//printf( "*(MY_IMAGE + %d) : %d\n", i, *(MY_IMAGE + i));
				counter += ((MY_IMAGE + i - 129) * -1);
				counter += ((MY_IMAGE + i - 128) * -1);
				counter += ((MY_IMAGE + i - 127) * -1);
				counter += ((MY_IMAGE + i -1) * -1);
				counter += ((MY_IMAGE + i) * 9);
				counter += ((MY_IMAGE + i +1) * -1);
				counter += ((MY_IMAGE + i + 127) * -1);
				counter += ((MY_IMAGE + i + 128) * -1);
				counter += ((MY_IMAGE + i + 129) * -1);
				*(&MY_IMAGE + i) = counter;
    	   }
    	ARR_VAL++;
    }
    cleanup_platform();
    return 0;
}
