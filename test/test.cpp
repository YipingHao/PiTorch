#include"extern.h"
#include<cmath>
using namespace Pikachu;

#include<cstring>
#include<time.h>
#include<stdlib.h>

typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor> GTNode;
typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor>::PostIterator GTiterator;

int static Test000(const hyperlex::dictionary& para);
int static Test001(const hyperlex::dictionary& para);
int static Test002(const hyperlex::dictionary& para);
int static Test003(const hyperlex::dictionary& para);
int static Test004(const hyperlex::dictionary& para);
int static Test005(const hyperlex::dictionary& para);
int static Test006(const hyperlex::dictionary& para);
int static Test007(const hyperlex::dictionary& para);
int static Test008(const hyperlex::dictionary& para);
int static Test009(const hyperlex::dictionary& para);
int static Test010(const hyperlex::dictionary& para);
int static Test011(const hyperlex::dictionary& para);
int static Test012(const hyperlex::dictionary& para);
int static Test013(const hyperlex::dictionary& para);
int static Test014(const hyperlex::dictionary& para);
int static Test015(const hyperlex::dictionary& para);
int static Test016(const hyperlex::dictionary& para);
int static Test017(const hyperlex::dictionary& para);
int static Test018(const hyperlex::dictionary& para);
int static Test019(const hyperlex::dictionary& para);
int static Test020(const hyperlex::dictionary& para);
int static Test021(const hyperlex::dictionary& para);
int static Test022(const hyperlex::dictionary& para);
int static Test023(const hyperlex::dictionary& para);
int static Test024(const hyperlex::dictionary& para);
int static Test025(const hyperlex::dictionary& para);
int static Test026(const hyperlex::dictionary& para);
int static Test027(const hyperlex::dictionary& para);
int static Test028(const hyperlex::dictionary& para);
int static Test029(const hyperlex::dictionary& para);
int static Test030(const hyperlex::dictionary& para);
int static Test031(const hyperlex::dictionary& para);
int static Test032(const hyperlex::dictionary& para);
int static Test033(const hyperlex::dictionary& para);
int static Test034(const hyperlex::dictionary& para);
int static Test035(const hyperlex::dictionary& para);
int static Test036(const hyperlex::dictionary& para);
int static Test037(const hyperlex::dictionary& para);
int static Test038(const hyperlex::dictionary& para);
int static Test039(const hyperlex::dictionary& para);
int static Test040(const hyperlex::dictionary& para);
int static Test041(const hyperlex::dictionary& para);
int static Test042(const hyperlex::dictionary& para);
int static Test043(const hyperlex::dictionary& para);
int static Test044(const hyperlex::dictionary& para);
int static Test045(const hyperlex::dictionary& para);
int static Test046(const hyperlex::dictionary& para);
int static Test047(const hyperlex::dictionary& para);
int static Test048(const hyperlex::dictionary& para);
int static Test049(const hyperlex::dictionary& para);
int static Test050(const hyperlex::dictionary& para);
int static Test051(const hyperlex::dictionary& para);
int static Test052(const hyperlex::dictionary& para);
int static Test053(const hyperlex::dictionary& para);
int static Test054(const hyperlex::dictionary& para);
int static Test055(const hyperlex::dictionary& para);
int static Test056(const hyperlex::dictionary& para);
int static Test057(const hyperlex::dictionary& para);
int static Test058(const hyperlex::dictionary& para);
int static Test059(const hyperlex::dictionary& para);
int static Test060(const hyperlex::dictionary& para);
int static Test061(const hyperlex::dictionary& para);
int static Test062(const hyperlex::dictionary& para);
int static Test063(const hyperlex::dictionary& para);
int test(hyperlex::dictionary& para)
{
    int item = para.search(1L, "TestItem::item");
    int error = 0;
    std::cout << "item: " << item << std::endl;
    switch (item)
    {
    case 0:
    {
        error = Test000(para);
        break;
    }
    case 1:
    {
        error = Test001(para);
        break;
    }
    case 2:
    {
        //std::cout << "Test class file path " << std::endl;
        error = Test002(para);
        break;
    }
    case 3:
    {
        error = Test003(para);
        break;
    }
    case 4:
    {
        error = Test004(para);
        break;
    }
    case 5:
    {
        error = Test005(para);
        break;
    }
    case 6:
    {
        error = Test006(para);
        break;
    }
    case 7:
    {
        error = Test007(para);
        break;
    }
    case 8:
    {
        error = Test008(para);
        break;
    }
    case 9:
    {
        error = Test009(para);
        break;
    }
    case 10:
    {
        error = Test010(para);
        break;
    }
    case 11:
    {
        error = Test011(para);
        break;
    }
    case 12:
    {
        error = Test012(para);
        break;
    }
    case 13:
    {
        error = Test013(para);
        break;
    }
    case 14:
    {
        error = Test014(para);
        break;
    }
    case 15:
    {
        error = Test015(para);
        break;
    }
    case 16:
    {
        error = Test016(para);
        break;
    }
    case 17:
    {
        error = Test017(para);
        break;
    }
    case 18:
    {
        error = Test018(para);
        break;
    }
    case 19:
    {
        error = Test019(para);
        break;
    }
    case 20:
    {
        error = Test020(para);
        break;
    }
    case 21:
    {
        error = Test021(para);
        break;
    }
    case 22:
    {
        error = Test022(para);
        break;
    }
    case 23:
    {
        error = Test023(para);
        break;
    }
    case 24:
    {
        error = Test024(para);
        break;
    }
    case 25:
    {
        error = Test025(para);
        break;
    }
    case 26:
    {
        error = Test026(para);
        break;
    }
    case 27:
    {
        error = Test027(para);
        break;
    }
    case 28:
    {
        error = Test028(para);
        break;
    }
    case 29:
    {
        error = Test029(para);
        break;
    }
    case 30:
    {
        error = Test030(para);
        break;
    }
    case 31:
    {
        error = Test031(para);
        break;
    }
    case 32:
    {
        error = Test032(para);
        break;
    }
    case 33:
    {
        error = Test033(para);
        break;
    }
    case 34:
    {
        error = Test034(para);
        break;
    }
    case 35:
    {
        error = Test035(para);
        break;
    }
    case 36:
    {
        error = Test036(para);
        break;
    }
    case 37:
    {
        error = Test037(para);
        break;
    }
    case 38:
    {
        error = Test038(para);
        break;
    }
    case 39:
    {
        error = Test039(para);
        break;
    }
    case 40:
    {
        error = Test040(para);
        break;
    }
    case 41:
    {
        error = Test041(para);
        break;
    }
    case 42:
    {
        error = Test042(para);
        break;
    }
    case 43:
    {
        error = Test043(para);
        break;
    }
    case 44:
    {
        error = Test044(para);
        break;
    }
    case 45:
    {
        error = Test045(para);
        break;
    }
    case 46:
    {
        error = Test046(para);
        break;
    }
    case 47:
    {
        error = Test047(para);
        break;
    }
    case 48:
    {
        error = Test048(para);
        break;
    }
    case 49:
    {
        error = Test049(para);
        break;
    }
    case 50:
    {
        error = Test050(para);
        break;
    }
    case 51:
    {
        error = Test051(para);
        break;
    }
    case 52:
    {
        error = Test052(para);
        break;
    }
    case 53:
    {
        error = Test053(para);
        break;
    }
    case 54:
    {
        error = Test054(para);
        break;
    }
    case 55:
    {
        error = Test055(para);
        break;
    }
    case 56:
    {
        error = Test056(para);
        break;
    }
    case 57:
    {
        error = Test057(para);
        break;
    }
    case 58:
    {
        error = Test058(para);
        break;
    }
    case 59:
    {
        error = Test059(para);
        break;
    }
    case 60:
    {
        error = Test060(para);
        break;
    }
    case 61:
    {
        error = Test061(para);
        break;
    }
    case 62:
    {
        error = Test062(para);
        break;
    }
    case 63:
    {
        error = Test063(para);
        break;
    }

    default:
    {
        error = Test000(para);
        break;
    }

    }
    return error;
}



