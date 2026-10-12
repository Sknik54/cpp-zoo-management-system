#pragma once
#include "std_lib_inc.h"
#include "spezie.h"

class animal
{
private:
    int aid;
    string aname;
    spezie aspezie;

public:
    animal();
    animal(int id, const string& name, spezie s);


    int getid() const;
    const string& getname() const;
    spezie getspezie() const;


    void setid(int id);
    void setname(const string& name);
    void setspezie(spezie s);
};


ostream& operator<<(ostream& os, const animal& a);


istream& operator>>(istream& is, animal& a);