#include "std_lib_inc.h"
#include "parameter_reader.h"

#include "zoodb.h"
#include "befehle.h"
#include "zooio.h"
#include "errorfall.h"

int main(int argc, char** argv)
{

    stringstream befehlestream = make_string_stream(argc, argv);


    zoodb db;
    int ladeerror = ladedatei("zoo", db);
    if(ladeerror != 100)
    {
        errornr(ladeerror);
        return 0;
    }


    befehle b;
    int ergebnis = b.fuehre_befehle_aus(befehlestream, db);


    if(ergebnis == 100)
    {
        int speichererror = speicherdatei("zoo", db);
        if(speichererror != 100)
        {
            errornr(speichererror);
            return 0;
        }
    }


    if(ergebnis != 0)
        errornr(ergebnis);

    return 0;
}