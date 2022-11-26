#pragma once
#include <memory>
#include <string>

namespace premierbob {

class StringData {
 public:
  StringData();
  StringData(const std::string& s);
  virtual ~StringData();

  StringData(const StringData&) = delete;            /* 禁用拷贝构造 */
  StringData& operator=(const StringData&) = delete; /* 禁用赋值函数 */

  virtual std::shared_ptr<StringData> DeepCopy() const; /* 深拷贝 */
  virtual void SetData(const char*, size_t);            /* 拷贝新值 */

  virtual size_t GetLength() const;       /* 获取串长度 */
  virtual char Index(size_t nPos) const;  /* 获取某个位置的值 */
  virtual void Finalize();                /* 设置数据不再可变化 */
  virtual const char* GetRawData() const; /* 获取原始数据 */

  virtual std::string GetString() const; /* 效率很低 */

 private:
  void FreeData();

  bool mFinalized = false;
  char* mStringData;
  size_t mStringLength;
};

}  // namespace premierbob
