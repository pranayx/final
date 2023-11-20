#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class job{
    public:
        int id;
        string name;
        int arrival_time;
        int burst_time;
        int completion_time;
        int tat_time;
        int waiting_time;
        int priority;

    job(){
        id=0;
        name="";
         arrival_time=0;
         burst_time=0;
         completion_time=0;
         tat_time=0;
         waiting_time=0;
         priority=0;
    }
    job(int id,string name,int arrival_time,int burst_time){
        this->id=id;
        this->name = name;
        this->arrival_time = arrival_time;
        this->burst_time = burst_time;
        this->completion_time = 0;
        this->tat_time = 0;
        this->waiting_time = 0;
        this->priority=0;
    }
    friend class Scheduling;
};
class Scheduling{
    int n;
    job *processes;
    vector<job>readyQueue;
    public:
        Scheduling(int n){
            this->n=n;
            processes=new job[n];
        }
        void input(){
            int at,bt;
            for(int i=0;i<n;i++){
                cout<<"Enter arrival and burst time:";
                cin>>at>>bt;
                processes[i].id=i+1;
                processes[i].arrival_time=at;
                processes[i].burst_time=bt;
                processes[i].name="P"+to_string(i+1);
            }
        }
        void display(){
            cout<<"id\tTa\tTs\tTc\tTtat\tTw"<<endl;
               // sort(processes,processes+n,[](const job &lhs,const job &rhs){
               // return lhs.id<rhs.id;
           // });
            for (int i = 0; i < n; i++) {
                cout<<processes[i].id<<"\t"<<processes[i].arrival_time<<"\t"<<processes[i].burst_time<<"\t"<<processes[i].completion_time<<"\t"<<processes[i].tat_time<<"\t"<<processes[i].waiting_time<<endl;
            }
        }
        void fcfs(){
            int totaltime=0;
            int currenttime=0;
            int processCompleted=0;
            sort(processes,processes+n,[](const job &lhs,const job &rhs){
                return lhs.arrival_time<rhs.arrival_time;
            });
            for(int i=0;i<n;i++){
                totaltime=totaltime+processes[i].burst_time;
            }
            while(currenttime<=totaltime){
                while(processCompleted<n&&processes[processCompleted].arrival_time<=currenttime){
                    readyQueue.push_back(processes[processCompleted]);
                    processCompleted++;
                }
                if(readyQueue.size()>0){
                    readyQueue[0].burst_time--;
                    if(readyQueue[0].burst_time==0){
                        for(int i=0;i<n;i++){
                            if(processes[i].id==readyQueue[0].id){
                                processes[i].completion_time=currenttime+1;
                                processes[i].tat_time=processes[i].completion_time-processes[i].arrival_time;
                                processes[i].waiting_time=processes[i].tat_time-processes[i].burst_time;
                        }
                        }
                        readyQueue.erase(readyQueue.begin());
                     }
                 }
            currenttime++;
        }
        this->display();
        }

//SJF PREEEMTIVE
        void sjf(){
            int totaltime=0;
            int currenttime=0;
            int processCompleted=0;

            for(int i=0;i<n;i++){
                totaltime=totaltime+processes[i].burst_time;
            }
            sort(processes,processes+n, [] (const job &lhs, const job & rhs) {
				    return lhs.arrival_time < rhs.arrival_time;
			    });
            
            while(currenttime<=totaltime){
                while(processCompleted<n&&processes[processCompleted].arrival_time<=currenttime){
                    readyQueue.push_back(processes[processCompleted]);
                    processCompleted++;
                }
                sort(readyQueue.begin(),readyQueue.end(),[](const job &lhs,const job &rhs){
                    return lhs.burst_time<rhs.burst_time;
                });

                if(readyQueue.size()>0){
                    readyQueue[0].burst_time--;
                    if(readyQueue[0].burst_time==0){
                        for(int i=0;i<n;i++){
                            if(processes[i].id==readyQueue[0].id){
                                processes[i].completion_time=currenttime+1;
                                processes[i].tat_time = (processes[i].completion_time - processes[i].arrival_time) ;
							    processes[i].waiting_time = (processes[i].tat_time - processes[i].burst_time) ;
                            }
                        }
                        readyQueue.erase(readyQueue.begin());
                    }
                        
                }
                currenttime++;
            }
            
        this->display();
        }

