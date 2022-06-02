#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE 
// 해시 테이블의 크기를 MAX_ARRAY_SIZE로 정의. 충돌을 막기 위해 소수로 하는 것이 좋다.

int initialize(int **a);		// 배열 생성
int freeArray(int *a);			// 배열 해제
void printArray(int *a);		// 배열 출력

int selectionSort(int *a);		// 선택정렬
int insertionSort(int *a);		// 삽입정렬
int bubbleSort(int *a); 		// 버블정렬
int shellSort(int *a);			// 셸정렬
int quickSort(int *a, int n);	// 퀵정렬

int hashCode(int key);	// 해시 코드 생성

int hashing(int *a, int **ht);	// 배열 a에 대한 hash table 생성

int search(int *ht, int key); // 해시 테이블에서 key를 찾아 해시 테이블의 인덱스 반환

int main()
{
	char command;
	int *array = NULL;	
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	int flag = 0;

	srand(time(NULL));
	printf("[-------------------- [복무창] [2021040021] --------------------]\n");
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
			flag = 1;
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			if(flag == 0)
			{
				printf("Please Initialize!\n");
				break;
			}
			selectionSort(array);
			break;
		case 'i': case 'I':
			if(flag == 0)
			{
				printf("Please Initialize!\n");
				break;
			}
			insertionSort(array);
			break;
		case 'b': case 'B':
			if(flag == 0)
			{
				printf("Please Initialize!\n");
				break;
			}
			bubbleSort(array);
			break;
		case 'l': case 'L':
			if(flag == 0)
			{
				printf("Please Initialize!\n");
				break;
			}
			shellSort(array);
			break;
		case 'k': case 'K':
			if(flag == 0)
			{
				printf("Please Initialize!\n");
				break;
			}
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			if(flag == 0)
			{
				printf("Please Initialize!\n");
				break;
			}
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			if(flag == 0)
			{
				printf("Please Initialize!\n");
				break;
			}
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

int initialize(int** a)		// 배열 생성
{
	int *temp = NULL;		// int에 대한 포인터 temp에 NULL을 넣는다.

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) // a가 가리키는 곳이 NULL인 경우. 배열이 없는 경우
	{
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		// 메모리의 Heap 영역에 int형 자료의 크기 x MAX_ARRAY_SIZE 만큼의 공간을 만들고, 
		// 그곳의 주소를 temp에 넣는다.
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else	// a가 가리키는 곳이 NULL이 아닌 경우. 배열이 존재하는 경우
		temp = *a;	// temp에 a가 가리키는 곳에 들어있는 주소를 넣는다.

	for(int i = 0; i < MAX_ARRAY_SIZE; i++)	// MAX_ARRAY_SIZE번 반복
		temp[i] = rand() % MAX_ARRAY_SIZE;	// 랜덤값을 배열의 값으로 저장

	return 0;
}

int freeArray(int *a)	// 배열 해제
{
	if(a != NULL)	// a가 NULL이 아닌 경우. 배열이 존재하는 경우
		free(a);	// a 해제

	return 0;
}

void printArray(int *a)	// 배열 출력
{
	if (a == NULL)	// a가 NULL인 경우. 배열이 존재하지 않는 경우 
	{
		printf("nothing to print.\n");	// 출력할 것이 없다는 문구 출력
		return;
	}

	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);					// 배열 인덱스 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);					// 배열 값 출력
	printf("\n");
}


int selectionSort(int *a) 	// 선택정렬
{
	int min;			// 최솟값 저장할 int형 변수 min
	int minindex;		// 최솟값의 인덱스 저장할 int형 변수 minindex		

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;	// minindex에 i의 값을 넣는다.
		min = a[i];		// min에 a[i]의 값을 넣는다.
		for(int j = i+1; j < MAX_ARRAY_SIZE; j++)	
		// i번째 인덱스 이후의 것들과 비교를 시작하면서 최솟값과 최솟값의 인덱스를 찾는다.
		{
			if (min > a[j])	// min이 a[j]보다 큰 경우.
			{
				min = a[j];		// min에 a[j]의 값을 넣는다.
				minindex = j;	// minindex에 j를 넣는다.
			}
		}
		// 위에서 찾은 새로운 최솟값과 최솟값의 인덱스를 업데이트한다.
		a[minindex] = a[i];	// a[minindex]에 a[i]의 값을 넣는다.
		a[i] = min;	// a[i]에 min의 값을 넣는다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	// 정렬 후 배열 출력

	return 0;
}

