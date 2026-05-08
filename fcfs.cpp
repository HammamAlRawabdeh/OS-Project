void runFCFS(vector<Process> p) {

    if (p.empty()){
    cout << "\nVector p is empty\n";
    return;
    }

    int n = p.size(); //number of processes

    sort(p.begin(), p.end(), compareArrival); //sorting them

    int currentTime = p[0].getAt(); 

    int completed = 0;

    cout << "\n--- Execution Trace ---\n";

    while (completed != n) {

        int j = -1; //index of the current process we'll be working on
        for (int i = 0; i < n; i++) {
            if (p[i].getAt()<=currentTime && !p[i].getIsCompleted()) { //if process is ready and isn't already done, assign it to j
                j = i;
                break;
            }
        }
        if (j != -1) { //FCFS occurs with its calculations 
            cout << "Time " << currentTime << ": Process " << p[j].getId() << " starts execution.\n";

            currentTime += p[j].getBt();

            p[j].setCt(currentTime);

            p[j].setTat(p[j].getCt() - p[j].getAt()); //turnaround time = current - arrival

            p[j].setWt(p[j].getTat() - p[j].getBt()); //waiting time = turnaround - burst

            p[j].setCompleted(true);

            completed++;

            cout << "Time " << currentTime << ": Process " << p[j].getId() << " finishes.\n";
        } else {
            cout << "Time " << currentTime << ": CPU is IDLE.\n";
            currentTime++;
        }
    }

    printResults(p);
}
