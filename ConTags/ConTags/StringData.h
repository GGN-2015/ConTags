#pragma once
#include <memory>
#include <string>

namespace premierbob {

class StringData {
 public:
  StringData();
  StringData(const std::string& s);
  virtual ~StringData();

  StringData(const StringData&) = delete;            /* ���ÿ������� */
  StringData& operator=(const StringData&) = delete; /* ���ø�ֵ���� */

  virtual std::shared_ptr<StringData> DeepCopy() const; /* ��� */
  virtual void SetData(const char*, size_t);            /* ������ֵ */

  virtual size_t GetLength() const;       /* ��ȡ������ */
  virtual char Index(size_t nPos) const;  /* ��ȡĳ��λ�õ�ֵ */
  virtual void Finalize();                /* �������ݲ��ٿɱ仯 */
  virtual const char* GetRawData() const; /* ��ȡԭʼ���� */

  virtual std::string GetString() const; /* Ч�ʺܵ� */

 private:
  void FreeData();

  bool mFinalized = false;
  char* mStringData;
  size_t mStringLength;
};

}  // namespace premierbob
