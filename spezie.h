#pragma once
#include "std_lib_inc.h"


enum class spezie
{
    Affe = 0,
    Baer = 1,
    Elefant = 2,
    Pinguin = 3,
    Zebra = 4
};


bool ist_gueltige_spezie(int nummer);


spezie spezie_von_int(int nummer);
int int_von_spezie(spezie s);