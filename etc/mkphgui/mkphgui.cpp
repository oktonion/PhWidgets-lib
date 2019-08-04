#include <Ap.h>

#include <string>
#include <fstream>

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
        printf("#%d: '%s' is a %s, child of #%d, at level %d.\n",
            i, wi.wgt_name, wi.wgt_class, wi.parent_index,
            wi.level);
    }

}