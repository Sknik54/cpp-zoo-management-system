#include "spezie.h"

bool ist_gueltige_spezie(int nummer)
{
    return nummer >= 0 && nummer <= 4;
}

spezie spezie_von_int(int nummer)
{
    return static_cast<spezie>(nummer);
}

int int_von_spezie(spezie s)
{
    return static_cast<int>(s);
}