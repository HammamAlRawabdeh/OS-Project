# CPU Scheduling Algorithms – Performance Evaluation

## 📌 Overview

This project is developed for the Operating Systems course (CS11335). It focuses on implementing and comparing CPU scheduling algorithms to evaluate their performance. 

To ensure highly accurate comparisons and adhere strictly to project guidelines, the team has engineered a **Centralized Interactive Evaluator** built entirely in C++. This CLI tool allows users to input a single set of processes and test them across multiple algorithms sequentially to observe differences in efficiency.

## ⚙️ Implemented Algorithms

* First-Come First-Served (FCFS)
* Round Robin (RR)
* Shortest Job First (SJF)
* Priority Scheduling (Non-Preemptive)
* Shortest Remaining Time First (SRTF)

## 🎯 Objective

Evaluate and compare scheduling algorithms using a shared, identical dataset based on:
* Average Waiting Time
* Average Turnaround Time

## 🛠️ Technologies Used

* C++ (Standard Library)
* Object-Oriented Programming (OOP) architecture for process data encapsulation.

## ▶️ How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/HammamAlRawabdeh/OS-Project.git
   cd OS-Project
   ```
2. Compile:
   ```bash
   g++ -o main main.cpp
   ```
3. Run:
   ```bash
   ./main
   ```
4. Follow the prompts to enter process data and select scheduling algorithms.

## 👥 Team Members

* Assad — FCFS
* Ghaith — SJF
* Abdullah — Round Robin
* Hammam — Priority Scheduling (Non-Preemptive)
* Khaled — SRTF

## 📊 Results

The performance of each algorithm is evaluated using:

* Average Waiting Time
* Average Turnaround Time

Results are presented using tables.

## 📄 Notes

This project follows course guidelines and includes both implementation and analysis of CPU scheduling algorithms.
[View Project Guidelines](./OS_Project_Guidelines.pdf)
[View Report Grade Form](./Report_Grade_Form.pdf)


## 🧠 How It Works (Under the Hood)

To guarantee that our performance comparisons are 100% accurate, the evaluator uses a **Master State Architecture**:
1. **Single Input Phase:** The user is prompted only once to enter the Arrival Time, Burst Time, and Priority for all processes. 
2. **Data Encapsulation:** This data is stored in a master vector of `Process` objects, protecting the initial state.
3. **Pass-by-Value Execution:** When the user selects an algorithm from the menu, the evaluator passes a *fresh copy* of the master list to the function. This ensures that process mutations (like updating remaining burst times or marking a process as completed) do not corrupt the data for the next algorithm.

## 💻 Sample Execution

Below is an example of what the interactive terminal looks like when testing the **Priority Scheduling (Non-Preemptive)** algorithm with a 5-process dataset.
```text
=== CPU Scheduling Algorithms Evaluator ===
Enter Number of Processes: 5

--- Process P1 ---
Arrival Time: 0
Burst Time: 5
Priority (Lower number = Higher priority): 3

... [Inputs for P2, P3, P4, P5] ...

=========================================
What scheduling algorithm would you try?
For First-Come First-Served enter (FCFS)
For Round Robin enter (RR)
For Shortest Job First enter (SJF)
For Priority Scheduling Non-Preemptive enter (Priority)
For Shortest Remaining Time First enter (SRTF)
Enter choice: Priority

>>> Running Priority <<<

--- Execution Trace ---
Time 0: Process P1 starts execution.
Time 5: Process P1 finishes.
Time 5: Process P2 starts execution.
Time 9: Process P2 finishes.
Time 9: Process P3 starts execution.
Time 11: Process P3 finishes.
Time 11: CPU is IDLE.
Time 12: CPU is IDLE.
Time 13: CPU is IDLE.
Time 14: CPU is IDLE.
Time 15: Process P4 starts execution.
Time 16: Process P4 finishes.
Time 16: Process P5 starts execution.
Time 19: Process P5 finishes.

================ Final Results ================
Process AT      BT      Pri     CT      TAT     WT
-----------------------------------------------
P1      0       5       3       5       5       0
P2      2       4       1       9       7       3
P3      3       2       4       11      8       6
P4      15      1       2       16      1       0
P5      16      3       5       19      3       0
-----------------------------------------------
Average Turnaround Time = 4.80
Average Waiting Time    = 1.80
===============================================

Do you want to try another algorithm for the same processes? (y/n):

