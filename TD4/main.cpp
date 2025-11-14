#include "lib.hpp"

template <typename T>
vecteur<T>::~vecteur()
{
    std::cout << "Destructeur de Vecteur appelé\n";
}

template <typename T>
vecteur_intelligent<T>::~vecteur_intelligent()
{
    std::cout << "Destructeur de Vecteur appelé\n";
}

template <typename T>
vecteur<T>::vecteur()
{
    std::cout << "Appel du constructeur vide pour vecteur\n";
    dim = -1;
    elements = nullptr;
}

template <typename T>
vecteur<T>::vecteur(int dim)
{
    std::cout << "Appel du constructeur avec dimension pour vecteur\n";
    if (dim < 0)
    {
        std::cout << "Error, dim < 0\n";
        return;
    }
    elements = new float[dim];
    for (int i = 0; i < dim; i++)
    {
        elements[i] = 0.0f;
    }
    this->dim = dim;
}

template <typename T>
vecteur<T>::vecteur(int dim, T value)
{
    std::cout << "Appel du constructeur avec dimension et valeur pour vecteur\n";

    if (dim < 0)
    {
        std::cout << "Error, dim < 0\n";
        return;
    }
    elements = new float[dim];
    for (int i = 0; i < dim; i++)
    {
        elements[i] = value;
    }
    this->dim = dim;
}

template <typename T>
vecteur<T>::vecteur(const vecteur &other)
{
    std::cout << "Appel du constructeur de recopie pour vecteur\n";
    dim = other.dim;

    if (dim > 0)
    {
        elements = new T[dim];
        for (int i = 0; i < dim; i++)
        {
            elements[i] = other.elements[i];
        }
    }
    else
    {
        elements = nullptr;
    }
}

template <typename T>
void vecteur<T>::affiche_vecteur(void)
{
    if (dim < 0)
    {
        std::cout << "Vecteur non initialisé\n";
        return;
    }
    if (elements == NULL)
    {
        std::cout << "Valeurs du vecteur non initialisées\n";
        return;
    }

    for (int i = 0; i < dim; i++)
    {
        std::cout << "Element" << i << " = " << elements[i] << "\n";
    }
}

template <typename T>
void vecteur<T>::set_elements(void)
{
    for (int i = 0; i < dim; i++)
    {
        std::cout << "Entrez la valeur de l'élement" << i << ": ";
        std::cin >> elements[i];
    }
}

template <typename T>
T &vecteur<T>::operator[](int index)
{
    if (index < 0 || index >= dim)
    {
        std::cout << ("Indice hors limites\n");
        exit(EXIT_FAILURE);
    }
    return elements[index];
}

template <typename T>
vecteur<T> &vecteur::operator=(const vecteur &other)
{
    std::cout << "Appel de l'opérateur d'affectation\n";

    if (this == &other)
    {
        return *this;
    }

    if (dim != other.dim)
    {
        delete[] elements;
        dim = other.dim;
        elements = (dim > 0) ? new T[dim] : nullptr;
    }

    for (int i = 0; i < dim; i++)
    {
        elements[i] = other.elements[i];
    }
    return *this;
}

template <typename T>
vecteur<T> vecteur::operator+(const vecteur &other) const
{
    if (dim != other.dim)
    {
        std::cout << "Erreur: dimensions incompatibles pour l'addition\n";
        exit(EXIT_FAILURE);
    }
    vecteur result(dim);
    for (int i = 0; i < dim; i++)
    {
        result.elements[i] = elements[i] + other.elements[i];
    }
    return result;
}

