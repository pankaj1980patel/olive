#include<stdio.h>
#include<stdint.h>
#include<errno.h>
#include<string.h>
#include "olive.c"

#define WIDTH 800
#define HEIGHT 600

static uint32_t pixels[HEIGHT*WIDTH];
void olivec_fill_rect(uint32_t *pixels, size_t pixels_width, size_t pixels_height, int x0, int y0, size_t w, size_t h, uint32_t color)
{
    for (int dy = 0; dy <(int)h; ++dy)
    {
        int y = y0 + dy;
        if(0<=y && y < (int)pixels_height){
            for (int  dx = 0; dx < (int)w; ++dx) 
            {
                int x = x0 + dx;
                if(0<=x && x<(int)pixels_width){
                    pixels[y*pixels_width+x] = color;
                }
            }
            
        }
    }
    
}

int main()
{
    //olivec_fill(pixels,WIDTH,HEIGHT,0xFF0000FF);
    size_t rw = 50 * 5;
    size_t rh = 30 * 5;
    olivec_fill_rect(pixels,WIDTH,HEIGHT,WIDTH/2 - rw/2 ,HEIGHT/2 - rh/2,rw,rh,0xFF2020FF);
    const char * file_path ="output.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT,file_path);
    if(err){
        fprintf(stderr,"ERROR: could not save file %s: %s\n", file_path, strerror(errno));
        return 1;
    }
    return 0;
}