#include <File.h>
#include <String.h>
#include <Entry.h>

#ifndef _WORDLISTFILE_H
#define _WORDLISTFILE_H

class WordListFile : public BFile {
	public:
							WordListFile(const BEntry* path);
		virtual				~WordListFile();
	
		void				ReadWord(BString &_result);
		void				ReadLine(BString &_result, long long lineno);
		long long			FindWord(BString &search);
};

#endif
