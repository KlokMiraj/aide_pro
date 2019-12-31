#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <sys/stat.h>
#include <time.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. Your personalised data set is included in the
  code. 
******************************************************************************/
int n_passwords = 4;

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


/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the 
 start of the line. Note that one of the most time consuming operations that 
 it performs is the output of intermediate results, so performance experiments 
 for this kind of program should not include this. i.e. comment out the printfs.
*/

void crack(char *salt_and_encrypted){
  int x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          //printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

int main(int argc, char *argv[]){

  struct timespec start, finish;   
  long long int time_elapsed;
  int i;

  clock_gettime(CLOCK_MONOTONIC, &start);  

  for(i=0;i<n_passwords;i<i++) {
    
    
    crack(encrypted_passwords[i]);
    
  }

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lld ns or %0.9lfs\n\n", time_elapsed,
                                         (time_elapsed/1.0e9));

  return 0;
}
