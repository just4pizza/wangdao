#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//-----------------顺序表数组----------------------
typedef struct
{
	int* array;//一个指向整型数组的指针
	//这意味着动态数组实际存储的是一个整数数组的地址，
	//通过这个指针可以访问和操作数组中的元素。
	size_t size;//数组中可用元素的数量
} dynamic_array;


//用于创建动态数组的函数 
//return_type function_name(parameters)
//结构体指针作为函数的返回类型
dynamic_array* create_array(size_t size)
{
	dynamic_array* arr = malloc(sizeof(dynamic_array));
	//函数分配足够存储dynamic_array 结构体的内存空间
	//并将返回的内存地址赋给指向该结构体类型的指针 arr
	arr->array = malloc(size * sizeof(int));
	// 分配能够存储 size 个整数的空间
	arr->size = size;
	//记录动态数组的实际容量
	return arr;
}

void inputarr(dynamic_array* arr)
{
	int x = 0;
	for (int i = 0; i < arr->size; i++)
	{
		printf("输入一个整数：\n");
		scanf("%d", &x);
		arr->array[i] = x;
	}
}


//用于读取动态数组元素的函数
int read_array(dynamic_array* arr, size_t index) {
	if (index < arr->size)
		return arr->array[index];
	else
	{
		printf("Error: index out of bounds: %d\n", index);
		return -1;
	}
}

//用于更新动态数组元素的函数
void update_array(dynamic_array* arr, size_t index, int value) {
	if (index < arr->size)
		arr->array[index] = value;
	else
		printf("Error: index out of bounds: %d\n", index);
}
//dynamic_array* arr：指向动态数组结构体的指针。
//size_t index：要更新的元素在数组中的索引位置。
//int value：新值，将用于替换原数组中对应索引位置的值。

//用于删除整个动态数组的函数
void delete_array(dynamic_array* arr) {
	free(arr->array);//free(arr->array) 来释放动态数组内部整数数组所占用的内存空间
	arr->array = NULL;
	free(arr);//释放整个动态数组结构体
	arr = NULL;
}

//打印整张表
void printflist(dynamic_array* arr)
{
	for (int i = 0; i < arr->size; i++)
	{
		printf("arr[%d]=%d\n", i, arr->array[i]);
	}
}
//删除指定元素并用值返回所在数列位置 王道1
void delete_elem(dynamic_array* arr, int value)
{
	int found = 0;

	for (int i = 0; i < arr->size; i++)
	{
		if (arr->array[i] == value)
		{
			printf("arr[%d]=%d find it\n", i, arr->array[i]);
			found = 1;

			// 移动元素覆盖被删除的元素
			for (int j = i; j < arr->size - 1; j++)
			{
				arr->array[j] = arr->array[j + 1];
			}

			// 调整数组大小
			arr->size -= 1;
			arr->array = realloc(arr->array, arr->size * sizeof(int));
			break; // 退出循环，因为我们只删除第一个匹配的元素
		}
	}

	if (!found)
	{
		printf("No\n");
	}
}
//元素逆转 王道2
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

//删除所有值为x的元素 王道3
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

//删除给定值在s和t之间的数字 包括s、t要求s<t 不合理显示错误退出
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

//删除重复的所有元素，使表中元素均不同(有序表) 王道5
//把不相同的元素前移然后改变数组大小
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

//将两个有序表合并成一个新的有序表 王道 6
bool merge(dynamic_array* arr, dynamic_array* arr2, dynamic_array* arr3)
{
	if (arr->size + arr2->size > arr3->size)
		return false;
	int i = 0, j = 0, k = 0;
	while (j < arr->size && k < arr2->size)//循环比较
	{
		if (arr->array[j] < arr2->array[k])
			arr3->array[i++] = arr->array[j++];
		else
			arr3->array[i++] = arr2->array[k++];
		
	}
	//将剩下的放入aar3中
	while(j<arr->size)
		arr3->array[i++] = arr->array[j++];
	while (k < arr2->size)
		arr3->array[i++] = arr2->array[k++];
}
//A[m+n]中存放两个线性表a和b，交换两个表的循序，将b放在a前 王道7
bool revlist_ab(dynamic_array* arr,size_t a,size_t b)
{
	if (a + b != arr->size)
		return false;
	revarr(arr,0,arr->size-1);
	revarr(arr, 0, b-1);
	revarr(arr, b, arr->size-1);
	return true;
}
//二分查找
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
//给定递增有序的线性表，要求设计一个算法完成最少时间查找数值为x的元素，找到则与其后面
//元素进行交换，找不到则将其插入表中并使表中元素依旧有序
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


//-----------------链表----------------------

//typedef struct LNode {
//	int data;
//	struct LNode* next;
//}LNode;
//#define Max 5
//typedef struct LNode* LinkList;
//
//void ShowList(LinkList L)					//打印整个链表
//{
//	LinkList p;
//	p = L->next;
//	if (p == NULL)
//	{
//		printf("这是一个空链表！\n");
//	}
//	printf("单链表");
//	while (p)
//	{
//		printf(" -> %d", p->data);
//		p = p->next;
//	}
//	printf("\n");
//}
//bool reverlist(LinkList L)//原地掉头
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
//	//初始化
//	LNode* p;
//	
//	while (length != Max)
//	{
//		printf("请输入你要插入的元素值：");
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