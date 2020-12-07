#ifndef Dir_h
#define Dir_h

#include <stdio.h>
#include "dirent.h"
#include <iostream>
#include "DirIter.h"

class Dir {
public:
	Dir(const std::string& path);
	~Dir();
	DirIter begin();
	DirIter end();
private:
	DIR* m_dir;
	DirIter m_iter;
};

#endif /* Dir_h */