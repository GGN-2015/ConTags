#include "StringData.h"

#include <cstring>
#include <string>

namespace premierbob {

StringData::StringData() : mStringData(nullptr), mStringLength(0) {}

StringData::StringData(const std::string& s) /* 从字符串获得值 */
    : mStringData(nullptr), mStringLength(0) {
  if (s.size() > 0) {
    this->SetData(s.c_str(), s.size());
  }
}

StringData::~StringData() { FreeData(); }

std::shared_ptr<StringData> StringData::DeepCopy() const {
  std::shared_ptr<StringData> nStringData(new StringData);
  nStringData->SetData(mStringData, mStringLength);
  return nStringData;
}

void StringData::SetData(const char* nStringData, size_t nStringLength) {
  if (mFinalized) {
    throw std::string(
        "[StringData::SetData] You Can not SetData for a Finalized "
        "StringData.");
  }

  FreeData();
  if (nStringLength != 0) {
    mStringData = new char[nStringLength];
    memcpy(mStringData, nStringData, nStringLength);
    mStringLength = nStringLength;
  }
}

size_t StringData::GetLength() const { return mStringLength; }

char StringData::Index(size_t nPos) const {
  if (0 <= nPos && nPos < mStringLength) {
    return mStringData[nPos];
  } else {
    throw std::string("[StringData::Index] Index Out of Range.");
  }
}

void StringData::Finalize() { mFinalized = true; }

const char* StringData::GetRawData() const { return mStringData; }

std::string StringData::GetString() const {
  std::string ans = "";
  for (int i = 0; i < GetLength(); i += 1) {
    ans += Index(i);
  }
  return ans;
}

void StringData::FreeData() {
  if (mStringData != nullptr) {
    delete[] mStringData;
  }
  mStringData = nullptr;
  mStringLength = 0;
}

}  // namespace premierbob
