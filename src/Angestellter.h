//
// Created by meric on 29.05.24.
//

#ifndef ADVANCEDC_ANGESTELLTER_H
#define ADVANCEDC_ANGESTELLTER_H
#include "Patient.h"
#include <string>
class Angestellter {
private:
    std::string _firstName;
    std::string _lastName;
    int _gehalt;
    static int nr;
    Terminkalender _tk;
public:
    Angestellter(std::string fn, std::string ln, int g);
    std::string getFirstName();
    std::string getLastName();
    std::string getName();
};


#endif //ADVANCEDC_ANGESTELLTER_H
