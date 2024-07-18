#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//-----------------链表----------------------

typedef struct Node {
	int data;
	struct Node* next;
	int size;
} Node;

typedef struct Node* LinkList;

typedef struct DNode {
	int data;
	struct DNode* next;
	struct DNode* pre;
} DNode;

typedef struct DNode* DLinkList;

//双向链表创立
DLinkList creatlistD(int size)
{
	if (size <= 0)
		return NULL;
	int num = 0;
	DLinkList L = (DLinkList)malloc(sizeof(DNode));
	L->next = L;
	L->pre = L;
	DNode* p = L;
	for (int i = 0; i < size; i++)
	{
		DNode* newNode = (DNode*)malloc(sizeof(DNode));
		printf("输入一个整数:\n");
		scanf("%d", &num);
		newNode->data = num;

		newNode->next = L;
		newNode->pre = p;
		p->next = newNode;
		L->pre = newNode;
		p = newNode;
	}
	return L;
}
void ShowDLinkList(DLinkList L) {
	if (L == NULL || L->next == L) {
		printf("这是一个空链表！\n");
		return;
	}

	DNode* p = L->next;  // 从第一个节点开始
	printf("双向循环链表内容:");
	while (p != L) {  // 循环到头节点结束
		printf(" %d", p->data);
		p = p->next;
	}
	printf("\n");
}

//Node *L 与 LinkList L 都是声明一个指向单链表第一个结点的指针

LinkList creatlist(int size) //尾插法 123456
{
	int num = 0;
	LinkList L = (LinkList)malloc(sizeof(Node)); // 创建头结点 
	L->next = NULL;
	Node* p = L;
	for (int i = 0; i < size; i++) {
		Node* newNode = (Node*)malloc(sizeof(Node)); // 正确的分配节点内存
		printf("输入一个整数:\n");
		scanf("%d", &num);
		newNode->data = num;
		newNode->next = NULL;
		p->next = newNode;
		p = newNode;
	}
	L->size = size;
	return L;
}

LinkList creatlist2(int size) //头插法
{
	int num = 0;
	LinkList L = (LinkList)malloc(sizeof(Node)); // 创建头结点
	L->next = NULL;
	for (int i = 0; i < size; i++) 
	{
		Node* newNode = (Node*)malloc(sizeof(Node)); // 正确的分配节点内存
		printf("输入一个整数:\n");
		scanf("%d", &num);
		newNode->data = num;
		newNode->next = L->next;
		L->next = newNode;
	}
	L->size = size;
	return L;
}

//更新表中index位置的元素，改成num
void updatalist(LinkList L, int index,int num)
{
	if (index > L->size)
		return false;
	Node* s = L;
	int i = 0;
	while (s!=NULL&&i<index)
	{
		s = s->next;
		i++;
	}
	s->data = num;
	return L;
}

void ShowList(LinkList L) { // 打印整个链表
	Node* p = L->next;
	if (p == NULL) {
		printf("这是一个空链表！\n");
		return;
	}
	printf("单链表");
	while (p) {
		printf(" -> %d", p->data);
		p = p->next;
	}
	printf("\n");
	//printf("表长:%d\n",L->size);
}
//在带有头节点的链表中删除所有值为num的链表结点，并释放空间
//力扣203. 移除链表元素
void deleteallxa(LinkList L, int num) //王道1
{
	if (L == NULL)
		return NULL;
	Node* scan = L->next;
	Node* pre = L;
	Node* del;
	pre->next = scan;
	while (scan != NULL)
	{
		if (scan->data == num)
		{
			del = scan;
			pre->next = scan->next;
			scan = scan->next;
			free(del);
			L->size--;
		}
		else {
			pre = scan;
			scan = scan->next;
		}
	}
	return L;
}
LinkList removeElements(LinkList head, int val)
{
	if (!head)
		return head;
	head->next = removeElements(head->next, val);
	return head->data == val ? head->next : head;
}

//删除带头结点的单链表中的最小值结点  王道2
void deletminnum(LinkList L)
{
	Node* scan = L->next;
	int min = scan->data;
	while (scan != NULL)
	{
		if (scan->data < min)
		{
			min = scan->data;
		}
		scan = scan->next;
	}
	deleteallxa(L, min);
}

//就地逆转 王道3
void revlist(LinkList L)
{
	Node* p, * r;
	p = L->next;
	L->next = NULL;
	while (p != NULL)
	{
		r = p->next;
		p->next = L->next;
		L->next = p;
		p = r;
	}
	return L;
}
//链表无序删除给定两个数之间的结点 包括这两个数
void Nodedeleteab(LinkList L, int a, int b)
{
	if (L == NULL)
		return NULL;
	Node* scan = L->next;
	Node* pre = L;
	Node* del;
	pre->next = scan;
	while (scan != NULL)
	{
		if (scan->data <= b && scan->data >= a)
		{
			del = scan;
			pre->next = scan->next;
			scan = scan->next;
			free(del);
			L->size--;
		}
		else {
			pre = scan;
			scan = scan->next;
		}
	}
	return L;
}
// 一个线性表{a1,b1,a2,b2,a3,b3...an,bn}拆成两个表{a1,a2,a3...an}、{b1,b2,b3...bn}
// 王道6
LinkList segmentlist(LinkList L)
{
	LinkList LB = (Node*)malloc(sizeof(Node));
	LB->next = NULL;
	Node* A = L->next;
	Node* B = A->next;
	Node* r = LB;
	while (A!=NULL&&B!=NULL)
	{
		B = A->next;
		A->next = B->next;
		B->next = NULL;
		r->next = B;
		r = B;
		A = A->next;
	}
	return LB;
}

