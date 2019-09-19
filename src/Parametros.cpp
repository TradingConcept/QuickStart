#include "Parametros.h"

// http://www.cplusplus.com/forum/unices/80716/

bool Parametros::ObtenerParametro(std::string& Result, std::string Application, std::string KeyName, std::string Default, std::string FileName)
{
    // Result = g_key_file_get_string(FileName, Application, KeyName, Default);
    return true ;
}

bool Parametros::EscribirParametro(std::string Application, std::string KeyName, std::string Value, std::string FileName)
{

    return true ;
}