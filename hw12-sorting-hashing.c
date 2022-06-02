#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE // �ؽ� ���̺��� ũ�⸦ MAX_ARRAY_SIZE�� ����

int initialize(int **a);		// �迭 ����
int freeArray(int *a);			// �迭 ����
void printArray(int *a);		// �迭 ���

int selectionSort(int *a);		// ��������
int insertionSort(int *a);		// ��������
int bubbleSort(int *a); 		// ��������
int shellSort(int *a);			// ������
int quickSort(int *a, int n);	// ������

int hashCode(int key);	// �ؽ� �ڵ� ����

int hashing(int *a, int **ht);	// �迭 a�� ���� hash table ����

int search(int *ht, int key); // �ؽ� ���̺��� key�� ã�� �ؽ� ���̺��� �ε��� ��ȯ

int main()
{
	char command;
	int *array = NULL;	
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
	printf("[-------------------- [����â] [2021040021] --------------------]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)		// �迭 ����
{
	int *temp = NULL;		// int�� ���� ������ temp�� NULL�� �ִ´�.

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) // a�� ����Ű�� ���� NULL�� ���. �迭�� ���� ���
	{
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		// �޸��� Heap ������ int�� �ڷ��� ũ�� x MAX_ARRAY_SIZE ��ŭ�� ������ �����, 
		// �װ��� �ּҸ� temp�� �ִ´�.
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else	// a�� ����Ű�� ���� NULL�� �ƴ� ���. �迭�� �����ϴ� ���
		temp = *a;	// temp�� a�� ����Ű�� ���� ����ִ� �ּҸ� �ִ´�.

	for(int i = 0; i < MAX_ARRAY_SIZE; i++)	// MAX_ARRAY_SIZE�� �ݺ�
		temp[i] = rand() % MAX_ARRAY_SIZE;	// �������� �迭�� ������ ����

	return 0;
}

int freeArray(int *a)	// �迭 ����
{
	if(a != NULL)	// a�� NULL�� �ƴ� ���. �迭�� �����ϴ� ���
		free(a);	// a ����

	return 0;
}

void printArray(int *a)	// �迭 ���
{
	if (a == NULL)	// a�� NULL�� ���. �迭�� �������� �ʴ� ��� 
	{
		printf("nothing to print.\n");	// ����� ���� ���ٴ� ���� ���
		return;
	}

	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);					// �迭 �ε��� ���
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);					// �迭 �� ���
	printf("\n");
}


int selectionSort(int *a) 	// ��������
{
	int min;			// �ּڰ� ������ int�� ���� min
	int minindex;		// �ּڰ��� �ε��� ������ int�� ���� minindex		

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ���� �� �迭 ���

	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;	// minindex�� i�� ���� �ִ´�.
		min = a[i];		// min�� a[i]�� ���� �ִ´�.
		for(int j = i+1; j < MAX_ARRAY_SIZE; j++)	
		// i��° �ε��� ������ �͵�� �񱳸� �����ϸ鼭 �ּڰ��� �ּڰ��� �ε����� ã�´�.
		{
			if (min > a[j])	// min�� a[j]���� ū ���.
			{
				min = a[j];		// min�� a[j]�� ���� �ִ´�.
				minindex = j;	// minindex�� j�� �ִ´�.
			}
		}
		// ������ ã�� ���ο� �ּڰ��� �ּڰ��� �ε����� ������Ʈ�Ѵ�.
		a[minindex] = a[i];	// a[minindex]�� a[i]�� ���� �ִ´�.
		a[i] = min;	// a[i]�� min�� ���� �ִ´�.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	// ���� �� �迭 ���

	return 0;
}

