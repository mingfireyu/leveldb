#include"statisticsmod.h"
#include<iostream>
using namespace std;
namespace leveldb{
StatisticsMod* StatisticsMod::mInstance = NULL;

unsigned long long inline  timevalTous(struct timeval &res) {
  return res.tv_sec * S2US + res.tv_usec;
}



long long unsigned int StatisticsMod::timeAddto(timeval& start_time, long long unsigned int& resTime)
{
    struct timeval end_time,res;
    unsigned long long diff;
    gettimeofday(&end_time,NULL);
    timersub(&end_time,&start_time,&res);
    diff = timevalTous(res);
    resTime += diff;
    return diff;
}

inline long long unsigned int  StatisticsMod::timeAddto(double timeElapsed,unsigned long long &resTime){
    resTime += timeElapsed*S2US;
    return resTime;
}
StatisticsMod* StatisticsMod::getInstance(){
  if(mInstance == NULL){
      mInstance  = new StatisticsMod();
    }
    return mInstance;
}

void StatisticsMod::DestroyInstance(){
   if(mInstance != NULL){
      delete mInstance;
      mInstance = NULL;
    }
}

StatisticsMod::StatisticsMod(){
    for(unsigned int i = 0 ; i < STATISTICSNUMLENGTH ; i++){
      nums[i] = 0;
      counts[i] = 0;
    }
    statisticsOpen = true;

    

}

long long unsigned int StatisticsMod::getElapsedTime(int index)
{
    return nums[index];
}


StatisticsMod::~StatisticsMod()
{
    unsigned long long sum = 0;
    unsigned int i;
    for(i = 0 ; i < STATISTICSNUMLENGTH ; i++){
	    printf("%llu,%s,%llu\n",counts[i],statisticsString[i], StatisticsMod::getInstance()->getElapsedTime(i));
    }
    
}

long long unsigned int StatisticsMod::timeProcess(double timeElapsed, unsigned int i)
{
    if(statisticsOpen){
	counts[i]++;
	nums[i] += timeElapsed*S2US;
	return nums[i];
    }
    return 0;
}


unsigned long long StatisticsMod::timeProcess(struct timeval &start_time,unsigned int i){

  if(statisticsOpen){
       counts[i]++;
       return  timeAddto(start_time,nums[i]);
    }
    return 0;
}

void StatisticsMod::openStatistics()
{
    statisticsOpen  =  true;
    gettimeofday(&totalTime,NULL);

}



long long unsigned int StatisticsMod::bytesProcess(long long unsigned int bytes, unsigned int i)
{
	nums[i] += bytes;
	return nums[i];
}
};
