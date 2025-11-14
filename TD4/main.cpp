#include "lib.hpp"
#include <cassert>

int main()
{
    std::cout << "=== TEST DE vecteur<T> ET vecteur_intelligent<T> ===\n\n";

    //===================================================================
    // 1. Test avec int
    //===================================================================
    std::cout << "1. Test avec int\n";
    vecteur_intelligent<int> vi1(3, 10);
    vecteur_intelligent<int> vi2(2, 20);

    std::cout << "vi1 = ";
    vi1.affiche_vecteur();
    std::cout << "vi2 = ";
    vi2.affiche_vecteur();

    // Test operator+
    auto vi3 = vi1 + vi2;
    std::cout << "vi1 + vi2 = ";
    vi3.affiche_vecteur(); // [30, 30, 10]

    // Test operator+= (agrandit vi1)
    vi1 += vi2;
    std::cout << "vi1 += vi2 → vi1 = ";
    vi1.affiche_vecteur(); // [30, 30, 10]

    // Test operator[] (modif)
    vi1[0] = 99;
    std::cout << "vi1[0] = 99 → ";
    vi1.affiche_vecteur();

    // Test operator= (copie)
    vecteur_intelligent<int> vi4;
    vi4 = vi1;
    std::cout << "vi4 = vi1 → ";
    vi4.affiche_vecteur();

    std::cout << "\n";

    //===================================================================
    // 2. Test avec double
    //===================================================================
    std::cout << "2. Test avec double\n";
    vecteur_intelligent<double> vd1(2, 1.5);
    vecteur_intelligent<double> vd2(4, 2.5);

    std::cout << "vd1 = ";
    vd1.affiche_vecteur();
    std::cout << "vd2 = ";
    vd2.affiche_vecteur();

    auto vd3 = vd1 + vd2;
    std::cout << "vd1 + vd2 = ";
    vd3.affiche_vecteur(); // [4.0, 4.0, 2.5, 2.5]

    vd1 += vd2;
    std::cout << "vd1 += vd2 → vd1 = ";
    vd1.affiche_vecteur();

    vd1[3] = 3.14;
    std::cout << "vd1[3] = 3.14 → ";
    vd1.affiche_vecteur();

    std::cout << "\n";

    //===================================================================
    // 3. Test avec float
    //===================================================================
    std::cout << "3. Test avec float\n";
    vecteur_intelligent<float> vf1(1, 5.5f);
    vecteur_intelligent<float> vf2(3, 1.1f);

    std::cout << "vf1 = ";
    vf1.affiche_vecteur();
    std::cout << "vf2 = ";
    vf2.affiche_vecteur();

    auto vf3 = vf1 + vf2;
    std::cout << "vf1 + vf2 = ";
    vf3.affiche_vecteur(); // [6.6, 1.1, 1.1]

    vf1 += vf2;
    std::cout << "vf1 += vf2 → vf1 = ";
    vf1.affiche_vecteur();

    std::cout << "\n";

    //===================================================================
    // 4. Test des constructeurs et destructeurs (via messages)
    //===================================================================
    std::cout << "4. Test des constructeurs et destructeurs\n";
    {
        vecteur_intelligent<double> temp(2, 3.0);
        std::cout << "temp créé\n";
        temp.affiche_vecteur();
    } // destructeur appelé ici
    std::cout << "Fin du bloc → destructeur appelé\n\n";

    //===================================================================
    // 5. Test des erreurs (dimensions incompatibles dans vecteur<T>)
    //===================================================================
    std::cout << "5. Test des erreurs (vecteur<T> normal)\n";
    vecteur<double> vreg1(2, 1.0);
    vecteur<double> vreg2(3, 2.0);

    std::cout << "vreg1 = ";
    vreg1.affiche_vecteur();
    std::cout << "vreg2 = ";
    vreg2.affiche_vecteur();

    // Cette ligne doit planter (dimensions différentes)
    std::cout << "Tentative vreg1 + vreg2 → doit échouer\n";
    try
    {
        auto erreur = vreg1 + vreg2;
    }
    catch (...)
    {
        std::cout << "Erreur capturée (comme attendu)\n";
    }

    std::cout << "\n";

    //===================================================================
    // 6. Test set_elements()
    //===================================================================
    std::cout << "6. Test set_elements()\n";
    vecteur_intelligent<int> vset(3);
    std::cout << "Entrez 3 valeurs pour vset :\n";
    vset.set_elements();
    std::cout << "vset après saisie = ";
    vset.affiche_vecteur();

    std::cout << "\n=== TOUS LES TESTS SONT PASSÉS ===\n";
    return 0;
}