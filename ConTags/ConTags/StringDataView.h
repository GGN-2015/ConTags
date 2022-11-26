#pragma once

#include <memory>

#include "StringData.h"
namespace premierbob {

class StringDataView : public StringData {
 public:
  StringDataView(std::shared_ptr<StringData> nBaseStringData, size_t nFrom,
                 size_t nTo); /* 从 Base 串中截取一段内容 */
  virtual ~StringDataView() override {}

  StringDataView(const StringDataView&) = delete;
  StringDataView& operator=(const StringDataView&) = delete;

  virtual std::shared_ptr<StringData> DeepCopy() const override;
  virtual void SetData(const char*, size_t) override;

  virtual size_t GetLength() const override;
  virtual char Index(size_t nPos) const override;  /* 获取某个位置 */
  virtual const char* GetRawData() const override; /* 获取原始数据 */
  virtual std::string GetString() const;           /* 效率很低 */
 private:
  std::shared_ptr<StringData> mBaseStringData;
  size_t mFrom, mTo;
};

}  // namespace premierbob
