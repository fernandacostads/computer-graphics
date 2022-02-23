#ifndef COMPUTACAOGRAFICA_MATERIAL_HPP
#define COMPUTACAOGRAFICA_MATERIAL_HPP


class Material {
public:
    Material();
    Material(float pKa[3], float pKd[3], float pKs[3], double pm);
    double* getKa();
    double* getKd();
    double Ka[3];
    double Kd[3];
    double Ks[3];
    double m;
};


#endif
