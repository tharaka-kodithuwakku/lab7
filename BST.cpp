#include <iostream>
using namespace std;

struct node {
  int key;
  struct node *left, *right;
};

// Inorder traversal
void traverseInOrder(struct node *root) {
  if (root != NULL) {
    traverseInOrder(root->left); // traverse left subtree
    cout << root->key << " "; // print root key
    traverseInOrder(root->right); // traverse right subtree
  }
}

// Insert a node
struct node *insertNode(struct node *node, int key) {
  if (node == NULL) { // if the tree is empty, create a new node
    node = new struct node;
    node->key = key;
    node->left = node->right = NULL;
  }
  else if (key < node->key) { // if the key is smaller than the node's key, insert in the left subtree
    node->left = insertNode(node->left, key);
  }
  else if (key > node->key) { // if the key is larger than the node's key, insert in the right subtree
    node->right = insertNode(node->right, key);
  }
  // if the key is equal to the node's key, do nothing (no duplicates allowed)
  return node;
}

// Find the minimum key in a subtree rooted at a given node
struct node *findMin(struct node *node) {
  if (node == NULL) { // if the tree is empty, return NULL
    return NULL;
  }
  else if (node->left == NULL) { // if the left subtree is empty, return the current node (it is the minimum)
    return node;
  }
  else { // otherwise, go to the left subtree and find the minimum there
    return findMin(node->left);
  }
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
  if (root == NULL) { // if the tree is empty, return NULL
    return NULL;
  }
  else if (key < root->key) { // if the key is smaller than the root's key, delete from the left subtree
    root->left = deleteNode(root->left, key);
  }
  else if (key > root->key) { // if the key is larger than the root's key, delete from the right subtree
    root->right = deleteNode(root->right, key);
  }
  else { // if the key is equal to the root's key, delete the root node
    if (root->left == NULL && root->right == NULL) { // case 1: no children
      delete root; // free the memory
      root = NULL; // set the pointer to NULL
    }
    else if (root->left == NULL) { // case 2: only right child
      struct node *temp = root; // store the current node in a temporary variable
      root = root->right; // make the right child as the new root
      delete temp; // free the memory of the old root
    }
    else if (root->right == NULL) { // case 3: only left child
      struct node *temp = root; // store the current node in a temporary variable
      root = root->left; // make the left child as the new root
      delete temp; // free the memory of the old root
    }
    else { // case 4: two children
      struct node *temp = findMin(root->right); // find the minimum key in the right subtree (the successor of the root)
      root->key = temp->key; // copy the successor's key to the root
      root->right = deleteNode(root->right, temp->key); // delete the successor from the right subtree
    }
  }
  return root;
}

// Driver code
int main() {
  struct node *root = NULL;

  int operation;
  int operand;
  cin >> operation;

  while (operation != -1) {
    switch(operation) {
      case 1: // insert
        cin >> operand;
        root = insertNode(root, operand);
        cin >> operation;
        break;
      case 2: // delete
        cin >> operand;
        root = deleteNode(root, operand);
        cin >> operation;
        break;
      default:
        cout << "Invalid Operator!\n";
        return 0;
    }
  }
  
  traverseInOrder(root);
}