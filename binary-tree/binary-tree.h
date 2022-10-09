#include<stack>
#include<queue>

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
                if(!stack_.empty())
                {
                    cur_node_ = stack_.top();
                }else{
                    return root_node_;
                }
                
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

//以先序遍历构建二叉树
TreeNode* buildBinaryTreeByLevelOrder(std::vector<int>& root)
{
    std::queue<TreeNode*>queue_;
    TreeNode* root_ = new TreeNode(root[0]);
    queue_.push(root_);
    int idx = 1;
    while(!queue_.empty() && idx < root.size())
    {
        int level_size_ = queue_.size();
        for(int i = 0; i < level_size_; i++)
        {
            TreeNode* node = queue_.front();
            queue_.pop();
            if(root[idx] != NULL)
            {
                TreeNode* new_node_ = new TreeNode(root[idx]);
                node->left = new_node_;
                queue_.push(new_node_);
            }
            idx++;
            if(root[idx] != NULL)
            {
                TreeNode* new_node_ = new TreeNode(root[idx]);
                node->right = new_node_;
                queue_.push(new_node_);
            }
            idx++;
        }
    }
    return root_;
}

void printBinaryTreeByLevelOrder(TreeNode* root)
{
    std::queue<TreeNode*>queue_;
    queue_.push(root);
    std::vector<int>root_;
    while(!queue_.empty())
    {
        int cur_level_size_ = queue_.size();
        for(int i = 0; i < cur_level_size_; i++)
        {
            TreeNode* root = queue_.front();
            queue_.pop();
            if(!root){ 
                root_.push_back(INT_MIN);
                continue;
            }
            root_.push_back(root->val);
            if(root->left){
                queue_.push(root->left);
            }else{
                queue_.push(nullptr);
            }
            if(root->right){
                queue_.push(root->right);
            }else{
                queue_.push(nullptr);
            }
        }
    }
    std::cout << "[" ;
    for(int i =0; i < root_.size()-1; i++)
    {
        if(root_[i] == INT_MIN)
        {
            std::cout << "null,";
        }else{
            std::cout << root_[i] << ",";
        }
    }
    std::cout << root_[root_.size()-1] << "]" << std::endl;
}