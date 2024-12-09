#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

#define WORKING_HOURS 9;

using namespace std;

class Problem {
public:
    string name, specialityNeeded;
    int timeNeeded, priority;
    Problem(const string& name, const string& specialityNeeded, const int& timeNeeded, const int& priority) {
        this->name = name;
        this->specialityNeeded = specialityNeeded;
        this->timeNeeded = timeNeeded;
        this->priority = priority;
    }
};

struct ProblemComparator {
    bool operator()(const Problem& p1, const Problem& p2) const {
        return p1.priority < p2.priority;
    }
};

class Doctor {
public:
    string id, speciality;
    int hoursWorked = 0;
    vector<Problem> problemsSolved;
    Doctor(const string& id, const string& speciality) {
        this->id = id;
        this->speciality = speciality;
    }
};

int main()
{
    ifstream inFile("input4_bonus.txt");

    int no_problems, no_doctors, timeNeeded, priority;
    string problemName, specialityNeeded, doctorId;
    priority_queue<Problem, vector<Problem>, ProblemComparator> problems;
    vector<Doctor> doctors;

    inFile >> no_problems;

    for (int i = 0; i < no_problems; ++i) {
        inFile >> problemName >> specialityNeeded >> timeNeeded >> priority;

        Problem problem(problemName, specialityNeeded, timeNeeded, priority);
        problems.push(problem);
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; ++i) {
        inFile >> doctorId >> specialityNeeded;

        Doctor doctor(doctorId, specialityNeeded);
        doctors.push_back(doctor);
    }

    while (!problems.empty()) {
        auto problem = problems.top();
        problems.pop();
        const auto lambda = [problem](const Doctor& doctor) {
            return problem.specialityNeeded == doctor.speciality && doctor.hoursWorked + problem.timeNeeded < WORKING_HOURS;
        };
        auto doctor = find_if(begin(doctors), end(doctors), lambda);
        if (doctor != end(doctors)) {
            doctor->hoursWorked += problem.timeNeeded;
            doctor->problemsSolved.push_back(problem);
        }
    }

    for (const auto & doctor : doctors) {
        if (doctor.problemsSolved.empty()) continue;
        cout << doctor.id << " " << doctor.problemsSolved.size() << " ";
        for (const auto & problem : doctor.problemsSolved) {
            cout << problem.name << " ";
        }
        cout << "\n";
    }

    return 0;
}