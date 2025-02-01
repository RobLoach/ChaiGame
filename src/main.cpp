#include <string>
#include <iostream> // TODO: Remove this

void libretro_chailove_pntr_set_error(int error);
#define PNTR_SET_ERROR libretro_chailove_pntr_set_error

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

void libretro_chailove_pntr_set_error(int error) {
    switch (error) {
        case PNTR_ERROR_NONE:
            // No error
            break;
        case PNTR_ERROR_INVALID_ARGS:
            pntr_app_log(PNTR_APP_LOG_ERROR, "[pntr] Invalid args passed");
            break;
        case PNTR_ERROR_NO_MEMORY:
            pntr_app_log(PNTR_APP_LOG_ERROR, "[pntr] No memory available");
            break;
        case PNTR_ERROR_NOT_SUPPORTED:
            pntr_app_log(PNTR_APP_LOG_ERROR, "[pntr] Not supported");
            break;
        case PNTR_ERROR_FAILED_TO_OPEN:
            pntr_app_log(PNTR_APP_LOG_ERROR, "[pntr] Failed to open");
            break;
        case PNTR_ERROR_FAILED_TO_WRITE:
            pntr_app_log(PNTR_APP_LOG_ERROR, "[pntr] Failed to write");
            break;
        default:
            pntr_app_log_ex(PNTR_APP_LOG_ERROR, "[pntr] Unknown error: %d", (int)error);
            break;
    }
}

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
    chailove->app = app;

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

void Event(pntr_app* app, pntr_app_event* event) {
    ChaiLove* chailove = (ChaiLove*)pntr_app_userdata(app);

    switch (event->type) {
        case PNTR_APP_EVENTTYPE_KEY_DOWN:
            chailove->keyboard.eventKeyPressed(event->key);
        break;

        case PNTR_APP_EVENTTYPE_KEY_UP:
            chailove->keyboard.eventKeyReleased(event->key);
        break;

        case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN:
            chailove->mouse.mousepressed(event->mouseX, event->mouseY, chailove->mouse.getButtonName(event->mouseButton));
        break;

        case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP:
            chailove->mouse.mousereleased(event->mouseX, event->mouseY, chailove->mouse.getButtonName(event->mouseButton));
        break;

        case PNTR_APP_EVENTTYPE_MOUSE_MOVE:
            chailove->mouse.mousemoved(event->mouseX, event->mouseY, event->mouseDeltaX, event->mouseDeltaY);
        break;

        case PNTR_APP_EVENTTYPE_MOUSE_WHEEL:
            if (event->mouseWheel != 0) {
                // TODO: Add horizontal mouse wheel to pntr
                chailove->mouse.wheelmoved(event->mouseWheel, 0);
            }
        break;

        case PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN:
            chailove->script->gamepadpressed(chailove->joystick[event->gamepad], chailove->joystick.getButtonName(event->gamepadButton));
            chailove->script->joystickpressed(chailove->joystick[event->gamepad], event->gamepadButton);
        break;

        case PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP:
            chailove->script->gamepadreleased(chailove->joystick[event->gamepad], chailove->joystick.getButtonName(event->gamepadButton));
            chailove->script->joystickreleased(chailove->joystick[event->gamepad], event->gamepadButton);
        break;
    }
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
        .width = 800,
        .height = 600,
        .title = "ChaiLove",
        .init = Init,
        .update = Update,
        .close = Close,
        .event = Event,
        .fps = 0,
    };
}
