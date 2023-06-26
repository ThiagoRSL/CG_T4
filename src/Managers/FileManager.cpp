#include "FileManager.h"

FileManager::FileManager()
{
    PATH_FILE = "./saves_t1/filename.txt";
}

bool FileManager::SaveData(char* SavedFilePath, std::string* LinesToSave, int figureNumber)
{
    // Create and open a text file
    std::ofstream MyFile(PATH_FILE);

    // Write to the file
    int i;
    for(i = 0; i < figureNumber; i++)
    {
        MyFile << LinesToSave[i];
        if(i != figureNumber-1)
        {
            MyFile << "\n";
        }
    }
    // Close the file
    MyFile.close();
}
bool FileManager::LoadSavedData(char* SavedFilePath, char** figure_descriptor, int* number_read_figures)
{
    // Read from the text file
    std::ifstream MyReadFile(PATH_FILE);

    std::string myText;
    // Use a while loop together with the getline() function to read the file line by line
    int line_index = 0;
    while (getline(MyReadFile, myText))
    {
        printf("%i:", line_index);
        int stringLength = strlen(myText.c_str());
        printf("\nString = %s", myText.c_str());
        printf("\nTamanho da string = %i", strlen(myText.c_str()));
        //figure_descriptor[line_index] = new char(stringLength);
        strcpy(figure_descriptor[line_index], myText.c_str());
        printf("\nString = %s", figure_descriptor[line_index]);
        line_index += 1;
    }
    *number_read_figures = line_index;
    return true;
}

/*

    while (getline(MyReadFile, myText))
    {
        int stringLength = strlen(myText.c_str());
        printf("Tamanho da string = %i", strlen(myText.c_str()));
        char* newText = new char(stringLength);
        strcpy(newText, myText.c_str());
        printf("\nAn %s", newText);
        printf("\nAn %i\n", newText);
        *SavedFileData[line_index] = newText;
        printf("\nAn %s", SavedFileData[line_index]);
        printf("\nAn %i\n", SavedFileData[line_index]);
        line_index += 1;
    }
*/
