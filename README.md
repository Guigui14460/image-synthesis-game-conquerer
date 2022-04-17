# Image Synthesis Project

University project proposed in the subject "Image Synthesis" in 1st year of MSc of Computer Science in Imaging & Machine Learning at the University of Caen Normandy.

You can see the glitter based project at [this repository](https://github.com/DrLSimon/glitter) from [Loïc Simon](https://simonl02.users.greyc.fr/).

## Table of contents

  - [Table of contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Setup](#setup)
  - [Commands](#commands)
  - [Authors](#authors)
  - [License](#license)

## Introduction
The goal of the project is to realize a game (2D or 3D) with two players on the same keyboard to introduce us to image synthesis with C++ and OpenGL.

We have chosen to make a fighting game in space where the players are represented by sea animals.

## Setup
You need to have C/C++ compiler and CMake installed in your machien to be able to build and run the project.
With that, you need have installed OpenGL in your computer.

You recommand to install glxgears (`sudo apt-get install mesa-utils`) to test the FPS, etc.

You can open the project with an editor like QtCreator, Visual Studio, Visual Studio Code, etc.

## Commands
## Building
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=RELEASE
make -j4
```

## Running glitter application
All the labs, must be launched without any optional argument, from the build root (otherwise the assets/shaders will not be found). For example,
```bash
# running glitter help
./glitter help
# getting help on pa1
./glitter help pa1
# running pa1 part 1
./glitter pa1 1
```

## Running project
```bash
./conquerer
```

## Authors
- [LEMAIRE Raphaëlle](https://github.com/Seirihiri)
- [LETELLIER Guillaume](https://github.com/Guigui14460)

## License
Project under the MIT license.
