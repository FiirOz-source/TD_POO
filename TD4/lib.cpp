#include "lib.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>

//===================================================================
// Implémentations de vecteur<T>
//===================================================================

template <typename T>
vecteur<T>::vecteur()
{
    std::cout << "Appel du constructeur vide pour vecteur\n";
    dim = -1;
    elements = nullptr;
}

template <typename T>
vecteur<T>::vecteur(int d)
{
    std::cout << "Appel du constructeur avec dimension pour vecteur\n";
    if (d < 0)
    {
        std::cout << "Error, dim < 0\n";
        dim = -1;
        elements = nullptr;
        return;
    }
    elements = new T[d]();
    dim = d;
}

template <typename T>
vecteur<T>::vecteur(int d, T value)
{
    std::cout << "Appel du constructeur avec dimension et valeur pour vecteur\n";
    if (d < 0)
    {
        std::cout << "Error, dim < 0\n";
        dim = -1;
        elements = nullptr;
        return;
    }
    elements = new T[d];
    for (int i = 0; i < d; ++i)
        elements[i] = value;
    dim = d;
}

template <typename T>
vecteur<T>::vecteur(const vecteur &other)
{
    std::cout << "Appel du constructeur de recopie pour vecteur\n";
    dim = other.dim;
    if (dim > 0)
    {
        elements = new T[dim];
        for (int i = 0; i < dim; ++i)
            elements[i] = other.elements[i];
    }
    else
    {
        elements = nullptr;
    }
}

template <typename T>
vecteur<T>::~vecteur()
{
    std::cout << "Destructeur de vecteur appelé\n";
    delete[] elements;
}

template <typename T>
void vecteur<T>::affiche_vecteur() const
{
    if (dim < 0)
    {
        std::cout << "Vecteur non initialisé\n";
        return;
    }
    std::cout << *this << "\n"; // Utilise operator<<
}

template <typename T>
void vecteur<T>::set_elements()
{
    if (dim <= 0)
    {
        std::cout << "Impossible : vecteur non initialisé ou taille nulle\n";
        return;
    }
    std::cin >> *this; // Utilise operator>>
}

template <typename T>
T &vecteur<T>::operator[](int index)
{
    if (index < 0 || index >= dim)
        throw vecteur_exception("Indice hors limites");
    return elements[index];
}

template <typename T>
const T &vecteur<T>::operator[](int index) const
{
    if (index < 0 || index >= dim)
        throw vecteur_exception("Indice hors limites");
    return elements[index];
}

template <typename T>
vecteur<T> &vecteur<T>::operator=(const vecteur<T> &other)
{
    if (this == &other)
        return *this;
    if (dim != other.dim)
    {
        delete[] elements;
        dim = other.dim;
        elements = (dim > 0) ? new T[dim] : nullptr;
    }
    for (int i = 0; i < dim; ++i)
        elements[i] = other.elements[i];
    return *this;
}

template <typename T>
vecteur<T> vecteur<T>::operator+(const vecteur<T> &other) const
{
    if (dim != other.dim || dim < 0)
        throw vecteur_exception("dimensions incompatibles pour +");
    vecteur<T> result(dim);
    for (int i = 0; i < dim; ++i)
        result[i] = elements[i] + other[i];
    return result;
}

template <typename T>
vecteur<T> &vecteur<T>::operator+=(const vecteur<T> &other)
{
    if (dim != other.dim || dim < 0)
        throw vecteur_exception("dimensions incompatibles pour +=");
    for (int i = 0; i < dim; ++i)
        elements[i] += other[i];
    return *this;
}

//===================================================================
// Surcharge << et >> pour vecteur<T>
//===================================================================

template <typename T>
std::ostream &operator<<(std::ostream &os, const vecteur<T> &v)
{
    if (v.dim < 0)
    {
        os << "[ Vecteur non initialisé ]";
        return os;
    }
    os << "[ ";
    for (int i = 0; i < v.dim; ++i)
    {
        os << v.elements[i];
        if (i < v.dim - 1)
            os << ", ";
    }
    os << " ]";
    return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, vecteur<T> &v)
{
    std::cout << "Entrez la dimension du vecteur : ";
    int nouvelle_dim;
    if (!(is >> nouvelle_dim))
    {
        is.setstate(std::ios::failbit);
        return is;
    }
    if (nouvelle_dim < 0)
    {
        is.setstate(std::ios::failbit);
        return is;
    }

    delete[] v.elements;
    v.dim = nouvelle_dim;
    v.elements = nouvelle_dim > 0 ? new T[nouvelle_dim] : nullptr;

    std::cout << "Entrez " << nouvelle_dim << " éléments :\n";
    for (int i = 0; i < nouvelle_dim; ++i)
    {
        std::cout << "Element[" << i << "] = ";
        if (!(is >> v.elements[i]))
        {
            delete[] v.elements;
            v.elements = nullptr;
            v.dim = -1;
            is.setstate(std::ios::failbit);
            return is;
        }
    }
    return is;
}

