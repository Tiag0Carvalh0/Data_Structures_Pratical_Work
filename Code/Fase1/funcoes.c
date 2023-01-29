#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <malloc.h>
#include "funcoes.h"
#include "user.h"

processes *NewProcess(processes *mainProcess, int totalProcesses, bool uploaded, int newAdd)
{
    processes *pAux = mainProcess, *newProcess = (processes *)malloc(sizeof(processes));
    ; // Alocate Memory

    int numOfMachines, time, operationNumber, workMac, prev = 0;

    if (newProcess != NULL)
    {
        if (pAux == NULL) // First of the list
        {

            printf("Please Insert Process Number!(Recomended 1) ");
            scanf("%d", &operationNumber);
            printf("\n");
            newProcess->operationNbr = operationNumber;
            printf("Total Machines to do the Process [1-8]?  ");
            scanf("%d", &numOfMachines);
            while (numOfMachines > 8)
            {
                printf("Please Insert a Valide Machine [1-8] ");
                scanf("%d", &numOfMachines);
            }

            printf("\n");
            newProcess->totalMachines = numOfMachines;

            // Create Arrays to Store the Process Data and Allocate Dynamic Memory for Them
            newProcess->workingMachines = (int *)malloc(sizeof(int) * numOfMachines);
            newProcess->time = (int *)malloc(sizeof(int) * numOfMachines);

            // Fill The Arrays With the Data
            for (int i = 0; i < numOfMachines; i++)
            {
                printf("Select Machines Who Will Work, by Ascending Order![1-8]  ");
                scanf("%i", &workMac);
                // Scan if Input Machine is Valid and If it is by Ascending Order
                while ((workMac > 8) || prev >= workMac)
                {
                    printf("Please Insert a Valide Machine [1-8] ");
                    scanf("%d", &workMac);
                }
                prev = workMac;
                printf("\n");
                printf("Select Time of Work!  ");
                scanf("%i", &time);
                printf("\n");
                newProcess->workingMachines[i] = workMac;
                newProcess->time[i] = time;
            }
            newProcess->nextProcesses = pAux;
            return (newProcess);
        }
        else
        {

            while (pAux->nextProcesses != NULL)
            {
                pAux = pAux->nextProcesses;
            }
            if (uploaded == true)
                printf("Please Insert Process Number!(Recomended %i)  ", totalProcesses);
            else
                printf("Please Insert Process Number!(Recomended %i)  ", newAdd);
            scanf("%d", &operationNumber);
            printf("\n");
            newProcess->operationNbr = operationNumber;

            printf("How Many Machines to do the Process [1-8]?  ");
            scanf("%d", &numOfMachines);
            while (numOfMachines > 8)
            {
                printf("Please Insert a Valide Machine [1-8] ");
                scanf("%d", &numOfMachines);
            }
            printf("\n");
            newProcess->totalMachines = numOfMachines;

            // Create Arrays to Store the Process Data and Allocate Dynamic Memory for Them
            newProcess->workingMachines = (int *)malloc(sizeof(int) * numOfMachines);
            newProcess->time = (int *)malloc(sizeof(int) * numOfMachines);

            // Fill The Arrays With the Data
            for (int i = 0; i < numOfMachines; i++)
            {
                printf("Select Machines Who Will Work, by Ascending Order! [1-8]  ");
                scanf("%i", &workMac);
                // Scan if Input Machine is Valid and If it is by Ascending Order
                while ((workMac > 8) || prev >= workMac)
                {
                    printf("Please Insert a Valide Machine [1-8] ");
                    scanf("%d", &workMac);
                }
                prev = workMac;
                printf("\n");
                printf("Select Time of Work!  ");
                scanf("%i", &time);
                printf("\n");
                newProcess->workingMachines[i] = workMac;
                newProcess->time[i] = time;
            }
            newProcess->nextProcesses = NULL; // End of the list
            pAux->nextProcesses = newProcess; // Next process on the list
            return (mainProcess);
        }
    }
    else
    {
        return (pAux);
    }
}

