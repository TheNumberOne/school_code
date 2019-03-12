//------------------------------------------------------------
// Do not modify this file.
//------------------------------------------------------------

#pragma once

#include <iostream>
#include <string>

class Student {
 public:
  Student() {
    _name = "";
    _id = 0;
    _age = 0;
  }

  Student(const std::string& name, const int id, const int age) {
    _name = name;
    _id = id;
    _age = age;
  }

  const std::string& name() const { return _name; }
  const int id() const { return _id; }
  const int age() const { return _age; }

  bool operator==(const Student& rhs) const {
    return name() == rhs.name() && id() == rhs.id() && age() == rhs.age();
  }

  bool operator!=(const Student& rhs) const {
    return !(*this == rhs);
  }

  friend std::ostream& operator<<(std::ostream& out, const Student& p) {
    out << p.name() << " " << p.id() << " " << p.age();
    return out;
  }

 private:
  std::string _name;
  int _id;
  int _age;
};
