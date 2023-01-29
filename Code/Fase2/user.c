#include <stdio.h>
#include <stdlib.h>

int MainMenu()
{
    int menu = 0;
    printf("1 --> Upload Data From File\n");
    printf("2 --> Add New Jobs\n");
    printf("3 --> Edit Jobs\n");
    printf("4 --> Remove Job\n");
    printf("5 --> Operations Menu\n");
    printf("6 --> Escalation Solution\n");
    printf("7 --> Show All Data\n");
    printf("8 --> Save All Data\n");
    printf("9 --> Exit Program\n");
    scanf("%i", &menu);

    return (menu);
}

int Menu()
{

    int menu = 0;
    printf("Select Option\n");
    printf("1 --> New Operation\n");
    printf("2 --> Remove Operation\n");
    printf("3 --> Modify Operation\n");
    printf("4 --> Calculate Minimum Working Time\n");
    printf("5 --> Calculate Maximum Working Time\n");
    printf("6 --> Calculate Average Working Time\n");
    printf("7 --> Show Data\n");
    printf("10 --> Main Menu\n");
    scanf("%i", &menu);

    return (menu);
}
