/*
 * Load balancing problem
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

string stripComments(const string& filename) {
  ifstream in(filename);
  string buf;
  while (!in.eof()) {
    string line;
    getline(in, line);
    if (line[0] != '#') {
      buf += line + " ";
    }
  }
  in.close();
  return buf;
}

void readFile(const string& filename) {
  stringstream in(stripComments(filename));
  
  int procId = 0;
  while (!in.eof()) {
    char cpu;
    int creation, time;
    in >> cpu >> creation >> time;
    if (!in.eof()) {
      printf("CPU %c creates process %d at time %d requiring %d time units.\n",
             cpu, procId, creation, time);
      int cpuidx = (int)(cpu - 'A');
      ++procId;
    }
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: balancing filename\n");
    return 1;
  }
  int argi = 1;
  const string filename = argv[argi++];

  readFile(filename);
}

