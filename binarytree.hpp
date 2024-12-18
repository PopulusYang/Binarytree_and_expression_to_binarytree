/*****************************************************************************************************************
 * @Author: PopulusYang
 * 头文件信息：binarytree.hpp
 * 作用：二叉树类
 * 食用方式：见read.md
*****************************************************************************************************************/
#pragma once

const bool debug = true;//debug开关,当debug为true时输出调试信息

//这里有一些我自己定义的头文件，如果没有可以用替代方案
#ifdef __has_include
#  if __has_include("Status.h")
#     include "Status.h"
#  else
typedef int Status;
#define STATUS
#ifndef OK
#define OK 1
#endif 
#ifndef NOT_OK
#define NOT_OK 0
#endif 
#ifndef ERROR
#define ERROR 0
#endif 
#   endif
#endif

#ifdef __has_include
#  if __has_include("Stack.hpp")
#    include "Stack.hpp"
#  else
#   include<stack>
#  define Stack std::stack
#  define Empty empty
#   endif
#endif


#include <sstream>
#include <iostream>
#include <vector>



template <typename T>
class TreeNode
{
public:
    T data;       // 节点存储的数据(字符类型)
    TreeNode<T> *left;  // 指向左子节点的指针
    TreeNode<T> *right; // 指向右子节点的指针
    TreeNode<T> *parent; // 指向双亲节点的指针
    // 构造函数
    TreeNode(T value) : data(value), left(nullptr), right(nullptr),parent(nullptr) 
    {
        if(debug)
            std::cout << "TreeNode(" << this->data << ") is created" << std::endl;
    }
    //迭代器左移
    inline Status Iterator_left(TreeNode<T> *&current)
    {
        if (this->left == nullptr)
            return ERROR; // 不存在左子树，返回错误
        //向左迭代
        current = this->left;
        return OK;
    }
    // 右移
    inline Status Iterator_right(TreeNode<T> *&current)
    {
        if (this->right == nullptr)
            return ERROR; // 不存在右子树，返回错误
        //向右迭代
        current = this->right;
        return OK;
    }
    inline Status Iterator_parent(TreeNode<T> *&current)
    {
        if (this-> parent == nullptr)
            return ERROR; // 不存在双亲，返回错误
        //向前迭代
        current = this->parent;
        return OK;
    }
};
template <typename T>
class array
{
public:
    TreeNode<T> *current = nullptr; // 当前节点
    array() 
    {
        if(debug)
            std::cout << "array() is created" << std::endl;
    }

    inline Status addNode_left(T data)//添加左节点
    {
        if(current->left == nullptr)
        {
            current->left = new TreeNode<T>(data);
            current->left->parent = current;
            return OK;
        }
        else
        {
            return ERROR;//存在左子树，返回错误
        }
    }


   inline Status addNode_right(T data)
    {
        if(current->right == nullptr)
        {
            current->right = new TreeNode<T>(data);
            current->right->parent = current;
            return OK;
        }
        else
        {
            return ERROR;//存在右子树，返回错误
        }
    }
    inline Status setvalue(T value)
    {
        if(current==nullptr)
            return ERROR;//不存在根节点，返回错误
        current->data = value;
        return OK;
    }
    //左移
    
};
template <typename T>
class BinaryTree : public array<T>
{
private:
    TreeNode<T> *root; // 根节点
    void displayTreeHelper(const TreeNode<T> *node, int level) const
    {
        if (node == nullptr)
            return;
        displayTreeHelper(node->right, level + 1);//递归处理右子树
        // 根据当前节点层次进行缩进，以体现树形结构
        for (int i = 0; i < level; ++i)
            std::cout << "    ";
        // 将节点数据转换为字符串输出
        std::stringstream ss;
        ss << node->data;
        std::cout << ss.str() << std::endl;
        //递归处理左子树
        displayTreeHelper(node->left, level + 1);
    }
public:
    BinaryTree(T value)
    {
        root = new TreeNode<T>(value);
        array<T>::current = root;
        if (debug)
        {
            std::cout << "BinaryTree(" << this->root->data << ") is created" << std::endl;
        }
        
    }
    BinaryTree()
    {
        root = nullptr;
        array<T>::current = root;
        if (debug)
        {
            std::cout << "BinaryTree(" << this->root->data << ") is created" << std::endl;
        }
    }
    BinaryTree(TreeNode<T>* root)
    {
        this->root = root;
        array<T>::current = root;
        if (debug)
        {
            std::cout << "BinaryTree(" << this->root->data << ") is created" << std::endl;
        }
    }
    //重载其他类型另写...
    ~BinaryTree() { Destroy(root); }
    void display() const
    {
        if (debug)
        {
            displayTreeHelper(root, 0);
        }
        else
        {
            std::cout << "Debug is not opened." << std::endl;
        }
    }

