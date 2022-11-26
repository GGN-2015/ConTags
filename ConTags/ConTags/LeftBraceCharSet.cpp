#include "LeftBraceCharSet.h"

#include <string>

namespace premierbob {

char LeftBraceCharSet::Index(int nPos) {
  if (0 <= nPos && nPos < Size()) {
    switch (nPos) {
      case 0:
        return '(';
      case 1:
        return '<';
      case 2:
        return '[';
      case 3:
        return '{';
    }
    return '\0';
  } else {
    throw std::string("[LeftBraceCharSet::Index] Index out of Range.");
  }
}

size_t LeftBraceCharSet::Size() const { return 4; }

bool LeftBraceCharSet::InSet(char c) {
  return c == '(' || c == '<' || c == '{' || c == '[';
}

}  // namespace premierbob
