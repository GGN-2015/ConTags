#pragma once
namespace premierbob {

class ICharSet {
 public:
  ICharSet() {}
  virtual ~ICharSet() {}

  ICharSet(const ICharSet&) = delete;
  ICharSet& operator=(const ICharSet&) = delete;

  virtual char Index(int nPos) = 0;
  virtual bool InSet(char c) = 0; /* ���ĳ���ַ��Ƿ������������ */
  virtual size_t Size() const = 0;
};

}  // namespace premierbob
