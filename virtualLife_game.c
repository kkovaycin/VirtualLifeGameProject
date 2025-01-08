#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Constant definitions
#define MAX_ROOMS 10       // Maximum 10 rooms
#define MAX_INPUT 100      // Maximum 100 characters for user input
#define MAX_DESC 256       // Maximum characters for room description
#define MAX_HEALTH 100     // Maximum player health
#define SAVE_FILE "game_save.txt"

// Struct definitions
typedef struct {
    char name[50];               // Player name
    int health;                  // Player health
    int strength;                // Player strength
    char **inventory;            // Player inventory (dynamic allocation)
    int inventory_count;         // Inventory count
    int max_inventory;           // Max inventory size
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
void load_game();
void save_game();
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
void free_resources();

// Random items
const char *items[] = {"Health Potion", "Gold Coins", "Sword", "Shield", "Magic Ring"};
const int num_items = 5;

// Main function
int main() {
    char command[MAX_INPUT];

    // Load game if save file exists
    FILE *file = fopen(SAVE_FILE, "r");
    if (file) {
        fclose(file);
        load_game();
    } else {
        init_game();
    }

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
    printf("Enter your name: ");
    fgets(player.name, sizeof(player.name), stdin);
    player.name[strcspn(player.name, "\n")] = '\0';

    player.health = MAX_HEALTH;
    player.strength = 10;
    player.inventory_count = 0;
    player.max_inventory = 5;
    player.inventory = (char **)malloc(player.max_inventory * sizeof(char *));

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

    start_time = time(NULL);
}

// Load game from a save file
void load_game() {
    FILE *file = fopen(SAVE_FILE, "r");
    if (!file) {
        printf("Failed to load the game. Starting a new game.\n");
        init_game();
        return;
    }

    fscanf(file, "%49[^"] %d %d %d", player.name, &player.health, &player.strength, &player.inventory_count);
    player.inventory = (char **)malloc(player.inventory_count * sizeof(char *));
    for (int i = 0; i < player.inventory_count; i++) {
        player.inventory[i] = (char *)malloc(50 * sizeof(char));
        fscanf(file, "%49s", player.inventory[i]);
    }
    fscanf(file, "%d", &current_room);

    fclose(file);
    start_time = time(NULL);
}

// Save game to a file
void save_game() {
    FILE *file = fopen(SAVE_FILE, "w");
    if (!file) {
        printf("Failed to save the game.\n");
        return;
    }

    fprintf(file, "%s %d %d %d\n", player.name, player.health, player.strength, player.inventory_count);
    for (int i = 0; i < player.inventory_count; i++) {
        fprintf(file, "%s\n", player.inventory[i]);
    }
    fprintf(file, "%d\n", current_room);

    fclose(file);
    printf("Game saved successfully!\n");
}

// Free allocated resources
void free_resources() {
    for (int i = 0; i < player.inventory_count; i++) {
        free(player.inventory[i]);
    }
    free(player.inventory);
}

// Show prompt with current room
void show_prompt() {
    printf("\n%s (Room %d) > ", player.name, current_room);
}

// Handle user commands
void handle_command(char *command) {
    if (strncmp(command, "move", 4) == 0) {
        move_player(command + 5);
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
    } else if (strcmp(command, "save") == 0) {
        save_game();
    } else if (strcmp(command, "explore_all") == 0) {
        explore_all_rooms();
    } else if (strcmp(command, "instructions") == 0) {
        show_instructions();
    } else if (strcmp(command, "exit") == 0) {
        save_game();
        free_resources();
        printf("Exiting the game. Goodbye!\n");
        exit(0);
    } else {
        printf("Unknown command. Type 'help' for a list of commands.\n");
    }
}

// Show game instructions
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
    printf("- save: Save your game progress.\n");
    printf("- instructions: Show these instructions again.\n");
    printf("- exit: Quit the game.\n");
    printf("---\n");
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

// Function to pick up an item
void pickup_item(char *item) {
    if (strlen(rooms[current_room].item) > 0 && strcmp(rooms[current_room].item, item) == 0) {
        if (player.inventory_count < player.max_inventory) {
            player.inventory[player.inventory_count] = (char *)malloc(50 * sizeof(char));
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
            free_resources();
            exit(0);
        }
    } else {
        printf("There is nothing to attack here.\n");
    }
}
