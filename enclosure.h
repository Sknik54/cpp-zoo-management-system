#pragma once
#include "std_lib_inc.h"


class enclosure
{
private:
    int eid;
    string ename;
    int egroesse;

public:
    enclosure();
    enclosure(int id, const string& name, int groesse);


    int getid() const;
    const string& getname() const;
    int getgroesse() const;


    void setid(int id);
    void setname(const string& name);
    void setgroesse(int groesse);
};


ostream& operator<<(ostream& os, const enclosure& e);


istream& operator>>(istream& is, enclosure& e);


bool lese_enclosure_ohne_id(istream& is, string& name, int& groesse);