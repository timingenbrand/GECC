#include <iostream>
#include <algorithm>
#include "snm_functions.h"
#include "snm_variables.h"
#include "snm_tree.h"

using namespace std;

vector<Node> tree_node_vec;
void SortTree(){
	int nodeindex;
	for(int reaction : recalc_list){
		nodeindex = tree_pointer_vec[reaction];
		CheckNode(nodeindex);
	}
}

void CheckNode(int a){
	// check parent
	if(tree_node_vec[a].b_parent){
	if(tree_node_vec[a].tau < tree_node_vec[a].parent->tau){

		int parentnode = tree_pointer_vec[tree_node_vec[a].parent->reaction];
		SwapNodes(a, parentnode);
		CheckNode(parentnode); // have to check main node again (indices swapped)
		return;
	}}
	// check left child
	if(tree_node_vec[a].b_left){
	if(tree_node_vec[a].tau > tree_node_vec[a].left->tau){

		int leftnode = tree_pointer_vec[tree_node_vec[a].left->reaction];
		SwapNodes(a, leftnode);
		CheckNode(leftnode); // have to check main node again
		return;
	}}
	// check right child
	if(tree_node_vec[a].right){
	if(tree_node_vec[a].tau > tree_node_vec[a].right->tau){

		int rightnode = tree_pointer_vec[tree_node_vec[a].right->reaction];
		SwapNodes(a, rightnode);
		CheckNode(rightnode); // have to check main node again
		return;
	}}

}
void SwapNodes(int a, int b){
	int old_parent;
	int old_child;
	if (a>b){
		old_parent = a;
		old_child = b;
	}
	else{
		old_parent = b;
		old_child = a;
	}
	int rea = tree_pointer_vec[tree_node_vec[a].reaction];
	tree_pointer_vec[tree_node_vec[a].reaction] = tree_pointer_vec[tree_node_vec[b].reaction];
	tree_pointer_vec[tree_node_vec[b].reaction] = rea;
	Node helpnode = tree_node_vec[a];
	tree_node_vec[a] = tree_node_vec[b];
	tree_node_vec[b] = helpnode;
	// keep parent/children relations in tact
	FindRelatedNodes(a);
	FindRelatedNodes(b);
}
void CreateTreeStructure()
{
	// creating all nodes
	Node helpnode(0,0);
	tree_node_vec.resize(0, helpnode);
	for (int s=0; s<n_reactions; s++){
		helpnode.reaction = s;
		helpnode.tau = 0.;
		tree_node_vec.push_back(helpnode);
	}
	// set correct parents and children for every node
	for (int s=0; s<n_reactions; s++){
		FindRelatedNodes(s);
	}
}

void FindRelatedNodes(int node){
	int help;
	tree_node_vec[node].parent = NULL;
	tree_node_vec[node].left = NULL;
	tree_node_vec[node].right = NULL;
	tree_node_vec[node].b_left=false;
	tree_node_vec[node].b_right=false;
	tree_node_vec[node].b_parent=false;

	help = 2 * node + 1;
	if (help<n_reactions){
		tree_node_vec[node].left = &(tree_node_vec[help]);
		tree_node_vec[node].b_left = true;
	}

	// child right
	help = 2 * node + 2;
	if (help<n_reactions){
		tree_node_vec[node].right = &(tree_node_vec[help]);
		tree_node_vec[node].b_right = true;
	}
	// parent
	if (node % 2 == 0){
		help = (node - 2) / 2;
	}
	else{
		help = (node-1)/2;
	}
	if (help>=0){
		tree_node_vec[node].parent = &(tree_node_vec[help]);
		tree_node_vec[node].b_parent = true;
	}
}
