#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <math.h>
#include <pthread.h>
#include <malloc.h>
#include <time.h>


typedef struct{
	int init;
	int blocks;
	}arguments_t; //for the thread argument

pthread_mutex_t mtx; //mutex decleration
pthread_cond_t conda, condb,condc, condp; //for signaling between the threads
int buffer =0; //Buffer variable to know the state of mutex

/* Since C doesn't allow dynamic operations on array*/
void sli_salt(char *dest,char *src,int start,int len){
memcpy(dest,src + start, len);
	*(dest+len)='\0';
	}

/*decrypt function for bruteforcing the password*/
char decrypt(char *ienc_password,char x,char y){
	char letter_ch[5];
	char salt_slice[7];
	char *enc_check;
	letter_ch[5]='\0';
	int count=0;

	sli_salt(salt_slice,ienc_password,0,6);
	
	//setting up variables for signaling mutex
		/*switch(x){
			case 'A':
				conda=x;
			break;
			case 'G':
				condb=y;
			break;
			case 'O':
				condc=
		}*/
		
		for(int fl=x;fl<=y;fl++){
			 letter_ch[0]=fl;
			for(int sl=x;sl<=y;sl++){
				letter_ch[1]=sl;
				for(int tl=x;tl<=y;tl++){
					letter_ch[2]=tl;
					for(int ll=x;ll<=y;ll++){
						letter_ch[3]=ll;
					pthread_mutex_lock(&mtx); //scheduling mutex for thread locking 
						while(buffer!=0){
							switch(x){
								case 'A':
									pthread_cond_wait(&conda,&mtx);
									buffer=count;
									pthread_cond_signal(&conda);
									pthread_mutex_unlock(&mtx);
								break;
								case 'G':
									pthread_cond_wait(&condb,&mtx);
									buffer=count;
									pthread_cond_signal(&condb);
									pthread_mutex_unlock(&mtx);
								break;
								case 'O':
									pthread_cond_wait(&condc,&mtx);
									buffer=count;
									pthread_cond_signal(&condc);
									pthread_mutex_unlock(&mtx);
								break;
								case 'T':
									pthread_cond_wait(&condp,&mtx);
									buffer=count;
									pthread_cond_signal(&condp);
									pthread_mutex_unlock(&mtx);
								break;
						}
					}
						sprintf(letter_ch, "%c%c%c%c", fl, sl, tl,ll); 
					enc_check=(char *)crypt(letter_ch,salt_slice);
					count++;
						//file fp=fwrite("'password',fl,'.txt'","w");

						//CHECKING IF  ENCPASSWORD is getting mixed with salt
						if(strcmp(enc_check,ienc_password)==0){
							printf("#%-8d%s %s\n", count, letter_ch, enc_check);
							}
						else{
							printf(" %-8d%s %s\n", count, letter_ch, enc_check);
						}
					pthread_mutex_unlock(&mtx); //scheduling mutex for thread unlocking
					}		
				}
			}
	}
		
	return (!letter_ch);
}


/*parallel processing the crack batchjob*/
void* process_def(void* arg){

	/*for(){

 	pthread_mutex_lock(&mtx);
	
	}*/
	
	
	}


int main(int argsc,char *argsv[]){
		

	/*printf("\n%s\n",argsv[0]);
	
	
	//Deal with the escaping character like $$ next time;
	
	//counting the password
		/*int array_count=sizeof(*argsv)/sizeof(argsv[1]);
		printf("%s",argsv[1]);*/
		

	if(argsc!=2 || strlen(argsv[1])<9){
	perror("Either Insuffecient Argument or Encrypted passwords not 92 characters long including salt\n");
    	return (EXIT_FAILURE);
	}else{
		//for total time elapsed
		time_t started=time(NULL);
		decrypt(argsv[1],'A','M');
		double seconds=difftime(time(NULL),started);
		printf("Total time for function execution was in seconds: %lf \t seconds %0.9lfs",seconds,(seconds/0.9e1));	

		//total combination explored
		return 0;
	}


}





