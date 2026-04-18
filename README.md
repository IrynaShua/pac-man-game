# pac-man-game
Terminal-Based Pac-Man Game in C

Developed a feature-rich Pac-Man-style game in C that runs entirely in the terminal using ASCII-based rendering. 
The project demonstrates strong use of 2D arrays, structs, and control logic to simulate real-time gameplay.

Core Features:

User-controlled movement: Implemented real-time movement using keyboard inputs (w, a, s, d) with boundary wrapping across the map
2D Game Engine: Designed and managed the game state using a 2D array of structs to represent entities (walls, dots, fruits, enemies)
Dynamic Map Creation: Built a command-based level editor allowing users to place walls, fruits, and enemies before gameplay
Collision Detection: Prevented movement through walls and handled interactions with game elements (dots, apples, bananas)
Scoring System: Implemented point accumulation logic based on collectibles and actions

Advanced Mechanics:

Special Item Effects:
Apple: Clears a 5×5 area and awards points based on affected tiles
Banana: Clears rows and columns dynamically until blocked by walls
Game Progression Logic: Tracks remaining dots and determines win condition when all are cleared
Map Wrapping: Enables Pac-Man to reappear on the opposite side of the grid when crossing boundaries
Enemy Representation: Integrated basic enemy presence using structs for future AI extension

Technical Highlights:

Extensive use of structs and enums to model game entities and behaviours
Modular design with helper functions (e.g., dot tracking function)
Careful handling of edge cases and boundary conditions
Efficient state updates and rendering in a constrained terminal environment
