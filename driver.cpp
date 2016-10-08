

#include "binary_tree.h"

int main(){
	
	int size = 7;
	int a [size] = {5, 10, 7, 1, 3, 1, 8}; 
	//int * a = new int[4];
	for (int i = 0; i < size; i++){
	//	a[i] = i;
	}
	BinaryTree* t  = new BinaryTree(a, size);
	t->insert(t, 22);
	
	cout << "Min " << t->min(t)->getKey() << endl;
	cout <<"Max " << t->max(t)->getKey() << endl;
	
	//BinaryTree * seven =  t->successor();
	cout << "Succ should be 7 " << t->successor()->getKey() << endl;
	cout << "Pred should be 3 " << t->predecessor()->getKey() << endl;
	
	/*
	t->inOrderTraversal(t);	
	t->remove(t->max(t));
	cout << "Removed leaf 22 " << endl;
	t->inOrderTraversal(t);
	*/
	
	/*
	cout << "Remove the 7 " << endl;
	t->remove(t->successor());
	t->inOrderTraversal(t);
	*/	
	//t->insert(t, 11);\
	
	t->inOrderTraversal(t);
	cout << "removing 10 " << endl;
	
	t->remove(t->getRight());
	t->inOrderTraversal(t);
	
}


