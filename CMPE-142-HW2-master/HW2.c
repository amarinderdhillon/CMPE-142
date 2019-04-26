#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubbleSort(int arr1[], int arr2[], int arr3[], int size);
void swap(int *i, int *j);
void bubbleSort_duration(int arr1[], int arr2[], int arr3[], int size);
void arrCopy(int arr1[], int arr2[], int size);

int main(){

	char ch, file_name[30];
   	printf("Enter name of a file:\n");
   	gets(file_name);
 
   	FILE *fp = fopen(file_name, "r"); // open file in read mode
 
   	if (fp == NULL) //throw handler in case file is empty
   	{
      		perror("Error opening the file.\n");
      		exit(EXIT_FAILURE);
   	}
 	
	printf("The contents of %s file are:\n", file_name);
	
	//create variables to temporarily parse data into
	char line[2048];
	int id;
	int arrival;
	int duration;
	
	//create variables to store parsed data into
	int id_arr[100];
	int arrival_arr[100];
	int duration_arr[100];

	int i = 0; //counter for array
	while(fgets(line, sizeof(line), fp) != NULL) //while fgets does not fail to scan a line
	{
    		if(sscanf(line, "%d %d %d", &id, &arrival, &duration) !=3) //If sscanf failed to scan everything from the scanned line
      		{    
         		printf("Bad line detected\n");
         		exit(-1);                   
    		}

		/*Below are test prints to check if file is being properly parsed
        	printf("ID= %d\n", id);
    		printf("Arrival= %d\n", arrival);
    		printf("Duration= %d\n\n", duration);*/
		
		//Saved parsed data to arrays
		id_arr[i] = id;
		arrival_arr[i] = arrival;
		duration_arr[i] = duration;
		i++;
	}
	
//FIFO Scheduling algorithm implemented below
	bubbleSort(arrival_arr, id_arr, duration_arr, i); //sort based on arrival time
	
	//Check to see if arrays are holding the correct data
        for(int x = 0; x < i; x++){
                printf("%d %d %d\n", id_arr[x], arrival_arr[x], duration_arr[x]);
        }
	printf("\nFIFO Scheduling:\n");

	//Output FIFO Start and Finish  Time for each job
	int finish_time[100];  
	int elapsed_time[100];
	int response_time[100];
	for(int x = 0; x < i; x++){
		//Calculating finish time for each process
                printf("ID: %d   Start Time: %d    ", id_arr[x], arrival_arr[x]);
		if(x==0){
                        finish_time[x] = arrival_arr[x] + duration_arr[x];
		}
                else if(finish_time[x-1] < arrival_arr[x]){
                        finish_time[x] = arrival_arr[x] + duration_arr[x];
                }
                else{
                        finish_time[x] = finish_time[x-1] + duration_arr[x];
                }
                printf("Finish time: %d    ",  finish_time[x]);
		
		//Calculating elapsed time for each process
		if(x==0){
                        elapsed_time[x] = arrival_arr[x] + duration_arr[x];
                }
                else if(elapsed_time[x-1] < arrival_arr[x]){
                        elapsed_time[x] = arrival_arr[x] + duration_arr[x];
                }
                else{
                        elapsed_time[x] = elapsed_time[x-1] + duration_arr[x];
                }
                printf("Elapsed time: %d    ", elapsed_time[x]);
		
		//Calculating response time for each process
		if(x == 0){
                        response_time[x] = duration_arr[x] - arrival_arr[x];
                }
                else{
                        response_time[x] = finish_time[x]  - arrival_arr[x];
                }
                printf("Response time: %d\n", response_time[x]);
        }
	
        /*for(int x = 0; x < i; x++){
		if(x == 0){
			response_time[x] = duration_arr[x] - arrival_arr[x];	
		}
		else{
			response_time[x] = response_time[x-1] + duration_arr[x]  - arrival_arr[x];
		}
		printf("Response time: %d\n", response_time[x]);
	}*/

//SJF Scheduling algorithm implemented below (not yet done, just formatting)

	/*Check to see if arrays are holding the correct data
	for(int x = 0; x < i; x++){
		printf("%d %d %d\n", id_arr[x], arrival_arr[x], duration_arr[x]);
	}*/
        bubbleSort(duration_arr, id_arr, arrival_arr, i);
        /*for(int y = 0; y < i; y++)
        {
            printf("%d\t",duration_arr[y]);
            printf("%d\t", id_arr[y]);
            printf("%d\t", arrival_arr[y]); 
        }*/
        int finishSJF[100];
        int elapsedSJF[100];
        int responseSJF[100];
	int marked[100] = {0};
        int start = 0;
        bool status = true;
	
	int minimum = arrival_arr[0];
	int count = 0;
	for(int y = 1; y < i; y++)
	{
		if(arrival_arr[y] < minimum)
		{
			minimum = arrival_arr[y];
			count = y;
		}
	}
        marked[count] = 1;
	finishSJF[0] = arrival_arr[count] + duration_arr[count];
        elapsedSJF[0] = arrival_arr[count] + duration_arr[count];
        responseSJF[0] = duration_arr[count] - arrival_arr[count]; 
	printf("Shortest Job First Scheduling:\n");
        printf("ID: %d\t Arrival Time: %d\t Finish Time: %d\t Elapsed Time: %d\t Response Time: %d\n", id_arr[count], arrival_arr[count], finishSJF[0], elapsedSJF[0], responseSJF[0]);
	
        int finished = finishSJF[0];
	for(int y = 0; y < i; y++)
	{
                //int finished = finishedSJF[y];
		if(arrival_arr[y] <= finishSJF[y] && marked[y] == 0)
		{
			finishSJF[y+1] = finishSJF[y] + duration_arr[y];
			elapsedSJF[y+1] = finishSJF[y] + duration_arr[y];
                        responseSJF[y+1] = finishSJF[y+1] - arrival_arr[y];
                        marked[y] = 1;                               
		}
		else
		{
                        y = y+1;
                        elapsedSJF[y+1] = finishSJF[y-1] + duration_arr[y];
                        finishSJF[y+1] = finishSJF[y-1] + duration_arr[y];
                        responseSJF[y+1] = finishSJF[y+1] - arrival_arr[y];
                        /*printf("ID NEXT: %d\n", id_arr[y+1]);
			printf("%d\n", finishSJF[y]);
               		printf("%d\n", arrival_arr[y]);
                        */
                        /*while(finishSJF[y] != arrival_arr[y])
                        {
			    finishSJF[y] = finishSJF[y] + 1;
                            printf("%d\n", finishSJF[y]);
                        }*/
		}

                printf("ID: %d\t Arrival Time: %d\t Finish Time: %d\t Elapsed Time: %d\t  Response Time: %d\n", id_arr[y], arrival_arr[y], finishSJF[y+1], elapsedSJF[y+1], responseSJF[y+1]);
	}
	
        //printf("%d\t %d\t %d", finishSJF[0], elapsedSJF[0], responseSJF[0]);
        /*while(status)
	{
            for(int y = 0; y < i; y++)
	    {

		if(y == 0)
		    {
		       	    finishSJF[y] = arrival_arr[y] + duration_arr[y];
                            finished = finishSJF[y];
			    marked[y] = 1;
		    }
        	    else if(arrival_arr[y] < finished)
	      	    { 
		    }
            } 
	} 
        */

   	fclose(fp); //close file
   	return 0;
}

//All arrays are sorted based on the index of first argument, arr1[]
void bubbleSort(int arr1[], int arr2[], int arr3[], int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size-i-1; j++){
			if(arr1[j] > arr1[j+1])
			{	
				swap(&arr1[j], &arr1[j+1]);
				swap(&arr2[j], &arr2[j+1]);
				swap(&arr3[j], &arr3[j+1]);				
			}
		}
	}	
}

//Bubble sort is re-written so that if the arrival time is the same for two ID's, the duration is used to sort 
void bubbleSort_duration(int arr1[], int arr2[], int arr3[], int size){
        for(int i = 0; i < size; i++){
                for(int j = 0; j < size-i-1; j++){
                        if(arr1[j] == arr1[j+1] && arr3[j] > arr3[j+1]){
                                swap(&arr1[j], &arr1[j+1]);
                                swap(&arr2[j], &arr2[j+1]);
                                swap(&arr3[j], &arr3[j+1]);

                        }
                }
        }
}


void swap(int *i, int *j)
{
    int temp = *i;
    *i = *j;
    *j = temp;
}

void arrCopy(int arr1[], int arr2[], int size){
	for(int i = 0; i < size; i++){
		arr2[i] = arr1[i];
	}
}
