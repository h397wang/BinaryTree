#ifndef BINARY_TREE_H
#define BINARY_TREE_H


#include <iostream>
#include <string>

using namespace std;


class BinaryTree{
	
	public:
		BinaryTree(const int & k);
		BinaryTree(const int * a, const int size);
		~BinaryTree();
		
		// Accessors
		int getKey() const;
		BinaryTree* getParent() const;
		BinaryTree* getLeft() const;
		BinaryTree* getRight() const;
		
		// Searches
		void inOrderTraversal(BinaryTree *);
		BinaryTree * min();
		BinaryTree * max();
		BinaryTree * successor();
		BinaryTree * predecessor(); 
		
		
		// Mutators
		void setKey(const int &);
		void setParent(BinaryTree*);
		void setLeft(BinaryTree*);
		void setRight(BinaryTree*);
		
		void insert(const int &);

		void remove(BinaryTree *);
		
		BinaryTree* search(BinaryTree*, const int &);
		
	private:	
		int keyValue;
		BinaryTree* parent;
		BinaryTree* left;
		BinaryTree* right;
				
		BinaryTree* min(BinaryTree *) const;
		BinaryTree* max(BinaryTree *) const;
	
		void insert(BinaryTree *, const int &);
};


BinaryTree::BinaryTree(const int & k){
	parent = NULL;
	left = NULL;
	right = NULL;
	keyValue = k;
	
}

BinaryTree::BinaryTree(const int * a, const int size){
	
	keyValue = a[0];
	
	for (int i = 1; i < size; i++){
		insert(this, a[i]);
	}
}

BinaryTree::~BinaryTree(){
	// no need to do anything...
}

int BinaryTree::getKey() const{
	return keyValue;	
}


BinaryTree* BinaryTree::getParent() const{
	return parent;	
}

BinaryTree* BinaryTree::getLeft() const{
	return left;	
}

BinaryTree* BinaryTree::getRight() const{
	return right;	
}


void BinaryTree::inOrderTraversal(BinaryTree * t){
	if (t != NULL){	
		inOrderTraversal(t->getLeft());
		cout << t->getKey() << ", ";
		inOrderTraversal(t->getRight());	
	}
}

BinaryTree* BinaryTree::min(){
	return min(this);
}

BinaryTree* BinaryTree::min(BinaryTree * t) const{
	if (t->getLeft() != NULL){
		return min(t->getLeft());	
	}else{
		return t;
	}
}

BinaryTree* BinaryTree::max(){
	return max(this);	
}

BinaryTree* BinaryTree::max(BinaryTree * t) const{
	if (t->getRight() != NULL){
		return max(t->getRight());	
	}else{
		return t;
	}
}

BinaryTree* BinaryTree::successor(){
	// case 1, the node has a right child
	if (getRight() != NULL){
		return min(getRight());
	}else{ 
		/*  case 2, no right child
			Go up the tree until an ancestor is the left child of its parent
			the parent node is successor	
		*/
		BinaryTree* c = this;
		BinaryTree* p = this->getParent();
		while (p != NULL && c == p->getRight()){
			c = p;
			p = p->getParent();
		}
		return p;
	}
}



BinaryTree* BinaryTree::predecessor(){
	// case 1
	if (getLeft() != NULL){
		return max(getLeft());
	}else{ 
		/*  case 2, no left child
			Go up the tree until an ancestor is the right child of its parent
			the parent node is predecessor	
		*/
		BinaryTree* c = this;
		BinaryTree* p = this->getParent();
		while (p != NULL && c == p->getLeft()){
			c = p;
			p = p->getParent();
		}
		return p;
	}
}



void BinaryTree::setKey(const int & k){
	keyValue = k;
}

void BinaryTree::setParent(BinaryTree* t){
	parent = t;
}

void BinaryTree::setLeft(BinaryTree* t){
	left = t;
}

void BinaryTree::setRight(BinaryTree* t){
	right = t;
}



void BinaryTree::insert(const int & k){
	insert(this, k);	
}

/*
When equal, go left
*/
void BinaryTree::insert(BinaryTree* t, const int & k){
		
	if (k <= t->getKey()){
		if (t->getLeft() == NULL){
			// insert it here
			BinaryTree* l = new BinaryTree(k);
			l->setParent(t);
			t->setLeft(l);
		}else{
			
			insert(t->getLeft(), k);
		}
	}else{
		
		if (t->getRight() == NULL){
			// insert it here
			BinaryTree* r = new BinaryTree(k);
			r->setParent(t);
			t->setRight(r);
		}else{
			insert(t->getRight(), k);
		}
	}
	
	
}

/*
Input: pointer to a node to be removed
*/
void BinaryTree::remove(BinaryTree * t){
	// case 1: leaf node
	// just remove it 
	if (t->getLeft() == NULL && t->getRight() == NULL){
		
		BinaryTree * p = t->getParent();
		if (p->getLeft() == t){
			p->setLeft(NULL);	
		}else{ // if t is the right child of p
			p->setRight(NULL);
		}
		
	}else if (t->getLeft() != NULL && t->getRight() == NULL){
		
		BinaryTree * c = t->getLeft();
		
		if (t->getParent() != NULL){
			
			BinaryTree * p = t->getParent();
			
			c->setParent(p);
			if (c->getKey() <= p->getKey()){
				p->setLeft(c);
			}else{
				p->setRight(c);
			}
		}else{ // edge case where t is the root (with one child)
			c->setParent(NULL);
		}
			
	}else if (t->getLeft() == NULL && t->getRight() != NULL){	
				
		BinaryTree * c = t->getRight();
		
		if (t->getParent() != NULL){
			
			BinaryTree * p = t->getParent();
			
			c->setParent(p);
			//cout << "The single child value " << c->getKey() << endl;
			if (c->getKey() <= p->getKey()){
				p->setLeft(c);
			}else{
				p->setRight(c);
			}
			
		}else{ // edge case where t is the root (with one child)
			// actually not sure what to do in this case lol
			c->setParent(NULL);	

		}
	}else if (t->getLeft() != NULL && t->getRight() != NULL){ // the node to be removed has two children
		/*
		To remove node x, find its succ or pred, y
		Replace x with y
		*/
		
		
		BinaryTree * p = t->getParent();
		BinaryTree * l = t->getLeft();
		BinaryTree * r = t->getRight();
		BinaryTree * s = t->successor();
		
		
		if (s == t->getRight()){ // When the succ is it's immediate child
			
			if (t->getKey() <= p->getKey()){
				// t is the left child of p
				p->setLeft(s);
				
			}else{
				// t is the right child of p
				p->setRight(s);
			}
			s->setLeft(l);
		
		}else{ // proceed as normal I believe
			
			if (t->getKey() <= p->getKey()){
				p->setLeft(s);
			}else{
				p->setRight(s);
			}

			s->setLeft(l);
			s->setRight(r);
		}
		
		s->setParent(p);
	}
	
	delete t;
}

BinaryTree* BinaryTree::search(BinaryTree * t, const int & k){
	if (t == NULL){
		return NULL;
	}
	
	if (t->getKey() == k){
		return t;
	}
	
	if (k <= t->getKey()){
		return search(t->getLeft(), k);
	}else{
		return search(t->getRight(), k);
	}
		
}




	
		
#endif




