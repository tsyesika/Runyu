#include <File.h>
#include <String.h>

#ifndef _WORDLISTFILE_H
#define _WORDLISTFILE_H

class WordListFile : public BFile {
	public:
							WordListFile(const char* path);
		virtual				~WordListFile();
	
		void				ReadWord(BString &_result);
		void				ReadLine(BString &_result, int lineno);
};

#endif
