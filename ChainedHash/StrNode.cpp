#ifndef STRNODE_CPP
#include <string>
using std::string;

class StrNode
{
public:
    StrNode(string);
    ~StrNode();

    string data;
    StrNode* next;
};

StrNode::StrNode(string data): data(data), next(nullptr) {}

StrNode::~StrNode()
{
}
#endif //NODE_H