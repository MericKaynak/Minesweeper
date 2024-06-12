//
// Created by meric on 29.05.24.
//

#ifndef ADVANCEDC_PATIENT_H
#define ADVANCEDC_PATIENT_H
#include <string>
#include "Terminkalender.h"

class Patient {
private:
   std::string _firstName;
   std::string _lastName;
   int _gehalt;
   static int nr;
   Terminkalender _tk;
   Patient(std::string fn, std::string ln, int g);
public:
    std::string getFirstName();
    std::string getLastName();
    std::string getName();
};

int Patient::nr=1;

#endif //ADVANCEDC_PATIENT_H
