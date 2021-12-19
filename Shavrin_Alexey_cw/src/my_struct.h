#pragma once

struct Word{
	wchar_t *wchars;	//pointer to wide string
	wchar_t sep;	//word separator
	int size;	//buffer size
	int count_c;	//word length
};

struct Sentence{
	struct Word *wwords;	//pointer to struct Word
	int size;	//buffer size
	int count_w;	//count words
};

struct Text{
	struct Sentence *sents;	//pointer to struct Sentence
	int size;	//buffer size
	int count_s;	//count sents
};
