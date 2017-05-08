#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;/* ElemType���͸���ʵ������������������Ϊint */

typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node;
typedef struct Node *LinkList; /* ����LinkList */


/* ��ʼ��˳�����Ա� */
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(Node)); /* ����ͷ���,��ʹLָ���ͷ��� */
	if (!(*L)) /* �洢����ʧ�� */
	{
		return ERROR;
	}
	(*L)->next = NULL; /* ָ����Ϊ�� */

	return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
Status ClearList(LinkList *L)
{
	LinkList p, q;
	p = (*L)->next;           /*  pָ���һ����� */
	while (p)                /*  û����β */
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;        /* ͷ���ָ����Ϊ�� */
	return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next; /* pָ���һ����� */
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}

/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* ������������ζ�L��ÿ������Ԫ����� */
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

/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* �����������e����L�е�i������Ԫ�ص�ֵ */
Status GetElem(LinkList L, int i, ElemType *e)
{
	int j;
	LinkList p;		/* ����һ���p */
	p = L->next;		/* ��pָ������L�ĵ�һ����� */
	j = 1;		/*  jΪ������ */
	while (p && j < i)  /* p��Ϊ�ջ��߼�����j��û�е���iʱ��ѭ������ */
	{
		p = p->next;  /* ��pָ����һ����� */
		++j;
	}
	if (!p || j>i)
		return ERROR;  /*  ��i��Ԫ�ز����� */
	*e = p->data;   /*  ȡ��i��Ԫ�ص����� */
	return OK;
}

/*  �������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��ͷ�巨�� */
void CreateListHead(LinkList *L, int n)
{
	LinkList p;
	int i;
	srand(time(0));                         /* ��ʼ����������� */
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;                      /*  �Ƚ���һ����ͷ���ĵ����� */
	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node)); /*  �����½�� */
		p->data = rand() % 100 + 1;             /*  �������100���ڵ����� */
		p->next = (*L)->next;
		(*L)->next = p;						/*  ���뵽��ͷ */
	}
}

/*  �������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��β�巨�� */
void CreateListTail(LinkList *L, int n)
{
	LinkList p, r;
	int i;
	srand(time(0));                      /* ��ʼ����������� */
	*L = (LinkList)malloc(sizeof(Node)); /* LΪ�������Ա� */
	r = *L;                                /* rΪָ��β���Ľ�� */
	for (i = 0; i < n; i++)
	{
		p = (Node *)malloc(sizeof(Node)); /*  �����½�� */
		p->data = rand() % 100 + 1;           /*  �������100���ڵ����� */
		r->next = p;                        /* ����β�ն˽���ָ��ָ���½�� */
		r = p;                            /* ����ǰ���½�㶨��Ϊ��β�ն˽�� */
	}
	r->next = NULL;                       /* ��ʾ��ǰ������� */
}

/* ��ʼ������˳�����Ա�L�Ѵ���,1��i��ListLength(L)�� */
/* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	int j;
	LinkList p, s;
	p = *L;     /* ����һ����� p��ָ��ͷ��� */
	j = 1;
	while (p && j < i)     /* Ѱ�ҵ�i����� */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;   /* ��i��Ԫ�ز����� */
	s = (LinkList)malloc(sizeof(Node));  /*  �����½��(C���Ա�׼����) */
	s->data = e;
	s->next = p->next;      /* ��p�ĺ�̽�㸳ֵ��s�ĺ��  */
	p->next = s;          /* ��s��ֵ��p�ĺ�� */
	return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p->next && j < i)	/* ����Ѱ�ҵ�i��Ԫ�� */
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i)
		return ERROR;           /* ��i��Ԫ�ز����� */
	q = p->next;
	p->next = q->next;			/* ��q�ĺ�̸�ֵ��p�ĺ�� */
	*e = q->data;               /* ��q����е����ݸ�e */
	free(q);                    /* ��ϵͳ���մ˽�㣬�ͷ��ڴ� */
	return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* �������������L�е�1����e�����ϵ������Ԫ�ص�λ�� */
/* ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
int LocateElem(LinkList L, ElemType e)
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		if (p->data == e) /* �ҵ�����������Ԫ�� */
			return i;
		p = p->next;
	}

	return 0;
}

