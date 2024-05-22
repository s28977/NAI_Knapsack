#include <stdio.h>
#include <time.h>

struct Object
{
    int size;
    int value;
};


void visitVector(int* maxVector, int* maxValue, int vector, const struct Object* objectsArr, int arrSize, int capacity);


void readFile(const char* path, int* capacity, struct Object* objArr, int* size);

void printVector(int vector, const struct Object* objArr, int size);

int main(void)
{
    clock_t start, end;
    start = clock();
    int capacity;
    struct Object objArr[100];
    int arrSize;
    readFile("C:\\Users\\Jan\\JetBrainsProjects\\CLionProjects\\NAI\\NAI_Knapsack\\knapsack_data\\8", &capacity, objArr,
             &arrSize);
    int maxVector;
    int maxValue = 0;
    for (int vector = 0b0, lastVector = (0b1 << 30) - 1; vector < lastVector; vector++)
    {
        visitVector(&maxVector, &maxValue, vector, objArr, arrSize, capacity);
    }
    printVector(maxVector, objArr, arrSize);
    end = clock();
    printf("Execution time: %f seconds\n", ((double) (end - start)) / CLOCKS_PER_SEC);
}


void readFile(const char* path, int* pCapacity, struct Object* objArr, int* pArrSize)
{
    FILE* filePtr = fopen(path, "r");
    fscanf(filePtr, "%d", pCapacity);
    *pArrSize = 0;
    for (int tmpSize, tmpValue, i = 0; fscanf(filePtr, "%d %d", &tmpSize, &tmpValue) != EOF; i++, (*pArrSize)++)
    {
        objArr[i].size = tmpSize;
        objArr[i].value = tmpValue;
    }
    fclose(filePtr);
}

void visitVector(int* maxVector, int* maxValue, int vector, const struct Object* objectsArr, int arrSize, int capacity)
{
    int totalSize = 0;
    int totalValue = 0;
    for (unsigned int mask = 0b1, i = 0; i < arrSize; mask = (mask << 1), i++)
    {
        if (vector & mask)
        {
            totalSize += objectsArr[i].size;
            totalValue += objectsArr[i].value;
        }
        if (totalSize > capacity)
        {
            return;
        }
    }
    if (totalValue > *maxValue)
    {
        printVector(vector, objectsArr, arrSize);
        *maxVector = vector;
        *maxValue = totalValue;
    }
}

void printVector(int vector, const struct Object* objArr, int size)
{
    char vectorStr[size+1];
    int totalSize = 0;
    int totalValue = 0;
    for (unsigned int mask = 0b1, i = 0; i < size; mask = (mask << 1), i++)
    {
        if (vector & mask)
        {
            vectorStr[size - 1 - i] = '1';
            totalSize += objArr[i].size;
            totalValue += objArr[i].value;
        } else
        {
            vectorStr[size - 1 - i] = '0';
        }
    }
    printf("%s: size = %d, value = %d\n", vectorStr, totalSize, totalValue);
}
