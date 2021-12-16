#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
#include <string.h>
#include "my_struct.h"


void freeSentence(struct Sentence sent){
	for (struct Word *word = sent.wwords; word < sent.wwords + sent.len; word++){
		free(word -> wchars);	//cleaning memory
	}
	free(sent.wwords);	//cleaning memory
}

void freeText(struct Text *text){
	for (int i = 0; i < text -> len; i++){
		freeSentence(text -> sents[i]);	//cleaning memory
	}
	free(text -> sents);	//cleaning memory
	text -> sents = NULL;
	text -> size = 0;
	text -> len = 0;
}

void removingSentence(struct Text *text, int index){
	freeSentence(text -> sents[index]);	//cleaning memory
	memmove(text -> sents+index, text -> sents+index+1, (text -> len-index-1)*sizeof(struct Sentence));	//shift of sentences in the text
	text -> len--;	//overwrite count of sentences in the text
}

int removingDuplicateSentences(struct Text *text){
	int count = 0;	//count removing sentences
	int coincidence1, coincidence2;
	struct Word *word1;
	struct Word *word2;
	for (int rs = text -> len-1; rs > 0; rs--){
		for (int ls = rs-1; ls >= 0; ls--){
			if (text -> sents[ls].len == text -> sents[rs].len){
				word1 = text -> sents[ls].wwords;
				word2 = text -> sents[rs].wwords;
				coincidence1 = coincidence2 = 0;
				for (int i = 0; i < text -> sents[ls].len; i++){
					coincidence1 = word1[i].sep != word2[i].sep;
					coincidence2 = wcscasecmp(word1[i].wchars, word2[i].wchars);
					if (coincidence1 || coincidence2)
						break;
				}
				if (!coincidence1 && !coincidence2){
					removingSentence(text, rs);
					count++;
					break;
				}
			}	
		}
	}
	return count;
}

