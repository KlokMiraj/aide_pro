#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <math.h>
#include <time.h>


typedef struct{
	int start;
	int block_size;
	}arguments_t;

/* Since C doesn't allow dynamic operations on array*/
void sli_salt(char *dest,char *src,int start,int len){
memcpy(dest,src + start, len);
	*(dest+len)='\0';
	}

/*decrypt function for bruteforcing the password*/
char decrypt(char *ienc_password,char x,char y){
	char letter_ch[6];
	char salt_slice[7];
	char *enc_check;
	letter_ch[6]='\0';
	int count=0;

	sli_salt(salt_slice,ienc_password,0,6);
	
		for(int fl=x;fl<=y;fl++){
			 letter_ch[0]=fl;
			for(int sl=x;sl<=y;sl++){
				letter_ch[1]=sl;
				for(int tl=x;tl<=y;tl++){
					letter_ch[2]=tl;
					for(int ll=x;ll<=y;ll++){
						letter_ch[3]=ll;	
						for(int ll=0;ll=99;ll++){
						letter_ch[4]=ll;
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
									}
				
								}		
							}
						}
					}
		
					return (!letter_ch);
						}

				/*parallel processing the crack batchjob*/
				//void pass_process(){
					
					
					//}


int main(int argsc,char *argsv[]){
		
/*printf("\n%s\n",argsv[0]);
		printf("\n%d\n",argsc-1);
		for(int i=1;i<argsc;i++){
		printf("argsv[%d]=%s\n",i,argsv[i]);
	return 1;
	}-*/

	if(argsc!=2 || strlen(argsv[1])<9){
	perror("Either Insuffecient Argument or Encrypted passwords not 92 characters long including salt\n");
    	return (EXIT_FAILURE);
	}else{
		//for total time elapsed
		time_t started=time(NULL);
		decrypt(argsv[1],'A','L');
		decrypt(argsv[1],'M','Z');
		double seconds=difftime(time(NULL),started);
		printf("Total time for function execution was in seconds: %lf \t seconds %0.9lfs",seconds,(seconds/0.9e1));	

		//total combination explored
		return 0;
	}


}





