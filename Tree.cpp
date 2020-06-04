#include "pch.h"
#include "Tree.h"
#include <sstream>
#include <exception>

std::ostream& operator<< (std::ostream &out, NodeType &data) {
	std::visit([&out](auto const& e) { out << e; }, data);
	return out;
}

void TreeNode::SetChild(node_ptr &child) {
	children.push_back(child);
}

void Tree::deserialize(std::istream& in) {
	try {
		std::string str;
		in >> str;
		std::stringstream ss(str);
		std::stack<TreeNode*> parent_nodes;
		int level = 0;
		std::string word = "";
		char letter;
		ss >> letter;
		while (letter != '[') {
			word += letter;
			ss >> letter;
		}
		if (!word.empty()) {
			root = std::make_shared<TreeNode>(word);
			parent_nodes.push(root.get());
			level++;
		}
		else { throw std::exception("Trere is not first element"); }
		while (!parent_nodes.empty()&&(ss>>letter)) {
			word = "";
			while (letter != '[' && letter != ',' && letter != ']' &&(!ss.eof())) {
				word += letter;
				ss >> letter;
			}

			if (letter == '[') {
				if (word.empty()) { throw std::logic_error("No value before '['"); }
				node_ptr node = std::make_shared<TreeNode>(Parse(word));
				parent_nodes.top()->SetChild(node);
				parent_nodes.push(node.get());
				level++;
			}
			if (letter == ',') {
				if (!word.empty()) {
					node_ptr node = std::make_shared<TreeNode>(Parse(word));
					parent_nodes.top()->SetChild(node);
				}
			}
			if (letter == ']') {

				if (!word.empty()) {
					node_ptr node = std::make_shared<TreeNode>(Parse(word));
					parent_nodes.top()->SetChild(node);
				}
				parent_nodes.pop();
				level--;
			}
		}

		if (ss.eof()) {
			if (level != 0) { throw std::logic_error("Number of '[' is not equal to number of ']'"); }
		}
		else if(ss >> letter) { throw std::logic_error("Parse Error"); }
		
	}
	catch(std::exception &exeption){
		std::cerr << "Error:" << exeption.what() << '/n';
		exit(-1);
		
	}
}

void Tree::serialize(std::ostream& out) {
	if (root != NULL) {
		serialize(out, root);
	}
	
}

void Tree::serialize(std::ostream &out, const node_ptr &node) {
	auto value = node->m_value;
	out << value;
	if (!node->children.empty()) {
		out << '[';
		bool first = true;
		for (auto const &child : node->children) {
			if (!first) { out << ','; }
			serialize(out, child);
			first = false;
		}
		out << ']';
	}
	
		
}

void Tree::Print() {
	if (root!=NULL) {
		std::queue<TreeNode *> queue;
		queue.push(root.get());
		while (!queue.empty()) {
			auto &node = *queue.front();
			std::cout << "Tree node: " << node.m_value << "---->" << "Tree node children: ";
			bool first = true;
			for (const auto &ch : node.children) {
				if (!first)
					std::cout << ',';
				first = false;
				std::cout << ch->m_value;
				if (!ch->children.empty())
					queue.push(ch.get());
			}
			queue.pop();
			std::cout << '\n';
		}
	}
}

NodeType Tree::Parse(const std::string &str) {
	try {
		std::size_t pos = 0;
		int val = std::stoi(str, &pos);
		if (pos == str.size())
			return val;
	}
	catch (...) {}
	try {
		std::size_t pos = 0;
		double val = std::stod(str, &pos);
		if (pos == str.size())
			return val;
	}
	catch (...) {}

	return std::move(str);
}