#pragma once
#include "ICharSet.h"

namespace premierbob {

class RightBraceCharSet : public ICharSet {
 public:
  RightBraceCharSet(){};
  virtual ~RightBraceCharSet(){};

  RightBraceCharSet(const RightBraceCharSet&) = delete;
  RightBraceCharSet& operator=(const RightBraceCharSet&) = delete;

  virtual char Index(int nPos) override;
  virtual size_t Size() const override;
  virtual bool InSet(char c) override;
};

}  // namespace premierbob
