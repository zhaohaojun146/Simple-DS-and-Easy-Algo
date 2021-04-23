/*链式存储结构的二叉树，使用栈遍历*/
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10 //栈的最大存储容量

/*二叉树的结点的结构体*/
typedef struct Node {
    char data; //数据域
    struct Node *left_child; //左孩子指针
    struct Node *right_child; //右孩子指针
} TreeNode;

/*栈的结构体*/
typedef struct {
    TreeNode *nodes[MAXSIZE]; //数组中存储二叉树的结点
    int top; //栈顶指针
} Stack;


/**
 * 创造二叉树的结点
 * elem: 结点数据域的值
 */
TreeNode *create_tree_node(char elem)
{
    TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
    new->data = elem;
    new->left_child = NULL;
    new->right_child = NULL;
    return new;
}

/**
 * 创造一个二叉树
 * root: 指向根结点的指针的指针
 */
void create_binary_tree(TreeNode **root)
{
    char elem;
    scanf("%c", &elem);
    if (elem == '#') {
        *root = NULL;
    } else {
        *root = create_tree_node(elem);
        create_binary_tree(&((*root)->left_child));
        create_binary_tree(&((*root)->right_child));
    }
}

/**
 * 初始化栈
 */
void init_stack(Stack *stack)
{
    for (int i = 0; i < MAXSIZE; i++) {
        stack->nodes[i] = NULL;
    }
    stack->top = -1;
}

/**
 * 是否为空栈，1为空栈
 */
int stack_is_empty(Stack *stack)
{
    if (stack->top == -1) {
        return 1;
    }
    return 0;
}

/**
 * 是否为满栈
 */
int stack_is_full(Stack *stack)
{
    if (stack->top == MAXSIZE - 1) {
        return 1;
    }
    return 0;
}

/**
 * 入栈操作，入的是指向二叉树结点的指针
 */
int push(Stack *stack, TreeNode *node)
{
    if (stack_is_full(stack)) {
        printf("栈满，不能再入\n");
        return 0;
    }
    stack->top++;
    stack->nodes[stack->top] = node;
    return 1;
}

/**
 * 出栈操作，出的是指向 指向二叉树结点的指针 的指针
 */
int pop(Stack *stack, TreeNode **node)
{
    if (stack_is_empty(stack)) {
        printf("空栈，无元素可出\n");
        return 0;
    }
    *node = stack->nodes[stack->top];
    stack->top--;
    return 1;
}

/**
 * 读取栈顶元素
 */
void get_top(Stack *stack, TreeNode **node)
{
    if (stack_is_empty(stack)) {
        printf("空栈，无栈顶元素\n");
        return;
    }
    *node = stack->nodes[stack->top];
}

/**
 * 使用栈实现的先序遍历
 */
void preorder_traversal_by_stack(TreeNode *root)
{
    //创造并初始化栈
    Stack stack;
    init_stack(&stack);
    
    TreeNode *curr = root; //辅助指针curr

    while (curr != NULL || !stack_is_empty(&stack)) {
        while (curr != NULL) {
            printf("%c", curr->data); //打印根结点
            push(&stack, curr); //根结点入栈
            curr = curr->left_child; //进入左子树
        }
        if (!stack_is_empty(&stack)) {
            pop(&stack, &curr); //出栈，回到上一个根结点
            curr = curr->right_child; //进入右子树
        }
    }
}

/**
 * 使用栈实现的中序遍历
 */
void inorder_traversal_by_stack(TreeNode *root)
{
    Stack stack;
    init_stack(&stack);
    TreeNode *curr = root;
    while (curr != NULL || !stack_is_empty(&stack)) {
        while (curr != NULL) {
            push(&stack, curr);
            curr = curr->left_child;
        }
        if (!stack_is_empty(&stack)) {
            pop(&stack, &curr);
            printf("%c", curr->data);
            curr = curr->right_child;
        }
    }
}

/**
 * 使用栈实现的后序遍历
 */
void postorder_traversal_by_stack(TreeNode *root)
{
    Stack stack;
    init_stack(&stack);

    TreeNode *curr = root; //辅助指针curr，记录当前访问结点
    TreeNode *prev = NULL; //脚印指针prev，记录上一个访问过的结点

    while (curr != NULL || !stack_is_empty(&stack)) {
        if (curr != NULL) {
            push(&stack, curr); //根结点入栈
            curr = curr->left_child; //进入左子树
        } else {
            get_top(&stack, &curr); //读栈顶元素，不是出栈
            if (curr->right_child != NULL && curr->right_child != prev) { //右子树不为空，且右子树没被遍历
                curr = curr->right_child; //进入右子树
                push(&stack, curr); //根结点入栈
                curr = curr->left_child; //进入左子树
            } else { //右子树已被遍历或者右子树为空，可以打印根结点了
                pop(&stack, &curr); //根结点出栈
                printf("%c", curr->data); //打印根结点
                prev = curr; //记录
                curr = NULL; //置空，进入下一轮循环
            }
        }
    }
}

int main()
{
    /**********************************
    //测试栈的功能
    Stack stack;
    init_stack(&stack);
    push(&stack,create_tree_node('A'));
    TreeNode *node;
    pop(&stack, &node);
    printf("%c\n", node->data);
    ***********************************/

    TreeNode *root = NULL;
    create_binary_tree(&root); //ABD##E##C#F##
    printf("先序遍历为：");
    preorder_traversal_by_stack(root); //ABDECF
    printf("\n");

    printf("中序遍历为：");
    inorder_traversal_by_stack(root); //DBEACF
    printf("\n");

    printf("后序遍历为：");
    postorder_traversal_by_stack(root); //DEBFCA
    printf("\n");

    return 0;
}