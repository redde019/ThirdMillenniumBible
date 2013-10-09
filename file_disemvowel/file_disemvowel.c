#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define BUF_SIZE 1024

int is_vowel(char c) {
  bool vowel = false;
  if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'){
    vowel = true;
  }
return vowel;
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
  int i;
  int outPosition = 0;
  for(i = 0; i < num_chars; i++){
    if(!(is_vowel(in_buf[i]))){
      out_buf[outPosition] = in_buf[i];
		//printf("%c", out_buf[outPosition]);
      outPosition++;
    }
  }
	//printf("%d", num_chars);
  return (outPosition);
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
 
   

   char* input = malloc(BUF_SIZE);
   char c;
	int i;
   char* output = malloc(BUF_SIZE);
   int chars_num = 0;
	
	while((c = fgetc(inputFile)) != EOF) {
		chars_num++;
		input[i] = c;
		i++;
	}
		

  int n = copy_non_vowels(chars_num, input, output);

  
  //copy_non_vowels(chars_num, input, output);
  //fwrite(output, outputFile);
  
  fwrite(output, sizeof(char), sizeof(BUF_SIZE)+n-4, outputFile);
}

int main(int argc, char *argv[]) {
  //printf("%d\n", argc);
	if(argc == 3){
		FILE *vowelFile = fopen(argv[1], "r");
		FILE *createFile = fopen(argv[2], "wr");
		disemvowel(vowelFile, createFile);
	}
	if(argc == 1){
		disemvowel(stdin, stdout);
	}
    if(argc == 2){
		FILE *vowelFile = fopen(argv[1], "r");
		disemvowel(vowelFile, stdout);
      }
  return 0;
}
