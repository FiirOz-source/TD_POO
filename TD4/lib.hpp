#ifndef LIB_HPP
#define LIB_HPP

#include <iostream>
#include <string>

// === Template Class vecteur ===
template <typename T> // T est le type variable
class vecteur
{
public:
    vecteur();
    vecteur(int dim);
    vecteur(int dim, T value);
    vecteur(const vecteur &); // constructeur de recopie
    ~vecteur();

    void affiche_vecteur(void);
    void set_elements(void);

    T &operator[](int index);
    const T &operator[](int index) const;
    vecteur &operator=(const vecteur &other);
    vecteur operator+(const vecteur &other) const;
    vecteur &operator+=(const vecteur &other);

protected: // passage protected car on veut que ça soit visible par les classes qui héritent
    T *elements;
    int dim;
};

template <typename U>
class vecteur_intelligent : public vecteur<U>
{
public:
    vecteur_intelligent() : vecteur<U>() {}
    vecteur_intelligent(int dim) : vecteur<U>(dim) {}
    vecteur_intelligent(int dim, U value) : vecteur<U>(dim, value) {}
    vecteur_intelligent(const vecteur_intelligent &v) : vecteur<U>(v) {}

    ~vecteur_intelligent();

    vecteur_intelligent operator+(const vecteur_intelligent &other) const;
    vecteur_intelligent &operator+=(const vecteur_intelligent &other);
};

#endif // LIB_HPP
