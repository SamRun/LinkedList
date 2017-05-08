#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node;
typedef struct Node *LinkList; /* 定义LinkList */


/* 初始化顺序线性表 */
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
	if (!(*L)) /* 存储分配失败 */
	{
		return ERROR;
	}
	(*L)->next = NULL; /* 指针域为空 */

	return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{
	LinkList p, q;
	p = (*L)->next;           /*  p指向第一个结点 */
	while (p)                /*  没到表尾 */
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;        /* 头结点指针域为空 */
	return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next; /* p指向第一个结点 */
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

Status visit(ElemType c)
{
	printf("-> %d ", c);
	return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
Status GetElem(LinkList L, int i, ElemType *e)
{
	int j;
	LinkList p;		/* 声明一结点p */
	p = L->next;		/* 让p指向链表L的第一个结点 */
	j = 1;		/*  j为计数器 */
	while (p && j < i)  /* p不为空或者计数器j还没有等于i时，循环继续 */
	{
		p = p->next;  /* 让p指向下一个结点 */
		++j;
	}
	if (!p || j>i)
		return ERROR;  /*  第i个元素不存在 */
	*e = p->data;   /*  取第i个元素的数据 */
	return OK;
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（头插法） */
void CreateListHead(LinkList *L, int n)
{
	LinkList p;
	int i;
	srand(time(0));                         /* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;                      /*  先建立一个带头结点的单链表 */
	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node)); /*  生成新结点 */
		p->data = rand() % 100 + 1;             /*  随机生成100以内的数字 */
		p->next = (*L)->next;
		(*L)->next = p;						/*  插入到表头 */
	}
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n)
{
	LinkList p, r;
	int i;
	srand(time(0));                      /* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node)); /* L为整个线性表 */
	r = *L;                                /* r为指向尾部的结点 */
	for (i = 0; i < n; i++)
	{
		p = (Node *)malloc(sizeof(Node)); /*  生成新结点 */
		p->data = rand() % 100 + 1;           /*  随机生成100以内的数字 */
		r->next = p;                        /* 将表尾终端结点的指针指向新结点 */
		r = p;                            /* 将当前的新结点定义为表尾终端结点 */
	}
	r->next = NULL;                       /* 表示当前链表结束 */
}

/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	int j;
	LinkList p, s;
	p = *L;     /* 声明一个结点 p，指向头结点 */
	j = 1;
	while (p && j < i)     /* 寻找第i个结点 */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;   /* 第i个元素不存在 */
	s = (LinkList)malloc(sizeof(Node));  /*  生成新结点(C语言标准函数) */
	s->data = e;
	s->next = p->next;      /* 将p的后继结点赋值给s的后继  */
	p->next = s;          /* 将s赋值给p的后继 */
	return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p->next && j < i)	/* 遍历寻找第i个元素 */
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i)
		return ERROR;           /* 第i个元素不存在 */
	q = p->next;
	p->next = q->next;			/* 将q的后继赋值给p的后继 */
	*e = q->data;               /* 将q结点中的数据给e */
	free(q);                    /* 让系统回收此结点，释放内存 */
	return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(LinkList L, ElemType e)
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		if (p->data == e) /* 找到这样的数据元素 */
			return i;
		p = p->next;
	}

	return 0;
}

/*单链表中不包含头节点*/
LinkList  reverseList(LinkList  head)  /*反转链表*/
{
	LinkList p, q, r;

	//链表为空，或是单结点链表直接返回头结点
	if (head == NULL || head->next == NULL)
	{
		return head;
	}
	p = head;
	q = head->next;
	head->next = NULL;
	while (q != NULL)
	{
		r = q->next;
		q->next = p;
		p = q;
		q = r;
	}	
	head = p;

	return head;
}

/* 单链表反转/逆序 */
LinkList ListReverse(LinkList L)	//单链表中包含头节点
{
	LinkList current, pnext, prev;
	if (L == NULL || L->next == NULL)
		return L;
	current = L->next;  /* current指向链表头节点的下一个节点 */
	pnext = current->next;
	current->next = NULL;
	while (pnext != NULL)
	{
		prev = pnext->next;
		pnext->next = current;
		current = pnext;
		pnext = prev;
	}
	//printf("current = %d,next = %d \n",current->data,current->next->data);	
	L->next = current;  /* 将链表头节点指向current */
	return L;
}

Status ListReverse2(LinkList L)
{
	LinkList current, p;

	if (L == NULL)
	{
		return NULL;
	}
	current = L->next;
	while (current->next != NULL)
	{
		p = current->next;
		current->next = p->next;
		p->next = L->next;
		L->next = p;
		ListTraverse(L);
		printf("current = %d, \n", current->data);
	}
	return L;
}

LinkList RemoveDupNode(LinkList L)//删除重复结点的算法
{
	LinkList p, q, r;
	p = L->next;
	while (p)    // p用于遍历链表
	{
		q = p;
		while (q->next) // q遍历p后面的结点，并与p数值比较
		{
			if (q->next->data == p->data)
			{
				r = q->next; // r保存需要删掉的结点
				q->next = r->next;   // 需要删掉的结点的前后结点相接
				free(r);
			}
			else
				q = q->next;
		}
		p = p->next;
	}
	return L;
}

