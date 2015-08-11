#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INEEASTBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int Status;
typedef struct
{
    char *name;
    int number;
    int data;
}ElemType;
typedef struct
{
    ElemType *elem;//存储空间基址
    int length;//当前长度
    int listsize;//当前分配容量
}SqList;

Status InitList_Sq(SqList *L)//初始化L
{
    L->elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L) exit(OVERFLOW);
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return OK;
}
Status DestroyList(SqList *L)//销毁线性表
{
    while(L->length>0)
    {
        free(L->elem);
        --L->length;
    }
    free(L);
    return OK;
}

Status ClearList(SqList *L)//清空线性表
{
    if(0 == ListEmpty(L))
    {
        L->length=0;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int ListLength(SqList L)//顺序表L长度
{
    return L.length;
}

Status ListEmpty(SqList L)//判断L是否为空
{
    if(0 == L.length)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

ElemType GetElem(SqList L,int i)//返回L中的第i个元素
{
    if(i<1 || i>L.length) return;
    return (L.elem[i-1]);
}

int LocateElem(SqList L,ElemType e)//返回L中第一个与e元素相同的位置
{
    int i=0;
    for(i=0;i<L.length;++i)
    {
        if(e.number==L.elem[i].number && e.data==L.elem[i].data)
        {
           return i+1;
        }
    }
    return 0;
}

ElemType PriorElem(SqList L,ElemType cur_e)//返回L中cur_e元素的前驱
{
    if(LocateElem(L,cur_e)<=1) return;
    return L.elem[LocateElem(L,cur_e)-2];
}

ElemType NextElem(SqList L,ElemType cur_e)//返回L中cur_e元素的后继
{
    if(LocateElem(L,cur_e)<=0 || LocateElem(L,cur_e)>=L.length) return;
    return L.elem[LocateElem(L,cur_e)];
}

Status ListInsert_Sq(SqList *L,int i,ElemType e)//向顺序表L插入数据
{
    ElemType *p,*q;
    if(i<1 || i>L->length+1)return ERROR;
    if(L->length>L->listsize)
    {
        ElemType *newbase=(ElemType*)realloc(L->elem,(L->listsize+LIST_INIT_SIZE)*sizeof(ElemType));
        if(!newbase) exit(OVERFLOW);
        L->elem=newbase;
        L->listsize+=LISTINCREMENT;
    }
    q=&(L->elem[i-1]);
    for(p=&(L->elem[L->length-1]);p>=q;--p)
    {
        *(p+1)=*p;
    }
    *q=e;
    ++L->length;
    return OK;
}

Status ListDelete_Sq(SqList *L,int i,ElemType e)//删除数据
{
    ElemType *p,*q;
    if(i<1 || i>L->length) return ERROR;
    p=&(L->elem[i-1]);
    e=*p;
	printf("DeleteNode:\t");
	printf("%d\t%d\n",e.number,e.data);
    q=L->elem+L->length-1;
    for(++p;p<=q;++p)
    {
        *(p-1)=*p;
    }
    --L->length;
    return OK;
}

Status ListTraverse(SqList *L, int (*visit)(ElemType e))
{
   int i, ret;
   for (i = 0; i < L->length; ++i)
   {
       ret = visit(L->elem[i]);
       if (ret != 0)
        return ret;
   }
   return ERROR;
}

int main()
{
    srand((int) time(0));
    SqList L;
    ElemType e;
    int k=0;
    InitList_Sq(&L);
    for(k=0;k<10;k++)
    {
        e.number=k;
        e.data=rand()%100;
        ListInsert_Sq(&L,k+1,e);
    }
	printf("InitListNode:\n");
    for(k=0;k<L.length;++k)
    {
        printf("\t%d\t%d\n",L.elem[k].number,L.elem[k].data);
    }
    printf("ListLength：%d\n",ListLength(L));
	ListDelete_Sq(&L,rand()%10,e);
	printf("DeleteListNode:\n");
	for(k=0;k<L.length;++k)
    {
        printf("\t%d\t%d\n",L.elem[k].number,L.elem[k].data);
    }
    DestroyList(&L);
    printf("DestroyList:\n");
    for(k=0;k<L.length;++k)
    {
        printf("\t%d\t%d\n",L.elem[k].number,L.elem[k].data);
    }
}
















