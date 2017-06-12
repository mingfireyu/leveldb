#ifndef _STATISTICS_MOD_H
#define _STATISTICS_MOD_H
#include <vector>
#define S2US 1000000
#include "stdio.h"
#include <sys/time.h>
#include<climits>
namespace leveldb{
    const char statisticsString[][50]={"WAIT","WRITETOLOG","WRITETOMEMTABLE","ARENAALLOCATE","MEMCPY","TABLEINSERT","MEMTABLEADD"};
    enum Statistics{
      WAIT,WRITETOLOG,WRITETOMEMTABLE,ARENAALLOCATE,MEMCPY,TABLEINSERT,MEMTABLEADD,STATISTICSNUMLENGTH
    };
    class StatisticsMod {
 
    public:
      static unsigned long long timeAddto(struct timeval &start_time,unsigned long long &resTime);
      static unsigned long long timeAddto(double timeElapsed,unsigned long long &resTime);  
      static StatisticsMod *getInstance();
  
      static void DestroyInstance();
  
    private:
      StatisticsMod();
      ~StatisticsMod();
    public:
      unsigned long long timeProcess(struct timeval &start_time,unsigned int i);
      unsigned long long timeProcess(double timeElapsed,unsigned int i);
      unsigned long long bytesProcess(unsigned long long bytes,unsigned int i);
      unsigned long long getElapsedTime(int index);
      void openStatistics();

      bool statisticsOpen;
      static StatisticsMod* mInstance;
      unsigned long long nums[STATISTICSNUMLENGTH];
      unsigned long long counts[STATISTICSNUMLENGTH];
      struct timeval totalTime;  
    };

};
#endif
