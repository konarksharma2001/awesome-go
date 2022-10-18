#include <bits/stdc++.h>
using namespace std;

class Node
{

public:
    int data;
    Node *left;
    Node *right;

    Node(int data)
    {

        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

Node *buildTree(Node *root)
{

    int data;
    cout << " Enter Data: " << endl;
    cin >> data;
    root = new Node(data);

    if (data == -1)
        return NULL;

    cout << "Enter Data for Inserting in left of " << data << endl;
    root->left = buildTree(root->left);

    cout << "Enter Data for Inserting in right of " << data << endl;
    root->right = buildTree(root->right);

    return root;
}

void levelOrderTraversal(Node *root)
{

    if (root == NULL)
        return;
    queue<Node *> q;
    q.push(root);
    q.push(NULL); // Separator

    while (!q.empty())
    {

        Node *temp = q.front();
        q.pop();

        if (temp == NULL)
        {
            cout << endl; // Adding Separator
            if (!q.empty())
                // Queue still has some child nodes
                q.push(NULL);
        }

        else
        {

            cout << " " << temp->data << " ";
            if (temp->left != NULL)
                q.push(temp->left);
            if (temp->right != NULL)
                q.push(temp->right);
        }
    }
}

class Solution
{
public:
    // Approach 1 : Brute force
    // T.C. -> O(N log(N)) + O(N)
    // S.C. -> O(N)
    /*
    void inorder(Node *root, vector<int> &ans)
    {

        if (root == NULL)
            return;
        // L N R : left root right

        inorder(root->left, ans);
        ans.push_back(root->data);
        inorder(root->right, ans);
    }

    int kthSmallest(Node *root, int k)
    {
        vector<int> ans;
        inorder(root, ans);
        sort(ans.begin(), ans.end());
        return ans[k - 1];
    }
    */

    // Optimal Approach
    // T.C. -> O(N)
    // S.C. -> O(H)
    Node *solve(Node *root, int &k)
    {

        if (root == NULL)
            return NULL;
        Node *left = solve(root->left, k);
        if (left != NULL)
            return left;
        k--;
        if (k == 0)
            return root;
        return solve(root->right, k);
    }

    int kthSmallest(Node *root, int k)
    {
        Node *ans = solve(root, k);
        return ans->data;
    }
};

int main()
{

    Node *root = NULL;

    // Creating a Binary Search Tree
    // 8 5 4 -1 -1 7 6 -1 -1 -1 12 10 -1 -1 14 13 -1 -1 -1
    //            8
    //          /   \
    //         /     \
    //        /       \
    //       /         \
    //      5          12
    //     /  \        / \
    //    /    \      /   \
    //   4      7    10    14
    //         /           /
    //        /           /
    //       6            13
    //

    root = buildTree(root);

    cout << "\n The  BST is: " << endl;
    levelOrderTraversal(root);

    Solution obj;
    int k = 3;
    int ans = obj.kthSmallest(root, k);
    cout << "\n The " << k << " smallest element in the BST is " << ans << endl;

    return 0;
}
