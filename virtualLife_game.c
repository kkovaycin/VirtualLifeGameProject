#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Constant definitions
#define MAX_INVENTORY 5    // Maximum 5 inventory items
#define MAX_ROOMS 10       // Maximum 10 rooms
#define MAX_INPUT 100      // Maximum 100 characters for user input
#define MAX_DESC 256       // Maximum characters for room description
#define MAX_HEALTH 100     // Maximum player health

// Struct definitions
typedef struct {
    char name[50];                     // Player name
    int health;                        // Player health
    int strength;                      // Player strength
    char inventory[MAX_INVENTORY][50]; // Player inventory
    int inventory_count;               // Inventory count
} Player;

typedef struct {
    char description[MAX_DESC];  // Room description
    char item[50];               // Item in the room (if exists)
    char creature[50];           // Creature in the room (if exists)
    int up, down, left, right;   // Connected room indices (-1 if no connection)
} Room;

// Global variables
Player player;
Room rooms[MAX_ROOMS];
int current_room = 0;
time_t start_time;

// Function prototypes
void init_game();
void show_prompt();
void handle_command(char *command);
void move_player(char *direction);
void look_room();
void show_inventory();
void pickup_item(char *item);
void attack_creature();
void show_health();
void show_instructions();
void show_play_time();
void explore_all_rooms();

// Random items
const char *items[] = {"Health Potion", "Gold Coins", "Sword", "Shield", "Magic Ring"};
const int num_items = 5;

// Function to pick up an item and increase health by 3 points
void pickup_item(char *item) {
    if (strlen(rooms[current_room].item) > 0 && strcmp(rooms[current_room].item, item) == 0) {
        if (player.inventory_count < MAX_INVENTORY) {
            strcpy(player.inventory[player.inventory_count++], item);
            printf("You picked up %s.\n", item);
            rooms[current_room].item[0] = '\0';

            // Increase health by 3 points, but do not exceed MAX_HEALTH
            if (player.health + 3 <= MAX_HEALTH) {
                player.health += 3;
            } else {
                player.health = MAX_HEALTH; // Cap health at MAX_HEALTH
            }
            printf("Your health increased by 3! Current health: %d/%d\n", player.health, MAX_HEALTH);
        } else {
            printf("Your inventory is full!\n");
        }
    } else {
        printf("There is no %s here.\n", item);
    }
}


// Function to attack a creature
void attack_creature() {
    if (strlen(rooms[current_room].creature) > 0) {
        printf("You attacked the %s!\n", rooms[current_room].creature);
        player.health -= 10;
        printf("The %s is defeated, but you lost 10 health points.\n", rooms[current_room].creature);
        rooms[current_room].creature[0] = '\0';

        if (player.health <= 0) {
            printf("You have succumbed to your injuries. Game over!\n");
            exit(0);
        }
    } else {
        printf("There is nothing to attack here.\n");
    }
}

// Function to show play time
void show_play_time() {
    time_t end_time = time(NULL);
    double elapsed = difftime(end_time, start_time);
    printf("You have been playing for %.0f seconds.\n", elapsed);
}


// Main function
int main() {
    char command[MAX_INPUT];

    // Get player name
    printf("Enter your name: ");
    fgets(player.name, sizeof(player.name), stdin);
    player.name[strcspn(player.name, "\n")] = '\0';

    // Start time and random seed
    start_time = time(NULL);
    srand((unsigned int)start_time);

    // Initialize the game
    init_game();
    printf("\nWelcome, %s, to the Virtual Life Adventure!\n", player.name);
    printf("Type 'help' to see a list of commands.\n");

    // Main game loop
    while (true) {
        show_prompt();
        fgets(command, MAX_INPUT, stdin);
        command[strcspn(command, "\n")] = '\0';
        handle_command(command);
    }

    return 0;
}

