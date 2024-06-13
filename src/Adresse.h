//
// Created by meric on 13/06/2024.
//

#ifndef ADRESSE_H
#define ADRESSE_H
#include <string>


class Adresse {
private:
    std::string _plz;
    std::string _strasse;
    int _nr;
public:
    Adresse(std::string plz,std::string strasse,int nr);
    std::string getAdresse();
    int setAdresse(std::string plz,std::string strasse,int nr);
};



#endif //ADRESSE_H
