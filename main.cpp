#include "header/tgaimage.h"
#include <iostream>
#include <cmath>
#include "header/pelukis.hpp"
#include "header/objek.hpp"
#include "library/eigen/Eigen/Dense"

const TGAColor PUTIH = TGAColor(255, 255, 255, 255);
const TGAColor MERAH   = TGAColor(255, 0,   0,   255);
const TGAColor BIRU   = TGAColor(0, 0,  255,   255);
const TGAColor HIJAU   = TGAColor(0, 255,  0,   255);

const int LEBAR = 800;
const float RATIO = 16.f/9.f;
const int TINGGI = int(fmax((float(LEBAR)/RATIO),1));

Eigen::Matrix4d M_persprojek;
Eigen::Matrix4d M_persprojek2;
Eigen::Matrix4d M_othviewing;
Eigen::Matrix4d M_perspektifviewing;

Eigen::Vector4d orthografik(Eigen::Vector4d point){
    return M_othviewing*point;
}

Eigen::Vector4d perspektif(Eigen::Vector4d point){
    Eigen::Vector4d vp = M_perspektifviewing*point;
    Eigen::Vector4d vp2(vp(0)/vp(3), vp(1)/vp(3), vp(2)/vp(3), vp(3)/vp(3));
    return vp2;
}

int main()
{
    //kamera---------------------------------------------------------------------------------
    Eigen::Vector3d e_kam(-1, 0, 1.8);// posisi kamera
    Eigen::Vector3d g_kam(0.5, 0, -1);// arah kamera tgk
    Eigen::Vector3d t_kam(0, 1, 0);

    Eigen::Vector3d w = -(g_kam.normalized());
    Eigen::Vector3d u = t_kam.cross(w);
    Eigen::Vector3d v = w.cross(u);
    
    Eigen::Matrix4d M1 = (Eigen::Matrix4d() << 
        u(0), u(1), u(2), 0,
        v(0), v(1), v(2), 0,
        w(0), w(1), w(2), 0,
        0,        0,   0, 1).finished();
    Eigen::Matrix4d M2 = (Eigen::Matrix4d() << 
        1, 0, 0, -e_kam(0),
        0, 1, 0, -e_kam(1),
        0, 0, 1, -e_kam(2),
        0, 0, 0,     1).finished();
    Eigen::Matrix4d M_kam = M1*M2;

    //viewport--------------------------------------------------------------------------------
    Eigen::Matrix4d M_vew = (Eigen::Matrix4d() <<
        LEBAR/2.f,  0, 0,  (LEBAR-1)/2.f,
        0, TINGGI/2.f, 0, (TINGGI-1)/2.f,
        0,          0, 1,              0,
        0,          0, 0,              1).finished();

    //orthographic proj------------------------------------------------------------------------
    float fov = 59;
    float skalar = 1;
    float n = -1;
    float f = -(std::numeric_limits<float>::max());
    float t = skalar*abs(n)*tan((fov/2.f)*(M_PI/180.f));
    float b = -t;
    float r = t*(LEBAR/float(TINGGI));
    float l = -r;
    Eigen::Matrix4d M_oth = (Eigen::Matrix4d() << 
        2/(r-l),       0,       0, -((r+l)/(r-l)),
                0, 2/(t-b),       0, -((t+b)/(t-b)),
                0,       0, 2/(n-f), -((n+f)/(n-f)),
                0,       0,       0,              1).finished();

    //perspectif projektion--------------------------------------------------------------------
    Eigen::Matrix4d M_perp = (Eigen::Matrix4d() <<
        n, 0,   0,        0,
        0, n,   0,        0,
        0, 0, n+f, -1*(f*n),
        0, 0,   1,        0).finished();

    //pengiraan viewing transform--------------------------------------------------------------------------------------
    M_othviewing = (M_vew*M_oth)*M_kam;
    M_persprojek = M_perp*M_kam;
    M_persprojek2 = M_vew*M_oth;
    M_perspektifviewing = (M_vew*M_oth)*M_perp*M_kam;

    //pembuatan model---------------------------------------------------------------------------
    Model kubus("model/african_head.obj");

    //render perspektif------------------------------------------------------------------------------------
    TGAImage gambar_perspektif(LEBAR, TINGGI, TGAImage::RGB);
        for(Muka muka: kubus.mukas){
            Eigen::Vector4d pv[3];
            for(int i=0;i<3;i++){
                pv[i] = perspektif(muka.p[i]);
            }
                LukisLine(int(round(pv[0](0))), int(round(pv[0](1))), int(round(pv[1](0))), int(round(pv[1](1))), gambar_perspektif, PUTIH);
                LukisLine(int(round(pv[0](0))), int(round(pv[0](1))), int(round(pv[2](0))), int(round(pv[2](1))), gambar_perspektif, PUTIH);
                LukisLine(int(round(pv[1](0))), int(round(pv[1](1))), int(round(pv[2](0))), int(round(pv[2](1))), gambar_perspektif, PUTIH);
        }

        gambar_perspektif.flip_vertically();
        gambar_perspektif.write_tga_file("gambar_perspektif.tga");

    //render orthografik------------------------------------------------------------------------------------
    TGAImage gambar_orthografik(LEBAR, TINGGI, TGAImage::RGB);
        for(Muka muka: kubus.mukas){
            Eigen::Vector4d pv[3];
            for(int i=0;i<3;i++){
                pv[i] = orthografik(muka.p[i]);
            }
                LukisLine(int(round(pv[0](0))), int(round(pv[0](1))), int(round(pv[1](0))), int(round(pv[1](1))), gambar_orthografik, PUTIH);
                LukisLine(int(round(pv[0](0))), int(round(pv[0](1))), int(round(pv[2](0))), int(round(pv[2](1))), gambar_orthografik, PUTIH);
                LukisLine(int(round(pv[1](0))), int(round(pv[1](1))), int(round(pv[2](0))), int(round(pv[2](1))), gambar_orthografik, PUTIH);
        }

        gambar_orthografik.flip_vertically();
        gambar_orthografik.write_tga_file("gambar_orthografik.tga");
}