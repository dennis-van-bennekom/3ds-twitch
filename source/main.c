#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <3ds.h>

#include "http.h"

typedef enum {
    STATE_LOADING_GAMES,
    STATE_SELECTING_GAME,
    STATE_LOADING_STREAMS,
    STATE_SELECTING_STREAM,
    STATE_WATCHING
} state_t;

state_t state = STATE_LOADING_GAMES;

void loadingGames() {
    Result ret = 0;

    ret = http_download("https://api.twitch.tv/helix/games/top");

    printf("return from http_download: %" PRId32 "\n", ret);

    // consoleClear();

//    json = json_parse(*output, output_size);
//    json_value *gamearray = json->u.object.values[2].value;
//    json_value *gameobject;
//
//    for (int i = 0; i < gamearray->u.array.length; i++) {
//        gameobject = gamearray->u.array.values[i]->u.object.values[0].value;
//
//        //printf(gameobject->u.object.values[0].value->u.string.ptr);
//        //printf("\n");
//    }

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
