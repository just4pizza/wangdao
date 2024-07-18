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
	*insert_pos = left; // ��¼����λ��
	return -1; // δ�ҵ�
}
//����������������Ա�Ҫ�����һ���㷨�������ʱ�������ֵΪx��Ԫ�أ��ҵ����������
//Ԫ�ؽ��н������Ҳ������������в�ʹ����Ԫ���������� ����8
void find_and_insert(dynamic_array* arr, int target)
{
	int insert_pos;
	int index = twopartfind(arr, target, &insert_pos);

	if (index != -1) // �ҵ�Ԫ��
	{
		if (index != arr->size - 1) // �������һ��Ԫ��
		{
			// �����ҵ���Ԫ����������Ԫ��
			int temp = arr->array[index];
			arr->array[index] = arr->array[index + 1];
			arr->array[index + 1] = temp;
		}
	}
	else // δ�ҵ�Ԫ��
	{
		// ��������
		arr->array = realloc(arr->array, (arr->size + 1) * sizeof(int));
		arr->size++;

		// ��Ԫ�ز������λ�ò���������
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
//������������a��b��c���Ⱦ�Ϊn����Ϊ���ظ�Ԫ�صĵ������У����һ���������ͬʱ����
// ���������е��е�����Ԫ�� ����9
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
//2010ͳ������
void revleftlist(dynamic_array* arr, int p)
{
	//x1 x2 x3 x4 x5 x6
	revarr(arr, 0, arr->size - 1); //x6 x5 x4 x3 x3 x2 x1
	revarr(arr, 0, p);//x3 x4 x5 x6 x2 x1
	revarr(arr, p+1, arr->size-1);//x3 x4 x5 x6 x1 x2

}
//2011ͳ������
void midnumlist(dynamic_array* arr, dynamic_array* arr2)
{
	dynamic_array* arr3 = create_array(arr->size + arr2->size);
	merge(arr, arr2, arr3);
	printf("%d", arr3->array[(arr3->size-1) / 2]);
	//printflist(arr3);
}
//ð������
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
//2013ͳ������ ��һ������Ϊn�����У�������m����ȵ�Ԫ��x����m>n/2,���xΪ��Ԫ�أ������һ���㷨
//�ҳ�Ԫ��x��������x�������Ԫ�أ������������-1-----����169. ����Ԫ��
//void amainsumA(dynamic_array* arr)��ʺ
//{
//	babosort(arr);
//	//��Ԫ��Ψһ
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
//2013�Ľ��㷨 Ħ��ͶƱ�㷨
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

//2018ͳ������ �ҳ�������δ���ֵ���С������ ����41
//int neverseeminnum(int *arr,int size) //[2,1]����
//{--------------------------��ʺ
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
//�൱�����������±�����������������Ǵ����������Ԫ�أ������ɺ�
//ԭ��������Ԫ�ض�ӳ�䵽�����±����˲��Ҷ�������ģ�ԭ����Ԫ�ر���˴��ڱ��λ��
//�������ҳ�����λ�ã�ֻ��Ҫ�ҵ���һ��û��������±��ټ�һ���ǽ����ͦ�����
{
	//�������еķ��������ʹ��� size �����滻Ϊ size + 1����Щ������Ӱ������
	for (int i = 0; i < size; i++) {
		if (arr[i] <= 0 || arr[i] > size) {
			arr[i] = size + 1;
		}
	}
	//�������飬��ÿ���� [1, size] ��Χ�ڵ����Ķ�Ӧ����λ�ñ��Ϊ������
	// ��ʾ������λ�õ���ֵ�����������С�
	for (int i = 0; i < size; i++) {
		int num = (arr[i]);
		if (num <= size) {
			arr[num - 1] = -(arr[num - 1]);
		}
	}
	//�ٴα������飬�ҳ���һ������������λ�ã�������λ�ü�1��Ϊ��Сδ���ֵ���������
	// �������λ�ö��ѱ��Ϊ�������򷵻� size + 1��
	for (int i = 0; i < size; i++) {
		if (arr[i] > 0) {
			return i + 1;
		}
	}

	return size + 1;
}
//2020ͳ������
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


