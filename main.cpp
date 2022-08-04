#include <Blockchain.h>
#include "menu_functions.h"

int main()
{
    Block::Blockchain blockchain;
    Block::Key my_key;
    my_key.generate();
    my_key.save_private_key("my_private_key.md");
    my_key.save_public_key("my_public_key.md");
    functions funcs = init_menu_choices();
    unsigned result = 0;
    while(true)
    {
        show_menu();
        std::cin >> result;
        if(result > 5)
        {
            clear();
            std::cout << "Wrong choice!" << std::endl;
            continue;
        }
        if(result == 0) break;
        funcs[result](blockchain,my_key);
        std::cout << "Press any key" << std::endl;
        std::cin.get();
        std::cin.get();
        clear();
    }
}
