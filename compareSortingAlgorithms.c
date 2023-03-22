/*
Gary Orsargos
ga080892
3/21/2023
Submission for "Assignment 4"
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

//used during the merge sort algorithm
void merge(int arr[], int left, int middle, int right) {
  //set sizes for the different parts of the subarray (left and right)
  int sizeL = middle - left + 1;
  int sizeR = right - middle;
  //allocate memory for subarrays, then insert the items to their respective array
  int x, y, z;
  int *rightArr = (int *)malloc(sizeR * sizeof(int));
  int *leftArr = (int *)malloc(sizeL * sizeof(int));
  extraMemoryAllocated += sizeof(int)*2;
  for (y = 0; y < sizeR; y++)
    rightArr[y] = arr[middle+y+1];
  for (x = 0; x < sizeL; x++)
    leftArr[x] = arr[left + x];
  int leftCount = 0, rightCount = 0, merged = left;
  //merge the two new subarrays back together in ascending number order
  while (rightCount < sizeR && leftCount < sizeL) {
    if (leftArr[leftCount] <= rightArr[rightCount]) {
      arr[merged] = leftArr[leftCount];
      leftCount++;
    } else {
      arr[merged] = rightArr[rightCount];
      rightCount++;
    }
    merged++;
  }
  //if the two arrays are not the same length, these loops will fill pData array with the remaining data
  while (leftCount < sizeL) {
    arr[merged] = leftArr[leftCount];
    leftCount++;
    merged++;
  }
  while (rightCount < sizeR) {
    arr[merged] = rightArr[rightCount];
    rightCount++;
    merged++;
  }
  //free memory
  free(rightArr);
  free(leftArr);
}
// implement merge sort (the above function is also used in this implementation)
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int left, int right) {
  if (left < right) {
    int middle = (left + right)/2;
    mergeSort(pData, middle + 1, right);
    mergeSort(pData, left, middle);
    merge(pData, left, middle, right);
  }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	for (int i = 1; i < n; i++) {
    int x = pData[i], j = i - 1;
    while (x < pData[j] && j >= 0) {
      pData[j + 1] = pData[j];
      j--;
    }
    pData[j + 1] = x;
  }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int sorted = 0, temp;
	while(!sorted){
		sorted = 1;
		for(int i = 0; i < n-1; i++){
			if(pData[i]>pData[i+1]){
				sorted = 0;
				temp = pData[i];
				pData[i] = pData[i+1];
				pData[i+1] = temp;
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int count = 0, smallestIndex = 0, temp;
	for(int i = 0 ; i < n; i++){
		smallestIndex = i;
		for(int j = i; j < n; j++){
			if(pData[smallestIndex] > pData[j])
				smallestIndex = j;
		}
		temp = pData[i];
		pData[i] = pData[smallestIndex];
		pData[smallestIndex] = temp;
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		int *inArr = *ppData;
		for(int i = 0; i < dataSz; i++){
			fscanf(inFile, "%d", &(inArr[i]));
		}
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}