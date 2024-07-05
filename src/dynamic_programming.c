#include <stdio.h>
#include <time.h>

struct Object
{
    int size;
    int value;
};

void readFile(const char* path, int* capacity, struct Object* objArr, int* size);

void printVector(int vector, const struct Object* objArr, int size);


int main(void)
{
    clock_t start, end;
    start = clock();
    int capacity;
    struct Object objArr[100];
    int arrSize;
    readFile("C:\\Users\\Jan\\JetBrainsProjects\\CLionProjects\\NAI\\NAI_Knapsack\\knapsack_data\\1", &capacity, objArr,
             &arrSize);
    int solArray[arrSize + 1][capacity + 1];
    for (int i = 0; i <= arrSize; i++)
    {
        solArray[i][0] = 0;
    }
    for (int j = 0; j <= capacity; j++)
    {
        solArray[0][j] = 0;
    }
    // Filling solution array
    for (int i = 1; i <= arrSize; i++)
    {
        for (int j = 1; j <= capacity; j++)
        {
            int previous = solArray[i - 1][j];
            int reducedCapacity = j - objArr[i - 1].size;
            if (reducedCapacity < 0)
            {
                solArray[i][j] = previous;
            } else
            {
                int candidate = solArray[i - 1][reducedCapacity] + objArr[i - 1].value;
                solArray[i][j] = candidate > previous ? candidate : previous;
            }
        }
    }
    // Reconstructing the solution
    int solutionVector = 0b0;
    for (int i = arrSize, j = capacity; i > 0 && j > 0; i--)
    {
        if (solArray[i][j] != solArray[i - 1][j])
        {
            j = j - objArr[i-1].size;
            int mask = 0b1 << (i - 1);
            solutionVector = solutionVector | mask;
        }
    }
    printVector(solutionVector, objArr, arrSize);
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

void printVector(int vector, const struct Object* objArr, int size)
{
    char vectorStr[size + 1];
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
