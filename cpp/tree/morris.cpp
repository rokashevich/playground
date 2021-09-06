#include <vector>
/*
          1
        /   \
       2     3
      / \   /
     4   5 6

First, 1 is the root, so initialize 1 as current, 1 has left child which is 2,
the current's left subtree is
         2
        / \
       4   5
So in this subtree, the rightmost node is 5, then make the current(1) as the
right child of 5. Set current = cuurent.left (current = 2). The tree now looks
like:
         2
        / \
       4   5
            \
             1
              \
               3
              /
             6
For current 2, which has left child 4, we can continue with thesame process as
we did above
        4
         \
          2
           \
            5
             \
              1
               \
                3
               /
              6
*/

struct Node {
  int val;
  Node *left;
  Node *right;
  Node() : val(0), left(nullptr), right(nullptr) {}
  Node(int x) : val(x), left(nullptr), right(nullptr) {}
  Node(int x, Node *left, Node *right) : val(x), left(left), right(right) {}
};

std::vector<int> Morris1(Node *root) {
  std::vector<int> nodes;
  while (root) {
    if (root->left) {
      Node *cur = root->left;  //запоминаем левое дерево

      while (cur->right && cur->right != root) {  //спускаемся по правому рукаву
        cur = cur->right;  //левого дерева в самый низ
      }

      if (!cur->right) {  //приклеиваем корень в самый низ правого рукава левой
                          //ветки?
        cur->right = root;
        root = root->left;
      } else {
        cur->right = NULL;
        nodes.push_back(root->val);
        root = root->right;
      }
    } else {
      nodes.push_back(root->val);
      root = root->right;
    }
  }
  return nodes;
}

/* Function to traverse binary tree without recursion and
   without stack */
std::vector<int> Morris2(struct Node *root) {
  std::vector<int> nodes;
  struct Node *cur, *pre;
  cur = root;
  while (cur != NULL) {
    if (cur->left == NULL) {  //нет левого рукава от cur
      nodes.push_back(cur->val);
      cur = cur->right;
    } else {  //левый рукав от cur, ищем предшественника (inorder predecessor)
      pre = cur->left;  //текущего cur - нижний правый рукав этого левого рукава
      while (pre->right != NULL && pre->right != cur) pre = pre->right;

      /* Make current as right child of its inorder predecessor */
      if (pre->right == NULL) {
        pre->right = cur;
        cur = cur->left;
      }

      // MAGIC OF RESTORING the Tree happens here:
      /* Revert the changes made in if part to restore the original
        tree i.e., fix the right child of predecssor */
      else {
        pre->right = NULL;
        nodes.push_back(cur->val);
        cur = cur->right;
      } /* End of if condition pre->right == NULL */
    }   /* End of if condition current->left == NULL*/
  }     /* End of while */
  return nodes;
}