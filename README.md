Flappy Bird – C++ Console Edition**

A simple Flappy Bird clone built entirely in **C++** using the **Windows Console API.**
This project focuses on understanding game loops, cursor manipulation, collision detection, and real-time input without using any external graphics libraries.

🚀 Features

* Console-based bird animation
* Random pipe generation
* Collision detection (pipes + ground)
* Score tracking
* Non-blocking keyboard input
* Smooth game loop with manual frame control
* Uses Windows API for cursor positioning and screen updates

🛠 What I Learned

* Working with **Windows API functions** like `SetConsoleCursorPosition()`
* Hiding and controlling the console cursor
* Implementing a real-time **game loop**
* Reading keyboard input using `kbhit()` and `getch()`
* Handling state management (pipes, bird position, flags, score)
* Clearing and redrawing frames efficiently
* Using `rand()` for generating dynamic gaps in pipes

🔧 Future Improvements

* Add difficulty levels
* Add menu animations
* Improve collision precision
* Port to SFML/SDL for graphical version

📜 License

This project is free to use, modify, and learn from.
