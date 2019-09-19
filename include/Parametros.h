#pragma once

#include <iostream>
#include <string>

class Parametros {

public:

    static bool ObtenerParametro(std::string& Result, std::string Application, std::string KeyName, std::string Default, std::string FileName);
    static bool EscribirParametro(std::string Application, std::string KeyName, std::string Value, std::string FileName);

};