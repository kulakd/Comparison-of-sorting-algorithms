#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h>
#include "sort_algorithm.cpp"

// Program made by kulakd

int main()
{
	FILE *measurement=NULL;
	measurement=fopen("sorting_comparison_measurements.txt","w");
    srand(time(NULL));
    // Randomly Given number of repetition
    const int M = Random(500,1000);
	int j;
    printf("Repetitions M: %d\n\n",M);
    sortPerf BubbleArr[M];
    sortPerf InseertionArr[M];
    sortPerf ShellArr[M];
    sortPerf QSArr[M];
    printf("SORTING, PLEASE WAIT!\nTHIS MAT TAKE UP TO A FEW MINUTES(DEPENDING ON THE AMOUNT OF DATA)");
    for(j=0;j<M;j++)
    {
    	// Random size of array with data
        const int size = Random(900,1000);
        int data[size];
		int i;
        // preparing data
        for( i=0;i<size;i++) 
			data[i] = Random(1,size);
        // ------------------ Bubblesort ------------------
        sortPerf Babel;
        Babel.comparison = 0;
        Babel.modification = 0;
        int *daneBabel = (int*)malloc(size * sizeof(int));
        copyArr(data,daneBabel,size);
        // Sorting
        Bubble(daneBabel,size,&Babel);
        // Free memory and save results
        free(daneBabel); 
        daneBabel=NULL;
        BubbleArr[j].comparison = Babel.comparison;
        BubbleArr[j].modification = Babel.modification;
        
        // ------------------ InsertionSort ------------------
        sortPerf wstaw;
        wstaw.comparison = 0;
        wstaw.modification = 0;
        int *daneWstaw = (int*)malloc(size * sizeof(int));
        copyArr(data,daneWstaw,size);
        // Sorting
        Insertion(daneWstaw,size,&wstaw);
        // Free memory and save results
        free(daneWstaw); 
        daneWstaw = NULL;
        InseertionArr[j].comparison = wstaw.comparison;
        InseertionArr[j].modification = wstaw.modification;

        // ------------------ ShellSort ------------------
        sortPerf shell;
        shell.comparison = 0;
        shell.modification = 0;
        int *daneShell = (int*)malloc(size * sizeof(int));
        copyArr(data,daneShell,size);
     
        // Sorting
        Shell(daneShell,size,&shell);
       
        // Free memory and save results
        free(daneShell); 
        daneShell = NULL;
        ShellArr[j].comparison = shell.comparison;
        ShellArr[j].modification = shell.modification;

        // ------------------ QuickSort ------------------
        sortPerf qs;
        qs.comparison = 0;
        qs.modification = 0;
        int *daneQs = (int*)malloc(size * sizeof(int));
        copyArr(data,daneQs,size);

        // Sorting
        QS(daneQs,0,size-1,&qs);
                
        // Free memory and save results
        free(daneQs); 
        daneQs = NULL;
        QSArr[j].comparison = qs.comparison;
        QSArr[j].modification = qs.modification;
    }
    printf("\nSummary:\n\n");
    fprintf(measurement,"\nSummary:\n\n");
    printf("--------- Bubblesort sorting -------------------------\n");
    fprintf(measurement,"--------- Bubblesort sorting -------------------------\n");
    show_data(BubbleArr,M,measurement);
	printf("\n\n");
	fprintf(measurement,"\n\n");
    printf("--------- InsertionSort Sorting ------------------\n");
    fprintf(measurement,"--------- InsertionSort Sorting ------------------\n");
    show_data(InseertionArr,M,measurement);
	printf("\n\n");
	fprintf(measurement,"\n\n");
    printf("--------- Shellsort sorting ----------------------------\n");
    fprintf(measurement,"--------- Shellsort sorting ----------------------------\n");
    show_data(ShellArr,M,measurement);
	printf("\n\n");
	fprintf(measurement,"\n\n");
    printf("--------- Quicksort Sorting ---------------------------\n");
    fprintf(measurement,"--------- Quicksort Sorting ---------------------------\n");
    show_data(QSArr,M,measurement);
    fclose(measurement);
    return 0;
}
