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
const std::string phwidgets_default_include = "<Widget.h> // PhWidgets::Widget class";
std::set<std::string> widget_includes;

std::map<int, ApDBWidgetInfo_t> widgets;
std::map<int, std::vector<int>/**/> hierarchy;
int last_child_id = -1;

void init_phwidgets_includes()
{
    phwidgets_includes["PtBasic"]           = "<Basic.h> // PhWidgets::Basic class";
    phwidgets_includes["PtButton"]          = "<Button.h> // PhWidgets::Button class";
    phwidgets_includes["PtComboBox"]        = "<ComboBox.h> // PhWidgets::ComboBox class";
    phwidgets_includes["PtCompound"]        = "<Compound.h> // PhWidgets::Compound class";
    phwidgets_includes["PtContainer"]       = "<Container.h> // PhWidgets::Container class";
    phwidgets_includes["PtDisjoint"]        = "<Disjoint.h> // PhWidgets::Disjoint class";
    phwidgets_includes["PtGauge"]           = "<Gauge.h> // PhWidgets::Gauge class";
    phwidgets_includes["PtGraphic"]         = "<Graphic.h> // PhWidgets::Graphic class";
    phwidgets_includes["PtImageArea"]       = "<ImageArea.h> // PhWidgets::ImageArea class";
    phwidgets_includes["PtLabel"]           = "<Label.h> // PhWidgets::Label class";
    phwidgets_includes["PtNumeric"]         = "<Numeric.h> // PhWidgets::Numeric class";
    phwidgets_includes["PtNumericFloat"]    = "<NumericFloat.h> // PhWidgets::NumericFloat class";
    phwidgets_includes["PtNumericInteger"]  = "<NumericInteger.h> // PhWidgets::NumericInteger class";
    phwidgets_includes["PtOnOffButton"]     = "<OnOffButton.h> // PhWidgets::OnOffButton class";
    phwidgets_includes["PtPane"]            = "<Pane.h> // PhWidgets::Pane class";
    phwidgets_includes["PtText"]            = "<Text.h> // PhWidgets::Text class";
    phwidgets_includes["PtTimer"]           = "<Timer.h> // PhWidgets::Timer class";
    phwidgets_includes["PtToggleButton"]    = "<ToggleButton.h> // PhWidgets::ToggleButton class";
    phwidgets_includes["PtWidget"]          = "<Widget.h> // PhWidgets::Widget class";
    phwidgets_includes["PtWindow"]          = "<Window.h> // PhWidgets::Window class";
}

