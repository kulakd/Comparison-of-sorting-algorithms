#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

typedef struct sort
{
    int comparison;
    int modification;
}sortPerf;
    // Methodology:
    // Each access to a cell in an array increases the individual counter by 1.
    // - Swapping two elements in an array together increases the modification counter by 2
    // - Comparing two array elements with each other increases the comparison counter by 2

void Bubble(int array[],const int size,sortPerf *measurement)
{
	int i,j;
    int tmp;
    for(i=0;i<size-1;i++)
    {
        for(j=0;j<size-i-1;j++)
        {
            if(array[j]>array[j+1])
            {
                tmp = array[j+1];
                array[j+1] = array[j];
                array[j] = tmp;
                measurement->modification+=2;
            }
            measurement->comparison+=2;
        }   
    }       
}

void Insertion(int array[],const int size, sortPerf *measurement)
{
    int i,j,tmp;
    for(i=1;i<size;i++)
    {
        if(array[i]<array[0])
        {
            measurement->comparison+=2;
            tmp = array[0];
            array[0] = array[i];
            measurement->modification+=1;
        }
        else
        {
            measurement->comparison+=2;
            tmp = array[i];
        }
        for(j=i-1; tmp<array[j];j--)
        {
            measurement->comparison++;
            array[j+1] = array[j];
            measurement->modification++;
        }
        array[j+1] = tmp;
        measurement->modification++;
    }
}

void Shell(int array[],const int size, sortPerf *measurement)
{
    int i, j, interval, tmp;
    // We assume that the interval is half the size of the array
    for(interval=size/2;interval>0;interval/=2)
    {
        for(i=interval;i<size;i++)
        {
            tmp = array[i];
            for(j=i;j>=interval;j-=interval)
            {
                if(tmp < array[j-interval])
                {
                    measurement->comparison++;
                    array[j] = array[j-interval];
                    measurement->modification++;
                }
                else
                {
                    measurement->comparison++;
                    break;
                }
            }
            array[j] = tmp;
            measurement->modification++;
        }
    }
}

int Search(int array[], int start, int end, sortPerf *measurement) 
{    
    // we choose the last element as our point
    int change = array[end];
    int i = (start-1);
    int tmp,j;
    for (j=start;j<end;j++)
    {
        if (array[j] <= change) 
        { 
            i++;
            // replacment
            tmp=array[i];
            array[i] = array[j];
            array[j]=tmp;
            measurement->modification+=2;
        }
        measurement->comparison++;
  }
    // replacment
    tmp=array[i+1];
    array[i+1] = array[end];
    array[end]=tmp;
    measurement->modification+=2;
    return (i + 1); // we return the value by one to the right
}

void QS(int array[], int start, int end, sortPerf *measurement)
{
    if (start < end) 
    {
        // We choose a place in the array, smaller values ​​go to the left and larger values ​​to the righ
        int change = Search(array,start,end,measurement);
        // left side
        QS(array,start,change-1,measurement);    
        // right side
        QS(array,change+1,end,measurement);
    }
}

bool FINISH(int array[], const int size, sortPerf *measurement)
{
	int i;
    for(i=0;i<size;i++)
    {
        if(array[i]>array[i+1])
        {
            measurement->comparison++;
            return false;
        }
        measurement->comparison++;
    }
    return true;
}

void copyArr(int from[],int whereto[],const int size)
{
	int i;
    for(i=0;i<size;i++)
        whereto[i]=from[i];
}

void showArr(int array[], const int size)
{
	int i;
    for(i=0;i<size;i++)
        printf("%d\n",array[i]);
}

int Random(int min, int max)
{ 
	return (rand()%(max-min+1))+min; 
}

void show_data(sortPerf measurement[], const int ite, FILE *xyz)
{
    long int minMod = measurement[0].modification;
    long int maxMod = measurement[0].modification;
    long int minCom = measurement[0].comparison;
    long int maxCom = measurement[0].comparison;
    long int sumMod = 0;
    long int sumCom = 0;
	int i;
    for(i=0;i<ite;i++)
    {
        sumMod += measurement[i].modification;
        sumCom += measurement[i].comparison;
        
        if(measurement[i].modification > maxMod)
			maxMod = measurement[i].modification;
        if(measurement[i].modification < minMod)
			minMod = measurement[i].modification;
        if(measurement[i].comparison > maxCom)
			maxCom = measurement[i].comparison;
        if(measurement[i].comparison < minCom)
			minCom = measurement[i].comparison;
    }
    double avgMod =(sumMod*1.0)/(ite*1.0);
    double avgCom =(sumCom*1.0)/(ite*1.0);
    printf("Comparisons:      (MAX | MIN | AVG):   %ld | %ld | %.2lf\n",maxCom,minCom,avgCom);
    fprintf(xyz,"Comparisons:      (MAX | MIN | AVG):   %ld | %ld | %.2lf\n",maxCom,minCom,avgCom);
    printf("Modifications:   (MAX | MIN | AVG):   %ld | %ld | %.2lf\n",maxMod,minMod,avgMod);
    fprintf(xyz,"Modifications:   (MAX | MIN | AVG):   %ld | %ld | %.2lf\n",maxMod,minMod,avgMod);
}
