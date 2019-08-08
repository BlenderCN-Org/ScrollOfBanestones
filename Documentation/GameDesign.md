# Game Design Document
**Version:** 0.2  
**Last Updated:** 7th, August 2019.  

## General Overview

### Introduction

This game design document outlines the vision of the game as well as the more technical details that will define the direction we will be taking the game towards.

In this document we will design a game that will be free, open source software that will be released under a permissive license whilst the game assets will be released under a different license.

Our goal here is to create a 3D action RPG game set in a fictional world. This game will be based on a third person perspective (think of the camera in the 3D and HD Grand Theft Auto games)

### Platforms

The intended platforms will be the three main desktop platforms which are as follows:
* Windows
* macOS
* Linux

We do not at this moment in time have any intention of releasing to the mobile platforms (Android, iOS) or the console platforms (Xbox, PlayStation)

The minimum system requirements should be:
* Any Intel Core i3 or AMD equivalent from the last 5 years.
* 4GB Ram.
* Any GPU from within the last 5 years.
* Windows 7+, macOS 10.12+, Ubuntu 16.04+.

### Flowchart

### Unique Selling Points

### Build System

The build system for the game should probably be the open source oriented build system Travis CI. This build system works well for most projects and I see no reason why it should not work for us either.

I do believe that Travis CI is macOS & Linux only, we'll probably need a similar system that will support Windows.

### Artistic Style

The art style for this game will be considered "cartoonish" which will be the following:
* Happy Vibe overall, but for the slightly darker maps such as a demonic level, we should go for a slightly darker colour that fits with our colour pallete.  
* Light Colours with slight gradients.  

