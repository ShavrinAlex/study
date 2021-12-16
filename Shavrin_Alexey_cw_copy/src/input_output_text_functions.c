#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_struct.h"
#include "text_processing_functions.h"
#define MEM_STEP 5
#define BUF_CHOICE 5
#define WORDS_SEPARATORS L" ,"
#define SENTS_SEPARATORS L".\n"


struct Word *readWord(){
	int size = MEM_STEP;	//buffer size
	int len = 0;	//word length(iteration variable)
	wchar_t *temp = (wchar_t*)malloc(size*sizeof(wchar_t));	//buffer
	wchar_t sep = L' ';	//words separator
	wchar_t wchar = L' ';	//input char
	if (temp != NULL){	//checking memory allocation
		wchar_t *word = temp;
		while (wchar == L' ')	//skipping space
			wchar = fgetwc(stdin);
		while (!wcschr(WORDS_SEPARATORS, wchar) && !wcschr(SENTS_SEPARATORS, wchar)){
			word[len++] = wchar;
			if (len == size){	//checking for buffer overflow
				size += MEM_STEP;	//increase buffer
				temp = (wchar_t*)realloc(word, size*sizeof(wchar_t));
				if (temp != NULL)	//checking memory allocation
					word = temp;
				else{
					free(word);	//cleaning memory
					return NULL;
				}
			}
			wchar = fgetwc(stdin);
		}
		word[len] = L'\0';
		sep = wchar;
		return &(struct Word){word, sep, size, len};
	}
	return NULL;
}	

struct Sentence *readSentence(){
	int size = MEM_STEP;	//buffer size
	struct Word *temp = (struct Word*)malloc(size*sizeof(struct Word));	//buffer
	if (temp != NULL){	//checking memory allocation
		struct Word *sent = temp;
		int len = 0;	//count words(iteration variable)
		struct Word *ww;	//input wide word
		do{	
			ww = readWord();

			//if (ww == NULL){	//checking memory allocation
				//freeSentence((struct Sentence){sent, size, len});	//cleaning memory
			//	return NULL;
			//}
			if (len == size){	//checking for buffer overflow
				size += MEM_STEP;	//increase buffer
				temp = (struct Word*)realloc(sent, size*sizeof(struct Word));
				if (temp != NULL)	//checking memory allocation
					sent = temp;
				else{
					freeSentence((struct Sentence){sent, size, len});	//cleaning memory
					return NULL;
				}
			}
			sent[len++] = *ww;
		}while (!wcschr(SENTS_SEPARATORS, ww->sep));
		return &(struct Sentence){sent, size, len};
	}
	return NULL;
}

struct Text *readText(){
	int size = MEM_STEP;	//buffer size
	struct Sentence *temp = (struct Sentence*)malloc(size*sizeof(struct Sentence));	//buffer
	if (temp != NULL){	//checking memory allocation
		struct Sentence *text = temp;
		int len = 0;	//count sentences(iteration variable)
		struct Sentence *sent;	//input sentence
		do{
			sent = readSentence();
			//if (sent == NULL){	//checking memory allocation
				//freeText(&(struct Text){text, size, len});	//clearning memory
			//	return NULL;
			//}
			if (sent->len == 1 && !sent->wwords[0].len && sent->wwords[0].sep == L'\n'){
				free(sent->wwords[0].wchars);	//clearning memory
				free(sent->wwords);	//cleaning memory
				break;
			}
			else{
				if (len == size){	//checking for buffer overflow
					size += MEM_STEP;	//increase buffer
					temp = (struct Sentence*)realloc(text, size*sizeof(struct Sentence));	//buffer
					if (temp != NULL)	//checking memory allocation
						text = temp;
					else{
						freeText(&(struct Text){text, size, len});	//cleaning memory
						return NULL;
					}
				}
				text[len++] = *sent;
			}
		}while ((sent->wwords[sent->len - 1].sep) != L'\n');
		if ((sent->wwords[sent->len - 1].sep) == L'\n')
			(sent->wwords[sent->len - 1].sep) = L'.';	//adding a dot to an unfinished sentence
		return &(struct Text){text, size, len};
	}
	return NULL;
}

void printText(struct Text text){
	for (struct Sentence *sent = text.sents; sent < text.sents + text.len; sent++){
		for (struct Word *word = sent -> wwords; word < sent -> wwords + sent -> len; word++){
			fputws(word -> wchars, stdout);
			fputwc(word -> sep, stdout);
			if (word -> sep != L' ')
				fputwc(L' ', stdout);
		}
	}
	fputwc(L'\n', stdout);
}

void userChoice(struct Text text){
	wchar_t choice[BUF_CHOICE];
	while (choice[0] != L'5'){
		fputws(L"Выберите, что необходимо сделать с текстом:\n", stdout);
		fputws(L"1 - Посчитать и вывести в минутах количество секунд встречающихся в тексте.", stdout);
		fputws(L"2 - Отсортировать предложения по увеличению суммы кодов символов первого слова в предложении.", stdout);
		fputws(L"3 - Заменить все символы ‘%’, ‘#’, ‘@’ на “<percent>”, “<решетка>”, “(at)” соответственно.", stdout);
		fputws(L"4 - Удалить все предложения которые заканчиваются на слово с тремя согласными подряд.", stdout);
		fputws(L"5 - Закончить обработку и завершить программу.", stdout);
		fgetws(choice, BUF_CHOICE, stdin);
		switch (choice[0]){
			case L'1':
				fputws(L"Количество секунд встречающихся в тексте равно: ", stdout);
				//func
				printText(text);
				break;
			case L'2':
				fputws(L"Результат сортировки:\n", stdout);
				//func
				printText(text);
				break;
			case L'3':
				fputws(L"Результат замены:\n", stdout);
				//func
				printText(text);
				break;
			case L'4':
				fputws(L"Результат удаления:\n", stdout);
				//func
				printText(text);
				break;
			case L'5':
				fputws(L"Обработка завершена. Программа окончена.\n", stdout);
				break;
			default:
				fputws(L"Вы ввели некорректный номер, выберите число от 1 до 5\n", stdout);
		}
	}
}

