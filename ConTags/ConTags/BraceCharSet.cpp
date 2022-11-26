#include "BraceCharSet.h"

#include <string>

char premierbob::BraceCharSet::Index(int nPos) {
  if (0 <= nPos && nPos < Size()) {
    if (nPos < 4) {
      return mLeftBraceCharSet->Index(nPos);
    } else {
      return mRightBraceCharSet->Index(nPos - 4);
    }
  } else {
    throw std::string("[BraceCharSet::Index] Index out of Range.");
  }
}

size_t premierbob::BraceCharSet::Size() const {
  return mLeftBraceCharSet->Size() + mRightBraceCharSet->Size();
}

bool premierbob::BraceCharSet::InSet(char c) {
  return mLeftBraceCharSet->InSet(c) || mRightBraceCharSet->InSet(c);
}
