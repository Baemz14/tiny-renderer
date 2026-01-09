#ifndef OBJEK
#define OBJEK

#include "../library/eigen/Eigen/Dense"
#include <deque>
#include <iostream>
#include <fstream>
#include <string>

struct Muka{
        Eigen::Vector4d p[3];
        TGAColor kale[3];
};

class Model{
    public:
        std::deque<Muka> mukas;
        Model(std::string namafile){

            //buat deque vertex
            std::deque<Eigen::Vector4d> vertices;

            //bukak file
            std::ifstream obj;
            obj.open(namafile);
            if(!obj.is_open())std::cout << "fail tokle buke\n";

            //baca file
            std::string konten;
            while(obj.good()){

                //baca setiap line
                std::getline(obj, konten);

                //asingkan setiap perkataan
                std::deque<std::string> perka;
                std::string tmp;
                for(char i: konten){
                    tmp += i;
                    if(i == ' '){
                        tmp.pop_back();
                        perka.push_back(tmp);
                        tmp.clear();
                    }
                }
                perka.push_back(tmp);

                //mencari vertex
                if(perka[0].compare("v") == 0){
                    Eigen::Vector4d vertex(std::stod(perka[1]), std::stod(perka[2]), std::stod(perka[3]), 1);
                    vertices.push_back(vertex);
                }

                //mencari face
                if(perka[0].compare("f") != 0)continue;
                std::deque<std::string> nilai_muka_V;
                std::string nilai;
                for(int i = 1; i< perka.size(); i++){
                    for(char j: perka[i]){
                        nilai += j;
                        if(j == '/'){
                            nilai.pop_back();
                            nilai_muka_V.push_back(nilai);
                            nilai.clear();
                            break;
                        }
                    }
                }
                Muka muka;
                //kita assume satu face ada 3 je vertex
                int kira[3] = {std::stoi(nilai_muka_V[0]), std::stoi(nilai_muka_V[1]), std::stoi(nilai_muka_V[2])};
                for(int i = 0; i < 3; i++){
                    muka.p[i] << vertices[kira[i]-1];
                    muka.kale[i] = TGAColor(255, 255, 255, 255);
                }
                mukas.push_back(muka);
            }

        }
        int total_muka(){
            return mukas.size();
        }
};

#endif