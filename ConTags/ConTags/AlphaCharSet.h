#pragma once
#include <memory>

#include "ICharSet.h"
#include "LowerCharSet.h"
#include "UpperCharSet.h"

namespace premierbob {

class AlphaCharSet : public ICharSet {
 public:
  AlphaCharSet()
      : pLowerCharSet(new LowerCharSet), pUpperCharSet(new UpperCharSet){};
  virtual ~AlphaCharSet(){};

  AlphaCharSet(const AlphaCharSet&) = delete;
  AlphaCharSet& operator=(const AlphaCharSet&) = delete;

  virtual char Index(int nPos) override;
  virtual size_t Size() const override;
  virtual bool InSet(char c) override;

 private:
  std::shared_ptr<LowerCharSet> pLowerCharSet;
  std::shared_ptr<UpperCharSet> pUpperCharSet;
};

}  // namespace premierbob
