# Game Engine Design Document
**Version:** 0.1  
**Last Updated:** 12th, August 2019.  

## General Overview

### Introduction

### Platforms

### Flowchart

### Build System

### Command Line Arguments

## Core

### Logging

### Timer

### Math
The game engine will use it's own internal math library that will wrap around the GLM library.
Here is an example of the math library:
```cpp
Vector2 vec2(0.0f, 1.0f); // Vector2
Vector3 vec3(0.0f, 1.0f, 2.0f); // Vector3
Vector4 vec4(0.0f, 1.0f, 2.0f, 3.0f); // Vector4
Quarternion quart(0.0f, 1.0f, 2.0f, 1.0f); // Quarternion
```

### Game Data
The game data will be stored in a file with the extension `.sbp` which will stand for "Scrolls of Banestones Package"  
This file will contain the following sets of data:
* Header
* Trigger
* Alchemy
* Armour
* Book
* Body Part
* Worldspace
* Map
* Class
* Clothing
* NPC
* Container
* Door
* Faction
* Global Variable
* Terrain
* Sound

### Settings

### Networking

## Features

#### Game Loop

#### Scene

## Components

#### Game Object

#### Transform

#### Renderer
For the graphics rendering, we will be using a third party solution known as OGRE (Object-Oriented Graphics Rendering Engine) which will be linked to as a git-submodule. We will be using this as it supports all the main desktop platforms and will provide us with a platform where we can understand how graphics API's work.

We will prefer to use the rendering API that is native to the OS, so Direct3D on Windows, Metal on macOS and OpenGL (Ogre2 does not support Vulkan) on Linux.

#### Input System

#### Customisation

### Editor

## Character System

### Character Creation

### Character Stats

### Player Skills

### Equipment

### Combat System

### Death

### Playable Races

## The World

### Overview of the world

### Worldspaces

### Maps

### Climates

### Models

### Particles

## NPC's

### Combat Styles

### Services

### NPC Races

## Object Interaction