// Initialize the game
void init_game() {
    // Player starting values
    player.health = MAX_HEALTH;
    player.strength = 10;
    player.inventory_count = 0;

    // Room descriptions and connections
    strcpy(rooms[0].description, "You are at the entrance of a dark virtual life.");
    strcpy(rooms[0].creature, "Troll");
    rooms[0].up = 1; rooms[0].down = -1; rooms[0].left = -1; rooms[0].right = 2;

    strcpy(rooms[1].description, "You are in a damp corridor with torches on the walls.");
    rooms[1].up = 3; rooms[1].down = 0; rooms[1].left = -1; rooms[1].right = 4;

    strcpy(rooms[2].description, "You are in a room with a treasure chest.");
    rooms[2].up = 4; rooms[2].down = -1; rooms[2].left = 0; rooms[2].right = 5;

    strcpy(rooms[3].description, "You are in a room filled with old weapons.");
    rooms[3].up = -1; rooms[3].down = 1; rooms[3].left = -1; rooms[3].right = 6;

    strcpy(rooms[4].description, "You are in a mysterious library with ancient books.");
    rooms[4].up = 6; rooms[4].down = 2; rooms[4].left = 1; rooms[4].right = 7;

    strcpy(rooms[5].description, "You are in a bright hall with a magical aura.");
    rooms[5].up = 7; rooms[5].down = -1; rooms[5].left = 2; rooms[5].right = -1;

    strcpy(rooms[6].description, "You are in a room filled with eerie statues.");
    rooms[6].up = -1; rooms[6].down = 4; rooms[6].left = 3; rooms[6].right = 8;

    strcpy(rooms[7].description, "You are in a narrow corridor with flickering lights.");
    rooms[7].up = -1; rooms[7].down = 5; rooms[7].left = 4; rooms[7].right = 9;

    strcpy(rooms[8].description, "You are in a treasure vault glowing with gold.");
    rooms[8].up = 9; rooms[8].down = -1; rooms[8].left = 6; rooms[8].right = -1;

    strcpy(rooms[9].description, "You are in the final room, a dark chamber with an ominous presence.");
    strcpy(rooms[9].creature, "Dark Sorcerer");
    rooms[9].up = -1; rooms[9].down = 8; rooms[9].left = 7; rooms[9].right = -1;

    // Randomly assign items to rooms
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rand() % 2 == 0) {
            strcpy(rooms[i].item, items[rand() % num_items]);
        } else {
            rooms[i].item[0] = '\0';
        }
    }
}


// Show prompt with current room
void show_prompt() {
    printf("\n%s (Room %d) > ", player.name, current_room);
}

// Handle user commands
void handle_command(char *command) {
    if (strncmp(command, "move", 4) == 0) {
        move_player(command + 5);
    } else if (strcmp(command, "explore_all") == 0) {
        explore_all_rooms();
    } else if (strcmp(command, "look") == 0) {
        look_room();
    } else if (strcmp(command, "inventory") == 0) {
        show_inventory();
    } else if (strncmp(command, "pickup", 6) == 0) {
        pickup_item(command + 7);
    } else if (strcmp(command, "attack") == 0) {
        attack_creature();
    } else if (strcmp(command, "health") == 0) {
        show_health();
    } else if (strcmp(command, "instructions") == 0) {
        show_instructions();
    } else if (strcmp(command, "time") == 0) {
        show_play_time();
    } else if (strcmp(command, "exit") == 0) {
    // Show health and inventory before exiting
        printf("\n--- Final Game Summary ---\n");
        show_health();
        show_inventory();
        show_play_time();
        printf("Exiting the game. Goodbye!\n");
        exit(0);
    } else if (strcmp(command, "help") == 0) {
        show_instructions();
    } else {
        printf("Unknown command. Type 'help' for a list of commands.\n");
    }
}

// Move the player based on direction
void move_player(char *direction) {
    int next_room = -1;

    if (strcmp(direction, "up") == 0) {
        next_room = rooms[current_room].up;
    } else if (strcmp(direction, "down") == 0) {
        next_room = rooms[current_room].down;
    } else if (strcmp(direction, "left") == 0) {
        next_room = rooms[current_room].left;
    } else if (strcmp(direction, "right") == 0) {
        next_room = rooms[current_room].right;
    } else {
        printf("Invalid direction! Available directions: up, down, left, right.\n");
        return;
    }

    if (next_room != -1) {
        current_room = next_room;
        printf("You moved to a new room.\n");
        look_room();
    } else {
        printf("You cannot move in that direction!\n");
    }
}

