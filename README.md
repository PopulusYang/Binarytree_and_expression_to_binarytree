# 《二叉树类模板与表达式处理函数使用说明文档》

## 说明

本代码实现了一个二叉树类模板，以及一些四则运算相关函数的实现。

## 目录

- [说明](#说明)
- [二叉树类模板](#二叉树类模板)
  - [概述](#概述)
  - [类模板介绍](#类模板介绍)
    - [TreeNode 类模板](#treenode-类模板)
    - [array 类模板](#array-类模板)
    - [BinaryTree 类模板](#binarytree-类模板)
  - [全局变量](#全局变量)
  - [使用示例](#使用示例)
- [表达式处理](#表达式处理)
  - [std_expression 函数](#std_expression-函数)
  - [infixToPostfix 函数](#infixtopostfix-函数)
  - [PostfixtoBT 函数](#postfixtobt-函数)
    - [食用栗子](#食用栗子)
- [表达式运算](#表达式运算)
  - [复数类](#复数类)
  - [calculate 函数](#运算表达式calculate-函数)

## 二叉树类模板

### 概述

本代码实现了一个二叉树数据结构，包含节点类 `TreeNode`、辅助类 `array` 以及二叉树类 `BinaryTree`。二叉树中的每个节点存储特定类型的数据，并具有指向左右子节点和双亲节点的指针。提供了多种操作二叉树的方法，如添加节点、遍历二叉树等，同时还具备调试信息输出功能，可通过全局变量 `debug` 控制。

### 类模板介绍

#### `TreeNode` 类模板

- **功能**：表示二叉树的节点。
- **数据成员**：
  - `data`：存储节点的数据，类型为模板参数 `T`。
  - `left`：指向左子节点的指针，类型为 `TreeNode<T>`。
  - `right`：指向右子节点的指针，类型为 `TreeNode<T>`。
  - `parent`：指向双亲节点的指针，类型为 `TreeNode<T>`。
- **成员函数**：
  - `TreeNode(T value)`：构造函数，接受一个 `T` 类型的值来初始化节点数据，并在调试模式下输出节点创建信息。
  - `Iterator_left(TreeNode<T> *&current)`：将当前指针 `current` 移动到左子节点（若存在），若左子节点不存在则返回 `ERROR`，否则返回 `OK`。
  - `Iterator_right(TreeNode<T> *&current)`：将当前指针 `current` 移动到右子节点（若存在），若右子节点不存在则返回 `ERROR`，否则返回 `OK`。
  - `Iterator_parent(TreeNode<T> *&current)`：将当前指针 `current` 移动到双亲节点（若存在），若双亲节点不存在则返回 `ERROR`，否则返回 `OK`。

#### `array` 类模板

- **功能**：提供一些与二叉树节点操作相关的辅助功能。
- **数据成员**：
  - `current`：指向当前节点的指针，类型为 `TreeNode<T>`，初始化为 `nullptr`。
- **成员函数**：
  - `array()`：构造函数，在调试模式下输出自身创建信息。
  - `addNode_left(T data)`：尝试在当前节点添加左子节点，若当前节点左子节点为空，则创建新的 `TreeNode` 并将其作为左子节点，同时设置双亲指针，成功返回 `OK`，若左子节点已存在则返回 `ERROR`。
  - `addNode_right(T data)`：尝试在当前节点添加右子节点，若当前节点右子节点为空，则创建新的 `TreeNode` 并将其作为右子节点，同时设置双亲指针，成功返回 `OK`，若右子节点已存在则返回 `ERROR`。
  - `setvalue(T value)`：若当前节点不为空，则设置当前节点的数据值为传入的 `value`，成功返回 `OK`，若当前节点为空则返回 `ERROR`。

#### `BinaryTree` 类模板

- **功能**：表示整个二叉树结构，继承自 `array<T>` 类。
- **数据成员**：
  - `root`：指向二叉树根节点的指针，类型为 `TreeNode<T>`。
- **成员函数**：
  - `BinaryTree(T value = 0)`：构造函数，创建根节点并将其数据初始化为传入的值（默认为 0），同时将 `array<T>` 中的 `current` 指针指向根节点，并在调试模式下输出二叉树创建信息。
  - `~BinaryTree()`：析构函数，调用 `Destroy` 函数释放二叉树的所有节点，并在调试模式下输出二叉树销毁信息。
  - `Iterator_reset()`：将 `array<T>` 中的 `current` 指针重置为根节点。
  - `Destroy(TreeNode<T> *root)`：递归地释放二叉树节点内存。通过栈辅助实现非递归的后序遍历释放节点。从根节点开始，先将当前节点及其左子树节点依次压入栈，当左子树遍历完后，处理右子树，最后释放当前节点。
  - `static std::vector<T> preOrder(BinaryTree<T>& tree)`：静态成员函数，实现二叉树的前序遍历。返回一个包含二叉树所有节点数据的 `std::vector`，遍历顺序为根节点、左子树、右子树。使用栈来辅助实现非递归遍历，先将根节点压入栈，然后循环弹出栈顶节点，将其数据加入结果向量，再依次将右子节点和左子节点压入栈（若存在）。
  - `static std::vector<T> inOrder(BinaryTree<T>& tree)`：静态成员函数，实现二叉树的中序遍历。返回一个包含二叉树所有节点数据的 `std::vector`，遍历顺序为左子树、根节点、右子树。使用栈来辅助实现非递归遍历，从根节点开始，先将当前节点及其左子树节点依次压入栈，当左子树遍历完后，弹出栈顶节点（即当前节点），将其数据加入结果向量，然后转向右子树继续遍历。
  - `static std::vector<T> postOrder(BinaryTree<T>& tree)`：静态成员函数，实现二叉树的后序遍历。返回一个包含二叉树所有节点数据的 `std::vector`，遍历顺序为左子树、右子树、根节点。使用栈和一个标记节点来辅助实现非递归遍历，从根节点开始，先将当前节点及其左子树节点依次压入栈，当左子树遍历完后，若右子树存在且未被访问，则转向右子树，否则弹出栈顶节点，将其数据加入结果向量，并标记该节点已访问。

### 全局变量

- `debug`：布尔类型，用于控制是否输出调试信息。当 `debug` 为 `true` 时，在节点创建、二叉树创建、节点销毁等操作时会输出相应的调试信息。

### 使用示例

以下是一个简单的使用示例，展示如何创建二叉树、添加节点以及进行遍历：

```cpp
#include "binarytree.hpp"

int main()
{
    // 创建一个二叉树，根节点数据为 1
    BinaryTree<int> tree(1);

    // 在根节点添加左子节点，数据为 2
    tree.addNode_left(2);
    // 在根节点添加右子节点，数据为 3
    tree.addNode_right(3);

    // 将当前指针移动到根节点的左子节点
    tree.current->Iterator_left(tree.current);
    // 在当前节点（即根节点的左子节点）添加左子节点，数据为 4
    tree.addNode_left(4);
    // 在当前节点添加右子节点，数据为 5
    tree.addNode_right(5);

    // 将当前指针移动回根节点
    tree.current->Iterator_parent(tree.current);
    // 将当前指针移动到根节点的右子节点
    tree.current->Iterator_right(tree.current);
    // 在当前节点（即根节点的右子节点）添加左子节点，数据为 6
    tree.addNode_left(6);
    // 在当前节点添加右子节点，数据为 7
    tree.addNode_right(7);

    // 前序遍历二叉树并输出节点数据
    std::vector<int> preorderResult = BinaryTree<int>::preOrder(tree);
    std::cout << "Preorder traversal: ";
    for (int i : preorderResult)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}
```

- 在上述示例中，首先创建了一个根节点数据为 1 的二叉树，然后逐步添加子节点构建二叉树结构，最后分别进行了前序遍历并输出结果。通过修改 `debug` 变量的值，可以控制是否输出调试信息，以便在开发和调试过程中观察二叉树的创建、销毁以及节点操作的过程。

- 注意：在实际使用中，应确保根据需要正确处理模板参数 `T` 的类型，以及合理地管理二叉树的内存，避免出现内存泄漏或悬空指针等问题。同时，代码中的 `Stack` 类模板未给出完整定义，如果在使用过程中出现与 `Stack` 相关的问题，需要进一步检查和完善 `Stack` 类模板的实现。

## 表达式处理

以下是对上述代码中几个主要函数的使用说明：

### `std_expression` 函数

- **功能**：对输入的数学表达式字符串进行标准化处理，主要处理负号相关的特殊情况，包括负号前缀（如 `-3` 可能转换为 `(0-3)`）、连续正负号（如 `--3` 转换为 `3`，`+-3` 转换为 `(0-3)`）以及负号后缀（如 `3-` 转换为 `3-(0)`）等情况，使表达式在后续处理中更规范统一。
- **参数**：
  - `expression`：输入输出参数，传入需要处理的原始数学表达式字符串，在函数内部会对其进行修改，将其中的负号相关情况按照规则转换，处理完成后该字符串即为标准化后的表达式。
- **示例用法**：

```cpp
std::string expr = "3-(-5+2)*3";
std_expression(expr);
// 此时 expr 被修改为 "3-(0-(5+2))*3"
```

### `infixToPostfix` 函数

- **功能**：将中缀表达式转换为后缀表达式。中缀表达式是常见的数学表达式书写形式（如 `3 + 4 * 2`），而后缀表达式将运算符放在操作数之后（如 `3 4 2 * +`），这种形式在构建二叉树等后续处理中更方便。该函数按照运算符优先级以及括号规则进行转换，遇到数字直接输出到后缀表达式字符串，遇到运算符则根据栈中已有运算符的优先级决定是否入栈或弹出已有运算符到后缀表达式字符串。
- **参数**：
  - `exp`：输入参数，需要转换的中缀表达式字符串。
- **返回值**：
  - 返回转换后的后缀表达式字符串，其中数字和运算符之间用空格分隔，方便后续处理时按空格分割提取信息。
- **示例用法**：

```cpp
std::string infix = "3*(4+2)/5";
std::string postfix = infixToPostfix(infix);
// 此时 postfix 的值为 "3 4 2 + * 5 / "
```

### `PostfixtoBT` 函数

#### 一、函数功能

`PostfixtoBT` 函数的主要功能是将给定的后缀表达式转换为二叉树结构。它通过扫描后缀表达式字符串，依据不同的字符类型（数字或运算符）进行相应的操作，从而构建出完整的二叉树。在扫描过程中，遇到数字时创建包含该数字的二叉树节点并压入栈中，遇到运算符时从栈中弹出两个节点作为左右子节点构建新节点，最后栈中剩余的唯一节点即为二叉树的根节点。

#### 二、函数参数

- `postfix`：这是一个 `std::string` 类型的输入参数，表示需要转换为二叉树的后缀表达式字符串。此字符串要求数字和运算符之间用空格分隔，并且与 `infixToPostfix` 函数返回的后缀表达式格式保持一致，以确保函数能够正确解析。例如：`"3 4 + 2 *"` 就是一个符合要求的后缀表达式字符串示例。

#### 三、函数返回值

函数返回一个 `BinaryTree<exporfu>` 类型的对象。其中，`BinaryTree` 是自定义的二叉树模板类，`exporfu` 是一个自定义结构体，用于存储二叉树节点的数据。该结构体能够存储复数信息（如果节点表示复数）或运算符信息。返回的 `BinaryTree<exporfu>` 对象即为构建好的二叉树结构，其内部节点数据类型为 `exporfu`，可以存储数字或运算符等信息，以便后续对二叉树进行遍历、求值等操作。

#### 四、示例用法

以下是 `PostfixtoBT` 函数的示例用法：

```cpp
std::string postfixExpr = "3 4 + 2 *";
BinaryTree<exporfu> tree = PostfixtoBT(postfixExpr);
// 此时 tree 即为构建好的二叉树，可以通过 tree 的相关成员函数（如 display 函数，如果已定义）来查看二叉树结构或进行其他操作
```

在实际应用中，通常会与其他相关函数配合使用。一般先调用 `std_expression` 函数对原始中缀表达式进行标准化处理，然后将处理后的表达式传入 `infixToPostfix` 函数得到后缀表达式，最后将后缀表达式传入 `PostfixtoBT` 函数构建二叉树，这样就完成了从原始数学表达式到二叉树结构的转换过程。例如：

```cpp
try {
    std::string expr = "3*(4+2)/5";
    std_expression(expr);
    std::string postfix = infixToPostfix(expr);
    BinaryTree<exporfu> tree = PostfixtoBT(postfix);
    // 若上述过程无异常，则继续进行其他操作，如查看二叉树结构
    tree.display(); 
} catch (const std::runtime_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

#### 五、函数内部实现细节

1. **初始化**：
   - 首先创建一个 `std::stack<TreeNode<exporfu> *>` 类型的栈 `nodeStack`，用于存储二叉树节点的指针。
   - 定义一个索引变量 `i`，并初始化为 `0`，用于遍历后缀表达式字符串 `postfix`。
2. **扫描后缀表达式字符串**：
   - 进入一个循环，只要 `i` 小于 `postfix` 的长度，就持续进行以下操作。
   - 如果当前字符 `postfix[i]` 是空格，说明遇到了分隔符，直接将索引 `i` 加 `1`，并跳过本次循环的后续操作，继续下一个字符的检查。
   - 如果当前字符是数字（包括小数点和 `i`，假设考虑复数和浮点数情况），则执行以下步骤：
     - 进入一个内层循环，只要 `i` 小于 `postfix` 的长度且当前字符是数字、小数点或 `i`，就将当前字符添加到字符串 `item` 中，并将 `i` 加 `1`。这样可以完整地提取出一个数字或复数的字符串表示。
     - 创建一个新的 `TreeNode<exporfu>` 节点 `node`。
     - 通过调用 `node->data.construct_complex(Complex::strtoComplex(item))`，将提取的字符串转换为复数并存储在节点的数据部分（如果是数字则会被正确转换为复数形式存储）。
     - 将新创建的节点 `node` 压入 `nodeStack` 栈中。
   - 如果当前字符是运算符：
     - 将当前运算符字符作为 `item`。
     - 首先进行错误判断，如果 `nodeStack` 栈中的元素个数小于 `2`，说明没有足够的操作数来执行该运算符操作，此时输出错误信息：`Invalid postfix expression: insufficient operands for operator <当前运算符>`，并抛出 `std::runtime_error` 异常，表示后缀表达式无效。
     - 如果栈中元素足够，则从栈顶弹出两个节点，分别作为右子节点 `rightNode` 和左子节点 `leftNode`。
     - 创建一个新的 `TreeNode<exporfu>` 节点 `operatorNode`，将当前运算符存储在其数据部分的 `fuhao` 成员变量中。
     - 设置 `operatorNode` 的左右子节点分别为 `leftNode` 和 `rightNode`，并同时设置左右子节点的父节点为 `operatorNode`。
     - 将新创建的 `operatorNode` 压入 `nodeStack` 栈中，并将索引 `i` 加 `1`，继续下一个字符的处理。
3. **检查结果**：
   - 当扫描完整个后缀表达式字符串后，检查 `nodeStack` 栈中元素的个数。如果栈中元素个数不等于 `1`，说明后缀表达式存在错误，可能是运算符和操作数数量不匹配等问题，此时输出错误信息：`Invalid postfix expression: incorrect number of elements remaining in stack`，并抛出 `std::runtime_error` 异常，表示后缀表达式无效。
4. **构建并返回二叉树**：
   - 如果栈中元素个数为 `1`，则将栈顶节点作为二叉树的根节点 `root`，并从栈中弹出。
   - 使用根节点 `root` 创建一个 `BinaryTree<exporfu>` 对象 `res`，并将其作为函数的返回值返回，完成二叉树的构建和返回操作。

通过以上详细的步骤，`PostfixtoBT` 函数能够准确地将符合要求的后缀表达式转换为二叉树结构，在表达式处理和二叉树相关应用场景中发挥重要作用。同时，通过对各种错误情况的检测和处理，保证了函数在面对非法输入时能够及时报错并抛出异常，提高了程序的健壮性。

### 食用栗子

以下是一个使用上述函数将数学表达式转换为二叉树的完整示例，示例中的表达式为 `3*(4+2)/5`，下面展示逐步转换的过程：

### 1. 原始表达式

首先有一个中缀表达式 `-(-3+2)/2+3`。

### 2. 标准化表达式（调用 `std_expression` 函数）

```cpp
#include <iostream>
#include <string>
#include "exptobinarytree.hpp"

int main() {
    std::string expression = "-(-3+2)/2+3";
    std_expression(expression);
    std::cout << "After std_expression: " << expression << std::endl;
    return 0;
}
```

- 运行结果：`After std_expression:(0-((0-3)+2))/2+3`

### 3. 中缀表达式转后缀表达式（调用 `infixToPostfix` 函数）

```cpp
#include <iostream>
#include <string>
#include "exptobinarytree.hpp"

int main() {
    std::string expression = "-(-3+2)/2+3";
    std_expression(expression);
    std::string postfix = infixToPostfix(expression);
    std::cout << "After infixToPostfix: " << postfix << std::endl;
    return 0;
}
```

在 `infixToPostfix` 函数中，按照运算符优先级以及括号规则进行转换，扫描中缀表达式，数字直接输出到后缀表达式字符串，运算符根据栈内已有运算符优先级决定入栈或弹出已有运算符到后缀表达式字符串。对于表达式 `-(-3+2)/2+3`，转换后的后缀表达式为 `0 0 3 - 2 + - 2 / 3 +` （数字和运算符之间用空格分隔）。

### 4. 后缀表达式转二叉树（调用 `PostfixtoBT` 函数）

```cpp
#include <iostream>
#include <string>
#include "exptobinarytree.hpp"

int main() {
    std::string expression = "3*(4+2)/5";
    std_expression(expression);
    std::string postfix = infixToPostfix(expression);
    try {
        BinaryTree<std::string> tree = PostfixtoBT(postfix);
    } catch (const std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
```

`PostfixtoBT` 函数扫描后缀表达式字符串 `0 0 3 - 2 + - 2 / 3 +`，遇到数字就创建包含该数字的二叉树节点并压入栈中，遇到运算符则从栈中弹出两个节点作为左右子节点，创建包含该运算符的新节点，构建好子树关系后将新节点压入栈中。最后栈中剩下的唯一节点就是二叉树的根节点，以此构建出完整的二叉树结构，代表了原表达式 `-(-3+2)/2+3` 的运算逻辑关系。

整个流程总结起来就是：先对原始中缀表达式（如果有需要）进行标准化处理，接着将其转换为后缀表达式，最后再把后缀表达式转换为二叉树，这样就完成了从表达式到二叉树的转换过程。后续如果有相关功能函数实现（比如基于二叉树进行表达式求值等），就可以继续基于构建好的二叉树做进一步操作了。

注意，在实际运行代码时，如果表达式格式不符合函数要求（比如括号不匹配、后缀表达式中运算符和操作数数量关系不对等情况），`infixToPostfix` 函数和 `PostfixtoBT` 函数会输出错误信息并抛出异常，所以在调用这些函数时，建议像示例中那样使用 `try-catch` 块来捕获异常并进行相应的错误处理，保证程序的稳定性。

- 以下是一种使用文本形式将上述从表达式转换为二叉树的过程可视化呈现的方式，我们依旧以表达式 `-(-3+2)/2+3` 为例：

### 1. 原始中缀表达式

```cmd
-(-3+2)/2+3
```

#### 一、原始中缀表达式分析

给定表达式 `-(-3+2)/2+3`，这是一个典型的中缀表达式，其中包含了加法、减法、除法运算以及括号来确定运算的优先级。从运算顺序来看，先计算括号内的表达式，即 `-3+2`，其结果为 `-1`，然后再处理外面的负号，得到 `1`。整个表达式的运算顺序较为复杂，尤其是多重负号的存在，使得在计算机处理时需要进行标准化处理，以明确运算的具体步骤和逻辑。

#### 二、标准化表达式

在标准化过程中，为了清晰地展现每一步运算所遵循的数学规则，我们引入 `0` 来表示负号所蕴含的减法运算。对于表达式中的 `-(-3+2)`，可以将其逐步转化为 `0 - (0 - 3 + 2)`。具体而言，把最外层的负号看作是 `0` 减去括号内的式子，而括号内的 `-3` 又可表示为 `0 - 3`。这样，原表达式 `-(-3+2)/2+3` 就标准化为 `(0-((0-3)+2))/2+3`。

以下是标准化表达式的树状结构示意（以括号体现层次关系）：

```cmd
        (+)
      /    \
    (/)      (3)
  /   \
(-)     (2)
  /   \
(0)    (-)
      /   \
    (0)    (+)
          /   \
        (-3)    (2)
```

#### 三、中缀表达式转后缀表达式

标准化后的中缀表达式 `(0-(0-3+2))/2+3` 转换为后缀表达式的过程如下：

首先，扫描表达式，遇到数字时将其输出到后缀表达式中，遇到运算符时，根据其优先级以及栈的状态进行处理。

1. 遇到 `0`，输出到后缀表达式，此时后缀表达式为 `0`。
2. 遇到 `-`，将其压入栈中，栈内元素为 `[-]`。
3. 遇到 `0`，输出到后缀表达式，此时后缀表达式为 `0 0`。
4. 遇到 `-`，因为其与栈顶 `-` 优先级相同，将其压入栈中，栈内元素为 `[-,-]`。
5. 遇到 `3`，输出到后缀表达式，此时后缀表达式为 `0 0 3`。
6. 遇到 `+`，因为 `+` 优先级低于栈顶 `-`，将 `-` 弹出并输出到后缀表达式，然后将 `+` 压入栈中，此时后缀表达式为 `0 0 3 -`，栈内元素为 `[+]`。
7. 遇到 `2`，输出到后缀表达式，此时后缀表达式为 `0 0 3 - 2`。
8. 遇到 `)`，将栈内元素 `+` 弹出并输出到后缀表达式，此时后缀表达式为 `0 0 3 - 2 +`。
9. 遇到 `-`，将其压入栈中，栈内元素为 `[-]`。
10. 遇到 `)`，将栈内元素 `-` 弹出并输出到后缀表达式，此时后缀表达式为 `0 0 3 - 2 + -`。
11. 遇到 `/`，将其压入栈中，栈内元素为 `[/]`。
12. 遇到 `2`，输出到后缀表达式，此时后缀表达式为 `0 0 3 - 2 + - 2`。
13. 遇到 `+`，因为 `+` 优先级低于栈顶 `/`，将 `/` 弹出并输出到后缀表达式，然后将 `+` 压入栈中，此时后缀表达式为 `0 0 3 - 2 + - 2 /`，栈内元素为 `[+]`。
14. 遇到 `3`，输出到后缀表达式，此时后缀表达式为 `0 0 3 - 2 + - 2 / 3`。
15. 扫描结束，将栈内剩余元素 `+` 弹出并输出到后缀表达式，最终得到的后缀表达式为 `0 0 3 - 2 + - 2 / 3 +`。

#### 四、后缀表达式转二叉树

以下以表格形式展示每一步扫描后缀表达式以及栈和二叉树构建的情况（`nodeStack` 表示节点栈，`操作` 列表示当前扫描到后缀表达式的元素后进行的操作，`二叉树结构示意（简略）` 列用简单的括号形式表示当前二叉树大概的结构）：

| 扫描位置 | 后缀表达式元素 | nodeStack（栈内节点情况，从栈底到栈顶） |
|:----:|:----:|:----:|
| 开始 | `0 0 3 - 2 + - 2 / 3 +` | `空` |
| 1 | `0` | `[TreeNode("0")]` |
| 2 | `0` | `[TreeNode("0"), TreeNode("0")]` |
| 3 | `3` | `[TreeNode("0"), TreeNode("0"), TreeNode("3")]` |
| 4 | `-` | `[TreeNode("0"), TreeNode("(0 - 3)")]` |
| 5 | `2` | `[TreeNode("0"), TreeNode("(0 - 3)"), TreeNode("2")]` |
| 6 | `+` | `[TreeNode("0"), TreeNode("((0 - 3) + 2)")]` |
| 7 | `-` | `[TreeNode("(0 - ((0 - 3) + 2))")]` |
| 8 | `2` | `[TreeNode("(0 - ((0 - 3) + 2))"), TreeNode("2")]` |
| 9 | `/` | `[TreeNode("((0 - ((0 - 3) + 2)) / 2)")]` |
| 10 | `3` | `[TreeNode("((0 - ((0 - 3) + 2)) / 2)"), TreeNode("3")]` |
| 11 | `+` | `[TreeNode("(((0 - ((0 - 3) + 2)) / 2) + 3)")]` |

最终构建好的二叉树可视化结构如下：

```cmd
                    (+)
                  /    \
                (/)      (3)
              /    \
            (-)      (2)
          /   \
        (0)    (-)
              /   \
            (0)    (+)
                  /   \
                (-3)    (2)
```

## 表达式运算

### 复数类

以下是一份关于上述`complex_number.hpp`中定义的复数类的使用说明

### 一、引言

`complex_number.hpp`头文件中定义了一个功能丰富的复数类`Complex`，它封装了复数的基本属性（实部和虚部），并通过重载运算符以及提供实用的静态方法，方便在C++程序中对复数进行各种操作以及和字符串之间的转换，同时还重载了输出流运算符便于直观展示复数结果。以下将详细介绍其使用方法。

### 二、类的基本结构与成员

#### （一）成员变量

- `real`（`double`类型）：代表复数的实部，在构造函数中可进行初始化，默认初始值为 `0.0`。例如创建一个复数对象时，若不指定实部的值，其实部就会默认为 `0`。
- `imaginary`（`double`类型）：代表复数的虚部，同样在构造函数中初始化，默认初始值是 `0.0`。

#### （二）构造函数

`Complex(double r = 0.0, double i = 0.0)`：这是类的构造函数，用于创建复数对象。通过传入两个参数（分别对应实部和虚部）来初始化一个复数。示例如下：

```cpp
// 创建一个实部为3.0，虚部为4.0的复数对象
Complex complex1(3.0, 4.0); 
// 创建一个实部和虚部都为0的复数对象（默认构造）
Complex complex2; 
```

#### （三）访问函数

- `double getReal() const`：该成员函数用于获取复数对象的实部数值，返回值类型为 `double`。例如：

```cpp
Complex complex(5.0, 3.0);
double realValue = complex.getReal(); // 此时realValue的值为5.0
```

- `double getImaginary() const`：用于获取复数对象的虚部数值，同样返回 `double` 类型的值。例如：

```cpp
Complex complex(5.0, 3.0);
double imaginaryValue = complex.getImaginary(); // imaginaryValue的值为3.0
```

### 三、运算符重载的使用

#### （一）加法运算符重载（`operator+`）

`Complex operator+(const Complex& other) const`：通过重载加法运算符，使得两个`Complex`类对象可以直接使用 `+` 运算符进行相加操作，返回结果是一个新的复数对象，其实部和虚部分别为两个相加复数对应实部和虚部之和。示例：

```cpp
Complex complex1(2.0, 3.0);
Complex complex2(1.0, 1.0);
Complex sum = complex1 + complex2; // sum的实部为3.0（2.0 + 1.0），虚部为4.0（3.0 + 1.0）
```

#### （二）减法运算符重载（`operator-`）

`Complex operator-(const Complex& other) const`：重载减法运算符后，允许使用 `-` 运算符对两个复数对象做减法运算，返回值是一个表示相减结果的新复数对象，其实部和虚部分别是被减数与减数的实部、虚部之差。例如：

```cpp
Complex complex1(5.0, 4.0);
Complex complex2(2.0, 1.0);
Complex difference = complex1 - complex2; // difference实部为3.0（5.0 - 2.0），虚部为3.0（4.0 - 1.0）
```

#### （三）乘法运算符重载（`operator*`）

`Complex operator*(const Complex& other) const`：实现了复数乘法的逻辑，按照复数乘法的数学规则（即 `(a + bi) * (c + di) = (ac - bd) + (ad + bc)i`）进行计算，返回相乘后的复数对象。例如：

```cpp
Complex complex1(2.0, 3.0);
Complex complex2(1.0, 2.0);
Complex product = complex1 * complex2; 
// 计算过程：(2 + 3i) * (1 + 2i) = 2 + 4i + 3i + 6i^2 = -4 + 7i，所以product实部为 -4.0，虚部为7.0
```

#### （四）除法运算符重载（`operator/`）

`Complex operator/(const Complex& other) const`：支持复数的除法运算，依据复数除法的数学原理（通过将分子分母同时乘以分母的共轭复数来化简）进行计算，返回相除后的复数对象。示例：

```cpp
Complex complex1(4.0, 6.0);
Complex complex2(2.0, 1.0);
Complex quotient = complex1 / complex2; 
// 按照复数除法规则计算后，quotient实部约为2.8，虚部约为1.6（具体计算过程略）
```

### 四、字符串转换函数（`strtoComplex`）

`static Complex strtoComplex(std::string str)`：这是一个静态成员函数，用于将一个表示复数的字符串转换为`Complex`类的对象。它能够处理多种格式的字符串输入情况：

- **只有实部的情况**：例如输入字符串 `"3"`，函数会解析并创建一个实部为 `3.0`，虚部为 `0.0` 的复数对象。
- **只有虚部的情况**：如果输入 `"4i"`，会转换得到实部为 `0.0`，虚部为 `4.0` 的复数对象；特别地，若输入字符串为 `"i"`，则虚部视为 `1.0`，即转换为实部 `0.0`、虚部 `1.0` 的复数对象。
- **既有实部又有虚部的情况**：像 `"2+3i"` 或者 `"3i+2"` 这类格式的字符串，函数都能正确解析出实部和虚部的值，并创建对应的复数对象。以下是使用示例：

```cpp
std::string str1 = "3+4i";
Complex complexFromStr1 = Complex::strtoComplex(str1); // 得到实部为3.0，虚部为4.0的复数对象

std::string str2 = "5i";
Complex complexFromStr2 = Complex::strtoComplex(str2); // 得到实部为0.0，虚部为5.0的复数对象
```

### 五、输出流运算符重载（`operator<<`）

`std::ostream& operator<<(std::ostream& os, const Complex& c)`：通过重载输出流运算符 `<<`，使得可以方便地将复数对象输出到标准输出流（例如 `std::cout`）或者其他符合 `std::ostream` 类型的流对象中。输出格式会根据复数的实部和虚部具体情况进行调整：

- **实部和虚部都为0的情况**：直接输出 `0`。
- **只有实部不为0的情况**：只输出实部的值。
- **虚部不为0的情况**：若实部也不为 `0`，则按照 `实部 + 虚部i` 的格式输出（并且当虚部为正数时，前面会加上 `+` 号）。示例如下：

```cpp
Complex complex1(3.0, 4.0);
std::cout << complex1 << std::endl; // 输出：3+4i

Complex complex2(5.0, 0.0);
std::cout << complex2 << std::endl; // 输出：5

Complex complex3(0.0, 0.0);
std::cout << complex3 << std::endl; // 输出：0
```

### 运算表达式：`calculate` 函数

以下是对 `Complex calculate(TreeNode<exporfu>* root)` 函数的详细说明：

### 一、函数功能概述

该函数的主要功能是对给定的二叉表达式树（以 `TreeNode<exporfu>*` 类型的节点作为树结构的基本组成单元）进行遍历和计算，最终返回该二叉表达式树所表示的表达式的计算结果，结果以 `Complex` 类型（复数类型）返回，意味着此函数可用于处理包含复数运算的表达式求值场景。

### 二、函数参数说明

`TreeNode<exporfu>* root`：这是函数唯一的输入参数，代表二叉表达式树的根节点指针。通过这个根节点，可以递归地访问整棵二叉表达式树的各个节点，进而解析并计算出表达式的值。需要确保传入的根节点指针是有效的，如果传入 `nullptr`，函数将会抛出 `std::invalid_argument` 类型的异常，表示遇到了空节点的错误情况。

### 三、函数内部逻辑说明

#### （一）空节点检查

函数首先会对传入的根节点 `root` 进行检查，如果 `root` 为 `nullptr`，意味着传入了空的二叉表达式树，这不符合正常的计算前提，此时函数会抛出 `std::invalid_argument` 类型的异常，并给出相应提示信息 `"Null node encountered!"`，告知调用者出现了空节点的错误情况。

#### （二）叶子节点处理（即操作数情况）

如果根节点的左子节点 `root->left` 和右子节点 `root->right` 都为 `nullptr`，这表明当前节点是叶子节点，也就是表达式中的操作数（在此处应为复数类型的操作数）。此时，函数通过调用 `root->data.get_complex()` 获取叶子节点所存储的复数数据，并直接返回该复数，作为递归计算的最基础部分。

#### （三）非叶子节点处理（即运算符情况）

当节点不是叶子节点时，意味着当前节点存储的是运算符，需要先递归地计算其左右子树所代表的子表达式的值，然后根据当前节点存储的运算符进行相应的运算。具体如下：

- **递归计算左右子树的值**：
通过 `Complex leftvalue = calculate(root->left);` 和 `Complex rightvalue = calculate(root->right);` 这两条语句，分别以递归的方式计算当前节点的左子树和右子树所表示表达式的值，并将结果存储在 `leftvalue` 和 `rightvalue` 这两个 `Complex` 类型的变量中。
- **根据运算符进行相应运算**：
  - **加法运算（`+` 运算符）**：如果当前节点存储的运算符是 `'+'`，则将左子树计算得到的复数 `leftvalue` 和右子树计算得到的复数 `rightvalue` 通过调用 `Complex` 类重载的加法运算符（`leftvalue + rightvalue`）进行相加运算，并返回相加后的结果作为当前子表达式的计算值。
  - **减法运算（`-` 运算符）**：若当前节点的运算符为 `'-'`，则使用 `Complex` 类重载的减法运算符，执行 `leftvalue - rightvalue` 操作，返回相减后的结果作为当前子表达式的计算值。
  - **乘法运算（`*` 运算符）**：当运算符是 `'*'` 时，调用 `Complex` 类重载的乘法运算符，执行 `leftvalue * rightvalue` 运算，将乘法运算的结果返回作为当前子表达式的计算值。
  - **除法运算（`/` 运算符）**：对于除法运算，首先会检查右子树计算得到的复数 `rightvalue`，如果其虚部 `rightvalue.getImaginary()` 和实部 `rightvalue.getReal()` 都为 `0`，意味着出现了除数为 `0` 的情况，这在数学运算中是不允许的。此时函数会抛出 `std::invalid_argument` 类型的异常，并给出提示信息 `"zero error!!!!!!!!!!!!!!!"`，告知调用者出现了除数为 `0` 的错误。若右子树的值不为 `0`，则通过调用 `Complex` 类重载的除法运算符 `leftvalue / rightvalue` 进行除法运算，并返回相除后的结果作为当前子表达式的计算值。
  - **其他未知运算符处理**：如果当前节点存储的运算符不属于上述 `+`、`-`、`*`、`/` 这几种常见的运算符，函数会抛出 `std::invalid_argument` 类型的异常，并提示 `"unknow operator"`，表明遇到了不认识的运算符。

### 四、函数返回值说明

函数最终返回一个 `Complex` 类型的值，这个值代表了对整个二叉表达式树所表示的表达式进行计算后得到的结果。如果在计算过程中没有出现上述提到的异常情况（如空节点、除数为 `0`、未知运算符等），返回的 `Complex` 值就是按照二叉表达式树所定义的表达式运算逻辑计算得出的正确结果。

### 五、使用例子、

以下是 `calculate` 函数的使用例子：

```cpp
#include "exptobinarytree.hpp"
#include <string>
#include <iostream>


int main()
{
    std::string exp = "-(-3+2)/2+3";
    std_expression(exp);
    std::cout << exp << std::endl;
    std::cout << infixToPostfix(exp) << std::endl;
    std::string postfixexp = infixToPostfix(exp);
    BinaryTree<exporfu> bt = PostfixtoBT(postfixexp);
    bt.display();
    std::cout << exp << '=' << calculate(bt.current) << std::endl;
    return 0;
}
```

输出结果：`(0-(5+3i))*(2+4i)=2-26i`
