#GameProject
Virtual Life Adventure
Welcome to Virtual Life Adventure, a simple text-based adventure game where you explore rooms, collect items, and face dangerous creatures!

Game Description
In this game, you navigate through different rooms, collect useful items, and battle creatures that stand in your way. Your objective is to survive and explore all the rooms. Watch your health and plan your moves wisely!

How to Play
Getting Started
Compile the Game:

bash
Copy code
gcc virtualLife_game.c -o virtual_life
Run the Game:

bash
Copy code
./virtual_life
Enter your name to begin your adventure.

Commands
Here are the commands you can use:

Move: move <direction> – Move in a specified direction (up, down, left, right).
Look: look – Examine the current room.
Inventory: inventory – Show your inventory.
Pick Up: pickup <item> – Pick up an item if it exists in the room.
Attack: attack – Attack a creature in the room.
Health: health – Check your current health.
Play Time: time – Show how long you've been playing.
Explore All: explore_all – Automatically explore all rooms.
Help: help – Show the list of available commands.
Exit: exit – Quit the game.
Sample Gameplay
vbnet
Copy code
Enter your name: Kubra

Welcome, Kubra, to the Virtual Life Adventure!
Type 'help' to see a list of commands.

Kubra (Room 0) > look
You are at the entrance of a dark virtual life.
A Troll is here!

Kubra (Room 0) > move up
You moved to a new room.
You are in a damp corridor with torches on the walls.

Kubra (Room 1) > pickup Gold Coins
You picked up Gold Coins.
Your health increased by 3! Current health: 100/100

Kubra (Room 1) > inventory
Inventory:
- Gold Coins
Rooms and Navigation
The game features 10 interconnected rooms, each with unique descriptions and challenges.

Room Connections
Room 0: Entrance of a dark virtual life

Up -> Room 1
Right -> Room 2
Room 1: Damp corridor with torches

Up -> Room 3
Down -> Room 0
Right -> Room 4
Room 9: Final room, a dark chamber with an ominous presence

For a complete list of room connections, use the instructions command in the game.

Game Elements
Player
Health: Starts at 100. Losing all health ends the game.
Inventory: Can hold up to 5 items.
Items
Randomly generated in rooms:

Health Potion
Gold Coins
Sword
Shield
Magic Ring
Creatures
Troll
Dark Sorcerer

Development
Dependencies
Standard C libraries (stdio.h, stdlib.h, string.h, stdbool.h, time.h)
File Structure
css
Copy code
virtualLife_game.c - Main game source code




