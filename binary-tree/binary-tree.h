#include<stack>

typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
}TreeNode;

//以先序遍历构建二叉树
TreeNode* buildBinaryTree(std::vector<int>& root)
{
    TreeNode* root_node_ = nullptr, *cur_node_ = nullptr;
    std::stack<TreeNode*> stack_;
    for(int i =0; i < root.size(); i++)
    {
        if(root[i] == NULL)
        {
            if(i-1 > 0 && root[i-1] == NULL)
            {
                cur_node_->right = nullptr;
                stack_.pop();
                cur_node_ = stack_.top();
            }else{
                cur_node_->left = nullptr;
            }
        }else{
            TreeNode* node = new TreeNode(root[i]);
            if(root_node_ == nullptr)
            {
                root_node_ = node;
                cur_node_ = node;
                stack_.push(node);
            }else{
                //while(cur_node_->left && cur_node_->right)
                while(cur_node_->right)
                {
                    stack_.pop();
                    cur_node_ = stack_.top();
                }
                if(cur_node_->left || root[i-1] == NULL)
                {
                    cur_node_->right = node;
                    cur_node_ = node;
                    stack_.push(node);
                }else{
                    cur_node_->left = node;
                    cur_node_ = node;
                    stack_.push(node);                   
                }
                // while(cur_node_->left && cur_node_->right)
                // {
                //     stack_.pop();
                //     cur_node_ = stack_.top();
                // }
                // if(i > 1 && root[i-1] == NULL)
                // {
                //     cur_node_->right = node;
                //     cur_node_ = node;
                //     stack_.push(node);
                // }else{
                //     cur_node_->left = node;
                //     cur_node_ = node;
                //     stack_.push(node);
                // }
            }
        }
    }
    return root_node_;
}

