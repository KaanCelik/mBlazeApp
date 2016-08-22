

#include <stdio.h>
#include <stdlib.h>

char * readFile(char* fileName){

	FILE *f = fopen(fileName, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);

	char *fileContent = malloc(fsize + 1);
	fread(fileContent, fsize, 1, f);
	fclose(f);

	fileContent[fsize] = 0;
	return fileContent;
}

int main(int argc, char **argv) {

	char * resultText;
	int i = 0;
	for (i = 1; i < argc; i++) {
		resultText = readFile(argv[i]);
		printf("%s\r\n", resultText);
		free(resultText);

	}
	return 0;
}

