#pragma once
#include "std_lib_inc.h"


struct assignment
{
    int enclosureid = -1;
    int animalid = -1;
};

ostream& operator<<(ostream& os, const assignment& a);
istream& operator>>(istream& is, assignment& a);