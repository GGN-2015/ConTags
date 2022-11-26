#include "StringDataView.h"

#include <string>

premierbob::StringDataView::StringDataView(
    std::shared_ptr<StringData> nBaseStringData, size_t nFrom, size_t nTo)
    : mBaseStringData(nBaseStringData), mFrom(nFrom), mTo(nTo) {
  if (nFrom >= nTo) {
    throw std::string(
        "[StringDataView::StringDataView] nFrom should Less than nTo.");
  }
  nBaseStringData->Finalize(); /* 原始数据不再可变 */

  if (0 <= nFrom && nTo <= nBaseStringData->GetLength()) {
  } else {
    throw std::string(
        "[StringDataView::StringDataView] Index out of Range When Creating "
        "View.");
  }
}

std::shared_ptr<premierbob::StringData> premierbob::StringDataView::DeepCopy()
    const {
  std::shared_ptr<premierbob::StringData> nStringData(
      new premierbob::StringData);

  size_t len = this->GetLength();
  if (len > 0) {
    char* tmpBuf = new char[len];
    memcpy(tmpBuf, this->GetRawData(), len); /* 快速拷贝 */
    nStringData->SetData(tmpBuf, len);       /* 复制数据 */
    delete[] tmpBuf;
  }
  return nStringData;
}

void premierbob::StringDataView::SetData(const char*, size_t) {
  throw std::string("[StringDataView::SetData] Can not SetData for a View.");
}

size_t premierbob::StringDataView::GetLength() const {
  return mTo - mFrom; /* 左闭右开 */
}

char premierbob::StringDataView::Index(size_t nPos) const {
  if (0 <= nPos && nPos < this->GetLength()) {
    return mBaseStringData->Index(nPos + mFrom);
  } else {
    throw std::string("[StringDataView::Index] Index out of Range.");
  }
}

const char* premierbob::StringDataView::GetRawData() const {
  return mBaseStringData->GetRawData() + mFrom;
}

std::string premierbob::StringDataView::GetString() const {
  std::string ans = "";
  for (size_t i = 0; i < GetLength(); i += 1) {
    ans += Index(i);
  }
  return ans;
}
