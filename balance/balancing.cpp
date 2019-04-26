/*
 * Load balancing problem
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <map>

using namespace std;

struct job
{
    job(int id, char cpu, int time, int length) : id(id), cpu(cpu), time(time), length(length) { }
    
    int id = 0;
    char cpu = 0;
    int time = 0;
    int length = 0;
};

void print_jobs(vector<job> &vector);

void process_jobs(vector<job> &vector);

string stripComments(const string &filename)
{
    ifstream in(filename);
    string buf;
    while (in) {
        string line;
        getline(in, line);
        if (line[0] != '#') {
            buf += line + " ";
        }
    }
    in.close();
    return buf;
}

std::vector<job> readFile(const string &filename)
{
    stringstream in(stripComments(filename));
    
    std::vector<job> jobs;
    int procId = 0;
    while (in) {
        char cpu;
        int creation, time;
        in >> cpu >> creation >> time;
        if (in) {
            printf(
                "CPU %c creates process %d at time %d requiring %d time units.\n",
                cpu, procId, creation, time
            );
            jobs.emplace_back(procId, cpu, creation, time);
            ++procId;
        }
    }
    return jobs;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: balancing filename\n");
        return 1;
    }
    const string filename = argv[1];
    
    auto jobs = readFile(filename);
    printf("\n");
    print_jobs(jobs);
    printf("\n");
    process_jobs(jobs);
    printf("\n");
    print_jobs(jobs);
}


void process_jobs(std::vector<job> &jobs)
{
    std::set<char> cpus;
    std::map<char, std::queue<job *>> jobs_by_cpu;
    std::map<char, job *> current_jobs;
    int jobs_completed = 0;
    
    for (job &job : jobs) {
        jobs_by_cpu[job.cpu].push(&job);
        cpus.insert(job.cpu);
    }
    
    printf("Time Proc State Action\n");
    int time = 0;
    while (true) {
        std::set<char> over;
        std::set<char> under;
        for (char cpu : cpus) {
            std::queue<job *> &queue = jobs_by_cpu[cpu];
            
            if (current_jobs[cpu] != nullptr && time >= current_jobs[cpu]->time + current_jobs[cpu]->length) {
                current_jobs[cpu] = nullptr;
                jobs_completed++;
            }
            
            if (!queue.empty()) {
                job * next_job = queue.front();
                // push forward the start time
                if (current_jobs[cpu] == nullptr && next_job->time <= time) {
                    next_job->time = time;
                    next_job->cpu = cpu;
                    queue.pop();
                    current_jobs[cpu] = next_job;
                    under.erase(cpu);
                }
            }
        }
        if (jobs_completed >= jobs.size()) {
            return;
        }
        for (char cpu : cpus) {
            auto &q = jobs_by_cpu[cpu];
            if (current_jobs[cpu] == nullptr) {
                printf("%- 4d %c    under\n", time, cpu);
            } else if (!q.empty() && q.front()->time <= time) {
                job * next_job = q.front();
                
                bool found_transfer = false;
                for (char candidate: cpus) {
                    if (current_jobs[candidate] == nullptr) {
                        q.pop();
                        next_job->cpu = candidate;
                        next_job->time = time;
                        current_jobs[candidate] = next_job;
                        printf("%- 4d %c    over  process %d -> CPU %c\n", time, cpu, next_job->id, candidate);
                        found_transfer = true;
                        break;
                    }
                }
                if (!found_transfer) {
                    printf("%- 4d %c    over\n", time, cpu);
                }
            }
        }
        time++;
    }
}

void print_jobs(std::vector<job> &jobs)
{
    std::sort(
        jobs.begin(), jobs.end(), [](const job &lhs, const job &rhs)
        {
            return lhs.cpu == rhs.cpu ? lhs.time < rhs.time : lhs.cpu < rhs.cpu;
        }
    );
    int max_time = 20;
    
    printf("   ");
    for (int i = 0; i < max_time; i++) {
        printf("%- 3d", i);
    }
    printf("\n");
    
    for (const job &job : jobs) {
        printf("%c: ", job.cpu);
        for (int i = 0; i < job.time; i++) {
            printf("   ");
        }
        for (int i = 0; i < job.length; i++) {
            printf("%- 3d", job.id);
        }
        printf("\n");
    }
}