#pragma once
// third party
#include <core/sstring.hh>
#include <re2/re2.h>

namespace smf {
static const re2::RE2 kFileNameRE("[a-zA-Z\\d]+_\\d+\\.wal");

struct wal_name_parser {
  wal_name_parser(sstring _prefix = "smf") : prefix(_prefix) {
    for(char c : prefix) {
      if(c == '\\' || c == '(' || c == ')' || c == '[' || c == ']')
        throw std::runtime_error(
          "wal_name_parser cannot include a prefix with special chars");
    }
  }
  const sstring prefix;

  bool operator()(const sstring &filename) {
    return re2::RE2::FullMatch(filename.c_str(), kFileNameRE);
  }
};


} // namespace smf
