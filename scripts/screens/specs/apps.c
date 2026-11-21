/* Apps that are not part of a protocol section: Archive, U2F */
#include "screen.h"
#include "spec_util.h"

/* ---- Archive -----------------------------------------------------------
 * archive_view_render() is private to the view, so the view source is
 * compiled into this spec (as specs/subghz.c does for the frequency
 * analyzer). The browser worker that fills the list reads the SD card, so
 * the model is filled here instead, the way archive_add_file_item() does. */
#include <applications/main/archive/views/archive_browser_view.c>

/* The view calls these two out of helpers/archive_browser.c, which drags in
 * Storage, the loader and the favourites file. archive_is_known_app() is an
 * inline definition in archive_browser.h: this declaration emits it. */
extern bool archive_is_known_app(ArchiveFileTypeEnum type);

/* helpers/archive_browser.c */
bool archive_is_item_in_array(ArchiveBrowserViewModel* model, uint32_t idx) {
    size_t array_size = files_array_size(model->files);

    if((idx >= (uint32_t)model->array_offset + array_size) ||
       (idx < (uint32_t)model->array_offset)) {
        return false;
    }

    return true;
}

/* archive_add_file_item() */
static void archive_spec_add(ArchiveBrowserViewModel* model, const char* path, ArchiveFileTypeEnum type) {
    ArchiveFile_t item;
    ArchiveFile_t_init(&item);
    furi_string_set(item.path, path);
    item.type = type;
    files_array_push_back(model->files, item);
    model->item_cnt = files_array_size(model->files);
    ArchiveFile_t_clear(&item);
}

SCREEN(apps_archive,
       .file = "apps/archive",
       .section = "apps",
       .title = "Archive: Sub-GHz tab",
       .menu_path = "Desktop → ↓",
       .scene = "applications/main/archive/views/archive_browser_view.c") {
    /* browser_alloc() without the file browser worker */
    View* view = view_alloc();
    view_allocate_model(view, ViewModelTypeLocking, sizeof(ArchiveBrowserViewModel));
    view_set_draw_callback(view, archive_view_render);

    with_view_model(
        view,
        ArchiveBrowserViewModel * model,
        {
            files_array_init(model->files);
            menu_array_init(model->context_menu);
            model->tab_idx = ArchiveTabSubGhz;
            model->clipboard_mode = CLIPBOARD_MODE_OFF;
            /* /ext/subghz, as the worker would list it */
            archive_spec_add(model, "/ext/subghz/Garage", ArchiveFileTypeFolder);
            archive_spec_add(model, "/ext/subghz/Barrier.sub", ArchiveFileTypeSubGhz);
            archive_spec_add(model, "/ext/subghz/Gate_left.sub", ArchiveFileTypeSubGhz);
            archive_spec_add(model, "/ext/subghz/Gate_right.sub", ArchiveFileTypeSubGhz);
            archive_spec_add(model, "/ext/subghz/Ceiling_lamp.sub", ArchiveFileTypeSubGhz);
            archive_spec_add(model, "/ext/subghz/Window_blinds.sub", ArchiveFileTypeSubGhz);
            model->item_idx = 1;
        },
        false);

    screen_draw_view(canvas, view);
}

/* ---- U2F --------------------------------------------------------------- */
#include <u2f/views/u2f_view.h>

SCREEN(apps_u2f,
       .file = "apps/u2f",
       .section = "apps",
       .title = "U2F: waiting for authentication",
       .menu_path = "U2F",
       .scene = "applications/main/u2f/views/u2f_view.c") {
    U2fView* u2f = u2f_view_alloc();
    u2f_view_set_state(u2f, U2fMsgAuth);
    screen_draw_view(canvas, u2f_view_get_view(u2f));
}

SCREEN(apps_u2f_not_connected,
       .file = "apps/u2f_not_connected",
       .section = "apps",
       .title = "U2F: not connected",
       .menu_path = "U2F",
       .scene = "applications/main/u2f/views/u2f_view.c") {
    U2fView* u2f = u2f_view_alloc();
    u2f_view_set_state(u2f, U2fMsgNotConnected);
    screen_draw_view(canvas, u2f_view_get_view(u2f));
}

/* ---- Clock -------------------------------------------------------------
 * clock_render_callback() and AppState are private to the app, so the app
 * source is compiled in and the view is built the way ns_app_alloc() does. */
#include <clock_app/clock_app.c>

SCREEN(apps_clock,
       .file = "apps/clock",
       .section = "apps",
       .title = "Clock",
       .menu_path = "Clock",
       .scene = "applications/main/clock_app/clock_app.c") {
    static AppState state;
    memset(&state, 0, sizeof(state));
    /* ns_app_alloc(): formats from Settings → System, charge from the power
     * service; stopwatch not started, alarm off */
    state.time_format = locale_get_time_format();
    state.date_format = locale_get_date_format();
    state.battery_pct = 100;

    View* view = view_alloc();
    view_allocate_model(view, ViewModelTypeLocking, sizeof(ClockModel));
    with_view_model(view, ClockModel * model, { model->app = &state; }, false);
    view_set_draw_callback(view, clock_render_callback);
    screen_draw_view(canvas, view);
}

/* ---- Snake -------------------------------------------------------------
 * snake_game_render_callback() is private; the state is the one
 * snake_game_init_game() builds at the start of a game. */
#include <applications/system/snake_game/snake_game.c>

SCREEN(apps_snake,
       .file = "apps/snake",
       .section = "apps",
       .title = "Snake",
       .menu_path = "Apps → Games → Snake",
       .scene = "applications/system/snake_game/snake_game.c") {
    static SnakeState snake_state;
    memset(&snake_state, 0, sizeof(snake_state));
    snake_game_init_game(&snake_state);
    snake_state.state = GameStateLife;
    snake_state.mutex = furi_mutex_alloc(FuriMutexTypeNormal);
    screen_draw_fullscreen(canvas, snake_game_render_callback, &snake_state);
}
