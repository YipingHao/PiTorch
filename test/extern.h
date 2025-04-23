#ifndef EXTERNHJEDRAGFU9IAERTU9ERAFGJIERFGhwetwrgarjfoeragjo
#define EXTERNHJEDRAGFU9IAERTU9ERAFGJIERFGhwetwrgarjfoeragjo

#include"../src/header/Pikachu.h"
#include"../extern/header/all.h"
class parameter
{
public:
    parameter();
    ~parameter();
    void build(hyperlex::dictionary& pf);
    std::string FullInputName(void) const;
    std::string FullOutputName(void) const;
    std::string FullDataName(void) const;
    void Demo(FILE* fp)const;
    size_t thread;
    char* funcName;
    bool option1;
    int option2;
private:
    char* inputPath;
    char* outputPath;

    char* inputName;
    char* outputName;

    char* DataFilePath;
    char* DataFileName;

};

class CFile
{
public:
    CFile();
    ~CFile();
    void close(void);
    void Open(const char* name, const char* mode);
    void OpenRead(const char* s);//SH_read_from_file__(const char* s);
    void OpenWriteAtRear(const char* s);//fp_write_at_rear(const char* s);
    void OpenWritePlus(const char* s);//fp_write_plus
    std::string FusePathAndName(const std::string& path, const std::string& name);//path_add_file_name
    std::string FusePathAndName(const char* path, const std::string& name);//path_add_file_name
    std::string ChangeSuffix(const std::string& file, const char* new_one);//string suffix_change(const string& file, const char* new_one);

    FILE* fp;
private:

};


int test_extern(const parameter& para, int item);
#endif