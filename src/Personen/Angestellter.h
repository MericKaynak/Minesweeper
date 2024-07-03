//
// Created by meric on 29.05.24.
//

#ifndef ADVANCEDC_ANGESTELLTER_H
#define ADVANCEDC_ANGESTELLTER_H
#include <string>
#include "../Terminkalender.h"
#include "../Behandlungen/Behandlung.h"
#include <memory>
#include "../Adresse.h"


class Angestellter {
private:
    std::string _vorname;
    std::string _nachname;
    int _gehalt;
    static int nr;
    std::shared_ptr<Behandlung> _behandlungen;
    Terminkalender _tk;
public:
    Angestellter(std::string fn, std::string ln, int g);
    std::string getVorname();
    std::string getNachname();
    int getGehalt();
    int setGehalt(int g);
    int addBehandlung(Behandlung*Behandlung);
};
int Angestellter::nr=1;

#endif //ADVANCEDC_ANGESTELLTER_H
