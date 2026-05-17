Markdown# ⚔️ Text-Based Adventure Game Engine

A modular, enterprise-ready console text adventure game engine written entirely in modern C++ utilizing Object-Oriented Programming (OOP) architectures. This project was developed as a comprehensive academic semester project evaluating advanced software engineering principles.

---

## 🛠️ Key Architectural OOP Concepts Demonstrated

This system is engineered utilizing rigid Object-Oriented paradigms to ensure modular scalability, clean division of labor, and thread-safe data protection:

*   **Encapsulation (Data Hiding):** The `Player` state machine isolates vital metrics (`health`, `gold`, `experience`) inside `private` blocks. State mutation is restricted exclusively through strictly controlled public interface methods (Getters/Setters) and internal validation logic.
*   **Abstraction:** Modeled via a strict Abstract Base Class `GameEntity` containing pure virtual functions, creating structural interface blueprints without exposing concrete initialization overhead.
*   **Inheritance:** Implemented an extensible structural polymorphic entity hierarchy (`Goblin` and `Dragon` types derive publicly from the abstract base class `Enemy`).
*   **Runtime Polymorphism:** Overrode standard dynamic dispatch handlers (`virtual void attack() override`) allowing the runtime engine to calculate specific battle moves polymorphically depending on runtime instantiation.
*   **File Handling (I/O Persistence):** Engineered custom file streams (`std::ofstream` & `std::ifstream`) to serialize and deserialize the current contextual game state variables directly into a plaintext disk snapshot database (`savegame.txt`).
*   **Rigorous Exception Handling:** Wrapped user interactive console selections within explicit `try-catch` structures validating data stream constraints against injection errors or typing failures without breaking the application runtime loop.

---

## 📂 System Architecture & File Topology

The project architecture breaks down into decoupled subsystems facilitating clean developer collaboration models:

```text
text_adventure_game/
│
├── player.h / player.cpp       # Subsystem 1: Character State & Data Serialization
├── world.h / world.cpp         # Subsystem 2: Abstract Entities, Mapping & Quest Pipelines
├── combat.h / combat.cpp       # Subsystem 3: Hierarchical Enemies & Battle Engines
└── main.cpp                    # Subsystem 4: Application Loop Orchestrator
👥 Team Contribution RosterTeam MemberDomain ModulesCore Functional ResponsibilityDeveloper 1 (Person 1)player.h, player.cppCharacter Progression, Stat Validation, Inventory Buffers, Persistence Architecture (File I/O).Developer 2 (Person 2)world.h, world.cppAbstract Entity Foundations, Event Triggers, Spatial Maps, Storyline Quest Pipelines.Developer 3 (Person 3)combat.h, combat.cppHierarchical Enemy Polymorphism, Combat Game Loop, Fault-Tolerant Input Exception Parsers.🕹️ Game Elements & Mechanics MatrixAdaptive Environment System: Travel to multiple distinct zones. Certain late-game high-level locations are systematically locked until quest-specific cryptographic key entities are parsed from inventory arrays.Reactive Event Registry: Moving between locations triggers algorithmic environmental dice rolls executing positive or negative ambient modifiers (hidden floor traps, abandoned gold caches).Turn-Based Battle Engine: Real-time tactical options during combat. Damage calculations shift Dynamically based on the weapons currently flagged in the inventory profile.Game Progression Database: Save progress at any non-combat crossroad and resume exactly where you left off.🚀 Compilation and Local ExecutionSystem RequirementsA native C++ compiler compiler chain supporting at least standard C++17 or greater (g++ / GCC).An internal operating terminal wrapper environment (PowerShell, Bash, Command Prompt).Compiling through TerminalOpen your native console terminal inside the root directory containing the source repository files and run the following multi-file build sequence command:Bashg++ main.cpp player.cpp world.cpp combat.cpp -o "AdventureGame"
Launching the ApplicationOnce compilation is successful without errors, launch the binary target object out of the root folder tree:Windows Environment (PowerShell)PowerShell.\AdventureGame.exe
Unix Environment (Linux / macOS Terminal)Bashchmod +x AdventureGame
./AdventureGame
📜 Academic Evaluation DisclaimerThis project is developed exclusively for educational purposes as an academic evaluation benchmark highlighting structural design principles, encapsulation clean code patterns, and file system abstractions inside native C++. All source architectures are formatted to prioritize maintainability and clean class design boundaries.
