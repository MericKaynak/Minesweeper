//
// Created by meric on 13/06/2024.
//

#ifndef ADRESSE_H
#define ADRESSE_H
#include <string>
#include <stdexcept>

bool isValidPlz(const std::string &str) {
    if (str.length() != 5) {
        return false;
    }

    for (char c : str) {
        if (c < '0' || c > '9') {
            return false;
        }
    }

    return true;
}

class Adresse {
private:
    std::string _plz;
    std::string _strasse;
    int _nr;
public:
    Adresse(std::string& plz,std::string& strasse,int const nr){
    if ((isValidPlz(plz)))
        throw std::invalid_argument("Plz ist nicht Verfuegbar");
    _plz=std::move(plz);
    _strasse=std::move(strasse);
    _nr=nr;
    }
    std::string getAdresse() const{
        return _plz+" "+_strasse+" "+std::to_string(_nr);
    }

    int setAdresse(std::string& plz,std::string &strasse,int const nr) {
        _plz=std::move(plz);
        _strasse=std::move(strasse);
        _nr=nr;
    };
};



#endif //ADRESSE_H
