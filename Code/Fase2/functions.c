#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <malloc.h>
#include "functions.h"
#include "user.h"

//********************************************Jobs Functions**************************************************************//

jobs *NewJob(jobs *mainJob, int totalNewJobs, int jobNumb)
{

    jobs *jAux = mainJob, *newJob = (jobs *)malloc(sizeof(jobs));
    ;
    if (newJob != NULL)
    {
        if (jAux == NULL) // First Jobs Of The List
        {
            newJob->jobNumber = jobNumb; //Associate Job Number
            newJob->totalProcesses = 0; 
            newJob->processList = NULL;//Create Empty List Of Processes
            newJob->nextJob = jAux;

            return (newJob);
        }
        else
        {
            while (jAux->nextJob != NULL)
            {
                jAux = jAux->nextJob;
            }
            newJob ->jobNumber = jobNumb;//Associate Job Number
            newJob->totalProcesses = 0;
            newJob->processList = NULL;//Create Empty List Of Processes
            newJob->nextJob = NULL;//Last Item of the List
            jAux->nextJob = newJob;
            return (mainJob);
        }
    }
    else
    {
        return (jAux);
    }
}

jobs *NewAtUpload(jobs *mainJob, int jobNbr, int totalProc, int *operationNumber, int *totalMachines, int operations, int *buffMach, int *bufferTime, int lastPos)
{
    jobs *jAux = mainJob, *newJob = (jobs *)malloc(sizeof(jobs));
    int retirados = 0;
    if (newJob != NULL)
    {
        if (jAux == NULL)
        {
            newJob->jobNumber = jobNbr;//Associate Job Number
            newJob->processList = NULL;//Create Empty List of Processes
            //Create the Processes
            for (int i = 0; i < totalProc; i++)
            {
                newJob->processList = NewAtLoad(newJob->processList, totalMachines, operationNumber, i, buffMach, bufferTime, retirados);
                retirados = retirados + (totalMachines[i]);
            }
            newJob->totalProcesses = totalProc;
            newJob->nextJob = jAux;
            return (newJob);
        }
        else
        {
            while (jAux->nextJob != NULL)
            {
                jAux = jAux->nextJob;
            }
            newJob->jobNumber = jobNbr;//Associate Job Number
            newJob->processList = NULL; //Create Empty List of Processes
            //Create the Processes
            for (int i = 0; i < totalProc; i++)
            {
                newJob->processList = NewAtLoad(newJob->processList, totalMachines, operationNumber, i, buffMach, bufferTime, retirados);
                retirados = retirados + (totalMachines[i]);
            }

            newJob->totalProcesses = totalProc;
            newJob->nextJob = NULL; //End of the List
            jAux->nextJob = newJob;
            return (mainJob);
        }
    }
    else
    {
        return (jAux);
    }
}

jobs *LoadFromFile(jobs *mainJob, int *totalJobs)
{
    jobs *jobAux = mainJob;
    FILE *getDataFile;                       // Variable of FILE type
    getDataFile = fopen("allData.txt", "r"); // Open to Read

    int *totalMachines, *operationNumber, totalProc, jobNbr, operations;
    int *buffMach, *bufferTime; // Auxiliar Buffers
    int lastPos = 0;

    fscanf(getDataFile, "%d", &(*totalJobs)); // Total Of Jobs
    for (int i = 0; i < (*totalJobs); i++)
    {
        fscanf(getDataFile, "%d", &jobNbr);                       // Job Number
        fscanf(getDataFile, "%d", &totalProc);                    // Total Processes
        operationNumber = (int *)malloc(sizeof(int) * totalProc); // Allocate Memory for the Buffer
        totalMachines = (int *)malloc(sizeof(int) * totalProc);   // Allocate Memory for the Buffers
        buffMach = (int *)malloc(sizeof(int) * 30);               // Allocate Memory for the Buffers
        bufferTime = (int *)malloc(sizeof(int) * 30);             // Allocate Memory for the Buffers

        for (int j = 0; j < totalProc; j++)
        {
            fscanf(getDataFile, "%d", &operationNumber[j]);//Number of the Operation
            fscanf(getDataFile, "%d", &totalMachines[j]); // Number of machines in this operation

            for (int k = 0; k < (totalMachines[j]); k++)
            {
                fscanf(getDataFile, "%d", &buffMach[lastPos + k]);   // Get Machine
                fscanf(getDataFile, "%d", &bufferTime[lastPos + k]); // Get Time of the Machine
            }
            lastPos = lastPos + (totalMachines[j]);
        }
        lastPos = 0;
        mainJob = NewAtUpload(mainJob, jobNbr, totalProc, operationNumber, totalMachines, operations, buffMach, bufferTime, lastPos);

        free(operationNumber); // Free Memory of the Buffer
        free(totalMachines);   // Free Memory of the Buffer
        free(buffMach);        // Free Memory of the Buffer
        free(bufferTime);      // Free Memory of the Buffer
    }
    fclose(getDataFile); // Close File
    return (mainJob);
}

