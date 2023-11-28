//HW5  AVL Tree
//Due: 11:59pm, Monday, Nov. 13
//This homework requires more efforts. You should get started as soon as possible.
//Plan to complete add_node by this weekend.
//You are not allowed to use any extra function.
//You are not allowed to add extra members to either class node or class AVLtree.

#include <iostream>

using namespace std;

//You need to use the following node class for each node of the AVL tree
class node {
public:
	int value;
	int height;//this is node height. Leaf node is 1; empty node (i.e., NIL) is 0
	int Lheight, Rheight;//height of two child branches
	node* parent;//nullptr for root
	node* Lchild;
	node* Rchild;
	bool Is_Lchild;//true: L  false R
	node() {}
	node(int i, bool b) : value{ i }, height{ 1 }, Lheight{ 0 }, Rheight{ 0 }, parent{ nullptr },
		Lchild{ nullptr }, Rchild{ nullptr }, Is_Lchild{ b } {}

};

class avl_tree {
public:
	node* root;
	avl_tree() {
		root = nullptr;
	}

	//************************************************************************************
	//Implement the following member functions


	void add_node(int i) {
		//in case of a tie, go to the branch with lower height; if still a tie, go to left branch.
																																								//Step 1: Create a new node
		node* newNode = new node(i, false);  //create a new node


																																								//Step 2: Insert new node incorrect position
		if (root == nullptr) {											// if root is empty  place new newNode as root																						
			root = newNode;
			return;
		}

		node* current = root;

		node* parent = nullptr;

		while (current != nullptr) {	 //insert node in AVL 

			parent = current;			//update parent


																						//calculate left right heights 
			int leftHeight;
			int rightHeight;
			if (current->Lchild == nullptr) { 
				leftHeight = 0;
			}
			else {
				leftHeight = current->Lchild->height;
			}

			
			if (current->Rchild == nullptr) { 
				rightHeight = 0;
			}
			else {
				rightHeight = current->Rchild->height;
			}


			if (i < current->value) {

				current = current->Lchild;											//traverse left
			}

			else if (i > current->value) {

				current = current->Rchild;											// traverse right
			}
			else { //i == current->value 

				if (leftHeight <= rightHeight) {	
					current = current->Lchild;
				}
				else {
					current = current->Rchild;
				}
			}
		}




		newNode->parent = parent;				//update parent - node

		if (i < parent->value) { // if new node is less then  node
			parent->Lchild = newNode;
			newNode->Is_Lchild = 1;
		}
		else {
			parent->Rchild = newNode;// if new node is less then  node
			newNode->Is_Lchild = 0;

		}






		pair<node*, int> result = height_update(newNode->parent);																									//Step 3: Update height, balance tree

		switch (result.second) {

		case 1:									//LL Violation
			R_Rotate(result.first);
			height_update(result.first);
			break;


		case 3:									//RR violation
			L_Rotate(result.first);
			height_update(result.first);
			break;

		case 2:									//LR violation
			L_Rotate(result.first->Lchild);

			height_update(result.first->Lchild->Lchild);

			R_Rotate(result.first);

			height_update(result.first);
			break;


		case 4:									//RL violation
			R_Rotate(result.first->Rchild);

			height_update(result.first->Rchild->Rchild);											//minor fix

			L_Rotate(result.first);

			height_update(result.first);
			break;


		default:
			break;
		}
		



	}

	
	void delete_node(int i) {
		//Delete the node with value i.  in case of multiple nodes with value i, delete the first node encountered.

		//If the node to delete is a leaf node, just delete it.
		//If the node is parent of only a leaf node, replace it with the leaf node.
		//For all other cases, replace it with in-oreder predecessor if left branch has a larger height; replace it with a
		//in-order successor if right branch has a larger height; replace it with in-order predecessor in case of a tie.

		node* startNode = nullptr; //for starting where to update from 
																																															//step 1: Find Node to delete
		node* current = root;

		while (current != nullptr) {
			if (current->value == i) {		//if node is found break
				break;
			}
			else if (i < current->value) {		//if i  is smaller the current vlaue move left 
				current = current->Lchild;
			}
			else {
				current = current->Rchild;
			}
		}

		if (current == nullptr) {
			return;
		}

																																													//Step 2: Delete based on nodes children

		if ((current->Lchild == nullptr) && (current->Rchild == nullptr)) {																															//delete a leaf 
			if (current != root) {
				if (current->Is_Lchild) {					//if current is a Lchild, delete parents left child
					current->parent->Lchild = nullptr;
				}
				else {
					current->parent->Rchild = nullptr;		//if current is a Rchild, delete parents right child		
				}
				startNode = current->parent;
			}
			else {
				root = nullptr;
			}
			delete current;
		}
													
		else if ((current->Lchild == nullptr) || (current->Rchild == nullptr)) {																												//delete node with one child 
			node* replacement;

			if (current->Lchild != nullptr) {		//locate its replacement
				replacement = current->Lchild;
			}
			else {								
				replacement = current->Rchild;
			}


			if (current != root) {
				replacement->parent = current->parent;

				if (current->Is_Lchild) { //if current is a Lchild, set child to position of current
					current->parent->Lchild = replacement;
				}
				else {
					current->parent->Rchild = replacement; // set child to position of current
				}
			}
			else {
				root = replacement;
				replacement->parent = nullptr;
			}

			delete current;
		}

		else {																																													//delete node with two children
			
			int leftheight = 0;
			int rightheight = 0;
			node* replacement;
			

			if (current->Lchild != nullptr) {		//calculate left height
				leftheight = current->Lchild->height;
			}
			else if (current->Rchild != nullptr) {			//calculate reight height
				rightheight = current->Rchild->height;
			}
																	//locate replacement 
			if (leftheight > rightheight) {		//find in-order successor
				replacement = current->Lchild;
				while (replacement->Rchild != nullptr) {
					replacement = replacement->Rchild;
				}

			}
			else {							//find in-order predecessor
				replacement = current->Rchild;
				while (replacement->Lchild != nullptr) {
					replacement = replacement->Rchild;
				}
			}

			current->value = replacement->value;		//replace value of current	with replacement


			if (replacement->Lchild == nullptr && replacement->Rchild == nullptr) {		// empty replacement, delete, if its a leaf
				if (replacement == replacement->parent->Rchild) {
					replacement->parent->Rchild = nullptr;
				}
				else {
					replacement->parent->Lchild = nullptr;
				}
				startNode = replacement->parent;
				delete replacement;

			}

			else {														// empty replacement, delete, if has a child
				node* child;

				if (replacement->Lchild != nullptr) {
					child = replacement->Lchild;
				}
				else {
					child = replacement->Rchild;
				}
				child->parent = replacement->parent;
				if (replacement == replacement->parent->Lchild) {
					replacement->parent->Lchild = child;
				}
				else {
					replacement->parent->Rchild = child;
				}
				startNode = replacement->parent;
				delete replacement;
			}
		}

		
		

		// Step 3: Update heights and balance the tree
		pair<node*, int> result = height_update(startNode);

																																												// Step 3: Update heights and balance the tree

		
		switch (result.second) {

		case 1:									//LL Violation
			R_Rotate(result.first);
			height_update(result.first);
			break;


		case 3:									//RR violation
			L_Rotate(result.first);
			height_update(result.first);
			break;

		case 2:									//LR violation
			L_Rotate(result.first->Lchild);
			

			height_update(result.first);
			R_Rotate(result.first);
			height_update(result.first);
			break;


		case 4:									//RL violation
			R_Rotate(result.first->Rchild);
			height_update(result.first);
			L_Rotate(result.first);
			height_update(result.first);
			break;


		default:
			break;
		}

		result = height_update(startNode);		//repeat as other violations may have occurred

	}

	



