#pragma once
#include "std_lib_inc.h"

inline void errornr(int code)
{

    switch(code)
    {
        case 100: cout << "100: Alles erfolgreich.\n"; break;
        case 101: cout << "101: Befehl ist unbekannt.\n"; break;
        case 102: cout << "102: Ein Parameter eines Befehls konnte nicht gelesen werden.\n"; break;
        case 201: cout << "201: Gehege kann nicht geloescht werden.\n"; break;
        case 202: cout << "202: Tier kann nicht geloescht werden.\n"; break;
        case 301: cout << "301: Eine solche Zuordnung existiert nicht.\n"; break;
        case 302: cout << "302: Eine solche Zuordnung existiert bereits.\n"; break;
        case 401: cout << "401: Eine solches Gehege existiert nicht.\n"; break;
        case 402: cout << "402: Ein solches Tier existiert nicht.\n"; break;
        case 501: cout << "501: Das Gehege ist voll.\n"; break;
        case 502: cout << "502: Das Tier ist einem anderen Gehege zugeordnet.\n"; break;
        case 601: cout << "601: Datei kann nicht geoeffnet werden.\n"; break;
        case 602: cout << "602: Datei hat ein unbekanntes Format.\n"; break;
        case 603: cout << "603: Datei kann nicht geschrieben werden.\n"; break;
        default:  cout << code << ": Unbekannter Code.\n"; break;
    }
}