//---------------------------------------------------------------------------

#pragma hdrstop

#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
//---------------------------------------------------------------------------

struct Word
{
	char* word;
	int length;


};


bool Equal(Word* word1, Word* word2)
{
	if(word1 != NULL && word2 != NULL)
	{
		if(word1 -> length != word2 -> length)
		{
			return false;
		}

		char* pointer1 = word1 -> word;
		char* pointer2 = word2 -> word;

		while(*pointer1 != '\0')
		{
			if(*pointer1 != *pointer2)
			{
				return false;
			}
			pointer1++;
			pointer2++;
		}

		return true;
	}
	return false;
}



class WordArray
{
	private:
	Word** _word_array;
	int _length;
	int _words_amount;


	public:
	WordArray(char* text)
	{
		_word_array =  ( Word**)malloc( sizeof(Word*) * 2);
		_length = 2;
		SeparateToWords(text);

	}

	void replace_word(Word* replacable_word, Word* replacing_word)
	{
		for(int i = 0; i < _words_amount; i++)
		{
			if( Equal(replacable_word, _word_array[i]) )
			{
				strcpy( _word_array[i] -> word, replacing_word -> word );
				_word_array[i] -> length = replacing_word -> length;
            }
        }
	}

	char* convert_to_text()
	{
		char* destination =(char*) malloc( sizeof(char) * overall_letters_amount() );
		char* pointer = destination;
		for(int i = 0; i < _words_amount; i++)
		{
			for(int j = 0; j < _word_array[i] -> length ; j++, pointer++)
			{
				*pointer = (_word_array[i] -> word)[j];
			}

		}
		*pointer = '\0';
		return destination;
    }

	Word** GetWordArray()
	{
		 return _word_array;
	}

	private:

	long overall_letters_amount()
	{
		long amount = 0;
		for(int i = 0; i < _words_amount; i++)
		{
			amount += _word_array[i] -> length + 1;//+1 ��� �������, � ����� ���������� ����� - ���  \0
		}

		return amount;
	}

	void SeparateToWords(char* text)
	{

		 int WordCounter = 0;
		 char* pointer = text;

		 while(*pointer != '\0')
		 {

			 int WordLength = 0;


			 char ch = *(pointer + WordLength  );

			 while(( (int)ch >= 65 && int(ch) <= 90 ) || ( (int)ch >= 97 && (int)ch <= 122 ) )
			 {
				 WordLength++;
				 ch = *(pointer + WordLength );
			 }

			 if(WordLength == 0)
			 {
				  while(ch != ' ' && ch != '\n' )
				  {
						WordLength++;
						ch = *(pointer + WordLength );
				  }
			 }

			 if(WordLength == 0)
			 {
				 while(ch == ' ' || ch == '\n' )
				 {
					  WordLength++;
					  ch = *(pointer + WordLength );
                 }
             }
			  _word_array[ WordCounter ] = (Word*)malloc( sizeof(Word) );
			  _word_array[ WordCounter ] -> word = (char*)malloc( sizeof(char) * WordLength + 1);
			  _word_array[ WordCounter ] -> length= WordLength;

			 int i = 0;
			 while( i < WordLength)
			 {
				 (_word_array[ WordCounter ] -> word)[i] = (*pointer);
				 pointer++;
				 i++;
			 }

			 (_word_array[ WordCounter ]->word)[i] = '\0';


			 //pointer++;

			 WordCounter++;

			 if(_length == WordCounter)
			 {
				 WordArrayResize();
			 }

		 }

		 _words_amount = WordCounter;
	}



	void WordArrayResize()
	{
		_word_array = (Word**)realloc( _word_array , sizeof(Word*) * _length * 2);
		_length *= 2;
	}


    public:
	~WordArray()
	{
		for(int i = 0; i < _words_amount; i++)
		{
			free(_word_array[i]->word);
			free(_word_array[i]);
		}
		free(_word_array);
	}


};


char* ReadFromFile(const char* FilePath)
{
	FILE *SourceFileStream;

	if( ( SourceFileStream = fopen(FilePath,"r") ) == NULL )
	{
		printf("Cannot open the source file");
		getch();
		exit(1);
	}

	fseek(SourceFileStream,0,SEEK_END);
	unsigned long file_size = ftell(SourceFileStream);
	fseek(SourceFileStream,0,SEEK_SET);


	char* text = (char*)malloc( file_size * sizeof(char) + 1);

	fread(text, sizeof(char), file_size, SourceFileStream);
	fclose(SourceFileStream);

	return text;
}


#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{
	
	char* text = ReadFromFile("text.txt");

	printf("The text from the source file is:\n\n%s\n\n", text);

	ifstream DictionaryFileStream;
	DictionaryFileStream.open("dictionary.txt");
	if(!DictionaryFileStream.is_open())
	{
		printf("Cannot open dictionary file");
		getch();
		exit(1);
    }


	WordArray* TextWordArray = new WordArray(text);

	char* string_of_dict_file = (char*)malloc(sizeof(char) * 45);

	printf("the dictionary is:\n\n");

	while( DictionaryFileStream.getline(string_of_dict_file, 45,'\n') )
	{
		 printf("%s\n",string_of_dict_file);
		 WordArray* dictionary_temp = new WordArray( string_of_dict_file );
		 Word** dictionary_temp_array = dictionary_temp -> GetWordArray();
		 TextWordArray -> replace_word( dictionary_temp_array[0], dictionary_temp_array[2] );
		 delete dictionary_temp;

	}




	char* NewText;
	NewText = TextWordArray -> convert_to_text();
	printf("\nthe new text is:\n\n%s\n\n", NewText);


	FILE* DestinationFileStream;
	if( ( DestinationFileStream = fopen("NewText.txt","w") ) == NULL)
	{
		printf("Cannot open destination file");
		getch();
		exit(1);
	}

	fputs(NewText, DestinationFileStream);

	fclose(DestinationFileStream);
	free(NewText);
	delete TextWordArray;
	free(text);
	getch();
	return 0;
}
//---------------------------------------------------------------------------
