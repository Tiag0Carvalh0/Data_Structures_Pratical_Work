#include <stdio.h>
#include <stdlib.h>


 int Menu(){

     int menu= 0; 
    printf("Select Option\n");
    printf("1 --> Load Data\n");
    printf("2 --> New Operation\n");
    printf("3 --> Remove Operation\n");
    printf("4 --> Modify Operation\n");
    printf("5 --> Calculate Minimum Working Time\n");
    printf("6 --> Calculate Maximum Working Time\n");
    printf("7 --> Calculate Average Working Time\n");
    printf("8 --> Save Data\n");
    printf("9 --> Show Data\n");
    printf("10 --> Quit Program\n");
    scanf("%i", &menu);

     return (menu);
 }
