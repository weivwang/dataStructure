#include <stdio.h>
#include <mm_malloc.h>
typedef int ElemType;
#define MaxSize 50
typedef struct stack
{
    ElemType data[MaxSize];
    int top;
} SQstack;

//初始化栈
void InitStack(SQstack *&s)
{
    s = (SQstack *)malloc(sizeof(SQstack));
    s->top = -1;
}

//销毁栈
void DestoryStack(SQstack *&s)
{
    free(s);
}

//判断栈是否为空
bool StackEmpty(SQstack *&s)
{
    return (s->top == -1);
}

//进栈
bool Push(SQstack *&s, ElemType &e)
{
    if (s->top == MaxSize - 1) //栈满
        return false;
    s->top++;
    s->data[s->top] = e;
    return true;
}

//出栈
bool Pop(SQstack *&s, ElemType &e)
{
    if (s->top == -1)
        return false;
    e = s->data[s->top];
    s->top--;
    return true;
}
//取栈顶元素
bool GetTop(SQstack *&s, ElemType e)
{
    if (s->top == -1)
        return false;
    e = s->data[s->top];
    return true;
}

//判断一个字符串是否是对称串
bool symmery(ElemType str[])
{
    int i;
    ElemType e;
    SQstack *st;
    for (int i = 0; str[i] != '\0'; i++)
        Push(st, str[i]);
    for (int i = 0; str[i] != '\0'; i++)
    {
        Pop(st, e);
        if (str[i] != e)
        {
            DestoryStack(st);
            return false;
        }
    }
    DestoryStack(st);
    return true;
}
//简单表达式求值
//将中缀表达式转化为后缀表达式
//exp存放中缀表达式，postexp存放后缀表达式
void trans(char *exp, char postexp[])
{
    char e;
    SQstack *Optr; //定义运算符栈指针
    InitStack(Optr);
    int i = 0; //postexp[]下标
    while (*exp != '\n')
    {
        switch (*exp)
        {
        case '(':
            Push(Optr, *exp);
            exp++;
            break;
        case ')':
            Pop(Optr, *exp);
            while (*exp != ')')
            {
                Pop(Optr, *exp);
                postexp[i++] = e;
            }
            exp++;
            break;
        case '+':
        case '-':
            while (!StackEmpty(Optr))
            {
                GetTop(Optr, e);
                if (e != '(')
                {
                    Pop(Optr, e);
                    postexp[i++] = e;
                }
                else
                    break;
                Push(Optr, *exp);
                exp++;
                break;
            }
        case '*':
        case '/':
            while (!StackEmpty())
            {
                GetTop(Optr, e);
                if (e == '*' || e == '/')
                {
                    Pop(Optr, e);
                    postexp[i++] = e;
                }
                else
                    break;
                Push(Optr, *exp);
                exp++;
                break;
            }
        default:
            while (*exp >= '0' && *exp <= '9')
            {
                postexp[i++] = *exp;
                exp++;
            }
            postexp[i++] = '#';
        }
    }
    while (!StackEmpty(Optr))
    {
        Pop(Optr, e);
        postexp[i++] = e;
    }
    postexp[i] = '\0';
    DestoryStack(Optr);
}