//
// Created by meric on 29.05.24.
//

#ifndef ADVANCEDC_ANGESTELLTER_H
#define ADVANCEDC_ANGESTELLTER_H
#include "../Terminkalender.h"
#include <string>
class Angestellter {
private:
    std::string _vorname;
    std::string _nachname;
    int _gehalt;
    static int nr;
    Terminkalender _tk;
public:
    Angestellter(std::string fn, std::string ln, int g);
    std::string getVorname();
    std::string getNachname();
    int getGehalt();
    int setGehalt(int g);
    int set
};


#endif //ADVANCEDC_ANGESTELLTER_H
