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
int twopartfind(dynamic_array* arr, int value, int* insert_pos)
{
	int left = 0;
	int right = arr->size - 1;

	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (value == arr->array[mid])
			return mid;
		else if (value > arr->array[mid])
			left = mid + 1;
		else
			right = mid - 1;
	}
	*insert_pos = left; // 记录插入位置
	return -1; // 未找到
}
//给定递增有序的线性表，要求设计一个算法完成最少时间查找数值为x的元素，找到则与其后面
//元素进行交换，找不到则将其插入表中并使表中元素依旧有序 王道8
void find_and_insert(dynamic_array* arr, int target)
{
	int insert_pos;
	int index = twopartfind(arr, target, &insert_pos);

	if (index != -1) // 找到元素
	{
		if (index != arr->size - 1) // 不是最后一个元素
		{
			// 交换找到的元素与其后面的元素
			int temp = arr->array[index];
			arr->array[index] = arr->array[index + 1];
			arr->array[index + 1] = temp;
		}
	}
	else // 未找到元素
	{
		// 扩大数组
		arr->array = realloc(arr->array, (arr->size + 1) * sizeof(int));
		arr->size++;

		// 将元素插入合适位置并保持有序
		for (int i = arr->size - 1; i > insert_pos; i--)
		{
			arr->array[i] = arr->array[i - 1];
		}
		arr->array[insert_pos] = target;
	}
}

int Maxabc(int x, int y, int z)
{
	int max;

	if (x > y)    max = x;
	else        max = y;
	if (z > max)  max = z;

	return max;
}
//给定三个序列a、b、c长度均为n，均为无重复元素的递增序列，设计一个逐行输出同时存在
// 这三个序列的中的所有元素 王道9
void three_arr_same_sum(dynamic_array* arr, dynamic_array* arr2, dynamic_array* arr3,int n)
{
	int i = 0, j = 0, k = 0;
 	while (i<n&&j<n&&k<n)
	{
		if (arr->array[i] == arr2->array[j]&& arr2->array[j]==arr3->array[k])
		{
			printf("%d\n", arr->array[i]);
			i++;
			j++;
			k++;
		}
		else if(arr->array[i]< Maxabc(arr->array[i], arr2->array[j], arr3->array[k]))
		{
			i++;
		}
		else if (arr2->array[j] < Maxabc(arr->array[i], arr2->array[j], arr3->array[k]))
		{
			j++;
		}
		else if (arr3->array[k] < Maxabc(arr->array[i], arr2->array[j], arr3->array[k]))
		{
			k++;
		}
	}

}
//2010统考真题
void revleftlist(dynamic_array* arr, int p)
{
	//x1 x2 x3 x4 x5 x6
	revarr(arr, 0, arr->size - 1); //x6 x5 x4 x3 x3 x2 x1
	revarr(arr, 0, p);//x3 x4 x5 x6 x2 x1
	revarr(arr, p+1, arr->size-1);//x3 x4 x5 x6 x1 x2

}
//2011统考真题
void midnumlist(dynamic_array* arr, dynamic_array* arr2)
{
	dynamic_array* arr3 = create_array(arr->size + arr2->size);
	merge(arr, arr2, arr3);
	printf("%d", arr3->array[(arr3->size-1) / 2]);
	//printflist(arr3);
}
//冒泡排序
void babosort(dynamic_array* arr)
{
	for (int i = 0; i < arr->size-1; i++)
	{
		for (int j = 0; j < arr->size - 1 - i; j++)
		{
			if (arr->array[j] > arr->array[j+1])
			{
				int temp = arr->array[j + 1];
				arr->array[j + 1] = arr->array[j];
				arr->array[j] = temp;
			}
		}
	}

}
//2013统考真题 给一个长度为n的序列，若存在m个相等的元素x，且m>n/2,则称x为主元素，请设计一个算法
//找出元素x，若存在x则输出该元素，不存在则输出-1-----力扣169. 多数元素
//void amainsumA(dynamic_array* arr)狗屎
//{
//	babosort(arr);
//	//主元素唯一
//	int i = 0;
//	int j = 1;
//	int count = 1;
//	int most_num = 0;
//	while(j < arr->size - 1)
//	{
//		if (arr->array[i] != arr->array[j])
//		{
//			i++;
//			j++;
//		}
//		else
//		{
//			count++;
//			if (count > arr->size / 2)
//			{
//				printf("yes,num=%d", arr->array[i]);
//				break;
//			}
//			j++;
//			i++;
//		}
//	}
//	return -1;
//
//}
//2013改进算法 摩尔投票算法
int find_majority_element(dynamic_array* arr)
{
	int count = 0;
	int candidate = -1;

	// Phase 1: Find a candidate
	for (int i = 0; i < arr->size; i++)
	{
		if (count == 0)
		{
			candidate = arr->array[i];
			count = 1;
		}
		else if (arr->array[i] == candidate)
		{
			count++;
		}
		else
		{
			count--;
		}
	}

	// Phase 2: Verify the candidate
	count = 0;
	for (int i = 0; i < arr->size; i++)
	{
		if (arr->array[i] == candidate)
		{
			count++;
		}
	}

	if (count > arr->size / 2)
	{
		printf("%d", candidate);
		return candidate;
	}
	else
	{
		printf("-1");
		return -1;
	}
}

