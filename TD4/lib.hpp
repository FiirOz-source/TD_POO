#ifndef LIB_HPP
#define LIB_HPP

#include <iostream>
#include <string>
#include <stdexcept>

class vecteur_exception : public std::runtime_error
{
public:
    explicit vecteur_exception(const std::string &msg)
        : std::runtime_error(msg.c_str()) {}
};

//===================================================================
//  Classe template générique vecteur<T>
//===================================================================
template <typename T>
class vecteur
{
public:
    vecteur();
    vecteur(int dim);
    vecteur(int dim, T value);
    vecteur(const vecteur &other);
    ~vecteur();

    void affiche_vecteur() const;
    void set_elements();

    T &operator[](int index);
    const T &operator[](int index) const;

    vecteur &operator=(const vecteur &other);
    vecteur operator+(const vecteur &other) const;
    vecteur &operator+=(const vecteur &other);

protected:
    T *elements;
    int dim;
};

//===================================================================
//  Classe template vecteur_intelligent<U>
//  hérite de vecteur<U> – type variable
//===================================================================
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