//
// Created by meric on 15/07/2024.
//

#ifndef STYLE_H
#define STYLE_H
#include <string>


class Style {

public:
    Style()=delete;
    static std::string getColor(int const value){
      switch (value) {
          case 1:
              return "blue";
          case 2:
              return "green";
          case 3:
              return "red";
          case 4:
              return "darkblue";
          case 5:
              return "darkred";
          case 6:
              return "aqua";
          case 7:
              return "black";
          case 8:
              return "grey";
          default:
              return "easter egg";
      }
    }
};



#endif //STYLE_H
