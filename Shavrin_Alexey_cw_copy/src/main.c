#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "my_struct.h"
#include "input_output_text_functions.h"
#include "text_processing_functions.h"


int main(){
	setlocale(LC_ALL, "");
	struct Text *text;
	fputws(L"Введите текст:\n", stdout);
	text = readText();
	if (text == NULL){
		fputws(L"Возникла ошибка выделения памяти. Введенный вами текст слишком большой.\n", stdout);
		return -1;
	}
	else{
		//fputws(L"Повторяющиеся предложения удалены: ", stdout);
	//	wprintf(L"%d\n", removingDuplicateSentences(text));
		printText(*text);
		//userChoice();
	}
	return 0;
}
