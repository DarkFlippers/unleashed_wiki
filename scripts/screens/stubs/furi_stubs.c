/*
 * Host stubs for the parts of furi / furi_hal that the GUI code touches.
 * Rendering is single-threaded and deterministic, so mutexes are no-ops,
 * timers never fire and the tick counter is frozen at 0.
 */
#include <furi.h>
#include <furi_hal.h>
#include <furi_hal_rtc.h>
#include <furi_hal_version.h>
#include <toolbox/version.h>
#include <ble_glue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* ---- crash / log ------------------------------------------------------ */
void __furi_crash_implementation(void) {
    fprintf(stderr, "furi_crash / furi_check failed\n");
    abort();
}
void __furi_halt_implementation(void) {
    fprintf(stderr, "furi_halt\n");
    abort();
}
void furi_log_print_format(FuriLogLevel level, const char* tag, const char* format, ...) {
    (void)level;
    if(!getenv("SCREENS_VERBOSE")) return;
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[%s] ", tag);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

/* ---- kernel ----------------------------------------------------------- */
uint32_t furi_kernel_get_tick_frequency(void) {
    return 1000;
}
/* The tick counter is frozen so that every screenshot is reproducible. A spec
 * that shows an uptime (desktop_view_debug.c) sets it for its own draw and
 * resets it afterwards. */
uint32_t screen_host_tick = 0;
uint32_t furi_get_tick(void) {
    return screen_host_tick;
}
uint32_t furi_ms_to_ticks(uint32_t milliseconds) {
    return milliseconds;
}
void furi_delay_ms(uint32_t milliseconds) {
    (void)milliseconds;
}
void furi_delay_us(uint32_t microseconds) {
    (void)microseconds;
}
void furi_delay_tick(uint32_t ticks) {
    (void)ticks;
}

/* ---- mutex ------------------------------------------------------------ */
struct FuriMutex {
    int dummy;
};
FuriMutex* furi_mutex_alloc(FuriMutexType type) {
    (void)type;
    return calloc(1, sizeof(FuriMutex));
}
void furi_mutex_free(FuriMutex* instance) {
    free(instance);
}
FuriStatus furi_mutex_acquire(FuriMutex* instance, uint32_t timeout) {
    (void)instance;
    (void)timeout;
    return FuriStatusOk;
}
FuriStatus furi_mutex_release(FuriMutex* instance) {
    (void)instance;
    return FuriStatusOk;
}

/* ---- timer ------------------------------------------------------------ */
/* Timers never fire on their own. A spec may call screen_fire_oneshot_timers()
 * to emulate "a moment later" (e.g. a temporary hint has disappeared). */
struct FuriTimer {
    FuriTimerCallback cb;
    void* ctx;
    FuriTimerType type;
    bool running;
    struct FuriTimer* next;
};
static FuriTimer* timers = NULL;
FuriTimer* furi_timer_alloc(FuriTimerCallback func, FuriTimerType type, void* context) {
    FuriTimer* t = calloc(1, sizeof(FuriTimer));
    t->cb = func;
    t->ctx = context;
    t->type = type;
    t->next = timers;
    timers = t;
    return t;
}
void furi_timer_free(FuriTimer* instance) {
    for(FuriTimer** p = &timers; *p; p = &(*p)->next) {
        if(*p == instance) {
            *p = instance->next;
            break;
        }
    }
    free(instance);
}
FuriStatus furi_timer_start(FuriTimer* instance, uint32_t ticks) {
    (void)ticks;
    instance->running = true;
    return FuriStatusOk;
}
FuriStatus furi_timer_restart(FuriTimer* instance, uint32_t ticks) {
    (void)ticks;
    instance->running = true;
    return FuriStatusOk;
}
FuriStatus furi_timer_stop(FuriTimer* instance) {
    instance->running = false;
    return FuriStatusOk;
}
uint32_t furi_timer_is_running(FuriTimer* instance) {
    return instance->running;
}
void screen_fire_oneshot_timers(void) {
    for(FuriTimer* t = timers; t; t = t->next) {
        if(t->running && t->type == FuriTimerTypeOnce) {
            t->running = false;
            t->cb(t->ctx);
        }
    }
}
void furi_timer_set_thread_priority(FuriTimerThreadPriority priority) {
    (void)priority;
}

/* ---- records ---------------------------------------------------------- */
void* furi_record_open(const char* name) {
    (void)name;
    static char dummy[256];
    return dummy;
}
void furi_record_close(const char* name) {
    (void)name;
}

/* ---- threads (never actually run) --------------------------------------- */
struct FuriThread {
    int dummy;
};
FuriThread* furi_thread_alloc_ex(
    const char* name,
    uint32_t stack_size,
    FuriThreadCallback callback,
    void* context) {
    (void)name;
    (void)stack_size;
    (void)callback;
    (void)context;
    return calloc(1, sizeof(FuriThread));
}
void furi_thread_free(FuriThread* thread) {
    free(thread);
}
void furi_thread_start(FuriThread* thread) {
    (void)thread;
}
bool furi_thread_join(FuriThread* thread) {
    (void)thread;
    return true;
}
FuriThreadId furi_thread_get_id(FuriThread* thread) {
    return (FuriThreadId)thread;
}
uint32_t furi_thread_flags_set(FuriThreadId thread_id, uint32_t flags) {
    (void)thread_id;
    return flags;
}
uint32_t furi_thread_flags_wait(uint32_t flags, uint32_t options, uint32_t timeout) {
    (void)flags;
    (void)options;
    (void)timeout;
    return 0;
}

/* ---- furi_hal --------------------------------------------------------- */
const GpioPin gpio_display_rst_n = {0};
const GpioPin gpio_display_di = {0};
FuriHalSpiBusHandle furi_hal_spi_bus_handle_display;

FuriHalVersionDisplay furi_hal_version_get_hw_display(void) {
    return FuriHalVersionDisplayErc;
}

static uint32_t rtc_flags = 0;
bool furi_hal_rtc_is_flag_set(FuriHalRtcFlag flag) {
    return rtc_flags & flag;
}
void furi_hal_rtc_set_flag(FuriHalRtcFlag flag) {
    rtc_flags |= flag;
}
void furi_hal_rtc_reset_flag(FuriHalRtcFlag flag) {
    rtc_flags &= ~flag;
}
FuriHalRtcLocaleTimeFormat furi_hal_rtc_get_locale_timeformat(void) {
    return FuriHalRtcLocaleTimeFormat24h;
}
FuriHalRtcLocaleDateFormat furi_hal_rtc_get_locale_dateformat(void) {
    return FuriHalRtcLocaleDateFormatDMY;
}
FuriHalRtcLocaleUnits furi_hal_rtc_get_locale_units(void) {
    return FuriHalRtcLocaleUnitsMetric;
}
void furi_hal_rtc_get_datetime(DateTime* datetime) {
    /* fixed placeholder time used on every screenshot */
    datetime->hour = 12;
    datetime->minute = 34;
    datetime->second = 56;
    datetime->day = 21;
    datetime->month = 11;
    datetime->year = 2026;
    datetime->weekday = 6;
}
void furi_hal_rtc_set_locale_units(FuriHalRtcLocaleUnits value) {
    (void)value;
}
void furi_hal_rtc_set_locale_timeformat(FuriHalRtcLocaleTimeFormat value) {
    (void)value;
}
void furi_hal_rtc_set_locale_dateformat(FuriHalRtcLocaleDateFormat value) {
    (void)value;
}

/* ---- device identity ---------------------------------------------------
 * Screens that print the firmware version, the hardware revision or the
 * Flipper's name (desktop_view_debug.c, dolphin_passport/passport.c) get
 * placeholder values: a generic name, the retail F7B9C6 board revision and
 * a release-style version string. Nothing here comes from a real device.
 */
#define HOST_FLIPPER_NAME "Flipper"

const char* furi_hal_version_get_name_ptr(void) {
    return HOST_FLIPPER_NAME;
}
const char* furi_hal_version_get_device_name_ptr(void) {
    return "Flipper " HOST_FLIPPER_NAME;
}
const char* furi_hal_version_get_ble_local_device_name_ptr(void) {
    return "Flipper " HOST_FLIPPER_NAME;
}
uint8_t furi_hal_version_get_hw_version(void) {
    return 13;
}
uint8_t furi_hal_version_get_hw_target(void) {
    return 7;
}
uint8_t furi_hal_version_get_hw_body(void) {
    return 9;
}
uint8_t furi_hal_version_get_hw_connect(void) {
    return 6;
}
FuriHalVersionColor furi_hal_version_get_hw_color(void) {
    return FuriHalVersionColorBlack;
}
FuriHalVersionRegion furi_hal_version_get_hw_region_otp(void) {
    return FuriHalVersionRegionUnknown;
}
const char* furi_hal_version_get_hw_region_name_otp(void) {
    return "R00";
}
const char* furi_hal_version_get_hw_region_name(void) {
    return "R00";
}

/* lib/toolbox/version.c is generated from git at build time (version.inc.h),
 * so it is not compiled here; these accessors return the placeholder build. */
static const uint8_t host_version_handle = 0;

const Version* version_get(void) {
    return (const Version*)&host_version_handle;
}
const Version* furi_hal_version_get_firmware_version(void) {
    return version_get();
}
const char* version_get_version(const Version* v) {
    UNUSED(v);
    return "unlshd-080";
}
const char* version_get_builddate(const Version* v) {
    UNUSED(v);
    return "21-11-2026";
}
const char* version_get_githash(const Version* v) {
    UNUSED(v);
    return "7f31d0cc";
}
const char* version_get_gitbranch(const Version* v) {
    UNUSED(v);
    return "dev";
}
const char* version_get_gitbranchnum(const Version* v) {
    UNUSED(v);
    return "0";
}
bool version_get_dirty_flag(const Version* v) {
    UNUSED(v);
    return false;
}
uint8_t version_get_target(const Version* v) {
    UNUSED(v);
    return 7;
}
const char* version_get_firmware_origin(const Version* v) {
    UNUSED(v);
    return "Unleashed";
}
const char* version_get_custom_name(const Version* v) {
    UNUSED(v);
    return NULL;
}
void furi_hal_info_get_api_version(uint16_t* major, uint16_t* minor) {
    /* targets/f7/api_symbols.csv */
    *major = 88;
    *minor = 27;
}

/* ble_glue_get_c2_info(): the copro version string the radio stack reports
 * ("<major>.<minor>.<sub>:<release type>", L = BLE Light, the stack the
 * Flipper ships, COPRO_CUBE_VERSION in fbt_options.py) */
const BleGlueC2Info* ble_glue_get_c2_info(void) {
    static BleGlueC2Info info = {
        .mode = BleGlueC2ModeStack,
        .VersionMajor = 1,
        .VersionMinor = 20,
        .VersionSub = 0,
        .StackType = 0x04, /* INFO_STACK_TYPE_BLE_LIGHT */
        .StackTypeString = "1.20.0:L",
    };
    return &info;
}
