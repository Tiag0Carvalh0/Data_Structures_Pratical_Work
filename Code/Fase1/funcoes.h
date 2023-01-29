#include <stdlib.h>
#include <stdbool.h>

// Struct of Job 1
typedef struct process
{
    int operationNbr, totalMachines;
    int *workingMachines, *time; // Dynamic Array

    struct process *nextProcesses;
} processes;

// Add Process Manually
processes *NewProcess(processes *mainProcess, int totalProcesses, bool uploaded, int newAdd);
// Add Process By Uploading From File
processes *NewAtLoad(processes *loadProcess, int totalMachines, int operationNumber, int *bufferMachines, int *bufferTimes);
// Remove Process From The List
int RemoveProcess(processes **proce, bool *loaded);
// Modify Data From a Process
int ModifyData(processes *pAux, bool *loaded);
// Calculate Minimum Time Needed For Complete All Processes
int MinimumTime(processes *pAux, bool uploaded, int min);
// Calculate Maximum Time Needed For Complete All Processes
int MaximumTime(processes *pAux, bool uploaded, int max);
// Calculate Average Time Of All Availabel Machines
float AverageTime(processes *pAux, bool uploaded, float avgDefault);
// Export Data to a File
void SaveData(processes *pAux, int min, int max, float avg, int processes, bool uploaded);
// Inport Data From a File
processes *GetData(processes *pAux, int *minTime, int *maxTime, float *avgTime, int *totalProcesses, bool *uploaded);
// Show All Machines And Times of Each Machine
void ShowData(processes *pro, int min, int max, float avg, bool uplaoded);