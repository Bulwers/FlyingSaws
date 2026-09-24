# FlyingSaws

A small **3D slot machine game created in Unreal Engine using C++**.

The project was created as an Unreal Engine programming exercise.

## Features

* Interactive 3D slot machine
* Three independently rotating drums with randomized results
* Multiple possible slot machine outcomes and rewards
* Player HP represented by fingers
* Physics-based gold and saw spawning
* Main menu and Game Over screen
* In-game HUD displaying gold and lost fingers
* Smooth camera transitions between menu and gameplay
* Sound effects and background music
* Interactive 3D elements reacting to mouse input

## Technologies

* C++
* Unreal Engine
* Unreal Engine C++ API
* Unreal Motion Graphics (UMG)
* Visual Studio 2022

## Gameplay

The player starts with a limited amount of gold and uses it to play the slot machine.

Pulling the handle costs one gold and starts all three drums.

The game ends when the player runs out of gold or loses all available fingers.

## Controls

The game is primarily controlled using the mouse.

* Click the slot machine handle to spin the drums
* Use the menu buttons to start or quit the game
* Hover over interactive objects to trigger their interactions

## Technical Features

Exaples of gameplay systems implemented in C++:

* Communication between gameplay objects using multicast delegates
* Timer-based drum, handle, camera, and object animations
* Randomized drum rotations and object spawning
* Runtime creation of Actor components
* Physics impulses for thrown objects
* UMG widgets controlled from C++
* Mouse click and hover interactions
* Runtime audio playback and pitch variation

## Possible Improvements

Some improvements for a future version:

* Refactor prize logic
* Further separate gameplay logic from presentation
* Improve state management
* Add unit tests for gameplay logic
* Improve error and null-pointer handling
* Reduce unnecessary Actor ticking
* Improve configuration of gameplay parameters
