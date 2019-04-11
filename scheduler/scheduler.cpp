#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: scheduler i filename\n");
    printf("  i - starting location of cylinder head\n");
    return 1;
  }
  int argi = 1;
  const int startPos = atoi(argv[argi++]);
  const string filename = argv[argi++];

  // Read cylinder requests into cylinders array
  vector<int> cylinders;
  ifstream file(filename);
  int inCylinder;
  file >> inCylinder;
  while (!file.eof()) {
    cylinders.push_back(inCylinder);
    file >> inCylinder;
  }
  file.close();

  // This is where you'll implement FCFS, FFS and elevator.
  cout << "Cylinders to visit: " << startPos << " ";
  for (int val : cylinders) {
    cout << val << " ";
  }
  cout << endl;
}
