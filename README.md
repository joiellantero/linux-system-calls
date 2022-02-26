# Linux-System-Calls

a simple game that simulates the relationship of a server and a client using systems calls in linux

### Program scenario

The king of the cyber kingdom holds a contest where contestants will guess the secret code he specified. If the contestants guessed the correct code, their process id will be recorded in the hall of fame. However, if they don’t guess it correctly within the number of trials the king specified, then the king will order that the process be terminated. Additionally, the king will only entertain one process at a time and if another tries to connect, they will be terminated. You, a very smart hackerman/hackerwoman, decided to play the game and win multiple times. Instead of always running a process, you decided to run a single process that automatically spawns child processes to compete in order to win multiple times.

### Goal of the program

* The king accepts input using a FIFO from contestants until they guessed the correct secret code or they exceeded the number of trials.
* Emulates the contestants that generates multiple child processes and connects to the king using a FIFO and answers multiple times.

### License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

### Author

* Joie Llantero