    bool empty()
    {
        return root == nullptr;
    }
    inline void Iterator_reset()
    {
        array<T>::current = root;
    }
    void Destroy(TreeNode<T> *root)
    {
        if (root == nullptr)
            return;

        Stack<TreeNode<T> *> nodeStack;
        TreeNode<T>* lastVisited = nullptr;
        TreeNode<T>* current = root;

        while (!nodeStack.Empty() || current != nullptr)
        {
            if (current != nullptr)
            {
                nodeStack.push(current);
                current = current->left; // 向左子树遍历
            }
            else
            {

                TreeNode<T> *peekNode = nodeStack.top();
                // 如果右子树存在且未被访问，则转向右子树
                if (peekNode->right != nullptr && lastVisited != peekNode->right)
                {
                    current = peekNode->right;
                }
                else
                {
                    // 释放节点
                    if(debug)
                        std::cout << "Deleting node with value: " << peekNode->data << std::endl; 
                    nodeStack.pop();
                    delete peekNode;
                    lastVisited = peekNode;
                }
            }
        }
        if (debug)
        {
            std::cout << "BinaryTree is destroyed" << std::endl;
        }
        
    }
    static std::vector<T> preOrder(BinaryTree<T>& tree)//前序遍历，但获得的是该二叉树各节点数据的拷贝值
    {
        TreeNode<T> *root = tree.root;
        std::vector<T> result;
        if (root == nullptr)
            return result;
        Stack<TreeNode<T>*> nodeStack;
        nodeStack.push(root);
        while (!nodeStack.Empty())
        {
            TreeNode<T> *current = nodeStack.top();
            nodeStack.pop();
            result.push_back(current->data);
            if (current->right != nullptr)
                nodeStack.push(current->right);
            if (current->left != nullptr)
                nodeStack.push(current->left);
        }
        return result;
    }

    static std::vector<T> inOrder(BinaryTree<T>& tree)//中序遍历，但获得的是该二叉树各节点数据的拷贝值
    {
        TreeNode<T> *root = tree.root;
        std::vector<T> result;
        if (root == nullptr)
            return result;
        Stack<TreeNode<T> *> nodeStack;
        TreeNode<T> *current = root;
        while (!nodeStack.Empty() || current != nullptr)
        {
            if (current != nullptr)
            {
                nodeStack.push(current);
                current = current->left; // 向左子树遍历，但获得的是该二叉树各节点数据的拷贝值
            }
            else
            {
                TreeNode<T> *peekNode = nodeStack.top();
                nodeStack.pop();
                result.push_back(peekNode->data);
                current = peekNode->right;
            }
        }
        return result;
    }

    static std::vector<T> postOrder(BinaryTree<T>& tree)//后序遍历
    {
        TreeNode<T> *root = tree.root;
        std::vector<T> result;
        if (root == nullptr)
            return result;
        Stack<TreeNode<T> *> nodeStack;
        TreeNode<T> *current = root;
        TreeNode<T> *lastVisited = nullptr;
        while (!nodeStack.Empty() || current != nullptr)
        {
            if (current != nullptr)
            {
                nodeStack.push(current);
                current = current->left; // 向左子树遍历
            }
            else
            {
                TreeNode<T> *peekNode = nodeStack.top();
                // 如果右子树存在且未被访问，则转向右子树
                if (peekNode->right != nullptr && lastVisited != peekNode->right)
                {
                    current = peekNode->right;
                }
                else
                {
                    // 释放节点
                    nodeStack.pop();
                    result.push_back(peekNode->data);
                    lastVisited = peekNode;
                }
            }
        }
        return result;
    }

};
