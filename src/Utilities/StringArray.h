#ifndef STRINGARRAY_H_
#define STRINGARRAY_H_

typedef struct StringArray{
	int count;
	char data[][];
};

void construct(StringArray * strArray);
void destroy(StringArray * strArray);

int getCount();
char * getElement(int i);
void setElement(int i, char* str);

#endif /* STRINGARRAY_H_ */