int RemoveJobs(jobs **mainjob, int toRemove)
{
    int count = 0;
    if ((*mainjob)->jobNumber == toRemove)
    {
        jobs *removeJob = *mainjob;
        *mainjob = (*mainjob)->nextJob;
        free(removeJob->processList->time);
        free(removeJob->processList->workingMachines);
        free(removeJob->processList);
        free(removeJob);
        // Reorder Jobs Numbers
        jobs *reOrder = *mainjob;
        while (reOrder != NULL)
        {
            if (reOrder->jobNumber == 1)
            {
                reOrder = reOrder->nextJob;
            }
            else
            {
                reOrder->jobNumber = (reOrder->jobNumber) - 1;
                reOrder = reOrder->nextJob;
            }
        }
        free(reOrder);
        return (1);
    }

    for (jobs *curr = *mainjob; curr != NULL; curr = curr->nextJob)
    {
        if (curr->nextJob->jobNumber == toRemove)
        {
            jobs *remove = curr->nextJob;
            curr->nextJob = curr->nextJob->nextJob;
            free(remove->processList->time);
            free(remove->processList->workingMachines);
            free(remove->processList);
            free(remove);
            // Reorder Jobs Numbers
            jobs *reOrder = *mainjob;
            while (reOrder != NULL)
            {
                if (reOrder->jobNumber == 1)
                {
                    reOrder = reOrder->nextJob;
                }
                else
                {
                    reOrder->jobNumber = (reOrder->jobNumber) - 1;
                    reOrder = reOrder->nextJob;
                }
            }
            free(reOrder);
            return (1);
        }
    }
}

processes *SaveAllData(jobs *mainJob, int totalJobs)
{
    jobs *export = mainJob;
    processes *head = mainJob->processList;

    FILE *saveAllData;                       // Variable of FILE type
    saveAllData = fopen("allData.txt", "w"); // Open to Writte

    if (saveAllData != NULL)
    {
        fprintf(saveAllData, "%i\n", totalJobs);
        while (mainJob != NULL)
        {

            fprintf(saveAllData, "%i\n", mainJob->jobNumber); //Save The Number of the Job
            fprintf(saveAllData, "%i\n", mainJob->totalProcesses);//Save Total Of Processes on the Job
            while (mainJob->processList != NULL)
            {
                fprintf(saveAllData, "%i\n", mainJob->processList->operationNbr); //Save Operation Number
                fprintf(saveAllData, "%i\n", mainJob->processList->totalMachines); //Save Total Of Machines in the Process
                for (int i = 0; i < mainJob->processList->totalMachines; i++)
                {
                    fprintf(saveAllData, "%i\n%i\n", mainJob->processList->workingMachines[i], mainJob->processList->time[i]);//Save Machines and Times
                }
                mainJob->processList = mainJob->processList->nextProcesses;
            }
            mainJob = mainJob->nextJob;
        }
    }
    fclose(saveAllData);
    return (head);
}

