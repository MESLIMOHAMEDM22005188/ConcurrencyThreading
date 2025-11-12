#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "WorkerConcurrency.hpp"
#include "LoggerSync.hpp"
#include "BenchmarkPerformence.hpp"

#include "BarberProblem.hpp"
#include "ElevatorProblem.hpp"
#include "BuffetProblem.hpp"
#include "LightouseProblem.hpp"

int main() {
    bool continuer = true;
    while (continuer) {
        std::cout << "\n==============================================\n";
        std::cout << "Bienvenue dans le simulateur C++ multithread !" << std::endl;
        std::cout << "Choisis un concept a explorer :" << std::endl;
        std::cout << "==============================================" << std::endl << std::endl;

        std::cout << "1- Concurrence (multithreading)" << std::endl
                  << "   Execute un calcul en parallele sur deux threads." << std::endl << std::endl;

        std::cout << "2- Synchronisation (mutex pour logs)" << std::endl
                  << "   Ajoute des messages dans un vecteur depuis plusieurs threads." << std::endl << std::endl;

        std::cout << "3- Performance (benchmark simple)" << std::endl
                  << "   Mesure le temps pour executer une boucle d'addition massive." << std::endl << std::endl;

        std::cout << "4- Probleme du Barbier Dormant" << std::endl
                  << "   Simulation classique de synchronisation de threads." << std::endl << std::endl;

        std::cout << "5- Probleme de l Ascenseur" << std::endl
                  << "   Gestion des requetes d etages concurrentes." << std::endl << std::endl;

        std::cout << "6- Probleme du Buffet" << std::endl
                  << "   Reapprovisionnement et consommation avec attente." << std::endl << std::endl;

        std::cout << "7- Probleme du Phare" << std::endl
                  << "   Synchronisation entre un phare et des navires." << std::endl << std::endl;

        int choix = 0;
        while (true) {
            std::cout << "Choisis un nombre entre 1 et 7 : ";
            if (!(std::cin >> choix)) {
                // entree invalide
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entree invalide, reessaie." << std::endl;
                continue;
            }
            if (choix >= 1 && choix <= 7) break;
            std::cout << "Nombre hors plage, reessaie." << std::endl;
        }

        std::cout << "\n==============================================" << std::endl;

        switch (choix) {
            case 1: {
                std::vector<int> results;
                std::cout << "\nDemonstration de la concurrence :" << std::endl;
                WorkerConcurrency::executeAdditionTask(results);
                WorkerConcurrency::printResults(results);
                break;
            }
            case 2: {
                std::vector<std::string> logs;
                std::cout << "\nTest de synchronisation avec mutex :" << std::endl;
                LoggerSync::runSafeLogging(logs);
                LoggerSync::printLogs(logs);
                break;
            }
            case 3: {
                std::cout << "\nMesure de performance (benchmark) :" << std::endl;
                double time = BenchmarkPerformance::runBenchmark();
                BenchmarkPerformance::printPerformance(time);
                break;
            }
            case 4: {
                std::cout << "\nSimulation du probleme du barbier dormant :" << std::endl;
                BarberProblem::runBarberProblem();
                BarberProblem::printLogs();
                break;
            }
            case 5: {
                std::cout << "\nSimulation du probleme de l ascenseur :" << std::endl;
                ElevatorProblem::runElevatorProblem();
                std::cout << ElevatorProblem::generateElevatorHTML() << std::endl;
                break;
            }
            case 6: {
                std::cout << "\nSimulation du probleme du buffet :" << std::endl;
                BuffetProblem::runBuffetProblem();
                std::cout << BuffetProblem::generateBuffetHTML() << std::endl;
                break;
            }
            case 7: {
                std::cout << "\nSimulation du probleme du phare :" << std::endl;
                LighthouseProblem::runLighthouseProblem();
                std::cout << LighthouseProblem::generateLighthouseHTML() << std::endl;
                break;
            }
            default:
                break;
        }

        std::cout << "\n==============================================" << std::endl;
        std::cout << "Veux-tu rejouer ? (o/n) : ";
        char reponse;
        std::cin >> reponse;
        if (reponse != 'o' && reponse != 'O') continuer = false;
    }

    std::cout << "\nMerci d'avoir utilise le simulateur ! a bientot." << std::endl;
    return 0;
}
