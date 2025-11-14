#include "lib.hpp"

vecteur::~vecteur()
{
    std::cout << "Destructeur de Vecteur appelé\n";
}

vecteur::vecteur()
{
    std::cout << "Appel du constructeur vide pour vecteur\n";
    dim = -1;
    elements = nullptr;
}

vecteur::vecteur(int dim)
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

vecteur::vecteur(int dim, float value)
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

vecteur::vecteur(const vecteur &other)
{
    std::cout << "Appel du constructeur de recopie pour vecteur\n";
    dim = other.dim;

    if (dim > 0)
    {
        elements = new float[dim];
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

void vecteur::affiche_vecteur(void)
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

void vecteur::set_elements(void)
{
    for (int i = 0; i < dim; i++)
    {
        std::cout << "Entrez la valeur de l'élement" << i << ": ";
        std::cin >> elements[i];
    }
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
    return 0;
}