processes *ShowAllData(jobs *jAux)
{
    int count = 0;
    processes *aux = jAux->processList;
    while (jAux != NULL)
    {
        printf("Job Number [%i]\n", jAux->jobNumber); //Print Job Number

        while (jAux->processList != NULL)
        {
            printf("****************************\n");
            printf("     Process Number  %i     \n", jAux->processList->operationNbr); //Print Number Of Operation
            for (int i = 0; i < (jAux->processList->totalMachines); i++)
            {
                if (jAux->processList->workingMachines != NULL)
                {
                    printf("Machine --> %i - Time--> %i\n", jAux->processList->workingMachines[i], jAux->processList->time[i]); //Print Machines and Times
                }
            }
            jAux->processList = jAux->processList->nextProcesses;
            printf("****************************\n");
        }
        count++;
        jAux = jAux->nextJob;
    }
    return (aux);
}

processes *EditJobs(jobs *jAux, int toModify, int newJobNbr, bool *loaded)
{
    jobs *aux = jAux;
    jobs *ascending = jAux;
    processes *head ;
    int modified, repeatNewJob, prev = 0;
    // Compare if the Job Already Exist
    while (aux != NULL)
    {
        if (aux->jobNumber == newJobNbr) //Compare if the Job is Available
        {
            printf("Select a Vailable Job\n ");
            return (head);
        }
        aux = aux->nextJob;
    }
    while (jAux != NULL)
    {
        if (jAux->jobNumber == toModify)
        {
            head = jAux->processList;
            if (newJobNbr != 00)
            {

                jAux->jobNumber = newJobNbr; //New Job Number
                modified = ModifyData(jAux->processList, &(*loaded));//Modify Data
                 jAux->processList = head;
                return (head);
            }
            else
            { 
                modified = ModifyData(jAux->processList, &(*loaded)); //Modify Data
                 jAux->processList = head;
                return (head);
            }
        }
        jAux->processList = head;
        jAux = jAux->nextJob;
    }
}

int AvailableJobs(jobs *jAux)
{
    int selected;
    while (jAux != NULL)
    {
        printf("[%i] ", jAux->jobNumber);
        jAux = jAux->nextJob;
    }
    printf("\n");
    scanf("%i", &selected);
    return (selected);
}

void FJSSP(jobs *jAux)
{
    jobs *head = jAux;
    jobs *saveOp = jAux;
    processes *headProc[8];
    int counterOp = 0, totalTime;
    int timesPerMachine[8];     //Save the Total Time on Each Machine
    int timesPerJob[8];            //Save Total Time Per Job
    int myTable[8][200];                                 // 8 Machines and 100 Units of Time;
    memset(myTable, 0, sizeof(myTable));                 // Set all positions to 0
    memset(timesPerMachine, 0, sizeof(timesPerMachine)); // Set all positions to 0
    memset(timesPerJob, 0, sizeof(timesPerJob));         // Set all positions to 0

    int minor = 0, machine = 0, next = 1, operationNmber, lastMachine;
    int lastTime = 0, lastTimeDifMachine = 0;
    int aux;
    int tempo = 0;

    while (saveOp != NULL) //Save All Head In 1 Array
    {
        headProc[((saveOp->jobNumber) - 1)] = saveOp->processList;
        saveOp = saveOp->nextJob;
    }

    while (next <= 8)
    {
        jAux = head;
        while (jAux != NULL)
        {
            jAux->processList = headProc[counterOp];

            while (jAux->processList != NULL)
            {
                if (jAux->processList->operationNbr == next)
                {
                    for (int i = 0; i < jAux->processList->totalMachines; i++)
                    {
                        if (i == 0)
                        {
                            minor = jAux->processList->time[i]; // First Time is the Minor
                            machine = jAux->processList->workingMachines[i];
                        }
                        else if (minor > jAux->processList->time[i]) // Compare if the Next Time is Lower than the Minor
                        {
                            minor = jAux->processList->time[i]; // If True, New Minor is The Value of That Machine
                            machine = jAux->processList->workingMachines[i];
                        }
                        else if (minor == jAux->processList->time[i]) //In Case of Equal Times, it Chooses the Machine with Less Time
                        {
                            if (timesPerMachine[jAux->processList->workingMachines[i - 1]] < jAux->processList->workingMachines[machine - 1]) 
                            {
                                machine = jAux->processList->workingMachines[i];
                            }
                        }
                    }
                }
                jAux->processList = jAux->processList->nextProcesses;
            }
            for (int i = 1; i <= minor; i++)
            {

                tempo = timesPerMachine[machine - 1];                          
                myTable[machine - 1][tempo] = ((jAux->jobNumber * 10) + next); //Place the Data in the Array
                timesPerMachine[machine - 1]++;
            }
            timesPerJob[((jAux->jobNumber) - 1)] = timesPerJob[((jAux->jobNumber) - 1)] + timesPerMachine[machine - 1] + 1;

            for (int i = 0; i < 8; i++) //Calculate Total Time To Start the Next Operation
            {
                if (timesPerMachine[machine - 1] > totalTime)
                {
                    totalTime = timesPerMachine[machine - 1];
                }
            }
            lastMachine = machine;
            minor = 0;
            jAux->processList = headProc[counterOp];
            jAux = jAux->nextJob;
            counterOp++;
        }
        for (int i = 0; i < 8; i++) 
        {
            timesPerMachine[i] = totalTime;
        }
        next++;
        counterOp = 0;
    }
    ExportFJSSPTable(myTable, totalTime);
}

