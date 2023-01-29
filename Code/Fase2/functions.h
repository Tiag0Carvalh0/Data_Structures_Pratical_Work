#include <stdlib.h>
#include <stdbool.h>

//****************************************************Structs**************************************************************//
// Struct of Job 1
typedef struct process
{
    int operationNbr, totalMachines;
    int *workingMachines, *time; // Dynamic Array
    struct process *nextProcesses;
} processes;

typedef struct job
{
    int jobNumber , totalProcesses;
    struct job *nextJob; //Next job on the list
    processes *processList;

} jobs;

//****************************************************Jobs Functions**************************************************************//

// Add New Jobs Manually
jobs *NewJob(jobs *mainJob, int totalNewJobs, int jobNumb);
// Add New Jobs bt File
jobs *NewAtUpload(jobs *mainJob, int jobNbr, int totalProc, int *operationNumber, int *totalMachines, int operations, int *buffMach, int *bufferTime, int lastPos);
// Get Data From File
jobs *LoadFromFile(jobs *mainJob, int *totalJobs);
// Remove Jobs
int RemoveJobs(jobs **mainjob, int toRemove);
// Save To File
processes *SaveAllData(jobs *mainJob, int totalJobs);
// Show All Data
processes *ShowAllData(jobs *jAux);
// Edit Jobs Data
processes *EditJobs(jobs *jAux, int toModify, int newJobNbr, bool *loaded);
// Print Available Jobs
int AvailableJobs(jobs *jAux);
// FJSSP
void FJSSP(jobs *jAux);
// Export FJSSP Table
void ExportFJSSPTable(int myArray[8][200], int totalTime);
//****************************************************Procecess Functions**************************************************************//

// Add Process Manually
processes *NewProcess(processes *mainProcess, int totalProcesses, bool uploaded, int newAdd);
// Add Process By Uploading From File
processes *NewAtLoad(processes *loadProcess, int *totalMachines, int *operationNumber, int counter, int *bufferMachines, int *bufferTimes, int lastPos);
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
// Show All Machines And Times of Each Machine
void ShowData(processes *pro, int min, int max, float avg, bool uplaoded);