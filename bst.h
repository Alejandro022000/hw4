#include <iostream>
using namespace std;
 
class BST {
    string data;
    BST *left, *right;
 
public:    
    BST();// Default constructor     
    BST(string);// Parameterized constructor    
    BST* Insert(BST*, string);// Insert function
    void Inorder(BST*,ofstream &);// Inorder traversal
    void Preorder(BST*,ofstream &);// Preorder traversal
    void Postorder(BST*,ofstream &);// Postorder traversal
};
 //.
BST ::BST(): data(""), left(nullptr), right(nullptr){} 
BST ::BST(string value){data = value;left = right = NULL;}



BST* BST ::Insert(BST* root, string value){
    if (!root) 
        return new BST(value);
    if (value.size() == (root->data).size())      
        root = Insert(root->right, value);//insert right node depending on str lenghts  
    if (value.size() > (root->data).size())      
        root->right = Insert(root->right, value);//insert right node depending on str lenghts
    else if (value.size() < (root->data).size())
        root->left = Insert(root->left, value);//insert right node depending on str lenghts
    return root;
}
 
void BST ::Inorder(BST* root, ofstream &out){
    if (!root)
        return;
    Inorder(root->left, out);//go to the left of the tree
    //print the node
    cout << root->data << endl;
    out << root->data << endl;
    Inorder(root->right, out);//go to the right of the tree
}
void BST ::Preorder(BST* root, ofstream &out){
    if (!root)
        return;
    //print the node
    cout << root->data <<endl;
    out << root->data <<endl; 
    
    Preorder(root->left, out);//go to the left of the tree     
    Preorder(root->right, out);//go to the right of the tree
}
void BST ::Postorder(BST* root, ofstream &out)
{
    if (!root)
        return;
    Postorder(root->left, out);//go to the left of the tree
    Postorder(root->right, out);//go to the right of the tree
 
    //print the node
    cout << root->data << endl;
    out << root->data <<endl;
}