int insertionSort(int *a)	// ��������
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	// ���� �� �迭 ���

	for(i = 1; i < MAX_ARRAY_SIZE; i++)	
	// 0��° �ε����� �ִ� ���� ���ĵ� ������ ����ϹǷ� i�� 1���� ����
	{
		t = a[i];	// t�� a[i]�� ���� �ִ´�.
		j = i;		// j�� i�� ���� �ִ´�.
		while (a[j-1] > t && j > 0)	
		//  ���Ե� �� t�� a[j-1]�� ������ �۰�, j�� 0���� ū ��쿡 �ݺ�
		// ���ĵ��� ���� �κп��� �Ͼ�� ���̴�.
		{
			a[j] = a[j-1];	// a[j]�� a[j-1]�� �ִ´�.
			j--;			// j�� 1 ����
		}
		a[j] = t;	// a[j]�� t�� �ִ´�.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	// ���� �� �迭 ���

	return 0;
}

int bubbleSort(int *a)	// ��������
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	// ���� �� �迭 ���

	for(i = 0; i < MAX_ARRAY_SIZE; i++)	// MAX_ARRAY_SIZE ũ�⸸ŭ �ݺ�
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)	// MAX_ARRAY_SIZE ũ�⸸ŭ �ݺ�
		{
			if (a[j-1] > a[j])	// a[j-1]�� a[j]���� ū ���
			{
				t = a[j-1];		// t�� a[j-1]�� ���� �ִ´�.
				a[j-1] = a[j];	// a[j-1]�� a[j]�� ���� �ִ´�.
				a[j] = t;		// a[j]�� t�� ���� �ִ´�.
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	// ���� �� �迭 ���

	return 0;
}

int shellSort(int *a)	// ������
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	// ���� �� �迭 ���

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // h�� �κ������� ������ �Ǵ� ����
	/* h�� MAX_ARRAY_SIZE / 2 �� ���� �ִ´�. h�� 1/2�� �پ���. 
	�� ���� h�� 0���� ū ��쿡�� �ݺ� */
	{
		for (i = 0; i < h; i++)	// h�� ũ�� ��ŭ �ݺ�
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			/* j�� i+h�� ���� �ִ´�. �� �� ������ �� �� j�� j+h�� ���� �ִ´�.
			�� ���� j�� MAX_ARRAY_SIZE ũ�⺸�� ���� ��쿡�� �ݺ� */
			{
				v = a[j];	// v�� a[j]�� ���� �ִ´�.
				k = j;		// k�� j�� ���� �ִ´�.
				while (k > h-1 && a[k-h] > v)
				// k�� h-1 ���� ũ�� a[k-h]�� v���� ū ��쿡 �ݺ�
				{
					a[k] = a[k-h];	// a[k]�� a[k-h]�� ���� �ִ´�.
					k -= h;	// k�� k-h�� ���� �ִ´�.
				}
				a[k] = v;	// a[k]�� v�� �ִ´�.
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);	// ���� �� �迭 ���

	return 0;
}

int quickSort(int *a, int n)	// ������
{
	int v, t;	
	int i, j;

	if (n > 1)	// n�� 1���� ū ���
	{
		v = a[n-1];	// v�� a[n-1]�� ���� �ִ´�. v�� �����Ŀ����� pivot�̴�.
		i = -1;		// i�� -1�� �ʱ�ȭ
		j = n - 1;	// j�� n-1�� �ִ´�.

		while(1)
		{
			while(a[++i] < v);	
			/* i�� 1�� ���� ��, a[i]�� v���� ���� ��쿡 �ݺ� 
			pivot���� ū �� ã�� ���� */
			while(a[--j] > v);	
			/* j�� 1�� �� ��, a[j]�� v���� ū ��쿡 �ݺ� 
			pivot���� ���� �� ã�� ���� */

			if (i >= j) break;	// i�� j �̻��� ��� Ż��

			/* ������ ã�� pivot�� ���ʿ��� pivot���� ū ���� 
			pivot�� �����ʿ��� pivot���� ���� ������ �ڸ��� �ٲ۴�. */
			t = a[i];		
			a[i] = a[j];
			a[j] = t;
		}

		/* pivot���� ū ���� �ε����� pivot���� ���� ���� �ε������� ū ���.
		i, j �ε��� Ž���� ������ ��쿡 ����Ǵ� �κ�.
		pivot���� ū ���� ���� ������ �ڸ��� �ٲ۴�. */

		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); // pivot ���� �߽����� ���� �κ��� ������� ����
		quickSort(a+i+1, n-i-1); // pivot ���� �߽����� ������ �κ��� ������� ����
	}

	return 0;
}

