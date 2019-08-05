#include <Ap.h>

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>

int main(int argc, const char* argv[])
{
    if (argc == 1)
        return 0;


    ApDBase_t *dbase = ApOpenDBaseFile(argv[1]);

    if (NULL == dbase)
        return -1;

    ApDBWidgetInfo_t wi;

    std::fstream fs;
    std::map<int, ApDBWidgetInfo_t> widgets;
    std::map<int, std::vector<int>/**/> hierarchy;

    for (int i = 0; ApGetDBWidgetInfo(dbase, i, &wi); ++i)
    {
        /*printf("#%d: '%s' is a %s, child of #%d, at level %d.\n",
            i, wi.wgt_name, wi.wgt_class, wi.parent_index,
            wi.level);*/
        widgets[i] = wi;
        hierarchy[wi.level].push_back(i);
    }
    
    typedef std::map<int, std::vector<int>/**/>::iterator hierarchy_iterator;

    for (hierarchy_iterator it = hierarchy.begin(); it != hierarchy.end(); ++it)
    {
        ApDBWidgetInfo_t twi = widgets[it->first];
        std::cout << std::string(it->first * 2, ' ') << "struct " << twi.wgt_class << " " << twi.wgt_name << "{" << std::endl;

        for (size_t i = 0; i < it->second.size(); ++i)
        {
            ApDBWidgetInfo_t wi = widgets[ it->second[i] ];
            std::cout << std::string(it->first * 4, ' ') << wi.wgt_class << " " << twi.wgt_name << ";" << std::endl;
        }

        std::cout << std::string(it->first * 4, ' ') << "};" << std::endl;
    }


    return 0;
}