/* main.c  */

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

int main()
{

    printf("\n\n-----------Clustering-----------\n\n");

    input_data();
    
    CLUSTER_DATA();

    printf("writing out file...\n");
    output_result();
  
    printf("\n\n-----------Clustering-----------\n\n");
    
    return 0;
}
