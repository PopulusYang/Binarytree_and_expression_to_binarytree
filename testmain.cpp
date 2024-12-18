#include "exptobinarytree.hpp"
#include <string>
#include <iostream>


int main()
{
    std::string exp = "-(-1+2)*3";
    std_expression(exp);
    std::cout << exp << std::endl;
    std::cout << infixToPostfix(exp) << std::endl;
    std::string postfixexp = infixToPostfix(exp);
    BinaryTree<std::string> bt = PostfixtoBT(postfixexp);
    bt.display();
    return 0;
}