processes *NewAtLoad(processes *loadProcess, int totalMachines, int operationNumber, int *bufferMachines, int *bufferTimes)
{
    
    processes *pAux = loadProcess, *newProcess = (processes *)malloc(sizeof(processes));

    if (newProcess != NULL)
    {
        if (pAux == NULL)
        {
            newProcess->operationNbr = operationNumber;
            newProcess->totalMachines = totalMachines;

            // Create Arrays to Store the Process Data and Allocate Dynamic Memory for Them
            newProcess->workingMachines = (int *)malloc(sizeof(int) * totalMachines);
            newProcess->time = (int *)malloc(sizeof(int) * totalMachines);

            for (int i = 0; i < (totalMachines); i++) // Fill the Arrays with the Buffer Data
            {
                newProcess->workingMachines[i] = bufferMachines[i];
                newProcess->time[i] = bufferTimes[i];
            }

            newProcess->nextProcesses = pAux;
            return (newProcess);
        }
        else
        {
            while (pAux->nextProcesses != NULL)
            {
                pAux = pAux->nextProcesses;
            }
            newProcess->operationNbr = operationNumber;
            newProcess->totalMachines = totalMachines;

            // Create Arrays to Store the Process Data and Allocate Dynamic Memory for Them
            newProcess->workingMachines = (int *)malloc(sizeof(int) * totalMachines);
            newProcess->time = (int *)malloc(sizeof(int) * totalMachines);

            for (int i = 0; i < (totalMachines); i++) // Fill The Arrays with the Buffer Data
            {
                newProcess->workingMachines[i] = bufferMachines[i];
                newProcess->time[i] = bufferTimes[i];
            }

            newProcess->nextProcesses = NULL; // End of the list
            pAux->nextProcesses = newProcess; // Next Process on the list
            return (loadProcess);
        }
    }
    else
    {
        return (pAux);
    }
}

int RemoveProcess(processes **proce, bool *loaded)
{
    int toRemove, count = 0;
    processes *printAux = *proce;

    printf("Available Processes\n");
    while (printAux != NULL) // Show all Available Machines
    {
        printf("[%i] ", printAux->operationNbr);
        count++;
        printAux = printAux->nextProcesses;
    }
    printf("\nSelect Process To Remove ");
    scanf("%i", &toRemove);
    while (toRemove > count)
    {
        printf("Please Valid Process [1-%i] ", count);
        scanf("%i", &toRemove);
    }
    printf("\n");
    if (*proce == NULL)
    {
        printf("ERROR\n");
        exit(1);
    }
    if ((*proce)->operationNbr == toRemove) // If it is the First Node
    {
        processes *remove = *proce;
        *proce = (*proce)->nextProcesses;
        free(remove->time);            // Free Memory of the Array
        free(remove->workingMachines); // Free Memory of the Array
        free(remove);                  // Free Memory of the Node
        *loaded = false;
        // Re-Order the Number of processes
        processes *reOreder1 = *proce;
        while (reOreder1 != NULL)
        {
            reOreder1->operationNbr = (reOreder1->operationNbr) - 1;
            reOreder1 = reOreder1->nextProcesses;
        }
        return (1);
    }
    for (processes *curr = *proce; curr != NULL; curr = curr->nextProcesses)
    {
        if (curr->nextProcesses->operationNbr == toRemove)
        {
            processes *remove = curr->nextProcesses;
            curr->nextProcesses = curr->nextProcesses->nextProcesses;
            free(remove->time);            // Free Memory of the Array
            free(remove->workingMachines); // Free Memory of the Array
            free(remove);                  // Free Memory of the Node
            *loaded = false;
            printf("Current -> %i\n", curr->operationNbr);
            // Re-Order the Number of processes
            processes *reOrder = curr;
            reOrder = reOrder->nextProcesses;
            while (reOrder != NULL)
            {
                reOrder->operationNbr = (reOrder->operationNbr) - 1;
                reOrder = reOrder->nextProcesses;
            }
            return (1);
        }
    }
}