void DelMaxNode(LinkList * L)  /*删除一个单链表L(带头节点)中元素值最大的节点*/
{
	LinkList p = (*L)->next, pre = (*L), maxp = p, maxpre = pre;
	while (p != NULL)
	{
		if (maxp->data < p->data)   //若找到一个更大的节点
		{
			maxp = p;			//更改maxp
			maxpre = pre;    //更改maxpre
		}
		pre = p;     //p、pre同步后移一个节点
		p = p->next;
	}
	maxpre->next = maxp->next;  //删除maxp节点
	free(maxp);  //释放maxp节点

}


//采用的是直接插入排序方法
void ListSort(LinkList * L)  /*存在一个带头节点的单链表L，设计一个算法使其元素递增有序排列*/
{
	LinkList p, pre, r;
	if ((*L)->next != NULL)  //若原单链表中有一个或者以上的数据结点
	{
		p = (*L)->next->next;  //p指向L的第2个数据节点
		(*L)->next->next = NULL;  //构造只含有一个数据节点的有序表
		while (p != NULL)
		{
			r = p->next; //r保存p节点后继节点的指针
			pre = (*L); //从有序表开头进行比较，pre指向插入p的前驱节点
			while (pre->next != NULL && pre->next->data < p->data)
				pre = pre->next;  //在有序表中找插入p的前驱节点pre
			p->next = pre->next;     //将pre之后插入p
			pre->next = p;
			p = r;    //扫描原单链表剩余的节点
		}
	}
}

// 获取单链表(含有头节点)倒数第k个结点值
LinkList GetkthNodeFromBack(LinkList L, unsigned int k)
{
	if (L == NULL || k == 0)
		return NULL;
	int i;
	LinkList Ptr1,Ptr2;
	Ptr1 = Ptr2 = L;
	for (i = 0; i < k; ++i)  //前移k步
	{
		if (Ptr1->next != NULL)
			Ptr1 = Ptr1->next;
		else
			return NULL;
	}
	while (Ptr1 != NULL)
	{
		//查找倒数第k个元素
		Ptr1 = Ptr1->next;
		Ptr2 = Ptr2->next;
	
	}
	return Ptr2;
}

Status GetMidNode(LinkList L, ElemType *e)  //找出有头结点链表的中间元素
{
	LinkList search, mid;
	mid = search = L->next;
	while (search->next != NULL) {
		//search移动的速度是 mid 的2倍
		if (search->next->next != NULL) {
			search = search->next->next;
			mid = mid->next;
			//printf("search %d\n", search->data);
			//printf("mid %d\n", mid->data);
		}
		else
		{
			search = search->next;
		}
	}
	*e = mid->data;
	return OK;
}

int main()
{
	LinkList L,Lreverse;
	LinkList Lk; //指向倒数第k个元素的指针
	Status i;
	int k, pos, value;
	char opp = 'A';
	ElemType e,eMid;


	i = InitList(&L);
	printf("链表L初始化完毕，ListLength(L)=%d\n", ListLength(L));

	printf("\n1.整表创建（尾插法） \n2.找出单链表中倒数第2个元素 \n3.插入操作 \n4.删除操作 \n5.获取节点数据 \n6.查找某个数是否在链表中 \n7.将链表中元素值按递增排序 \n8.删除链表中元素值最大的节点 \n9.反转链表 \nA.链表中间节点 \n0.退出 \n请选择你的操作：\n\n");
	while (opp != '0'){
		scanf("%c", &opp);
		switch (opp){
		case '1':
			CreateListTail(&L, 10);
			//CreateListHead(&L, 10);
			printf("整体创建L的元素(尾插法)：\n");
			ListTraverse(L);
			printf("\n");
			break;

		//case '2':
			//ListTraverse(L);
			//printf("\n");
			//break;

		case '2':
			printf("单链表中倒数第7个元素:");
			Lk = GetkthNodeFromBack(L, 7);
			printf("%d \n", Lk->data);
			printf("\n");
			break;

		case '3':
			printf("要在第几个位置插入元素？");
			scanf("%d", &pos);

			printf("插入的元素值是多少？");
			scanf("%d", &value);
			ListInsert(&L, pos, value);
			ListTraverse(L);
			printf("\n");
			break;

		case '4':
			printf("要删除第几个元素？");
			scanf("%d", &pos);
			ListDelete(&L, pos, &e);
			printf("删除第%d个元素成功，现在链表为：\n", pos);
			ListTraverse(L);
			printf("\n");
			break;

		case '5':
			printf("你需要获取第几个元素？");
			scanf("%d", &pos);
			GetElem(L, pos, &e);
			printf("第%d个元素的值为：%d\n", pos, e);
			printf("\n");
			break;

		case '6':
			printf("输入你需要查找的数：");
			scanf("%d", &pos);
			k = LocateElem(L, pos);
			if (k)
				printf("第%d个元素的值为%d\n", k, pos);
			else
				printf("没有值为%d的元素\n", pos);
			printf("\n");
			break;

		case '7':
			printf("链表元素递增：\n");
			ListSort(&L);
			ListTraverse(L);
			printf("\n");
			break;

		case '8':
			printf("删除链表元素值最大的节点：\n");
			DelMaxNode(&L);
			ListTraverse(L);
			printf("\n");
			break;

		case '9':
			printf("反转链表：\n");
			Lreverse = ListReverse(L);  /*反转链表*/
			ListTraverse(Lreverse);
			printf("\n");
			break;

		case 'A':
			printf("中间节点的值为：");
			GetMidNode(L, &eMid);
			printf(" %d\n", eMid);
			printf("\n");
			break;

		case '0':
			exit(0);
		}
	}

}