int insertionSort(int *a)	// 삽입정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	// 정렬 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)	
	// 0번째 인덱스에 있는 값은 정렬된 것으로 취급하므로 i가 1부터 시작
	{
		t = a[i];	// t에 a[i]의 값을 넣는다.
		j = i;		// j에 i의 값을 넣는다.
		while (a[j-1] > t && j > 0)	
		//  삽입될 값 t가 a[j-1]의 값보다 작고, j가 0보다 큰 경우에 반복
		// 정렬되지 않은 부분에서 일어나는 일이다.
		{
			a[j] = a[j-1];	// a[j]에 a[j-1]을 넣는다.
			j--;			// j는 1 감소
		}
		a[j] = t;	// a[j]에 t를 넣는다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	// 정렬 후 배열 출력

	return 0;
}

int bubbleSort(int *a)	// 버블정렬
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	// 정렬 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)	// MAX_ARRAY_SIZE 크기만큼 반복
	{
		for (j = 0; j < MAX_ARRAY_SIZE-1; j++)	// MAX_ARRAY_SIZE -1 크기만큼 반복
		{
			if (a[j-1] > a[j])	// a[j-1]이 a[j]보다 큰 경우
			{
				t = a[j-1];		// t에 a[j-1]의 값을 넣는다.
				a[j-1] = a[j];	// a[j-1]에 a[j]의 값을 넣는다.
				a[j] = t;		// a[j]에 t의 값을 넣는다.
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	// 정렬 후 배열 출력

	return 0;
}

int shellSort(int *a)	// 셸정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	// 정렬 전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // h는 부분집합의 기준이 되는 간격
	/* h에 MAX_ARRAY_SIZE / 2 의 값을 넣는다. h는 1/2씩 줄어든다. 
	이 일을 h가 0보다 큰 경우에만 반복 */
	{
		for (i = 0; i < h; i++)	// h의 크기 만큼 반복
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			/* j에 i+h의 값을 넣는다. 한 번 루프를 돌 때 j에 j+h의 값을 넣는다.
			이 일을 j가 MAX_ARRAY_SIZE 크기보다 작은 경우에만 반복 */
			{
				v = a[j];	// v에 a[j]의 값을 넣는다.
				k = j;		// k에 j의 값을 넣는다.
				while (k > h-1 && a[k-h] > v)
				// k가 h-1 보다 크고 a[k-h]가 v보다 큰 경우에 반복
				{
					a[k] = a[k-h];	// a[k]에 a[k-h]의 값을 넣는다.
					k -= h;	// k에 k-h의 값을 넣는다.
				}
				a[k] = v;	// a[k]에 v를 넣는다.
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);	// 정렬 후 배열 출력

	return 0;
}

int quickSort(int *a, int n)	// 퀵정렬
{
	int v, t;	
	int i, j;

	if (n > 1)	// n이 1보다 큰 경우
	{
		v = a[n-1];	// v에 a[n-1]의 값을 넣는다. v는 퀵정렬에서의 pivot이다.
		i = -1;		// i를 -1로 초기화
		j = n - 1;	// j에 n-1을 넣는다.

		while(1)
		{
			while(a[++i] < v);	
			/* i에 1을 더한 후, a[i]가 v보다 작은 경우에 반복 
			pivot보다 큰 값 찾는 과정 */
			while(a[--j] > v);	
			/* j에 1을 뺀 후, a[j]가 v보다 큰 경우에 반복 
			pivot보다 작은 값 찾는 과정 */

			if (i >= j) break;	// i가 j 이상인 경우 탈출

			/* 위에서 찾은 pivot의 왼쪽에서 pivot보다 큰 수와 
			pivot의 오른쪽에서 pivot보다 작은 수끼리 자리를 바꾼다. */
			t = a[i];		
			a[i] = a[j];
			a[j] = t;
		}

		/* pivot보다 큰 값의 인덱스가 pivot보다 작은 값의 인덱스보다 큰 경우.
		i, j 인덱스 탐색이 엇갈린 경우에 실행되는 부분.
		pivot보다 큰 값과 작은 값끼리 자리를 바꾼다. */

		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); // pivot 값을 중심으로 왼쪽 부분을 재귀적을 정렬
		quickSort(a+i+1, n-i-1); // pivot 값을 중심으로 오른쪽 부분을 재귀적을 정렬
	}

	return 0;
}

int hashCode(int key) // 해시 코드 생성
{
   return key % MAX_HASH_TABLE_SIZE; // 입력받은 key를 MAX_HASH_TABLE_SIZE로 나눈 나머지 반환
}

int hashing(int *a, int **ht)	// 배열 a에 대한 hash table 생성
{
	int *hashtable = NULL;	// int 형에 대한 포인터 hashtable에 NULL을 넣는다.

	if(*ht == NULL)	// ht가 NULL인 경우
	{
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		/* 메모리의 Heap 영역에 4바이트 * MAX_ARRAY_SIZE 만큼의 크기를 만들고,
		그곳의 주소를 hashtable에 넣는다. */
		*ht = hashtable;  
		/* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} 
	else	// ht가 NULL이 아닌 경우 
	{
		hashtable = *ht;	
		// hashtable에 ht가 가리키는 곳에 들어있느 주소를 넣는다.
		// 원래 있던 해시테이블을 재활용하는 것이다.
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)	// MAX_HASH_TABLE_SIZE 크기 만큼 반복
		hashtable[i] = -1;	// hashtable[i]를 -1로 초기화

	int key = -1;		// key -1로 초기화
	int hashcode = -1;	// hashcode -1로 초기화
	int index = -1;		// index -1로 초기화
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)	// MAX_ARRAY_SIZE 크기 만큼 반복
	{
		key = a[i];					// key에 a[i]의 값을 넣는다.
		hashcode = hashCode(key);	
		// hashcode에 hashCode(key)의 결과로 나온 해시코드를 넣는다.
	
		if (hashtable[hashcode] == -1)
		// hashtable[hashcode]가 -1인 경우. 다른 key가 들어있지 않은 상태
		{
			hashtable[hashcode] = key;	// hashtable[hashcode]에 key를 넣는다.
		} 
		else // hashtable[hashcode]가 -1이 아닌 경우. 다른 key가 들어있는 상태
		// 충돌 발생
		{
			index = hashcode;	// index에 hashcode의 값을 넣는다.

			while(hashtable[index] != -1)
			// hashtable[index] 가 -1이 아닌 경우 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/* index에 index에 1을 더하고 그 결과에 
				MAX_HASH_TABLE_SIZE를 나눴을 때의 나머지를 넣는다.*/
			}
			
			// key를 넣을 수 있는 공간을 찾은 상태
			hashtable[index] = key; // hashtable[index]에 key의 값을 넣는다.
		}
	}

	return 0;
}

int search(int *ht, int key)	// 해시 테이블에서 key를 찾아 해시 테이블의 인덱스 반환
{
	int index = hashCode(key);	
	// index에 hashCode(key)의 결과로 생성되는 해시코드를 넣는다.

	if(ht[index] == key)	// ht[index]의 값이 입력받은 key와 같은 경우
		return index;	// index 반환

	while(ht[++index] != key)	// ht[++index]가 입력받은 key가 아닌 경우에 반복
	{
		index = index % MAX_HASH_TABLE_SIZE;
		// index에 index를 MAX_HASH_TABLE_SIZE로 나눴을 때의 나머지를 넣는다.
	}

	return index;	//  인덱스 반환
}