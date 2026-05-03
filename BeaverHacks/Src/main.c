#include "ILI9341_driver.h"

#include <stdint.h>


int main(){
    ILI9341_Init();

	while(1){
        draw_Square(0, 239, 0, 319, 'b');
        draw_Square(0, 239, 0, 319, 'w');
    }
}
