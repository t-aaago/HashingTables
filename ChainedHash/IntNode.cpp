#ifndef INTNODE_CPP


class IntNode
{
public:
    IntNode(int);
    ~IntNode();

    int data;
    IntNode* next;
};

IntNode::IntNode(int data): data(data), next(nullptr) {}

IntNode::~IntNode()
{
}
#endif //NODE_H