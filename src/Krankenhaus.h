//
// Created by meric on 29.05.24.
//
#ifndef ADVANCEDC_KRANKENHAUS_H
#define ADVANCEDC_KRANKENHAUS_H
#include <string>
#include <vector>
#include "Personen/Patient.h"
#include "Personen/Angestellter.h"

class Krankenhaus {
private:
    std::string _name;
    std::vector<Patient> _patienten;
    std::vector<Angestellter> _angestellten;
public:
    int addPatient(Patient &p);
    int addAngestellter(Angestellter &p);
    int deletePatient(int nr);
    int deleteAngestellter(int nr);
    int behandeln(int pnr,int anr,double duration);
    int printTermin();
};


#endif //ADVANCEDC_KRANKENHAUS_H
