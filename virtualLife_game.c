#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Const definitions
#define MAX_INVENTORY 5    // This exits max 5 inventory
#define MAX_ROOMS 10       // Max 10 room
#define MAX_INPUT 100      // Max 100 character user input
#define MAX_DESC 256       // Chacter for descripton room
#define MAX_HEALTH 100     // Max value of player health

// Struct definition
typedef struct {
    char name[50];                     // Player name
    int health;                        // Player health
    int strength;                      // Player strength
    char inventory[MAX_INVENTORY][50]; // Player inventory
    int inventory_count;               // Inverntory count
} Player;

typedef struct {
    char description[MAX_DESC];  // Room description
    char item[50];               // Items in room (is exists)
    char creature[50];           // Creature in room (is exists)
    int up, down, left, right;   // Index of connnection rooms (-1 if connection not exist)
} Room;

// Global variables
Player player;
Room rooms[MAX_ROOMS];
int current_room = 0;
time_t start_time;

// Functions prototips
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

// Random items
const char *items[] = {"Health Potion", "Gold Coins", "Sword", "Shield", "Magic Ring"};
const int num_items = 5;

int main() {
    char command[MAX_INPUT];

    // Get player name
    printf("Enter your name: ");
    fgets(player.name, sizeof(player.name), stdin);
    player.name[strcspn(player.name, "\n")] = '\0';

    // Start time and create random number for seed
    start_time = time(NULL);
    srand((unsigned int)start_time);

    init_game();
    printf("Welcome, %s, to the Vİrtual Life Adventure!\nType 'help' for a list of commands.\n", player.name);

    // Main play loop
    while (true) {
        show_prompt();
        fgets(command, MAX_INPUT, stdin);
        command[strcspn(command, "\n")] = '\0';
        handle_command(command);
    }

    return 0;
}

void init_game() {
    // Player priority values 
    player.health = MAX_HEALTH;
    player.strength = 10;
    player.inventory_count = 0;

    // Description of rooms
    strcpy(rooms[0].description, "You are in the entrance of a dark virtualLife.");
    strcpy(rooms[0].creature, "Creature");
    rooms[0].up = 1; rooms[0].down = -1; rooms[0].left = -1; rooms[0].right = 2;

    strcpy(rooms[1].description, "You are in a damp corridor with torches on the walls.");
    rooms[1].up = -1; rooms[1].down = 0; rooms[1].left = 3; rooms[1].right = -1;

    strcpy(rooms[2].description, "You are in a room with a treasure chest.");
    rooms[2].up = -1; rooms[2].down = -1; rooms[2].left = 0; rooms[2].right = -1;

    strcpy(rooms[3].description, "You found a room filled with old weapons.");
    rooms[3].up = -1; rooms[3].down = -1; rooms[3].left = -1; rooms[3].right = 1;
    
    strcpy(rooms[4].description, "You are in a mysterious library with ancient books.");
    rooms[4].up = -1; rooms[4].down = -1; rooms[4].left = 2; rooms[4].right = 5;

    strcpy(rooms[5].description, "You are in a bright hall with a magical aura.");
    rooms[5].up = -1; rooms[5].down = -1; rooms[5].left = 4; rooms[5].right = 6;

    strcpy(rooms[6].description, "You are in a room filled with eerie statues.");
    rooms[6].up = -1; rooms[6].down = -1; rooms[6].left = 5; rooms[6].right = 7;

    strcpy(rooms[7].description, "You are in a narrow corridor with flickering lights.");
    rooms[7].up = -1; rooms[7].down = -1; rooms[7].left = 6; rooms[7].right = 8;

    strcpy(rooms[8].description, "You are in a treasure vault glowing with gold.");
    rooms[8].up = -1; rooms[8].down = -1; rooms[8].left = 7; rooms[8].right = 9;

    strcpy(rooms[9].description, "You are in the final room, a dark chamber with an ominous presence.");
    rooms[9].up = -1; rooms[9].down = -1; rooms[9].left = 8; rooms[9].right = -1;


    // Create random inventory
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rand() % 2 == 0) {
            strcpy(rooms[i].item, items[rand() % num_items]);
        } else {
            rooms[i].item[0] = '\0';
        }
    }
}

void show_prompt() {
    printf("\n%s > ", player.name);
}

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
    } else if (strcmp(command, "instructions") == 0) {
        show_instructions();
    } else if (strcmp(command, "time") == 0) {
        show_play_time();
    } else if (strcmp(command, "exit") == 0) {
        show_play_time();
        show_health();
        show_inventory();
        printf("Goodbye!\n");
        exit(0);
    } else if (strcmp(command, "help") == 0) {
        printf("Available commands:\nmove <direction>,\nlook,\ninventory,\npickup <item>,\nattack,\nhealth,\ninstructions,\ntime,\nexit\n");
    } else {
        printf("Unknown command. Type 'help' for a list of commands.\n");
    }
}

void move_player(char *direction) {
    printf("You moved %s.\n", direction);
}

void look_room() {
    printf("%s\n", rooms[current_room].description);
    if (strlen(rooms[current_room].item) > 0) {
        printf("You see a %s here.\n", rooms[current_room].item);
    }
    if (strlen(rooms[current_room].creature) > 0) {
        printf("A %s is here!\n", rooms[current_room].creature);
    }
}

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

void pickup_item(char *item) {
    if (strlen(rooms[current_room].item) > 0 && strcmp(rooms[current_room].item, item) == 0) {
        if (player.inventory_count < MAX_INVENTORY) {
            strcpy(player.inventory[player.inventory_count++], item);
            printf("You picked up %s.\n", item);
            rooms[current_room].item[0] = '\0';

            // Increase health
            if (player.health + 3 <= MAX_HEALTH) {
                player.health += 3;
            } else {
                player.health = MAX_HEALTH; // Max health boundary
            }
            printf("Your health increased by 3! Current health: %d/%d\n", player.health, MAX_HEALTH);
        } else {
            printf("Your inventory is full!\n");
        }
    } else {
        printf("There is no %s here.\n", item);
    }
}


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

void show_health() {
    printf("Your health: %d/%d\n", player.health, MAX_HEALTH);
}

void show_play_time() {
    time_t end_time = time(NULL);
    double elapsed = difftime(end_time, start_time);
    printf("You have been playing for %.0f seconds.\n", elapsed);
}

void show_instructions() {
    printf("Welcome to the Virtual Life Adventure!\n");
    printf("Explore the life, collect items, and fight creatures.\n");
    printf("Commands you can use:\n");
    printf("- move <direction>: Move up, down, left, or right.\n");
    printf("- look: Look around the current room.\n");
    printf("- inventory: View your collected items.\n");
    printf("- pickup <item>: Pick up an item.\n");
    printf("- attack: Attack a creature in the room.\n");
    printf("- health: Check your current health.\n");
    printf("- time: Show how long you've been playing.\n");
    printf("- exit: Quit the game.\n");
}