        void priority() {
            int totalTime = 0;
            int currentTime = 0;
            int processCompleted = 0;

            cout<<"Enter priorities"<<endl;
            for (int i = 0; i < n; i++) {
                cin>>processes[i].priority;
               
            }
            sort(processes,processes+n, [] (const job &lhs, const job & rhs) {
				    return lhs.arrival_time < rhs.arrival_time;
			});
            
            for (int i = 0; i < n; i++) {
                totalTime += processes[i].burst_time;
            }
            
            while (currentTime <= totalTime) {
                while (processCompleted < n&&processes[processCompleted].arrival_time<=currentTime) {
                    readyQueue.push_back(processes[processCompleted]);
                    processCompleted++;
                }
                sort(readyQueue.begin(), readyQueue.end(), [](const job &lhs, const job &rhs) {
                     return lhs.priority < rhs.priority;
                });
                int addburst;
                if (readyQueue.size() > 0) {
                    addburst=readyQueue[0].burst_time;
                    readyQueue[0].burst_time=readyQueue[0].burst_time-addburst;
                    if (readyQueue[0].burst_time == 0) {
                        for (int i = 0; i < n; i++) {
                            if (readyQueue[0].id == processes[i].id) {
                                
                                processes[i].completion_time = currentTime + addburst;
                                processes[i].tat_time = processes[i].completion_time - processes[i].arrival_time ;
                                processes[i].waiting_time = processes[i].tat_time - processes[i].burst_time;
                            }
                        }
                        readyQueue.erase(readyQueue.begin());
                    }
                }
                currentTime=currentTime+addburst;
            }

            this->display();
        }
	

    void roundRobin() {
        int totalTime = 0;
        int currentTime = 0;
        int processCompleted = 0;
        int interval = 0;
        job addedJob;
        addedJob.burst_time = 0;

        cout << "Enter time interval: ";
        cin >> interval;

        for (int i = 0; i < n; i++) {
            totalTime += processes[i].burst_time;
        }

        // Sort the processes based on arrival time
        sort(processes, processes + n, [](const job &lhs, const job &rhs) {
            return lhs.arrival_time < rhs.arrival_time;
        });

        // Simulation loop
        while (currentTime <= totalTime) {
            // Add arriving processes to the ready queue
            while (processCompleted < n && processes[processCompleted].arrival_time <= currentTime) {
                readyQueue.push_back(processes[processCompleted]);
                processCompleted++;
            }

            // If there is an unfinished job from the previous round, add it to the ready queue
            if (addedJob.burst_time > 0) {
                readyQueue.push_back(addedJob);
            }
            int addedBurst;
            // Process jobs in the ready queue
            if (readyQueue.size() > 0) {
                addedJob = readyQueue[0];
                readyQueue.erase(readyQueue.begin());
                addedBurst = min(interval, addedJob.burst_time);

                // Execute the job for the specified time quantum
                addedJob.burst_time -= addedBurst;

                // Update completion, turnaround, and waiting times if the job is completed
                if (addedJob.burst_time == 0) {
                    for (int i = 0; i < n; i++) {
                        if (addedJob.id == processes[i].id) {
                            processes[i].completion_time = currentTime + addedBurst;
                            processes[i].tat_time = processes[i].completion_time - processes[i].arrival_time;
                            processes[i].waiting_time = processes[i].tat_time - processes[i].burst_time;
                        }
                    }
                }
            }
            // Move the simulation time to the next interval
            currentTime += addedBurst;
        }

        // Display the final results
        this->display();
    }

            

};
int main(){
    int x;
    cin>>x;
    Scheduling s(x);
    s.input();
    s.priority();
}