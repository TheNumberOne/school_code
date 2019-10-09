#pragma once

#include <string>

class Song {
 public:
  Song(const std::string& name, const std::string& band) {
    _name = name;
    _band = band;
  }

  const std::string& name() const { return _name; }
  const std::string& band() const { return _band; }

  bool operator==(const Song& rhs) const {
    return name() == rhs.name() && band() == rhs.band();
  }

  bool operator!=(const Song& rhs) const {
    return !(*this == rhs);
  }

  friend std::ostream& operator<<(std::ostream& out, const Song& p) {
    out << p.name() << " - " << p.band();
    return out;
  }

 public:
  std::string _name;
  std::string _band;
};
