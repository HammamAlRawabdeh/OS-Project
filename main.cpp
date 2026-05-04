#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// ==========================================
// 1. ROBUST PROCESS CLASS (Encapsulation)
// ==========================================
class Process {
private:
    string id;  // id = Process ID (e.g., "P1")
    int at, bt, pri;    // at = Arrival Time (When it enters the ready queue)
                        // bt = Burst Time (How much CPU time it needs)
                        // pri = Priority (Lower number = Higher priority)
    
    int ct, tat, wt, remaining_bt;  // ct = Completion Time (When it finishes)
                                    // tat = Turnaround Time (Completion Time - Arrival Time)
                                    // wt = Waiting Time (Turnaround Time - Burst Time)
                                    // remaining_bt = Remaining Burst Time (Crucial for RR and SRTF)
    bool isCompleted;   // isCompleted = Status flag (false = waiting/running, true = finished)

public:
    // Constructor
    Process() : id(""), at(0), bt(0), pri(0), ct(0), tat(0), wt(0), remaining_bt(0), isCompleted(false) {}

    // --- GETTERS ---
    // TEAM REMINDER: Because variables are private, you cannot write p[i].bt anymore.
    // You MUST use these functions to read data. Example: if (p[i].getAt() <= time)
    string getId() const { return id; }
    int getAt() const { return at; }
    int getBt() const { return bt; }
    int getPri() const { return pri; }
    int getCt() const { return ct; }
    int getTat() const { return tat; }
    int getWt() const { return wt; }
    int getRemainingBt() const { return remaining_bt; }
    bool getIsCompleted() const { return isCompleted; }


    // --- SETTERS WITH VALIDATION ---
    // TEAM REMINDER: You MUST use these functions to modify data. 
    // Example: To update completion time, write p[i].setCt(currentTime);    
    void setId(string new_id) {
        if (!new_id.empty()) id = new_id;
        else cout << "Warning: ID cannot be empty.\n";
    }

    void setAt(int new_at) {
        if (new_at >= 0) at = new_at;
        else {
            cout << "Warning: Arrival time cannot be negative. Defaulting to 0.\n";
            at = 0;
        }
    }

    void setBt(int new_bt) {
        if (new_bt > 0) {
            bt = new_bt;
            remaining_bt = new_bt; // Automatically sync remaining burst time
        } else {
            cout << "Warning: Burst time must be greater than 0. Defaulting to 1.\n";
            bt = 1;
            remaining_bt = 1;
        }
    }

    void setPri(int new_pri) { pri = new_pri; } // Priorities can theoretically be negative, so we allow it.
    
    void setCt(int new_ct) { if (new_ct >= 0) ct = new_ct; }
    void setTat(int new_tat) { if (new_tat >= 0) tat = new_tat; }
    void setWt(int new_wt) { if (new_wt >= 0) wt = new_wt; }
    void setRemainingBt(int r_bt) { if (r_bt >= 0) remaining_bt = r_bt; }
    void setCompleted(bool status) { isCompleted = status; }
};

// ==========================================
// 2. ALGORITHM PROTOTYPES
// ==========================================
void runFCFS(vector<Process> p);
void runRR(vector<Process> p, int time_quantum);
void runSJF(vector<Process> p);
void runPriority(vector<Process> p);
void runSRTF(vector<Process> p);

// Helper function for sorting by Arrival Time
bool compareArrival(const Process& a, const Process& b) {
    return a.getAt() < b.getAt();
}

// ==========================================
// 3. MAIN EVALUATOR HUB
// ==========================================
int main() {
    int n;
    cout << "=== CPU Scheduling Algorithms Evaluator ===\n";
    cout << "Enter Number of Processes: ";
    cin >> n;

    // This is the "Master List". It stores the clean, original user input.
    // We keep this safe and unchanged so every algorithm gets the exact same starting data.
    vector<Process> original_processes(n);

    // Get all initial data once using setters
    for(int i = 0; i < n; i++) {
        int temp_at, temp_bt, temp_pri;
        
        original_processes[i].setId("P" + to_string(i + 1));
        cout << "\n--- Process " << original_processes[i].getId() << " ---\n";
        
        cout << "Arrival Time: ";
        cin >> temp_at;
        original_processes[i].setAt(temp_at);
        
        cout << "Burst Time: ";
        cin >> temp_bt;
        original_processes[i].setBt(temp_bt);
        
        cout << "Priority (Lower number = Higher priority): ";
        cin >> temp_pri;
        original_processes[i].setPri(temp_pri);
    }

    // Dynamic Menu Setup
    vector<string> available_algos = {"FCFS", "RR", "SJF", "Priority", "SRTF"};
    string choice;

    while (!available_algos.empty()) {
        cout << "\n=========================================\n";
        cout << "What scheduling algorithm would you try?\n";
        
        for (const string& algo : available_algos) {
            if (algo == "FCFS") cout << "For First-Come First-Served enter (FCFS)\n";
            else if (algo == "RR") cout << "For Round Robin enter (RR)\n";
            else if (algo == "SJF") cout << "For Shortest Job First enter (SJF)\n";
            else if (algo == "Priority") cout << "For Priority Scheduling Non-Preemptive enter (Priority)\n";
            else if (algo == "SRTF") cout << "For Shortest Remaining Time First enter (SRTF)\n";
        }
        
        cout << "Enter choice: ";
        cin >> choice;

        auto it = find(available_algos.begin(), available_algos.end(), choice);
        
        if (it != available_algos.end()) {
            cout << "\n>>> Running " << choice << " <<<\n";
            
            // Execute the chosen algorithm, passing a FRESH COPY of the processes
            // EXTREMELY IMPORTANT: We are passing 'original_processes' to the functions.
            // Because the functions are defined as (vector<Process> p) and NOT (vector<Process> &p),
            // C++ makes a fresh copy of the master list for each algorithm. 
            // This prevents one algorithm from accidentally marking all processes as 'completed' for the next one!
            if (choice == "FCFS") runFCFS(original_processes);
            else if (choice == "RR") {
                int tq;
                cout << "Enter Time Quantum for Round Robin: ";
                cin >> tq;
                runRR(original_processes, tq);
            }
            else if (choice == "SJF") runSJF(original_processes);
            else if (choice == "Priority") runPriority(original_processes);
            else if (choice == "SRTF") runSRTF(original_processes);

            available_algos.erase(it);

            if (!available_algos.empty()) {
                string continue_choice;
                cout << "\nDo you want to try another algorithm for the same processes? (y/n): ";
                cin >> continue_choice;
                if (continue_choice == "n" || continue_choice == "N") break;
            } else {
                cout << "\nAll algorithms have been tested!\n";
            }
        } else {
            cout << "\nInvalid choice or algorithm already executed. Please try again.\n";
        }
    }

    cout << "\nExiting Evaluator. Don't forget to compile your results for the final report!\n";
    return 0;
}

