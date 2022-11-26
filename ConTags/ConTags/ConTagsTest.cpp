#include <iostream>

#include "AlphaDigitCharSet.h"
#include "BraceCharSet.h"
#include "ConTagsNode.h"
#include "ICharSet.h"
#include "LeftBraceCharSet.h"
#include "RightBraceCharSet.h"
#include "StringData.h"
#include "StringFind.h"

using namespace premierbob;

int main() {
  std::shared_ptr<ICharSet> pCharSet(new RightBraceCharSet);
  for (size_t i = 0; i < pCharSet->Size(); i += 1) {
    std::cerr << "Char[" << i << "] = \t" << pCharSet->Index(i) << std::endl;
  }
  return 0;
}