int hashCode(int key) // �ؽ� �ڵ� ����
{
   return key % MAX_HASH_TABLE_SIZE; // �Է¹��� key�� MAX_HASH_TABLE_SIZE�� ���� ������ ��ȯ
}

int hashing(int *a, int **ht)	// �迭 a�� ���� hash table ����
{
	int *hashtable = NULL;	// int ���� ���� ������ hashtable�� NULL�� �ִ´�.

	if(*ht == NULL)	// ht�� NULL�� ���
	{
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		/* �޸��� Heap ������ 4����Ʈ * MAX_ARRAY_SIZE ��ŭ�� ũ�⸦ �����,
		�װ��� �ּҸ� hashtable�� �ִ´�.

		*ht = hashtable;  
		/* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} 
	else	// ht�� NULL�� �ƴ� ��� 
	{
		hashtable = *ht;	
		// hashtable�� ht�� ����Ű�� ���� ����ִ� �ּҸ� �ִ´�.
		// ���� �ִ� �ؽ����̺��� ��Ȱ���ϴ� ���̴�.
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)	// MAX_HASH_TABLE_SIZE ũ�� ��ŭ �ݺ�
		hashtable[i] = -1;	// hashtable[i]�� -1�� �ʱ�ȭ

	int key = -1;		// key -1�� �ʱ�ȭ
	int hashcode = -1;	// hashcode -1�� �ʱ�ȭ
	int index = -1;		// index -1�� �ʱ�ȭ
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)	// MAX_ARRAY_SIZE ũ�� ��ŭ �ݺ�
	{
		key = a[i];					// key�� a[i]�� ���� �ִ´�.
		hashcode = hashCode(key);	
		// hashcode�� hashCode(key)�� ����� ���� �ؽ��ڵ带 �ִ´�.
	
		if (hashtable[hashcode] == -1)
		// hashtable[hashcode]�� -1�� ���. �ٸ� key�� ������� ���� ����
		{
			hashtable[hashcode] = key;	// hashtable[hashcode]�� key�� �ִ´�.
		} 
		else // hashtable[hashcode]�� -1�� �ƴ� ���. �ٸ� key�� ����ִ� ����
		// �浹 �߻�
		{
			index = hashcode;	// index�� hashcode�� ���� �ִ´�.

			while(hashtable[index] != -1)
			// hashtable[index] �� -1�� �ƴ� ��� �ݺ�
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/* index�� index�� 1�� ���ϰ� �� ����� 
				MAX_HASH_TABLE_SIZE�� ������ ���� �������� �ִ´�.*/
			}
			
			// key�� ���� �� �ִ� ������ ã�� ����
			hashtable[index] = key; // hashtable[index]�� key�� ���� �ִ´�.
		}
	}

	return 0;
}

int search(int *ht, int key)	// �ؽ� ���̺��� key�� ã�� �ؽ� ���̺��� �ε��� ��ȯ
{
	int index = hashCode(key);	
	// index�� hashCode(key)�� ����� �����Ǵ� �ؽ��ڵ带 �ִ´�.

	if(ht[index] == key)	// ht[index]�� ���� �Է¹��� key�� ���� ���
		return index;	// index ��ȯ

	while(ht[++index] != key)	// ht[++index]�� �Է¹��� key�� �ƴ� ��쿡 �ݺ�
	{
		index = index % MAX_HASH_TABLE_SIZE;
		// index�� index�� MAX_HASH_TABLE_SIZE�� ������ ���� �������� �ִ´�.
	}

	return index;	//  �ε��� ��ȯ
}