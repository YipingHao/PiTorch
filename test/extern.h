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




int test_extern(const parameter& para, int item);
#endif