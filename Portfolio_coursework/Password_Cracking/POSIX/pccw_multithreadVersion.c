#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <crypt.h>

/****************************************************************************
  Compile and run with:
    cc -o  pccw_multithreadVersion pccw_multithreadVersion.c -pthread -lcrypt
    ./pccw_multithreadVersion
  
***************************************************************************/


/*  a mutex lock has been defined with global scope so that it could be used 
by both of the threads */
pthread_mutex_t mutex_lock;

int n_passwords = 4; 


/* variable for counting solutions examined by two threads */
int solution_counter;
	
	
/* those variables are made global so that each thread can access them	*/
char *saltAndEncryptedText;
char salt[7];    
char *enc;  


/***** 4 hash value of password supplied *******/
char *encrypted_passwords[] = {
  "$6$KB$36REBSFzq1/dui1N6SgVpJNWbH7.H09nEmDF84hZhfeauI13ShDyaMT/d1tPMVh35NJKKkQrT6OIYDS9VLrIY0",
  "$6$KB$y.PArc/oPKxP9VZrVz/PKh1YnIO5Y17fKuUf2fzN/CY9nsu8pM1A1sL1DFqP6opCSrghErWUmBWXeYxzV/yO51",
  "$6$KB$dzMbKiZard0rTfPtzDNxInzgsgYk.xYdOMGPWk1ZH0u30ySyP7XaQWhcX/MkoLXjRsJrAAqY3GqB7xPOnboJc.",
  "$6$KB$EboVTynH7cHCTdC3B.gP2Tq4yF/rJhziZlrhoUCq.TWT/3spujem0kTzlktwP6WJB/sx5DsbMeKzabWAEAsx1/"
};  



int time_difference(struct timespec *start, 
                    struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}



/* A function to extract substring from a src string to dest string starting 
from index 'start' upto index 'length'	*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}




/*  the thread function to decrypt hash and compared it against the hash value supplied
the function makes comparsion brute-forcely. the function check for password starting form initial 
letter 'A' to 'M'  */

void *crackA2M(){

 int x, y, z;     // Loop counters
 char plain[7];   

 for(x='A'; x<='M'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
	sprintf(plain, "%c%c%02d", x, y, z); 
	enc = (char *) crypt(plain, salt);

	/* locking critical section of the program */
         pthread_mutex_lock(&mutex_lock);
          
          solution_counter++;
         
         /* releasing lock from  critical section of the program */
         pthread_mutex_unlock(&mutex_lock);
	
	if(strcmp(saltAndEncryptedText, enc) == 0){
	  printf("#%-8d%s %s (computed by thread 1 : ID %ld)\n", solution_counter, plain, enc,pthread_self());
	} else {
	  //printf("%-8d%s %s (computed by thread %ld)\n", count, plain, enc,pthread_self());
	}
      }
    }
  }

  pthread_exit(NULL);
 }




/*** the purpose of this function is same as that of 'crackA2M' except that it checks for passwords 
starting from 'N' to 'Z'  **/

void *crackN2Z(){

 int x, y, z;     // Loop counters
 char plain[7];   

 for(x='N'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
	sprintf(plain, "%c%c%02d", x, y, z); 
	enc = (char *) crypt(plain, salt);
	
         /* locking critical section of the program */
         pthread_mutex_lock(&mutex_lock);
          
          solution_counter++;
         
         /* releasing lock from  critical section of the program */
         pthread_mutex_unlock(&mutex_lock);
	

	if(strcmp(saltAndEncryptedText, enc) == 0){
	  printf("#%-8d%s %s (computed by thread 2 : %ld)\n", solution_counter, plain, enc,pthread_self());
	} else {
	  //printf("%-8d%s %s (computed by thread %ld)\n", count, plain, enc,pthread_self());
	}
      }
    }
  }

  pthread_exit(NULL);
 }




/* a function to implement 2 threads */

void crack(char *salt_and_encrypted){

  solution_counter=0;
  saltAndEncryptedText=salt_and_encrypted;

  pthread_t t1, t2;

  substr(salt, salt_and_encrypted, 0, 6);

  if(pthread_create(&t1, NULL, crackA2M, NULL)!=0){
    printf("Sorry, Thread could not be created !\n");
    exit(EXIT_FAILURE);
  }
  
  if(pthread_create(&t2, NULL, crackN2Z, NULL)!=0){
    printf("Sorry, Thread could not be created !\n");
    exit(EXIT_FAILURE);
  }

  pthread_join(t1, NULL); 
  pthread_join(t2, NULL);
  printf("%d solutions explored\n",solution_counter); //shows total number of comparsion performed
  }

	

int main(int argc, char *argv[]){
  
struct timespec start, finish;   
long long int time_elapsed;
int i;

clock_gettime(CLOCK_MONOTONIC, &start);  


/** initialization of mutex lock with error checking **/

if(pthread_mutex_init(&mutex_lock, NULL)!=0) {
printf("problem with initialising mutex...\nProgram terminating...");
exit(EXIT_FAILURE);
}

for(i=0;i<n_passwords;i<i++) {
crack(encrypted_passwords[i]);
}

/* destroying of the mutex lock at the end */

pthread_mutex_destroy(&mutex_lock);


clock_gettime(CLOCK_MONOTONIC, &finish);
time_difference(&start, &finish, &time_elapsed);
printf("Time elapsed was %lld ns or %0.9lfs\n\n", time_elapsed,
                                 (time_elapsed/1.0e9));

  return 0;
}