// Explore all rooms
void explore_all_rooms() {
    bool visited[MAX_ROOMS] = {false};
    int original_room = current_room;

    printf("Starting to explore all rooms...\n");

    for (int i = 0; i < MAX_ROOMS; i++) {
        if (!visited[i]) {
            current_room = i;
            visited[i] = true;
            printf("\nYou discovered Room %d:\n", i);
            look_room();
        }
    }

    printf("\nAll rooms explored! Returning to the starting room...\n");
    current_room = original_room;
}

// Display the current room details
void look_room() {
    printf("%s\n", rooms[current_room].description);
    if (strlen(rooms[current_room].item) > 0) {
        printf("You see a %s here.\n", rooms[current_room].item);
    }
    if (strlen(rooms[current_room].creature) > 0) {
        printf("A %s is here!\n", rooms[current_room].creature);
    }
}

// Show the player's inventory
void show_inventory() {
    if (player.inventory_count == 0) {
        printf("Your inventory is empty.\n");
    } else {
        printf("Inventory:\n");
        for (int i = 0; i < player.inventory_count; i++) {
            printf("- %s\n", player.inventory[i]);
        }
    }
}

// Show player health
void show_health() {
    printf("Your health: %d/%d\n", player.health, MAX_HEALTH);
}

// Display instructions
// Display instructions and movement details
void show_instructions() {
    printf("\n--- Game Instructions ---\n");
    printf("Available commands:\n");
    printf("- move <direction>: Move in the specified direction (up, down, left, or right).\n");
    printf("- look: Examine the current room.\n");
    printf("- inventory: Show your inventory.\n");
    printf("- pickup <item>: Pick up an item in the room.\n");
    printf("- attack: Attack a creature in the room.\n");
    printf("- health: Check your current health.\n");
    printf("- time: Show how long you've been playing.\n");
    printf("- explore_all: Explore all rooms automatically.\n");
    printf("- exit: Quit the game.\n");
    printf("- help: Show this list of commands.\n");

    printf("\n--- Room Navigation Guide ---\n");
    printf("Use the following commands to move between rooms:\n");
    printf("- 'move up': Move to the room above (if available).\n");
    printf("- 'move down': Move to the room below (if available).\n");
    printf("- 'move left': Move to the room on the left (if available).\n");
    printf("- 'move right': Move to the room on the right (if available).\n");

    printf("\n--- Room Connections ---\n");
    printf("Here are the connections for each room:\n\n");

    printf("Room 0: Entrance of a dark virtual life\n");
    printf("  - up -> Room 1\n");
    printf("  - right -> Room 2\n");
    printf("  - left -> Room 4\n\n");

    printf("Room 1: Damp corridor with torches\n");
    printf("  - up -> Room 3\n");
    printf("  - down -> Room 0\n");
    printf("  - right -> Room 4\n\n");

    printf("Room 2: Room with a treasure chest\n");
    printf("  - up -> Room 4\n");
    printf("  - left -> Room 0\n");
    printf("  - right -> Room 5\n\n");

    printf("Room 3: Room filled with old weapons\n");
    printf("  - down -> Room 1\n");
    printf("  - right -> Room 6\n\n");

    printf("Room 4: Mysterious library with ancient books\n");
    printf("  - up -> Room 6\n");
    printf("  - down -> Room 2\n");
    printf("  - left -> Room 1\n");
    printf("  - right -> Room 7\n\n");

    printf("Room 5: Bright hall with a magical aura\n");
    printf("  - up -> Room 7\n");
    printf("  - left -> Room 2\n\n");

    printf("Room 6: Room filled with eerie statues\n");
    printf("  - down -> Room 4\n");
    printf("  - left -> Room 3\n");
    printf("  - right -> Room 8\n\n");

    printf("Room 7: Narrow corridor with flickering lights\n");
    printf("  - down -> Room 5\n");
    printf("  - left -> Room 4\n");
    printf("  - right -> Room 9\n\n");

    printf("Room 8: Treasure vault glowing with gold\n");
    printf("  - up -> Room 9\n");
    printf("  - left -> Room 6\n\n");

    printf("Room 9: Final room, a dark chamber with an ominous presence\n");
    printf("  - down -> Room 8\n");
    printf("  - left -> Room 7\n");

    printf("\nType 'look' to see details of the current room, including available directions.\n");
    printf("--------------------------\n");
}


