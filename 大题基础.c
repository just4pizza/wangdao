#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//-----------------˳�������----------------------
typedef struct
{
	int* array;//һ��ָ�����������ָ��
	//����ζ�Ŷ�̬����ʵ�ʴ洢����һ����������ĵ�ַ��
	//ͨ�����ָ����Է��ʺͲ��������е�Ԫ�ء�
	size_t size;//�����п���Ԫ�ص�����
} dynamic_array;


//���ڴ�����̬����ĺ��� 
//return_type function_name(parameters)
//�ṹ��ָ����Ϊ�����ķ�������
dynamic_array* create_array(size_t size)
{
	dynamic_array* arr = malloc(sizeof(dynamic_array));
	//���������㹻�洢dynamic_array �ṹ����ڴ�ռ�
	//�������ص��ڴ��ַ����ָ��ýṹ�����͵�ָ�� arr
	arr->array = malloc(size * sizeof(int));
	// �����ܹ��洢 size �������Ŀռ�
	arr->size = size;
	//��¼��̬�����ʵ������
	return arr;
}

void inputarr(dynamic_array* arr)
{
	int x = 0;
	for (int i = 0; i < arr->size; i++)
	{
		printf("����һ��������\n");
		scanf("%d", &x);
		arr->array[i] = x;
	}
}


//���ڶ�ȡ��̬����Ԫ�صĺ���
int read_array(dynamic_array* arr, size_t index) {
	if (index < arr->size)
		return arr->array[index];
	else
	{
		printf("Error: index out of bounds: %d\n", index);
		return -1;
	}
}

//���ڸ��¶�̬����Ԫ�صĺ���
void update_array(dynamic_array* arr, size_t index, int value) {
	if (index < arr->size)
		arr->array[index] = value;
	else
		printf("Error: index out of bounds: %d\n", index);
}
//dynamic_array* arr��ָ��̬����ṹ���ָ�롣
//size_t index��Ҫ���µ�Ԫ���������е�����λ�á�
//int value����ֵ���������滻ԭ�����ж�Ӧ����λ�õ�ֵ��

//����ɾ��������̬����ĺ���
void delete_array(dynamic_array* arr) {
	free(arr->array);//free(arr->array) ���ͷŶ�̬�����ڲ�����������ռ�õ��ڴ�ռ�
	arr->array = NULL;
	free(arr);//�ͷ�������̬����ṹ��
	arr = NULL;
}

//��ӡ���ű�
void printflist(dynamic_array* arr)
{
	for (int i = 0; i < arr->size; i++)
	{
		printf("arr[%d]=%d\n", i, arr->array[i]);
	}
}
//ɾ��ָ��Ԫ�ز���ֵ������������λ�� ����1
void delete_elem(dynamic_array* arr, int value)
{
	int found = 0;

	for (int i = 0; i < arr->size; i++)
	{
		if (arr->array[i] == value)
		{
			printf("arr[%d]=%d find it\n", i, arr->array[i]);
			found = 1;

			// �ƶ�Ԫ�ظ��Ǳ�ɾ����Ԫ��
			for (int j = i; j < arr->size - 1; j++)
			{
				arr->array[j] = arr->array[j + 1];
			}

			// ���������С
			arr->size -= 1;
			arr->array = realloc(arr->array, arr->size * sizeof(int));
			break; // �˳�ѭ������Ϊ����ֻɾ����һ��ƥ���Ԫ��
		}
	}

	if (!found)
	{
		printf("No\n");
	}
}
//Ԫ����ת ����2
void revarr(dynamic_array* arr,int left,int right)
{
	int temp = 0;
	/*size_t left = 0;
	size_t right = arr->size - 1;*/
	while (left < right)
	{
		temp = arr->array[left];
		arr->array[left] = arr->array[right];
		arr->array[right] = temp;
		left++;
		right--;
	}
}

//ɾ������ֵΪx��Ԫ�� ����3
void deleteallx(dynamic_array* arr, int x)
{
	{
		int k = 0, i = 0;
		while (i < arr->size)
		{
			if (arr->array[i] == x)
				k++;
			else
				arr->array[i - k] = arr->array[i];
			i++;
		}
		arr->size = arr->size - k;

	}
}

//ɾ������ֵ��s��t֮������� ����s��tҪ��s<t ��������ʾ�����˳�
bool delete_stot(dynamic_array* arr, int s, int t)
{
	if (s >t||arr->size==0)
		return false;
	int sum = 0;
	while (s<=t)
	{
		int i = 0, k = 0;
		deleteallx(arr, s);
		s++;
	}
}

