#ifndef __FS_FILESYSTEM_H__
#define __FS_FILESYSTEM_H__

enum OS
{
	OS_Unknown,
	OS_Windows
};

#ifdef _WIN32
#define OS OS_Windows
#else 
#define OS OS_Unknown
#error only windows supported right now
#endif

void test()
{
	/*
	DirIter *iter = Filesystem_IterateDirectory(path);
	char *current = DirIter_Next(iter);

	Filesystem_CreateDirectory(path);
	Filesystem_DeleteDirectory(path);
	Filesystem_CreateFile(path);
	Filesystem_DeleteFile(path);
	Filesystem_WriteToFile(path, data, dataSize);
	char *filecontents = Filesystem_ReadFileAsString(path);
	void *data = Filesytem_ReadFile(path, &dataSize);

	char **paths = Filesystem_GetDirectoryPaths(&pathCount);

	while (current)
	{
		if (Filesystem_IsDirectory(current))
		{
			//Recurse(current);
		}
		else if(Filesystem_IsReadableFile(current))
		{
			char *fileContent = ReadFileAsString(current);
			// do work on file
		}

		char *current = DirIter_Next(iter);
	}
	*/
}

#endif // __FS_FILESYSTEM_H__