int ModifyData(processes *pAux, bool *loaded)
{
    processes *printAux = pAux;
    int toModify, changeMachine, new = 0, newTime = 0, newMach = 0, count = 0, menu = 0, last = 0;;
    int *bufferMach, *bufferTime;

    while (menu != 9)
    {
        switch (menu)
        {
        case 0:
            printf("1 --> Add Machine And Time\n");
            printf("2 --> Remove Machine and Time\n");
            printf("3 --> Edit Machine\n");
            printf("4 --> Edit Time\n");
            printf("9 --> Main Menu\n");
            scanf("%i", &menu);
            break;
        case 1:
            printf("Available Processes\n");
            while (printAux != NULL) // Show all Available Processes
            {
                printf("[%i] ", printAux->operationNbr);
                count++;
                printAux = printAux->nextProcesses;
            }
            //Copy Data From the Struct
            bufferMach = (int *)malloc(sizeof(int) * (pAux->totalMachines));
            bufferTime = (int *)malloc(sizeof(int) * (pAux->totalMachines));

            processes *newMachine = pAux; //Create Aux variable of processes tyep
        
            printf("\nProcess To Modify ");
            scanf("%i", &toModify);
            printf("\n");
            while (newMachine != NULL)
            {
                if (newMachine->operationNbr == toModify)
                { // Save Data of the operation
                    for (int i = 0; i < newMachine->totalMachines; i++)
                    {
                        bufferMach[i] = newMachine->workingMachines[i];
                        bufferTime[i] = newMachine->time[i];
                    }
                    printf("Total Number of New Machines\n");
                    scanf("%i", &new);
                    newMachine->totalMachines = (newMachine->totalMachines) + new; //Increment Total of Machines
                    //Free The Space of the Arrays
                    free(newMachine->workingMachines);
                    free(newMachine->time);
                    //Alocate new Space For The new Total Of Machines
                    newMachine->workingMachines = (int *)malloc(sizeof(int) * (newMachine->totalMachines));
                    newMachine->time = (int *)malloc(sizeof(int) * (newMachine->totalMachines));

                    for (int i = 0; i < newMachine->totalMachines; i++)
                    {
                        if (i < newMachine->totalMachines - new)
                        {
                            newMachine->workingMachines[i] = bufferMach[i];
                            newMachine->time[i] = bufferTime[i];
                            last = newMachine->workingMachines[i];
                        }
                        else //When its Time to Add the New Machine
                        {
                            printf("Insert New Machine Number\n");
                            scanf("%i", &newMach);
                            while (newMach <= last) //Check if the Machine is Available
                            {
                                printf("Machine Should Be Higher then %i\n", last);
                                scanf("%i", &newMach);
                            }
                            last = newMach;
                            printf("Insert New Time\n");
                            scanf("%i", &newTime); //Get New Time
                            newMachine->workingMachines[i] = newMach;
                            newMachine->time[i] = newTime;
                        }
                    }
                }
                newMachine = newMachine->nextProcesses;
            }
            free(bufferMach); //Free Buffer Memory
            free(bufferTime); //Free Buffer Memory
            free(newMachine); //Free aux Variable
            menu = 0;
            break;
        case 2:
            printf("Available Processes\n");
            while (printAux != NULL) // Show all Available Processes
            {
                printf("[%i] ", printAux->operationNbr);
                count++;
                printAux = printAux->nextProcesses;
            }
            printf("\nProcess To Modify ");
            scanf("%i", &toModify);
            printf("\n");

            processes *toRemove = pAux; //Aux Variable of Processes Type
            int remove, auxMach[9], auxTime[9],line=0;

            while (toRemove != NULL)
            {
                if (toRemove->operationNbr == toModify)
                {
                    printf("Available Machines\n");
                    for (int i = 0; i < toRemove->totalMachines; i++) // Show All Machines of the Selected Process
                    {
                        printf("Machine -> %i\t", toRemove->workingMachines[i]);
                    }
                    printf("\nMachine to Remove ");
                    scanf("%i", &remove);

                    
                    for (int i = 0; i < toRemove->totalMachines; i++) //Save The Machines in a aux Array
                    {
                        auxMach[i] = toRemove->workingMachines[i];
                        auxTime[i] = toRemove->time[i];
                    }
                    // Free the Space and Alocate New One
                    free(toRemove->workingMachines);
                    free(toRemove->time);
                    toRemove->totalMachines = (toRemove->totalMachines)-1; //Decrement the Total Machines
                    //Alocate New Space For the New Total Machines
                    toRemove->workingMachines = (int *)malloc(sizeof(int) * (toRemove->totalMachines));
                    toRemove->time = (int *)malloc(sizeof(int) * (toRemove->totalMachines));

                    for (int i = 0; i < toRemove->totalMachines; i++)
                    {
                        if (auxMach[line] == remove) 
                        {
                            line = line + 1; //Skip the Removed Machine
                        } 
                            toRemove->workingMachines[i] = auxMach[line];
                            toRemove->time[i] = auxTime[line];
                            line ++;
                    }
                }
                toRemove = toRemove->nextProcesses;
            }
            free(toRemove);//Free aux Variable
            menu = 0;
            break;

        case 3:
            printf("Available Processes\n");
            int valid[8];
            while (printAux != NULL) // Show all Available Processes
            {
                printf("[%i] ", printAux->operationNbr);
                count++;
                printAux = printAux->nextProcesses;
            }
            int newMach = 0, pos = 0, machSelec = 0, aux;
            printf("\nProcess To Modify ");
            scanf("%i", &toModify);
            printf("\n");
            processes *newMachNum = pAux; //Aux Variable of Processes Type
            while (newMachNum != NULL)
            {
                if (newMachNum->operationNbr == toModify)
                {
                    for (int i = 0; i < newMachNum->totalMachines; i++) // Show All Machines of the Selected Process
                    {
                        valid[i] = newMachNum->workingMachines[i];
                        printf("Machine -> %i\t", newMachNum->workingMachines[i]);
                    }
                    printf("\n Select Machine ");
                    scanf("%i", &machSelec);
                    printf("New Machine Number ");
                    scanf("%i", &newMach);
                    for(int i=0; i<8 ; i++){
                        if(newMach == valid[i]){
                            printf("Select Valid Machine\n");
                            return(0);
                        }
                    }
                    for (int i = 0; i < newMachNum->totalMachines; i++) // Change the Data
                    {
                        if (newMachNum->workingMachines[i] == machSelec)
                        {
                            newMachNum->workingMachines[i] = newMach;
                        }
                    }
                    // Put in Ascending Order the New Machine
                    for (int i = 0; i < newMachNum->totalMachines; i++)
                    {
                        for (int j = i + 1; j < newMachNum->totalMachines; j++)
                        {
                            if ((newMachNum->workingMachines[i]) > (newMachNum->workingMachines[j]))
                            {
                                aux = newMachNum->workingMachines[i];
                                newMachNum->workingMachines[i] = newMachNum->workingMachines[j];
                                newMachNum->workingMachines[j] = aux;
                            }
                        }
                    }
                }
                newMachNum = newMachNum->nextProcesses;
            }
            free(newMachNum);//Free aux Variable
            menu = 0;
            break;
        case 4:
            printf("Available Processes\n");
            while (printAux != NULL) // Show all Available Processes
            {
                printf("[%i] ", printAux->operationNbr);
                count++;
                printAux = printAux->nextProcesses;
            }
            processes *changeTime = pAux; //Aux Variable of Processes Type
            printf("\nProcess To Modify ");
            scanf("%i", &toModify);
            printf("\n");
            while (changeTime!= NULL)
            {
                if (changeTime->operationNbr == toModify)
                {
                    printf("Available Machines\n");
                    for (int i = 0; i < changeTime->totalMachines; i++) // Show All Machines of the Selected Process
                    {
                        printf("Machine -> %i\t", changeTime->workingMachines[i]);
                    }
                    printf("\nMachine to Modify ");
                    scanf("%i", &changeMachine);
                    printf("\nNew Time ");
                    scanf("%i", &newTime);
                    for (int i = 0; i < changeTime->totalMachines; i++) 
                    {
                        if (changeTime->workingMachines[i] == changeMachine) // Change the Time
                        {
                            changeTime->time[i] = newTime;
                        }
                    }
                }
                changeTime = changeTime->nextProcesses;
            }
            free(changeTime);//Free aux Variable
            menu = 0;
            break;
        }
    }
    *loaded = false;
    return (1);
}

