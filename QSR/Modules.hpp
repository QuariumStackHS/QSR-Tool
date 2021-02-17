/*put includes here*/
#include "Modules/Mod_Admin.hpp"
#include "includes/Argser.hpp"
/*put your module in this function to add it*/
void Init_Modules(Argser *I){
    I->add_Module(Admin_main());

}