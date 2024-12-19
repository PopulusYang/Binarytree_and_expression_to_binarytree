/*********************************************************
* @Author: PopulusYang, marasame
* filename: exptobinarytree.hpp
* head needed: binarytree.hpp，
* description: 将表达式转换为二叉树
* 食用方法：见read.md
* updated: 2024/12/19
* content: 
1.对虚数的支持
2.可以将表达式树进行运算（calculate函数）
**********************************************************/

#pragma once
extern const bool debug;
#include "binarytree.hpp"
#include "complex_number.hpp"
#include <type_traits>

const std::string Ins = "(0";

// 用于存储表达式树节点的数据结构
struct exporfu
{
    bool is_complex = false; // 是否为复数
    std::aligned_storage_t<sizeof(Complex), alignof(Complex)> complex_storage;//为复数动态地申请空间
    char fuhao;

    ~exporfu() {
        if (is_complex)
        {
            Complex* complex_ptr = reinterpret_cast<Complex*>(&complex_storage);
            complex_ptr->~Complex();
            if (debug)
            {
                // std::cout << "complex destructed" << std::endl;
            }
        }
    }

    void construct_complex(const Complex num) {
        Complex* complex_ptr = new (&complex_storage) Complex(num);
        is_complex = true;
    }
    Complex& get_complex() {
        return *reinterpret_cast<Complex*>(&complex_storage);
    }
};
std::ostream& operator<<(std::ostream& os, exporfu& exp) 
{
    if (exp.is_complex) 
    {
        Complex* complex_ptr = reinterpret_cast<Complex*>(&exp.complex_storage);//复原
        os << *complex_ptr;
    }
    else 
    {
        os << exp.fuhao;
    }
    return os;
}
std::stringstream& operator<<(std::stringstream& ss, exporfu& exp)
{
    if (exp.is_complex) 
    {
        Complex* complex_ptr = reinterpret_cast<Complex*>(&exp.complex_storage);//复原
        ss << *complex_ptr;
    }
    else 
    {
        ss << exp.fuhao;
    }
    return ss;
}

