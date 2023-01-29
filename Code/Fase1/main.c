#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcoes.c"
#include "user.c"

int main()
{
    bool loaded = false;
    int numOfProcesses = 0, totalProcesses = 0, menu = 0, minTime = 0, maxTime = 0, removed = 0, modify = 0;
    float avgTime;

    processes *p1 = NULL; // First Empty List (1 Job)

    while (menu != 10)
    {
        switch (menu)
        {
        case 0:
            menu = Menu();
            break;
        case 1:
            p1 = GetData(p1, &minTime, &maxTime, &avgTime, &totalProcesses, &loaded); // Read From File
            menu = 0;
            break;
        case 2:
            printf("Number Of New Processes to Add  ");
            scanf("%i", &numOfProcesses);
            for (int i = 1; i <= numOfProcesses; i++)
            { // Iteration Not to Return Always to The Main Menu
                totalProcesses = totalProcesses + 1;
                p1 = NewProcess(p1, totalProcesses, loaded, i);
            }
            loaded = false;
            menu = 0;
            break;
        case 3:
            removed = RemoveProcess(&p1, &loaded);
            if (removed != 0)
                printf("Process Successfully Removed\n");
            menu = 0;
            break;
        case 4:
            modify = ModifyData(p1, &loaded);
            if (modify != 0)
                printf("Process Successfully Modifyed\n");
            menu = 0;
            break;
        case 5:
            minTime = MinimumTime(p1, loaded, minTime);
            printf("The Minimum Time To Work is %i minutes\n\n", minTime);
            menu = 0;
            break;
        case 6:
            maxTime = MaximumTime(p1, loaded, maxTime);
            printf("The Maximum Time To Work is %i minutes\n\n", maxTime);
            menu = 0;
            break;
        case 7:
            avgTime = AverageTime(p1, loaded, avgTime);
            printf("The Average Time To Work is %0.2f minutes on Job 1 \n", avgTime);
            menu = 0;
            break;
        case 8:
            SaveData(p1, minTime, maxTime, avgTime, totalProcesses, loaded);
            menu = 0;
            break;
        case 9:
            ShowData(p1, minTime, maxTime, avgTime, loaded);
            menu = 0;
            break;
        };
    }
    free(p1);        // Free the Malloc
    system("pause"); // Pause Before Quit
    return 0;
}