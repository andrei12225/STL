#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define WORKING_HOURS 9;

using namespace std;

class Problem {
public:
    string name, specialityNeeded;
    int timeNeeded;
    Problem(const string& name, const string& specialityNeeded, const int& timeNeeded) {
        this->name = name;
        this->specialityNeeded = specialityNeeded;
        this->timeNeeded = timeNeeded;
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
        this->problemsSolved = problemsSolved;
    }
};

int main()
{
    ifstream inFile("input4_bonus.txt");

    int no_problems, no_doctors, timeNeeded;
    string problemName, specialityNeeded, doctorId;
    vector<Problem> problems;
    vector<Doctor> doctors;

    inFile >> no_problems;

    for (int i = 0; i < no_problems; ++i) {
        inFile >> problemName >> specialityNeeded >> timeNeeded;

        Problem problem(problemName, specialityNeeded, timeNeeded);
        problems.push_back(problem);
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; ++i) {
        inFile >> doctorId >> specialityNeeded;

        Doctor doctor(doctorId, specialityNeeded);
        doctors.push_back(doctor);
    }

    for (auto & problem : problems) {
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
        cout << doctor.id << " " << doctor.problemsSolved.size() << " ";
        for (const auto & problem : doctor.problemsSolved) {
            cout << problem.name << " ";
        }
        cout << "\n";
    }

    return 0;
}