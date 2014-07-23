#include "WordListFile.h"

#include <File.h>

WordListFile::WordListFile(const char* path)
	: BFile(path, B_READ_ONLY)
{
}

WordListFile::~WordListFile()
{
}

void
WordListFile::ReadWord(BString &_result)
{
	_result.SetTo(""); // need the string to be empty.
	
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
WordListFile::ReadLine(BString &_result, int lineno)
{
	int oldPosition = Position();
	int currentLine = -1;
	
	Seek(0, SEEK_SET);
	
	do
	{
		currentLine++;
		ReadWord(_result);
	} while (currentLine < lineno);
	
	// Restore the old position
	Seek(oldPosition, SEEK_SET);
}
