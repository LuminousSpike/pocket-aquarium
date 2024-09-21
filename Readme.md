# Pocket Aquarium

Pocket Aquarium is a Game Boy game project. This project includes various sprites and game logic to create an interactive aquarium simulation.

## Project Structure

- **res/**: Contains resources such as sprites and background images.
- **src/**: Contains the source code for the game logic.

## Building the Project

To build the project, you need to have the GBDK (Game Boy Development Kit) installed as a subfolder in this repo.

### Using Makefile

1. Open a terminal.
2. Navigate to the project directory.
3. Run the following command:

```sh
make
```

### Using cmake

Using cmake provides a more flexible way to build the project. You can use cmake to generate a Makefile or other build systems. Out of the box there is support for compilation databases for clang and Visual Studio.

To build the project using cmake, follow these steps:

```sh
cmake -S . -B build
```