void print_root_widgets(std::vector<int> & root_widgets, std::fstream &header, std::fstream &source)
{
    for (std::size_t i = 0; i < root_widgets.size(); ++i)
    {
        int widget_index = root_widgets[i];
        ApDBWidgetInfo_t root_wi = widgets[widget_index];
        

        std::vector<int>& child_widgets = hierarchy[widget_index];
        
        bool is_nameless_widget = 
                std::string(root_wi.wgt_name) == std::string(root_wi.wgt_class),
             is_implemented_class =
                (phwidgets_includes.count(root_wi.wgt_class) && 
                 phwidgets_includes[root_wi.wgt_class].length() &&
                 phwidgets_includes[root_wi.wgt_class] != phwidgets_default_include);

        if (root_wi.level == 1)
        {
            bool is_parent = child_widgets.size();
            if (is_parent)
            {
                header << std::endl;
                source << std::endl;
            }

            if(!is_nameless_widget)
            header << 
                std::string((root_wi.level) * 2, ' ') << "struct " << root_wi.wgt_name << " : " << std::endl <<
                std::string((root_wi.level) * 2, ' ') << "    public PhWidgets::" << 
                    (is_implemented_class ? (root_wi.wgt_class + 2) : "Widget") << std::endl <<
                std::string((root_wi.level) * 2, ' ') << "{" << std::endl <<
                std::string((root_wi.level) * 4, ' ') << root_wi.wgt_name << "(); // (constructor)" << std::endl;
                

            if(!is_nameless_widget)
            source << 
                root_wi.wgt_name << "::" << root_wi.wgt_name << "() :" << std::endl <<
                "    PhWidgets::" << (is_implemented_class ? (root_wi.wgt_class + 2) : "Widget") 
                    << "(ABN_" << root_wi.wgt_name << ")" << std::endl;;

            if (child_widgets.size() && !is_nameless_widget)
            {
                last_child_id = child_widgets.back();

                print_root_widgets(child_widgets, header, source);

                header << std::endl;
            }


            if(!is_nameless_widget)
            header << 
                std::string((root_wi.level) * 2, ' ') << "};" << std::endl;
            if(!is_nameless_widget)
            source << 
                std::string((root_wi.level) * 2, ' ') << "{ }" << std::endl;
        }
        else
        {
            bool is_parent = child_widgets.size();
            if (is_parent && !is_nameless_widget)
            {
                header << std::endl;
                source << std::endl;
            }

            if(!is_nameless_widget)
            header << 
                std::string((root_wi.level) * 2, ' ') << "PhWidgets::" << 
                    (is_implemented_class ? (root_wi.wgt_class + 2) : "Widget") << " " << root_wi.wgt_name << ";" << (is_parent ? "// :" : "") << std::endl;
            
            if(!is_nameless_widget)
            source << "    ," << root_wi.wgt_name << "(ABN_" << root_wi.wgt_name << ")" << std::endl;

            if (child_widgets.size())
            {
                print_root_widgets(child_widgets, header, source);
                if(!is_nameless_widget)
                header << 
                    std::string((root_wi.level) * 2, ' ') << "// end of "  << root_wi.wgt_name << std::endl << std::endl;
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
    std::fstream header, source;

    if (argc < 2)
        return 0;

    init_phwidgets_includes();

    ApDBase_t *dbase = ApOpenDBaseFile(argv[1]);

    std::string output_dir = argc > 2? argv[2] : "./";

    if (NULL == dbase)
    {
        std::cout << "Cannot open dbase file '" << argv[1] << "'.";
        return -1;
    }

    ApDBWidgetInfo_t wi;

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

        source.open((output_dir + file_name + ".cpp").c_str(), std::fstream::out);
        header.open((output_dir + file_name + ".h").c_str(), std::fstream::out);
    }

    if (!source || !header)
    {
        std::cout << "Cannot create header/source files pair for '" << file_name << "' in '" << output_dir << "'.";
        return -1;
    }

    std::string header_guard = std::string("PHGUI_") + file_name + "_H";

    std::for_each(header_guard.begin(), header_guard.end(), convert_to_upper());

    source << 
        "#include \"" << (file_name + ".h") << "\"" << std::endl <<
        std::endl << 
        "#include <Ap.h>" << std::endl <<
        "#include <Pt.h>" << std::endl <<
        "#include <abimport.h>" << std::endl  << 
        "#include <ablibs.h>" << std::endl  << 
        std::endl << "using namespace PhGUI;" << 
        std::endl << 
        std::endl;

    header << 
        "#ifndef " << header_guard << std::endl <<
        "#define " << header_guard << std::endl;
    
    for (std::set<std::string>::iterator it = widget_includes.begin(); it != widget_includes.end(); ++it)
    {
        header << "#include " << (*it) << std::endl;
    }

    header << 
        std::endl << "namespace PhGUI" << 
        std::endl << "{" << std::endl << 
        "  using namespace PhWidgets;" << std::endl <<
        std::endl;

    for (hierarchy_iterator it = hierarchy.begin(); it != hierarchy.end(); ++it)
    {
        std::vector<int>& root_widgets = it->second;
        if(root_widgets.size())
        {
            print_root_widgets(root_widgets, header, source);
            break;
        }
        
    }

    header << "} // namespace PhGUI" << std::endl;
    header << "#endif // " << header_guard << std::endl;


    return 0;
}