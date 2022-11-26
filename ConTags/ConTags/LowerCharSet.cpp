#include "LowerCharSet.h"

#include <string>

char premierbob::LowerCharSet::Index(int nPos) {
  if (0 <= nPos && nPos < Size()) {
    return nPos + 'a';
  } else {
    throw std::string("[UpperCharSet::Index] Index out of Range.");
  }
}

size_t premierbob::LowerCharSet::Size() const { return 26; }

bool premierbob::LowerCharSet::InSet(char c) { return 'a' <= c && c <= 'z'; }
