#include <Blockchain.h>
#include "menu_functions.h"

int main()
{
    Block::Blockchain blockchain;
    functions menu_funcs = init_menu_choices();
    try
    {
        for(unsigned result; (result = show_menu()); pause_menu())
        {
            menu_funcs[result](blockchain);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
