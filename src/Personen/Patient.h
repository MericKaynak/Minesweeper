//
// Created by meric on 29.05.24.
//

#ifndef ADVANCEDC_PATIENT_H
#define ADVANCEDC_PATIENT_H
#include <string>
#include "../Terminkalender.h"
#include "../Behandlungen/Behandlung.h"
#include <memory>
#include "../Adresse.h"

class Patient {
private:
   std::string _firstName;
   std::string _lastName;
   static int nr;
   Adresse _adresses;
   std::shared_ptr<Behandlung> _behandlungen;
public:
    Patient(std::string fn, std::string ln, Adresse a);
    std::string getFirstName();
    std::string getLastName();
    Adresse getAdresse();
    std::string getInfo();
    void addBehandlung(Behandlung * b);
};

int Patient::nr=1;

#endif //ADVANCEDC_PATIENT_H
