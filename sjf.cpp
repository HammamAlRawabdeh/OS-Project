#pragma once
#include<iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "Process.cpp"
using namespace std;


class sjf
{
public:
    //comperators 
    static  bool compsjf(const Process& l, const Process& r) {
        return l.bt > r.bt;
    }

    static bool compat(const Process& l, const Process& r) {
        return l.at < r.at;
    }

    // containers to store Processes 
    priority_queue<Process, vector<Process>, decltype(&sjf::compsjf)> sjfQueue{ sjf::compsjf };

    sjf(vector<Process> given)
    {
        input = given;
        ProcessCount = (int)given.size();
        TotalWaitTime = 0;
        TotalTurnAroundTime = 0;
        CurTime = 0;
    }

    int  getTotalWaitTime() const { return TotalWaitTime; }
    int  getTotalTurnAroundTime() const { return TotalTurnAroundTime; }
    vector<Process> answer()
    {
        // clean previous use and sort Processes on arrival time
        initailize();

        // main logic 

        int ArrivalIndex = 0;
        while (ArrivalIndex != ProcessCount || !sjfQueue.empty())
        {
            if (sjfQueue.empty()) {
                CurTime = input[ArrivalIndex].at;
                while (ArrivalIndex != ProcessCount && input[ArrivalIndex].at <= CurTime) {
                    sjfQueue.push(input[ArrivalIndex]);
                    ArrivalIndex++;
                }
            }
            Process WorkingProcess = sjfQueue.top();
            sjfQueue.pop();


            TotalWaitTime += CurTime - WorkingProcess.at;
            CurTime += WorkingProcess.bt;
            WorkingProcess.ct = CurTime;

            WorkingProcess.isCompleted = true;
            WorkingProcess.tat = CurTime - WorkingProcess.at;

            WorkingProcess.remaining_bt = 0;
            WorkingProcess.isCompleted = true;

            WorkingProcess.wt = WorkingProcess.tat - WorkingProcess.bt;

            TotalTurnAroundTime += CurTime - WorkingProcess.at;
            output.push_back(WorkingProcess);
            while (ArrivalIndex != ProcessCount && input[ArrivalIndex].at <= CurTime) {
                sjfQueue.push(input[ArrivalIndex]);
                ArrivalIndex++;
            }


        }
        // calc average wait time and turn around time 
        finalize();
        return output;
    }
    
private:
    vector<Process>input;
    vector<Process>output;
    // variables used for calculation
    int TotalWaitTime; // = summation(StartTime-at)/ProcessCount
    int TotalTurnAroundTime; // = summation(EndTime-StartTime)/ProcessCount
    int ProcessCount;
    int CurTime;

    //constructor
   

    //Main Logic 
    

    void initailize()
    {
        TotalWaitTime = 0;
        TotalTurnAroundTime = 0;
        CurTime = 0;
        ProcessCount = (int)input.size();

        sjfQueue = priority_queue<Process, vector<Process>, decltype(&sjf::compsjf)>(sjf::compsjf);
        sort(input.begin(), input.end(), sjf::compat);
    }

    void finalize()
    {
        sort(output.begin(), output.end(), [](const Process& l, const Process& r) {return l.id < r.id; });
        TotalTurnAroundTime /= (ProcessCount == 0 ? 1 : ProcessCount);
        TotalWaitTime /= (ProcessCount == 0 ? 1 : ProcessCount);
    }
};
