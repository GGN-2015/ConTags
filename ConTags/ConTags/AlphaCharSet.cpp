#include "AlphaCharSet.h"

#include <string>

char premierbob::AlphaCharSet::Index(int nPos) {
  if (0 <= nPos && nPos < Size()) {
    if (nPos < pUpperCharSet->Size()) {
      return pUpperCharSet->Index(nPos);
    } else {
      return pLowerCharSet->Index(nPos - pUpperCharSet->Size());
    }
  } else {
    throw std::string("[AlphaCharSet::Index] Index out of Range.");
  }
}

size_t premierbob::AlphaCharSet::Size() const {
  return pLowerCharSet->Size() + pUpperCharSet->Size();
}

bool premierbob::AlphaCharSet::InSet(char c) {
  return pLowerCharSet->InSet(c) || pUpperCharSet->InSet(c);
}