//2018统考真题 找出数组中未出现的最小正整数 力扣41
//int neverseeminnum(int *arr,int size) //[2,1]错误
//{--------------------------狗屎
//	int i = 0;
//	int minnum = 1;
//	while (i < size)
//	{
//		if (arr[i] <= 0)
//		{
//			arr[i] = size + 1;
//		}
//		else
//		{
//			if (arr[i] == minnum)
//				minnum++;
//		}
//		i++;
//	}
//	return minnum;
//}

int missingnum(int* arr, int size)
//相当于利用数组下标这个有序的数列来标记存在于数组的元素，标记完成后，
//原来的数组元素都映射到数组下标上了并且都是有序的，原来的元素变成了存在标记位，
//第三步找出正数位置，只需要找到第一个没标记数组下标再加一就是结果，挺巧妙的
{
	//将数组中的非正整数和大于 size 的数替换为 size + 1，这些数不会影响结果。
	for (int i = 0; i < size; i++) {
		if (arr[i] <= 0 || arr[i] > size) {
			arr[i] = size + 1;
		}
	}
	//遍历数组，将每个在 [1, size] 范围内的数的对应索引位置标记为负数，
	// 表示该索引位置的数值存在于数组中。
	for (int i = 0; i < size; i++) {
		int num = (arr[i]);
		if (num <= size) {
			arr[num - 1] = -(arr[num - 1]);
		}
	}
	//再次遍历数组，找出第一个正数的索引位置，该索引位置加1即为最小未出现的正整数。
	// 如果所有位置都已标记为负数，则返回 size + 1。
	for (int i = 0; i < size; i++) {
		if (arr[i] > 0) {
			return i + 1;
		}
	}

	return size + 1;
}
//2020统考真题
//https://www.bilibili.com/video/BV1rK4y1e7JR?t=3956.4&p=2




printfarr(int* arr, int n)
{
	for(int i=0;i<n;i++)
	printf("arr[%d]=%d\n", i, arr[i]);
}
//int main()
//{
//	int arr[7] = { 2,1,7,-1,6,0,8 };
//	int a = sizeof(arr)/sizeof(int);
//	/*dynamic_array* arr = create_array(7);
//	dynamic_array* arr2 = create_array(5);*/
//	//dynamic_array* arr3 = create_array(5);
//	/*inputarr(arr);*/
//	//inputarr(arr2);
//	/*for (int i = 0; i < arr->size; i++)
//	{
//		update_array(arr, i, i);
//	}
//	for (int i = 0; i < arr2->size; i++)
//	{
//		update_array(arr2, i, i+2);
//	}*/
//	/*for (int i = 0; i < arr3->size; i++)
//	{
//		update_array(arr3, i, i + 3);
//	}*/
//	/*printflist(arr);
//	printf("------------\n");
//	
//	printf("------------\n");
//	printflist(arr);*/
//	return 0;
//}


