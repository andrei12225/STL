#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream inFile("input.txt");

    vector<string> doctors;
    vector<pair<string, string>> problems;
    int nrProblems, nrDocs;

    inFile >> nrProblems;
    while (nrProblems--) {
        string problem, speciality;
        inFile >> problem >> speciality;

        problems.emplace_back(problem, speciality);
    }

    inFile >> nrDocs;
    while (nrDocs--) {
        string docId, doc;
        inFile >> docId >> doc;

        doctors.emplace_back(doc);
    }

    for (const auto& problem : problems) {
        int ok = 0;
        for (const auto& doctor : doctors) {
            if (doctor == problem.second) { ok = 1; break; }
        }
        if (ok) cout << problem.first << " Acceptat\n";
        else cout << problem.first << " Respins\n";
    }


    return 0;
}