int static Test000(const hyperlex::dictionary& para)
{
    int error = 0;
    std::cout << "welcome: ==================================" << std::endl;
    para.print(stdout);
    return error;
}




static bool compare(const char* str1, const char* str2)
{
    size_t i;
    for (i = 0; (str1[i] != '\0') && (str1[i] == str2[i]); i++);
    return str1[i] == str2[i];
}




int static Test001(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}

int static Test002(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}

int static Test003(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test004(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test005(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test006(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test007(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test008(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test009(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test010(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test011(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test012(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test013(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test014(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test015(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test016(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test017(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test018(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test019(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test020(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test021(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test022(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test023(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test024(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test025(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test026(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test027(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test028(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test029(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test030(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test031(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test032(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test033(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test034(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test035(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test036(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test037(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test038(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test039(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test040(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test041(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test042(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test043(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test044(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test045(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test046(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test047(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test048(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test049(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test050(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test051(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test052(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test053(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test054(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test055(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test056(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test057(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test058(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test059(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test060(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test061(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test062(const hyperlex::dictionary& para)
{
    int error = 0;
    return error;
}
int static Test063(const hyperlex::dictionary& para)
{
    int error = 0;
    for (size_t i = 0; i < 64; i++)
    {
        printf("int static Test");
        if (i < 10) printf("00%zu", i);
        else if (i < 100) printf("0%zu", i);
        else printf("%zu", i);
        printf("(const hyperlex::dictionary& para)");
        if (error == 0)
        {
            printf("\n{\n");
            printf("\tint error = 0;\n");
            printf("\treturn error;\n");
            printf("}\n");
        }
        else
        {
            printf(";");
        }
    }

    for (size_t i = 2; i < 64; i++)
    {
        printf("\t\tcase ");
        printf("%zu:\n\t\t{\n\t\t\terror = Test", i);
        if (i < 10) printf("00%zu", i);
        else if (i < 100) printf("0%zu", i);
        else printf("%zu", i);
        printf("(para);\n");
        printf("\t\t\tbreak;\n");
        printf("\t\t}\n");
    }
    return error;
}
























