# boosterizer
Creates commander booster draft packs from card list.
Card list should separate legendary creatures and regular cards with an empty line.

# Installation
1. Make sure CMake is installed.
2. Clone this repository
3. cd into repo
4. `mkdir build`
5. `cd build`
6. `cmake ..`
7. `cmake --build .`

# Usage
```
Usage: Boosteriser [--help] [--version] [--legendaries VAR] [--main VAR] [--players VAR] [--boosters VAR] [--nodupes] [--input VAR] [--output VAR]

Optional arguments:
  -h, --help         shows help message and exits 
  -v, --version      prints version information and exits 
  -l, --legendaries  Number of legendaries required in a booster pack [default: 4]
  -m, --main         Number of main cards required in a booster pack [default: 16]
  -p, --players      Number of players in draft [default: 4]
  -b, --boosters     Number of booster packs per player [default: 3]
  --nodupes          Do not allow duplicates into draft 
  -i, --input        Name of input file [default: "input.txt"]
  -o, --output       Name of output file [default: "output.txt"]
```
