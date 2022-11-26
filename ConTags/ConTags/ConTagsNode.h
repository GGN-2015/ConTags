#pragma once
#include <memory>
#include <vector>

#include "StringData.h"

namespace premierbob {

class ConTagsNode;
typedef std::vector<std::shared_ptr<ConTagsNode>> ConTagsNodeList;

class ConTagsNode {
 public:
  ConTagsNode()
      : mNodeName(new StringData),
        mNodeValue(new StringData),
        mNodeSonList(new ConTagsNodeList){}; /* Ĭ��ÿ����Ա���г�ʼ�� */

  ~ConTagsNode(){};
  ConTagsNode(const ConTagsNode&) = delete;
  ConTagsNode& operator=(const ConTagsNode&) = delete;

  std::shared_ptr<ConTagsNode> DeepCopy();           /* ��� */
  std::shared_ptr<StringData> GetNodeName() const;   /* ������� */
  std::shared_ptr<StringData> GetNodeValue() const;  /* �����Ϣ */
  std::shared_ptr<ConTagsNodeList> GetNodeSonList(); /* �������б� */

  void AddSon(std::shared_ptr<ConTagsNode> nSon);
  void SetNodeName(std::shared_ptr<StringData> nNodeName, bool nCopy);
  void SetNodeValue(std::shared_ptr<StringData> nNodeValue, bool nCopy);
  void DebugShow() const; /* �ݹ���ʾ���νṹ */

 private:
  std::shared_ptr<StringData> mNodeName;
  std::shared_ptr<StringData> mNodeValue;
  std::shared_ptr<ConTagsNodeList> mNodeSonList;
};

}  // namespace premierbob
