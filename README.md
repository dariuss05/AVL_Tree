# AVL_Tree (only insertion and traversals)

In computer science, an AVL tree (named after inventors **A**delson-**V**elsky and **L**andis) is a self-balancing binary search tree (BST). It was the first such data structure to be invented. In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property. Lookup, insertion, and deletion all take O(log n) time in both the average and worst cases, where {\displaystyle n}n is the number of nodes in the tree prior to the operation. Insertions and deletions may require the tree to be rebalanced by one or more tree rotations.

*Insertion*  
When inserting a node into an AVL tree, you initially follow the same process as inserting into a Binary Search Tree. If the tree is empty, then the node is inserted as the root of the tree. If the tree is not empty, then we go down the root, and recursively go down the tree searching for the location to insert the new node. This traversal is guided by the comparison function. In this case, the node always replaces a NULL reference (left or right) of an external node in the tree i.e., the node is either made a left-child or a right-child of the external node.

After this insertion if a tree becomes unbalanced, only ancestors of the newly inserted node are unbalanced. This is because only those nodes have their sub-trees altered. So it is necessary to check each of the node's ancestors for consistency with the invariants of AVL trees: this is called "retracing". This is achieved by considering the balance factor of each node.

*Traversal*  
As a read-only operation the traversal of an AVL tree functions the same way as on any other binary tree. Exploring all n nodes of the tree visits each link exactly twice: one downward visit to enter the subtree rooted by that node, another visit upward to leave that node's subtree after having explored it.

*Rebalancing*  
If during a modifying operation the height difference between two child subtrees changes, this may, as long as it is < 2, be reflected by an adaption of the balance information at the parent. During insert and delete operations a (temporary) height difference of 2 may arise, which means that the parent subtree has to be "rebalanced". The given repair tools are the so-called tree rotations, because they move the keys only "vertically", so that the ("horizontal") in-order sequence of the keys is fully preserved (which is essential for a binary-search tree).

There are four possible variants of the violation:

Right Right	⟹ Z is a *right	child* of its parent X and BalanceFactor(Z) ≥ 0  
Left Left	⟹ Z is a *left	child* of its parent X and BalanceFactor(Z) ≤ 0  
Right Left	⟹ Z is a *right	child* of its parent X and BalanceFactor(Z) < 0  
Left Right	⟹ Z is a *left	child* of its parent X and BalanceFactor(Z) > 0  


*Time complexity in big O Notation*

| Algorithm | Average | Worst Case |
| :-------: | :-----: | :--------: |
| Space     | Θ(n)    | O(n)       |
| Search    | Θ(log n)| O(log n)   |
| Insert    | Θ(log n)| O(log n)   |

*Graphic way of inserting and rebalancing an AVL Tree*

![AVL Tree, Insertion](https://upload.wikimedia.org/wikipedia/commons/f/fd/AVL_Tree_Example.gif)