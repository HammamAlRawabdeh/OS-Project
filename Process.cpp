#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

// process class alone
class sjf;
class Process {
protected:
    friend class sjf;
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
