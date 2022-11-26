#include "AlphaDigitCharSet.h"

#include <string>

char premierbob::AlphaDigitCharSet::Index(int nPos) {
  if (0 <= nPos && nPos < Size()) {
    if (nPos < pDigitalCharSet->Size()) {
      return pDigitalCharSet->Index(nPos);
    } else {
      return pAlphaCharSet->Index(nPos - pDigitalCharSet->Size());
    }
  } else {
    throw std::string("[AlphaDigitCharSet::Index] Index out of Range.");
  }
}

size_t premierbob::AlphaDigitCharSet::Size() const {
  return pAlphaCharSet->Size() + pDigitalCharSet->Size();
}

bool premierbob::AlphaDigitCharSet::InSet(char c) {
  return pAlphaCharSet->InSet(c) || pDigitalCharSet->InSet(c);
}