int MinimumTime(processes *pAux, bool uploaded, int min)
{
    int minor = 0, sum = 0;
    if (uploaded == false)
    {
        while (pAux != NULL)
        {
            for (int i = 0; i < pAux->totalMachines; i++)
            {
                if (i == 0)
                {
                    minor = pAux->time[i]; // First Time is the Minor
                }
                else if (minor > pAux->time[i]) // Compare if the Next Time is Lower than the Minor
                {
                    minor = pAux->time[i]; // If True, New Minor is The Value of That Machine
                }
            }
            sum += minor;               // Sum of Total Min Time
            pAux = pAux->nextProcesses; // Next Node of the List
        }
        return (sum); // Return the Total Min Time To Produce
    }
    else
    {
        return (min);
    }
}

int MaximumTime(processes *pAux, bool uploaded, int max)
{
    int maximum, sum = 0;
    if (uploaded == false)
    {
        while (pAux != NULL)
        {
            for (int i = 0; i < pAux->totalMachines; i++)
            {
                if (i == 0)
                {
                    maximum = pAux->time[i]; // First Time is the Higher
                }
                else if (maximum <= pAux->time[i]) // Compare if the Next Time is Higher than the Maximum
                {
                    maximum = pAux->time[i]; // If True, New Max is The Value of That Machine
                }
            }
            sum += maximum;             // Sum of Total Max Time
            pAux = pAux->nextProcesses; // Next Node of the List
        }
        return (sum); // Return the Total Max Time To Produce
    }
    else
    {
        return (max);
    }
}

