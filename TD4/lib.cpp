#include "lib.hpp"
#include <algorithm>
#include <cstdlib>

//===================================================================
//  Implémentations de vecteur<T>
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
    elements = new T[d];
    for (int i = 0; i < d; ++i)
        elements[i] = T();
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
    if (!elements)
    {
        std::cout << "Valeurs du vecteur non initialisées\n";
        return;
    }
    for (int i = 0; i < dim; ++i)
    {
        std::cout << "Element" << i << " = " << elements[i] << "\n";
    }
}

template <typename T>
void vecteur<T>::set_elements()
{
    if (dim <= 0)
    {
        std::cout << "Impossible : vecteur non initialisé ou taille nulle\n";
        return;
    }
    for (int i = 0; i < dim; ++i)
    {
        std::cout << "Entrez la valeur de l'élément " << i << ": ";
        std::cin >> elements[i];
    }
}

template <typename T>
T &vecteur<T>::operator[](int index)
{
    if (index < 0 || index >= dim)
    {
        std::cout << "Indice hors limites\n";
        throw vecteur_exception("ton message");
    }
    return elements[index];
}

template <typename T>
const T &vecteur<T>::operator[](int index) const
{
    if (index < 0 || index >= dim)
    {
        std::cout << "Indice hors limites\n";
        throw vecteur_exception("ton message");
    }
    return elements[index];
}

template <typename T>
vecteur<T> &vecteur<T>::operator=(const vecteur<T> &other)
{
    std::cout << "Appel de l'opérateur d'affectation\n";
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
    {
        std::cout << "Erreur: dimensions incompatibles pour l'addition\n";
        throw vecteur_exception("ton message");
    }
    vecteur<T> result(dim);
    for (int i = 0; i < dim; ++i)
        result[i] = elements[i] + other[i];
    return result;
}

template <typename T>
vecteur<T> &vecteur<T>::operator+=(const vecteur<T> &other)
{
    if (dim != other.dim || dim < 0)
    {
        std::cout << "Erreur: dimensions incompatibles pour l'addition\n";
        throw vecteur_exception("ton message");
    }
    for (int i = 0; i < dim; ++i)
        elements[i] += other[i];
    return *this;
}

//===================================================================
//  Implémentations de vecteur_intelligent<U>
//===================================================================

template <typename U>
vecteur_intelligent<U>::~vecteur_intelligent()
{
    std::cout << "Destructeur de vecteur_intelligent appelé\n";
    // Le tableau est libéré par le destructeur de vecteur<U>
}

template <typename U>
vecteur_intelligent<U> vecteur_intelligent<U>::operator+(const vecteur_intelligent<U> &other) const
{
    if (this->dim < 0 || other.dim < 0)
    {
        std::cout << "Erreur: vecteur non initialisé\n";
        throw vecteur_exception("ton message");
    }

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
    {
        std::cout << "Erreur: vecteur à ajouter non initialisé\n";
        throw vecteur_exception("ton message");
    }

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

// ===================================================================
//  INSTANCIATIONS EXPLICITES
// ===================================================================

// Pour vecteur<T>
template class vecteur<int>;
template class vecteur<double>;
template class vecteur<float>;

// Pour vecteur_intelligent<U>
template class vecteur_intelligent<int>;
template class vecteur_intelligent<double>;
template class vecteur_intelligent<float>;