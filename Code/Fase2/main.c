
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.c"
#include "user.c"

int main()
{
    bool loaded = false;
    int job = 0,numOfProcesses = 0, totalJobs = 0, totalProcesses = 0, mainMenu = 0, menu = 0, minTime = 0, maxTime = 0, removed = 0, modify = 0, numOfJobs = 0, toRemoveJob, modifyJob, newJobNbr, total, jobNumb;
    float avgTime;
    char jobNmr;

    jobs *j1 = NULL;

    while (mainMenu != 9)
    {
        switch (mainMenu)
        {
        case 0:
            mainMenu = MainMenu();
            break;
        case 1:
            j1 = LoadFromFile(j1, &totalJobs);
            mainMenu = 0;
            break;
        case 2:
            printf("Number Of New Jobs to Add ");
            scanf("%i", &numOfJobs);
            for (int i = 1; i <= numOfJobs; i++)
            { // Iteration Not to Return Always to The Main Menu
                printf("Please Input Job Number ");
                scanf("%i", &jobNumb);
                printf("\n");
                totalJobs = totalJobs + 1;
                j1 = NewJob(j1, totalJobs, jobNumb);
            }
            mainMenu = 0;
            break;
        case 3:
            printf("Select Job To Modify\n");
            modifyJob = AvailableJobs(j1);
            printf("\n Modify Job Number?[y/n]  \n");
            scanf(" %c", &jobNmr);
            if (jobNmr == 'y')
            {
                printf("New Job Number \n");
                scanf("%i", &newJobNbr);
                j1->processList = EditJobs(j1, modifyJob, newJobNbr, &loaded);
            }
            else
            {
                newJobNbr = 00;
                j1->processList = EditJobs(j1, modifyJob, newJobNbr, &loaded);
            }
            mainMenu = 0;
            break;
        case 4:
            printf("Select Job To Remove ");
            toRemoveJob = AvailableJobs(j1);
            RemoveJobs(&j1, toRemoveJob);
            mainMenu = 0;
            break;
        case 5:
            printf("Select The Job To Acess The Operations! ");
            scanf("%i", &job);
            jobs *jAux = j1;
            while (jAux != NULL)
            {
                if (jAux->jobNumber == job)
                {
                    while (menu != 10)
                    {
                        switch (menu)
                        {
                        case 0:
                            menu = Menu();
                            break;
                        case 1:
                            printf("Number Of New Processes to Add  ");
                            scanf("%i", &numOfProcesses);
                            for (int i = 1; i <= numOfProcesses; i++)
                            { // Iteration Not to Return Always to The Main Menu
                                totalProcesses = totalProcesses + 1;
                                jAux->processList = NewProcess(jAux->processList, totalProcesses, loaded, i);
                            }
                            jAux->totalProcesses += totalProcesses;
                            totalProcesses = 0;
                            loaded = false;
                            menu = 0;
                            break;
                        case 2:
                            removed = RemoveProcess(&jAux->processList, &loaded);
                            menu = 0;
                            break;
                        case 3:
                            modify = ModifyData(jAux->processList, &loaded);
                            if (modify != 0)
                                printf("Process Successfully Modifyed\n");
                            menu = 0;
                            break;
                        case 4:
                            minTime = MinimumTime(jAux->processList, loaded, minTime);
                            printf("The Minimum Time To Work is %i minutes\n\n", minTime);
                            menu = 0;
                            break;
                        case 5:
                            maxTime = MaximumTime(jAux->processList, loaded, maxTime);
                            printf("The Maximum Time To Work is %i minutes\n\n", maxTime);
                            menu = 0;
                            break;
                        case 6:
                            avgTime = AverageTime(jAux->processList, loaded, avgTime);
                            printf("The Average Time To Work is %0.2f minutes on Job 1 \n", avgTime);
                            menu = 0;
                            break;
                        case 7:
                            ShowData(jAux->processList, minTime, maxTime, avgTime, loaded);
                            menu = 0;
                            break;
                        };
                    }
                    menu = 0;
                }
                jAux = jAux->nextJob;
            }
            free(jAux);
            mainMenu = 0;
            break;
        case 6:
            FJSSP(j1);
            mainMenu = 0;
            break;
        case 7:
            j1->processList = ShowAllData(j1);
            mainMenu = 0;
            break;
        case 8:
            j1->processList = SaveAllData(j1, totalJobs);
            mainMenu = 0;
            break;
        }
    }

    //**********************************Processes*******************************************//

    free(j1);        // Free the Malloc
    system("pause"); // Pause Before Quit
    return 0;
}