//有序单增链表中存在重复元素，设计算法删除重复元素 王道7
void Nodedeletesamenum(LinkList L)
{
	Node* scan = L->next;
	Node* pre = L;
	Node* r;
	while (scan != NULL)
	{
		if (scan->data != pre->data)
		{
			pre = scan;
			scan = scan->next;
		}
		else if(scan->data == pre->data)
		{
			r = scan;
			scan = scan->next;
			if (scan->data != pre->data)
			{
				pre->next = scan;
				r->next = NULL;
				L->size--;
				pre = scan;
				scan = scan->next;
			}
		}
	}
}
//AB为两个递增的单链表，在不破坏AB的情况下，设计一个算法从A和B的公共元素产生链表C 王道8
LinkList listABsamenode(LinkList A, LinkList B)
{
	LinkList C = (Node*)malloc(sizeof(Node));
	C->next = NULL;
	Node* a = A->next;
	Node* b = B->next;
	Node* r = C;
	while (a != NULL && b != NULL)
	{
		if (a->data < b->data)
			a = a->next;
		else if (a->data > b->data)
			b = b->next;
		else if (a->data == b->data)
		{
			Node* c = (Node*)malloc(sizeof(Node));
			c->data = a->data;
			c->next = NULL;
			r->next = c;
			r = c;
			a = a->next;
			b = b->next;
		}

	}
	r->next = NULL;
	return C;
}
//AB为两个递增的单链表，设计一个算法求A和B的公共元素并存放在A中 王道9
LinkList listABsamenodetoA(LinkList A, LinkList B)
{
	Node* a = A->next;
	Node* b = B->next;
	Node* del;
	Node* r = A;
	while (a != NULL && b != NULL)
	{
		 if (a->data == b->data)
		{
			r->next = a;
			r = a;
			a = a->next;
			del = b;
			b = b->next;
			free(del);
		}
		 else if (a->data < b->data)
		{
			del = a;
			a = a->next;
			free(del);
		}
		else 
		{
			del = b;
			b = b->next;
			free(del);
		}
		
	}
	while (a!=NULL)
	{
		del = a;
		a = a->next;
		free(del);
	}
	while (b != NULL)
	{
		del = b;
		b = b->next;
		free(del);
	}
	r->next = NULL;
	free(B);
	return A;
}
//判断B是否是A的连续子数列 王道10
void isBisAson(LinkList A, LinkList B)
{
	Node* a = A->next;
	Node* b = B->next;
	Node* preb = B->next;
	while (b != NULL&&a!=NULL)
	{
		if (a->data == b->data)
		{
			a = a->next;
			b = b->next;
		}
		else {
			a = a->next;
			b = B->next;
		}
		if (b == NULL)
		{
			printf("yes\n");
			return true;
		}
	}
	printf("no\n");
	return false;
}
//判断循环双链表是否对称
bool dnodesymmetry(DLinkList L)
{
	DNode* start = L->next;
	DNode* end = L->pre;
	while (start->next != end && start != end)
	{
		if (start->data == end->data)
		{
			start = start->next;
			end = end->pre;
		}
		else {
			printf("No\n");
			return false;
		}
	}
	printf("yes\n");
	return true;
}

//循环单链表合并,h1和h2，将h2链接导h1之后，连接完成后仍为循环链表
void circulatelist()
{

}
int main() 
{
	//int n = 0;
	//printf("请输入链表的长度:\n");
	//scanf("%d", &n); // 定义长度
	/*LinkList L = creatlist(5);
	LinkList L2 = creatlist(5);*/
	//LinkList A = (Node*)malloc(sizeof(Node));
	//A->next = NULL;
	//Node* p = A;
	//int dataA[] = { 1, 2, 3, 4, 5 ,6,7,2,3,6,8,5};
	//for (int i = 0; i < 12; i++) {
	//	Node* newNode = (Node*)malloc(sizeof(Node));
	//	newNode->data = dataA[i];
	//	newNode->next = NULL;
	//	p->next = newNode;
	//	p = newNode;
	//}

	//// 创建链表 B
	//LinkList B = (Node*)malloc(sizeof(Node));
	//B->next = NULL;
	//p = B;
	//int dataB[] = { 2, 3, 7 };
	//for (int i = 0; i < 3; i++) {
	//	Node* newNode = (Node*)malloc(sizeof(Node));
	//	newNode->data = dataB[i];
	//	newNode->next = NULL;
	//	p->next = newNode;
	//	p = newNode;
	//}
	DLinkList A= creatlistD(4);
	ShowDLinkList(A);
	dnodesymmetry(A);
	return 0;
}