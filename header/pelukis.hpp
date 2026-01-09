#ifndef PELUKIS
#define PELUKIS
#include "tgaimage.h"
#include <iostream>
#include <cmath>

void pempasti(int &n0, int &m0, int &n1, int &m1){
    if(n1<n0){
        //std::cout << "test\n";
        int tmp = n1;
        n1 = n0;
        n0 = tmp;

        tmp = m1;
        m1 = m0;
        m0 = tmp;
    }
}

void LukisLine(int x0, int y0, int x1, int y1, TGAImage &gambar, TGAColor kale){
    float m = float(float(y1) - y0)/float(float(x1) - x0);
    if(m<-1||m>=1)pempasti(y0, x0, y1, x1);
    else{pempasti(x0, y0, x1, y1);}

    //loop lukisan
    if(m>=0&&m<1){
        int y = y0;
        for(int x = x0;x< x1;x++){
            gambar.set(x, y, kale);
            if(((y0-y1)*(x+1)+(x1-x0)*(y+0.5)+x0*y1-x1*y0)<0)y++;
        }
    }
    else if(m>=-1&&m<0){
        int y = y0;
        for(int x = x0;x< x1;x++){
            gambar.set(x, y, kale);
            if(((y0-y1)*(x+1)+(x1-x0)*(y+0.5)+x0*y1-x1*y0)>0)y--;
        }
    }
    else if(m<-1){
        int x = x0;
        for(int y = y0;y< y1;y++){
            gambar.set(x, y, kale);
            if(((y0-y1)*(x+0.5)+(x1-x0)*(y+1)+x0*y1-x1*y0)<0)x--;  
        }
    }
    else{
        int x = x0;
        for(int y = y0;y< y1;y++){
            gambar.set(x, y, kale);
            if(((y0-y1)*(x+0.5)+(x1-x0)*(y+1)+x0*y1-x1*y0)>0)x++;  
        }
    }  
}

#endif