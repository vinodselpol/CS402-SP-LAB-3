#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// Read data from file
float * fetchData(char* datafile, int* xp, int* yp);

// print stats        
void printStats (float arr[], int size, int total_size);

// helper method for sort
void swapValues(float* xp, float* yp);
  
// sort
void sort(float arr[], int n);

// find findMedian
float findMedian(float arr[], int size);

// find findMean
double findMean(float arr[], int size);

//find Standard Deviation
double findStandardDeviation(float arr[], int size);

int main(int argc, char *argv[])
{
    if ( argc != 2 ) 
    {
        
        printf( "usage: %s filename\n", argv[0] );
    }
    else
    {   
        int count = 0;
        int size = 20;
        float* set;

        set = fetchData(argv[1], &count, &size); 
        sort(set, count); 
        printStats(set, count, size);      
    }
}

float * fetchData(char* datafile, int* count, int* size)
{
    int n = 20;
    //allocate memory
    float* set = (float*)malloc(n * sizeof(float)); 
    
     //test for memory allocation
    if (set == NULL) { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    } 
    
    int counter = 0;
    float data = 0;
    FILE *file;
    //read file
    file = fopen(datafile, "r"); 

    char maxSize[100];  
    while (fgets(maxSize, sizeof(maxSize), file))  
    {
        data = strtof(maxSize, NULL);
        set[counter] = data;
        counter++; 
        

        if (counter == n)
        {
            
            n = n*2;
            //allocate memory
            float* temp = (float*)malloc(n * sizeof(float)); 

            //test for memory allocation
            if (temp == NULL) { 
                printf("Memory not allocated.\n"); 
                exit(0); 
            }

            //copy memory
            memcpy(temp, set, n * sizeof(float));
            free(set);
            set = (float*)malloc(n * sizeof(float)); 
            memcpy(set, temp, n * sizeof(float));
            free(temp);
        }
    }
    if (feof(file)) 
    {
        fclose(file);
    } 
    *size = n;
    *count = counter;
    return set;
}

// print stats        
void printStats (float arr[], int n, int total_size)
{
    printf("Results:\n");
    printf("--------------\n");
    printf("Num Values:\t\t%d\n", n);
    printf("mean\t\t\t%lf\n", findMean(arr, n));
    printf("median:\t\t\t%f\n", findMedian(arr, n));
    printf("stddev:\t\t\t%lf\n", findStandardDeviation(arr, n));
    printf("Unused array capacity:\t%d\n\n", (total_size-n));
}

// Swap values
void swapValues(float* xp, float* yp) 
{ 
    float temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// sorting values - insertion sort
void sort(float arr[], int n) 
{ 
    int i, j, min; 
         
    for (i = 0; i < n - 1; i++) { 
        min = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j] < arr[min]) 
                min = j; 
                swapValues(&arr[min], &arr[i]); 
    } 
} 

//find median
float findMedian(float arr[], int size)
{
    float findMedian = 0;
    if(size % 2 == 0)
    {
        findMedian = (arr[(size-1)/2] + arr[size/2])/2.0;
    }
    else
    {
        findMedian = arr[size/2];
    }
    return findMedian;
}

//find mean
double findMean(float arr[], int size)
{
    int counter;
    float sum;
    double average;

    sum = average = 0;
   
    for(counter = 0; counter < size; counter++) 
    {
      sum = sum + arr[counter];
    }
   
    average = (double)sum / size;
    return average;
}

//find Standard Deviation
double findStandardDeviation(float arr[], int size)
{
    int counter;
    float sum;
    double average, findStandardDeviation;

    average = findMean(arr, size); 
   
    for(counter = 0; counter < size; counter++) 
    {
      sum = sum + ((arr[counter] - average) * (arr[counter] - average));
    }
   
    findStandardDeviation = (double) sqrt(sum / size);
    return findStandardDeviation;

}