void ExportFJSSPTable(int myArray[8][200], int totalTime)
{
    FILE *escalationTable;                     // Variable of FILE type
    escalationTable = fopen("FJSSP.txt", "w"); // Open to Writte
    if (escalationTable != NULL)
    {
        fprintf(escalationTable, "\t\t\t");
        for (int j = 1; j <= totalTime; j++)
        {
            fprintf(escalationTable, "T[%i]\t", j); //Print Coloumns That Represent Time Line
        }
        fprintf(escalationTable, "\n");

        for (int k = 0; k < 8; k++)
        {
            fprintf(escalationTable, "Maquina [%i]\t", k + 1); //Print Rows That Represent Machines
            for (int i = 0; i < totalTime; i++)
            {
                if (myArray[k][i] == 0)
                {
                    fprintf(escalationTable, "----  \t"); //If There is no Job Print "---" to Better Visualization
                }
                else
                    fprintf(escalationTable, "J%i O%i \t", (myArray[k][i] / 10), ((myArray[k][i]) % 10)); //Print All The Data
            }
            fprintf(escalationTable, "\n\n");
        }
        fprintf(escalationTable, "Total Time = %i Minutes\n", totalTime); //Total Time to Complete the Table
    }
    else
        printf("ERROR OPENING FILE\n");
    fclose(escalationTable);
}

//********************************************Processes Functions*********************************************************//

