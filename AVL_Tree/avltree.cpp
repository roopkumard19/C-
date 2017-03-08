#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

template <class Comparable>
class AvlTree : public BinarySearchTree<Comparable>
{
public:
    AvlTree();
    virtual ~AvlTree();

protected:
    virtual int height(BinaryNode<Comparable> *ptr);
    virtual void insert(const Comparable& data, BinaryNode<Comparable>* &ptr);
    virtual void remove(const Comparable& data, BinaryNode<Comparable>* &ptr);

private:
    BinaryNode<Comparable> *balance(BinaryNode<Comparable> *&ptr);
    BinaryNode<Comparable> *singleRightRotation(BinaryNode<Comparable> *k2);
    BinaryNode<Comparable> *doubleLeftRightRotation(BinaryNode<Comparable> *k3);
    BinaryNode<Comparable> *doubleRightLeftRotation(BinaryNode<Comparable> *k1);
    BinaryNode<Comparable> *singleLeftRotation(BinaryNode<Comparable> *k1);
    int checkBalance(BinaryNode<Comparable> *ptr);
};

/**
 * Default constructor.
 */
template <class Comparable>
AvlTree<Comparable>::AvlTree()
    : BinarySearchTree<Comparable>()
{
}

/**
 * Destructor.
 */
template <class Comparable>
AvlTree<Comparable>::~AvlTree()
{
}

/**
 * Private method to compute the height of a subtree.
 * Overrides the base class method.
 * @param ptr pointer to the root node of the subtree.
 * @return the height of the subtree.
 */
template <class Comparable>
int AvlTree<Comparable>::height(BinaryNode<Comparable> *ptr)
{
    return ptr == nullptr ? -1 : ptr->height;
}

/**
 * Private method to insert a data item into a subtree
 * and set the new root of the subtree.
 * Overrides the base class method.
 * @param data the data to insert.
 * @param ptr the root node of the subtree.
 */
template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable& data, BinaryNode<Comparable>* &ptr)
{
    BinarySearchTree<Comparable>::insert(data, ptr);
    balance(ptr);
}

/**
 * Private method to remove a data item from a subtree
 * and set the new root node of the subtree.
 * Do nothing if the data item is not found.
 * Overrides the base class method.
 * @param data the data to remove.
 * @param ptr the root node of the subtree.
 */
template <class Comparable>
void AvlTree<Comparable>::remove(const Comparable& data, BinaryNode<Comparable>* &ptr)
{
    BinarySearchTree<Comparable>::remove(data, ptr);
    balance(ptr);
}

/**
 * Private method to balance the tree.
 * @param ptr pointer to the node to balance.
 * @return pointer to the balanced node.
 */
template <class Comparable>
BinaryNode<Comparable> *AvlTree<Comparable>::balance(BinaryNode<Comparable> *&ptr)
{
    if (ptr == nullptr) return ptr;

    // Left side too high.
    if (height(ptr->left) - height(ptr->right) > 1)
    {
        if (height(ptr->left->left)
                >= height(ptr->left->right))
        {
            ptr = singleRightRotation(ptr);
            cout << "    --- Single right rotation at node "
                 << ptr->data << endl;
        }
        else
        {
            ptr = doubleLeftRightRotation(ptr);
            cout << "    --- Double left-right rotation at node "
                 << ptr->data << endl;
        }
    }

    // Right side too high.
    else if (height(ptr->right) - height(ptr->left) > 1)
    {
        if (height(ptr->right->right)
                >= height(ptr->right->left))
        {
            ptr = singleLeftRotation(ptr);
            cout << "    --- Single left rotation at node "
                 << ptr->data << endl;
        }
        else
        {
            ptr = doubleRightLeftRotation(ptr);
            cout << "    --- Double right-left rotation at node "
                 << ptr->data << endl;
        }
    }

    // Recompute the node's height.
    ptr->height = (max(height(ptr->left),
                        height(ptr->right)) + 1);

    if (checkBalance(ptr) < 0)
    {
        cout << endl << "***** Tree unbalanced!" << endl;
    }

    return ptr;
}

/**
 * Case 1 (outside left-left): Rebalance with a single right rotation.
 * Update heights and return the new root node.
 * @param k2 pointer to the node to rotate.
 * @return pointer to the new root node.
 */

template <class Comparable>
BinaryNode<Comparable> *AvlTree<Comparable>
    ::singleRightRotation(BinaryNode<Comparable> *k2)
{
	BinaryNode<Comparable> *temp;

	temp = k2->left;
	k2->left=temp->right;
	temp->right=k2;

	k2->height = (k2->height)-1;
	return temp;
}

/**
 * Case 2 (inside left-right): Rebalance with a double left-right rotation.
 * @param k3 pointer to the node to rotate.
 * @return pointer to the new root node.
 */

template <class Comparable>
BinaryNode<Comparable> *AvlTree<Comparable>
    ::doubleLeftRightRotation(BinaryNode<Comparable> *k3)
{
	BinaryNode<Comparable> *temp;

    k3->left=singleLeftRotation(k3->left);
    temp = singleRightRotation(k3);
        return temp;
}

/**
 * Case 3 (inside right-left): Rebalance with a double left rotation.
 * @param k1 pointer to the node to rotate.
 * @return pointer to the new root node.
 */

template <class Comparable>
BinaryNode<Comparable> *AvlTree<Comparable>
    ::doubleRightLeftRotation(BinaryNode<Comparable> *k1)
{
	BinaryNode<Comparable> *temp;

   k1->right=singleRightRotation(k1->right);
   temp= singleLeftRotation(k1);

   return temp;
}

/**
 * Case 4 (outside right-right): Rebalance with a single left rotation.
 * Update heights and return the new root node.
 * @param k2 pointer to the node to rotate.
 * @return pointer to the new root node.
 */

template <class Comparable>
BinaryNode<Comparable> *AvlTree<Comparable>
    ::singleLeftRotation(BinaryNode<Comparable> *k1)
{
	BinaryNode<Comparable> *temp;

	temp = k1->right;
	k1->right=temp->left;
	temp->left=k1;

	k1->height = (k1->height)-1;
	return temp;
}

/**
 * Private method for a paranoid check of whether a tree node is balanced.
 * @param ptr pointer to the node to check.
 * @return the height of the node if balanced, -1 if the node is null,
 *         or -2 if unbalanced.
 */
template <class Comparable>
int AvlTree<Comparable>::checkBalance(BinaryNode<Comparable> *ptr)
{
    if (ptr == nullptr) return -1;

    int leftHeight  = checkBalance(ptr->left);
    int rightHeight = checkBalance(ptr->right);

    if ((abs(height(ptr->left) - height(ptr->right)) > 1)
        || (height(ptr->left)  != leftHeight)
        || (height(ptr->right) != rightHeight))
    {
        return -2;       // unbalanced
    }

    return height(ptr);  // balanced
}

#endif // AVL_TREE_H
