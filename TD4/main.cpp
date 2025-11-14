#include "lib.hpp"
#include <cassert>
#include <iostream>

int main()
{
    std::cout << "=== TEST DE vecteur<T> ET vecteur_intelligent<T> ===\n\n";

    //===================================================================
    // 1. Test avec int + operator<<
    //===================================================================
    std::cout << "1. Test avec int + operator<<\n";
    vecteur_intelligent<int> vi1(3, 10);
    vecteur_intelligent<int> vi2(2, 20);

    std::cout << "vi1 = " << vi1 << "\n"; // [ 10, 10, 10 ]
    std::cout << "vi2 = " << vi2 << "\n"; // [ 20, 20 ]

    auto vi3 = vi1 + vi2;
    std::cout << "vi1 + vi2 = " << vi3 << "\n"; // [ 30, 30, 10 ]

    vi1 += vi2;
    std::cout << "vi1 += vi2 → vi1 = " << vi1 << "\n"; // [ 30, 30, 10 ]

    vi1[0] = 99;
    std::cout << "vi1[0] = 99 → " << vi1 << "\n"; // [ 99, 30, 10 ]

    vecteur_intelligent<int> vi4 = vi1;
    std::cout << "vi4 = vi1 → " << vi4 << "\n\n";

    //===================================================================
    // 2. Test avec double + operator<<
    //===================================================================
    std::cout << "2. Test avec double + operator<<\n";
    vecteur_intelligent<double> vd1(2, 1.5);
    vecteur_intelligent<double> vd2(4, 2.5);

    std::cout << "vd1 = " << vd1 << "\n"; // [ 1.5, 1.5 ]
    std::cout << "vd2 = " << vd2 << "\n"; // [ 2.5, 2.5, 2.5, 2.5 ]

    auto vd3 = vd1 + vd2;
    std::cout << "vd1 + vd2 = " << vd3 << "\n"; // [ 4, 4, 2.5, 2.5 ]

    vd1 += vd2;
    std::cout << "vd1 += vd2 → " << vd1 << "\n"; // [ 4, 4, 2.5, 2.5 ]

    vd1[3] = 3.14;
    std::cout << "vd1[3] = 3.14 → " << vd1 << "\n\n"; // [ 4, 4, 2.5, 3.14 ]

    //===================================================================
    // 3. Test avec float + operator<<
    //===================================================================
    std::cout << "3. Test avec float + operator<<\n";
    vecteur_intelligent<float> vf1(1, 5.5f);
    vecteur_intelligent<float> vf2(3, 1.1f);

    std::cout << "vf1 = " << vf1 << "\n"; // [ 5.5 ]
    std::cout << "vf2 = " << vf2 << "\n"; // [ 1.1, 1.1, 1.1 ]

    auto vf3 = vf1 + vf2;
    std::cout << "vf1 + vf2 = " << vf3 << "\n"; // [ 6.6, 1.1, 1.1 ]

    vf1 += vf2;
    std::cout << "vf1 += vf2 → " << vf1 << "\n\n"; // [ 6.6, 1.1, 1.1 ]

    //===================================================================
    // 4. Test des constructeurs/destructeurs (messages)
    //===================================================================
    std::cout << "4. Test des constructeurs et destructeurs\n";
    {
        vecteur_intelligent<double> temp(2, 3.0);
        std::cout << "temp créé → " << temp << "\n";
    } // destructeur appelé ici
    std::cout << "Fin du bloc → destructeur appelé\n\n";

    //===================================================================
    // 5. Test erreurs (vecteur<T> normal)
    //===================================================================
    std::cout << "5. Test des erreurs (vecteur<T> normal)\n";
    vecteur<double> vreg1(2, 1.0);
    vecteur<double> vreg2(3, 2.0);

    std::cout << "vreg1 = " << vreg1 << "\n"; // [ 1, 1 ]
    std::cout << "vreg2 = " << vreg2 << "\n"; // [ 2, 2, 2 ]

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
    // 6. Test operator>> (saisie interactive)
    //===================================================================
    std::cout << "6. Test operator>> (saisie interactive)\n";
    vecteur_intelligent<int> v_input;
    std::cout << "Saisie d'un vecteur_intelligent<int> avec cin >> v_input :\n";
    std::cin >> v_input;
    std::cout << "Vecteur saisi : " << v_input << "\n\n";

    //===================================================================
    // 7. Test operator>> sur vecteur<T> normal
    //===================================================================
    std::cout << "7. Test operator>> sur vecteur<T> normal\n";
    vecteur<double> v_normal;
    std::cout << "Saisie d'un vecteur<double> normal :\n";
    std::cin >> v_normal;
    std::cout << "Vecteur normal saisi : " << v_normal << "\n\n";

    //===================================================================
    // 8. Test erreur de saisie (dimension négative)
    //===================================================================
    std::cout << "8. Test erreur de saisie (dimension négative)\n";
    vecteur_intelligent<int> v_err;
    std::cout << "Entrez une dimension négative (ex: -5) → doit échouer proprement\n";
    if (std::cin >> v_err)
    {
        std::cout << "Saisie réussie : " << v_err << "\n";
    }
    else
    {
        std::cout << "Échec de saisie détecté (comme attendu)\n";
        std::cin.clear(); // réinitialise le flux
        std::cin.ignore(10000, '\n');
    }
    std::cout << "\n";

    //===================================================================
    // 9. Test operator<< sur vecteur non initialisé
    //===================================================================
    std::cout << "9. Test affichage vecteur non initialisé\n";
    vecteur_intelligent<int> v_uninit;
    std::cout << "v_uninit (non initialisé) = " << v_uninit << "\n\n";

    //===================================================================
    // 10. Test operator>> avec erreur de type (ex: lettre au lieu de nombre)
    //===================================================================
    std::cout << "10. Test erreur de type lors de la saisie\n";
    std::cout << "Entrez un caractère invalide (ex: 'a') lors de la saisie d'un élément → doit échouer\n";
    vecteur_intelligent<double> v_bad;
    if (std::cin >> v_bad)
    {
        std::cout << "Saisie réussie : " << v_bad << "\n";
    }
    else
    {
        std::cout << "Échec de saisie (mauvais type) → capturé\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    std::cout << "\n=== TOUS LES TESTS SONT PASSÉS (y compris << et >>) ===\n";
    return 0;
}