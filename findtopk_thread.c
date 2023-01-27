#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>

#define NUM_THREADS 4

int k;

typedef struct thread_data{
	int tid;
	int data;
} thread_data;

void *func(void *arg){
	thread_data *data = (thread_data *) arg;
	
	int i, j, temp;
	char file_name[5];
	int nums[100000];
	sprintf(file_name, "%d.txt",data->tid);
	FILE *fp = fopen(file_name,"r");
	
	for(i=0; i<100000; i++){
		fscanf(fp,"%d",&nums[i]);
	//	printf("%d\n",nums[i]);
	}
	
	fclose(fp);
	
	for(i=0; i<100000; i++){
		for(j=0; j<100000-1-i; j++){
			if(nums[j]<nums[j+1]){
				temp=nums[j];
				nums[j]=nums[j+1];
				nums[j+1]=temp;
			}
		}
	}
	
/*	for(i=0; i<1000; i++){
		printf("%d\n",nums[i]);
	}*/
	
	data->data = nums[k];
	
	FILE *output=fopen("output.txt","a");
	fprintf(output,"%d\n",data->data);
	
	fclose(output);
	
	printf("hello from thread func, thread id: %d\n", data->tid);
	
	pthread_exit(NULL);

}


int main(){
	clock_t start, end;
	double execution_time;
	start = clock();


	
	int n;
	
	printf("enter n value: ");
	scanf("%d",&n);
	printf("enter k value: ");
	scanf("%d",&k);
	
	pthread_t thr[n];
	
	int i, rc;
	
	thread_data thr_data[n];
	
	
	FILE *fp=fopen("output.txt","w");
	fclose(fp);
	
	for(i=0; i<n; ++i){
		thr_data[i].tid = i;
		
		if((rc=pthread_create(&thr[i], NULL, func, &thr_data[i]))){
			fprintf(stderr, "error: pthread_create, rc: %d\n",rc);
			return EXIT_FAILURE;
		}
	}
	
	for(i=0; i<n; ++i){
		pthread_join(thr[i], NULL);
	}
	
	end = clock();
	execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
	printf("EXECUTION TIME %f\n",execution_time);
	
	return EXIT_SUCCESS;
}
















