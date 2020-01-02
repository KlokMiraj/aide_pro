#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <math.h>
#include <pthread.h>
#include <malloc.h>
#include <time.h>
#define no_th 4 //no_of_threads

typedef struct{
	int init;
	int blocks;
	}vector_args; //for the thread argument

pthread_mutex_t mtx; //mutex decleration
pthread_cond_t conda, condb,condc, condp; //for signaling between the threads
int buffer =0; //Buffer variable for state of mutex

/* Since C doesn't allow dynamic operations on array*/
void sli_salt(char *dest,char *src,int start,int len){
memcpy(dest,src + start, len);
	*(dest+len)='\0';
	}

/*decrypt function for bruteforcing the password*/
void *decrypt(char *ienc_password){
	char letter_ch[5];
	char salt_slice[7];
	char *enc_check;
	letter_ch[5]='\0';
	int count=0;

	sli_salt(salt_slice,ienc_password,0,6);
	
	/*fl,sl,tl,ll refers to first letter, second letter, third letter and last letter respectively*/
		
		for(int fl='a';fl<='m';fl++){
			 letter_ch[0]=fl;
			for(int sl='a';sl<='z';sl++){
				letter_ch[1]=sl;
				for(int tl=0;tl<=99;tl++){
					letter_ch[2]=tl;
					//for(int ll='a';ll<=y;ll++){
						//letter_ch[3]=ll;
					pthread_mutex_lock(&mtx); //scheduling mutex for thread locking 
						
					sprintf(letter_ch, "%c%c%c", fl, sl, tl); 
					enc_check=(char *)crypt(letter_ch,salt_slice);
					count++;
						//file fp=fwrite("'password',fl,'.txt'","w");

						//CHECKING IF  ENCPASSWORD is getting mixed with salt
						if(strcmp(enc_check,ienc_password)==0){
							printf("#%-8d%s %s\n", count, letter_ch, enc_check);
							}
						else{
							printf(" %-8d%s %s\n", count, letter_ch, enc_check);
						//}
					pthread_mutex_unlock(&mtx); //scheduling mutex for thread unlocking
					}		
				}
			}
	}
	pthread_exit(0);
		
	
}


/*parallel processing the crack batchjob*/ 
void process_def(char *args){
	 pthread_t *t = malloc(sizeof(pthread_t) * no_th);
  	 vector_args *a = malloc(sizeof(vector_args) * no_th);
int i=0;
  while(i<no_th){
    a[i].init = i;
    a[i].blocks = no_th;
  i++;
  }
//initializing the thread sequence
	
 void *decrypt(& args); //need to call this from here instead of main and pass the arguments for each threads
  
	pthread_mutex_init(&mtx,0); //initializing the mutex schedueled earlier
	  for(i<no_th;i++;){
    		pthread_create(&t[i], NULL, decrypt, NULL);
  }
//pthread_cond_init(); //for all four threads and their mutual exclusion

  for(i=0;i<no_th;i++){
    pthread_join(t[i], NULL);
  }

//pthread_cond_init(); //for all four threads and their exclusion conclusion
  free(t);
  free(a);

  pthread_mutex_destroy(&mtx);

	//spin lock all of the four threads in a loop after the exclusion!
}
	


int main(int argsc,char *argsv[]){
		

	if(argsc!=2 || strlen(argsv[1])<9){
	perror("Either Insuffecient Argument or Encrypted passwords not 92 characters long including salt\n");
    	return (EXIT_FAILURE);
	}else{
		//for total time elapsed
		time_t started=time(NULL);
		//decrypt(argsv[1],'A','M');
		double seconds=difftime(time(NULL),started);
		printf("Total time for function execution was in seconds: %lf \t seconds %0.9lfs",seconds,(seconds/0.9e1));	

		//total combination explored
		return 0;
	}


}





