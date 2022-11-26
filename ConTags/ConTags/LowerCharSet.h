#pragma once
#include "ICharSet.h"

namespace premierbob {

class LowerCharSet : public ICharSet {
 public:
  LowerCharSet(){};
  virtual ~LowerCharSet(){};

  LowerCharSet(const LowerCharSet&) = delete;
  LowerCharSet& operator=(const LowerCharSet&) = delete;

  virtual char Index(int nPos) override;
  virtual size_t Size() const override;
  virtual bool InSet(char c) override;
};

}  // namespace premierbob
