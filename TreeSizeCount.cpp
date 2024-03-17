#include <bits/stdc++.h>
using namespace std;

typedef struct TreeNode
{
    int val;
    int size;
    int count;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) : val(val), size(1), count(1), left(nullptr), right(nullptr) {}
} TreeNode;

// 中序遍历
void PrintTrees(TreeNode *root)
{
    if (!root)
        return;
    PrintTrees(root->left);
    cout << "val: " << root->val << ", count: " << root->count << ", size: " << root->size << endl;
    PrintTrees(root->right);
}

// void InsertTree(TreeNode *&root, int val)
// {
//     if (!root)
//         root = new TreeNode(val);//上面参数必须是引用，因为这里是修改root变量，而不是root-》成员变量，懂？
//     if (val < root->val)
//     {
//         InsertTree(root->left, val);
//     }
//     else if (val > root->val)
//     {
//         InsertTree(root->right, val);
//     }
//     else
//     {
//         // 有
//         root->count++;
//     }
// }

TreeNode *InsertTree(TreeNode *root, int val)
{
    if (!root)
        return new TreeNode(val);

    if (root->val == val)
        root->count++;
    else if (val < root->val)
    {
        root->left = InsertTree(root->left, val);
    }
    else if (val > root->val)
    {
        root->right = InsertTree(root->right, val);
    }

    // root->size++;
    root->size = root->count + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);
    return root;
}

// 搜索一个元素
TreeNode *SearchByVal(TreeNode *root, int target)
{
    if (!root)
        return nullptr;
    if (target < root->val)
        return SearchByVal(root->left, target);
    else if (target > root->val)
        return SearchByVal(root->right, target);
    // else if (root->val == target)
    return root;
}

TreeNode *getMinTree(TreeNode *root)
{
    while (root->left)
    {
        root = root->left;
    }
    return root;
}

// 删除一个元素
// 返回值null判断是否成功，也有可能一个元素，删除成功也是nullptr
TreeNode *DeleteByval(TreeNode *root, int target)
{
    if (!root)
        return nullptr;

    if (target < root->val)
        root->left = DeleteByval(root->left, target);
    else if (target > root->val)
        root->right = DeleteByval(root->right, target);
    // 删除
    else if (root->count > 1)
    {
        root->count--, root->size--;
    }
    else
    {
        // 1，没有子节点
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            root = nullptr;
        }
        // 2.只有一个子姐点
        else if (root->left != nullptr && root->right == nullptr)
        {
            TreeNode *temp = root->left;
            delete root;
            root = temp;
        }
        else if (root->left == nullptr && root->right != nullptr)
        {
            TreeNode *temp = root->right;
            delete root;
            root = temp;
        }
        // 3.有两个子节点， 找到右子树的最小节点赋值给root，并删除其节点
        else
        {
            // 找到最小节点
            auto m = getMinTree(root->right);
            // delete root;//必须注释，不得删除注释
            root->val = m->val;
            root->count = m->count, root->size--;
            root->right = DeleteByval(root->right, m->val);
        }
    }
    return root;
}

// 查找最大值
TreeNode *SearchMax(TreeNode *root)
{
    if (!root)
        return nullptr;
    while (root->left)
    {
        root = root->left;
    }
    return root;
}

TreeNode *SearchMin(TreeNode *root)
{
    if (!root)
        return nullptr;
    while (root->right)
    {
        root = root->right;
    }
    return root;
}

// 根据val查找排名
// int paiming(TreeNode *root, int target)
// {
//     if (!root)
//         return 0;

//     if (target == root->val)
//         return ((root->left) ? (root->left->size) : 0) + 1;
//     else if (target < root->val)
//         return paiming(root->left, target);
//     return ((root->left) ? (root->left->size) : 0) + root->count + paiming(root->right, target);
// }
int paiming(TreeNode *root, int target)
{
    if (!root)
        return 0;

    if (target == root->val)
    {
        return ((root->left) ? (root->left->size) : 0) + 1; // 这里是+1
    }
    else if (target < root->val)
    {
        return paiming(root->left, target);
    }
    else
    {
        return ((root->left) ? (root->left->size) : 0) + root->count + paiming(root->right, target); // 这里是+root->count很严谨
    }
}

// 查找排名为k的元素
void SearchByOrder(TreeNode *root, int &k, TreeNode *&result)
{
    if (!root)
        return;
    SearchByOrder(root->left, k, result);
    if (--k == 0)
    {
        result = root;
        return;
    }
    SearchByOrder(root->right, k, result);
}

//        Y
//       / \
//      X   C
//     / \
//    A   B
// 右旋
TreeNode *YouXuan(TreeNode *Y)
{
    TreeNode *X = Y->left;
    TreeNode *B = X->right;

    X->right = Y;
    Y->left = B;

    X->size = X->count + ((X->left) ? X->left->val : 0) + ((X->right) ? X->right->val : 0);
    Y->size = Y->count + ((Y->left) ? Y->left->val : 0) + ((Y->right) ? Y->right->val : 0);

    return X;
}

int main()
{
    TreeNode *root = nullptr;
    vector<int> nums{8, 3, 10, 1, 6, 14, 14, 4, 7};
    for (int i = 0; i < nums.size(); i++)
    {
        root = InsertTree(root, nums[i]);
    }
    cout << "zhongxu: " << endl;
    PrintTrees(root);
    cout << "===============================" << endl;

    if (auto result = SearchMax(root))
        cout << "max: " << result->val << endl;
    if (auto result = SearchMin(root))
        cout << "min: " << result->val << endl;

    auto result = paiming(root, 14);
    if (result != -1)
        cout << "paiming: " << result << endl;
    else
        cout << "no paiming" << endl;

    for (int i = 1; i <= 9; i++)
    {
        int k = i; // 这里必须要有中间变量，因为func会改变第二参数的值
        TreeNode *result2 = nullptr;
        SearchByOrder(root, k, result2);
        if (result2)
            cout << "result: " << result2->val << endl;
        else
            cout << "no" << endl;
    }

    // sort(nums.begin(), nums.end());
    // for (int i = 0; i < nums.size(); i++)
    // {
    //     if (auto result = SearchByVal(root, nums[i]))
    //         cout << result->val << " " << result->count << " " << result->size << endl;
    //     else
    //         cout << "not found" << endl;
    // }
    // if (auto result = SearchByVal(root, 123))
    //     cout << result->val << " " << result->count << " " << result->size << endl;
    // else
    //     cout << "not found" << endl;
    // cout << "=================" << endl;

    // if (auto result = DeleteByval(root, 14))
    //     cout << "delete yes" << endl;
    // else
    //     cout << "delete no" << endl;

    // PrintTrees(root);

    // if (auto result = DeleteByval(root, 3))
    //     cout << "delete yes" << endl;
    // else
    //     cout << "delete no" << endl;

    // PrintTrees(root);
}
