#include "ILI9341_driver.h"
#include "game.h"

#include <stdint.h>


int main(){
    ILI9341_Init();

    fill_screen('w');

    ball game_ball = bouncing_ball_init(200, 120, 10);

	while(1){
        //move_ball(&game_ball);
    }
}
