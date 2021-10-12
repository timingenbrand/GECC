//#include <string>
//#include <random>
#include "snm_variables.h"


struct Node {
    double tau;
	int reaction;
	bool b_left = false;
	bool b_right = false;
	bool b_parent = false;
    struct Node* left;
    struct Node* right;
	struct Node* parent;

    Node(int react, double val)
    {
        reaction = react;
		tau = val;

        // Left and right child for node
        // will be initialized to null
		parent = NULL;
        left = NULL;
        right = NULL;
    }
};

extern std::vector<Node> tree_node_vec;
void CheckNode(int a);
void SwapNodes(int a, int b);
void FindRelatedNodes(int node);
