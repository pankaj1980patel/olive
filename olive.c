#ifndef OLIVE_C_
#define OLIVE_C_

#include<stdint.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define return_defer(value) { result = (value);goto defer;}
#define Errno int

Errno olivec_save_to_ppm_file(uint32_t *pixels,size_t width,size_t height, const char *output_file_path){
    int result =0;
    FILE *f=NULL;

    {
        f = fopen(output_file_path,"wb");
        if (!f) 
        {
            return_defer(errno);
        }
        fprintf(f,"P6\n %zu %zu 255\n",width,height);
        if(ferror(f)) return_defer(errno);
        for(size_t i =0;i <height*width;++i)
        {
            uint32_t pixel = pixels[i];
            __uint8_t bytes[3] = 
            {
                (pixel>>(8*0))&0xFF,
                (pixel>>(8*1))&0xFF,
                (pixel>>(8*2))&0xFF,
            };
            fwrite(bytes, sizeof(bytes),1,f);
            if(ferror(f)) return_defer(errno);
        }
        if(ferror(f)) return_defer(errno);
    }

    defer :
        if(f) fclose(f);
        return result;
    return 0;
}
void olivec_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color){
    for(size_t i =0;i <height*width;++i){
        pixels[i] = color;
    }
}
#endif // OLIVE_C_