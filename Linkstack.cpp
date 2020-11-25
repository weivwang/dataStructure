#include <stdio.h>
#include <mm_malloc.h>
typedef char Elemtype;

//节点类型
typedef struct linknode
{
    Elemtype data;
    struct linknode *next;
};

void InitStack(linknode *&s)
{
    s = (linknode *)malloc(sizeof(linknode));
    s->next = NULL;
}

//销毁栈
void DestoryStack(linknode *&s)
{
    linknode *pre = s;
    linknode *p = s->next;
    while (p != NULL)
    {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
}

//判断栈空
bool SatckEmpty(linknode *&s)
{
    return (s->next == NULL);
}

//进栈

void Push(linknode *&s, Elemtype e)
{
    linknode *p;
    p = (linknode *)malloc(sizeof(linknode));
    p->data = e;
    p->next = s->next;
    s->next = p;
}

//出栈
bool Pop(linknode *&s, Elemtype &e)
{
    linknode *p;
    if (s->next = NULL)
        return false;
    p = s->next;
    e = p->data;
    s->next = p->next;
    free(p);
    return true;
}

//取栈顶元素
bool GetTop(linknode *&s, Elemtype e)
{
    linknode *p;
    if (s->next == NULL)
        return false;
    p = s->next;
    e = p->data;
    return true;
}

//匹配左右括号是否配对
bool Match(char a[], int n)
{
    int i = 0;
    char e;
    bool match = true;
    linknode *s;
    InitStack(s);
    while (i < n && match)
    {
        if (a[i] == '(')
            Push(s, a[i]);
        else if (a[i] = ')')
        {
            if (GetTop(s, e) == true)
            {
                if (e != ')')
                    match = false;
                else
                    Pop(s, e);
            }
            else
            {
                match = false;
            }
        }
        i++;
    }
    if (!SatckEmpty(s))
        match = false;
    DestoryStack(s);
    return match;
}
//简单表达式求值
//将中缀表达式转化为后缀表达式
