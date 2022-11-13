#include <iostream>
using namespace std;
 
class BST {
    string data;
    BST *left, *right;
 
public:
    // Default constructor.
    BST();
 
    // Parameterized constructor.
    BST(string);
 
    // Insert function.
    BST* Insert(BST*, string);
 
    // Inorder traversal.
    void Inorder(BST*,ofstream &);

    void Preorder(BST*,ofstream &);

    void Postorder(BST*,ofstream &);
};
 
// Default Constructor definition.
BST ::BST()
    : data("")
    , left(NULL)
    , right(NULL)
{
}
 
// Parameterized Constructor definition.
BST ::BST(string value)
{
    data = value;
    left = right = NULL;
}
 
// Insert function definition.
BST* BST ::Insert(BST* root, string value)
{
    if (!root) {
        return new BST(value);
    }
 
    // Insert data.
    if (value.size() > (root->data).size()) {
        // Insert right node data, if the 'value'
        // to be inserted is greater than 'root' node data.
 
        // Process right nodes.
        root->right = Insert(root->right, value);
    }
    else if (value.size() < (root->data).size()){
        // Insert left node data, if the 'value'
        // to be inserted is smaller than 'root' node data.
 
        // Process left nodes.
        root->left = Insert(root->left, value);
    }
 
    // Return 'root' node, after insertion.
    return root;
}
 
// Inorder traversal function.
// This gives data in sorted order.
void BST ::Inorder(BST* root, ofstream &out)
{
    if (!root) {
        return;
    }
    Inorder(root->left, out);
    cout << root->data << endl;
    out << root->data << endl;
    Inorder(root->right, out);
}
void BST ::Preorder(BST* root, ofstream &out){
    if (!root){
        return;
    }
    /* first print data of node */
    cout << root->data <<endl;
    out << root->data <<endl;
 
    /* then recur on left subtree */
    Preorder(root->left, out);
 
    /* now recur on right subtree */
    Preorder(root->right, out);
}
void BST ::Postorder(BST* root, ofstream &out)
{
    if (!root)
        return;
    // first recur on left subtree
    Postorder(root->left, out);
 
    // then recur on right subtree
    Postorder(root->right, out);
 
    // now deal with the node
    cout << root->data << endl;
    out << root->data <<endl;
}