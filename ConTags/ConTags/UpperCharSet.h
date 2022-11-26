#pragma once
#include "ICharSet.h"
namespace premierbob {

class UpperCharSet : public ICharSet {
 public:
  UpperCharSet(){};
  virtual ~UpperCharSet(){};

  UpperCharSet(const UpperCharSet&) = delete;
  UpperCharSet& operator=(const UpperCharSet&) = delete;

  virtual char Index(int nPos) override;
  virtual size_t Size() const override;
  virtual bool InSet(char c) override;
};

}  // namespace premierbob
