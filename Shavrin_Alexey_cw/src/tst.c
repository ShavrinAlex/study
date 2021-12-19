#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdio.h>
struct Word{
	char *chars;
	int len;
	int size;
};

struct Word *readWord(){
	char *p = malloc(9*sizeof(char));
	int i = 0;
	while (i < 8){
		p[i++] = fgetc(stdin);
	}
	p[i] = '\0';
	//return &(struct Word){p, 8, 9};
	return NULL;
}

void printStruct(struct Word *word){
	struct Word *w = word;
	if (w == NULL){
		printf("NULL");
	}
	else{
		printf("good");
	}
}

int main(){
	//struct Word *w = malloc(sizeof(struct Word));
	//*w = *readWord();
	//if (readWord() == NULL){
	//	fputs("NULL\n", stdout);
	//}
	//printf("%s", w->chars);
	wchar_t s[] = L"3456";
	char c[15];
	c = s;
	printf("%s", c);
	return 0;
}
