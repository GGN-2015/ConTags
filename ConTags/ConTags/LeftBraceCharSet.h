#pragma once
#include "ICharSet.h"
namespace premierbob {

class LeftBraceCharSet : public ICharSet {
 public:
  LeftBraceCharSet(){};
  virtual ~LeftBraceCharSet(){};

  LeftBraceCharSet(const LeftBraceCharSet&) = delete;
  LeftBraceCharSet& operator=(const LeftBraceCharSet&) = delete;

  virtual char Index(int nPos) override;
  virtual size_t Size() const override;
  virtual bool InSet(char c) override;
};

}  // namespace premierbob
