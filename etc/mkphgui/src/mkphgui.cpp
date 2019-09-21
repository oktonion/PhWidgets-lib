#include <Ap.h>

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <cctype>

std::map<std::string, std::string> phwidgets_includes;
std::string phwidgets_default_include = "<Widget.h> // PhWidgets::Widget class";
std::set<std::string> widget_includes;

std::map<int, ApDBWidgetInfo_t> widgets;
std::map<int, std::vector<int>/**/> hierarchy;
int last_child_id = -1;

std::fstream header, source;

void init_phwidgets_includes()
{
    phwidgets_includes["PtWidget"] = "<Widget.h> // PhWidgets::Widget class";
    phwidgets_includes["PtBasic"] = "<Basic.h> // PhWidgets::Basic class";
    phwidgets_includes["PtButton"] = "<Button.h> // PhWidgets::Button class";
    phwidgets_includes["PtCompound"] = "<Compound.h> // PhWidgets::Compound class";
    phwidgets_includes["PtContainer"] = "<Container.h> // PhWidgets::Container class";
    phwidgets_includes["PtDisjoint"] = "<Disjoint.h> // PhWidgets::Disjoint class";
    phwidgets_includes["PtGraphic"] = "<Graphic.h> // PhWidgets::Graphic class";
    phwidgets_includes["PtLabel"] = "<Label.h> // PhWidgets::Label class";
    phwidgets_includes["PtNumeric"] = "<Numeric.h> // PhWidgets::Numeric class";
    phwidgets_includes["PtNumericFloat"] = "<NumericFloat.h> // PhWidgets::NumericFloat class";
    phwidgets_includes["PtOnOffButton"] = "<OnOffButton.h> // PhWidgets::OnOffButton class";
    phwidgets_includes["PtText"] = "<Text.h> // PhWidgets::Text class";
    phwidgets_includes["PtTimer"] = "<Timer.h> // PhWidgets::Timer class";
    phwidgets_includes["PtToggleButton"] = "<ToggleButton.h> // PhWidgets::ToggleButton class";
    phwidgets_includes["PtWindow"] = "<Window.h> // PhWidgets::Window class";
}

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
            bool is_parent = child_widgets.size();
            if (is_parent)
            {
                header << std::endl;
                source << std::endl;
            }

            header << std::string((root_wi.level) * 2, ' ') << "struct " << root_wi.wgt_name << " : " << std::endl <<
                std::string((root_wi.level) * 2, ' ') << "    public PhWidgets::" << (root_wi.wgt_class + 2) << std::endl <<
                "{" << std::endl;

            source << std::string((root_wi.level) * 2, ' ') << root_wi.wgt_name << "::" << root_wi.wgt_name << "() :" << std::endl <<
                "    PhWidgets::" << (root_wi.wgt_class + 2) << "(ABN_" << root_wi.wgt_name;

            if (child_widgets.size())
            {
                source << ")," << std::endl;
                last_child_id = child_widgets.back();

                print_root_widgets(child_widgets);

                header << std::endl;
            }

            source << ")" << std::endl;

            header << std::string((root_wi.level) * 2, ' ') << "};" << std::endl;

            source << std::string((root_wi.level) * 2, ' ') << "{ }" << std::endl;
        }
        else
        {
            bool is_parent = child_widgets.size();
            if (is_parent)
            {
                header << std::endl;
                source << std::endl;
            }

            header << std::string((root_wi.level) * 2, ' ') << "PhWidgets::" << (root_wi.wgt_class + 2) << " " << root_wi.wgt_name << ";" << (is_parent ? "// :" : "") << std::endl;

            source << "    " << root_wi.wgt_name << "(ABN_" << root_wi.wgt_name;

            if(widget_index != last_child_id)
                source << ")," << std::endl;

            if (child_widgets.size())
            {
                print_root_widgets(child_widgets);

                header << std::string((root_wi.level) * 2, ' ') << "// end of "  << root_wi.wgt_name << std::endl << std::endl;
            }

        }
    }
}

std::vector<std::string> splitpath(
    const std::string& str
    , const std::set<char> delimiters)
{
    std::vector<std::string> result;

    char const* pch = str.c_str();
    char const* start = pch;
    for (; *pch; ++pch)
    {
        if (delimiters.find(*pch) != delimiters.end())
        {
            if (start != pch)
            {
                std::string str(start, pch);
                result.push_back(str);
            }
            else
            {
                result.push_back("");
            }
            start = pch + 1;
        }
    }
    result.push_back(start);

    return result;
}

struct convert_to_upper {
    void operator()(char& c) const { c = std::toupper(c); }
};

int main(int argc, const char* argv[])
{
    if (argc == 1)
        return 0;

    init_phwidgets_includes();

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
        std::string winclude = phwidgets_includes[wi.wgt_class];
        if (winclude.length())
            widget_includes.insert(winclude);
        else
            widget_includes.insert(phwidgets_default_include);
    }

    if (hierarchy.begin() == hierarchy.end())
        return 0;
    
    typedef std::map<int, std::vector<int>/**/>::iterator hierarchy_iterator;

    std::vector<int>& root_widgets = hierarchy.begin()->second;

    std::string
        file_name_with_ext,
        file_name;

    {
        std::set<char> delims;
        delims.insert('/');

        std::vector<std::string> path = splitpath(argv[1], delims);
        file_name_with_ext = path.back();

        delims.clear();
        delims.insert('.');
        path = splitpath(file_name_with_ext, delims);
        file_name = path.size() ? path.front() : file_name_with_ext;

        source.open((std::string("./") + file_name + ".cpp").c_str(), std::fstream::out);
        header.open((std::string("./") + file_name + ".h").c_str(), std::fstream::out);
    }

    if (!source || !header)
        return -1;

    std::string header_guard = std::string("PHGUI_") + file_name + "_H";

    std::for_each(header_guard.begin(), header_guard.end(), convert_to_upper());

    source << "#include \"" << (file_name + ".h") << "\"" << std::endl << std::endl << "#include <abimport.h>" << std::endl << "#include <ablibs.h>" << std::endl << std::endl << "using namespace PhGUI;" << std::endl << std::endl;
    header << "#ifndef " << header_guard << std::endl << "#define " << header_guard << std::endl;
    
    for (std::set<std::string>::iterator it = widget_includes.begin(); it != widget_includes.end(); ++it)
    {
        header << "#include " << (*it) << std::endl;
    }

    header << std::endl << "namespace PhGUI" << std::endl << "{" << std::endl;

    print_root_widgets(root_widgets);

    header << "} // namespace PhGUI" << std::endl;
    header << "#endif // " << header_guard << std::endl;


    return 0;
}