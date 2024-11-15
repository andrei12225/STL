#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Doctor {
public:
    string id, speciality;
    bool busy = false;
    Doctor(const string& id, const string& speciality) {
        this->id = id;
        this->speciality = speciality;
    }
};

class Problem {
public:
    string name, specialityNeeded;
    Problem(const string& name, const string& specialityNeeded) {
        this->name = name;
        this->specialityNeeded = specialityNeeded;
    }
};

int main()
{
    ifstream inFile("input.txt");

    int no_problems, no_doctors;
    string problemName, specialityNeeded, doctorId;
    vector<Problem> problems;
    vector<Doctor> doctors;

    inFile >> no_problems;

    for (int i = 0; i < no_problems; ++i) {
        inFile >> problemName >> specialityNeeded;

        Problem problem(problemName, specialityNeeded);
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
            return problem.specialityNeeded == doctor.speciality && !doctor.busy;
        };
        auto doctor = find_if(begin(doctors), end(doctors), lambda);
        if (doctor != end(doctors)) {
            doctor->busy = true;
            cout << doctor->id << " " << problem.name << "\n";
        }
    }

    return 0;
}