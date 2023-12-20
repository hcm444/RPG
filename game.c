#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WORLD_WIDTH 20
#define WORLD_HEIGHT 20
#define TILE_SIZE 40
#define MOVEMENT_SPEED 50.0  // Adjusted for frame rate independence

char* currentResponses[] = {NULL, NULL, NULL, NULL};
int npcDialogueDisplayed = 0;
typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    Vector2 position;
} Player;

typedef struct {
    Vector2 position;
    char* dialogue;
} NPC;

// Update NPC's initial dialogue
NPC npc = {{TILE_SIZE * 5, TILE_SIZE * 5}, "Hello!"};



int map[WORLD_HEIGHT][WORLD_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Player player;

SDL_Texture* tiles[2];
SDL_Texture* playerTexture;
SDL_Texture* npcTexture;  // Texture for the NPC


void initializeSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("RPG with Image Tiles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    tiles[0] = IMG_LoadTexture(renderer, "0.png");
    tiles[1] = IMG_LoadTexture(renderer, "1.png");
    tiles[6] = IMG_LoadTexture(renderer, "6.png");
    tiles[4] = IMG_LoadTexture(renderer, "4.png");
    tiles[5] = IMG_LoadTexture(renderer, "5.png");
    playerTexture = IMG_LoadTexture(renderer, "player.png");
    npcTexture = IMG_LoadTexture(renderer, "npc.png");
}

void handleNPCResponse(int selectedOption) {
    switch (selectedOption) {
        case 1:
            printf("Player: %s\n", currentResponses[0]);
            break;
        // Add more cases for additional response options
        default:
            printf("Player: %s\n", currentResponses[0]);
            break;
    }
}



void cleanupSDL() {
    for (int i = 0; i < 2; ++i) {
        SDL_DestroyTexture(tiles[i]);
    }

    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(npcTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void updatePlayerResponses() {
    if (strcmp(npc.dialogue, "Hello!") == 0) {
        currentResponses[0] = "Hello back!";
    } else {
        // Handle additional NPC dialogues and player responses here
        currentResponses[0] = "Default Response";
    }
}

void displayPlayerResponses() {
    printf("1. %s\n", currentResponses[0]);
    printf("2. %s\n", currentResponses[1]);
    printf("3. %s\n", currentResponses[2] != NULL ? currentResponses[2] : "N/A");
    printf("4. %s\n", currentResponses[3] != NULL ? currentResponses[3] : "N/A");
}




void update() {
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    Vector2 movement = {0.0, 0.0};

    if (keyboardState[SDL_SCANCODE_W]) {
        movement.y -= 1.0;
    }
    if (keyboardState[SDL_SCANCODE_S]) {
        movement.y += 1.0;
    }
    if (keyboardState[SDL_SCANCODE_D]) {
        movement.x += 1.0;
    }
    if (keyboardState[SDL_SCANCODE_A]) {
        movement.x -= 1.0;
    }

    float length = sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length != 0.0) {
        movement.x /= length;
        movement.y /= length;
    }

    // Adjusted for frame rate independence
    float deltaTime = 1.0 / 60.0; // Assuming a target frame rate of 60 FPS
     float newPlayerX = player.position.x + movement.x * MOVEMENT_SPEED * deltaTime;
    float newPlayerY = player.position.y + movement.y * MOVEMENT_SPEED * deltaTime;
    float distanceToNPC = sqrt(pow(newPlayerX - npc.position.x, 2) + pow(newPlayerY - npc.position.y, 2));

    // Check for the proximity to the NPC and trigger the dialogue only if it hasn't been displayed
if (distanceToNPC <= TILE_SIZE) {
    if (!npcDialogueDisplayed) {
        printf("NPC: %s\n", npc.dialogue);
        npcDialogueDisplayed = 1;
        updatePlayerResponses();
        displayPlayerResponses();
    } else {
        if (keyboardState[SDL_SCANCODE_1]) {
            handleNPCResponse(1);
            npcDialogueDisplayed = 0;
        }
        // Add more conditions for additional responses as needed
    }
} else {
    npcDialogueDisplayed = 0;
}



// If the player is close to the NPC, show dialogue and responses
if (distanceToNPC <= TILE_SIZE) {
    if (!npcDialogueDisplayed) {
        printf("NPC: %s\n", npc.dialogue);
        npcDialogueDisplayed = 1;
        updatePlayerResponses();
        displayPlayerResponses();
    } else {
        if (keyboardState[SDL_SCANCODE_1]) {
            printf("Player: %s\n", currentResponses[0]);
            handleNPCResponse(1);
            npcDialogueDisplayed = 0;
        } else if (keyboardState[SDL_SCANCODE_2]) {
            printf("Player: %s\n", currentResponses[1]);
            handleNPCResponse(2);
            npcDialogueDisplayed = 0;
        }
        // Add more conditions for additional responses as needed
    }
}

    // Ensure the player stays within the world boundaries
    int newPlayerMapX = (int)((newPlayerX + TILE_SIZE / 2) / TILE_SIZE);
    int newPlayerMapY = (int)((newPlayerY + TILE_SIZE / 2) / TILE_SIZE);

    if (newPlayerX >= 0 && newPlayerX <= (WORLD_WIDTH - 1) * TILE_SIZE &&
        newPlayerY >= 0 && newPlayerY <= (WORLD_HEIGHT - 1) * TILE_SIZE &&
        newPlayerMapX >= 0 && newPlayerMapX < WORLD_WIDTH &&
        newPlayerMapY >= 0 && newPlayerMapY < WORLD_HEIGHT &&
        map[newPlayerMapY][newPlayerMapX] == 0) {

        player.position.x = newPlayerX;
        player.position.y = newPlayerY;
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < WORLD_HEIGHT; ++i) {
        for (int j = 0; j < WORLD_WIDTH; ++j) {
            SDL_Rect tileRect = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderCopy(renderer, tiles[map[i][j]], NULL, &tileRect);
        }
    }

    SDL_Rect playerRect = {(int)(player.position.x), (int)(player.position.y), TILE_SIZE, TILE_SIZE};
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

    SDL_Rect npcRect = {(int)(npc.position.x), (int)(npc.position.y), TILE_SIZE, TILE_SIZE};
    SDL_RenderCopy(renderer, npcTexture, NULL, &npcRect);

    SDL_RenderPresent(renderer);
}

int main() {
    initializeSDL();

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                cleanupSDL();
                return 0;
            }
        }

        update();
        render();
    }

    return 0;
}