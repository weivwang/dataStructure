//注意：只要是需要输出的，就要声明为引用
#include <stdio.h>
#include <mm_malloc.h>
#include <iostream>
#define MaxSize 50
using namespace std;

typedef int ElemType;
typedef struct 
{
    /* data */
    ElemType data[MaxSize];
    int length;
} Sqlist;

//整体建立顺序表，其实就是将 a[] 复制到 L 中，注意这里的 L是数组的头指针
// 可以直接代表数组
void CreateList(Sqlist *&L,ElemType a[],int n) 
{
    L = (Sqlist *)malloc(sizeof(Sqlist));
    for(int i=0;i<n;i++)
        L->data[i] = a[i];
    L->length = n;   
}

//初始化顺序表，其实就是：1，给L分配连续空间； 2，将L的长度置0
void InitList(Sqlist *&L)
{
    L = (Sqlist *)malloc(sizeof(Sqlist));
    L->length = 0;
}

//销毁线性表,就是将L的空间释放
void DestoryList(Sqlist *&L)
{
    free(L);//free()释放了malloc所申请的内存，指针可能变为野指针
    // 最好将指针指向NULL
}

//判断线性表是否为空表,为空则返回值为true，否则为false
bool ListEmpty(Sqlist *L)
{
    return(L->length == 0);
}

//求线性表的长度,个人感觉此方法有点多余，直接用L->length即可，这里写一个函数可能是为了更好的格式化
int ListLength(Sqlist *L)
{
    return(L->length);
}

//输出线性表
void DispList(Sqlist *L)
{
    for(int i=0;i<L->length;i++)
        printf("%c",L->data[i]);
    printf("\n");
}

//求线性表中第i个元素值
bool GetElem(Sqlist *L,int i,ElemType &e)
{
    if(i<1 || i>L->length)
        return false;
    e = L->data[i-1];
    return true;
}

//查找第一个值为e的元素序号
/*
我的思路：
int LocateElem(Sqlist *L;ElemType e)
{
    for(int i=0;i<L->length;i++)
    {
        if(L->data[i] == e)
            return i+1;
    }
    return 0;
}
*/
//教材思路：
int LocateElem(Sqlist *L,ElemType e)
{
    int i=0;
    while(i<L->length && L->data[i] != e)
        i++;
    if(i>=L->length)
        return 0;
    else
        return i+1;
}

//将元素e插入第i个元素
bool ListInsert(Sqlist *&L,int i,int e)
{
    int j;
    if(i<1 || i>L->length)
        return false;
    i--; //第i个元素在data[]中对应的下标为i-1
    for(int j=L->length;j>i;j--)
        L->data[j] = L->data[j-1];//将i之后元素都后移一位
    L->length++;
    L->data[i] = e;
    return true;
}

// 删除第i个元素
bool ListDelete(Sqlist *&L,int i)
{
    int j;
    if(i<1 || i > L->length)
        return false;
    i--;
    for(int j=i;j<L->length;j++)
        L->data[j] = L->data[j+1];
    L->length--;
    return true;
}

//删除线性表中所有值等于x的元素，算法时间复杂度为O(n)
void delnode1(Sqlist *&L,ElemType x)
{
    int k=0,i;
    for(int i=0;i<L->length;i++)
    {
        if(L->data[i] != x)
        {
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
}

//删除线性表中所有值等于x的元素，方法二。时间复杂度同样是O(n)
void delnode2(Sqlist *&L,ElemType x)
{
    int k = 0,i;
    for(int i=0;i<L->length;i++)
    {
        if(L->data[i] == x)
        {
            k++;
        }
        else
        {
            L->data[i-k] = L->data[i];
        }
    }
    L->length -= k;
}

//以第一个元素为基准，让小于等于该基准的元素移到它左边，大于它的元素移到它的右边
void partition1(Sqlist *&L)
{
    int i=0,j=L->length-1;
    ElemType povit = L->data[0];
    while(i<j)
    {
        while(i<j && L->data[j] > povit)
            j--;
        cout<<j<<endl;
        while(i<j && L->data[i] <= povit)
            i++;
        cout<<i<<endl;
        
        if(i<j)
            swap(L->data[i],L->data[j]);
        }
        swap(L->data[0],L->data[i]);

}
//以第一个元素为基准，让小于等于该基准的元素移到它左边，大于它的元素移到它的右边

void partition2(Sqlist *&L)
{
    int i=0,j=L->length-1;
    ElemType povit = L->data[0];
    while(i<j)
    {
        while(i<j && L->data[j] > povit)
            j--;
        L->data[i] = L->data[j];
        while(i<j && L->data[i] <= povit)
            i++;
        L->data[j] = L->data[i];
    }
    L->data[i] = povit;
}
//把所有奇数移到偶数前面
void move1(Sqlist * &L)
{
    int i=0,j=L->length-1;
    while(i<j)
    {
        while(i<j && L->data[j]%2 == 0)
            j--;
        while(i<j && L->data[i]%2 != 0)
            i++;
        if(i<j)
            swap(L->data[i],L->data[j]);
    }
}
void move2(Sqlist *& L)
{
    int i=-1,j;
    for(int j=0;j<=L->length-1;j++)
    {
        if(L->data[j]%2 != 0)
        {
            i++;
            if(i!=j) //测试发现，该条件可有可无
                swap(L->data[i],L->data[j]);
        }
    }
}


int main()
{
    Sqlist *L;
    ElemType a[5] = {3,1,2,5,4};
    CreateList(L,a,5);
    //ListDelete(L,3);
    //delnode1(L,'3');
    //partition2(L);
    move2(L);

    for(int i=0;i<L->length;i++)
        printf("%d ",L->data[i]);
    printf("\n");
}