Here is a visual image showing the colour palette that we intend on using for most GUI and texture elements:  
![Colour Palette](https://raw.githubusercontent.com/scrollofbanestones/ScrollOfBanestones/master/Documentation/Images/ColourPalette.png "Colour Palette")

### Concept Art

## Features

### Design Pillars

The design pillars for the game are as follows:
* Combat
* Exploration
* Looting
* Customisation

#### Combat
Combat means that the game must have decent combat for a third person game, this means that the player should be able to fight in a third person environment whilst still being able to accuratly target their enemies or their friends, if they're feeling evil >:-).

But we should take great effort to ensure that the player does not unintentially attack those who they do not intend on attacking otherwise (NPC or other player).

In order to achive the above goal, we must ensure that the camera is always behind the player with the ability to zoom in and zoom out using the mouse wheel or the V key. The camera will then face slightly above the shoulder so that the player has a full third person perspective whilst still also allowing them to be able to see what they are attacking.

There will then be an icon in the middle of the screen, this will show slightly above the shoulder where the camera is pointed, so that means that the player will know what they are attacking.

The player will then either use the Left Mouse button or the Right Trigger button on their controller which will initiate an attack towards whatever they intend to attack.

It will trigger an animation which when the sword hits onto the enemy, the enemy will take damage.

The damage will use the following math:
```
damage = (weapon_strength / 2) + (player_strength / 2) + ( random(0, player_luck) / 2) + ( player_level / 5 )
```

If the player has a weapon with a damage strength of 30, player strength of 10, luck of 10 and level of 50, the damage output will be **35 health points** which will deduct from their health. If the player is wearing armour, the health damage will be:
```
final_damage = damage - (armour_strength / 2)
```

If the player has an armour strength of 10, the damage will be reduced to **30 health points**.

#### Exploration
Exploration means that the player should be able to explore the world around them in an open world envionment that is typical of many action RPGs. They should be able to travel between different towns, cities and into different area's, preferably with little to no loading screens (if possible).

This means that we should be able to load in most of the world at once whilst keeping the terrain visible from a distance of `draw_distance * 2` and removing most grass at a distance of `draw_distance - 20%`.

Most towns and cities should not need a loading screen, but for the especially large towns with a lot of objects, we may consider it as a possibility although as a last resort.

Moving between different islands or continents should require a loading screen as each island or continent will be within a worldspace of its own. Worldspaces and Maps will be described further down the line in this document.

#### Looting
The player should be able to loot the bodies of their enemies, fallen comrades or loot the world of its items. This means that we will require an inventory system of some sort and also the world items they loot should have some way of seamlessly regenerating.

The player should be able to view their inventory, remove items, give items to other players, and should also be able to pick pocket from NPC's and other players if the server allows it (server setting).

The player should be able to see what is inside their inventory by pressing the `I` key.

The player should be able to remove items from their inventory by hovering over the item and pressing the `R` key which will drop the item to the ground.  
The server will then delete the item after a period of 10 minutes if the area has no active player characters. This can also be disabled by the server.

The player can give an item to another player by pressing the `E` key when hovered over an alive player and then place the item in their inventory. This will then show a dialog prompt for the other player who will be given the option to either accept or deny the item.

The player should be able to loot the bodies of NPCs and dead players. This option can also be disabled by the server.
The player will loot bodies by hoving over the body with the camera centered on the object and then they interact with the body by pressing the `E` key.

#### Customisation
This means that the player should be able to customise the game through what ever means they wish. This also means that servers should also be able modify the game server-side such as custom models, sounds, scripts or other data.

The player should be able change the following about their character:
* Face Shape
* Eye Colour
* Hair Style
* Hair Colour
* Race
* Skin Colour
* Lip Colour
* Shirt (will be hidden if wearing Body Armour)
* Left & Right Arm Armour
* Leg Armour (Greaves)
* Body Armour (Chest)
* Head Armour (Helmet)

### Editor
The editor will be called "Scrolls of Banestones Editor" and it will be a seperate application that will share a lot of code with the main game but the user interface will be designed to allow the user to create and edit worldspaces and maps.

This editor will be described in better detail in [Game Editor Design Document](../Documentation/EditorDesign.md).

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

Each continent/island/hell will be in its own worldspace.
A worldspace will contain the following data:
* Sky Colour (RRGGBB)
* Sky Enabled (bool)
* Gravity Strength (float, default 1.0)
* Water Colour (RRGGBB)
* Water Height (float)
* Water Enabled (bool)
* Climate (string)
* Climate Enabled (bool)
* Ambient Sound
* Ambience Enabled (bool)

If `Sky Enabled` is true, set the sky colour to what ever is defined in the `Sky Colour`, otherwise the sky colour to black (000000)
Set the gravity to what ever the defined value is, it is by default at 1.0f.
If `Water Enabled` is true, set the colour of the water to the `Water Colour`
If `Climate Enabled` is true, set the climate to the specified climate.
If `Ambience Enabled` is true, play and loop the `Ambient Sound`.

### Maps

Each worldspace will be able to have a large amount of maps and moving from one map to another should not be noticable to the end user (i.e. no loading screen) whereas moving from a worldspace will require a loading screen.

### Climates

There will be a number of different climates that will be in the game:
* Clear (Always sunny)
* Temperate (Alternates between sunny and raining with the occasional fog)
* Tropical (Mostly sunny, but does rain occasionally)
* Desert (Mostly sunny with the occasional sand storm)
* Ashy (Thick never ending ash fog)
* Cold (Alternates between Sunny and snowing with the occasional fog)
* Very Cold (Never ending snow)

### Models

### Particles

## NPC's

### Combat Styles

### Services

### NPC Races

## Object Interaction

## Multiplayer

### Server

### Gamemode

### Plugins

## Main Story

The game story will revolve around an ancient mostly forgotten prophesy where an ancient race of people will attempt to reclaim their land from the current occupants. This was told by small number of people but who also dismissed the prophesy also.

This race of people will start to attack the land in small numbers whilst as the game progresses, their attacks will get stronger and larger resulting in widespread panic amongst the current occupants.

From this, the local armies will attempt to fight these attacking hordes but a hero or group of heroes will emerge to fight this growing menace and in doing so will stop this invasion.