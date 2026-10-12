#include "enclosure.h"

enclosure::enclosure() {
    eid = -1;
    ename = "";
    egroesse = 0;

}


enclosure::enclosure(int id, const string& name, int groesse) {
    eid = id;
    ename = name;
    egroesse = groesse;
}


int enclosure::getid() const { return eid; }
const string& enclosure::getname() const { return ename; }
int enclosure::getgroesse() const { return egroesse; }


void enclosure::setid(int id) { eid = id; }
void enclosure::setname(const string& name) { ename = name; }
void enclosure::setgroesse(int groesse) { egroesse = groesse; }


bool lese_enclosure_ohne_id(istream& is, string& name, int& groesse)
{
    is >> ws;
    if(!is) return false;

    if(is.peek() == '%') //peek ist eine standartmethode von der c++ Bibliothek die das nöchste zeichen sich NUR anguckt
    {
        char p;
        if(!(is >> p)) return false;
        getline(is, name, '%');
        if(!is) return false;
        if(!(is >> groesse)) return false;

        if(name.empty())
        {
            is.setstate(ios::failbit);
            return false;
        }
        return true;
    }
    else
    {
        if(!(is >> name >> groesse)) return false;

        if(name.empty())
        {
            is.setstate(ios::failbit);
            return false;
        }
        return true;
    }
}



ostream& operator<<(ostream& os, const enclosure& e) // <ID> %<Name>% <Groesse> || <ID> <Name> <Groesse>
{
    const bool hat_whitespace = (e.getname().find(' ') < e.getname().length());

    os << e.getid() << ' ';
    if(hat_whitespace)
        os << '%' << e.getname() << "% ";
    else
        os << e.getname() << ' ';

    os << e.getgroesse();
    return os;
}

istream& operator>>(istream& is, enclosure& e) // <ID> %<Name>% <Groesse> || <ID> <Name> <Groesse>
{
    int id;
    if(!(is >> id))
        return is;

    string name;
    int groesse;
    if(!lese_enclosure_ohne_id(is, name, groesse))
        return is;

    e = enclosure(id, name, groesse);
    return is;
}