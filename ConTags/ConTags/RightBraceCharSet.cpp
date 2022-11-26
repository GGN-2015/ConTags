#include "RightBraceCharSet.h"

#include <string>

namespace premierbob {

char RightBraceCharSet::Index(int nPos) {
  if (0 <= nPos && nPos < Size()) {
    switch (nPos) {
      case 0:
        return ')';
      case 1:
        return '>';
      case 2:
        return ']';
      case 3:
        return '}';
    }
    return '\0';
  } else {
    throw std::string("[RightBraceCharSet::Index] Index out of Range.");
  }
}

size_t RightBraceCharSet::Size() const { return 4; }

bool RightBraceCharSet::InSet(char c) {
  return c == ')' || c == '>' || c == '}' || c == ']';
}

}  // namespace premierbob