//===================================================================
// Implémentations de vecteur_intelligent<U>
//===================================================================

template <typename U>
vecteur_intelligent<U>::~vecteur_intelligent()
{
    std::cout << "Destructeur de vecteur_intelligent appelé\n";
}

template <typename U>
vecteur_intelligent<U> vecteur_intelligent<U>::operator+(const vecteur_intelligent<U> &other) const
{
    if (this->dim < 0 || other.dim < 0)
        throw vecteur_exception("vecteur non initialisé");

    int max_dim = std::max(this->dim, other.dim);
    vecteur_intelligent<U> result(max_dim);
    int min_dim = std::min(this->dim, other.dim);

    for (int i = 0; i < min_dim; ++i)
        result[i] = this->elements[i] + other.elements[i];
    for (int i = min_dim; i < this->dim; ++i)
        result[i] = this->elements[i];
    for (int i = min_dim; i < other.dim; ++i)
        result[i] = other.elements[i];

    return result;
}

template <typename U>
vecteur_intelligent<U> &vecteur_intelligent<U>::operator+=(const vecteur_intelligent<U> &other)
{
    if (other.dim < 0)
        throw vecteur_exception("vecteur à ajouter non initialisé");

    if (this->dim < other.dim)
    {
        U *nouveau = new U[other.dim];
        for (int i = 0; i < this->dim; ++i)
            nouveau[i] = this->elements[i] + other.elements[i];
        for (int i = this->dim; i < other.dim; ++i)
            nouveau[i] = other.elements[i];
        delete[] this->elements;
        this->elements = nouveau;
        this->dim = other.dim;
    }
    else
    {
        for (int i = 0; i < other.dim; ++i)
            this->elements[i] += other.elements[i];
    }
    return *this;
}

//===================================================================
// Surcharge << et >> pour vecteur_intelligent<U>
//===================================================================

template <typename U>
std::ostream &operator<<(std::ostream &os, const vecteur_intelligent<U> &v)
{
    return operator<<(os, static_cast<const vecteur<U> &>(v));
}

template <typename U>
std::istream &operator>>(std::istream &is, vecteur_intelligent<U> &v)
{
    return operator>>(is, static_cast<vecteur<U> &>(v));
}

//===================================================================
// INSTANCIATIONS EXPLICITES (OBLIGATOIRE !)
//===================================================================

// Pour vecteur<T>
template class vecteur<int>;
template class vecteur<double>;
template class vecteur<float>;

// Pour vecteur_intelligent<U>
template class vecteur_intelligent<int>;
template class vecteur_intelligent<double>;
template class vecteur_intelligent<float>;

// Instanciation des opérateurs << et >>
template std::ostream &operator<< <int>(std::ostream &, const vecteur<int> &);
template std::ostream &operator<< <double>(std::ostream &, const vecteur<double> &);
template std::ostream &operator<< <float>(std::ostream &, const vecteur<float> &);

template std::istream &operator>> <int>(std::istream &, vecteur<int> &);
template std::istream &operator>> <double>(std::istream &, vecteur<double> &);
template std::istream &operator>> <float>(std::istream &, vecteur<float> &);

template std::ostream &operator<< <int>(std::ostream &, const vecteur_intelligent<int> &);
template std::ostream &operator<< <double>(std::ostream &, const vecteur_intelligent<double> &);
template std::ostream &operator<< <float>(std::ostream &, const vecteur_intelligent<float> &);

template std::istream &operator>> <int>(std::istream &, vecteur_intelligent<int> &);
template std::istream &operator>> <double>(std::istream &, vecteur_intelligent<double> &);
template std::istream &operator>> <float>(std::istream &, vecteur_intelligent<float> &);