	void in_order_traversal(node* p) {//such as (2 5 1 2 3) (3 3 0 1 0) (5 2 1 0 0) (6 1 0 2 1) .....  (value height Is_Lchild Lheight Rheight)

		if (p == nullptr) {
			return;
		}

		in_order_traversal(p->Lchild); //recur on left child

		cout << "(" << p->value << " " << p->height << " ";				//value, height 

		if (p->Is_Lchild) {											   //is_Lchild
			cout << "1 ";
		}
		else {
			cout << "0 ";
		}

		if (p->Lchild != nullptr) {
			cout << p->Lchild->height << " ";
		}
		else {
			cout << "0 ";
		}

		if (p->Rchild != nullptr) {
			cout << p->Rchild->height;
		}
		else {
			cout << "0";
		}

		cout << ") ";


		in_order_traversal(p->Rchild);


	}


	pair<node*, int> height_update(node* p) {
		/*
		This function will be invoked by add_node and delete_node.
		p points to the first node that we need to check for possible height update.  We then need to check possible height update toward root.
		All nodes whose heights need to be updated will be performed in this function.
		In case of a violation, the function will return
		{address of Action Node, pattern}, where violation pattern = 1, 2, 3, 4 for LL, LR RR, RL, respectively.
		In case of no violation, the function will return {nullptr, 0}.
		*/
																																								//Step 1: initalize first node we check for height update
		node* current = p;



		while (current != nullptr) {																															//Step 2: set heights of nodes and nodes with children

			int leftHeight;
			int rightHeight;

																																									

																								
			if (current->Lchild == nullptr) {			//if theres no left child, left height is 0
				leftHeight = 0;
			}
			else {
				leftHeight = current->Lchild->height;		
			}

			if (current->Rchild == nullptr) {
				rightHeight = 0;
			}
			else {
				rightHeight = current->Rchild->height;
			}


			//update the current nodes height 

			if (current->Lchild == nullptr && current->Rchild == nullptr) {																					
				current->height = 1;
			}
			else {
				current->height = 1 +max(leftHeight, rightHeight);
			}

		



			int balance = leftHeight - rightHeight;

			if (balance > 1) {																																//Step 2b: Check for imbalance

				if (current->Lchild->Lchild != nullptr) { // LL violation
					return { current, 1 };
				}
				else { // LR violation
					return { current, 2 };
				}
			}
			else if (balance < -1) {
	
				if (current->Rchild->Rchild != nullptr ) { // RR violation
					return { current, 3 };
				}
				else { // RL Violation
					return { current, 4 };
				}
			}

			current = current->parent; //move to parent node																							//Step 2c: move to parent node



		}

		root->Is_Lchild = 0;

		return { nullptr, 0 };
	}



















