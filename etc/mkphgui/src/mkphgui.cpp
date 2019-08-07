#include <Ap.h>

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>

std::map<int, ApDBWidgetInfo_t> widgets;
std::map<int, std::vector<int>/**/> hierarchy;
int last_child_id = -1;

std::fstream header, source;

void print_root_widgets(std::vector<int> & root_widgets)
{
    for (std::size_t i = 0; i < root_widgets.size(); ++i)
    {
        int widget_index = root_widgets[i];
        ApDBWidgetInfo_t root_wi = widgets[widget_index];
        

        std::vector<int>& child_widgets = hierarchy[widget_index];

        if (std::string(root_wi.wgt_name) == std::string(root_wi.wgt_class))
            continue;

        if (root_wi.level == 1)
        {
            header << std::string((root_wi.level - 1) * 2, ' ') << "struct " << root_wi.wgt_name << " : " << std::endl <<
                std::string((root_wi.level - 1) * 2, ' ') << "    public PhWidgets::" << (root_wi.wgt_class + 2) << std::endl <<
                "{" << std::endl <<  std::string((root_wi.level - 1) * 2, ' ') ;

            source << std::string((root_wi.level - 1) * 2, ' ') << root_wi.wgt_name << "::" << root_wi.wgt_name << "() :" << std::endl <<
                "    PhWidgets::" << (root_wi.wgt_class + 2) << "(ABN_" << root_wi.wgt_name;

            if (child_widgets.size())
            {
                source << ")," << std::endl;
                last_child_id = child_widgets.back();

                print_root_widgets(child_widgets);
            }

            source << ")" << std::endl;

            header << std::string((root_wi.level - 1) * 2, ' ') << "};" << std::endl;

            source << std::string((root_wi.level - 1) * 2, ' ') << "{ }" << std::endl;
        }
        else
        {
            header << std::string((root_wi.level - 1) * 2, ' ') << "PhWidgets::" << (root_wi.wgt_class + 2) << " " << root_wi.wgt_name << ";" << std::endl;

            source << "    " << root_wi.wgt_name << "(ABN_" << root_wi.wgt_name;

            if(widget_index != last_child_id)
                source << ")," << std::endl;
         

            print_root_widgets(child_widgets);

        }
    }
}

int main(int argc, const char* argv[])
{
    if (argc == 1)
        return 0;


    ApDBase_t *dbase = ApOpenDBaseFile(argv[1]);

    if (NULL == dbase)
        return -1;

    ApDBWidgetInfo_t wi;

    std::fstream fs;

    for (int i = 0; ApGetDBWidgetInfo(dbase, i, &wi); ++i)
    {
        /*printf("#%d: '%s' is a %s, child of #%d, at level %d.\n",
            i, wi.wgt_name, wi.wgt_class, wi.parent_index,
            wi.level);*/
        widgets[i] = wi;
        hierarchy[wi.parent_index].push_back(i);
    }

    if (hierarchy.begin() == hierarchy.end())
        return 0;
    
    typedef std::map<int, std::vector<int>/**/>::iterator hierarchy_iterator;

    std::vector<int>& root_widgets = hierarchy.begin()->second;

    source.open("./Widget.cpp", std::fstream::out);
    header.open("./Widget.h", std::fstream::out);

    if (!source || !header)
        return -1;

    source << "#include \"Widget.h\"" << std::endl << "#include <abimport.h>" << std::endl << "#include <ablibs.h>" << std::endl << std::endl << "using namespace PhGUI;" << std::endl << std::endl;
    header << "#ifndef PHGUI_WIDGET_H" << std::endl << "#define PHGUI_WIDGET_H" << std::endl << std::endl << "namespace PhGUI" << std::endl << "{" << std::endl;

    print_root_widgets(root_widgets);

    header << "} // namespace PhGUI" << std::endl;
    header << "#endif // PHGUI_WIDGET_H" << std::endl;


    return 0;
}