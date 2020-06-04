#include<iostream>
#include<variant>
#include<memory>
#include<vector>
#include<string>
#include<stack>
#include<queue>

class TreeNode;

using node_ptr = std::shared_ptr<TreeNode>;
using NodeType = std::variant<std::string, int, double>;



class TreeNode {
public:
	TreeNode(NodeType value) :m_value(value) {}
	void SetChild(node_ptr &child);
public:
	NodeType m_value;
	std::vector<node_ptr> children;
};

class Tree {
public:
	void serialize(std::ostream& out);
	void deserialize(std::istream& in);
	void Print();
	static NodeType Parse(const std::string&);
	friend std::ostream& operator<< (std::ostream &out, NodeType &data);
private:
	void serialize(std::ostream&, const node_ptr&);
	node_ptr root;
};

