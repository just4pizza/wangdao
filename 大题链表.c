#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//-----------------����----------------------

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

//˫��������
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
		printf("����һ������:\n");
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
		printf("����һ��������\n");
		return;
	}

	DNode* p = L->next;  // �ӵ�һ���ڵ㿪ʼ
	printf("˫��ѭ����������:");
	while (p != L) {  // ѭ����ͷ�ڵ����
		printf(" %d", p->data);
		p = p->next;
	}
	printf("\n");
}

//Node *L �� LinkList L ��������һ��ָ�������һ������ָ��

LinkList creatlist(int size) //β�巨 123456
{
	int num = 0;
	LinkList L = (LinkList)malloc(sizeof(Node)); // ����ͷ��� 
	L->next = NULL;
	Node* p = L;
	for (int i = 0; i < size; i++) {
		Node* newNode = (Node*)malloc(sizeof(Node)); // ��ȷ�ķ���ڵ��ڴ�
		printf("����һ������:\n");
		scanf("%d", &num);
		newNode->data = num;
		newNode->next = NULL;
		p->next = newNode;
		p = newNode;
	}
	L->size = size;
	return L;
}

LinkList creatlist2(int size) //ͷ�巨
{
	int num = 0;
	LinkList L = (LinkList)malloc(sizeof(Node)); // ����ͷ���
	L->next = NULL;
	for (int i = 0; i < size; i++) 
	{
		Node* newNode = (Node*)malloc(sizeof(Node)); // ��ȷ�ķ���ڵ��ڴ�
		printf("����һ������:\n");
		scanf("%d", &num);
		newNode->data = num;
		newNode->next = L->next;
		L->next = newNode;
	}
	L->size = size;
	return L;
}

//���±���indexλ�õ�Ԫ�أ��ĳ�num
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

void ShowList(LinkList L) { // ��ӡ��������
	Node* p = L->next;
	if (p == NULL) {
		printf("����һ��������\n");
		return;
	}
	printf("������");
	while (p) {
		printf(" -> %d", p->data);
		p = p->next;
	}
	printf("\n");
	//printf("��:%d\n",L->size);
}
//�ڴ���ͷ�ڵ��������ɾ������ֵΪnum�������㣬���ͷſռ�
//����203. �Ƴ�����Ԫ��
void deleteallxa(LinkList L, int num) //����1
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

//ɾ����ͷ���ĵ������е���Сֵ���  ����2
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

//�͵���ת ����3
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
//��������ɾ������������֮��Ľ�� ������������
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
// һ�����Ա�{a1,b1,a2,b2,a3,b3...an,bn}���������{a1,a2,a3...an}��{b1,b2,b3...bn}
// ����6
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

//�����������д����ظ�Ԫ�أ�����㷨ɾ���ظ�Ԫ�� ����7
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
//ABΪ���������ĵ������ڲ��ƻ�AB������£����һ���㷨��A��B�Ĺ���Ԫ�ز�������C ����8
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
//ABΪ���������ĵ��������һ���㷨��A��B�Ĺ���Ԫ�ز������A�� ����9
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
//�ж�B�Ƿ���A������������ ����10
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
//�ж�ѭ��˫�����Ƿ�Գ�
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

//ѭ��������ϲ�,h1��h2����h2���ӵ�h1֮��������ɺ���Ϊѭ������
void circulatelist()
{

}
int main() 
{
	//int n = 0;
	//printf("����������ĳ���:\n");
	//scanf("%d", &n); // ���峤��
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

	//// �������� B
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