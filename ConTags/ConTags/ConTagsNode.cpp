#include "ConTagsNode.h"

#include <iostream>

namespace premierbob {

std::shared_ptr<ConTagsNode> ConTagsNode::DeepCopy() {
  std::shared_ptr<ConTagsNode> nNode(new ConTagsNode);

  nNode->mNodeName = this->mNodeName->DeepCopy();
  nNode->mNodeValue = this->mNodeValue->DeepCopy();

  for (auto& sonNode : *mNodeSonList) {
    nNode->mNodeSonList->push_back(sonNode->DeepCopy()); /* Éî¿½±´ */
  }
  return nNode;
}

std::shared_ptr<StringData> ConTagsNode::GetNodeName() const {
  return mNodeName;
}

std::shared_ptr<StringData> ConTagsNode::GetNodeValue() const {
  return mNodeValue;
}

std::shared_ptr<ConTagsNodeList> ConTagsNode::GetNodeSonList() {
  return mNodeSonList;
}

void ConTagsNode::AddSon(std::shared_ptr<ConTagsNode> nSon) {
  if (nSon.get() == this) {
    throw "[ConTagsNode::AddSon] Can not Add `this` into Sonlist of `this`.";
  }
  mNodeSonList->push_back(nSon);
}

void ConTagsNode::SetNodeName(std::shared_ptr<StringData> nNodeName,
                              bool nCopy) {
  if (nCopy) {
    mNodeName = nNodeName->DeepCopy();
  } else {
    mNodeName = nNodeName;
  }
}

void ConTagsNode::SetNodeValue(std::shared_ptr<StringData> nNodeValue,
                               bool nCopy) {
  if (nCopy) {
    mNodeValue = nNodeValue->DeepCopy();
  } else {
    mNodeValue = nNodeValue;
  }
}

void ConTagsNode::DebugShow() const {
  if (mNodeValue->GetLength() > 0) {
    std::cerr << mNodeName->GetString() << ":" << mNodeValue->GetString()
              << std::endl;
  } else {
    std::cerr << mNodeName->GetString() << ": {";
    for (auto& sonNode : *mNodeSonList) {
      sonNode->DebugShow();
    }
    std::cerr << "}" << std::endl;
  }
}

}  // namespace premierbob
