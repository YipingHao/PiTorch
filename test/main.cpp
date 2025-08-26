#include"extern.h"
#include<iostream>

#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif
int test_entrance_old(const char* output_path);
int static entrance(int argc, char* argv[]);
int test(hyperlex::dictionary& para);
#include<cmath>
int main(int argc, char* argv[])
{
    int error;
    error = entrance(argc, argv);
    return error;
    try
    {
        error = test_entrance_old("./");
    }
    catch (Pikachu::PikaError& E)
    {
        std::cout << "int main(): " << std::endl;
        E.show(stderr);
    }
    catch (hyperlex::dictionary* Error)
    {
        std::cout << "int main(): hyperlex::dictionary* Error" << std::endl;
        Error->print(stderr);
		delete Error;
    }
    return error;
}

static bool compare(const char* str1, const char* str2);
int static entrance(int argc, char* argv[])
{
    hyperlex::dictionary para;
    FILE* fp;
    std::string file, outputDir;
    CFile CF;
    int error;
    hyperlex::BufferChar input;
    hyperlex::BufferChar temp;
    int info;

    if (argc > 1) file = argv[1];
    else file = "./parameter/parameter.txt";
    if (argc > 2) outputDir = argv[2];
    else outputDir = "./output/";
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    //fp = CF.OpenRead(file.c_str());
    fp = fopen(file.c_str(), "r");
    std::cout << "InputFileName: " << file << std::endl;
    std::cout << "OutputFilePath: " << outputDir << std::endl;
    input << fp;
    temp.append(input);
    std::cout << "/*" << std::endl;
    std::cout << temp.ptr() << std::endl;
    std::cout << "*/" << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    fclose(fp);
    error = para.build(input.ptr());
    std::cout << "error: " << error << std::endl;


    hyperlex::FilePath Opath;
    hyperlex::FilePath O_1, O_2, O_3;
    Opath.build(outputDir.c_str());

    O_1.build(para.search("L.txt", "OutputFileName"));
    O_2.build(para.search("G.txt", "OutputFileName2"));
    O_3.build(para.search("G2.txt", "OutputFileName3"));

    hyperlex::FilePath F_1, F_2, F_3;

    F_1.copy(Opath);
    F_2.copy(Opath);
    F_3.copy(Opath);

    F_1.RearOnlyAppend(O_1);
    F_2.RearOnlyAppend(O_2);
    F_3.RearOnlyAppend(O_3);


    para.assign("OutputFileName", F_1.path());
    para.assign("OutputFileName2", F_2.path());
    para.assign("OutputFileName3", F_3.path());

    para.print(stdout);

    const char* item;
    item = para.search("test old", "item");
    std::cout << "item: " << item << std::endl;
    if (compare(item, "test old"))
    {
        try
        {
            info = test_entrance_old(outputDir.c_str());
        }
        catch (Pikachu::PikaError& E)
        {
            std::cout << "int main(): " << std::endl;
            E.show(stderr);
        }
    }
    //else if (compare(item, "simple LR"))
    //{
    //    info = simpleLR(para);
    //}
    //else if (compare(item, "simple LR v02"))
    //{
    //    info = simpleLR_v02(para);
    //}
    else if (compare(item, "test"))
    {
        info = test(para);
    }
    else
    {
        info = test(para);
    }
    return info;
}
static bool compare(const char* str1, const char* str2)
{
    size_t i;
    for (i = 0; (str1[i] != '\0') && (str1[i] == str2[i]); i++);
    return str1[i] == str2[i];
}