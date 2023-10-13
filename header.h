//header.h
#ifndef HEADERE_H
#define HEADER_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
enum E{ERROR,OK};
typedef int Status;
typedef int Bool;
typedef char StackElem;
//栈的定义
typedef struct {
    char* pBase;
    char* pTop;
    int size;
} Stack;

/**
*对栈进行初始化
*-init函数对栈做初始化操作，也就是为栈的成员变量赋初值。参
*数pStack是指向栈的指针。如果初始化成功，返回OK；如果失败，返
*回ERROR。在为栈的成员变量pBase和pTop赋初值之前，需要为栈元素分配
*内存空间。
*/
Status init_stack(Stack* pStack);

/**
*释放栈元素的内存
*-free函数释放栈元素的内存。参数pStack是指向栈的指针
*/
void stack_free(Stack *pStack);
/**
*清空栈
*-clear函数把pStack指向的栈中的数据元素清空。要清空栈内的数据元
素，其实并不需要真的把那些数据删除，只要把栈顶指针移到栈底即可。
*/
void stack_clear(Stack *pStack);

/**
*判断栈是否为空
*/
Bool is_empty(Stack* pStack);

/**
*求栈的长度
*/
int stack_length(Stack *pStack);

/**
*取栈顶元素
*-get_top函数读取栈顶元素。参数pStack是栈指针，pElem是数据元素指
*针，读取的栈顶元素存入*pElem 中。如果成功，返回OK；如果失败，返
*回ERROR。这个函数不改变栈顶指针的值。
*/
Status stack_get_top(Stack *pStack,StackElem *pElem);

/**
*入栈
*-push函数把pElem指向的数据元素压入pStack指向的栈。如果成功，返
*回OK；如果失败，返回ERROR。
*/
Status stack_push(Stack *pStack,StackElem *pElem);

/**
*出栈
*-pop函数弹出栈顶元素，pStack是栈指针，弹出的元素存入pElem指向的
*内存中。如果成功，返回OK；如果失败，返回ERROR。
*/
Status stack_pop(Stack *pStack,StackElem *pElem);

/**
*遍历栈
*-traverse函数遍历由pStack所指向的栈，对栈中的每个数据元素执
*行visit操作。如果成功，返回OK；如果失败，返回ERROR。其中visit是
*函数指针，它的参数是数据元素的指针，返回值是Status类型的。
*/
Status stack_traverse(Stack *pStack,Status (*visit)(StackElem*));
#endif