# 🕹️ Virtual Life Adventure

**Virtual Life Adventure** is a simple text-based adventure game where you explore rooms, collect items, and face dangerous creatures. Are you ready to embark on this thrilling journey?

---

## 🎮 Game Description

In **Virtual Life Adventure**, you navigate through different rooms, collect useful items, and battle creatures. Your goal is to **survive** and **explore all the rooms**. Watch your health carefully and plan your moves wisely!

---

## 🚀 How to Play

### 🛠️ Getting Started

1. **Compile the Game**:
   ```bash
   gcc virtualLife_game.c -o virtual_life
## 🚀 Run the Game

## 🚀 Run the Game

To start the game, use the following command:

```bash
./virtual_life


Start Your Adventure: Enter your name to begin your journey into the virtual life.

## 📜 Commands
Use the following commands to interact with the game:

Move: move <direction> – Move in a specified direction (e.g., up, down, left, right).
Look: look – Examine the current room.
Inventory: inventory – Check the items in your inventory.
Pick Up: pickup <item> – Pick up an item if it exists in the room.
Attack: attack – Attack a creature in the room.
Health: health – Check your current health.
Play Time: time – View how long you've been playing.
Explore All: explore_all – Automatically explore all rooms.
Help: help – Show the list of available commands.
Exit: exit – Quit the game.
🎲 Sample Gameplay
text
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
🗺️ Rooms and Navigation
The game features 10 interconnected rooms, each with unique descriptions and challenges.

🔗 Room Connections
Room 0: Entrance of a dark virtual life

Up → Room 1
Right → Room 2
Room 1: Damp corridor with torches

Up → Room 3
Down → Room 0
Right → Room 4
Room 9: Final room, a dark chamber with an ominous presence

Use the instructions command in the game for a complete list of room connections.

🎮 Game Elements
🧑 Player
Health: Starts at 100. Losing all health ends the game.
Inventory: Can hold up to 5 items.
🛡️ Items
Randomly generated in rooms:

Health Potion
Gold Coins
Sword
Shield
Magic Ring
👾 Creatures
Troll
Dark Sorcerer
🛠️ Development
🧩 Dependencies
The game uses standard C libraries:

<stdio.h>
<stdlib.h>
<string.h>
<stdbool.h>
<time.h>
📁 File Structure
plaintext
Copy code
virtualLife_game.c - Main game source code
✨ Features to Explore
Text-based adventure gameplay.
10 interconnected rooms to explore.
Challenging creatures to battle.
Random item generation for each room.
📋 License
This project is licensed under the MIT License. Feel free to modify and improve it!

🤝 Contributing
Have ideas for improvements? Fork the repository, make your changes, and submit a pull request. Let's make Virtual Life Adventure even better together!
