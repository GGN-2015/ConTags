#pragma once
#include <memory>

#include "ICharSet.h"
#include "LeftBraceCharSet.h"
#include "RightBraceCharSet.h"

namespace premierbob {

class BraceCharSet : public ICharSet {
 public:
  BraceCharSet()
      : mLeftBraceCharSet(new LeftBraceCharSet),
        mRightBraceCharSet(new RightBraceCharSet){};

  virtual ~BraceCharSet(){};

  BraceCharSet(const BraceCharSet&) = delete;
  BraceCharSet& operator=(const BraceCharSet&) = delete;

  virtual char Index(int nPos) override;
  virtual size_t Size() const override;
  virtual bool InSet(char);

 private:
  std::shared_ptr<LeftBraceCharSet> mLeftBraceCharSet;
  std::shared_ptr<RightBraceCharSet> mRightBraceCharSet;
};

}  // namespace premierbob
