#include "befehle.h"


int befehle::fuehre_befehle_aus(istream& is, zoodb& db) {
    string cmd;
    if(!(is >> cmd))            { return 102;}
    if (cmd == "add")           { return add(is,db);}
    else if (cmd == "delete")   { return del(is,db);}
    else if (cmd == "list")     { return list(is,db);}
    else if (cmd == "show")     { return show(is,db);}
    else if (cmd == "assign")   { return assign(is,db);}
    else if (cmd == "unassign") { return unassign(is,db);}
    else if (cmd == "help")     { return help(is,db);}
    else {

        return 101;
    }


}

int befehle::add(istream &is, zoodb &db) {
    string token;
    if (is >> token) {
        if (token == "animal") {
            string name;
            int spezienummer;
            if (!(is >> name >> spezienummer)) { return 102;}

            if (name.empty()) {
               return 102;
            }
            if (!ist_gueltige_spezie(spezienummer)) {
                return 402;
            }

            int animalid = db.naechsteidanimal();
            animal a(animalid, name, spezie_von_int(spezienummer));
            db.animals.push_back(a);

        }
        else if (token == "enclosure") {
            string name;
            int groesse;
            if (!lese_enclosure_ohne_id(is, name, groesse)) return 102;
            if (groesse < 0) { return 102;}
            int gehegeid = db.naechsteidenclosure();
            enclosure e(gehegeid, name, groesse);
            db.enclosures.push_back(e);
        }
        else {
            return 102;
        }

    } else { return 102;}

    return 100;

}

int befehle::del(istream &is, zoodb &db) {
    string token;
    if (is >> token) {
       if (token == "animal") {
           int gesuchteid;
           if (!(is >> gesuchteid)) { return 102;}
           const animal* a = db.findeanimal(gesuchteid);
           if (a == nullptr) {
               return 402;
           }
           for (const auto&e : db.assignments) {
               if (gesuchteid == e.animalid){ return 202;}
           }
           for (int i = 0; i < db.animals.size(); ++i) {
               if (db.animals[i].getid() == gesuchteid) {
                   db.animals.erase(db.animals.begin() + i);
                   return 100;
               }
           }

       } else if (token == "enclosure") {
           int gesuchteid;
           if (!(is >> gesuchteid)) { return 102;}
           const enclosure* e = db.findeenclosure(gesuchteid);
           if (e == nullptr) {
               return 401;
           }
           for (const auto&d : db.assignments) {
               if (gesuchteid == d.enclosureid){return 201;}
           }
           for (int i = 0; i < db.enclosures.size(); ++i) {
               if (db.enclosures[i].getid() == gesuchteid) {
                   db.enclosures.erase(db.enclosures.begin() + i);
                   return 100;
               }
           }
       } else {return 102;}
    } else { return 102;}
    return 0;
}

int befehle::list(istream &is, zoodb &db) {
    enum class Block { None, Animals, Enclosures, Assignments, Assigned, Unassigned };
    Block aktuellerblock = Block::None;
    string token;
    if (is >> token) {
        if (token == "animals") { aktuellerblock = Block::Animals;}
        if (token == "enclosures") {aktuellerblock = Block::Enclosures;}
        if (token == "assignments") {aktuellerblock = Block::Assignments;}
        if (token == "assigned") {aktuellerblock = Block::Assigned;}
        if (token == "unassigned") {aktuellerblock = Block::Unassigned;}

        if (aktuellerblock == Block::None) {
            return 102;
        }
        if (aktuellerblock == Block::Animals) {
            bool print = false;
            for (const auto&x : db.animals) {
                cout << x << "\n";
                print = true;
            }
            if (!print) { cout << "\n";}
        }

        if (aktuellerblock == Block::Enclosures) {
            bool print = false;
            for (const auto&x : db.enclosures) {
                cout << x << "\n";
                print = true;
            }
            if (!print) { cout << "\n";}
        }

        if (aktuellerblock == Block::Assignments) {
            bool print = false;
            for (const auto&x : db.assignments) {
                cout << x << "\n";
                print = true;
            }
            if (!print) { cout << "\n";}
        }

        if (aktuellerblock == Block::Assigned) {
            bool print = false;
            for (const auto&x : db.animals) {
                for (const auto&e : db.assignments) {
                    if (x.getid() == e.animalid) {
                        cout << x << "\n";
                        print = true;
                        break;
                    }
                }
            }
            if (!print) { cout << "\n";}
        }

        if (aktuellerblock == Block::Unassigned) {
            bool print = false;
            for (const auto&x : db.animals) {
                bool treffer = false;
                for (const auto&e : db.assignments) {
                    if (x.getid() == e.animalid) {
                           treffer = true;
                        }
                    }
                if (!treffer) {cout << x << "\n";  print = true;}
                }
            if (!print) { cout << "\n";}
            }
    }
    else return 102;

    return 0;
    }


int befehle::show(istream &is, zoodb &db) {
    string token;
    if(!(is >> token)) return 102;

    int id;
    if(!(is >> id)) return 102;
        if (token == "animal") {
            const animal* a = db.findeanimal(id);
            if(a == nullptr) return 402;

            cout << a->getname() << ' ' << int_von_spezie(a->getspezie()) << '\n';
            return 100;

            }   else if (token == "enclosure") {
            const enclosure* e = db.findeenclosure(id);
                if(e == nullptr) return 401;

                const string& name = e->getname();
                const bool hatwhitespace = (name.find(' ') < name.length());

                if(hatwhitespace) {
                    cout << '%' << name << "% " << e->getgroesse() << '\n';
                }
                else {
                    cout << name << ' ' << e->getgroesse() << '\n';
                }

                return 0;

        }
    return 102;

}
int befehle::assign(istream &is, zoodb &db) {
    int animalid;
    int enclosureid;
    if (!(is >> enclosureid)) return 102;
    if (!(is >> animalid)) return 102;

    const animal* a = db.findeanimal(animalid);
    const enclosure* e = db.findeenclosure(enclosureid);
    if(e == nullptr) return 401;
    if(a == nullptr) return 402;

    bool hatassignment = db.besitztassignment(enclosureid, animalid);
    if(hatassignment) {
        return 302;
    }


    int anzahltiere = 0;
    bool zugeordnet = false;
    for (const auto&x : db.assignments) {
        if (enclosureid == x.enclosureid) {
            anzahltiere++;
        }
        if (animalid == x.animalid) {
            zugeordnet = true;
        }
    }
    if (anzahltiere >= e->getgroesse()) {
        return 501;
    }
    if (zugeordnet) {
        return 502;
    }
    assignment asignment(enclosureid, animalid);
    db.assignments.push_back(asignment);
    return 100;


}
int befehle::unassign(istream &is, zoodb &db) {
    int animalid;
    int enclosureid;
    if (!(is >> enclosureid)) return 102;
    if (!(is >> animalid)) return 102;

    bool hatassignment = db.besitztassignment(enclosureid, animalid);
    if (hatassignment) {
        for(int i = 0; i < db.assignments.size(); i++)
        {

            if(db.assignments[i].enclosureid == enclosureid && db.assignments[i].animalid == animalid) {
                db.assignments.erase(db.assignments.begin() + i);
                return 100;
            }

        }

    }
    return 301;
}
int befehle::help(istream &is, zoodb &db){}




