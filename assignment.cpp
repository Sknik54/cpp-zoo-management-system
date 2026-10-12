#include "assignment.h"

ostream& operator<<(ostream& os, const assignment& a) //<Gehege-ID> <Tier-ID>
{
    os << a.enclosureid << ' ' << a.animalid;
    return os;
}

istream& operator>>(istream& is, assignment& a) //<Gehege-ID> <Tier-ID>
{
    is >> a.enclosureid >> a.animalid;
    return is;
}