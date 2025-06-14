#include "PrintJob.h"

PrintJob::PrintJob (int setP, int setJ,int numP)
  : priority(setP), jobNumber(setJ), numPages(numP)
{
}

// Return priority
int PrintJob::getPriority() const {
    return priority;
}

// Return jobNumber
int PrintJob::getJobNumber() const {
    return jobNumber;
}

// Return numPages
int PrintJob::getPages() const {
    return numPages;
}
