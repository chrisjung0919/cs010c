#pragma once

class PrintJob {
private:
  // Private variables
  int priority;
  int jobNumber;
  int numPages;

public:
  // Public functions
  PrintJob(int priority, int jobNum, int numPages);
  int getPriority() const;
  int getJobNumber() const;
  int getPages() const;
};