// ==========================================
// 4.  CENTRALIZED PRINT FUNCTION
// ==========================================
void printResults(const vector<Process>& p) {
    int n = p.size();
    float totalTat = 0, totalWt = 0;

    cout << "\n================ Final Results ================\n";
    cout << "Process\tAT\tBT\tPri\tCT\tTAT\tWT\n";
    cout << "-----------------------------------------------\n";
    
    for(int i = 0; i < n; i++) {
        // Calculate totals dynamically here so the algorithms don't have to!
        totalTat += p[i].getTat();
        totalWt += p[i].getWt();

        cout << p[i].getId() << "\t" 
             << p[i].getAt() << "\t" 
             << p[i].getBt() << "\t" 
             << p[i].getPri() << "\t" 
             << p[i].getCt() << "\t" 
             << p[i].getTat() << "\t" 
             << p[i].getWt() << "\n";
    }

    cout << "-----------------------------------------------\n";
    cout << "Average Turnaround Time = " << fixed << setprecision(2) << (totalTat / n) << "\n";
    cout << "Average Waiting Time    = " << fixed << setprecision(2) << (totalWt / n) << "\n";
    cout << "===============================================\n";
}

// ==========================================
// 5. TEAM MEMBER FUNCTIONS
// ==========================================

void runPriority(vector<Process> p) {
        cout << "\n[Hammam's Priority Logic Goes Here]\n";

   int n = p.size();
    
    // Sort processes based on arrival time initially
    sort(p.begin(), p.end(), compareArrival);

    int currentTime = p[0].getAt(); 
    int completed = 0;
    float totalTat = 0, totalWt = 0;

    cout << "\n--- Execution Trace ---\n";

    while (completed != n) {
        int highestPriIndex = -1;
        int highestPriority = 999999; 

        // Search for the highest priority process that is ready
        for (int i = 0; i < n; i++) {
            if (p[i].getAt() <= currentTime && !p[i].getIsCompleted()) {
                if (p[i].getPri() < highestPriority) { 
                    highestPriority = p[i].getPri();
                    highestPriIndex = i;
                }
                // Tie-breaker by arrival time
                else if (p[i].getPri() == highestPriority) {
                    if (p[i].getAt() < p[highestPriIndex].getAt()) {
                        highestPriIndex = i;
                    }
                }
            }
        }

        // If a process was found, execute it
        if (highestPriIndex != -1) {
            int l = highestPriIndex;
            cout << "Time " << currentTime << ": Process " << p[l].getId() << " starts execution.\n";
            
            currentTime += p[l].getBt(); 
            p[l].setCt(currentTime);
            p[l].setTat(p[l].getCt() - p[l].getAt());
            totalTat += p[l].getTat();
            
            p[l].setWt(p[l].getTat() - p[l].getBt());
            totalWt += p[l].getWt();
            
            p[l].setCompleted(true);
            completed++;
            
            cout << "Time " << currentTime << ": Process " << p[l].getId() << " finishes.\n";
        } else {
            // No process has arrived yet, CPU is idle
            cout << "Time " << currentTime << ": CPU is IDLE.\n";
            currentTime++; 
        }
    }

    // Print final results table using the centralized print function
    printResults(p);

}

void runFCFS(vector<Process> p) {
    cout << "\n[Assad's FCFS Logic Goes Here]\n";
}

void runRR(vector<Process> p, int time_quantum) {
    cout << "\n[Abdullah's RR Logic Goes Here]\n";
}

void runSJF(vector<Process> p) {
    cout << "\n[Ghaith's SJF Logic Goes Here]\n";
}

void runSRTF(vector<Process> p) {
    cout << "\n[Khaled's SRTF Logic Goes Here]\n";
}