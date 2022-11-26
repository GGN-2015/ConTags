#include "DigitalCharSet.h"

#include <string>

namespace premierbob {

char DigitalCharSet::Index(int nPos) {
  if (0 <= nPos && nPos < Size()) {
    return '0' + nPos;
  } else {
    throw std::string("[DigitalCharSet::Index] Index out of Range.");
  }
}

size_t DigitalCharSet::Size() const { return 10; }

bool DigitalCharSet::InSet(char c) { return '0' <= c && c <= '9'; }

}  // namespace premierbob
