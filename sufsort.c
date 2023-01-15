#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Used in show_sa function to iterate through SA array of ints
//provides the size of SA in the function because it passes a pointer, not actual value
//no null character at end of array of ints (char array has \0 for null at end)
int n;

//5. FUNCTION TO CREATE SA
void init_sa(int sa[],int n){
	int i;
        for(i=0;i<n;i++){
                sa[i]=i;
        }
}


//7. FUNCTION TO DISPLAY SUFFIX
void show_suf(int i,char string[]){
        int j;
        for(j=0;j<i;j++){
                string[j] = '.';
        }
        printf("%s\n",string);
}


//8. FUNCTION TO SHOW SA 
void show_sa(int sa[],char string[]){
	int i;
	char hold[20];
	for(i=0;i<n;i++){
		strcpy(hold,string);
		show_suf((sa[i]),hold);
	}
}


//9. RECURSIVE INSERTION SORT
void rsort_sa(int sa[], int n, char string[]){
        if(n<=1){
                return;
        }
        rsort_sa(sa,n-1,string);
        char last[n];
        strcpy(last,string+sa[n-1]);
        int j = n-2;
        int final = sa[n-1];
	
	//11. LEXICOGRAPHIC ORDER
        while(j>=0&&(strcmp(string+sa[j],last)>0)){
                sa[j+1]=sa[j];
                j--;
        }
        sa[j+1] = final;
}


//10. BUBBLE SORT 
void bsort_sa(int sa[], int n, char string[]){
        int i,j,temp;
        for(j=0;j<n-1;j++){
                for(i=0;i<n-j-1;i++){
			//11. LEXICOGRAPHIC ORDER
                        if(strcmp(string+sa[i],string+sa[i+1])>0){
                                temp = sa[i];
                                sa[i] = sa[i+1];
                                sa[i+1] = temp;
                        }
                }
        }
}


//---------MAIN METHOD-------------
int main(int argc, char *argv[]){
//1. CHECK COMMAND LINE ARGUMENTS
	if( argc != 2 ) {
     		printf("incorrect number of command line arguments\n");
		return 0;
   	}

//2. CHECK SUBMITTED STRING LENGTH
	if((strlen(argv[1]))<2){
		printf("submitted string too short\n");
		return 0;
	}
	else if((strlen(argv[1]))>20){
		printf("submitted string too long\n");
		return 0;
	}
	
//3. CHECK STRING ONLY CONTAINS A,B,C
	char string[20];
	strcpy(string,argv[1]);
	int z;
	for(z=0;string[z]!='\0';z++){
		if(string[z]>='a' && string[z]<='c'){
		}
		else{
			printf("submitted string is not over the alphabet {a,b,c}\n");
			return 0;
		}
	}

//4. DISPLAY SUBMITTED STRING
	printf("correct string submitted\n");
	printf("submitted string: %s\n", argv[1]);

//6. INITIALIZE 2 SA ARRAYS
	n = strlen(string);
	
	int sa1[n];
	init_sa(sa1,n);
	int sa2[n];
	init_sa(sa2,n);
	
//12. DISPLAY UNSORTED SUFFIXES
	printf("unsorted suffixes:\n");
	show_sa(sa1,argv[1]);

//13. CALL RSORT
	char holdargv[20];
	strcpy(holdargv,argv[1]);
	rsort_sa(sa1,n,argv[1]);
	
//14. DISPLAY RSORTED SUFFIXES
	printf("recursively sorted suffixes:\n");	
	show_sa(sa1,argv[1]);

//15. CALL BSORT
	strcpy(argv[1],holdargv);
	bsort_sa(sa2,n,argv[1]);

//16. DISPLAY BSORTED SUFFIXES
	printf("bubble sorted suffixes:\n");
	show_sa(sa2,argv[1]);

//17. CHECK IF RSORT AND BSORT AGREE
	int agree,indexcheck;
	for(agree=0; agree<n; agree++){
		if(sa1[agree]!=sa2[agree]){
			indexcheck = 0;
			break;
		}
		else{
			indexcheck = 1;
		}
	}	
	if(indexcheck == 1){
		printf("sa1 and sa2 do agree\n");
	}
	else if(indexcheck == 0){
		printf("sa1 and sa2 do not agree\n");
	}
	else{
		printf("something went wrong\n");
	}

	
//END OF PROGRAM
	return 0;
}
