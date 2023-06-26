#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>


class FileManager
{
    public:
        static FileManager &shared_instance() {static FileManager fileManager; return fileManager;}
        FileManager();

        bool SaveData(char* SavedFilePath, std::string* LinesToSave, int figureNumber);
        bool LoadSavedData(char* SavedFilePath, char** figure_descriptor, int* number_read_figures);

    protected:

    private:
        std::string PATH_FILE;
};

#endif // FILEMANAGER_H
