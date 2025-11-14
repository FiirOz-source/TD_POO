#ifndef LIB_HPP
#define LIB_HPP

#include <iostream>
#include <string>

// === Class vecteur ===
class vecteur
{
public:
    vecteur();
    vecteur(int dim);
    vecteur(int dim, float value);
    vecteur(const vecteur &); // constructeur de recopie
    ~vecteur();

    void affiche_vecteur(void);
    void set_elements(void);

private:
    float *elements;
    int dim;
};

#endif // LIB_HPP
