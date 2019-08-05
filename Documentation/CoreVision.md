# Core Vision Document
**Version:** 0.3  
**Last Updated:** 4th, August 2019.  
**Note:** This document does *not* represent the final product. The final product could be vastly different to what is presented in this document.  
This document will also talk using future-tense ("will do" instead of "I did", etc)

## Our Vision
Scrolls of Banestones will be a 3D third person action RPG based in a fictional universe.  
It will take inspiration from franchises such as The Elder Scrolls, The Witcher, Baldurs Gate, etc.

## Design Pillars
These are the main design pillars that the game will be designed around:
* Combat
* Exploration
* Looting
* Customisation

### Combat
Combat means that the game must have decent combat for a third person game, this means that the player should be able to fight in a third person environment whilst still being able to accuratly target their enemies or their friends, if they're feeling evil >:-).

But we should take great effort to ensure that the player does not unintentially attack those who they do not intend on attacking otherwise (NPC or other player).

### Exploration
Exploration means that the player should be able to explore the world around them in an open world envionment that is typical of many action RPGs. They should be able to travel between different towns, cities and into different area's, preferably with little to no loading screens (if possible).

### Looting
The player should be able to loot the bodies of their enemies, fallen comrades or loot the world of its items. This means that we will require an inventory system of some sort and also the world items they loot should have some way of seamlessly regenerating.

### Customisation
This means that the player should be able to customise the game through what ever means they wish. This also means that servers should also be able modify the game server-side such as custom models, sounds, scripts or other data.

## Heart and Soul
If you strip the game down to it's bare basics, it boils down to the story that the player wants to pursue in any given server with the rules and assets that are defined in that server.

The player will be reliant on using
* Traditional melee combat such as sword, fist, spear, axes or blunt weapons, or
* Ranged combat such as Bow, Throwing knives, Darts or Javelins, or
* Using magic that where the player can throw fire balls, spark balls, congure melee, ranged weapons or healing spells

They can also use a combination of the above as well if they wish.

The player will also need to loot the bodies of their enemies in order to gain better (or worse) equipment, more gold or overall find rare items.

The player can also run a server where they can define their own rules and own lore if they so wish.

The player will be able to take part as one of 10 humanoid races:
* Celtic-like
* Viking-like
* Arab-like
* Roman-like
* High Elf
* Snow Elf
* Dark Elf
* Wood Elf
* Dog-like
* Cat-like

Notes:
* These races will be available on all servers regardless of gamemode.  
* Servers may also be able to create their own races which will be exclusive to that server only. This will be discussed further in the design document.

## Game setting
This game may be set in a medieval-like world that will also take strong influences from modern society where appropriate (will be decided in design document).

The game world will be described in a `WorldBuild` folder inside of `(Root)/Documentation` where we will write all the lore, in-game books, main story, side quests and other world details.

## Game Controlling
The player should be able to control their gaming using two methods:
* Keyboard & Mouse
* Console Controller

The game should be designed around these two controller schemes and should make an effort to avoid complex keyboard or controller specific.

For text-based servers, the user will need access to a keyboard in order to communicate but for voice-based servers, this should not be too much of an issue.

The player should be able to move their camera around by moving their mouse around or by moving one of their controller analog sticks.

The player should then be able to move their character by using the other analog stick or by using the standard WASD on their keyboard.

The player should be able to handle most in-game actions with both a keyboard and a mouse.

The player should also be able to change most of these keyboard/controller keybinds to work with other keys.

## Game Settings
The player should be able to also change most graphical settings in-game without needing to quit the game.

The settings that the player should always have access to include:

Gameplay:
* Language (although this could easily be determined by the system language)
* FPS Counter
* Mouse / Controller Sensitivity
* Invert 
* UI Scale

Sound:
* Master Volume
* Music Volume
* Sound Effects Volume
* Footsteps Volume

Graphics:
* Resolution
* Texture Quality
* Shadow Quality
* Draw Distance
* Texture Filtering
* Ansiotropy

## Server
All servers should have a basic config file at the server root which will contain settings such as:
* Gamemode
* Plugins
* Max Players
* Password
* Language
* Port

The server executable file should be a command line application that should not require a GUI, although we may provide a GUI based server app as a frontend for the command line app for those more comfortable in a GUI-based environment.

The server executable should be a familar expierience on all platforms.