//ɾ���ظ�������Ԫ�أ�ʹ����Ԫ�ؾ���ͬ(�����) ����5
//�Ѳ���ͬ��Ԫ��ǰ��Ȼ��ı������С
bool deleteallsamenum(dynamic_array* arr)
{
	int i = 0,j=0;
	for (i = 0, j = 1; j < arr->size;j++)
	{
		if (arr->array[i] != arr->array[j])
		{
			arr->array[++i] = arr->array[j];
		}
	}
	arr->size = i + 1;
	return true;
}

//�����������ϲ���һ���µ������ ���� 6
bool merge(dynamic_array* arr, dynamic_array* arr2, dynamic_array* arr3)
{
	if (arr->size + arr2->size > arr3->size)
		return false;
	int i = 0, j = 0, k = 0;
	while (j < arr->size && k < arr2->size)//ѭ���Ƚ�
	{
		if (arr->array[j] < arr2->array[k])
			arr3->array[i++] = arr->array[j++];
		else
			arr3->array[i++] = arr2->array[k++];
		
	}
	//��ʣ�µķ���aar3��
	while(j<arr->size)
		arr3->array[i++] = arr->array[j++];
	while (k < arr2->size)
		arr3->array[i++] = arr2->array[k++];
}
//A[m+n]�д���������Ա�a��b�������������ѭ�򣬽�b����aǰ ����7
bool revlist_ab(dynamic_array* arr,size_t a,size_t b)
{
	if (a + b != arr->size)
		return false;
	revarr(arr,0,arr->size-1);
	revarr(arr, 0, b-1);
	revarr(arr, b, arr->size-1);
	return true;
}
//���ֲ���
bool twopartfind(dynamic_array* arr, int value)
{
	int left = 0;
	int right = arr->size - 1;
	
	while (left < right)
	{
		int mid = (right + left) / 2;
		if (value == arr->array[mid])
			return true;
		else if (value > arr->array[mid])
			left = mid + 1;
		else right = mid - 1;
	}
	if (left > right)
		return false;
}
//����������������Ա�Ҫ�����һ���㷨�������ʱ�������ֵΪx��Ԫ�أ��ҵ����������
//Ԫ�ؽ��н������Ҳ������������в�ʹ����Ԫ����������
void find_and_inseter()
{
	
}
int main()
{
	dynamic_array* arr = create_array(10);
	//dynamic_array* arr2 = create_array(10);
	//inputarr(arr);
	for (int i = 0; i < arr->size; i++)
	{
		update_array(arr, i, i);
	}
	/*for (int i = 0; i < arr2->size; i++)
	{
		update_array(arr2, i, i+3);
	}*/
	printflist(arr);
	printf("------------\n");
	
	printf("------------\n");
	printflist(arr);
	return 0;
}


//-----------------����----------------------

//typedef struct LNode {
//	int data;
//	struct LNode* next;
//}LNode;
//#define Max 5
//typedef struct LNode* LinkList;
//
//void ShowList(LinkList L)					//��ӡ��������
//{
//	LinkList p;
//	p = L->next;
//	if (p == NULL)
//	{
//		printf("����һ��������\n");
//	}
//	printf("������");
//	while (p)
//	{
//		printf(" -> %d", p->data);
//		p = p->next;
//	}
//	printf("\n");
//}
//bool reverlist(LinkList L)//ԭ�ص�ͷ
//{
//	LNode* p;
//	LNode* r;
//	p = L->next;
//	L->next = NULL;
//	while (p != NULL)
//	{
//		r = p->next;
//		p->next = L->next;
//		L->next = p;
//		p = r;
//	}
//	return true;
//}
//
//int main()
//{
//	int x;
//	int length = 0;
//	LinkList S;
//	S = (LNode*)malloc(sizeof(LNode));
//	S->next = NULL;
//	//��ʼ��
//	LNode* p;
//	
//	while (length != Max)
//	{
//		printf("��������Ҫ�����Ԫ��ֵ��");
//		scanf("%d", &x);
//		p = (LNode*)malloc(sizeof(LNode));
//		p->data = x;
//		p->next = S->next;
//		S->next = p;
//		length++;
//	}
//	ShowList(S);
//	reverlist(S);
//	ShowList(S);
//	return 0;
//}