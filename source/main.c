#include <string.h>
#include <stdio.h>

#include <3ds.h>

#include "http.h"
#include "json.h"

typedef enum {
    STATE_LOADING_GAMES,
    STATE_SELECTING_GAME,
    STATE_LOADING_STREAMS,
    STATE_SELECTING_STREAM,
    STATE_WATCHING
} state_t;

state_t state = STATE_LOADING_GAMES;

void loadingGames() {
    char **output = malloc(sizeof (char*));
    int output_size = 0;
    json_value *json;
    int i = 0;
    Result res;

    res = http_request("https://api.twitch.tv/helix/games/top", (u8 **)output, &output_size);
    if (res != 0) {
        printf("\x1b[1;1HError getting game list");
        return;
      }

    json = json_parse(*output, output_size);

    printf("\x1b[1;1HIk leef nog");

    state = STATE_SELECTING_GAME;
}

void selectGame() {

}

void loadStreams() {

}

void selectStream() {

}

void watch() {

}

int main(int argc, char **argv) {

	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	// Main loop
	while (aptMainLoop()) {

		gspWaitForVBlank();
		hidScanInput();

        switch (state) {
            case STATE_LOADING_GAMES:
                loadingGames();
                break;
            case STATE_SELECTING_GAME:
                selectGame();
                break;
            case STATE_LOADING_STREAMS:
                loadStreams();
                break;
            case STATE_SELECTING_STREAM:
                selectStream();
                break;
            case STATE_WATCHING:
                watch();
                break;
        }

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;

		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}
