#pragma once

#include <iostream>
#include <string>

#include "./Person.h"
#include "./Song.h"

#define TEST(test) { \
  testNum++; \
  if (!(test)) { \
    cerr << "Test " << testNum << " failed" << endl; \
    numFails++; \
  } \
}

template <typename T>
void printArray(const T* A, int n) {
  using namespace std;
  for (int i = 0; i < n; ++i) {
    cout << A[i] << endl;
  }
  cout << endl;
}

template <typename T>
bool arrayEquals(const T* A, const T* B, int n) {
  for (int i = 0; i < n; ++i) {
    if (A[i] != B[i]) return false;
  }
  return true;
}

//------------------------------------------------------------
// Person and Song functions
//------------------------------------------------------------
bool operator<(const Person& lhs, const Person& rhs) {
  return lhs.name() < rhs.name();
}

bool operator<=(const Person& lhs, const Person& rhs) {
  return lhs.name() <= rhs.name();
}

bool operator>(const Person& lhs, const Person& rhs) {
  return lhs.name() > rhs.name();
}

bool operator<(const Song& lhs, const Song& rhs) {
  return lhs._name < rhs._name;
}

bool operator<=(const Song& lhs, const Song& rhs) {
  return lhs._name <= rhs._name;
}

bool operator>(const Song& lhs, const Song& rhs) {
  return lhs._name > rhs._name;
}

void swap(int& lhs, int& rhs) {
  int temp = lhs;
  lhs = rhs;
  rhs = temp;
}

void swap(Person& lhs, Person& rhs) {
  Person temp = lhs;
  lhs = rhs;
  rhs = temp;
}

void swap(Song& lhs, Song& rhs) {
  Song temp = lhs;
  lhs = rhs;
  rhs = temp;
}