/*�������в�����ͷ�ڵ�*/
LinkList  reverseList(LinkList  head)  /*��ת����*/
{
	LinkList p, q, r;

	//����Ϊ�գ����ǵ��������ֱ�ӷ���ͷ���
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

/* ������ת/���� */
LinkList ListReverse(LinkList L)	//�������а���ͷ�ڵ�
{
	LinkList current, pnext, prev;
	if (L == NULL || L->next == NULL)
		return L;
	current = L->next;  /* currentָ������ͷ�ڵ����һ���ڵ� */
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
	L->next = current;  /* ������ͷ�ڵ�ָ��current */
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

LinkList RemoveDupNode(LinkList L)//ɾ���ظ������㷨
{
	LinkList p, q, r;
	p = L->next;
	while (p)    // p���ڱ�������
	{
		q = p;
		while (q->next) // q����p����Ľ�㣬����p��ֵ�Ƚ�
		{
			if (q->next->data == p->data)
			{
				r = q->next; // r������Ҫɾ���Ľ��
				q->next = r->next;   // ��Ҫɾ���Ľ���ǰ�������
				free(r);
			}
			else
				q = q->next;
		}
		p = p->next;
	}
	return L;
}

void DelMaxNode(LinkList * L)  /*ɾ��һ��������L(��ͷ�ڵ�)��Ԫ��ֵ���Ľڵ�*/
{
	LinkList p = (*L)->next, pre = (*L), maxp = p, maxpre = pre;
	while (p != NULL)
	{
		if (maxp->data < p->data)   //���ҵ�һ������Ľڵ�
		{
			maxp = p;			//����maxp
			maxpre = pre;    //����maxpre
		}
		pre = p;     //p��preͬ������һ���ڵ�
		p = p->next;
	}
	maxpre->next = maxp->next;  //ɾ��maxp�ڵ�
	free(maxp);  //�ͷ�maxp�ڵ�

}


//���õ���ֱ�Ӳ������򷽷�
void ListSort(LinkList * L)  /*����һ����ͷ�ڵ�ĵ�����L�����һ���㷨ʹ��Ԫ�ص�����������*/
{
	LinkList p, pre, r;
	if ((*L)->next != NULL)  //��ԭ����������һ���������ϵ����ݽ��
	{
		p = (*L)->next->next;  //pָ��L�ĵ�2�����ݽڵ�
		(*L)->next->next = NULL;  //����ֻ����һ�����ݽڵ�������
		while (p != NULL)
		{
			r = p->next; //r����p�ڵ��̽ڵ��ָ��
			pre = (*L); //�������ͷ���бȽϣ�preָ�����p��ǰ���ڵ�
			while (pre->next != NULL && pre->next->data < p->data)
				pre = pre->next;  //����������Ҳ���p��ǰ���ڵ�pre
			p->next = pre->next;     //��pre֮�����p
			pre->next = p;
			p = r;    //ɨ��ԭ������ʣ��Ľڵ�
		}
	}
}

// ��ȡ������(����ͷ�ڵ�)������k�����ֵ
LinkList GetkthNodeFromBack(LinkList L, unsigned int k)
{
	if (L == NULL || k == 0)
		return NULL;
	int i;
	LinkList Ptr1,Ptr2;
	Ptr1 = Ptr2 = L;
	for (i = 0; i < k; ++i)  //ǰ��k��
	{
		if (Ptr1->next != NULL)
			Ptr1 = Ptr1->next;
		else
			return NULL;
	}
	while (Ptr1 != NULL)
	{
		//���ҵ�����k��Ԫ��
		Ptr1 = Ptr1->next;
		Ptr2 = Ptr2->next;
	
	}
	return Ptr2;
}

Status GetMidNode(LinkList L, ElemType *e)  //�ҳ���ͷ���������м�Ԫ��
{
	LinkList search, mid;
	mid = search = L->next;
	while (search->next != NULL) {
		//search�ƶ����ٶ��� mid ��2��
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
	LinkList Lk; //ָ������k��Ԫ�ص�ָ��
	Status i;
	int k, pos, value;
	char opp = 'A';
	ElemType e,eMid;


	i = InitList(&L);
	printf("����L��ʼ����ϣ�ListLength(L)=%d\n", ListLength(L));

	printf("\n1.��������β�巨�� \n2.�ҳ��������е�����2��Ԫ�� \n3.������� \n4.ɾ������ \n5.��ȡ�ڵ����� \n6.����ĳ�����Ƿ��������� \n7.��������Ԫ��ֵ���������� \n8.ɾ��������Ԫ��ֵ���Ľڵ� \n9.��ת���� \nA.�����м�ڵ� \n0.�˳� \n��ѡ����Ĳ�����\n\n");
	while (opp != '0'){
		scanf("%c", &opp);
		switch (opp){
		case '1':
			CreateListTail(&L, 10);
			//CreateListHead(&L, 10);
			printf("���崴��L��Ԫ��(β�巨)��\n");
			ListTraverse(L);
			printf("\n");
			break;

		//case '2':
			//ListTraverse(L);
			//printf("\n");
			//break;

		case '2':
			printf("�������е�����7��Ԫ��:");
			Lk = GetkthNodeFromBack(L, 7);
			printf("%d \n", Lk->data);
			printf("\n");
			break;

		case '3':
			printf("Ҫ�ڵڼ���λ�ò���Ԫ�أ�");
			scanf("%d", &pos);

			printf("�����Ԫ��ֵ�Ƕ��٣�");
			scanf("%d", &value);
			ListInsert(&L, pos, value);
			ListTraverse(L);
			printf("\n");
			break;

		case '4':
			printf("Ҫɾ���ڼ���Ԫ�أ�");
			scanf("%d", &pos);
			ListDelete(&L, pos, &e);
			printf("ɾ����%d��Ԫ�سɹ�����������Ϊ��\n", pos);
			ListTraverse(L);
			printf("\n");
			break;

		case '5':
			printf("����Ҫ��ȡ�ڼ���Ԫ�أ�");
			scanf("%d", &pos);
			GetElem(L, pos, &e);
			printf("��%d��Ԫ�ص�ֵΪ��%d\n", pos, e);
			printf("\n");
			break;

		case '6':
			printf("��������Ҫ���ҵ�����");
			scanf("%d", &pos);
			k = LocateElem(L, pos);
			if (k)
				printf("��%d��Ԫ�ص�ֵΪ%d\n", k, pos);
			else
				printf("û��ֵΪ%d��Ԫ��\n", pos);
			printf("\n");
			break;

		case '7':
			printf("����Ԫ�ص�����\n");
			ListSort(&L);
			ListTraverse(L);
			printf("\n");
			break;

		case '8':
			printf("ɾ������Ԫ��ֵ���Ľڵ㣺\n");
			DelMaxNode(&L);
			ListTraverse(L);
			printf("\n");
			break;

		case '9':
			printf("��ת����\n");
			Lreverse = ListReverse(L);  /*��ת����*/
			ListTraverse(Lreverse);
			printf("\n");
			break;

		case 'A':
			printf("�м�ڵ��ֵΪ��");
			GetMidNode(L, &eMid);
			printf(" %d\n", eMid);
			printf("\n");
			break;

		case '0':
			exit(0);
		}
	}

}