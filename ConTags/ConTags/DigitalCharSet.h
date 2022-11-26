#pragma once
#include "ICharSet.h"

namespace premierbob {

class DigitalCharSet : public ICharSet {
 public:
  DigitalCharSet(){};
  virtual ~DigitalCharSet(){};

  DigitalCharSet(const DigitalCharSet&) = delete;
  DigitalCharSet& operator=(const DigitalCharSet&) = delete;

  virtual char Index(int nPos) override;
  virtual size_t Size() const override;
  virtual bool InSet(char c) override;
};

}  // namespace premierbob
