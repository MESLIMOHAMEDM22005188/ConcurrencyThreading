#include <iostream>
#include <vector>
#include <string>

#include "WorkerConcurrency.hpp"
#include "LoggerSync.hpp"
#include "BenchmarkPerformence.hpp"

#include "BarberProblem.hpp"
#include "ElevatorProblem.hpp"
#include "BuffetProblem.hpp"
#include "LightouseProblem.hpp"


int main() {
    std::cout << "Bienvenue dans le jeu C++ : Choisis un concept a explorer !\n\n";

    std::cout << "1. Concurrence (multithreading)\n"
              << "  -> Execute un calcul en parallele sur deux threads.\n\n";

    std::cout << "2. Synchronisation (mutex pour logs)\n"
              << "  -> Ajoute des messages dans un vecteur depuis plusieurs threads sans erreur.\n\n";

    std::cout << "3. Performance (benchmark simple)\n"
              << "  -> Mesure le temps pour faire une grosse boucle d'addition.\n\n";

    std::cout << "4. Probleme du Barbier Dormant\n"
              << "  -> Simulation classique de synchronisation de threads.\n\n";

    std::cout << "5. Probleme de l'Ascenseur\n"
              << "  -> Gestion des requetes d'etages concurrentes.\n\n";

    std::cout << "6. Probleme du Buffet\n"
              << "  -> Reapprovisionnement et consommation avec attente.\n\n";

    std::cout << "7. Probleme du Phare\n"
              << "  -> Synchronisation d'un phare et des navires.\n\n";

    int choix = 0;
    while (choix < 1 || choix > 7) {
        std::cout << "Choisis un nombre entre 1 et 7 : ";
        std::cin >> choix;
    }

    switch (choix) {
        case 1: {
            std::vector<int> results;
            WorkerConcurrency::executeAdditionTask(results);
            WorkerConcurrency::printResults(results);
            break;
        }
        case 2: {
            std::vector<std::string> logs;
            LoggerSync::runSafeLogging(logs);
            LoggerSync::printLogs(logs);
            break;
        }
        case 3: {
            double time = BenchmarkPerformance::runBenchmark();
            BenchmarkPerformance::printPerformance(time);
            break;
        }
        case 4: {
            BarberProblem::runBarberProblem();
            std::cout << BarberProblem::generateBarberHTML() << std::endl;
            break;
        }
        case 5: {
            ElevatorProblem::runElevatorProblem();
            std::cout << ElevatorProblem::generateElevatorHTML() << std::endl;
            break;
        }
        case 6: {
            BuffetProblem::runBuffetProblem();
            std::cout << BuffetProblem::generateBuffetHTML() << std::endl;
            break;
        }
        case 7: {
            LighthouseProblem::runLighthouseProblem();
            std::cout << LighthouseProblem::generateLighthouseHTML() << std::endl;
            break;
        }
    }

    std::cout << "\nMerci d'avoir joue !\n";
    return 0;
}
