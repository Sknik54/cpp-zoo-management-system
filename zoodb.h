#pragma once
#include "std_lib_inc.h"
#include "animal.h"
#include "enclosure.h"
#include "assignment.h"


struct zoodb
{
    vector<animal> animals;
    vector<enclosure> enclosures;
    vector<assignment> assignments;


    const animal* findeanimal(int id) const;
    const enclosure* findeenclosure(int id) const;

    bool besitztassignment(int enclosureid, int animalid) const;
    int naechsteidanimal();
    int naechsteidenclosure();
};


istream& operator>>(istream& is, zoodb& db);
ostream& operator<<(ostream& os, const zoodb& db);