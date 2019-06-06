#include <iostream>
#include <string>
#include <vector>
#include "info.h"
#include "user.h"
#include "publisher.h"
#include "customer.h"
#include "manager.h"
#include "commandprocessor.h"
#include "exceptions.h"
using namespace std;

int main()
{   
    Manager* main_manager = new Manager();
    CommandProcessor main_handler;
    MI central_info; 
    main_handler.set_manager(main_manager);
    do
    {
        main_handler.general_process_command(central_info);
    } while (central_info.system_sit!=SYSTEM_QUIT);
    
    return 0;
}