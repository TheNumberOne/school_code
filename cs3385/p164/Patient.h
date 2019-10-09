//------------------------------------------------------------
// Do not modify this file.
//------------------------------------------------------------

#pragma once

#include <iostream>

class Patient {
 public:
  Patient() {
    _name = "";
    _priority = 0;
  }

  Patient(const std::string& name, const int priority) {
    _name = name;
    _priority = priority;
  }

  const std::string& name() const { return _name; }
  const int priority() const { return _priority; }

  bool operator==(const Patient& rhs) const {
    return name() == rhs.name() && priority() == rhs.priority();
  }

  bool operator!=(const Patient& rhs) const {
    return !(*this == rhs);
  }

  friend std::ostream& operator<<(std::ostream& out, const Patient& p) {
    out << p.priority() << " " << p.name();
    return out;
  }

 private:
  std::string _name;
  int _priority;
};
