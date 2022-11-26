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
        mNodeSonList(new ConTagsNodeList){}; /* 默认每个成员都有初始化 */

  ~ConTagsNode(){};
  ConTagsNode(const ConTagsNode&) = delete;
  ConTagsNode& operator=(const ConTagsNode&) = delete;

  std::shared_ptr<ConTagsNode> DeepCopy();           /* 深拷贝 */
  std::shared_ptr<StringData> GetNodeName() const;   /* 结点名称 */
  std::shared_ptr<StringData> GetNodeValue() const;  /* 结点信息 */
  std::shared_ptr<ConTagsNodeList> GetNodeSonList(); /* 结点儿子列表 */

  void AddSon(std::shared_ptr<ConTagsNode> nSon);
  void SetNodeName(std::shared_ptr<StringData> nNodeName, bool nCopy);
  void SetNodeValue(std::shared_ptr<StringData> nNodeValue, bool nCopy);
  void DebugShow() const; /* 递归显示树形结构 */

 private:
  std::shared_ptr<StringData> mNodeName;
  std::shared_ptr<StringData> mNodeValue;
  std::shared_ptr<ConTagsNodeList> mNodeSonList;
};

}  // namespace premierbob
