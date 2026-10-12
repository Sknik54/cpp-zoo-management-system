#include "zoodb.h"



const animal* zoodb::findeanimal(int id) const
{
    for(const auto& a : animals)
        if(a.getid() == id) return &a;
    return nullptr;
}

const enclosure* zoodb::findeenclosure(int id) const
{
    for(const auto& e : enclosures)
        if(e.getid() == id) return &e;
    return nullptr;
}

bool zoodb::besitztassignment(int enclosureid, int animalid) const
{
    for(const auto& as : assignments)
    {

        if(as.enclosureid == enclosureid && as.animalid == animalid) return true;

    }
    return false;
}

int zoodb::naechsteidanimal() {
    if (animals.empty()) {return 0;}
    int id = animals.front().getid();
    for (const auto& e : animals) {
        if (e.getid() >= id) {
            id = e.getid();
        }
    }
    return id+1;
}

int zoodb::naechsteidenclosure() {
    if (enclosures.empty()) {return 0;}
    int id = enclosures.front().getid();
    for (const auto& a : enclosures) {
        if (a.getid() >= id) {
            id = a.getid();
        }
    }
    return id+1;
}

istream& operator>>(istream& is, zoodb& db)
{
    db.animals.clear();
    db.enclosures.clear();
    db.assignments.clear();

    enum class Block { None, Animals, Enclosures, Assignments };
    Block aktuellerblock = Block::None;

    string token;

    while(is >> token)
    {

        if(token == "[animals]")      { aktuellerblock = Block::Animals; continue; }
        if(token == "[enclosures]")   { aktuellerblock = Block::Enclosures; continue; }
        if(token == "[assignments]")  { aktuellerblock = Block::Assignments; continue; }

        if(aktuellerblock == Block::None)
        {
            is.setstate(ios::failbit);
            return is;
        }


        if(aktuellerblock == Block::Animals)
        {

            int id;
            istringstream tmp(token);

            if(!(tmp >> id)) { is.setstate(ios::failbit); return is; }

            string name;
            int species;

            if(!(is >> name >> species)) { is.setstate(ios::failbit); return is; }

            ostringstream zeile;
            zeile << id << ' ' << name << ' ' << species;

            istringstream parser (zeile.str()); //fügt die Daten in animal Objekt ein
            animal a;
            if(!(parser >> a)) { is.setstate(ios::failbit); return is; }

            db.animals.push_back(a);
        }
        else if(aktuellerblock == Block::Enclosures)
        {

            int id;
            istringstream tmp(token);

            if(!(tmp >> id)) { is.setstate(ios::failbit); return is; }

            is >> ws;
            if(!is) { is.setstate(ios::failbit); return is; }

            string gehegezeile;
            if(is.peek() == '%')
            {
                char c;
                if(!(is >> c)) { is.setstate(ios::failbit); return is; }
                string gehegename;
                getline(is, gehegename, '%');
                if(!is) { is.setstate(ios::failbit); return is; }
                int grenze;
                if(!(is >> grenze)) { is.setstate(ios::failbit); return is; }

                ostringstream zeile;
                zeile << id << " %" << gehegename << "% " << grenze;
                gehegezeile = zeile.str();
            }
            else
            {
                string name;
                int grenze;
                if(!(is >> name >> grenze)) { is.setstate(ios::failbit); return is; }

                ostringstream line;
                line << id << ' ' << name << ' ' << grenze;
                gehegezeile = line.str();
            }

            istringstream parser(gehegezeile);
            enclosure e;
            if(!(parser >> e)) { is.setstate(ios::failbit); return is; }

            db.enclosures.push_back(e);
        }
        else
        {

            int encid;
            {
                istringstream tmp(token);
                if(!(tmp >> encid)) { is.setstate(ios::failbit); return is; }
            }
            int aniid;
            if(!(is >> aniid)) { is.setstate(ios::failbit); return is; }

            ostringstream line;
            line << encid << ' ' << aniid;
            istringstream parser(line.str());

            assignment as;
            if(!(parser >> as)) { is.setstate(ios::failbit); return is; }

            db.assignments.push_back(as);
        }
    }


    return is;
}

ostream& operator<<(ostream& os, const zoodb& db)
{
    os << "[animals]\n";
    for(const auto& a : db.animals) os << a << '\n';

    os << "\n[enclosures]\n";
    for(const auto& e : db.enclosures) os << e << '\n';

    os << "\n[assignments]\n";
    for(const auto& as : db.assignments) os << as << '\n';

    return os;
}