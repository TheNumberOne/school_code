#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>
#include <iterator>

#include "./Person.h"
#include "./Student.h"

#define TEST(test) { \
  testNum++; \
  if (!(test)) { \
    cerr << "Test " << testNum << " failed" << endl; \
    numFails++; \
  } \
}

template<typename T>
void printArray(const T *A, int n) {
    using namespace std;
    for (int i = 0; i < n; ++i) {
        cout << A[i] << endl;
    }
    cout << endl;
}

template<typename T>
bool arrayEquals(const T *A, const T *B, int n) {
    for (int i = 0; i < n; ++i) {
        if (A[i] != B[i]) return false;
    }
    return true;
}

std::string removeWhitespace(const std::string &s) {
    using namespace std;
    regex e("\\s");
    string s2;
    regex_replace(back_inserter(s2), s.begin(), s.end(), e, "");
    return s2;
}

bool stringEquals(const std::string &a, const std::string &b) {
    return removeWhitespace(a) == removeWhitespace(b);
}

template<typename T>
std::string dotEdge(const T &a, const T &b) {
    using namespace std;
    stringstream ss;
    ss << "\"" << a << "\" -> \"" << b << "\"\n";
    return ss.str();
}

//------------------------------------------------------------
// Person functions
//------------------------------------------------------------
bool operator<(const Person &lhs, const Person &rhs) {
    return lhs.name() < rhs.name();
}

bool operator<=(const Person &lhs, const Person &rhs) {
    return lhs.name() <= rhs.name();
}

bool operator>(const Person &lhs, const Person &rhs) {
    return lhs.name() > rhs.name();
}

//------------------------------------------------------------
// Student functions
//------------------------------------------------------------
bool operator<(const Student &lhs, const Student &rhs) {
    return lhs.name() < rhs.name();
}

bool operator<=(const Student &lhs, const Student &rhs) {
    return lhs.name() <= rhs.name();
}

bool operator>(const Student &lhs, const Student &rhs) {
    return lhs.name() > rhs.name();
}

void swap(int &lhs, int &rhs) {
    int temp = lhs;
    lhs = rhs;
    rhs = temp;
}

void swap(Person &lhs, Person &rhs) {
    Person temp = lhs;
    lhs = rhs;
    rhs = temp;
}

void swap(Student &lhs, Student &rhs) {
    Student temp = lhs;
    lhs = rhs;
    rhs = temp;
}

