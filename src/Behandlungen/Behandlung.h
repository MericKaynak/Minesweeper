//
// Created by meric on 13/06/2024.
//

#ifndef BEHANDLUNG_H
#define BEHANDLUNG_H


#include "BehandlungTypen.h"
#include "../Personen/Angestellter.h"
#include "../Personen/Patient.h"
#include "../Datum.h"
#include <memory>

class Behandlung {
private:
    std::shared_ptr<Angestellter> _behandler;
    std::shared_ptr<Patient> _patient;
    int _typ;
    Datum _date;
public:
    Behandlung(Angestellter ag,Patient p, int typ,Datum d);
    void setTyp(int t);
    void setDatum(Datum d);
};



#endif //BEHANDLUNG_H
