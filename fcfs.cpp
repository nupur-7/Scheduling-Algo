//first git commit
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cout<<"Enter no of processes to execute:";
    cin>>n;
    vector<int> pid(n), arrivalTime(n), burstTime(n), completionTime(n), startTime(n), turnAroundTime(n), waitingTime(n), responseTime(n);
    
    for(int i=0;i<n;i++)
    {
        cout<<"enter pid of process "<<i+1<<":";
        cin>>pid[i];

        cout<<"enter arrival time of process "<<i+1<<":";
        cin>>arrivalTime[i];

        cout<<"enter burst time of process "<<i +1 <<":";
        cin>>burstTime[i];
    }

     // Sort processes by arrival time, and by pid if arrival times are the same
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if (arrivalTime[j] > arrivalTime[j+1] || 
                (arrivalTime[j] == arrivalTime[j+1] && pid[j] > pid[j+1])) {
                swap(arrivalTime[j], arrivalTime[j+1]);
                swap(burstTime[j], burstTime[j+1]);
                swap(pid[j], pid[j+1]);
            }
        }
    }

    // Calculate start time, completion time, turnaround time, waiting time, and response time
    startTime[0] = arrivalTime[0];
    completionTime[0] = startTime[0] + burstTime[0];
    turnAroundTime[0] = completionTime[0] - arrivalTime[0];
    waitingTime[0] = turnAroundTime[0] - burstTime[0];
    responseTime[0] = startTime[0] - arrivalTime[0];

    for(int i = 1; i < n; i++) {
        startTime[i] = max(completionTime[i-1], arrivalTime[i]);
        completionTime[i] = startTime[i] + burstTime[i];
        turnAroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnAroundTime[i] - burstTime[i];
        responseTime[i] = startTime[i] - arrivalTime[i];
    }

    cout << "\nPID\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n";
    for(int i = 0; i < n; i++) {
        cout << pid[i] << "\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << startTime[i] << "\t\t" 
            << completionTime[i] << "\t\t" << turnAroundTime[i] << "\t\t" << waitingTime[i] << "\t\t" 
            << responseTime[i] << "\n";
    }

    // cout << "\nOrder of execution of processes: ";
    // for(int i = 0; i < n; i++) {
    //     cout << "P" << pid[i];
    //     if (i < n - 1) cout << " -> ";
    // }
    // cout << "\n";

    double avgTAT = accumulate(turnAroundTime.begin(), turnAroundTime.end(), 0.0) / n;
    double avgWT = accumulate(waitingTime.begin(), waitingTime.end(), 0.0) / n;
    double avgRT = accumulate(responseTime.begin(), responseTime.end(), 0.0) / n;
    
    cout << "\nAverage Turnaround Time: " << avgTAT << "\n";
    cout << "Average Waiting Time: " << avgWT << "\n";
    cout << "Average Response Time: " << avgRT << "\n";

    return 0;
}