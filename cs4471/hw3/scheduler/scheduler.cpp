#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef vector<int> (*ordering_algorithm)(int start, const vector<int> &input);

void print_alg(const std::string &name, ordering_algorithm alg, int start, const vector<int> &requests);
void validate_ordering(int start, vector<int> requests, vector<int> ordering);
int calc_distance(const std::vector<int> &ordering);

vector<int> fcfs_ordering(int start, const vector<int> &input);
vector<int> ssf_ordering(int start, const vector<int> &input);
vector<int> elevator_ordering(int start, const vector<int> &input);

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
    while (file >> inCylinder) {
        cylinders.push_back(inCylinder);
    }
    file.close();

    // This is where you'll implement FCFS, SSF and elevator.
    std::vector<std::pair<std::string, ordering_algorithm>> algs{
            {"FCFS", &fcfs_ordering},
            {"SSF", &ssf_ordering},
            {"Elevator", &elevator_ordering},
    };

    for (const auto &name_alg_pair : algs) {
        print_alg(name_alg_pair.first, name_alg_pair.second, startPos, cylinders);
        std::cout << std::endl;
    }
}

void print_alg(const std::string &name, ordering_algorithm alg, int start, const vector<int> &requests) {
    std::cout << name << " ordering:";
    auto ordering = alg(start, requests);
    validate_ordering(start, requests, ordering);
    for (int command : ordering) {
        std::cout << " " << command;
    }
    std::cout << std::endl;
    std::cout << name << " distance: " << calc_distance(ordering) << std::endl;
}

void validate_ordering(int start, vector<int> requests, vector<int> ordering) {
    requests.push_back(start);
    if (requests.size() != ordering.size()) {
        throw std::runtime_error("Invalid ordering");
    }
    std::sort(requests.begin(), requests.end());
    std::sort(ordering.begin(), ordering.end());
    if (requests != ordering) {
        throw std::runtime_error("Invalid ordering");
    }
}

int calc_distance(const std::vector<int> &ordering) {
    int distance = 0;
    for (int i = 0; i < ordering.size() - 1; i++) {
        distance += std::abs(ordering[i] - ordering[i + 1]);
    }
    return distance;
}

vector<int> fcfs_ordering(int start, const vector<int> &input) {
    vector<int> result{start};
    std::copy(input.begin(), input.end(), std::back_inserter(result));
    return result;
}


vector<int> ssf_ordering(int start, const vector<int> &input) {
    vector<int> result{start};
    int current_position = start;
    std::multiset<int> requests{input.begin(), input.end()};
    auto closest_ptr = requests.lower_bound(current_position);

    while (!requests.empty()) {
        if (closest_ptr != requests.begin()) {
            auto left_ptr = closest_ptr;
            --left_ptr;

            if (closest_ptr == requests.end() ||
                std::abs(current_position - *left_ptr) <= std::abs(current_position - *closest_ptr)) {
                closest_ptr = left_ptr;
            }
        }
        result.push_back(*closest_ptr);
        current_position = *closest_ptr;
        closest_ptr = requests.erase(closest_ptr);
    }

    return result;
}

template <typename Iter>
std::reverse_iterator<Iter> reverse(Iter i) {
    return std::reverse_iterator<Iter>(i);
}

vector<int> elevator_ordering(int start, const vector<int> &input) {
    vector<int> result{start};
    vector<int> requests = input;
    auto inserter = std::back_inserter(result);
    std::sort(requests.begin(), requests.end());

    auto right = std::lower_bound(requests.begin(), requests.end(), start);
    if (right == requests.end()) {
        std::copy(requests.rbegin(), requests.rend(), inserter);
        return result;
    } else if (right == requests.begin()) {
        std::copy(requests.begin(), requests.end(), inserter);
        return result;
    }

    auto left = right;
    left--;
    if (std::abs(start - *left) <= std::abs(start - *right)) {
        std::copy(reverse(right), requests.rend(), inserter);
        std::copy(right, requests.end(), inserter);
    } else {
        std::copy(right, requests.end(), inserter);
        std::copy(reverse(right), requests.rend(), inserter);
    }

    return result;
}