template <typename T>
vecteur<T> &vecteur::operator+=(const vecteur &other)
{
    if (dim != other.dim)
    {
        std::cout << "Erreur: dimensions incompatibles pour l'addition\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < dim; i++)
    {
        elements[i] += other.elements[i];
    }
    return *this;
}

template <typename T>
vecteur_intelligent<T> vecteur_intelligent::operator+(const vecteur_intelligent &other)
{
    int max_value = (dim > other.dim ? dim : other.dim);
    vecteur_intelligent result(max_value);
    if (dim < other.dim)
    {
        std::cout << "Dim < other.dim\n";

        int temp = other.dim - dim;
        for (int i = 0; i < temp; i++)
        {
            elements[dim + i] = 0.0f;
        }
        dim = other.dim;

        for (int i = 0; i < dim; i++)
        {
            result.elements[i] = elements[i] + other.elements[i];
        }
    }
    else if (dim > other.dim)
    {
        std::cout << "Dim > other.dim\n";
        for (int i = 0; i < other.dim; i++)
        {
            result.elements[i] = elements[i] + other.elements[i];
        }
        for (int i = other.dim; i < dim; i++)
        {
            result.elements[i] = elements[i];
        }
    }
    else
    {
        std::cout << "Dim == other.dim\n";
        for (int i = 0; i < dim; i++)
        {
            result.elements[i] = elements[i] + other.elements[i];
        }
    }
    return result;
}

template <typename T>
vecteur_intelligent<T> &vecteur_intelligent::operator+=(const vecteur_intelligent &other)
{
    if (dim < other.dim)
    {
        std::cout << "Dim < other.dim\n";
        int temp = other.dim - dim;
        for (int i = 0; i < temp; i++)
        {
            elements[dim + i] = 0.0f;
        }
        dim = other.dim;

        for (int i = 0; i < dim; i++)
        {
            elements[i] += other.elements[i];
        }
    }
    else if (dim > other.dim)
    {
        std::cout << "Dim > other.dim\n";
        for (int i = 0; i < other.dim; i++)
        {
            elements[i] += other.elements[i];
        }
    }
    else
    {
        std::cout << "Dim == other.dim\n";
        for (int i = 0; i < dim; i++)
        {
            elements[i] += other.elements[i];
        }
    }
    return *this;
}

int main()
{

    std::cout << "Début des tests des constructeurs\n";
    vecteur vec1;
    vecteur vec2(5);
    vecteur vec3(8, 3.2f);
    vecteur vec4(vec3);

    std::cout << "Début des tests des fonctions d'affichage et de set\n";
    vec1.affiche_vecteur();
    std::cout << "Vec2 sans valeurs :\n";
    vec2.affiche_vecteur();
    std::cout << "Vec2 set valeurs :\n";
    vec2.set_elements();
    std::cout << "Vec2 avec valeurs :\n";
    vec2.affiche_vecteur();
    std::cout << "Vec3 :\n";
    vec3.affiche_vecteur();
    std::cout << "Vec4 :\n";
    vec4.affiche_vecteur();

    // Test de l'opérateur []
    std::cout << "Accès au 2ème élément de vec 3: " << vec3[1] << "\n";
    vec3[3] = 4.2f;
    std::cout << "Après modification vec3 : ";
    vec3.affiche_vecteur();

    // Test de l'opérateur d'affectation
    std::cout << "\nCopie vec2 dans vec3 via = \n";
    vec3 = vec2;
    std::cout << "vec3 devient : ";
    vec3.affiche_vecteur();

    // Test de +
    std::cout << "\nSomme vec4 = vec3 + vec2\n";
    vec4 = vec3 + vec2;
    std::cout << "vec4 : ";
    vec4.affiche_vecteur();

    // Test de +=
    std::cout << "\nApplication de vec2 += vec3\n";
    vec2 += vec3;
    std::cout << "vec3 : ";
    vec2.affiche_vecteur();

    std::cout << "-----TEST TD 3-----\n";

    vecteur_intelligent vecint1;
    vecteur_intelligent vecint2(5);
    vecteur_intelligent vecint3(8, 3.2f);
    vecteur_intelligent vecint4(vecint3);
    vecteur_intelligent vecint5(15, 1.0f);
    vecteur_intelligent vecint6(2, 1.0f);

    std::cout << "Début des tests des fonctions d'affichage et de set\n";
    vecint1.affiche_vecteur();
    std::cout << "Vecint2 sans valeurs :\n";
    vecint2.affiche_vecteur();
    std::cout << "Vecint2 set valeurs :\n";
    vecint2.set_elements();
    std::cout << "Vecint2 avec valeurs :\n";
    vecint2.affiche_vecteur();
    std::cout << "Vecint3 :\n";
    vecint3.affiche_vecteur();
    std::cout << "Vecint4 :\n";
    vecint4.affiche_vecteur();

    // Test de l'opérateur []
    std::cout << "Accès au 2ème élément de vec 3: " << vecint3[1] << "\n";
    vecint3[3] = 4.2f;
    std::cout << "Après modification vec3 : ";
    vecint3.affiche_vecteur();

    // Test de l'opérateur d'affectation
    std::cout << "\nCopie vecint2 dans vecint3 via = \n";
    vecint3 = vecint2;
    std::cout << "vecint3 devient : ";
    vecint3.affiche_vecteur();

    // Test de +
    std::cout << "\nSomme vecint4 = vecint5 + vecint3\n";
    std::cout << "vecint3 : \n";
    vecint3.affiche_vecteur();
    std::cout << "vecint5 : \n";
    vecint5.affiche_vecteur();
    vecint4 = vecint5 + vecint3;
    std::cout << "vecint4 : \n";
    vecint4.affiche_vecteur();

    vecteur_intelligent vecint10(6, 3.5f);
    std::cout << "vecint10 : \n";
    vecint10.affiche_vecteur();
    std::cout << "vecint6 : \n";
    vecint6.affiche_vecteur();
    std::cout << "\nSomme vecint4 = vecint6 + vecint10\n";
    vecint4 = vecint6 + vecint10;
    std::cout << "vecint4 : \n";
    vecint4.affiche_vecteur();

    // Test de +=
    std::cout << "\nApplication de vecint2 += vecint5\n";
    std::cout << "vecint2 : \n";
    vecint2.affiche_vecteur();
    std::cout << "vecint5 : \n";
    vecint5.affiche_vecteur();
    vecint2 += vecint5;
    std::cout << "vecint2 : \n";
    vecint2.affiche_vecteur();

    vecteur_intelligent vecint11(6, 3.5f);
    vecteur_intelligent vecint12(3, 3.5f);
    std::cout << "vecint11 : \n";
    vecint11.affiche_vecteur();
    std::cout << "vecint12 : \n";
    vecint12.affiche_vecteur();
    std::cout << "\nvecint11 += vecint12\n";
    vecint11 += vecint12;
    std::cout << "vecint11 : \n";
    vecint11.affiche_vecteur();
    std::cout << "\n=== Fin des tests ===\n";
    return 0;
}
