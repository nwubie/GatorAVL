# GatorAVL

Constructed a custom self-balancing AVL tree used to organize UF student accounts based on GatorIDs.

## Commands
**insert NAME ID:** *Add a Student object into the tree with the specified name, NAME and GatorID number*\
**remove ID:** *Find and remove the account with the specified ID from the tree*\
**search ID:** *Search for the student with the specified ID from the tree*\
**search NAME:** *Search for the student with the specified name, NAME in the tree*\
**printInorder:** *Print out a comma separated inorder traversal of the names in the tree*\
**printPreorder:** *Print out a comma separated preorder traversal of the names in the tree*\
**printPostorder:** *Print out a comma separated postorder traversal of the names in the tree*\
**printLevelCount:** *Prints the number of levels that exist in the tree*\
**removeInorder N:** *Remove the Nth GatorID from the inorder traversal of the tree (N = 0 for the first item, etc)*

## Sample Input/Output
**Input:**\
8\
insert "Brandon" 45679999\
insert "Brian" 35459999\
insert "Briana" 87879999\
insert "Bella" 95469999\
printInorder\
remove 45679999\
removeInorder 2\
printInorder

**Output:**\
successful\
successful\
successful\
successful\
Brian, Brandon, Briana, Bella\
successful\
successful\
Brian, Briana
