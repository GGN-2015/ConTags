#include "UpperCharSet.h"

#include <string>

namespace premierbob {

char UpperCharSet::Index(int nPos) {
  if (0 <= nPos && nPos < Size()) {
    return nPos + 'A';
  } else {
    throw std::string("[UpperCharSet::Index] Index out of Range.");
  }
}

size_t UpperCharSet::Size() const { return 26; }

bool UpperCharSet::InSet(char c) { return 'A' <= c && c <= 'Z'; }

}  // namespace premierbob
