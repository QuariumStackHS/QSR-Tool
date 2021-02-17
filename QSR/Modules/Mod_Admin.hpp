#ifndef Mod_Admin
#define Mod_Admin 1
#include "../includes/Argser.hpp"
//using namespace Argser;
/*
Administrate Modules includes and binary
*/

void* Admin(Argser* IN){
    cout<<"Console Admin"<<endl;
    cout<<""<<endl;
}


Argser::QSRcModule Admin_main(){
    Argser::QSRcModule M;
    M.Set_Name("Ads");
    M.add_Cask("Admin-Page","Lets you manage Project",&Admin);
    return M;

}
#endif