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

    float &operator[](int index);

    vecteur &operator=(const vecteur &other);
    vecteur operator+(const vecteur &other) const;
    vecteur &operator+=(const vecteur &other);

protected: // passage protected car on veut que ça soit visible par les classes qui héritent
    float *elements;
    int dim;
};

class vecteur_intelligent : public vecteur
{
public:
    vecteur_intelligent() : vecteur() {};
    vecteur_intelligent(int dim) : vecteur(dim) {};
    vecteur_intelligent(int dim, float value) : vecteur(dim, value) {};
    vecteur_intelligent(const vecteur_intelligent &v) : vecteur(v) {}; // constructeur de recopie
    ~vecteur_intelligent();

    vecteur_intelligent operator+(const vecteur_intelligent &other);
    vecteur_intelligent &operator+=(const vecteur_intelligent &other);
};

#endif // LIB_HPP
