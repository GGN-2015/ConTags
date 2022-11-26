#pragma once
#include <memory>

#include "AlphaCharSet.h"
#include "DigitalCharSet.h"
#include "ICharSet.h"

namespace premierbob {

class AlphaDigitCharSet : public ICharSet {
 public:
  AlphaDigitCharSet()
      : pAlphaCharSet(new AlphaCharSet), pDigitalCharSet(new DigitalCharSet){};
  virtual ~AlphaDigitCharSet(){};

  AlphaDigitCharSet(const AlphaDigitCharSet&) = delete;
  AlphaDigitCharSet& operator=(const AlphaDigitCharSet&) = delete;

  virtual char Index(int nPos) override;
  virtual size_t Size() const override;
  virtual bool InSet(char c) override;

 private:
  std::shared_ptr<AlphaCharSet> pAlphaCharSet;
  std::shared_ptr<DigitalCharSet> pDigitalCharSet;
};

}  // namespace premierbob