float AverageTime(processes *pAux, bool uploaded, float avgDefault)
{

    int sum = 0, count = 0;
    float avg = 0;

    if (uploaded == false)
    {
        while (pAux != NULL)
        {
            for (int i = 0; i < pAux->totalMachines; i++)
            {
                sum = sum + pAux->time[i]; // Summation of All Times From the Machines
                count++;                   // Increment Total Number Of Machines
            }
            pAux = pAux->nextProcesses; // Next Node of the List
        }
        avg = (float)sum / count; // Calculate the Average time
        return (avg);
    }
    else
    {
        return (avgDefault);
    }
}

void SaveData(processes *pAux, int min, int max, float avg, int processes, bool uploaded)
{
    FILE *saveData;                    // Variable of FILE type
    saveData = fopen("data.txt", "w"); // Open to Writte

    if (saveData != NULL)
    {
        fprintf(saveData, "%i\n", processes); // Total Number of Processes of This Job

        // Writte Data of Times
        if ((min == 0) || (max == 0) || (avg == 0))
        { // If The User Hasnt Acceded to The Functions to Calculate the Times
            fprintf(saveData, "%i\n", MinimumTime(pAux, uploaded, min));
            fprintf(saveData, "%i\n", MaximumTime(pAux, uploaded, max));
            fprintf(saveData, "%0.2f\n", AverageTime(pAux, uploaded, avg));
        }
        else
        { // If The User Has Acceded to The Functions to Calculate the Times
            fprintf(saveData, "%i\n", min);
            fprintf(saveData, "%i\n", max);
            fprintf(saveData, "%0.2f\n", avg);
        }
        // Data From The Operations
        while (pAux != NULL)
        {
            fprintf(saveData, "%i\n", pAux->totalMachines);
            fprintf(saveData, "%i\n", pAux->operationNbr);
            for (int i = 0; i < pAux->totalMachines; i++)
            {
                if (pAux->workingMachines != NULL)
                {
                    fprintf(saveData, "%i\n%i\n", pAux->workingMachines[i], pAux->time[i]);
                }
            }
            pAux = pAux->nextProcesses;
        }
        fclose(saveData); // Close File
    }
    else
    {
        printf("ERROR OPENNING THE FILE!\n"); // If Cant Open File
    }
    printf("Data Saved\n");
}

