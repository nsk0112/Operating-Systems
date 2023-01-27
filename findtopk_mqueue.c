#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <assert.h>
#include <time.h>

int dosya_yaz(int n){
	int no, i;
	for(no=0;no<n;no++){
		char dosya_isim[20];
		sprintf(dosya_isim, "%d.txt",no);
		FILE *fp=fopen(dosya_isim,"w");
		for(i=0;i<10000;i++){
			rand();
			fprintf(fp,"%d ",(rand()));
		}
		fclose(fp);
	}
}



void main(){
	clock_t start, end;
	double execution_time;
	start = clock();


	int n, k;
	int i, j, m, l, temp, get;
	int nums[100000];
	
	printf("enter n value: ");
	scanf("%d",&n);
	printf("enter k value: ");
	scanf("%d",&k);


	mqd_t mqd_wr = mq_open ("/OpenCSF_MQ", O_CREAT | O_EXCL | O_WRONLY,  0600, NULL);
	
	if (mqd_wr == -1)
	{
	    	perror ("mq_open");
	    	exit (1);
	  }
	  
	  
	  for(i=0; i<n; i++){  // dosya sayisi kadar loop
	  	
	  	char file_name[14];
	  	sprintf(file_name, "%d.txt", i);
	  	FILE *fp=fopen(file_name,"r");
	  	
	  	int nums[100000];
	  	int temp, get;
	  	
	  	for(j=0; j<100000; j++){
	  		fscanf(fp,"%d", &nums[j]);
	  	}
	  	
	  	
	  	for(m=0; m<100000; m++){
	  		for(l=0; l<100000-1-m; l++){
	  			if(nums[l]<nums[l+1]){
	  				temp = nums[l];
	  				nums[l]=nums[l+1];
	  				nums[l+1]=temp;
	  			}
	  		}
	  	}
	  	
	  	get=nums[k];
	
	  	char get_str[20];
	  	sprintf(get_str, "%d", get);
	  	
		mq_send (mqd_wr, get_str, 20, 10);
		
	  }
	mq_close (mqd_wr);


	mqd_t mqd2 = mq_open ("/OpenCSF_MQ", O_RDONLY);
	assert (mqd2 != -1);

	
	struct mq_attr attr;
	assert (mq_getattr (mqd2, &attr) != -1);
	
	
	char *buffer = calloc (20, 1);
	assert (buffer != NULL);
	
	FILE *output_file = fopen("output.txt","w");
	int output_list[n];
	
	for(i=0; i<n; i++){
	
		unsigned int priority = 0;
		if ((mq_receive (mqd2, buffer, attr.mq_msgsize, &priority)) == -1){
	  		printf ("Failed to receive message\n");
	  	}
	  	
		else{
	  		printf ("Received : '%s'\n", buffer);
	  		//
	  		sscanf(output_list[n], "%d", &buffer);
	  	}
	  	
	}
	
	for(m=0; m<n; m++){
	  		for(l=0; l<n-1-m; l++){
	  			if(output_list[l]<output_list[l+1]){
	  				temp = output_list[l];
	  				output_list[l]=output_list[l+1];
	  				output_list[l+1]=temp;
	  			}
	  		}
	  	}
	
	
	for(m=0;m<n;m++){
		fprintf(output_file, "%d\n", output_list[m]);
	}
	
	
	fclose(output_file);
	
	 
	free (buffer);
	buffer = NULL;
	mq_close (mqd2);
	
	mq_unlink("/OpenCSF_MQ");
	
	end = clock();
	execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
	printf("EXECUTION TIME %f\n",execution_time);
	
	
	
}
