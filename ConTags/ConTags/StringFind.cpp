#include "StringFind.h"

#include "StringDataView.h"

namespace premierbob {

int StringFind::Find(std::shared_ptr<StringData> pStringData,
                     std::string nString, size_t nFrom) {
  size_t len = nString.size();
  for (size_t i = nFrom; i + len <= pStringData->GetLength(); i += 1) {
    /* ��� [i, i + len) */
    std::shared_ptr<StringDataView> pStringDataView(
        new StringDataView(pStringData, i, i + len));
    if (pStringDataView->GetString() == nString) {
      return i; /* �ҵ��� */
    }
  }
  return -1; /* Not Found */
}

}  // namespace premierbob
