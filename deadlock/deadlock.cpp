#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

// number of processes nP and number of resources nR
int nP, nR;
// E is the existence vector. E[r] is the total number of resources
// of type r.
int *E;
// A is the availability vector. A[r] is the number of available resources
// of type r.
int *A;
// C is the allocation matrix. C[p][r] is the number of resources
// of type r allocated to process p.
int **C;
// R is the request matrix. R[p][r] is the number of resources of
// type r that might be requested by process p.
int **R;

string stripComments(const string &filename);

string printVector(int *V, int n);

string printMatrix(int **M, int rows, int cols);

void readFile(const string &filename);

void freeMemory();

void run_processes();

bool can_run(int process);

void run(int process);

void print_state();

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: scheduler filename\n");
        return 1;
    }
    int argi = 1;
    const string filename = argv[argi++];

    // Populate nP, nR, E, C, and R
    readFile(filename);

    // Debug output:
    cout << "E = " << printVector(E, nR) << endl << endl;
    cout << "A = " << printVector(A, nR) << endl << endl;
    cout << "C = " << endl << printMatrix(C, nP, nR) << endl;
    cout << "R = " << endl << printMatrix(R, nP, nR) << endl;

    // TODO: Make your additions here.
    run_processes();

    freeMemory();
}

void run_processes() {
    std::set<int> processes;
    for (int i = 0; i < nP; i++) {
        processes.insert(i);
    }

    while (!processes.empty()) {
        bool deadlock = true;
        for (auto process : processes) {
            if (can_run(process)) {
                run(process);
                deadlock = false;
                processes.erase(process);
                break;
            }
        }

        if (deadlock) {
            std::cout << "The original state is unsafe." << std::endl;
            return;
        }
    }

    std::cout << "The original state is safe." << std::endl;
}

void run(int process) {
    std::cout << "Run process " << process << ":" << std::endl;
    for (int resource = 0; resource < nR; resource++) {
        A[resource] += C[process][resource];
        C[process][resource] = 0;
        R[process][resource] = 0;
    }
    print_state();
}

void print_state() {
    cout << "A = " << printVector(A, nR) << endl;
    cout << "C = " << endl << printMatrix(C, nP, nR);
    cout << "R = " << endl << printMatrix(R, nP, nR) << std::endl;
}

bool can_run(int process) {
    for (int resource = 0; resource < nR; resource++) {
        if (A[resource] < R[process][resource]) {
            return false;
        }
    }
    return true;
}

//----------------------------------------------------------------------
// Helper functions
//----------------------------------------------------------------------

string stripComments(const string &filename) {
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

string printVector(int *V, int n) {
    stringstream out;
    for (int i = 0; i < n; ++i) {
        out << V[i] << " ";
    }
    return out.str();
}

string printMatrix(int **M, int rows, int cols) {
    stringstream out;
    for (int r = 0; r < rows; ++r) {
        out << "    " << r << ": ";
        for (int c = 0; c < cols; ++c) {
            out << M[r][c] << " ";
        }
        out << endl;
    }
    return out.str();
}

void readFile(const string &filename) {
    stringstream in(stripComments(filename));
    in >> nP >> nR;

    E = new int[nR];
    A = new int[nR];
    for (int r = 0; r < nR; ++r) {
        in >> E[r];
        A[r] = E[r];
    }

    C = new int *[nP];
    for (int p = 0; p < nP; ++p) {
        C[p] = new int[nR];
    }
    for (int p = 0; p < nP; ++p) {
        for (int r = 0; r < nR; ++r) {
            in >> C[p][r];
            A[r] -= C[p][r];
        }
    }

    R = new int *[nP];
    for (int p = 0; p < nP; ++p) {
        R[p] = new int[nR];
    }
    for (int p = 0; p < nP; ++p) {
        for (int r = 0; r < nR; ++r) {
            in >> R[p][r];
        }
    }
}

void freeMemory() {
    delete[] E;
    delete[] A;
    for (int p = 0; p < nP; ++p) {
        delete[] C[p];
    }
    delete[] C;
    for (int p = 0; p < nP; ++p) {
        delete[] R[p];
    }
    delete[] R;
}
