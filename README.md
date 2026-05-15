# CPU Scheduling Algorithms – Performance Evaluation

## 📌 Overview

This project is developed for the Operating Systems course (CS11335). It focuses on implementing and comparing CPU scheduling algorithms to evaluate their performance. 

The project uses a **Centralized Interactive Evaluator** built in C++. This CLI tool allows users to input a single set of processes and test them across multiple algorithms sequentially to compare their efficiency.

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

You can run this project either through an IDE or through the terminal.

### Option 1 : Download and Run Porject1.exe (may or may not work depending on Operating system and CPU architicture of the system)

### Option 2: Run through an IDE

1. Open the project folder in a C++ IDE.
2. Make sure `main.cpp` and all required files are included in the project.
3. Run the program from the IDE terminal.
4. Follow the prompts to enter process data and select scheduling algorithms.

### Option 3: Run through the terminal

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

* Asaad — FCFS
* Ghaith — SJF
* Abdullah — Round Robin
* Hammam — Priority Scheduling (Non-Preemptive)
* Khaled — SRTF

## 📊 Results

Using a 5-process dataset (P1: AT=0 BT=5, P2: AT=2 BT=4, P3: AT=3 BT=2, P4: AT=15 BT=1, P5: AT=16 BT=3), the following results were obtained:

| Algorithm | Avg Turnaround Time | Avg Waiting Time |
|-----------|---------------------|------------------|
| FCFS      | 4.80                | 1.80             |
| RR (q=2)  | 5.60                | 2.60             |
| SJF       | 4.40                | 1.40             |
| Priority  | 4.80                | 1.80             |

SJF achieved the lowest average waiting and turnaround times for this dataset by scheduling shorter jobs first. Round Robin had the highest averages due to the overhead of context switching with a small time quantum.

## 📄 Notes

This project follows course guidelines and includes both implementation and analysis of CPU scheduling algorithms.
[View Project Guidelines](./OS_Project_Guidelines.pdf)
[View Report Grade Form](./Report_Grade_Form.pdf)


## 🧠 How It Works

The evaluator ensures fair comparisons by keeping the original input unchanged across all algorithm runs:
1. **Single Input Phase:** The user enters Arrival Time, Burst Time, and Priority for all processes once.
2. **Data Encapsulation:** Process data is stored in a vector of `Process` objects using getters and setters.
3. **Pass-by-Value Execution:** Each algorithm receives a fresh copy of the process list, so modifications (like marking a process as completed) don't affect subsequent runs.

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

========================== Final Results ==========================
Process   Arrival   Burst   Priority  Completion   Turnaround   Waiting
-------------------------------------------------------------------
P1        0         5       3         5            5            0
P2        2         4       1         9            7            3
P3        3         2       4         11           8            6
P4        15        1       2         16           1            0
P5        16        3       5         19           3            0
-------------------------------------------------------------------
Average Turnaround Time = 4.80
Average Waiting Time    = 1.80
===================================================================

Do you want to try another algorithm for the same processes? (y/n):