void std_expression(std::string &expression)
{
    for (std::string::iterator it = expression.begin(); it != expression.end(); ++it)
    {
        if ((*it == '-' || *it == '+') && (it == expression.begin() || *(it - 1) == '+' || *(it - 1) == '-' || *(it - 1) == '*' || *(it - 1) == '/' || *(it - 1) == '(')) // 负号前缀
        {
            if (*(it + 1) == '(')
            {
                // 整体取负
                Stack<char> bracket;
                for (std::string::iterator jt = it + 1; jt != expression.end() + 1; ++jt)
                {
                    if (*jt == '(')
                    {
                        bracket.push('(');
                    }
                    else if (*jt == ')')
                    {
                        bracket.pop();
                        if (bracket.Empty()) // 找到右括号
                        {
                            expression.insert(jt + 1, ')'); // 插入右括号
                        }
                        break;
                    }
                }
                it = expression.insert(it, Ins.begin(), Ins.end()); // 插入(0
                it += 3;                                            // 跳过插入的字符
                continue;
            }
            if (*(it + 1) == '-' || *(it + 1) == '+')
            {
                // 连续负号/正号
                if (*(it) == *(it + 1))
                {
                    expression.erase(it); // 删除中间的符号
                    expression.erase(it);
                    it--; // 回退一步
                    continue;
                }
                else
                {
                    expression.erase(it); // 删除中间的符号
                    expression.erase(it);
                    expression.insert(it, '-'); // 插入0
                    it--;                       // 回退一步
                    continue;
                }
            }
            for (std::string::iterator jt = it + 1; jt != expression.end() + 1; ++jt)
            {
                if (*jt == '+' || *jt == '-' || *jt == '*' || *jt == '/' || jt == expression.end()) // 负号后缀
                {
                    expression.insert(jt, ')'); // 插入右括号
                    break;
                }
            }

            it = expression.insert(it, Ins.begin(), Ins.end()); // 插入(0
            it += 3;                                            // 跳过插入的字符
        }
    }
}
std::string infixToPostfix(std::string exp)
{
    Stack<char> s;
    std::string postfix;
    for (int i = 0; i < exp.length(); i++) // 从左到右扫描
    {
        if (isspace(exp[i]))
            continue; // 忽略空格

        if (isdigit(exp[i]) || exp[i] == '.' || exp[i] == 'i') // 数字
        {
            while (i < exp.length() && (isdigit(exp[i]) || exp[i] == '.'|| exp[i] == 'i'))
            {
                postfix += exp[i];
                i++;
            }
            postfix += ' '; // 使用空格分隔数字
            i--;
        }
        else if (exp[i] == '(') // 左括号
        {
            s.push('(');
        }
        else if (exp[i] == ')') // 右括号
        {
            while (s.top() != '(') // 弹出栈顶运算符直到遇到 '('
            {
                postfix += s.top();
                postfix += ' '; // 使用空格分隔运算符
                s.pop();
            }
            s.pop(); // 弹出 '('
        }
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') // 运算符
        {
            while (!s.Empty() && s.top() != '(' &&
                   (s.top() == '*' || s.top() == '/' ||
                    (s.top() == '+' || s.top() == '-') &&
                        (exp[i] == '+' || exp[i] == '-'))) // 遇到优先级更高的运算符，弹出栈顶运算符直到遇到 '(' 或优先级更低的运算符
            {
                postfix += s.top();
                postfix += ' '; // 使用空格分隔运算符
                s.pop();
            }
            s.push(exp[i]);
        }
    }
    while (!s.Empty()) // 弹出剩余运算符
    {
        postfix += s.top();
        postfix += ' '; // 使用空格分隔运算符
        s.pop();
    }
    return postfix;
}
//将后缀表达式转换成二叉树
BinaryTree<exporfu> PostfixtoBT(const std::string &postfix)
{
    std::stack<TreeNode<exporfu> *> nodeStack;
    size_t i = 0;
    while (i < postfix.size()) 
    {
        if(postfix[i]== ' ')
        {
            i++;
            continue;
        }
        std::string item;
        if (isdigit(postfix[i]) || postfix[i] == '.' ||postfix[i] == 'i') 
        {  // 如果遇到数字或小数点（假设处理浮点数情况，可按需调整），则创建一个节点
            while (i < postfix.size() && (isdigit(postfix[i]) || postfix[i] == '.'|| postfix[i] == 'i')) {
                item += postfix[i];
                i++;
            }
            TreeNode<exporfu> *node = new TreeNode<exporfu>;
            node->data.construct_complex(Complex::strtoComplex(item));
            nodeStack.push(node);
        } else {
            item = postfix[i];  // 将当前运算符字符作为item
            if (nodeStack.size() < 2) 
            {  //错误判断
                std::cerr << "Invalid postfix expression: insufficient operands for operator " << item << std::endl;
                throw std::runtime_error("Invalid postfix expression");
            }
            TreeNode<exporfu> *rightNode = nodeStack.top();
            nodeStack.pop();
            TreeNode<exporfu> *leftNode = nodeStack.top();
            nodeStack.pop();
            TreeNode<exporfu> *operatorNode = new TreeNode<exporfu>;
            operatorNode->data.fuhao = item[0];
            operatorNode->left = leftNode;
            operatorNode->right = rightNode;
            leftNode->parent = operatorNode;
            rightNode->parent = operatorNode;
            nodeStack.push(operatorNode);
            i++; 
        }
    }
    if (nodeStack.size()!= 1)
    {  // 最后检查栈中元素个数
        std::cerr << "Invalid postfix expression: incorrect number of elements remaining in stack" << std::endl;
        throw std::runtime_error("Invalid postfix expression");
    }
    TreeNode<exporfu> *root = nodeStack.top();
    nodeStack.pop();
    BinaryTree<exporfu> res(root);
    return res;  
}

Complex calculate(TreeNode<exporfu>* root)//输入二叉表达式树的头节点，返回计算结果
{
    if (root == nullptr) {
        throw std::invalid_argument("Null node encountered!");
    }
    if (root->left == nullptr && root->right == nullptr) {
        return root->data.get_complex();
    }

    Complex leftvalue = calculate(root->left);
    Complex rightvalue = calculate(root->right);

    if (root->data.fuhao == '+') {
        return leftvalue + rightvalue;
    }
    else if (root->data.fuhao == '-') {
        return leftvalue - rightvalue;
    }
    else if (root->data.fuhao == '*') {
        return leftvalue * rightvalue;
    }
    else if (root->data.fuhao == '/') {
        if (rightvalue.getImaginary() == 0&&rightvalue.getReal() == 0) 
        {
            throw std::invalid_argument("zero error!!!!!!!!!!!!!!!");
        }
        else {
            return leftvalue / rightvalue;
        }
    }

    else {
        throw std::invalid_argument("unknow operator");
    }

}
