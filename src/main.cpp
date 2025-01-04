#include <string>
#include <iostream> // TODO: Remove this

#define PNTR_PHYSFS_IMPLEMENTATION
#include "pntr_physfs.h"

#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_TTF
#define PNTR_ENABLE_MATH
#define PNTR_NO_STDIO
#define PNTR_NO_SAVE_IMAGE
#include "pntr_app.h"

#include "ChaiLove.h"

bool Init(pntr_app* app) {
    ChaiLove::environ_cb = pntr_app_libretro_environ_cb(app);

    // Initialize PhysFS
    if (PHYSFS_init((const char*)ChaiLove::environ_cb) == 0) {
        pntr_app_log(PNTR_APP_LOG_ERROR, "PHYSFS_init() failed");
        return false;
    }

    // Set up the chailove instance.
    ChaiLove* chailove = ChaiLove::getInstance();
    if (chailove == NULL) {
        PHYSFS_deinit();
        return false;
    }

    // Load
    std::string argFile = app->argFile == NULL ? "" : app->argFile;
    if (!chailove->load(argFile, app->argFileData, app->argFileDataSize)) {
        ChaiLove::destroy();
        PHYSFS_deinit();
        return false;
    }
    pntr_app_set_userdata(app, (void*)chailove);

    return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
    ChaiLove* chailove = (ChaiLove*)pntr_app_userdata(app);
    chailove->screen = screen;
    if (chailove == NULL) {
        return false;
    }

	// Update the game.
	chailove->update();

    if (chailove->event.m_shouldclose) {
        return false;
    }

	// Render the game.
	chailove->draw();

    return true;
}

void Close(pntr_app* app) {
    ChaiLove::destroy();
    PHYSFS_deinit();
}

pntr_app Main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    return (pntr_app) {
        .width = 640,
        .height = 480,
        .title = "ChaiLove",
        .init = Init,
        .update = Update,
        .close = Close,
        .fps = 0
    };
}
