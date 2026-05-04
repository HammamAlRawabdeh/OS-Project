// Source: https://usaco.guide/general/io

#include<iostream>
#include <queue>
#include <vector>

using namespace std;


struct process 
{
    
    //  Burst Time is the the time left that the process needs to complete
    static int NextId;
    int Id;
    int ArivalTime;
    int BurstTime;
    int Priority;
    int TotalWatingTime;
    // to calculate total waiting time I will add a variable for this wait period start starts at the arrival time and each time the proccess is preemtively switched it changes to that time
    int WaitPeriodStart;

    //constructor AT arival time , bt burst time , p priority 
        process(int AT,int BT,int P = 1) {   
        this -> ArivalTime = AT;
        this -> BurstTime = BT;
        this -> Priority = P;
        TotalWatingTime=0;
        WaitPeriodStart = ArivalTime;
        Id=NextId;
        NextId++;
        }
        

    // comperator for sjf
};
int process::NextId=1;



struct sjf
{
    //comperators 
        static  bool compsjf(const process & l ,const process & r){
               return l.BurstTime > r.BurstTime;
             }

        static bool compArivalTime (const process & l ,const process & r){
               return l.ArivalTime < r.ArivalTime;
             }

    // containers to store proccesses 
        priority_queue<process,vector<process>,decltype(& sjf::compsjf )> sjfQueue{sjf::compsjf};
        vector<process>input;

    // variables used for calculation
        long double AverageWaitTime; // = summation(StartTime-ArivalTime)/ProcessCount
        long double AverageTurnAroundTime; // = summation(EndTime-StartTime)/ProcessCount
        int ProcessCount;
        int CurTime;

    //constructor
    sjf(vector<process>& given )
    {
        input = given;
        ProcessCount = (int)given.size();
        AverageWaitTime = 0;
        AverageTurnAroundTime = 0;
        CurTime = 0;
    }

    //Main Logic 
    void answer()
    {
        // clean previous use and sort proccesses on arrival time
        initailize();

        // main logic 

        int ArrivalIndex = 0;
        while(ArrivalIndex != ProcessCount || !sjfQueue.empty())
        {
            if(sjfQueue.empty()) {
                CurTime = input[ArrivalIndex].ArivalTime;
                while(ArrivalIndex != ProcessCount && input[ArrivalIndex].ArivalTime <= CurTime) {
                    sjfQueue.push(input[ArrivalIndex]);
                    ArrivalIndex++;
                }
            }
            process WorkingProcess = sjfQueue.top();
            sjfQueue.pop();


            AverageWaitTime += CurTime - WorkingProcess.ArivalTime;
            CurTime += WorkingProcess.BurstTime;
            AverageTurnAroundTime += CurTime - WorkingProcess.ArivalTime;

            while(ArrivalIndex != ProcessCount && input[ArrivalIndex].ArivalTime <= CurTime) {
                    sjfQueue.push(input[ArrivalIndex]);
                    ArrivalIndex++;
                }


        }
        // calc average wait time and turn around time 
        finalize();
    }

    void initailize()
    {
        AverageWaitTime = 0;
        AverageTurnAroundTime = 0;
        CurTime = 0 ; 
        ProcessCount = (int)input.size();

        sjfQueue= priority_queue<process,vector<process>,decltype(& sjf::compsjf )>(sjf::compsjf);
        sort(input.begin(),input.end(),sjf::compArivalTime);
    }

    void finalize()
    {
        AverageTurnAroundTime /= (ProcessCount == 0 ?  1:ProcessCount );
        AverageWaitTime /= (ProcessCount == 0 ?  1:ProcessCount );
    }
};