	void L_Rotate(node* p) {
		//p points to the node at which the rotation will be performed.
		node* newRoot = p->Rchild;

		p->Rchild = newRoot->Lchild;

		if (newRoot->Lchild != nullptr) {   //update parent of Lchild of newRoot
			newRoot->Lchild->parent = p;
			newRoot->Lchild->Is_Lchild = true;
		}

		newRoot->parent = p->parent;		//newRoots parent is whatever p's parent was

		if (p->parent == nullptr) {
			root = newRoot;
		}
		else if (p == p->parent->Lchild) { //if p is the left child of its parent, make newRoot left child of parent 
			p->parent->Lchild = newRoot;
			newRoot->Is_Lchild = true;
		}
		else {
			p->parent->Rchild = newRoot; //make newRoot right child of parent
			newRoot->Is_Lchild = false;

		}
		p->Is_Lchild = true;
		if (p->Rchild != nullptr) {			//set its right child to false
			p->Rchild->Is_Lchild = false;
		}
		newRoot->Lchild = p; // make p the left child of new root
		p->parent = newRoot; //update p's parent



	}

	void R_Rotate(node* p) {
		//p points to the node at which the rotation will be performed.
		node* newRoot = p->Lchild;
		
		p->Lchild = newRoot->Rchild;
		


		if (newRoot->Rchild != nullptr) {   //update parent of Rchild of newRoot
			newRoot->Rchild->parent = p;
			newRoot->Lchild->Is_Lchild = true;
		}
		
		newRoot->parent = p->parent;		//newRoots parent is whatever p's parent was

		if (p->parent == nullptr) {
			root = newRoot;

		}
		else if (p == p->parent->Rchild) { //if p is the right child of its parent, make newRoot right child of parent 
			p->parent->Rchild = newRoot;
			newRoot->Is_Lchild = false;
		}
		else {
			p->parent->Lchild = newRoot; //make newRoot left child of parent
			newRoot->Is_Lchild = true;
		}

		p->Is_Lchild = false;
		if(p->Lchild != nullptr ){
			p->Lchild->Is_Lchild = true;
		}
		newRoot->Rchild = p; // make p the right child of new root
		p->parent = newRoot; //update p's parent





	}
};


int main() {
	//Different test cases will be used during grading.
	avl_tree t1;
	t1.add_node(100);
	t1.add_node(50);
	t1.add_node(150);
	t1.add_node(25);
	t1.add_node(75);
	t1.add_node(125);
	t1.add_node(175);
	t1.add_node(20);
	t1.add_node(30);
	t1.add_node(70);
	t1.add_node(80);
	t1.add_node(120);
	t1.add_node(130);
	t1.add_node(170);
	t1.add_node(180);
	t1.add_node(17);
	t1.add_node(22);
	t1.add_node(27);
	t1.add_node(35);
	t1.add_node(67);
	t1.add_node(72);
	t1.add_node(78);
	t1.add_node(82);
	t1.add_node(117);
	t1.add_node(122);
	t1.add_node(127);
	t1.add_node(132);
	t1.add_node(167);
	t1.add_node(172);
	t1.add_node(178);
	t1.add_node(182);
	t1.add_node(16);
	t1.add_node(18);
	t1.add_node(23);
	t1.add_node(26);
	t1.add_node(28);
	t1.add_node(34);
	t1.add_node(36);
	t1.add_node(66);
	t1.add_node(68);
	t1.add_node(73);
	t1.add_node(77);
	t1.add_node(81);
	t1.add_node(83);
	t1.add_node(116);

	t1.delete_node(18);
	t1.delete_node(175);
	t1.delete_node(50);
	t1.delete_node(150);
	t1.delete_node(100);
	
	t1.in_order_traversal(t1.root);
	return 0;
}