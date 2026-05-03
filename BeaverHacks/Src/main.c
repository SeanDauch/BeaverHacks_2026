#include "ILI9341_driver.h"
#include "pong.h"

#include <stdint.h>


int main(){
    ILI9341_Init();

    fill_screen('w');

    game my_game = game_init(10, 20);

    play_game(&my_game);
    
	while(1){

    }
}