processes *GetData(processes *pAux, int *minTime, int *maxTime, float *avgTime, int *totalProcesses, bool *uploaded)
{
   if(*uploaded == true){
       return pAux;

   } else {
    *uploaded = true;
    FILE *getData;                    // Variable of FILE type
    getData = fopen("data.txt", "r"); // Open to Read
    int machinesToWork, operationNumber;
    int *buffMach, *bufferTime; // Auxiliar Buffers

    // Get General Data(Time References)
    // Becaue they are Passed as Reference, We Can Change Value Directly on main()
    fscanf(getData, "%d", &(*totalProcesses)); // Total Processes
    fscanf(getData, "%d", &(*minTime));        // Min Time to Work
    fscanf(getData, "%d", &(*maxTime));        // Max Time to Work
    fscanf(getData, "%f", &(*avgTime));        // Average Time to Work

    // Put Data In BUFFER
    for (int i = 0; i < (*totalProcesses); i++)
    {
        fscanf(getData, "%d", &machinesToWork);                   // Total Machines to Work on the Process
        buffMach = (int *)malloc(sizeof(int) * machinesToWork);   // Allocate Memory for the Buffers
        bufferTime = (int *)malloc(sizeof(int) * machinesToWork); // Allocate Memory for the Buffers
        fscanf(getData, "%d", &operationNumber);                  // Operation Number
        for (int i = 0; i < (machinesToWork); i++)
        {
            fscanf(getData, "%d", &buffMach[i]);   // Get Machine
            fscanf(getData, "%d", &bufferTime[i]); // Get Time of the Machine
        }
        pAux = NewAtLoad(pAux, machinesToWork, operationNumber, buffMach, bufferTime); // Create Linked List
    }

    free(buffMach);   // Free Memory of the Buffer
    free(bufferTime); // Free Memory of the Buffer
    fclose(getData);  // Close File
    return (pAux);
   }
}

void ShowData(processes *pro, int min, int max, float avg, bool uploaded)
{
    if ((min == 0) || (max == 0) || (avg == 0))
    {
        printf("     Production Times      \n");
        printf("Maximum Time = %i\n", MaximumTime(pro, uploaded, max));
        printf("Miniimum Time = %i\n", MinimumTime(pro, uploaded, min));
        printf("Average Time = %0.2f\n", AverageTime(pro, uploaded, avg));
        printf("****************************\n");
    }
    else
    {
        printf("     Production Times      \n");
        printf("Maximum Time = %i\nMinimum Time = %i\nAverage Time = %0.2f\n", max, min, avg);
        printf("****************************\n");
    }

    while (pro != NULL) // Show all Machines and Times
    {
        printf("     Process Number  %i     \n", pro->operationNbr);
        for (int i = 0; i < pro->totalMachines; i++)
        {
            if (pro->workingMachines != NULL)
            {
                printf("Machine - %i --> Time--> %i\n", pro->workingMachines[i], pro->time[i]);
            }
            else
            {
                printf("Machine %i not in use!\n ", i + 1);
            }
        }
        pro = pro->nextProcesses; // Next node of the list
        printf("****************************\n");
    }
}
