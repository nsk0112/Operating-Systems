#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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

int yaprak(int num_child, int k){
	char dosya_isim[8];
	sprintf(dosya_isim, "%d.txt",num_child);
	FILE *fp=fopen(dosya_isim,"r");
	
	int nums[100000], i, j;
	for(i=0; i<100000; i++){
		fscanf(fp, "%d", &nums[i]);
	}
	
	fclose(fp);
	
	int gecici;    	
    		
	for(i=0; i<100000; i++){
        for(j=0; j<100000-1-i; j++){
            if(nums[j] < nums[j+1]){
                gecici = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = gecici;
            }
        }
    }

    char yaz_dosya_isim[8];
    int isim = ((int)num_child)+((int)k);
	sprintf(yaz_dosya_isim, "%d.txt",isim);
	FILE *fp_yaz=fopen(yaz_dosya_isim,"w");
   
	
	fprintf(fp_yaz,"%d",nums[k]);
	
	fclose(fp_yaz);
}


void parent(int children, int k){
	int i, j;
	int liste[children];
		
	for(i=0;i<children;i++){
				
		int send = i+k;
		int get=myread(send);
		
		liste[i]=get;
		
	}	
	
	int gecici;
	
	for(i=0; i<children; i++){
       	 for(j=0; j<children-1-i; j++){
            if(liste[j] < liste[j+1]){
                gecici = liste[j];
                liste[j] = liste[j+1];
                liste[j+1] = gecici;
            }
        }
    }
    
    
    
    FILE *outputfile=fopen("output.txt","w");
    for(i=0;i<children;i++){
    	fprintf(outputfile,"%d\n",liste[i]);
    }
    
    fclose(outputfile);

}

int myread(int num){
	char name[12];
	int get;
	sprintf(name,"%d.txt",num);
	FILE *fp=fopen(name,"r");
	fscanf(fp,"%d", &get);
	
	remove(name);
	
	return get;
}


void agac_olustur(int children, int k){
	
	int pid = fork();
	int pids[children];
	int i;
	
	if(pid>0){ 			
		
		for(i=0;i<children;i++){
			wait(NULL);
			if ((pids[i] = fork()) < 0) {
    				perror("fork");
    				abort();
  			} 
  			
  			else if (pids[i] == 0) {
    				yaprak(i, k);
    				exit(0);
  			}
		}
		
	}
	wait(NULL);
	
	parent(children, k);	
		
}



int main(){

	clock_t start, end;
	double execution_time;
	start = clock();


	int n, k;
	printf("Enter N value (1-5): ");
	scanf("%d",&n);
	printf("Enter k value (1-1000): ");
	scanf("%d",&k);	
	//dosya_yaz(n);			// dosya yazan fonk
	agac_olustur(n,k);		// agaci olusturan fonk
	
	end = clock();
	execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
	printf("EXECUTION TIME %f\n",execution_time);
}




