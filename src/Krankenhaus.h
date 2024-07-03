//
// Created by meric on 29.05.24.
//
#ifndef ADVANCEDC_KRANKENHAUS_H
#define ADVANCEDC_KRANKENHAUS_H
#include <string>
#include <vector>
#include "Personen/Patient.h"
#include "Personen/Angestellter.h"
#include <memory>
#include "Datum.h"

class Krankenhaus {
private:
    static Krankenhaus* instance;
    std::string _name;
    double _schmoney;
    std::shared_ptr<Patient> _patienten;
    std::shared_ptr<Angestellter> _angestellten;
    Krankenhaus();
public:
    static Krankenhaus getInstance();
    int addPatient(Patient &p);
    int addAngestellter(Angestellter &p);
    int deletePatient(int nr);
    int deleteAngestellter(int nr);
    int behandeln(int pnr,int anr,double duration, Datum datum);
    int printTermin();
};


#endif //ADVANCEDC_KRANKENHAUS_H
