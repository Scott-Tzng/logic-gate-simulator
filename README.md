# Sorting-Visualizer

<img width="802" height="927" alt="Capture" src="https://github.com/user-attachments/assets/5c0397c5-d108-413b-88a8-3c9b93feb6be" />

A program to visualize and step through sorting algorithms. Uses [raylib](https://github.com/raysan5/raylib) for rendering.


## Usage

```
Sorting-Visualizer <number of elements>
```

`number of elements` will default to 10

Controls

| Keys        | Command                               |
|-------------|---------------------------------------|
| S           | Shuffle elements                      |
| R           | Reset elements                        |
| Space       | Toggle sorting                        |
| Right Arrow | Step sorting                          |
| Up Arrow    | Incrase sorting delay by 0.1 seconds  |
| Down Arrow  | Decrease sorting delay by 0.1 seconds |
| 1           | Select selection sort                 |
| 2           | Select insertion sort                 |
| 3           | Select merge sort                     |
## building

Requires
- At least CMake version 3.29
- [vcpkg](https://github.com/microsoft/vcpkg) on root
- A C99 compiler

Run the following

```cmake --preset=default```

```cmake --build build```

vcpkg should handle the raylib dependency for you
