#include <iostream>
#include "TreeNode.h"
#include <fstream>

int main() {
    TreeNode* node = new TreeNode(20); // Allocates a new TreeNode object on the head. Node now points to root of tree.
    TreeNode* left = new TreeNode(10); // Creates two more nodes on the heap. Both have nullptr children
    TreeNode* right = new TreeNode(30);

    node->leftSubtree(left);    // Setter assigns the left pointer inside node to point to the node with value 10
    node->rightSubtree(right);  // Setter assigns the right pointer inside node to point to the node with value 30

    std::cout << "Root: " << node->value() << std::endl;
    std::cout << "Left child: " << node->leftSubtree()->value() << std::endl;
    std::cout << "Right child: " << node->rightSubtree()->value() << std::endl;

    delete left;
    delete right;
    delete node;

    std::ifstream in("input.txt");
    if (!in) {std::cerr << "no file\n"; return 1;}

    for (int i = 0; i < 5; ++i) {
        int next = in.peek();
        if (next == EOF) break;
        std::cout << "peek: " << char(next) << "\n";
        char c = in.get();
        if (c >= 'A' && c <= 'Z') {
            c = c-'A' + 'a';
        }
        std::cout << "get : " << c << "\n";
    }

    TreeNode* root = new TreeNode(5);
    root->leftSubtree(new TreeNode(3));
    root->rightSubtree(new TreeNode(8));
    root->leftSubtree()->leftSubtree(new TreeNode(2));
    root->leftSubtree()->rightSubtree(new TreeNode(4));
    root->rightSubtree()->rightSubtree(new TreeNode(10));

    // Test hasRootToLeafSum
    int target = 10;
    std::cout << "Looking for path sum " << target << "...\n";

    if (root->hasRootToLeafSum(root, target))
        std::cout << "Found a root-to-leaf path with sum = " << target << '\n';
    else
        std::cout << "No path with that sum.\n";


    TreeNode* n30 = new TreeNode(30);
    TreeNode* n31 = new TreeNode(31);
    TreeNode* n32 = new TreeNode(32);
    TreeNode* n34 = new TreeNode(34);
    TreeNode* n35 = new TreeNode(35);
    TreeNode* n39 = new TreeNode(39);
    TreeNode* n41 = new TreeNode(41);
    TreeNode* n54 = new TreeNode(54);
    TreeNode* n55 = new TreeNode(55);
    TreeNode* n56 = new TreeNode(56);
    TreeNode* n67 = new TreeNode(67);
    TreeNode* n72 = new TreeNode(72);
    TreeNode* n75 = new TreeNode(75);
    TreeNode* n79 = new TreeNode(79);
    TreeNode* n117 = new TreeNode(117);
    TreeNode* n120 = new TreeNode(120);

    // Build mini-BST fragments
    n30->right = n31;
    n32->left = n30;
    n32->right = n35;
    n35->left = n34;

    n41->left = n39;
    n79->left = n54;
    n54->right = n56;
    n56->left = n55;
    n56->right = n75;
    n75->left = n67;
    n67->right = n72;

    n120->left = n117;

    // ---- Tests ----
    std::cout << "Predecessor of 32:  " << root->inorderPredecessorValue(n32)  << std::endl;
    std::cout << "Predecessor of 41:  " << root->inorderPredecessorValue(n41)  << std::endl;
    std::cout << "Predecessor of 79:  " << root->inorderPredecessorValue(n79)  << std::endl;
    std::cout << "Predecessor of 120: " << root->inorderPredecessorValue(n120) << std::endl;
    return 0;
}