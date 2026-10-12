#include "animal.h"

animal::animal(){
    aid = -1;
    aname = "";
    aspezie = spezie::Affe;

}

animal::animal(int id, const string& name, spezie s){
     aid = id;
     aname = name;
     aspezie = s;

}

// getter
int animal::getid() const { return aid; }
const string& animal::getname() const { return aname; }
spezie animal::getspezie() const { return aspezie; }

// setter
void animal::setid(int id) { aid = id; }
void animal::setname(const string& name) { aname = name; }
void animal::setspezie(spezie s) { aspezie = s; }

ostream& operator<<(ostream& os, const animal& a) // <ID> <Name> <Speziesnummer>
{
    os << a.getid() << ' ' << a.getname() << ' ' << int_von_spezie(a.getspezie());
    return os;
}

istream& operator>>(istream& is, animal& a) // <ID> <Name> <Speziesnummer>
{
    int id;
    string name;
    int s;

    if(!(is >> id >> name >> s))
        return is;


    if(name.empty())
    {
        is.setstate(ios::failbit);
        return is;
    }


    if(!ist_gueltige_spezie(s))
    {
        is.setstate(ios::failbit);
        return is;
    }

    a = animal(id, name, spezie_von_int(s));
    return is;
}