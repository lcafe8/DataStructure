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
Status InitList_Sq(SqList *L)
{
    L->elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L) exit(OVERFLOW);
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return OK;
}
Status ListInsert_Sq(SqList *L,int i,ElemType e)
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
Status ListDelete_Sq(SqList *L,int i,ElemType e)
{
    ElemType *p,*q;
    if(i<1 || i>L->length) return ERROR;
    p=&(L->elem[i-1]);
    e=*p;
	printf("DeleteListNode:\t");
	printf("%d\t%d\n",e.number,e.data);
    q=L->elem+L->length-1;
    for(++p;p<=q;++p)
    {
        *(p-1)=*p;
    }
    --L->length;
    return OK;
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
	ListDelete_Sq(&L,rand()%10,e);
	printf("DeleteList:\n");
	for(k=0;k<L.length;++k)
    {
        printf("\t%d\t%d\n",L.elem[k].number,L.elem[k].data);
    }
}
















