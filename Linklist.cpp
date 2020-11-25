#include <stdio.h>
#include <mm_malloc.h>
#include <iostream>
typedef int ElemType;
using namespace std;

typedef struct LNode
{
    ElemType data;      //存放元素值
    struct LNode *next; //指向后继节点
} LinkNode;

/*头插法建立单链表,头插法建  立的单链表，数据域存储的a[]为逆序
a[n]---a[n-1]---.....---a[2]---a[1]
*/
void CreatListF(LinkNode *&L, ElemType a[], int n)
{
    LinkNode *s;
    L = (LinkNode *)malloc(sizeof(LinkNode));
    L->next = NULL;
    for (int i = 0; i < n; i++)
    {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        s->data = a[i];
        L->next = s->next;
        s = L->next;
    }
}

//尾插法建立的单链表为存储的a[]为顺序
void CreatListR(LinkNode *&L, ElemType a[], int n)
{
    LinkNode *s, *r;                          //
    L = (LinkNode *)malloc(sizeof(LinkNode)); //创建头节点
    r = L;                                    //创建尾节点，r始终指向链表的尾部，初始时指向L
    for (int i = 0; i < n; i++)
    {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;
}

//初始化线性表
void InitList(LinkNode *&L)
{
    L = (LinkNode *)malloc(sizeof(LinkNode));
    L->next = NULL;
}

//销毁线性表
void DestroyList(LinkNode *&L)
{
    LinkNode *pre = L, *p = L->next;
    while (p != NULL)
    {
        free(pre);
        pre = p;
        p = pre->next;
    }
}
//判断线性表是否为空表
bool ListEmpty(LinkNode *L)
{
    return (L->next == NULL);
}

//求线性表的长度
int ListLength(LinkNode *L)
{
    int n = 0;
    LinkNode *p = L;
    while (p->next != NULL)
    {
        n++;
        p = p->next;
    }
    return (n);
}
//输出线性表
void DispList(LinkNode *L)
{
    LinkNode *p = L->next;
    while (p != NULL)
    {
        printf("%d", p->data);
        p = p->next;
    }
}
//求线性表某个数据元素值
bool GetElem(LinkNode *L, int i, ElemType &e)
{
    int j = 0;
    LinkNode *p = L;
    if (i < 0)
        return false;
    while (j < i && p->next != NULL)
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
        return false;
    else
    {
        e = p->data;
        return true;
    }
}
//按照元素值查找
int LocateElem(LinkNode *L, ElemType e)
{
    int i = 1;
    LinkNode *p = L->next;
    while (p != NULL && p->data != e)
    {
        p = p->next;
        i++;
    }
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
//插入元素e到第i个位置
bool ListInserrt(LinkNode *L, int i, ElemType e)
{
    int j = 0;
    LinkNode *p = L, *s;
    if (i <= 0)
        return false;
    while (j < i - 1 && p != NULL)
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
    {
        return false;
    }
    else
    {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        s->next = p->next;
        p->next = s;
        s->data = e;
        return true;
    }
}
//删除元素e
bool ListDelete(LinkNode *L, int i, ElemType e)
{
    int j = 0;
    LinkNode *p = L, *q;
    while (j < i - 1 && p != NULL)
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
    {
        return false;
    }
    else
    {
        q = p->next;
        if (q == NULL)
            return false;
        p->next = q->next;
        e = q->data;
        free(q);
        return true;
    }
}
//把一个带头节点带单链表L = (a1,b1,a2,b2.......an,bn)拆分成两个带头节点的单链表L1和L2,其中L1=(a1,a2,a3.....an),L2 = (bn,bn-1......b1)
void spilt(LinkNode *L, LinkNode *L1, LinkNode *L2)
{
    LinkNode *p = L->next, *q, *r1;
    L1 = L;
    r1 = L1;
    L2 = (LinkNode *)malloc(sizeof(LinkNode));
    L2->next = NULL;
    while (p != NULL)
    {
        r1->next = p;
        r1 = p;
        p = p->next;
        q = p->next;
        p->next = L2->next;
        L2->next = p;
        p = q;
    }
    r1->next = NULL;
}
//删除单链表L中元素值的最大节点
void delmaxnode(LinkNode *&L)
{
    LinkNode *p = L->next;
    LinkNode *pre = L;
    LinkNode *maxp = p;
    LinkNode *maxpre = pre;
    while (p != NULL)
    {
        if (maxp->data < p->data)
        {
            maxp = p;
            maxpre = pre;
        }
        p = p->next;
        pre = pre->next;
    }
    maxpre->next = maxp->next;
    free(maxp);
}
//给一个带头节点的单链表按元素递增有序排列
void sort(LinkNode *&L)
{
    LinkNode *p, *pre, *q;
    p = L->next->next;
    L->next->next = NULL;
    while (p != NULL)
    {
        q = p->next;
        pre = L;
        while (pre->next != NULL && pre->next->data < p->data)
            pre = pre->next;
        p->next = pre->next;
    }
}
