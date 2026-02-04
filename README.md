# Technical Design Document (TDD) for C++ Game Engine

## Document Header
- **Project Title:** C++ Game Engine Project
- **Version:** 1.0
- **Date:** 04-02-2026
- **Authors:** [MOREAU Adrien],[GONÇALVES Téo],[DOUBLET Théo],[POMMEZ Kiliann] et [HANSON Liam]
- **Contact:** [your.email@example.com]

## Revision History
| Date       | Version | Description                | Author      |
|------------|---------|----------------------------|-------------|
| 04-02-2026 | 1.0     | Initial document creation  | Kiliann POMMEZ |

## Table of Contents
1. [Introduction](#1-introduction)
2. [System Overview](#2-system-overview)
3. [Requirements](#3-requirements)
4. [System Architecture & Design](#4-system-architecture--design)
5. [Detailed Module Design](#5-detailed-module-design)
6. [Interface Design](#6-interface-design)
7. [Performance and Optimization](#7-performance-and-optimization)
8. [Testing Strategy (TDD Implementation)](#8-testing-strategy-tdd-implementation)
9. [Tools, Environment, and Deployment](#9-tools-environment-and-deployment)
10. [Security and Safety Considerations](#10-security-and-safety-considerations)
11. [Project Timeline and Milestones](#11-project-timeline-and-milestones)
12. [Appendices](#12-appendices)

---

## 1. Introduction

### 1.1 Purpose
Ce document décrit la conception technique d'un moteur de jeu modulaire en C++, détaillant son architecture, ses modules

### 1.2 Scope
- **Objective:** Développer un moteur de jeu multiplateforme pour le rendu, la physique, l'audio et la gestion des entrées.
- **Application:** Développement de jeux en temps réel et projets académiques.
- **Contexte:** Ceci est un projet d'étudiant de 2 ème année de programation en équipe de 5 et sur une durée de 4 semaines
   
### 1.3 Definitions, Acronyms, and Abbreviations
- **API:** Application Programming Interface (Interface de programmation d'application)
- **FPS:** Frames Per Second (Images par seconde)
- **IDE:** Integrated Development Environment (Environnement de développement intégré)

### 1.4 References
- [C++ Standard Documentation](https://isocpp.org)
- [Google Test Framework](https://github.com/google/googletest)

### 1.5 Document Overview
Ce document détaille la conception, les interactions entre modules et les stratégies de test pour le moteur de jeu, assurant la clarté depuis l'architecture de haut niveau jusqu'aux détails d'implémentation de bas niveau.

---

## 2. System Overview

### 2.1 High-Level Description
Le moteur est un système modulaire écrit en C++ (C++17 ou ultérieur), conçu pour gérer le rendu, la simulation physique, le traitement audio et la gestion des entrées en temps réel.

### 2.2 System Context Diagram

```mermaid
graph TD;
    A["External Systems (Assets, Controllers)"] --> B["Game Engine (Rendering, Physics, Audio, Input, Logic)"];
    B --> C["Platform Hardware (GPU, CPU, Audio HW)"];
```

### 2.3 Major Components
- **Rendering Engine:** Gère les graphismes en utilisant une API DirectX11.
- **Physics Engine:** Gère la détection de collision et les simulations physiques.
- **Audio Engine:** Traite les effets sonores et la musique.
- **Input Manager:** Capture les événements clavier, souris.
- **Game Logic:** Intègre les modules via une interface de scripting.

---

## 3. Requirements

### 3.1 Functional Requirements
- Rendre des graphismes 2D/3D avec éclairage dynamique et ombrage (shading).
- Effectuer une simulation physique et une détection de collision en temps réel.
- Jouer de la musique de fond et déclencher des effets sonores.
- Capturer et traiter les entrées utilisateur.
- Fournir une interface de scripting pour la personnalisation du comportement du jeu.

### 3.2 Non-Functional Requirements
- **Performance:** Maintenir un minimum de 60 FPS.
- **Scalability:** Conception modulaire pour une extension facile.
- **Maintainability:** Structure de code claire avec une documentation exhaustive.

### 3.3 Use Cases
- **Rendering:** Charger et afficher des scènes complexes.
- **Physics:** Mettre à jour l'état des objets et détecter les collisions.
- **Audio:** Gérer et jouer les assets audio.
- **Input:** Mappers les actions utilisateur aux événements du jeu.

### 3.4 Design Constraints and Assumptions
- Utiliser le C++ moderne (C++17 ou ultérieur).
- S'appuyer sur l'accélération matérielle graphique.

---

## 4. System Architecture & Design

### 4.1 Architectural Overview
Le moteur utilise une architecture basée sur les composants. Chaque module possède des interfaces bien définies, assurant un couplage faible et un développement isolé.

### 4.2 Module Breakdown
- **Rendering Module:** Gère les shaders, les textures et communique avec le GPU.
- **Physics Module:** Implémente la détection de collision et la dynamique des corps rigides.
- **Audio Module:** Focntionnement de la bibliothèques audio.
- **Input Module:** Gère les entrées spécifiques aux périphériques.
- **Actor Module:**  Gère les actor avec les diférents components qu'il peuvent avoir
- **Editor Module:** gère les interface avec IMGui pour qu'on puisse intéragir avec la scene
- **Window Module:** Permet d'avoir une fenetre avec toute nos modules a l'intérieur
- **Scene Module:** Monde simuler en 3D qui est le monde de notre jeu

### 4.3 Interaction Diagrams


#### Architecture
```mermaid
graph TD;
    A[Class Engine] --> B[Actor Module];
    A --> C[Audio];
    A --> D[Physics];
    A --> E[Render];
    A --> F[IInput];
    A --> G[IWindows]
    G[IWindows]-->H[IEditor]
    F-->H[IEditor]
    E-->I[IScene]
    C-->I[IScene]
    D-->I[IScene]
    I-->H
    B-->H
```

### 4.4 Design Decisions and Rationale
- **Language Choice:** C++ pour la haute performance.
- **Modular Design:** Supporte les tests isolés et le développement indépendant des modules.
- **DX11:** Car ...
- **APIPhysics:** Pas trouvée
- **APIAUdio:** Pas trouvée

### 4.5 Why DX11
Nous n'avons pas choisis DX12 et Vulkan pour plusieurs raison :
 - **Pipeline State Objects (PSO):** DX11 permet de changer des états (BlendState, DepthStencilState) de manière granulaire. DX12 force la création de PSOs complets en amont, ce qui complexifie énormément l'architecture du système de matériaux (Material System) et constitue un travail considérable.
 - **Synchronisation et Race Conditions:** DX11 utilise un contexte immédiat qui gère la synchronisation pour vous. DX12/Vulkan imposent une gestion manuelle des files d'attente (queues) et des barrières de transition. Une erreur de synchronisation sous DX12 peut provoquer des crashs GPU aléatoires très difficiles à débugger.

Et nous n'avons pas choisis OpenGL pour ces raison :
- **État de la Machine (State Machine):** OpenGL est une machine à états globale héritée des années 90, ce qui rend le code difficile à encapsuler proprement en C++ (effets de bord fréquents). DX11, bien qu'utilisant un contexte, est beaucoup plus orienté objet et se prête mieux à une architecture avec RAII et Smart Pointers.
- **Drivers et Consistance:** Les drivers OpenGL (surtout chez AMD et Intel) sont notoirement inconsistants. Un shader qui fonctionne sur NVIDIA peut échouer sur AMD. DX11 est extrêmement stable et prévisible sur Windows.
  
---

## 5. Detailed Module Design

### 5.1 Class Diagrams and Data Structures
- **Rendering:** `Renderer`, `Shader`, `Texture`
- **Physics:** `PhysicsEngine`, `Collider`, `RigidBody`
- **Audio:** `AudioEngine`, `Sound`, `MusicPlayer`
- **Input:** `InputManager`, `Controller`
- **Actor:** `Component` , `Transform`
- **Scene:**
- **Windows:**
- **Editor**

### 5.2 Key Algorithms and Code Snippets


---

## 6. Interface Design

### 6.1 Internal Interfaces

- Définir des APIs claires entre les modules en utilisant des classes abstraites ou des interfaces.

### 6.2 External APIs and File Formats

- Supporter les formats de fichiers standards : OBJ (modèles), PNG (textures), WAV (audio).
- Fournir une documentation pour les interfaces de scripting externes.

---

## 7. Performance and Optimization

### 7.1 Performance Goals

- Atteindre constamment 60 FPS.
- Optimiser l'utilisation de la mémoire et la surcharge de traitement (overhead).

### 7.2 Profiling and Benchmarking

- Intégrer des outils de profilage tels que Valgrind ou Visual Studio Profiler.

### 7.3 Optimization Techniques

- Use object pooling and memory management best practices.
- Implement batching and frustum culling in the rendering process.

---

## 9. Tools, Environment, and Deployment

### 9.1 Development Tools and IDEs

- Recommended IDEs: Visual Studio
- Éditeurs de code supportant les fonctionnalités C++17.

### 9.2 Build System and Automation

- Utiliser CMake pour la configuration du projet.
- Automatiser les builds en utilisant des pipelines CI/CD.

### 9.3 Version Control

- Utiliser Git pour le contrôle de version.
- Adopter une stratégie de branches claire pour le développement des fonctionnalités.

### 9.4 Deployment Environment

- Target platforms: Windows.
- Fournir des instructions de déploiement et des guides de configuration de l'environnement.

---

## 11. Project Timeline and Milestones

- **Phase 1:** Analyse des prérequis & Conception détaillée
- **Phase 2:** Développement des modules
- **Phase 4:** Optimisation et Déploiement final

---

## 12. Appendices

### 12.1 Glossary

- **Game Engine:** Le cadre central gérant tous les processus du jeu.
- **Module:** Un composant autonome fournissant une fonctionnalité spécifique.
- **Shader:** Un programme exécuté sur le GPU pour contrôler le rendu.