processes *NewProcess(processes *mainProcess, int totalProcesses, bool uploaded, int newAdd)
{
    processes *pAux = mainProcess, *newProcess = (processes *)malloc(sizeof(processes));
    ; // Alocate Memory

    int numOfMachines, time, operationNumber, workMac, prev = 0, total;

    if (newProcess != NULL)
    {
        if (pAux == NULL) // First of the list
        {

            printf("Please Insert Process Number!");
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
            printf("Please Insert Process Number!");
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

processes *NewAtLoad(processes *loadProcess, int *totalMachines, int *operationNumber, int counter, int *bufferMachines, int *bufferTimes, int lastPos)
{
    processes *pAux = loadProcess, *newProcess = (processes *)malloc(sizeof(processes));

    if (newProcess != NULL)
    {
        if (pAux == NULL)
        {
            newProcess->operationNbr = operationNumber[counter];
            newProcess->totalMachines = totalMachines[counter];
            // Create Arrays to Store the Process Data and Allocate Dynamic Memory for Them
            newProcess->workingMachines = (int *)malloc(sizeof(int) * (newProcess->totalMachines));
            newProcess->time = (int *)malloc(sizeof(int) * (newProcess->totalMachines));

            for (int i = 0; i < (newProcess->totalMachines); i++) // Fill the Arrays with the Buffer Data
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
            newProcess->operationNbr = operationNumber[counter];
            newProcess->totalMachines = totalMachines[counter];
            // Create Arrays to Store the Process Data and Allocate Dynamic Memory for Them
            newProcess->workingMachines = (int *)malloc(sizeof(int) * (newProcess->totalMachines));
            newProcess->time = (int *)malloc(sizeof(int) * (newProcess->totalMachines));

            for (int i = 0; i < (newProcess->totalMachines); i++) // Fill The Arrays with the Buffer Data
            {
                newProcess->workingMachines[i] = bufferMachines[lastPos + i];
                newProcess->time[i] = bufferTimes[lastPos + i];
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
    processes *head = pAux;
    int toModify, changeMachine, new = 0, newTime = 0, newMach = 0, count = 0, menu = 0, last = 0;
    ;
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
           printAux = head;
            // Copy Data From the Struct
            bufferMach = (int *)malloc(sizeof(int) * (pAux->totalMachines));
            bufferTime = (int *)malloc(sizeof(int) * (pAux->totalMachines));

            processes *newMachine = head; // Create Aux variable of processes tyep

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
                    newMachine->totalMachines = (newMachine->totalMachines) + new; // Increment Total of Machines
                    // Free The Space of the Arrays
                    free(newMachine->workingMachines);
                    free(newMachine->time);
                    // Alocate new Space For The new Total Of Machines
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
                        else // When its Time to Add the New Machine
                        {
                            printf("Insert New Machine Number\n");
                            scanf("%i", &newMach);
                            while (newMach <= last) // Check if the Machine is Available
                            {
                                printf("Machine Should Be Higher then %i\n", last);
                                scanf("%i", &newMach);
                            }
                            last = newMach;
                            printf("Insert New Time\n");
                            scanf("%i", &newTime); // Get New Time
                            newMachine->workingMachines[i] = newMach;
                            newMachine->time[i] = newTime;
                        }
                    }
                }
                newMachine = newMachine->nextProcesses;
            }
            free(bufferMach); // Free Buffer Memory
            free(bufferTime); // Free Buffer Memory
            free(newMachine); // Free aux Variable
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
         printAux = head;
            printf("\nProcess To Modify ");
            scanf("%i", &toModify);
            printf("\n");

            processes *toRemove = head;; // Aux Variable of Processes Type
            int remove, auxMach[9], auxTime[9], line = 0;

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

                    for (int i = 0; i < toRemove->totalMachines; i++) // Save The Machines in a aux Array
                    {
                        auxMach[i] = toRemove->workingMachines[i];
                        auxTime[i] = toRemove->time[i];
                    }
                    // Free the Space and Alocate New One
                    free(toRemove->workingMachines);
                    free(toRemove->time);
                    toRemove->totalMachines = (toRemove->totalMachines) - 1; // Decrement the Total Machines
                    // Alocate New Space For the New Total Machines
                    toRemove->workingMachines = (int *)malloc(sizeof(int) * (toRemove->totalMachines));
                    toRemove->time = (int *)malloc(sizeof(int) * (toRemove->totalMachines));

                    for (int i = 0; i < toRemove->totalMachines; i++)
                    {
                        if (auxMach[line] == remove)
                        {
                            line = line + 1; // Skip the Removed Machine
                        }
                        toRemove->workingMachines[i] = auxMach[line];
                        toRemove->time[i] = auxTime[line];
                        line++;
                    }
                }
                toRemove = toRemove->nextProcesses;
            }
            free(toRemove); // Free aux Variable
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
            printAux = head;
            int newMach = 0, pos = 0, machSelec = 0, aux;
            printf("\nProcess To Modify ");
            scanf("%i", &toModify);
            printf("\n");
            processes *newMachNum = head; // Aux Variable of Processes Type
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
                    // Check if the machine is valid
                    for (int i = 0; i < newMachNum->totalMachines; i++)
                    {
                        if (newMach == valid[i])
                        {
                            printf("Select Valid Machine\n");
                            return (0);
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
            free(newMachNum); // Free aux Variable
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
            printAux = head;
            processes *changeTime = head;; // Aux Variable of Processes Type
            printf("\nProcess To Modify ");
            scanf("%i", &toModify);
            printf("\n");
            while (changeTime != NULL)
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
            free(changeTime); // Free aux Variable
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
