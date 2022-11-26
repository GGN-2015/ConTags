#pragma once
#include "StringData.h"

namespace premierbob {

class StringFind {
 public:
  StringFind(){};
  virtual ~StringFind(){};

  virtual int Find(std::shared_ptr<StringData> pStringData, std::string nString,
                   size_t nFrom);

  StringFind(const StringFind&) = delete;
  StringFind& operator=(const StringFind&) = delete;
};

}  // namespace premierbob
