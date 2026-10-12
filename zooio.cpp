

#include "zooio.h"
#include "animal.h"
#include "assignment.h"
#include "enclosure.h"
#include "spezie.h"


int ladedatei(const string& dateiname, zoodb& db)
{
    ifstream ifs(dateiname);

    if(!ifs)
    {
        ofstream erstelledatei(dateiname);
        if(!erstelledatei) return 601;
        return 100;
    }


    ifs >> db;


    if(!ifs && !ifs.eof())
        return 602;


    for(const auto& as : db.assignments)
    {
        if(db.findeenclosure(as.enclosureid) == nullptr)
            return 401;
        if(db.findeanimal(as.animalid) == nullptr)
            return 402;
    }

    return 100;
}

int speicherdatei(const string& filename, const zoodb& db)
{
    ofstream ofs(filename);
    if(!ofs)return 603;

    ofs << "[animals]\n";
    for(const auto& a : db.animals)
        ofs << a << '\n';

    ofs << "\n[enclosures]\n";
    for(const auto& e : db.enclosures)
        ofs << e << '\n';

    ofs << "\n[assignments]\n";
    for(const auto& as : db.assignments)
        ofs << as << '\n';

    if(!ofs)
        return 603;

    return 100;
}