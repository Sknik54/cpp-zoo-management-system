#pragma once
#include "zoodb.h"


class befehle {
public:
    int fuehre_befehle_aus(istream &is, zoodb &db);
private:
    int add(istream &is, zoodb &db);
    int del(istream &is, zoodb &db);
    int list(istream &is, zoodb &db);
    int show(istream &is, zoodb &db);
    int assign(istream &is, zoodb &db);
    int unassign(istream &is, zoodb &db);
    int help(istream &is, zoodb &db);
};


