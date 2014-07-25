#include "WordListFile.h"

#include <File.h>

WordListFile::WordListFile(const BEntry* path)
	: BFile(path, B_READ_ONLY)
{
}

WordListFile::~WordListFile()
{
}

void
WordListFile::ReadWord(BString &_result)
{
	_result.SetTo("");
	
	char buffer;
	Read(&buffer, 1);
	
	while (buffer != '\n')
	{
		_result += buffer;
		
		if (Read(&buffer, 1) != 1)
			break;
	}
}

void
WordListFile::ReadLine(BString &_result, long long lineno)
{
	int oldPosition = Position();
	int currentLine = -1;
	
	Seek(0, SEEK_SET);
	
	do
	{
		currentLine++;
		ReadWord(_result);
	} while (currentLine < lineno);
	
	Seek(oldPosition, SEEK_SET);
}

long long
WordListFile::FindWord(BString &search)
{
	long long lineno = 0LL;
	
	BString currentWord;
	BString definition;
	
	while (true)
	{
		ReadWord(currentWord);
		
		if (currentWord.Length() == 0)
			break;
		
		if (currentWord == search) {
			return lineno;
		}
		
		lineno++;
	}
	
	return -1LL;
}
