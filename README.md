# CppConcurrencyPlayground

Bienvenue dans ce projet C++ ludique et pédagogique consacré aux concepts de **concurrence**, **synchronisation** et **performance**.  
Ce dépôt contient plusieurs petits programmes et simulations pour explorer ces notions à travers des exemples concrets, implémentés en C++20 avec multithreading.

---

## Description

Ce projet propose un "jeu" en ligne de commande où tu choisis quel concept tu souhaites explorer parmi :

1. **Concurrence** — Exécution parallèle d'un calcul réparti sur plusieurs threads.
2. **Synchronisation** — Gestion sécurisée de logs partagés par plusieurs threads avec mutex.
3. **Performance** — Benchmark simple mesurant le temps d'exécution d'une boucle intensive.
4. **Problème du barbier dormant** — Simulation classique de synchronisation entre threads.
5. **Problème de l'ascenseur** — Gestion concurrente des appels à un ascenseur.
6. **Problème du buffet** — Gestion d'un système d'attente et réapprovisionnement.
7. **Problème du phare** — Synchronisation entre un phare et des navires.

Chaque exemple génère une sortie HTML ou texte pour visualiser les résultats.

---

## Structure

- `main.cpp` : Interface de sélection et lancement des concepts.
- `WorkerConcurrency.hpp/cpp` : Exemples de calculs multithreadés.
- `LoggerSync.hpp/cpp` : Logs synchronisés via mutex.
- `BenchmarkPerformence.hpp/cpp` : Mesure de performance.
- `BarberProblem.hpp/cpp` : Simulation du problème du barbier dormant.
- `ElevatorProblem.hpp/cpp` : Simulation du problème de l'ascenseur.
- `BuffetProblem.hpp/cpp` : Simulation du problème du buffet.
- `LighthouseProblem.hpp/cpp` : Simulation du problème du phare.

---

## Installation et compilation

Le projet utilise **CMake** (minimum version 3.31) et C++20.

```bash
mkdir build
cd build
cmake ..
cmake --build .
