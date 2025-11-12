#include "WorkerConcurrency.hpp"
#include <thread>
#include <iostream>
<<<<<<< HEAD
#include <vector>
#include <chrono>

namespace WorkerConcurrency {

    // Calcule la somme d'une plage de nombres entiers
=======

namespace WorkerConcurrency {

>>>>>>> d7828240d4531925dbd6db04f464d848ad9d7580
    void addRange(int start, int end, int& result) {
        result = 0;
        for (int i = start; i <= end; ++i) {
            result += i;
        }
    }

<<<<<<< HEAD
    // Execute la tache en deux threads
    void executeAdditionTask(std::vector<int>& results) {
        int r1 = 0, r2 = 0;

        std::cout << "\n=== CONTEXTE DE L'EXERCICE ===\n";
        std::cout << "Dans ce scenario, nous voulons additionner les nombres de 1 a 10 000.\n";
        std::cout << "Mais au lieu de faire ce calcul dans un seul thread (sequentiellement),\n";
        std::cout << "nous allons decouper la tache en deux parties et les executer en parallele.\n";
        std::cout << "Thread 1 : additionne de 1 a 5 000\n";
        std::cout << "Thread 2 : additionne de 5 001 a 10 000\n";
        std::cout << "Cela illustre le principe de la concurrence : plusieurs taches s'executent simultanement.\n\n";

        std::cout << "Creation et lancement des deux threads...\n";

        auto startTime = std::chrono::high_resolution_clock::now();

        // Lancement des threads
        std::thread t1(addRange, 1, 5000, std::ref(r1));
        std::thread t2(addRange, 5001, 10000, std::ref(r2));

        // Attente de leur fin
        t1.join();
        t2.join();

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = endTime - startTime;

        std::cout << "Les deux threads ont termine leur travail.\n";
        std::cout << "Temps total d'execution : " << duration.count() << " secondes\n\n";

        results = { r1, r2 };
    }

    // Affiche les resultats
    void printResults(const std::vector<int>& results) {
        std::cout << "=== RESULTATS ===\n";
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << "Thread " << (i + 1)
                      << " : Somme partielle = " << results[i] << '\n';
        }
        std::cout << "Somme totale combinee : " << (results[0] + results[1]) << "\n\n";

        std::cout << "Remarque :\n";
        std::cout << "Meme si cette addition semble simple, le principe ici est fondamental :\n";
        std::cout << "repartir une tache sur plusieurs threads permet d'exploiter la puissance\n";
        std::cout << "des processeurs multi-coeurs. C'est ce qu'on appelle la concurrence.\n";
        std::cout << "Ce concept est essentiel en programmation systeme, serveur ou simulation.\n";
    }
}
=======
    void executeAdditionTask(std::vector<int>& results) {
        int r1 = 0, r2 = 0;
        std::thread t1(addRange, 1, 5000, std::ref(r1));
        std::thread t2(addRange, 5001, 10000, std::ref(r2));
        t1.join();
        t2.join();
        results = { r1, r2 };
    }

    void printResults(const std::vector<int>& results) {
        std::cout << "Résultat Concurrence (addition parallèle) :\n";
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << " Thread " << (i + 1) << " → Somme: " << results[i] << '\n';
        }
    }
}

>>>>>>> d7828240d4531925dbd6db04f464d848ad9d7580
