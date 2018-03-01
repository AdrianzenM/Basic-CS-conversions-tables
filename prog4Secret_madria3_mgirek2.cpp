#include <stdio.h>
#include <stdlib.h>      // For file input and output
#include <assert.h>      // For sanity check assertions
#include <ctype.h>       // For character type checking
#include <iostream>
#include <string.h>

using namespace std;

// Global constants
const int MAX_LENGTH = 17424;   // global constant for max input line length
//const char FILE_NAME[] = "cipherOriginal.txt";
const char FILE_NAME[] = "samplecipher.txt";
const char FILE_NAME2[] = "keys.txt";

//-------------------------------------------------------------------------------------- 
// Display name and program information
void displayInfo()
{
    printf("\n");
    printf("Author: Manuel Adrianzen & Maciej Girek          \n");
    printf("Program: #4, Secret      \n");
    printf("TA: Praval Jain, T 3-4 \n");
    printf("March 6, 2016              \n");
    printf("\n");
}
//--------------------------------------------------------------------------------------
void openTextFile( FILE **pCipher, FILE **pKeys)
{
    // Associate the file pointer with the actual file name and try to open it
    *pCipher = fopen( FILE_NAME, "rb");   // open with "r" for "read" access
    *pKeys = fopen( FILE_NAME2,"rb");
	// verify that file open worked
    if (*pCipher == NULL || *pKeys == NULL) {
        printf("Can't open %s. Verify it is in correct location\n", FILE_NAME);
        exit(-1);
    }
}
//-------------------------------------------------------------------------------------
// function to determine the length of of array

int length(char word[]){
    int i = 0;
    for(i = 0;word[i]!='\0';++i);
    return i;
}

//--------------------------------------------------------------------------------------
// reads in cipher and copies txt into array
void displayCipherCount(FILE* pInputFile,char array[]){
    
    int counter = 0; 
    while(fgets(array, MAX_LENGTH,pInputFile) != NULL) {
        // Eliminate the trailing newline character '\n' if there is one on this line.
        // There potentially won't be one on the last line of the file.
       int n = length(array);
       cout<<"\nRead in "<<n<<" cipherText characters.\n\n";
       for(int i = 0; i < n;i++){
            counter++;
        }
    }
}

//----------------------------------------------------------------------------------
// display cipher with choice of width
void readInCipher(FILE* pInputFile,char cipher[],int charPerLine)
{
    int counter = 0; 
    int n; //= length(cipher);
    n=strlen(cipher);
    //iterate through whole cipher
	for(int i = 0; i < n;i++){
            cout<<cipher[i];
            counter++;
            // end line after character count equals width (charPerLine)
            if(counter % charPerLine == 0){
            cout<<"\n";
            }
        }

}

//---------------------------------------------------------------------------------------------
// display keyWords with default width of 81
void displayKeyWords(FILE* pInputFile,char array[],int charPerLine)
{
    int counter = 0; 
    char inputLine[MAX_LENGTH];
    while(fgets(array, MAX_LENGTH,pInputFile) != NULL) {
        // Eliminate the trailing newline character '\n' if there is one on this line.
        // There potentially won't be one on the last line of the file.
       int n = length(array);
       cout<<"\nRead in 3 keyWords, which are:\n";
     
    }
}

//---------------------------------------------------------------------------------------------
//Separate string by single words and populate 2d array with obtained words.
void split(char* word, char words[][25]) {
    int wordLength = length(word);
    int i = 0, j = 0;
    int index;
    //populating rows of 2d array untill reaching space character
    for (index = 0; index < wordLength; index++) {
        if (word[index] != ' ') {
            words[i][j] = word[index];
       
	        j++;
        } else {
        	//when null character is met , jump to next column of 2d array
            words[i][j] = '\0';
            i++;
            j = 0;
        }
        //set a null character at a index wordLength -1
        if (index == wordLength - 1) {
            words[i][j] = '\0';
        }
    }
}

//--------------------------------------------------------------------------------------
//print string contained in 2d array
void print2DWords(char array[20][25])
{
    for(int i =0;i<3;i++){
        printf("%s\n",array[i]);
    }

}

//--------------------------------------------------------------------------------------
// iterates through end of word checks against diagonal and horizontal
// if there is a match return 1 else 0
int wordMatches(char cipher[], char word[], int i, int charPerLine){
	int valid=1;
	for(int j=1; word[j]!='\0';j++){
		if(word[j]!=cipher[i+1*j+j*charPerLine]){ 
			valid=0;
		}
		if(word[j]!=cipher[i+j]){
			valid=0;
		}

	//	valid=1;
	}
	return valid;
}

//---------------------------------------------------------------------------------------
//array that iterates through cipher and checks against keys for match
void compare(char array[20][25], char cipher[], int charPerLine, int userChoice)
{   
    int i,j,k;
    i=j=k=0;
    int match=0;
	if(userChoice==1){
		for(k=0; k< 17424; k++){
			if(cipher[k]!= '\0'){
				//find characters that match the first letter of array 
				if(cipher[k]==array[i][0]){
					match=wordMatches(cipher, array[i], k, charPerLine);
					//if the string matches cipher print the word found
					if(match==1){
						cout<<array[i]<<" ";
						++i;
					}	
				}
			}
		}
	}
	for(k=0; k< 17424; k++){
		
		if(cipher[k]!= '\0'){
			//find characters that match the first letter of array 
			if(cipher[k]==array[i][0]){
				match=wordMatches(cipher, array[i], k, charPerLine);
				//if the string matches cipher print the word found
				if(match==1){
					if(array[i][0]!='\0'){
			//		cout<<"Found '"<<array[0]<<"' diagonaly ";
					cout<<array[i]<<" ";
					++i;
					}
				}	
			}
		}
	}
	
}
					
//-------------------------------------------------------------------------------------
// initializes each element of the 2d array to null
void begin(char words[20][25]){
	for(int i=0; i<20; i++){
		for(int j=0;j<25;j++){
			words[i][j]='\0';
		}
	}
}

//----------------------------------------------------------------------------------
int main()
{
	FILE *pCipher, *pKeys;               // file pointer
    int inputLineNumber = 0;
    int charPerLine;
    char keys[MAX_LENGTH]; //= "quick get going";
    char cipher[MAX_LENGTH];
    char words[20][25];
    int userChoice;
    begin(words); //initialize 2d array to zero
    displayInfo();
    openTextFile( &pCipher, &pKeys);
    
    displayKeyWords(pKeys,keys,81);
    split(keys,words);
    print2DWords(words);
    displayCipherCount(pCipher, cipher);
    cout<<"Choose from the following options:\n";    
    cout<<"	1. Display a particular sized table\n";
    cout<<"	2. Find all matching key word phrases\n"; 
    cout<<"	X. Exit the program \n";
    cout<<"Enter your choice -> ";
    cin >> userChoice;
    
    if(userChoice==1){
		cout<<"Enter the row size: ";
		cin>>charPerLine;
		if(charPerLine >= 13 && charPerLine <= 132){
			readInCipher(pCipher,cipher,charPerLine);
			split(keys,words);
	    cout<<endl;
	    cout<<"Secret message: ";
		compare(words, cipher, charPerLine, userChoice);
			    
	    }else{
	        cout<<"Number of characters must be between 13 and 132"<<endl;
	        
		}
	}
	else if(userChoice==2){
		int count=0;
		for(charPerLine=13; charPerLine<133; charPerLine++){
			if(count!=1){
				cout<<"Secret message: ";
	  	   		split(keys,words);
				compare(words, cipher, charPerLine,userChoice);
				count++;
			}
		}
	}
    return 0;
}

