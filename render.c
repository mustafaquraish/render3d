#include "stdarg.h"
#include "string.h"
#include "ctype.h"
#include "math.h"
#include "time.h"
#include "SDL2/SDL.h"
#include "zlib.h"
#include "dirent.h"
#include "unistd.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "errno.h"

/* Embed: /home/runner/work/render3d/render3d/ocen/std/og/interface.c */
/**
 * This is a simple interface to register a main loop function.
 * It's written at the C level since we want some compile-time
 * conditional logic dependong on the target platform, which
 * we cannot do natively in Ocen right now.
*/

// NOTE: Emscripten expects a callback that doesn't return anything,
//       but we want to be able to return a boolean to indicate when
//       the main loop should stop. We'll use a wrapper function to
//       handle this, and store the actual callback in a global variable.


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>

_Bool (*callback)(void) = NULL;
// EMS no-return callback wrapper
void ems_callback() {
    if (callback) callback();
}
#endif

void c_set_main_loop(_Bool (*func)(void)) {
#ifdef __EMSCRIPTEN__
    callback = func;
    emscripten_set_main_loop(ems_callback, 0, 1);
#else
    while (func()) {}
#endif
}


/* Embed: /home/runner/work/render3d/render3d/ocen/std/./prelude.h */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

const char* __asan_default_options() { return "detect_leaks=0"; }

//// Backtraces

volatile static const char *__oc_bt[] = {0};
volatile u64 __oc_bt_idx = 0;

#define _WITH_BT(s, ...)      \
  __oc_bt[__oc_bt_idx++] = s; \
  __VA_ARGS__;                \
  (void)__oc_bt_idx--;

void dump_backtrace() {
  if (__oc_bt_idx == 0) {
    return;
  }
  fprintf(stderr, "--------------------------------------------------------------------------------\n");
  fprintf(stderr, "Backtrace:\n");
  for (u64 i = 0; i < __oc_bt_idx; i++) {
    fprintf(stderr, "  => %s\n", __oc_bt[i]);
  }

  fprintf(stderr, "--------------------------------------------------------------------------------\n");
}

/// End backtraces

#ifdef __APPLE__
  #define oc_trap __builtin_debugtrap
#else
  #define oc_trap __builtin_trap
#endif

void ae_assert_fail(char *dbg_msg, char *msg) {
  dump_backtrace();
  fprintf(stderr, "--------------------------------------------------------------------------------\n");
  fprintf(stderr, "%s\n", dbg_msg);
  if (msg) {
    fprintf(stderr, "  Message: %s\n", msg);
  }
  fprintf(stderr, "--------------------------------------------------------------------------------\n");
  fflush(stdout);
  oc_trap();
}


/* Constants */
#define std_compact_map_INDEX_FREE (-1)
#define std_compact_map_INDEX_DELETED (-2)
#define std_og_state_FRAMETIMES_COUNT (200)
#define src_bvh_NUM_BUCKETS (12)
/* Typedefs */
typedef struct std_sv_SV std_sv_SV;
typedef struct std_sv_SVLineIterator std_sv_SVLineIterator;
typedef struct std_sv_SVSplitIterator std_sv_SVSplitIterator;
typedef struct _ClosureTy_18 _ClosureTy_18;
typedef struct std_compact_map_Item__0 std_compact_map_Item__0;
typedef struct std_compact_map_Map__0 std_compact_map_Map__0;
typedef struct std_vector_Iterator__6 std_vector_Iterator__6;
typedef struct std_compact_map_Iterator__0 std_compact_map_Iterator__0;
typedef struct std_image_Color std_image_Color;
typedef struct std_image_Image std_image_Image;
typedef struct std_argparse_ArgUnion std_argparse_ArgUnion;
typedef enum std_argparse_ArgType std_argparse_ArgType;
typedef struct std_argparse_Arg std_argparse_Arg;
typedef struct std_argparse_Parser std_argparse_Parser;
typedef enum std_argparse_BoolAction std_argparse_BoolAction;
typedef struct std_buffer_Buffer std_buffer_Buffer;
typedef enum std_logging_LogLevel std_logging_LogLevel;
typedef struct std_og_Texture std_og_Texture;
typedef struct std_og_state_KeyState std_og_state_KeyState;
typedef struct std_vec_Vec2__3 std_vec_Vec2__3;
typedef struct std_og_state_MouseState std_og_state_MouseState;
typedef enum std_og_state_MouseWheel std_og_state_MouseWheel;
typedef struct std_vec_Vec2__1 std_vec_Vec2__1;
typedef struct std_vec_Vec3__0 std_vec_Vec3__0;
typedef struct std_vector_Vector__0 std_vector_Vector__0;
typedef struct std_vector_Vector__1 std_vector_Vector__1;
typedef struct std_vector_Vector__2 std_vector_Vector__2;
typedef struct std_vector_Vector__3 std_vector_Vector__3;
typedef struct std_vector_Vector__4 std_vector_Vector__4;
typedef struct std_vector_Vector__5 std_vector_Vector__5;
typedef struct std_vector_Vector__6 std_vector_Vector__6;
typedef struct std_vector_Iterator__0 std_vector_Iterator__0;
typedef struct std_vector_Iterator__1 std_vector_Iterator__1;
typedef struct std_vector_Iterator__2 std_vector_Iterator__2;
typedef struct std_vector_Iterator__3 std_vector_Iterator__3;
typedef struct std_matrix_Matrix4f std_matrix_Matrix4f;
typedef struct src_bounds_Bounds src_bounds_Bounds;
typedef struct Triangle Triangle;
typedef struct src_bvh_BVH__0 src_bvh_BVH__0;
typedef struct src_bvh_Bucket src_bvh_Bucket;
typedef struct Mesh Mesh;
typedef struct Vertex Vertex;
typedef struct src_zbuffer_ZBuffer src_zbuffer_ZBuffer;
typedef struct src_ray_Ray src_ray_Ray;
typedef struct _ClosureTy_8 _ClosureTy_8;
typedef struct _ClosureTy_9 _ClosureTy_9;
typedef struct _ClosureTy_13 _ClosureTy_13;
typedef struct _ClosureTy_16 _ClosureTy_16;
typedef struct _ClosureTy_17 _ClosureTy_17;
typedef struct _ClosureTy_20 _ClosureTy_20;
typedef struct _ClosureTy_21 _ClosureTy_21;
typedef struct from_obj__Closure_0Ctx from_obj__Closure_0Ctx;
typedef struct run_ui__Closure_1Ctx run_ui__Closure_1Ctx;
typedef struct run_ui__Closure_2Ctx run_ui__Closure_2Ctx;
typedef struct run_ui__Closure_3Ctx run_ui__Closure_3Ctx;
typedef struct run_ui__Closure_4Ctx run_ui__Closure_4Ctx;
typedef struct run_ui__Closure_5Ctx run_ui__Closure_5Ctx;
typedef struct run_ui__Closure_6Ctx run_ui__Closure_6Ctx;
typedef struct run_ui__Closure_7Ctx run_ui__Closure_7Ctx;
typedef struct run_ui__Closure_8Ctx run_ui__Closure_8Ctx;
typedef struct run_ui__Closure_9Ctx run_ui__Closure_9Ctx;
typedef struct run_ui__Closure_10Ctx run_ui__Closure_10Ctx;
typedef struct run_ui__Closure_11Ctx run_ui__Closure_11Ctx;
typedef struct run_ui__Closure_12Ctx run_ui__Closure_12Ctx;
typedef struct run_ui__Closure_13Ctx run_ui__Closure_13Ctx;
typedef struct run_ui__Closure_14Ctx run_ui__Closure_14Ctx;
typedef struct draw_line_clipped_thick__Closure_15Ctx draw_line_clipped_thick__Closure_15Ctx;
typedef struct draw_bounds_projected__Closure_16Ctx draw_bounds_projected__Closure_16Ctx;
typedef struct std_argparse_usage_and_exit__Closure_21Ctx std_argparse_usage_and_exit__Closure_21Ctx;
typedef struct src_bvh_split_SAH__Closure_22Ctx src_bvh_split_SAH__Closure_22Ctx;
typedef struct src_bvh_split_equal__Closure_23Ctx src_bvh_split_equal__Closure_23Ctx;

/* Structs */
struct std_sv_SV {
  char *data;
  u32 len;
};

struct std_sv_SVLineIterator {
  std_sv_SV sv;
};

struct std_sv_SVSplitIterator {
  std_sv_SV sv;
  std_sv_SV delim;
};

char *std_sdl_Key_dbg(SDL_Scancode this) {
  switch (this) {
    case SDL_SCANCODE_A: return "A";
    case SDL_SCANCODE_B: return "B";
    case SDL_SCANCODE_C: return "C";
    case SDL_SCANCODE_D: return "D";
    case SDL_SCANCODE_E: return "E";
    case SDL_SCANCODE_F: return "F";
    case SDL_SCANCODE_G: return "G";
    case SDL_SCANCODE_H: return "H";
    case SDL_SCANCODE_I: return "I";
    case SDL_SCANCODE_J: return "J";
    case SDL_SCANCODE_K: return "K";
    case SDL_SCANCODE_L: return "L";
    case SDL_SCANCODE_M: return "M";
    case SDL_SCANCODE_N: return "N";
    case SDL_SCANCODE_O: return "O";
    case SDL_SCANCODE_P: return "P";
    case SDL_SCANCODE_Q: return "Q";
    case SDL_SCANCODE_R: return "R";
    case SDL_SCANCODE_S: return "S";
    case SDL_SCANCODE_T: return "T";
    case SDL_SCANCODE_U: return "U";
    case SDL_SCANCODE_V: return "V";
    case SDL_SCANCODE_W: return "W";
    case SDL_SCANCODE_X: return "X";
    case SDL_SCANCODE_Y: return "Y";
    case SDL_SCANCODE_Z: return "Z";
    case SDL_SCANCODE_UP: return "Up";
    case SDL_SCANCODE_DOWN: return "Down";
    case SDL_SCANCODE_LEFT: return "Left";
    case SDL_SCANCODE_RIGHT: return "Right";
    case SDL_SCANCODE_SPACE: return "Space";
    case SDL_SCANCODE_ESCAPE: return "Escape";
    case SDL_SCANCODE_COMMA: return "Comma";
    case SDL_SCANCODE_PERIOD: return "Dot";
    default: return "<unknown>";
  }
}

struct _ClosureTy_18 {
  void *_C;
  void (*fn)(void *__C);
};
struct std_compact_map_Item__0 {
  u32 hash;
  SDL_Scancode key;
  _ClosureTy_18 value;
};

struct std_compact_map_Map__0 {
  std_vector_Vector__6 *items;
  i32 *indices;
  u32 capacity;
  u32 num_tombstones;
};

struct std_vector_Iterator__6 {
  std_vector_Vector__6 *vec;
  u32 index;
};

struct std_compact_map_Iterator__0 {
  std_vector_Iterator__6 iter;
};

struct std_image_Color {
  u8 r;
  u8 g;
  u8 b;
};

struct std_image_Image {
  u32 width;
  u32 height;
  std_image_Color *data;
};

struct std_argparse_ArgUnion {
  char *as_str;
  i64 as_int;
  bool as_bool;
  f64 as_float;
};

enum std_argparse_ArgType {
  std_argparse_ArgType_String,
  std_argparse_ArgType_Int,
  std_argparse_ArgType_Bool,
  std_argparse_ArgType_Float,
};

char *std_argparse_ArgType_dbg(std_argparse_ArgType this) {
  switch (this) {
    case std_argparse_ArgType_String: return "String";
    case std_argparse_ArgType_Int: return "Int";
    case std_argparse_ArgType_Bool: return "Bool";
    case std_argparse_ArgType_Float: return "Float";
    default: return "<unknown>";
  }
}

struct std_argparse_Arg {
  std_vector_Vector__0 *flags;
  char *flags_display;
  bool is_positional;
  bool required;
  char *help;
  std_argparse_ArgType type;
  std_argparse_ArgUnion val;
  std_argparse_ArgUnion defolt;
  bool parsed;
};

struct std_argparse_Parser {
  char *description;
  std_vector_Vector__1 *args;
  char *program_name;
};

enum std_argparse_BoolAction {
  std_argparse_BoolAction_StoreTrue,
  std_argparse_BoolAction_StoreFalse,
};

char *std_argparse_BoolAction_dbg(std_argparse_BoolAction this) {
  switch (this) {
    case std_argparse_BoolAction_StoreTrue: return "StoreTrue";
    case std_argparse_BoolAction_StoreFalse: return "StoreFalse";
    default: return "<unknown>";
  }
}

struct std_buffer_Buffer {
  u8 *data;
  u32 size;
  u32 capacity;
};

enum std_logging_LogLevel {
  std_logging_LogLevel_Debug,
  std_logging_LogLevel_Info,
  std_logging_LogLevel_Warn,
  std_logging_LogLevel_Error,
};

char *std_logging_LogLevel_dbg(std_logging_LogLevel this) {
  switch (this) {
    case std_logging_LogLevel_Debug: return "Debug";
    case std_logging_LogLevel_Info: return "Info";
    case std_logging_LogLevel_Warn: return "Warn";
    case std_logging_LogLevel_Error: return "Error";
    default: return "<unknown>";
  }
}

struct std_og_Texture {
  SDL_Texture *tx;
  i32 w;
  i32 h;
  u8 *pixels;
  i32 pitch;
};

struct std_og_state_KeyState {
  bool keys[SDL_NUM_SCANCODES];
};

struct std_vec_Vec2__3 {
  i32 x;
  i32 y;
};

struct std_og_state_MouseState {
  std_vec_Vec2__3 vec;
  std_vec_Vec2__3 pos;
  bool buttons[16];
  bool wheel_dirs[8];
  std_vec_Vec2__3 scroll;
};

enum std_og_state_MouseWheel {
  std_og_state_MouseWheel_Down,
  std_og_state_MouseWheel_Right,
  std_og_state_MouseWheel_Up,
  std_og_state_MouseWheel_Left,
};

char *std_og_state_MouseWheel_dbg(std_og_state_MouseWheel this) {
  switch (this) {
    case std_og_state_MouseWheel_Down: return "Down";
    case std_og_state_MouseWheel_Right: return "Right";
    case std_og_state_MouseWheel_Up: return "Up";
    case std_og_state_MouseWheel_Left: return "Left";
    default: return "<unknown>";
  }
}

char *std_fs_SeekMode_dbg(i32 this) {
  switch (this) {
    case SEEK_SET: return "Set";
    case SEEK_CUR: return "Cur";
    case SEEK_END: return "End";
    default: return "<unknown>";
  }
}

struct std_vec_Vec2__1 {
  f32 x;
  f32 y;
};

struct std_vec_Vec3__0 {
  f32 x;
  f32 y;
  f32 z;
};

struct std_vector_Vector__0 {
  std_sv_SV *data;
  u32 size;
  u32 capacity;
};

struct std_vector_Vector__1 {
  std_argparse_Arg **data;
  u32 size;
  u32 capacity;
};

struct std_vector_Vector__2 {
  src_bvh_BVH__0 **data;
  u32 size;
  u32 capacity;
};

struct std_vector_Vector__3 {
  Triangle *data;
  u32 size;
  u32 capacity;
};

struct std_vector_Vector__4 {
  std_vec_Vec3__0 *data;
  u32 size;
  u32 capacity;
};

struct std_vector_Vector__5 {
  std_vec_Vec2__1 *data;
  u32 size;
  u32 capacity;
};

struct std_vector_Vector__6 {
  std_compact_map_Item__0 *data;
  u32 size;
  u32 capacity;
};

struct std_vector_Iterator__0 {
  std_vector_Vector__0 *vec;
  u32 index;
};

struct std_vector_Iterator__1 {
  std_vector_Vector__1 *vec;
  u32 index;
};

struct std_vector_Iterator__2 {
  std_vector_Vector__2 *vec;
  u32 index;
};

struct std_vector_Iterator__3 {
  std_vector_Vector__3 *vec;
  u32 index;
};

struct std_matrix_Matrix4f {
  f32 d[4][4];
};

char *std_sdl_MouseButton_dbg(u8 this) {
  switch (this) {
    case SDL_BUTTON_LEFT: return "Left";
    case SDL_BUTTON_MIDDLE: return "Middle";
    case SDL_BUTTON_RIGHT: return "Right";
    case SDL_BUTTON_X1: return "Forward";
    case SDL_BUTTON_X2: return "Backward";
    default: return "<unknown>";
  }
}

char *std_sdl_EventType_dbg(SDL_EventType this) {
  switch (this) {
    case SDL_QUIT: return "Quit";
    case SDL_KEYDOWN: return "KeyDown";
    case SDL_KEYUP: return "KeyUp";
    case SDL_MOUSEBUTTONDOWN: return "MouseDown";
    case SDL_MOUSEBUTTONUP: return "MouseUp";
    case SDL_MOUSEWHEEL: return "Wheel";
    case SDL_WINDOWEVENT: return "Window";
    case SDL_USEREVENT: return "User";
    default: return "<unknown>";
  }
}

struct src_bounds_Bounds {
  std_vec_Vec3__0 min;
  std_vec_Vec3__0 max;
};

struct Triangle {
  std_vec_Vec3__0 p0;
  std_vec_Vec3__0 p1;
  std_vec_Vec3__0 p2;
  std_vec_Vec3__0 n0;
  std_vec_Vec3__0 n1;
  std_vec_Vec3__0 n2;
};

struct src_bvh_BVH__0 {
  src_bounds_Bounds bounds;
  bool is_leaf;
  Triangle obj;
  src_bvh_BVH__0 *l;
  src_bvh_BVH__0 *r;
};

struct src_bvh_Bucket {
  u32 count;
  src_bounds_Bounds bounds;
};

struct Mesh {
  std_vector_Vector__3 *triangles;
};

struct Vertex {
  std_vec_Vec3__0 pos;
  std_vec_Vec2__1 tex;
  std_vec_Vec3__0 nor;
};

struct src_zbuffer_ZBuffer {
  u32 width;
  u32 height;
  f32 *data;
};

struct src_ray_Ray {
  std_vec_Vec3__0 pos;
  std_vec_Vec3__0 dir;
};

struct _ClosureTy_8 {
  void *_C;
  bool (*fn)(void *__C, Triangle);
};
struct _ClosureTy_9 {
  void *_C;
  void (*fn)(void *__C, std_argparse_Arg *arg);
};
struct _ClosureTy_13 {
  void *_C;
  i8 (*fn)(void *__C, Triangle, Triangle);
};
struct _ClosureTy_16 {
  void *_C;
  Vertex (*fn)(void *__C, std_sv_SV *line);
};
struct _ClosureTy_17 {
  void *_C;
  void (*fn)(void *__C, i32 dx, i32 dy, f32 sensitivity);
};
struct _ClosureTy_20 {
  void *_C;
  void (*fn)(void *__C, std_vec_Vec3__0 p0, std_vec_Vec3__0 p1, std_vec_Vec3__0 p2);
};
struct _ClosureTy_21 {
  void *_C;
  void (*fn)(void *__C, std_vec_Vec3__0 p0, std_vec_Vec3__0 p1);
};
struct from_obj__Closure_0Ctx {
  std_vector_Vector__5 **textures;
  std_vector_Vector__4 **normals;
  std_vector_Vector__4 **vectors;
};
struct run_ui__Closure_1Ctx {
  f32 *dtime;
};
struct run_ui__Closure_2Ctx {
  f32 *dtime;
  f32 *MOVE_SENSITIVITY;
};
struct run_ui__Closure_3Ctx {
  f32 *dtime;
  f32 *MOVE_SENSITIVITY;
};
struct run_ui__Closure_4Ctx {
  f32 *dtime;
  f32 *MOVE_SENSITIVITY;
};
struct run_ui__Closure_5Ctx {
  f32 *dtime;
  f32 *MOVE_SENSITIVITY;
};
struct run_ui__Closure_6Ctx {
  f32 *dtime;
  f32 *MOVE_SENSITIVITY;
};
struct run_ui__Closure_7Ctx {
  f32 *dtime;
  f32 *MOVE_SENSITIVITY;
};
struct run_ui__Closure_8Ctx {
};
struct run_ui__Closure_9Ctx {
};
struct run_ui__Closure_10Ctx {
  f32 *KEYBOARD_LOOK_SENSITIVITY;
  _ClosureTy_17 *rotate_camera;
};
struct run_ui__Closure_11Ctx {
  f32 *KEYBOARD_LOOK_SENSITIVITY;
  _ClosureTy_17 *rotate_camera;
};
struct run_ui__Closure_12Ctx {
  f32 *KEYBOARD_LOOK_SENSITIVITY;
  _ClosureTy_17 *rotate_camera;
};
struct run_ui__Closure_13Ctx {
  f32 *KEYBOARD_LOOK_SENSITIVITY;
  _ClosureTy_17 *rotate_camera;
};
struct run_ui__Closure_14Ctx {
};
struct draw_line_clipped_thick__Closure_15Ctx {
};
struct draw_bounds_projected__Closure_16Ctx {
  std_image_Color *color;
  bool *thick;
  f32 *thickness;
};
struct std_argparse_usage_and_exit__Closure_21Ctx {
  u32 *max_len;
};
struct src_bvh_split_SAH__Closure_22Ctx {
  src_bounds_Bounds *bounds;
  u32 *min_bucket;
  u32 *axis;
};
struct src_bvh_split_equal__Closure_23Ctx {
  u32 *axis;
};
/* function declarations */
void std_panic(char *msg) __attribute__((noreturn));
bool str_eq(char *this, char *other);
char *std_format(char *fmt, ...);
bool char_is_space(char this);
i32 i32_min(i32 this, i32 b);
i32 i32_max(i32 this, i32 b);
u32 u32_max(u32 this, u32 other);
char *std_mem_alloc__0(u32 count);
i32 *std_mem_alloc__1(u32 count);
std_image_Image *std_mem_alloc__2(u32 count);
std_image_Color *std_mem_alloc__3(u32 count);
std_argparse_Arg *std_mem_alloc__4(u32 count);
u8 *std_mem_alloc__5(u32 count);
std_vector_Vector__0 *std_mem_alloc__6(u32 count);
std_sv_SV *std_mem_alloc__7(u32 count);
std_vector_Vector__1 *std_mem_alloc__8(u32 count);
std_argparse_Arg **std_mem_alloc__9(u32 count);
std_vector_Vector__2 *std_mem_alloc__10(u32 count);
src_bvh_BVH__0 **std_mem_alloc__11(u32 count);
std_vector_Vector__3 *std_mem_alloc__12(u32 count);
Triangle *std_mem_alloc__13(u32 count);
f32 *std_mem_alloc__14(u32 count);
std_compact_map_Map__0 *std_mem_alloc__15(u32 count);
std_vector_Vector__6 *std_mem_alloc__16(u32 count);
std_compact_map_Item__0 *std_mem_alloc__17(u32 count);
std_vector_Vector__5 *std_mem_alloc__18(u32 count);
std_vec_Vec2__1 *std_mem_alloc__19(u32 count);
std_vector_Vector__4 *std_mem_alloc__20(u32 count);
std_vec_Vec3__0 *std_mem_alloc__21(u32 count);
void std_mem_free(void *ptr);
std_sv_SV *std_mem_realloc__1(std_sv_SV *ptr, u32 old_count, u32 new_count);
std_argparse_Arg **std_mem_realloc__2(std_argparse_Arg **ptr, u32 old_count, u32 new_count);
src_bvh_BVH__0 **std_mem_realloc__3(src_bvh_BVH__0 **ptr, u32 old_count, u32 new_count);
Triangle *std_mem_realloc__4(Triangle *ptr, u32 old_count, u32 new_count);
std_compact_map_Item__0 *std_mem_realloc__5(std_compact_map_Item__0 *ptr, u32 old_count, u32 new_count);
std_vec_Vec2__1 *std_mem_realloc__6(std_vec_Vec2__1 *ptr, u32 old_count, u32 new_count);
std_vec_Vec3__0 *std_mem_realloc__7(std_vec_Vec3__0 *ptr, u32 old_count, u32 new_count);
void *std_mem_impl_my_calloc(void *state, u32 size);
void *std_mem_impl_my_realloc(void *state, void *ptr, u32 old_size, u32 size);
void std_mem_impl_my_free(void *state, void *ptr);
bool std_sv_SV_is_empty(std_sv_SV *this);
std_sv_SV std_sv_SV_from_str(char *s);
std_sv_SV std_sv_SV_get(std_sv_SV this, u32 n);
char std_sv_SV_at(std_sv_SV this, u32 n);
std_sv_SV std_sv_SV_chop_left(std_sv_SV *this, u32 n);
void std_sv_SV_trim_left(std_sv_SV *this);
void std_sv_SV_trim_right(std_sv_SV *this);
void std_sv_SV_trim(std_sv_SV *this);
std_sv_SV std_sv_SV_chop_by_delim(std_sv_SV *this, char delim);
std_sv_SV std_sv_SV_chop_by_sv(std_sv_SV *this, std_sv_SV delim);
std_sv_SV std_sv_SV_chop_word(std_sv_SV *this);
u64 std_sv_SV_chop_unsigned(std_sv_SV *this, char *fn_name);
u32 std_sv_SV_chop_u32(std_sv_SV *this);
f32 std_sv_SV_chop_f32(std_sv_SV *this);
i64 std_sv_SV_chop_signed(std_sv_SV *this, char *fn_name);
i64 std_sv_SV_chop_i64(std_sv_SV *this);
std_sv_SV std_sv_SV_chop_line(std_sv_SV *this);
bool std_sv_SV_eq(std_sv_SV this, std_sv_SV other);
bool std_sv_SV_eq_str(std_sv_SV this, char *other);
void std_sv_SV_only_chop_left(std_sv_SV *this, u32 n);
bool std_sv_SV_starts_with_sv(std_sv_SV this, std_sv_SV other);
bool std_sv_SV_starts_with_str(std_sv_SV this, char *other);
std_sv_SVLineIterator std_sv_SV_lines(std_sv_SV this);
std_sv_SVSplitIterator std_sv_SV_split_str(std_sv_SV this, char *delim);
bool std_sv_SVLineIterator_has_value(std_sv_SVLineIterator *this);
std_sv_SV std_sv_SVLineIterator_cur(std_sv_SVLineIterator *this);
void std_sv_SVLineIterator_next(std_sv_SVLineIterator *this);
bool std_sv_SVSplitIterator_has_value(std_sv_SVSplitIterator *this);
std_sv_SV std_sv_SVSplitIterator_cur(std_sv_SVSplitIterator *this);
void std_sv_SVSplitIterator_next(std_sv_SVSplitIterator *this);
std_compact_map_Iterator__0 std_compact_map_Map__0_iter(std_compact_map_Map__0 *this);
std_compact_map_Item__0 std_compact_map_Iterator__0_cur(std_compact_map_Iterator__0 *this);
void std_compact_map_Iterator__0_next(std_compact_map_Iterator__0 *this);
bool std_compact_map_Iterator__0_has_value(std_compact_map_Iterator__0 *this);
void std_compact_map_Map__0_insert(std_compact_map_Map__0 *this, SDL_Scancode key, _ClosureTy_18 value);
u32 std_compact_map_Map__0_get_index(std_compact_map_Map__0 *this, SDL_Scancode key, u32 hash);
void std_compact_map_Map__0_resize(std_compact_map_Map__0 *this, u32 new_capacity);
std_compact_map_Map__0 *std_compact_map_Map__0_new(u32 capacity);
void std_compact_map_Map__0_resize_if_necessary(std_compact_map_Map__0 *this);
char *std_libc_errno_get_err(void);
std_image_Image *std_image_Image_new(u32 width, u32 height);
std_image_Color std_image_Image_get(std_image_Image *this, u32 x, u32 y);
void std_image_Image_set(std_image_Image *this, u32 x, u32 y, std_image_Color col);
void std_image_Image_clear(std_image_Image *this);
void std_argparse_Arg_save_val(std_argparse_Arg *this, char *s);
std_argparse_Parser std_argparse_Parser_make(char *description);
std_argparse_Arg *std_argparse_Parser__add(std_argparse_Parser *this, char *flags, bool required, char *help);
char **std_argparse_Parser_add_str(std_argparse_Parser *this, char *flags, char *defolt, bool required, char *help);
bool *std_argparse_Parser_add_bool(std_argparse_Parser *this, char *flags, std_argparse_BoolAction action, char *help);
std_argparse_Arg *std_argparse_find_arg(std_argparse_Parser *parser, char *_flag, i32 *positional_idx);
void std_argparse_Parser_usage_and_exit(std_argparse_Parser *this, i32 code);
void std_argparse_Parser_parse(std_argparse_Parser *this, i32 argc, char **argv, bool consume_first);
std_buffer_Buffer std_buffer_Buffer_make(u32 capacity);
std_sv_SV std_buffer_Buffer_sv(std_buffer_Buffer this);
void std_buffer_Buffer_free(std_buffer_Buffer *this);
void std_logging_vlog(std_logging_LogLevel level, char *fmt, va_list vargs);
void std_logging_log(std_logging_LogLevel level, char *fmt, ...);
i8 f32_compare(f32 this, f32 b);
u32 u32_hash(u32 this);
u32 std_og_get_ticks(void);
void std_og_init(u32 width, u32 height, char *title, bool fullscreen);
void std_og_toggle_fullscreen(void);
bool std_og_is_running(void);
void std_og_quit(void);
bool std_og_is_key_pressed(SDL_Scancode k);
bool std_og_is_key_down(SDL_Scancode k);
std_vec_Vec2__3 std_og_get_mouse_delta(void);
void std_og_grab_input(bool grab);
void std_og_show_cursor(bool show);
std_og_Texture *std_og_get_buffer_sized(i32 w, i32 h);
void std_og_draw_buffer(void);
void std_og_display_image(std_image_Image *img);
bool std_og_state_KeyState_get(std_og_state_KeyState *this, SDL_Scancode k);
void std_og_state_update_window_size(void);
void std_og_state_add_frametime(f32 frametime);
f32 std_og_state_get_avg_frametime(void);
void std_og_utils_handle_sdl_events(void);
std_buffer_Buffer std_fs_read_file(char *path);
f64 std_time_get_time_monotonic_ms(void);
f32 f32_inf(void);
f32 f32_min(f32 this, f32 b);
f32 f32_max(f32 this, f32 b);
std_vec_Vec2__1 std_vec_Vec2__1_mult(std_vec_Vec2__1 this, std_vec_Vec2__1 other);
std_vec_Vec2__3 std_vec_Vec2__1_to_i32(std_vec_Vec2__1 this);
std_vec_Vec2__1 std_vec_Vec2__1_mults(std_vec_Vec2__1 this, f32 val);
std_vec_Vec2__1 std_vec_Vec2__1_adds(std_vec_Vec2__1 this, f32 val);
std_vec_Vec2__1 std_vec_Vec2__1_div(std_vec_Vec2__1 this, std_vec_Vec2__1 other);
std_vec_Vec3__0 std_vec_Vec3__0_rotate_axis(std_vec_Vec3__0 this, std_vec_Vec3__0 axis, f32 angle);
std_vec_Vec3__0 std_vec_Vec3__0_add(std_vec_Vec3__0 this, std_vec_Vec3__0 other);
std_vec_Vec3__0 std_vec_Vec3__0_divs(std_vec_Vec3__0 this, f32 val);
f32 std_vec_Vec3__0_length(std_vec_Vec3__0 this);
std_vec_Vec3__0 std_vec_Vec3__0_sub(std_vec_Vec3__0 this, std_vec_Vec3__0 other);
std_vec_Vec3__0 std_vec_Vec3__0_multrs(f32 val, std_vec_Vec3__0 this);
std_vec_Vec3__0 std_vec_Vec3__0_normalized(std_vec_Vec3__0 this);
std_vec_Vec3__0 std_vec_Vec3__0_to_f32(std_vec_Vec3__0 this);
std_vec_Vec3__0 std_vec_Vec3__0_mults(std_vec_Vec3__0 this, f32 val);
std_vec_Vec3__0 std_vec_Vec3__0_adds(std_vec_Vec3__0 this, f32 val);
f32 std_vec_Vec3__0_dot(std_vec_Vec3__0 this, std_vec_Vec3__0 other);
std_vec_Vec3__0 std_vec_Vec3__0_cross(std_vec_Vec3__0 this, std_vec_Vec3__0 other);
f32 std_vec_Vec3__0_index(std_vec_Vec3__0 this, u32 idx);
std_vec_Vec3__0 std_vec_Vec3__0_divrs(f32 val, std_vec_Vec3__0 this);
std_vector_Iterator__0 std_vector_Vector__0_iter(std_vector_Vector__0 *this);
std_sv_SV std_vector_Iterator__0_cur(std_vector_Iterator__0 *this);
void std_vector_Iterator__0_next(std_vector_Iterator__0 *this);
bool std_vector_Iterator__0_has_value(std_vector_Iterator__0 *this);
std_vector_Iterator__0 std_vector_Iterator__0_make(std_vector_Vector__0 *vec);
std_sv_SV std_vector_Vector__0_at(std_vector_Vector__0 *this, u32 i);
void std_vector_Vector__0_resize(std_vector_Vector__0 *this, u32 new_capacity);
std_vector_Vector__0 *std_vector_Vector__0_new(u32 capacity);
void std_vector_Vector__0_push(std_vector_Vector__0 *this, std_sv_SV value);
std_vector_Iterator__1 std_vector_Vector__1_iter(std_vector_Vector__1 *this);
std_argparse_Arg *std_vector_Iterator__1_cur(std_vector_Iterator__1 *this);
void std_vector_Iterator__1_next(std_vector_Iterator__1 *this);
bool std_vector_Iterator__1_has_value(std_vector_Iterator__1 *this);
std_vector_Iterator__1 std_vector_Iterator__1_make(std_vector_Vector__1 *vec);
void std_vector_Vector__1_resize(std_vector_Vector__1 *this, u32 new_capacity);
std_vector_Vector__1 *std_vector_Vector__1_new(u32 capacity);
void std_vector_Vector__1_push(std_vector_Vector__1 *this, std_argparse_Arg *value);
void std_vector_Vector__2_zero_unused(std_vector_Vector__2 *this);
std_vector_Iterator__2 std_vector_Vector__2_iter(std_vector_Vector__2 *this);
src_bvh_BVH__0 *std_vector_Iterator__2_cur(std_vector_Iterator__2 *this);
void std_vector_Iterator__2_next(std_vector_Iterator__2 *this);
bool std_vector_Iterator__2_has_value(std_vector_Iterator__2 *this);
std_vector_Iterator__2 std_vector_Iterator__2_make(std_vector_Vector__2 *vec);
void std_vector_Vector__2_resize(std_vector_Vector__2 *this, u32 new_capacity);
std_vector_Vector__2 *std_vector_Vector__2_new(u32 capacity);
void std_vector_Vector__2_push(std_vector_Vector__2 *this, src_bvh_BVH__0 *value);
void std_vector_Vector__2_clear(std_vector_Vector__2 *this);
std_vector_Iterator__3 std_vector_Vector__3_iter(std_vector_Vector__3 *this);
Triangle std_vector_Iterator__3_cur(std_vector_Iterator__3 *this);
void std_vector_Iterator__3_next(std_vector_Iterator__3 *this);
bool std_vector_Iterator__3_has_value(std_vector_Iterator__3 *this);
std_vector_Iterator__3 std_vector_Iterator__3_make(std_vector_Vector__3 *vec);
Triangle std_vector_Vector__3_at(std_vector_Vector__3 *this, u32 i);
void std_vector_Vector__3_resize(std_vector_Vector__3 *this, u32 new_capacity);
std_vector_Vector__3 *std_vector_Vector__3_new(u32 capacity);
void std_vector_Vector__3_push(std_vector_Vector__3 *this, Triangle value);
std_vec_Vec3__0 std_vector_Vector__4_at(std_vector_Vector__4 *this, u32 i);
void std_vector_Vector__4_free(std_vector_Vector__4 *this);
void std_vector_Vector__4_resize(std_vector_Vector__4 *this, u32 new_capacity);
std_vector_Vector__4 *std_vector_Vector__4_new(u32 capacity);
void std_vector_Vector__4_push(std_vector_Vector__4 *this, std_vec_Vec3__0 value);
std_vec_Vec2__1 std_vector_Vector__5_at(std_vector_Vector__5 *this, u32 i);
void std_vector_Vector__5_free(std_vector_Vector__5 *this);
void std_vector_Vector__5_resize(std_vector_Vector__5 *this, u32 new_capacity);
std_vector_Vector__5 *std_vector_Vector__5_new(u32 capacity);
void std_vector_Vector__5_push(std_vector_Vector__5 *this, std_vec_Vec2__1 value);
std_vector_Iterator__6 std_vector_Vector__6_iter(std_vector_Vector__6 *this);
std_compact_map_Item__0 std_vector_Iterator__6_cur(std_vector_Iterator__6 *this);
void std_vector_Iterator__6_next(std_vector_Iterator__6 *this);
bool std_vector_Iterator__6_has_value(std_vector_Iterator__6 *this);
std_vector_Iterator__6 std_vector_Iterator__6_make(std_vector_Vector__6 *vec);
std_compact_map_Item__0 std_vector_Vector__6_at(std_vector_Vector__6 *this, u32 i);
void std_vector_Vector__6_resize(std_vector_Vector__6 *this, u32 new_capacity);
std_vector_Vector__6 *std_vector_Vector__6_new(u32 capacity);
void std_vector_Vector__6_push(std_vector_Vector__6 *this, std_compact_map_Item__0 value);
std_matrix_Matrix4f std_matrix_Matrix4f_make(f32 d00, f32 d01, f32 d02, f32 d03, f32 d10, f32 d11, f32 d12, f32 d13, f32 d20, f32 d21, f32 d22, f32 d23, f32 d30, f32 d31, f32 d32, f32 d33);
std_vec_Vec3__0 std_matrix_Matrix4f_mulv(std_matrix_Matrix4f this, std_vec_Vec3__0 v);
u32 std_sdl_Key_hash(SDL_Scancode this);
bool std_sdl_Key_eq(SDL_Scancode this, SDL_Scancode other);
void std_sdl_Texture_write_image(SDL_Texture *this, std_image_Image *img);
Triangle std_sort_nth_element_by__0(Triangle *data, u32 size, u32 n, _ClosureTy_13 cmp);
u32 std_sort_partition_by_closure__0(Triangle *data, u32 size, _ClosureTy_8 cmp);
void src_bvh_BVH__0_hit(src_bvh_BVH__0 *this, src_ray_Ray *ray, std_vector_Vector__2 *hit_nodes);
src_bvh_BVH__0 *src_bvh_BVH__0_create(std_vector_Vector__3 *objects);
src_bvh_BVH__0 *src_bvh_BVH__0_create_rec(std_vector_Vector__3 *objects, u32 start, u32 end);
u32 src_bvh_BVH__0_split_SAH(std_vector_Vector__3 *objects, u32 start, u32 end, src_bounds_Bounds bounds, u32 axis);
u32 src_bvh_BVH__0_split_equal(std_vector_Vector__3 *objects, u32 start, u32 end, src_bounds_Bounds bounds, u32 axis);
src_bounds_Bounds src_bounds_Bounds_empty(void);
src_bounds_Bounds src_bounds_Bounds_join(src_bounds_Bounds this, src_bounds_Bounds other);
void src_bounds_Bounds_join_assign(src_bounds_Bounds *this, src_bounds_Bounds other);
std_vec_Vec3__0 src_bounds_Bounds_offset(src_bounds_Bounds *this, std_vec_Vec3__0 p);
std_vec_Vec3__0 src_bounds_Bounds_centroid(src_bounds_Bounds this);
f32 src_bounds_Bounds_area(src_bounds_Bounds this);
bool src_bounds_Bounds_hit(src_bounds_Bounds *this, src_ray_Ray *ray, f32 *t1, f32 *t2, std_vec_Vec3__0 inv_d);
std_image_Color vec_to_col(std_vec_Vec3__0 vec, f32 scale);
std_vec_Vec2__3 camera_to_screen(std_vec_Vec3__0 p0);
void draw_triangle_camera_space(std_vec_Vec3__0 p0, std_vec_Vec3__0 p1, std_vec_Vec3__0 p2, std_image_Color c0, std_image_Color c1, std_image_Color c2);
std_image_Color interp_color(std_image_Color c0, std_image_Color c1, f32 t);
std_vec_Vec3__0 interp_vec(std_vec_Vec3__0 v0, std_vec_Vec3__0 v1, f32 t);
void swap__0(u32 *a, u32 *b);
void draw_triangle_clipped(Triangle tri);
i32 i32_sign(i32 this);
bool is_ok(i32 a, i32 b);
void fill_triangle_zc(std_vec_Vec2__3 p0, std_vec_Vec2__3 p1, std_vec_Vec2__3 p2, f32 z0, f32 z1, f32 z2, std_image_Color c0, std_image_Color c1, std_image_Color c2);
src_bounds_Bounds Triangle_bounds(Triangle this);
Mesh Mesh_from_obj(char *filename);
void update_camera(std_vec_Vec3__0 *origin, std_vec_Vec3__0 *direction);
std_vec_Vec3__0 rotate_vector(std_vec_Vec3__0 v, std_vec_Vec3__0 axis, f32 angle);
void run_ui(Mesh *mesh);
void draw_line_clipped_thick(std_vec_Vec3__0 p0_w, std_vec_Vec3__0 p1_w, std_image_Color color, f32 thickness);
void draw_line_clipped(std_vec_Vec3__0 p0_w, std_vec_Vec3__0 p1_w, std_image_Color color, bool ignore_z);
void draw_line_z(std_vec_Vec2__3 p1, std_vec_Vec2__3 p2, f32 z1, f32 z2, std_image_Color color, bool ignore_z);
void draw_bounds_projected(src_bounds_Bounds bounds, std_image_Color color, bool thick);
void draw_bvh(src_bvh_BVH__0 *root, u32 depth);
void draw_ray(void);
void draw_hit_nodes(void);
i32 main(i32 argc, char **argv);
src_zbuffer_ZBuffer *src_zbuffer_ZBuffer_new(u32 w, u32 h);
void src_zbuffer_ZBuffer_clear(src_zbuffer_ZBuffer *this);
bool src_zbuffer_ZBuffer_put_if_closer(src_zbuffer_ZBuffer *this, u32 x, u32 y, f32 z);
std_vec_Vec3__0 src_ray_Ray_at(src_ray_Ray this, f32 t);
Vertex from_obj__Closure_0(void *__C, std_sv_SV *line);
void run_ui__Closure_1(void *__C, i32 dx, i32 dy, f32 sensitivity);
void run_ui__Closure_2(void *__C);
void run_ui__Closure_3(void *__C);
void run_ui__Closure_4(void *__C);
void run_ui__Closure_5(void *__C);
void run_ui__Closure_6(void *__C);
void run_ui__Closure_7(void *__C);
void run_ui__Closure_8(void *__C);
void run_ui__Closure_9(void *__C);
void run_ui__Closure_10(void *__C);
void run_ui__Closure_11(void *__C);
void run_ui__Closure_12(void *__C);
void run_ui__Closure_13(void *__C);
void run_ui__Closure_14(void *__C);
void draw_line_clipped_thick__Closure_15(void *__C, std_vec_Vec3__0 p0, std_vec_Vec3__0 p1, std_vec_Vec3__0 p2);
void draw_bounds_projected__Closure_16(void *__C, std_vec_Vec3__0 p0, std_vec_Vec3__0 p1);
void std_argparse_usage_and_exit__Closure_21(void *__C, std_argparse_Arg *arg);
bool src_bvh_split_SAH__Closure_22(void *__C, Triangle a);
i8 src_bvh_split_equal__Closure_23(void *__C, Triangle a, Triangle b);
void *std_mem_state_allocator = NULL;
void *(*std_mem_state_alloc_fn)(void *, u32) = std_mem_impl_my_calloc;
void *(*std_mem_state_realloc_fn)(void *, void *, u32, u32) = std_mem_impl_my_realloc;
void (*std_mem_state_free_fn)(void *, void *) = std_mem_impl_my_free;
std_logging_LogLevel std_logging_log_level = std_logging_LogLevel_Warn;
char *std_logging_log_time_format = "%H:%M:%S";
SDL_Window *std_og_state_window = NULL;
SDL_Renderer *std_og_state_renderer = NULL;
u32 std_og_state_prev_time = 0;
f32 std_og_state_frame_time = 0.000000f;
bool std_og_state_running = true;
std_vec_Vec2__3 std_og_state_window_size = {0};
char *std_og_state_title = "Window";
std_og_state_KeyState std_og_state_prev_keys = {0};
std_og_state_KeyState std_og_state_keys = {0};
std_og_state_MouseState std_og_state_prev_mouse = {0};
std_og_state_MouseState std_og_state_mouse = {0};
f32 std_og_state_frametimes[std_og_state_FRAMETIMES_COUNT] = {0};
u32 std_og_state_frametime_index;
f32 std_og_state_frametime_total = 0.000000f;
char std_og_state_window_title_fps_buf[256] = {0};
u64 std_og_state_frame_num = ((u64)0);
std_og_Texture std_og_state_buffer = (std_og_Texture){.tx=NULL, .w=0, .h=0, .pixels=NULL, .pitch=0};
std_vec_Vec2__1 size_f = {0};
std_image_Image *image;
src_zbuffer_ZBuffer *zbuffer;
std_vec_Vec3__0 light_dir = {0};
std_vec_Vec2__1 aspect_ratio = {0};
bool backface_culling;
std_matrix_Matrix4f camera_transform = {0};
std_vec_Vec3__0 camera_pos = {0};
std_vec_Vec3__0 camera_dir = {0};
std_vec_Vec3__0 camera_up = {0};
f32 focal_length = 1.000000f;
f32 MIN_CLIP = 0.200000f;
src_bvh_BVH__0 *bvh = NULL;
std_vector_Vector__2 *hit_nodes = NULL;
src_ray_Ray ray = {0};
bool show_mesh = true;
bool show_ray_and_hit = false;
u32 depth_limit = 0;
/* function implementations */
void std_panic(char *msg) {
  dump_backtrace();
  fprintf(stderr, "--------------------------------------------------------------------------------""\n");
  fprintf(stderr, "%s""\n", msg);
  oc_trap();
  exit(1);
}

bool str_eq(char *this, char *other) {
  void *a = ((void *)this);
  void *b = ((void *)other);
  if (a==b) {
    return true;
  }
  if (!((((bool)a) && ((bool)b)))) {
    return false;
  }
  return strcmp(this, other)==0;
}

char *std_format(char *fmt, ...) {
  va_list args = {0};
  va_start(args, fmt);
  u32 size = vsnprintf(NULL, 0, fmt, args);
  va_end(args);
  va_start(args, fmt);
  char *s = std_mem_alloc__0(((u32)(size + 1)));
  vsnprintf(s, (size + 1), fmt, args);
  s[size]='\0';
  va_end(args);
  return s;
}

bool char_is_space(char this) {
  return isspace(this);}

i32 i32_min(i32 this, i32 b) {
  return ((this < b) ? this : b);}

i32 i32_max(i32 this, i32 b) {
  return ((this > b) ? this : b);}

u32 u32_max(u32 this, u32 other) {
  return ((this > other) ? this : other);}

char *std_mem_alloc__0(u32 count) {
  return ((char *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(char)))));
}

i32 *std_mem_alloc__1(u32 count) {
  return ((i32 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(i32)))));
}

std_image_Image *std_mem_alloc__2(u32 count) {
  return ((std_image_Image *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_image_Image)))));
}

std_image_Color *std_mem_alloc__3(u32 count) {
  return ((std_image_Color *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_image_Color)))));
}

std_argparse_Arg *std_mem_alloc__4(u32 count) {
  return ((std_argparse_Arg *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_argparse_Arg)))));
}

u8 *std_mem_alloc__5(u32 count) {
  return ((u8 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(u8)))));
}

std_vector_Vector__0 *std_mem_alloc__6(u32 count) {
  return ((std_vector_Vector__0 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__0)))));
}

std_sv_SV *std_mem_alloc__7(u32 count) {
  return ((std_sv_SV *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_sv_SV)))));
}

std_vector_Vector__1 *std_mem_alloc__8(u32 count) {
  return ((std_vector_Vector__1 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__1)))));
}

std_argparse_Arg **std_mem_alloc__9(u32 count) {
  return ((std_argparse_Arg **)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_argparse_Arg *)))));
}

std_vector_Vector__2 *std_mem_alloc__10(u32 count) {
  return ((std_vector_Vector__2 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__2)))));
}

src_bvh_BVH__0 **std_mem_alloc__11(u32 count) {
  return ((src_bvh_BVH__0 **)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(src_bvh_BVH__0 *)))));
}

std_vector_Vector__3 *std_mem_alloc__12(u32 count) {
  return ((std_vector_Vector__3 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__3)))));
}

Triangle *std_mem_alloc__13(u32 count) {
  return ((Triangle *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(Triangle)))));
}

f32 *std_mem_alloc__14(u32 count) {
  return ((f32 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(f32)))));
}

std_compact_map_Map__0 *std_mem_alloc__15(u32 count) {
  return ((std_compact_map_Map__0 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_compact_map_Map__0)))));
}

std_vector_Vector__6 *std_mem_alloc__16(u32 count) {
  return ((std_vector_Vector__6 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__6)))));
}

std_compact_map_Item__0 *std_mem_alloc__17(u32 count) {
  return ((std_compact_map_Item__0 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_compact_map_Item__0)))));
}

std_vector_Vector__5 *std_mem_alloc__18(u32 count) {
  return ((std_vector_Vector__5 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__5)))));
}

std_vec_Vec2__1 *std_mem_alloc__19(u32 count) {
  return ((std_vec_Vec2__1 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vec_Vec2__1)))));
}

std_vector_Vector__4 *std_mem_alloc__20(u32 count) {
  return ((std_vector_Vector__4 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__4)))));
}

std_vec_Vec3__0 *std_mem_alloc__21(u32 count) {
  return ((std_vec_Vec3__0 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vec_Vec3__0)))));
}

void std_mem_free(void *ptr) {
  if (std_mem_state_free_fn != NULL) {
    std_mem_state_free_fn(std_mem_state_allocator, ptr);
    return;
  }
}

std_sv_SV *std_mem_realloc__1(std_sv_SV *ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(std_sv_SV)));
  u32 new_size = (new_count * ((u32)sizeof(std_sv_SV)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  std_sv_SV *new_ptr = std_mem_alloc__7(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

std_argparse_Arg **std_mem_realloc__2(std_argparse_Arg **ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(std_argparse_Arg *)));
  u32 new_size = (new_count * ((u32)sizeof(std_argparse_Arg *)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  std_argparse_Arg **new_ptr = std_mem_alloc__9(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

src_bvh_BVH__0 **std_mem_realloc__3(src_bvh_BVH__0 **ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(src_bvh_BVH__0 *)));
  u32 new_size = (new_count * ((u32)sizeof(src_bvh_BVH__0 *)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  src_bvh_BVH__0 **new_ptr = std_mem_alloc__11(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

Triangle *std_mem_realloc__4(Triangle *ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(Triangle)));
  u32 new_size = (new_count * ((u32)sizeof(Triangle)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  Triangle *new_ptr = std_mem_alloc__13(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

std_compact_map_Item__0 *std_mem_realloc__5(std_compact_map_Item__0 *ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(std_compact_map_Item__0)));
  u32 new_size = (new_count * ((u32)sizeof(std_compact_map_Item__0)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  std_compact_map_Item__0 *new_ptr = std_mem_alloc__17(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

std_vec_Vec2__1 *std_mem_realloc__6(std_vec_Vec2__1 *ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(std_vec_Vec2__1)));
  u32 new_size = (new_count * ((u32)sizeof(std_vec_Vec2__1)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  std_vec_Vec2__1 *new_ptr = std_mem_alloc__19(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

std_vec_Vec3__0 *std_mem_realloc__7(std_vec_Vec3__0 *ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(std_vec_Vec3__0)));
  u32 new_size = (new_count * ((u32)sizeof(std_vec_Vec3__0)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  std_vec_Vec3__0 *new_ptr = std_mem_alloc__21(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

void *std_mem_impl_my_calloc(void *state, u32 size) {
  return calloc(size, 1);}

void *std_mem_impl_my_realloc(void *state, void *ptr, u32 old_size, u32 size) {
  return realloc(ptr, size);}

void std_mem_impl_my_free(void *state, void *ptr) {
    free(ptr);
}

bool std_sv_SV_is_empty(std_sv_SV *this) {
  return this->len==0;}

std_sv_SV std_sv_SV_from_str(char *s) {
  return (std_sv_SV){.data=s, .len=strlen(s)};}

std_sv_SV std_sv_SV_get(std_sv_SV this, u32 n) {
  return (std_sv_SV){.data=this.data, .len=n};}

char std_sv_SV_at(std_sv_SV this, u32 n) {
  if(!(n < this.len)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/sv.oc:30:12: Assertion failed: `n < .len`", "Index out of bounds in SV::at"); }
  return this.data[n];
}

std_sv_SV std_sv_SV_chop_left(std_sv_SV *this, u32 n) {
  std_sv_SV res = std_sv_SV_get((*this), n);
  this->data=(this->data + n);
  this->len-=n;
  return res;
}

void std_sv_SV_trim_left(std_sv_SV *this) {
  while ((this->len > 0) && char_is_space(this->data[0])) {
    this->data=(this->data + 1);
    this->len-=1;
  }
}

void std_sv_SV_trim_right(std_sv_SV *this) {
  while ((this->len > 0) && char_is_space(this->data[(this->len - 1)])) {
    this->len-=1;
  }
}

void std_sv_SV_trim(std_sv_SV *this) {
  std_sv_SV_trim_left(this);
  std_sv_SV_trim_right(this);
}

std_sv_SV std_sv_SV_chop_by_delim(std_sv_SV *this, char delim) {
  u32 i = 0;
  while ((i < this->len) && (this->data[i] != delim)) {
    i+=1;
  }
  std_sv_SV res = std_sv_SV_get((*this), i);
  if (i==this->len) {
    this->data=(this->data + i);
    this->len-=i;
  } else {
    this->data=((this->data + i) + 1);
    this->len-=(i + 1);
  }
  return res;
}

std_sv_SV std_sv_SV_chop_by_sv(std_sv_SV *this, std_sv_SV delim) {
  for (u32 i = 0; i < ((this->len - delim.len) + 1); i++) {
    if (memcmp((this->data + i), delim.data, delim.len)==0) {
      std_sv_SV res = std_sv_SV_get((*this), i);
      this->data=((this->data + i) + delim.len);
      this->len-=(i + delim.len);
      return res;
    }
  }
  std_sv_SV res = std_sv_SV_get((*this), this->len);
  this->data=(this->data + this->len);
  this->len=0;
  return res;
}

std_sv_SV std_sv_SV_chop_word(std_sv_SV *this) {
  std_sv_SV_trim_left(this);
  u32 i = 0;
  while ((i < this->len) && !(char_is_space(this->data[i]))) {
    i+=1;
  }
  std_sv_SV res = std_sv_SV_get((*this), i);
  if (i==this->len) {
    this->data=(this->data + i);
    this->len-=i;
  } else {
    this->data=((this->data + i) + 1);
    this->len-=(i + 1);
  }
  std_sv_SV_trim_left(this);
  return res;
}

u64 std_sv_SV_chop_unsigned(std_sv_SV *this, char *fn_name) {
  char *endptr = "";
  u64 res = strtoul(this->data, &endptr, 10);
  if(!(endptr != this->data)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/sv.oc:140:12: Assertion failed: `endptr != .data`", std_format("Failed to parse number in %s", fn_name)); }
  std_sv_SV_only_chop_left(this, ((u32)(endptr - this->data)));
  return res;
}

u32 std_sv_SV_chop_u32(std_sv_SV *this) {
  return ((u32)std_sv_SV_chop_unsigned(this, "SV::chop_u32"));}

f32 std_sv_SV_chop_f32(std_sv_SV *this) {
  char *endptr = "";
  f64 res = strtod(this->data, &endptr);
  if(!(endptr != this->data)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/sv.oc:163:12: Assertion failed: `endptr != .data`", "Failed to parse number in SV::chop_f32"); }
  std_sv_SV_only_chop_left(this, ((u32)(endptr - this->data)));
  return ((f32)res);
}

i64 std_sv_SV_chop_signed(std_sv_SV *this, char *fn_name) {
  char *endptr = "";
  i64 res = strtoll(this->data, &endptr, 10);
  if(!(endptr != this->data)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/sv.oc:172:12: Assertion failed: `endptr != .data`", std_format("Failed to parse number in %s", fn_name)); }
  std_sv_SV_only_chop_left(this, ((u32)(endptr - this->data)));
  return res;
}

i64 std_sv_SV_chop_i64(std_sv_SV *this) {
  return ((i64)std_sv_SV_chop_signed(this, "SV::chop_i64"));}

std_sv_SV std_sv_SV_chop_line(std_sv_SV *this) {
  return std_sv_SV_chop_by_delim(this, '\n');}

bool std_sv_SV_eq(std_sv_SV this, std_sv_SV other) {
  return (this.len==other.len && memcmp(this.data, other.data, this.len)==0);}

bool std_sv_SV_eq_str(std_sv_SV this, char *other) {
  return std_sv_SV_eq(this, std_sv_SV_from_str(other));}

void std_sv_SV_only_chop_left(std_sv_SV *this, u32 n) {
  this->data=(this->data + n);
  this->len-=n;
}

bool std_sv_SV_starts_with_sv(std_sv_SV this, std_sv_SV other) {
  if (this.len < other.len) {
    return false;
  }
  for (u32 i = 0; i < other.len; i+=1) {
    if (this.data[i] != other.data[i]) {
      return false;
    }
  }
  return true;
}

bool std_sv_SV_starts_with_str(std_sv_SV this, char *other) {
  return std_sv_SV_starts_with_sv(this, std_sv_SV_from_str(other));}

std_sv_SVLineIterator std_sv_SV_lines(std_sv_SV this) {
  return (std_sv_SVLineIterator){.sv=this};}

std_sv_SVSplitIterator std_sv_SV_split_str(std_sv_SV this, char *delim) {
  return (std_sv_SVSplitIterator){.sv=this, .delim=std_sv_SV_from_str(delim)};}

bool std_sv_SVLineIterator_has_value(std_sv_SVLineIterator *this) {
  return !(std_sv_SV_is_empty(&this->sv));}

std_sv_SV std_sv_SVLineIterator_cur(std_sv_SVLineIterator *this) {
  return std_sv_SV_chop_line(&this->sv);}

void std_sv_SVLineIterator_next(std_sv_SVLineIterator *this) {
}

bool std_sv_SVSplitIterator_has_value(std_sv_SVSplitIterator *this) {
  return !(std_sv_SV_is_empty(&this->sv));}

std_sv_SV std_sv_SVSplitIterator_cur(std_sv_SVSplitIterator *this) {
  return std_sv_SV_chop_by_sv(&this->sv, this->delim);}

void std_sv_SVSplitIterator_next(std_sv_SVSplitIterator *this) {
}

std_compact_map_Iterator__0 std_compact_map_Map__0_iter(std_compact_map_Map__0 *this) {
  return (std_compact_map_Iterator__0){.iter=std_vector_Vector__6_iter(this->items)};}

std_compact_map_Item__0 std_compact_map_Iterator__0_cur(std_compact_map_Iterator__0 *this) {
  return std_vector_Iterator__6_cur(&this->iter);}

void std_compact_map_Iterator__0_next(std_compact_map_Iterator__0 *this) {
  std_vector_Iterator__6_next(&this->iter);
}

bool std_compact_map_Iterator__0_has_value(std_compact_map_Iterator__0 *this) {
  return std_vector_Iterator__6_has_value(&this->iter);}

void std_compact_map_Map__0_insert(std_compact_map_Map__0 *this, SDL_Scancode key, _ClosureTy_18 value) {
  u32 hash = std_sdl_Key_hash(key);
  u32 index = std_compact_map_Map__0_get_index(this, key, hash);
  if (this->indices[index] < 0) {
    this->indices[index]=((i32)this->items->size);
    std_vector_Vector__6_push(this->items, (std_compact_map_Item__0){.hash=hash, .key=key, .value=value});
    std_compact_map_Map__0_resize_if_necessary(this);
  } else {
    if (this->indices[index]==std_compact_map_INDEX_DELETED) {
      this->num_tombstones-=1;
    }
    u32 item_index = ((u32)this->indices[index]);
    this->items->data[item_index].value=value;
  }
}

u32 std_compact_map_Map__0_get_index(std_compact_map_Map__0 *this, SDL_Scancode key, u32 hash) {
  u32 perturb = hash;
  u32 j = (hash % this->capacity);
  u32 i = j;
  i32 first_deleted = -1;
  while (this->indices[i] != std_compact_map_INDEX_FREE) {
    if (this->indices[i]==std_compact_map_INDEX_DELETED) {
      if (first_deleted < 0) {
        first_deleted=((i32)i);
      }
    } else {
      std_compact_map_Item__0 item = this->items->data[this->indices[i]];
      if (item.hash==hash && std_sdl_Key_eq(item.key, key)) {
        return i;
      }
    }
    j=(((5 * j) + perturb) + 1);
    i=(j % this->capacity);
    perturb=(perturb >> 5);
  }
  if (first_deleted < 0) {
    return i;
  }
  return ((u32)first_deleted);
}

void std_compact_map_Map__0_resize(std_compact_map_Map__0 *this, u32 new_capacity) {
  i32 *old_indices = this->indices;
  this->indices=std_mem_alloc__1(new_capacity);
  this->capacity=new_capacity;
  for (u32 i = 0; i < new_capacity; i++) {
    this->indices[i]=std_compact_map_INDEX_FREE;
  }
  for (u32 i = 0; i < this->items->size; i++) {
    std_compact_map_Item__0 item = std_vector_Vector__6_at(this->items, i);
    u32 index = std_compact_map_Map__0_get_index(this, item.key, item.hash);
    if (this->indices[index]==std_compact_map_INDEX_FREE) {
      this->indices[index]=((i32)i);
    }
  }
  this->num_tombstones=0;
  std_mem_free(old_indices);
}

std_compact_map_Map__0 *std_compact_map_Map__0_new(u32 capacity) {
  std_vector_Vector__6 *items = std_vector_Vector__6_new(capacity);
  i32 *indices = std_mem_alloc__1(capacity);
  for (u32 i = 0; i < capacity; i++) {
    indices[i]=std_compact_map_INDEX_FREE;
  }
  std_compact_map_Map__0 *map = std_mem_alloc__15(1);
  map->items=items;
  map->indices=indices;
  map->capacity=capacity;
  map->num_tombstones=0;
  return map;
}

void std_compact_map_Map__0_resize_if_necessary(std_compact_map_Map__0 *this) {
  if ((this->num_tombstones + ((u32)this->items->size)) >= ((this->capacity * 3) / 4)) {
    std_compact_map_Map__0_resize(this, (this->capacity * 2));
  }
}

char *std_libc_errno_get_err(void) {
  return ((char *)strerror(errno));}

std_image_Image *std_image_Image_new(u32 width, u32 height) {
  std_image_Image *img = std_mem_alloc__2(1);
  (*img)=(std_image_Image){.width=width, .height=height, .data=std_mem_alloc__3((width * height))};
  return img;
}

std_image_Color std_image_Image_get(std_image_Image *this, u32 x, u32 y) {
  return this->data[((y * this->width) + x)];}

void std_image_Image_set(std_image_Image *this, u32 x, u32 y, std_image_Color col) {
  this->data[((y * this->width) + x)]=col;
}

void std_image_Image_clear(std_image_Image *this) {
  memset(this->data, ((u8)0), ((this->width * this->height) * ((u32)sizeof(std_image_Color))));
}

void std_argparse_Arg_save_val(std_argparse_Arg *this, char *s) {
  std_sv_SV sv = std_sv_SV_from_str(s);
switch ((this->type)) {
    case std_argparse_ArgType_String:
    m_21_0:
      {
        this->val.as_str=s;
      } break;
    case std_argparse_ArgType_Int:
    m_21_1:
      {
        this->val.as_int=std_sv_SV_chop_i64(&sv);
      } break;
    case std_argparse_ArgType_Bool:
    m_21_2:
      {
        this->val.as_bool=({bool __yv_22;
          {
            char *__match_var_23 = s;
            if (str_eq(__match_var_23, "true") || str_eq(__match_var_23, "1")) {
              __yv_22 = true;
              goto _l___yv_22;
            } else if (str_eq(__match_var_23, "false") || str_eq(__match_var_23, "0")) {
              __yv_22 = false;
              goto _l___yv_22;
            } else  {
              std_sv_SV flag = std_vector_Vector__0_at(this->flags, 0);
              std_panic(std_format("Invalid boolean value: %s for arg %.*s", s, (flag).len, (flag).data));
            }
          }

_l___yv_22:
        __yv_22;});
      } break;
    case std_argparse_ArgType_Float:
    m_21_3:
      {
        this->val.as_float=((f64)std_sv_SV_chop_f32(&sv));
      } break;
  }}

std_argparse_Parser std_argparse_Parser_make(char *description) {
  return (std_argparse_Parser){.description=description, .args=({
    std_vector_Vector__1 *_vc24 = std_vector_Vector__1_new(8);
    _vc24;}), .program_name=""};}

std_argparse_Arg *std_argparse_Parser__add(std_argparse_Parser *this, char *flags, bool required, char *help) {
  std_argparse_Arg *arg = std_mem_alloc__4(1);
  arg->flags=({
    std_vector_Vector__0 *_vc25 = std_vector_Vector__0_new(8);
    _vc25;});
  for (std_sv_SVSplitIterator _i6 = std_sv_SV_split_str(std_sv_SV_from_str(flags), "/"); std_sv_SVSplitIterator_has_value(&_i6); std_sv_SVSplitIterator_next(&_i6)) {
    std_sv_SV flag = std_sv_SVSplitIterator_cur(&_i6);
    {
      if (flag.len > 0) {
        std_vector_Vector__0_push(arg->flags, flag);
      } else {
        std_panic("Flag names must not be empty");
      }
    }
  }
  arg->flags_display=flags;
  arg->required=required;
  arg->help=help;
  if(!(arg->flags->size > 0)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/argparse.oc:82:12: Assertion failed: `arg.flags.size > 0`", "Flag names must not be empty"); }
  arg->is_positional=(arg->flags->size==1 && !(std_sv_SV_starts_with_str(std_vector_Vector__0_at(arg->flags, 0), "-")));
  if (arg->is_positional) {
    arg->required=true;
  }
  std_vector_Vector__1_push(this->args, arg);
  return arg;
}

char **std_argparse_Parser_add_str(std_argparse_Parser *this, char *flags, char *defolt, bool required, char *help) {
  std_argparse_Arg *arg = std_argparse_Parser__add(this, flags, required, help);
  arg->type=std_argparse_ArgType_String;
  arg->defolt.as_str=defolt;
  arg->val.as_str=defolt;
  return &arg->val.as_str;
}

bool *std_argparse_Parser_add_bool(std_argparse_Parser *this, char *flags, std_argparse_BoolAction action, char *help) {
  std_argparse_Arg *arg = std_argparse_Parser__add(this, flags, false, help);
  arg->type=std_argparse_ArgType_Bool;
  arg->defolt.as_bool=({bool __yv_26;
switch ((action)) {
      case std_argparse_BoolAction_StoreTrue:
      m_27_0:
        {
          __yv_26 = false;
          goto _l___yv_26;
        } break;
      case std_argparse_BoolAction_StoreFalse:
      m_27_1:
        {
          __yv_26 = true;
          goto _l___yv_26;
        } break;
    }
_l___yv_26:
  __yv_26;});
  arg->val.as_bool=arg->defolt.as_bool;
  return &arg->val.as_bool;
}

std_argparse_Arg *std_argparse_find_arg(std_argparse_Parser *parser, char *_flag, i32 *positional_idx) {
  std_sv_SV flag = std_sv_SV_from_str(_flag);
  i32 cur_positional_idx = 0;
  for (std_vector_Iterator__1 _i7 = std_vector_Vector__1_iter(parser->args); std_vector_Iterator__1_has_value(&_i7); std_vector_Iterator__1_next(&_i7)) {
    std_argparse_Arg *arg = std_vector_Iterator__1_cur(&_i7);
    {
      if (arg->is_positional) {
        if (!(std_sv_SV_starts_with_str(flag, "-"))) {
          if (cur_positional_idx==(*positional_idx)) {
            (*positional_idx)+=1;
            return arg;
          }
          cur_positional_idx+=1;
        }
      } else {
        for (std_vector_Iterator__0 _i8 = std_vector_Vector__0_iter(arg->flags); std_vector_Iterator__0_has_value(&_i8); std_vector_Iterator__0_next(&_i8)) {
          std_sv_SV f = std_vector_Iterator__0_cur(&_i8);
          {
            if (std_sv_SV_starts_with_str(flag, "-")) {
              if (std_sv_SV_eq(f, flag)) {
                return arg;
              }
              if (std_sv_SV_starts_with_sv(flag, f) && std_sv_SV_at(flag, f.len)=='=') {
                return arg;
              }
            }
          }
        }
      }
    }
  }
  return NULL;
}

void std_argparse_Parser_usage_and_exit(std_argparse_Parser *this, i32 code) {
  bool has_options = false;
  printf("Usage: %s ", this->program_name);
  char *help_flags = "-h/--help";
  u32 max_len = strlen(help_flags);
  for (std_vector_Iterator__1 _i9 = std_vector_Vector__1_iter(this->args); std_vector_Iterator__1_has_value(&_i9); std_vector_Iterator__1_next(&_i9)) {
    std_argparse_Arg *arg = std_vector_Iterator__1_cur(&_i9);
    {
      max_len=u32_max(max_len, strlen(arg->flags_display));
      if (!(arg->is_positional)) {
        has_options=true;
      } else {
        std_sv_SV name = std_vector_Vector__0_at(arg->flags, 0);
        printf("<%.*s> ", (name).len, (name).data);
      }
    }
  }
  if (has_options) {
    printf("[options]\n");
  } else {
    printf("\n");
  }
  max_len+=2;
  printf("\n%s\n\n", this->description);
  printf("Arguments:\n");
  _ClosureTy_9 print_arg = ({std_argparse_usage_and_exit__Closure_21Ctx *_C28 = alloca(sizeof(std_argparse_usage_and_exit__Closure_21Ctx));_C28->max_len = &max_len;_ClosureTy_9 _ci29 = {._C=_C28, .fn=&std_argparse_usage_and_exit__Closure_21};_ci29;});
  for (std_vector_Iterator__1 _i10 = std_vector_Vector__1_iter(this->args); std_vector_Iterator__1_has_value(&_i10); std_vector_Iterator__1_next(&_i10)) {
    std_argparse_Arg *arg = std_vector_Iterator__1_cur(&_i10);
    {
      if (arg->is_positional) {
        print_arg.fn(print_arg._C, arg);
      }
    }
  }
  for (std_vector_Iterator__1 _i11 = std_vector_Vector__1_iter(this->args); std_vector_Iterator__1_has_value(&_i11); std_vector_Iterator__1_next(&_i11)) {
    std_argparse_Arg *arg = std_vector_Iterator__1_cur(&_i11);
    {
      if (!(arg->is_positional)) {
        print_arg.fn(print_arg._C, arg);
      }
    }
  }
  printf("    %s%*s  %s%s""\n", help_flags, ((i32)(max_len - strlen(help_flags))), "", "Show this help message and exit", " (Bool)");
  printf("""\n");
  exit(code);
}

void std_argparse_Parser_parse(std_argparse_Parser *this, i32 argc, char **argv, bool consume_first) {
  i32 positional_idx = 0;
  i32 i = 0;
  if (consume_first) {
    this->program_name=argv[0];
    i=1;
  }
  while (i < argc) {
    char *cur = argv[i];
    if (str_eq(cur, "-h") || str_eq(cur, "--help")) {
      std_argparse_Parser_usage_and_exit(this, 0);
    }
    std_argparse_Arg *arg = std_argparse_find_arg(this, cur, &positional_idx);
    if (((bool)arg)) {
      if (arg->is_positional) {
        std_argparse_Arg_save_val(arg, cur);
        arg->parsed=true;
        i+=1;
        continue;
      }
      if (arg->parsed) {
        printf("Argument %s is already parsed\n", cur);
        std_argparse_Parser_usage_and_exit(this, 1);
      }
      if (i >= (argc - 1)) {
        printf("Argument %s requires a value, but none was provided\n", cur);
        std_argparse_Parser_usage_and_exit(this, 1);
      }
      i+=1;
      char *next = argv[i];
      std_argparse_Arg_save_val(arg, next);
      arg->parsed=true;
      i+=1;
    } else {
      printf("Unknown argument: %s\n", cur);
      std_argparse_Parser_usage_and_exit(this, 1);
    }
  }
  for (std_vector_Iterator__1 _i12 = std_vector_Vector__1_iter(this->args); std_vector_Iterator__1_has_value(&_i12); std_vector_Iterator__1_next(&_i12)) {
    std_argparse_Arg *arg = std_vector_Iterator__1_cur(&_i12);
    {
      if (arg->required && !(arg->parsed)) {
        std_sv_SV flag = std_vector_Vector__0_at(arg->flags, 0);
        if (arg->is_positional) {
          printf("Missing required positional argument: %.*s\n", (flag).len, (flag).data);
        } else {
          printf("Missing required argument: %.*s\n", (flag).len, (flag).data);
        }
        std_argparse_Parser_usage_and_exit(this, 1);
      }
    }
  }
}

std_buffer_Buffer std_buffer_Buffer_make(u32 capacity) {
  return (std_buffer_Buffer){.data=std_mem_alloc__5(capacity), .size=0, .capacity=capacity};
}

std_sv_SV std_buffer_Buffer_sv(std_buffer_Buffer this) {
  return (std_sv_SV){.data=((char *)this.data), .len=this.size};}

void std_buffer_Buffer_free(std_buffer_Buffer *this) {
  std_mem_free(this->data);
}

void std_logging_vlog(std_logging_LogLevel level, char *fmt, va_list vargs) {
  if (((u32)level) < ((u32)std_logging_log_level)) {
    return;
  }
  if (((bool)std_logging_log_time_format)) {
    char time_buf[64] = {0};
    time_t timer = time(NULL);
    struct tm *tm_info = localtime(&timer);
    strftime(time_buf, 64, std_logging_log_time_format, tm_info);
    printf("(%s) ", time_buf);
  }
switch ((level)) {
    case std_logging_LogLevel_Debug:
    m_30_0:
      {
        printf("[DEBUG] ");
      } break;
    case std_logging_LogLevel_Info:
    m_30_1:
      {
        printf("[INFO] ");
      } break;
    case std_logging_LogLevel_Warn:
    m_30_2:
      {
        printf("[WARN] ");
      } break;
    case std_logging_LogLevel_Error:
    m_30_3:
      {
        printf("[ERROR] ");
      } break;
  }  vprintf(fmt, vargs);
  printf("\n");
}

void std_logging_log(std_logging_LogLevel level, char *fmt, ...) {
  va_list args = {0};
  va_start(args, fmt);
  std_logging_vlog(level, fmt, args);
  va_end(args);
}

i8 f32_compare(f32 this, f32 b) {
  return (((i8)(this > b)) - ((i8)(this < b)));}

u32 u32_hash(u32 this) {
  return (((u32)this) * 7817);}

u32 std_og_get_ticks(void) {
  return ((u32)SDL_GetTicks());}

void std_og_init(u32 width, u32 height, char *title, bool fullscreen) {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(((i32)width), ((i32)height), SDL_WINDOW_RESIZABLE, &std_og_state_window, &std_og_state_renderer);
  if (fullscreen) {
    SDL_SetWindowFullscreen(std_og_state_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  }
  std_og_state_title=title;
  SDL_SetWindowTitle(std_og_state_window, title);
  std_og_state_prev_time=std_og_get_ticks();
  std_og_state_update_window_size();
}

void std_og_toggle_fullscreen(void) {
  i32 flags = SDL_GetWindowFlags(std_og_state_window);
  if ((flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) {
    SDL_SetWindowFullscreen(std_og_state_window, 0);
  } else {
    SDL_SetWindowFullscreen(std_og_state_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  }
}

bool std_og_is_running(void) {
  SDL_RenderPresent(std_og_state_renderer);
  std_og_state_frame_num+=((u64)1);
  u32 cur_time = ((u32)std_og_get_ticks());
  std_og_state_frame_time=(((f32)(cur_time - std_og_state_prev_time)) / 1000.000000f);
  std_og_state_prev_time=cur_time;
  std_og_state_update_window_size();
  std_og_state_add_frametime(std_og_state_frame_time);
  if ((std_og_state_frame_num % ((u64)30))==((u64)0)) {
    f32 avg = std_og_state_get_avg_frametime();
    sprintf(std_og_state_window_title_fps_buf, "%s | FPS: %.0f", std_og_state_title, (1.000000f / avg));
    SDL_SetWindowTitle(std_og_state_window, std_og_state_window_title_fps_buf);
  }
  std_og_utils_handle_sdl_events();
  return std_og_state_running;
}

void std_og_quit(void) {
  SDL_Quit();
}

bool std_og_is_key_pressed(SDL_Scancode k) {
  return (std_og_state_KeyState_get(&std_og_state_prev_keys, k)==false && std_og_state_KeyState_get(&std_og_state_keys, k)==true);}

bool std_og_is_key_down(SDL_Scancode k) {
  return std_og_state_KeyState_get(&std_og_state_keys, k)==true;}

std_vec_Vec2__3 std_og_get_mouse_delta(void) {
  return std_og_state_mouse.vec;}

void std_og_grab_input(bool grab) {
    SDL_SetRelativeMouseMode(grab);
}

void std_og_show_cursor(bool show) {
    SDL_ShowCursor(show);
}

std_og_Texture *std_og_get_buffer_sized(i32 w, i32 h) {
  bool matches = true;
  if ((std_og_state_buffer.w != w) || (std_og_state_buffer.h != h)) {
    SDL_DestroyTexture(std_og_state_buffer.tx);
    matches=false;
  }
  if (!(matches)) {
    std_og_Texture buf = {0};
    buf.tx=SDL_CreateTexture(std_og_state_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    buf.w=w;
    buf.h=h;
    std_og_state_buffer=buf;
  }
  SDL_LockTexture(std_og_state_buffer.tx, NULL, ((void **)&std_og_state_buffer.pixels), &std_og_state_buffer.pitch);
  return &std_og_state_buffer;
}

void std_og_draw_buffer(void) {
  SDL_UnlockTexture(std_og_state_buffer.tx);
  SDL_RenderCopy(std_og_state_renderer, std_og_state_buffer.tx, NULL, NULL);
}

void std_og_display_image(std_image_Image *img) {
  std_og_Texture *tx = std_og_get_buffer_sized(((i32)img->width), ((i32)img->height));
  std_sdl_Texture_write_image(tx->tx, img);
  std_og_draw_buffer();
}

bool std_og_state_KeyState_get(std_og_state_KeyState *this, SDL_Scancode k) {
  return this->keys[((u32)k)];}

void std_og_state_update_window_size(void) {
  SDL_GetWindowSize(std_og_state_window, &std_og_state_window_size.x, &std_og_state_window_size.y);
}

void std_og_state_add_frametime(f32 frametime) {
  std_og_state_frametime_total+=(frametime - std_og_state_frametimes[std_og_state_frametime_index]);
  std_og_state_frametimes[std_og_state_frametime_index]=frametime;
  std_og_state_frametime_index=((std_og_state_frametime_index + 1) % std_og_state_FRAMETIMES_COUNT);
}

f32 std_og_state_get_avg_frametime(void) {
  return (std_og_state_frametime_total / ((f32)std_og_state_FRAMETIMES_COUNT));}

void std_og_utils_handle_sdl_events(void) {
  std_og_state_prev_mouse=std_og_state_mouse;
  std_og_state_prev_keys=std_og_state_keys;
  std_og_state_mouse.scroll=(std_vec_Vec2__3){.x=0, .y=0};
  SDL_Event event = {0};
  while (SDL_PollEvent(&event)) {
switch ((event.type)) {
      case SDL_QUIT:
      m_31_0:
        {
          std_og_state_running=false;
        } break;
      case SDL_KEYDOWN:
      m_31_1:
        {
          SDL_Scancode k = event.key.keysym.scancode;
          if (((i32)k) < 1024) {
            std_og_state_keys.keys[((i32)k)]=true;
          }
        } break;
      case SDL_KEYUP:
      m_31_2:
        {
          SDL_Scancode k = event.key.keysym.scancode;
          if (((i32)k) < 1024) {
            std_og_state_keys.keys[((i32)k)]=false;
          }
        } break;
      case SDL_MOUSEBUTTONDOWN:
      m_31_3:
        {
          u8 b = event.button.button;
          std_og_state_mouse.buttons[((i32)b)]=true;
        } break;
      case SDL_MOUSEBUTTONUP:
      m_31_4:
        {
          u8 b = event.button.button;
          std_og_state_mouse.buttons[((i32)b)]=false;
        } break;
      case SDL_MOUSEWHEEL:
      m_31_5:
        {
          std_og_state_mouse.wheel_dirs[((i32)std_og_state_MouseWheel_Right)]=(event.wheel.x > 0);
          std_og_state_mouse.wheel_dirs[((i32)std_og_state_MouseWheel_Left)]=(event.wheel.x < 0);
          std_og_state_mouse.wheel_dirs[((i32)std_og_state_MouseWheel_Down)]=(event.wheel.y > 0);
          std_og_state_mouse.wheel_dirs[((i32)std_og_state_MouseWheel_Up)]=(event.wheel.y < 0);
          std_og_state_mouse.scroll=(std_vec_Vec2__3){.x=event.wheel.x, .y=event.wheel.y};
        } break;
      default:
        {
        } break;
    }  }
  SDL_GetMouseState(&std_og_state_mouse.pos.x, &std_og_state_mouse.pos.y);
  SDL_GetRelativeMouseState(&std_og_state_mouse.vec.x, &std_og_state_mouse.vec.y);
}

std_buffer_Buffer std_fs_read_file(char *path) {
  FILE *file = fopen(path, "r");
  if (!(((bool)file))) {
    std_panic(std_format("[-] Failed to open file: %s: %s", path, std_libc_errno_get_err()));
  }
  fseek(file, ((i64)0), SEEK_END);
  u32 size = ((u32)ftell(file));
  fseek(file, ((i64)0), SEEK_SET);
  std_buffer_Buffer data = std_buffer_Buffer_make((size + 1));
  i32 read = fread(data.data, 1, size, file);
  if (((u32)read) != size) {
    std_panic(std_format("[-] Failed to read from file: %s", path));
  }
  fclose(file);
  data.size=((u32)size);
  data.data[size]=((u8)0);
  return data;
}

f64 std_time_get_time_monotonic_ms(void) {
  struct timespec tv = {0};
  clock_gettime(CLOCK_MONOTONIC, &tv);
  return (((f64)tv.tv_sec) * 1000.000000) + (((f64)tv.tv_nsec) / 1000000.000000);
}

f32 f32_inf(void) {
  return ((f32)INFINITY);}

f32 f32_min(f32 this, f32 b) {
  return ((this < b) ? this : b);}

f32 f32_max(f32 this, f32 b) {
  return ((this > b) ? this : b);}

std_vec_Vec2__1 std_vec_Vec2__1_mult(std_vec_Vec2__1 this, std_vec_Vec2__1 other) {
  return (std_vec_Vec2__1){.x=(this.x * other.x), .y=(this.y * other.y)};}

std_vec_Vec2__3 std_vec_Vec2__1_to_i32(std_vec_Vec2__1 this) {
  return (std_vec_Vec2__3){.x=((i32)this.x), .y=((i32)this.y)};}

std_vec_Vec2__1 std_vec_Vec2__1_mults(std_vec_Vec2__1 this, f32 val) {
  return (std_vec_Vec2__1){.x=(this.x * val), .y=(this.y * val)};}

std_vec_Vec2__1 std_vec_Vec2__1_adds(std_vec_Vec2__1 this, f32 val) {
  return (std_vec_Vec2__1){.x=(this.x + val), .y=(this.y + val)};}

std_vec_Vec2__1 std_vec_Vec2__1_div(std_vec_Vec2__1 this, std_vec_Vec2__1 other) {
  return (std_vec_Vec2__1){.x=(this.x / other.x), .y=(this.y / other.y)};}

std_vec_Vec3__0 std_vec_Vec3__0_rotate_axis(std_vec_Vec3__0 this, std_vec_Vec3__0 axis, f32 angle) {
  f32 c = cosf(angle);
  f32 s = sinf(angle);
  f32 t = (1.000000f - c);
  axis=std_vec_Vec3__0_normalized(axis);
  std_vec_Vec3__0 f = std_vec_Vec3__0_to_f32(this);
  return (std_vec_Vec3__0){.x=(((f.x * (((t * axis.x) * axis.x) + c)) + (f.y * (((t * axis.x) * axis.y) - (s * axis.z)))) + (f.z * (((t * axis.x) * axis.z) + (s * axis.y)))), .y=(((f.x * (((t * axis.y) * axis.x) + (s * axis.z))) + (f.y * (((t * axis.y) * axis.y) + c))) + (f.z * (((t * axis.y) * axis.z) - (s * axis.x)))), .z=(((f.x * (((t * axis.z) * axis.x) - (s * axis.y))) + (f.y * (((t * axis.z) * axis.y) + (s * axis.x)))) + (f.z * (((t * axis.z) * axis.z) + c)))};
}

std_vec_Vec3__0 std_vec_Vec3__0_add(std_vec_Vec3__0 this, std_vec_Vec3__0 other) {
  return (std_vec_Vec3__0){.x=(this.x + other.x), .y=(this.y + other.y), .z=(this.z + other.z)};}

std_vec_Vec3__0 std_vec_Vec3__0_divs(std_vec_Vec3__0 this, f32 val) {
  return (std_vec_Vec3__0){.x=(this.x / val), .y=(this.y / val), .z=(this.z / val)};}

f32 std_vec_Vec3__0_length(std_vec_Vec3__0 this) {
  return sqrtf(((f32)(((this.x * this.x) + (this.y * this.y)) + (this.z * this.z))));}

std_vec_Vec3__0 std_vec_Vec3__0_sub(std_vec_Vec3__0 this, std_vec_Vec3__0 other) {
  return (std_vec_Vec3__0){.x=(this.x - other.x), .y=(this.y - other.y), .z=(this.z - other.z)};}

std_vec_Vec3__0 std_vec_Vec3__0_multrs(f32 val, std_vec_Vec3__0 this) {
  return (std_vec_Vec3__0){.x=(val * this.x), .y=(val * this.y), .z=(val * this.z)};}

std_vec_Vec3__0 std_vec_Vec3__0_normalized(std_vec_Vec3__0 this) {
  f32 len = std_vec_Vec3__0_length(this);
  return (std_vec_Vec3__0){.x=(((f32)this.x) / len), .y=(((f32)this.y) / len), .z=(((f32)this.z) / len)};
}

std_vec_Vec3__0 std_vec_Vec3__0_to_f32(std_vec_Vec3__0 this) {
  return (std_vec_Vec3__0){.x=((f32)this.x), .y=((f32)this.y), .z=((f32)this.z)};}

std_vec_Vec3__0 std_vec_Vec3__0_mults(std_vec_Vec3__0 this, f32 val) {
  return (std_vec_Vec3__0){.x=(this.x * val), .y=(this.y * val), .z=(this.z * val)};}

std_vec_Vec3__0 std_vec_Vec3__0_adds(std_vec_Vec3__0 this, f32 val) {
  return (std_vec_Vec3__0){.x=(this.x + val), .y=(this.y + val), .z=(this.z + val)};}

f32 std_vec_Vec3__0_dot(std_vec_Vec3__0 this, std_vec_Vec3__0 other) {
  return (((this.x * other.x) + (this.y * other.y)) + (this.z * other.z));}

std_vec_Vec3__0 std_vec_Vec3__0_cross(std_vec_Vec3__0 this, std_vec_Vec3__0 other) {
  return (std_vec_Vec3__0){.x=((this.y * other.z) - (this.z * other.y)), .y=((this.z * other.x) - (this.x * other.z)), .z=((this.x * other.y) - (this.y * other.x))};
}

f32 std_vec_Vec3__0_index(std_vec_Vec3__0 this, u32 idx) {
  return ((f32 *)&this)[idx];}

std_vec_Vec3__0 std_vec_Vec3__0_divrs(f32 val, std_vec_Vec3__0 this) {
  return (std_vec_Vec3__0){.x=(val / this.x), .y=(val / this.y), .z=(val / this.z)};}

std_vector_Iterator__0 std_vector_Vector__0_iter(std_vector_Vector__0 *this) {
  return std_vector_Iterator__0_make(this);}

std_sv_SV std_vector_Iterator__0_cur(std_vector_Iterator__0 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:168:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::current"); }
  return this->vec->data[this->index];
}

void std_vector_Iterator__0_next(std_vector_Iterator__0 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:163:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::next"); }
  this->index+=1;
}

bool std_vector_Iterator__0_has_value(std_vector_Iterator__0 *this) {
  return (this->index < this->vec->size);}

std_vector_Iterator__0 std_vector_Iterator__0_make(std_vector_Vector__0 *vec) {
  return (std_vector_Iterator__0){.vec=vec, .index=0};}

std_sv_SV std_vector_Vector__0_at(std_vector_Vector__0 *this, u32 i) {
  if(!(i < this->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:122:12: Assertion failed: `i < .size`", std_format("Out of bounds in Vector::at, %u >= %u", i, this->size)); }
  return this->data[i];
}

void std_vector_Vector__0_resize(std_vector_Vector__0 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__1(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__0 *std_vector_Vector__0_new(u32 capacity) {
  std_vector_Vector__0 *list = std_mem_alloc__6(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__7(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__0_push(std_vector_Vector__0 *this, std_sv_SV value) {
  if (this->size==this->capacity) {
    std_vector_Vector__0_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

std_vector_Iterator__1 std_vector_Vector__1_iter(std_vector_Vector__1 *this) {
  return std_vector_Iterator__1_make(this);}

std_argparse_Arg *std_vector_Iterator__1_cur(std_vector_Iterator__1 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:168:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::current"); }
  return this->vec->data[this->index];
}

void std_vector_Iterator__1_next(std_vector_Iterator__1 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:163:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::next"); }
  this->index+=1;
}

bool std_vector_Iterator__1_has_value(std_vector_Iterator__1 *this) {
  return (this->index < this->vec->size);}

std_vector_Iterator__1 std_vector_Iterator__1_make(std_vector_Vector__1 *vec) {
  return (std_vector_Iterator__1){.vec=vec, .index=0};}

void std_vector_Vector__1_resize(std_vector_Vector__1 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__2(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__1 *std_vector_Vector__1_new(u32 capacity) {
  std_vector_Vector__1 *list = std_mem_alloc__8(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__9(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__1_push(std_vector_Vector__1 *this, std_argparse_Arg *value) {
  if (this->size==this->capacity) {
    std_vector_Vector__1_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

void std_vector_Vector__2_zero_unused(std_vector_Vector__2 *this) {
  src_bvh_BVH__0 **start = (this->data + this->size);
  memset(start, ((u8)0), ((this->capacity - this->size) * ((u32)sizeof(src_bvh_BVH__0 *))));
}

std_vector_Iterator__2 std_vector_Vector__2_iter(std_vector_Vector__2 *this) {
  return std_vector_Iterator__2_make(this);}

src_bvh_BVH__0 *std_vector_Iterator__2_cur(std_vector_Iterator__2 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:168:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::current"); }
  return this->vec->data[this->index];
}

void std_vector_Iterator__2_next(std_vector_Iterator__2 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:163:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::next"); }
  this->index+=1;
}

bool std_vector_Iterator__2_has_value(std_vector_Iterator__2 *this) {
  return (this->index < this->vec->size);}

std_vector_Iterator__2 std_vector_Iterator__2_make(std_vector_Vector__2 *vec) {
  return (std_vector_Iterator__2){.vec=vec, .index=0};}

void std_vector_Vector__2_resize(std_vector_Vector__2 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__3(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__2 *std_vector_Vector__2_new(u32 capacity) {
  std_vector_Vector__2 *list = std_mem_alloc__10(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__11(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__2_push(std_vector_Vector__2 *this, src_bvh_BVH__0 *value) {
  if (this->size==this->capacity) {
    std_vector_Vector__2_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

void std_vector_Vector__2_clear(std_vector_Vector__2 *this) {
  this->size=0;
  std_vector_Vector__2_zero_unused(this);
}

std_vector_Iterator__3 std_vector_Vector__3_iter(std_vector_Vector__3 *this) {
  return std_vector_Iterator__3_make(this);}

Triangle std_vector_Iterator__3_cur(std_vector_Iterator__3 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:168:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::current"); }
  return this->vec->data[this->index];
}

void std_vector_Iterator__3_next(std_vector_Iterator__3 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:163:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::next"); }
  this->index+=1;
}

bool std_vector_Iterator__3_has_value(std_vector_Iterator__3 *this) {
  return (this->index < this->vec->size);}

std_vector_Iterator__3 std_vector_Iterator__3_make(std_vector_Vector__3 *vec) {
  return (std_vector_Iterator__3){.vec=vec, .index=0};}

Triangle std_vector_Vector__3_at(std_vector_Vector__3 *this, u32 i) {
  if(!(i < this->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:122:12: Assertion failed: `i < .size`", std_format("Out of bounds in Vector::at, %u >= %u", i, this->size)); }
  return this->data[i];
}

void std_vector_Vector__3_resize(std_vector_Vector__3 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__4(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__3 *std_vector_Vector__3_new(u32 capacity) {
  std_vector_Vector__3 *list = std_mem_alloc__12(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__13(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__3_push(std_vector_Vector__3 *this, Triangle value) {
  if (this->size==this->capacity) {
    std_vector_Vector__3_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

std_vec_Vec3__0 std_vector_Vector__4_at(std_vector_Vector__4 *this, u32 i) {
  if(!(i < this->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:122:12: Assertion failed: `i < .size`", std_format("Out of bounds in Vector::at, %u >= %u", i, this->size)); }
  return this->data[i];
}

void std_vector_Vector__4_free(std_vector_Vector__4 *this) {
  std_mem_free(this->data);
  std_mem_free(this);
}

void std_vector_Vector__4_resize(std_vector_Vector__4 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__7(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__4 *std_vector_Vector__4_new(u32 capacity) {
  std_vector_Vector__4 *list = std_mem_alloc__20(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__21(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__4_push(std_vector_Vector__4 *this, std_vec_Vec3__0 value) {
  if (this->size==this->capacity) {
    std_vector_Vector__4_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

std_vec_Vec2__1 std_vector_Vector__5_at(std_vector_Vector__5 *this, u32 i) {
  if(!(i < this->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:122:12: Assertion failed: `i < .size`", std_format("Out of bounds in Vector::at, %u >= %u", i, this->size)); }
  return this->data[i];
}

void std_vector_Vector__5_free(std_vector_Vector__5 *this) {
  std_mem_free(this->data);
  std_mem_free(this);
}

void std_vector_Vector__5_resize(std_vector_Vector__5 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__6(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__5 *std_vector_Vector__5_new(u32 capacity) {
  std_vector_Vector__5 *list = std_mem_alloc__18(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__19(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__5_push(std_vector_Vector__5 *this, std_vec_Vec2__1 value) {
  if (this->size==this->capacity) {
    std_vector_Vector__5_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

std_vector_Iterator__6 std_vector_Vector__6_iter(std_vector_Vector__6 *this) {
  return std_vector_Iterator__6_make(this);}

std_compact_map_Item__0 std_vector_Iterator__6_cur(std_vector_Iterator__6 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:168:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::current"); }
  return this->vec->data[this->index];
}

void std_vector_Iterator__6_next(std_vector_Iterator__6 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:163:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::next"); }
  this->index+=1;
}

bool std_vector_Iterator__6_has_value(std_vector_Iterator__6 *this) {
  return (this->index < this->vec->size);}

std_vector_Iterator__6 std_vector_Iterator__6_make(std_vector_Vector__6 *vec) {
  return (std_vector_Iterator__6){.vec=vec, .index=0};}

std_compact_map_Item__0 std_vector_Vector__6_at(std_vector_Vector__6 *this, u32 i) {
  if(!(i < this->size)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/vector.oc:122:12: Assertion failed: `i < .size`", std_format("Out of bounds in Vector::at, %u >= %u", i, this->size)); }
  return this->data[i];
}

void std_vector_Vector__6_resize(std_vector_Vector__6 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__5(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__6 *std_vector_Vector__6_new(u32 capacity) {
  std_vector_Vector__6 *list = std_mem_alloc__16(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__17(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__6_push(std_vector_Vector__6 *this, std_compact_map_Item__0 value) {
  if (this->size==this->capacity) {
    std_vector_Vector__6_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

std_matrix_Matrix4f std_matrix_Matrix4f_make(f32 d00, f32 d01, f32 d02, f32 d03, f32 d10, f32 d11, f32 d12, f32 d13, f32 d20, f32 d21, f32 d22, f32 d23, f32 d30, f32 d31, f32 d32, f32 d33) {
  std_matrix_Matrix4f m = {0};
  m.d[0][0]=d00;
  m.d[0][1]=d01;
  m.d[0][2]=d02;
  m.d[0][3]=d03;
  m.d[1][0]=d10;
  m.d[1][1]=d11;
  m.d[1][2]=d12;
  m.d[1][3]=d13;
  m.d[2][0]=d20;
  m.d[2][1]=d21;
  m.d[2][2]=d22;
  m.d[2][3]=d23;
  m.d[3][0]=d30;
  m.d[3][1]=d31;
  m.d[3][2]=d32;
  m.d[3][3]=d33;
  return m;
}

std_vec_Vec3__0 std_matrix_Matrix4f_mulv(std_matrix_Matrix4f this, std_vec_Vec3__0 v) {
  f32 x = ((((v.x * this.d[0][0]) + (v.y * this.d[0][1])) + (v.z * this.d[0][2])) + this.d[0][3]);
  f32 y = ((((v.x * this.d[1][0]) + (v.y * this.d[1][1])) + (v.z * this.d[1][2])) + this.d[1][3]);
  f32 z = ((((v.x * this.d[2][0]) + (v.y * this.d[2][1])) + (v.z * this.d[2][2])) + this.d[2][3]);
  return (std_vec_Vec3__0){.x=x, .y=y, .z=z};
}

u32 std_sdl_Key_hash(SDL_Scancode this) {
  return u32_hash(((u32)this));}

bool std_sdl_Key_eq(SDL_Scancode this, SDL_Scancode other) {
  return this==other;}

void std_sdl_Texture_write_image(SDL_Texture *this, std_image_Image *img) {
  u8 *data;
  i32 i_pitch = 0;
  i32 tw = 0;
  i32 th = 0;
  SDL_QueryTexture(this, NULL, NULL, &tw, &th);
  if(!(((u32)tw)==img->width && ((u32)th)==img->height)) { ae_assert_fail("/home/runner/work/render3d/render3d/ocen/std/sdl/mod.oc:263:12: Assertion failed: `tw as u32 == img.width and th as u32 == img.height`", "Texture and Image sizes do not match"); }
  SDL_LockTexture(this, NULL, ((void **)&data), &i_pitch);
  for (u32 y = 0; y < img->height; y+=1) {
    for (u32 x = 0; x < img->width; x+=1) {
      std_image_Color c = std_image_Image_get(img, x, y);
      u32 offset = ((y * ((u32)i_pitch)) + (x * 4));
      data[(offset + 0)]=c.r;
      data[(offset + 1)]=c.g;
      data[(offset + 2)]=c.b;
      data[(offset + 3)]=((u8)255);
    }
  }
  SDL_UnlockTexture(this);
}

Triangle std_sort_nth_element_by__0(Triangle *data, u32 size, u32 n, _ClosureTy_13 cmp) {
  if (size <= 1) {
    return data[0];
  }
  Triangle pivot = data[(size / 2)];
  u32 i = 0;
  u32 j = (size - 1);
  while (i <= j) {
    while (cmp.fn(cmp._C, data[i], pivot) < ((i8)0)) {
      i+=1;
    }
    while (cmp.fn(cmp._C, data[j], pivot) > ((i8)0)) {
      j-=1;
    }
    if (i <= j) {
      Triangle tmp = data[i];
      data[i]=data[j];
      data[j]=tmp;
      i+=1;
      j-=1;
    }
  }
  if (n < j) {
    return std_sort_nth_element_by__0(data, (j + 1), n, cmp);
  } else if (n >= i) {
    return std_sort_nth_element_by__0((data + i), (size - i), (n - i), cmp);
  } else {
    return pivot;
  }
}

u32 std_sort_partition_by_closure__0(Triangle *data, u32 size, _ClosureTy_8 cmp) {
  u32 first = size;
  for (u32 i = 0; i < size; i+=1) {
    if (!(cmp.fn(cmp._C, data[i]))) {
      first=i;
      break;
    }
  }
  for (u32 i = first; i < size; i+=1) {
    if (cmp.fn(cmp._C, data[i])) {
      Triangle tmp = data[i];
      data[i]=data[first];
      data[first]=tmp;
      first+=1;
    }
  }
  return first;
}

void src_bvh_BVH__0_hit(src_bvh_BVH__0 *this, src_ray_Ray *ray, std_vector_Vector__2 *hit_nodes) {
  if (this->is_leaf) {
    std_vector_Vector__2_push(hit_nodes, this);
  } else {
    std_vector_Vector__2_push(hit_nodes, this);
    f32 t_l = 0.000000f;
    f32 t_r = 0.000000f;
    bool hit_l = src_bounds_Bounds_hit(&this->l->bounds, ray, &t_l, &t_r, std_vec_Vec3__0_divrs(1.000000f, ray->dir));
    bool hit_r = src_bounds_Bounds_hit(&this->r->bounds, ray, &t_l, &t_r, std_vec_Vec3__0_divrs(1.000000f, ray->dir));
    if (!(hit_l) && !(hit_r)) {
      return;
    }
    if (!(hit_l)) {
      src_bvh_BVH__0_hit(this->r, ray, hit_nodes);
      return;
    }
    if (!(hit_r)) {
      src_bvh_BVH__0_hit(this->l, ray, hit_nodes);
      return;
    }
    if (t_l < t_r) {
      src_bvh_BVH__0_hit(this->l, ray, hit_nodes);
      src_bvh_BVH__0_hit(this->r, ray, hit_nodes);
    } else {
      src_bvh_BVH__0_hit(this->r, ray, hit_nodes);
      src_bvh_BVH__0_hit(this->l, ray, hit_nodes);
    }
  }}

src_bvh_BVH__0 *src_bvh_BVH__0_create(std_vector_Vector__3 *objects) {
  f64 start_time = std_time_get_time_monotonic_ms();
  src_bvh_BVH__0 *bvh = src_bvh_BVH__0_create_rec(objects, 0, objects->size);
  f64 duration = (std_time_get_time_monotonic_ms() - start_time);
  std_logging_log(std_logging_LogLevel_Info, "BVH created with %u objects in %.2fs", objects->size, (duration / 1000.000000));
  return bvh;
}

src_bvh_BVH__0 *src_bvh_BVH__0_create_rec(std_vector_Vector__3 *objects, u32 start, u32 end) {
  if ((end - start)==1) {
    Triangle object = std_vector_Vector__3_at(objects, start);
    src_bounds_Bounds bounds = Triangle_bounds(object);
    src_bvh_BVH__0 leaf = {0};
    leaf.is_leaf=true;
    leaf.obj=object;
    leaf.bounds=bounds;
    return ({src_bvh_BVH__0 *_new_32 = std_mem_state_alloc_fn(std_mem_state_allocator, sizeof(src_bvh_BVH__0)); *_new_32 = leaf; _new_32; });
  } else {
    src_bounds_Bounds bounds = src_bounds_Bounds_empty();
    for (u32 i = start; i < end; i+=1) {
      src_bounds_Bounds_join_assign(&bounds, Triangle_bounds(std_vector_Vector__3_at(objects, i)));
    }
    std_vec_Vec3__0 box_sizes = std_vec_Vec3__0_sub(bounds.max, bounds.min);
    u32 dim = 0;
    if (std_vec_Vec3__0_index(box_sizes, dim) < std_vec_Vec3__0_index(box_sizes, 1)) {
      dim=1;
    }
    if (std_vec_Vec3__0_index(box_sizes, dim) < std_vec_Vec3__0_index(box_sizes, 2)) {
      dim=2;
    }
    u32 mid = src_bvh_BVH__0_split_SAH(objects, start, end, bounds, dim);
    src_bvh_BVH__0 *l = src_bvh_BVH__0_create_rec(objects, start, mid);
    src_bvh_BVH__0 *r = src_bvh_BVH__0_create_rec(objects, mid, end);
    src_bvh_BVH__0 internal = {0};
    internal.is_leaf=false;
    internal.l=l;
    internal.r=r;
    internal.bounds=bounds;
    return ({src_bvh_BVH__0 *_new_33 = std_mem_state_alloc_fn(std_mem_state_allocator, sizeof(src_bvh_BVH__0)); *_new_33 = internal; _new_33; });
  }
}

u32 src_bvh_BVH__0_split_SAH(std_vector_Vector__3 *objects, u32 start, u32 end, src_bounds_Bounds bounds, u32 axis) {
  src_bvh_Bucket buckets[src_bvh_NUM_BUCKETS] = {0};
  for (u32 i = start; i < end; i++) {
    u32 b = ((u32)(((f32)src_bvh_NUM_BUCKETS) * std_vec_Vec3__0_index(src_bounds_Bounds_offset(&bounds, src_bounds_Bounds_centroid(Triangle_bounds(std_vector_Vector__3_at(objects, i)))), axis)));
    if (b==src_bvh_NUM_BUCKETS) {
      b=(src_bvh_NUM_BUCKETS - 1);
    }
    buckets[b].count+=1;
    buckets[b].bounds=src_bounds_Bounds_join(buckets[b].bounds, Triangle_bounds(std_vector_Vector__3_at(objects, i)));
  }
  f32 cost[(src_bvh_NUM_BUCKETS - 1)] = {0};
  for (u32 i = 0; i < (src_bvh_NUM_BUCKETS - 1); ++i) {
    src_bounds_Bounds b0 = src_bounds_Bounds_empty();
    src_bounds_Bounds b1 = src_bounds_Bounds_empty();
    u32 c0 = 0;
    u32 c1 = 0;
    for (u32 j = 0; j <= i; ++j) {
      b0=src_bounds_Bounds_join(b0, buckets[j].bounds);
      c0+=buckets[j].count;
    }
    for (u32 j = (i + 1); j < src_bvh_NUM_BUCKETS; ++j) {
      b1=src_bounds_Bounds_join(b1, buckets[j].bounds);
      c1+=buckets[j].count;
    }
    cost[i]=(0.125000f + (((((f32)c0) * src_bounds_Bounds_area(b0)) + (((f32)c1) * src_bounds_Bounds_area(b1))) / src_bounds_Bounds_area(bounds)));
  }
  u32 min_bucket = 0;
  for (u32 i = 1; i < (src_bvh_NUM_BUCKETS - 1); ++i) {
    if (cost[i] < cost[min_bucket]) {
      min_bucket=i;
    }
  }
  u32 mid = (start + std_sort_partition_by_closure__0((objects->data + start), (end - start), ({src_bvh_split_SAH__Closure_22Ctx *_C34 = alloca(sizeof(src_bvh_split_SAH__Closure_22Ctx));_C34->bounds = &bounds;_C34->min_bucket = &min_bucket;_C34->axis = &axis;_ClosureTy_8 _ci35 = {._C=_C34, .fn=&src_bvh_split_SAH__Closure_22};_ci35;})));
  if (mid==start || mid==end) {
    mid=src_bvh_BVH__0_split_equal(objects, start, end, bounds, axis);
  }
  return mid;
}

u32 src_bvh_BVH__0_split_equal(std_vector_Vector__3 *objects, u32 start, u32 end, src_bounds_Bounds bounds, u32 axis) {
  u32 mid = ((start + end) / 2);
  std_sort_nth_element_by__0((objects->data + start), (end - start), mid, ({src_bvh_split_equal__Closure_23Ctx *_C36 = alloca(sizeof(src_bvh_split_equal__Closure_23Ctx));_C36->axis = &axis;_ClosureTy_13 _ci37 = {._C=_C36, .fn=&src_bvh_split_equal__Closure_23};_ci37;}));
  return mid;
}

src_bounds_Bounds src_bounds_Bounds_empty(void) {
  return (src_bounds_Bounds){.min=(std_vec_Vec3__0){.x=f32_inf(), .y=f32_inf(), .z=f32_inf()}, .max=(std_vec_Vec3__0){.x=-f32_inf(), .y=-f32_inf(), .z=-f32_inf()}};}

src_bounds_Bounds src_bounds_Bounds_join(src_bounds_Bounds this, src_bounds_Bounds other) {
  std_vec_Vec3__0 new_min = (std_vec_Vec3__0){.x=f32_min(this.min.x, other.min.x), .y=f32_min(this.min.y, other.min.y), .z=f32_min(this.min.z, other.min.z)};
  std_vec_Vec3__0 new_max = (std_vec_Vec3__0){.x=f32_max(this.max.x, other.max.x), .y=f32_max(this.max.y, other.max.y), .z=f32_max(this.max.z, other.max.z)};
  return (src_bounds_Bounds){.min=new_min, .max=new_max};
}

void src_bounds_Bounds_join_assign(src_bounds_Bounds *this, src_bounds_Bounds other) {
    (*this)=src_bounds_Bounds_join((*this), other);
}

std_vec_Vec3__0 src_bounds_Bounds_offset(src_bounds_Bounds *this, std_vec_Vec3__0 p) {
  std_vec_Vec3__0 t = std_vec_Vec3__0_sub(p, this->min);
  if (this->max.x > this->min.x) {
    t.x/=(this->max.x - this->min.x);
  }
  if (this->max.y > this->min.y) {
    t.y/=(this->max.y - this->min.y);
  }
  if (this->max.z > this->min.z) {
    t.z/=(this->max.z - this->min.z);
  }
  return t;
}

std_vec_Vec3__0 src_bounds_Bounds_centroid(src_bounds_Bounds this) {
  return std_vec_Vec3__0_divs(std_vec_Vec3__0_add(this.min, this.max), 2.000000f);}

f32 src_bounds_Bounds_area(src_bounds_Bounds this) {
  std_vec_Vec3__0 d = std_vec_Vec3__0_sub(this.max, this.min);
  return 2.000000f * (((d.x * d.y) + (d.x * d.z)) + (d.y * d.z));
}

bool src_bounds_Bounds_hit(src_bounds_Bounds *this, src_ray_Ray *ray, f32 *t1, f32 *t2, std_vec_Vec3__0 inv_d) {
  f32 tmin = -f32_inf();
  f32 tmax = f32_inf();
  {
    f32 tmin_ = ((this->min.x - ray->pos.x) * inv_d.x);
    f32 tmax_ = ((this->max.x - ray->pos.x) * inv_d.x);
    if (tmin_ > tmax_) {
      f32 tmp = tmin_;
      tmin_=tmax_;
      tmax_=tmp;
    }
    if ((tmin > tmax_) || (tmin_ > tmax)) {
      return false;
    }
    if (tmin_ > tmin) {
      tmin=tmin_;
    }
    if (tmax_ < tmax) {
      tmax=tmax_;
    }
  }
  {
    f32 tmin_ = ((this->min.y - ray->pos.y) * inv_d.y);
    f32 tmax_ = ((this->max.y - ray->pos.y) * inv_d.y);
    if (tmin_ > tmax_) {
      f32 tmp = tmin_;
      tmin_=tmax_;
      tmax_=tmp;
    }
    if ((tmin > tmax_) || (tmin_ > tmax)) {
      return false;
    }
    if (tmin_ > tmin) {
      tmin=tmin_;
    }
    if (tmax_ < tmax) {
      tmax=tmax_;
    }
  }
  {
    f32 tmin_ = ((this->min.z - ray->pos.z) * inv_d.z);
    f32 tmax_ = ((this->max.z - ray->pos.z) * inv_d.z);
    if (tmin_ > tmax_) {
      f32 tmp = tmin_;
      tmin_=tmax_;
      tmax_=tmp;
    }
    if ((tmin > tmax_) || (tmin_ > tmax)) {
      return false;
    }
    if (tmin_ > tmin) {
      tmin=tmin_;
    }
    if (tmax_ < tmax) {
      tmax=tmax_;
    }
  }
  if ((tmin < 0.000100f) && (tmax < 0.000100f)) {
    return false;
  }
  if (tmin < 0.000100f) {
    tmin=0.000000f;
  }
  if (((bool)t1)) {
    (*t1)=tmin;
  }
  if (((bool)t2)) {
    (*t2)=tmax;
  }
  return true;
}

std_image_Color vec_to_col(std_vec_Vec3__0 vec, f32 scale) {
  vec=std_vec_Vec3__0_mults(std_vec_Vec3__0_adds(std_vec_Vec3__0_mults(std_vec_Vec3__0_normalized(vec), 128.000000f), 128.000000f), scale);
  return (std_image_Color){.r=((u8)vec.x), .g=((u8)vec.y), .b=((u8)vec.z)};
}

std_vec_Vec2__3 camera_to_screen(std_vec_Vec3__0 p0) {
  std_vec_Vec2__1 p0_s = std_vec_Vec2__1_mults((std_vec_Vec2__1){.x=(p0.x / p0.z), .y=(p0.y / p0.z)}, focal_length);
  std_vec_Vec2__1 p0_i = std_vec_Vec2__1_mult(std_vec_Vec2__1_mults(std_vec_Vec2__1_adds(std_vec_Vec2__1_div((std_vec_Vec2__1){.x=p0_s.x, .y=-p0_s.y}, aspect_ratio), 1.000000f), 0.500000f), size_f);
  return std_vec_Vec2__1_to_i32(p0_i);
}

void draw_triangle_camera_space(std_vec_Vec3__0 p0, std_vec_Vec3__0 p1, std_vec_Vec3__0 p2, std_image_Color c0, std_image_Color c1, std_image_Color c2) {
  std_vec_Vec3__0 cam_normal = std_vec_Vec3__0_normalized(std_vec_Vec3__0_cross(std_vec_Vec3__0_sub(p1, p0), std_vec_Vec3__0_sub(p2, p0)));
  if (backface_culling && (std_vec_Vec3__0_dot(cam_normal, std_vec_Vec3__0_multrs(-1.000000f, p0)) < 0.000000f)) {
    return;
  }
  fill_triangle_zc(camera_to_screen(p0), camera_to_screen(p1), camera_to_screen(p2), p0.z, p1.z, p2.z, c0, c1, c2);
}

std_image_Color interp_color(std_image_Color c0, std_image_Color c1, f32 t) {
  return (std_image_Color){.r=((u8)((((f32)c0.r) * (1.000000f - t)) + (((f32)c1.r) * t))), .g=((u8)((((f32)c0.g) * (1.000000f - t)) + (((f32)c1.g) * t))), .b=((u8)((((f32)c0.b) * (1.000000f - t)) + (((f32)c1.b) * t)))};
}

std_vec_Vec3__0 interp_vec(std_vec_Vec3__0 v0, std_vec_Vec3__0 v1, f32 t) {
  return std_vec_Vec3__0_add(std_vec_Vec3__0_mults(v0, (1.000000f - t)), std_vec_Vec3__0_mults(v1, t));
}

void swap__0(u32 *a, u32 *b) {
  u32 tmp = (*a);
  (*a)=(*b);
  (*b)=tmp;
}

void draw_triangle_clipped(Triangle tri) {
  std_vec_Vec3__0 p0 = std_matrix_Matrix4f_mulv(camera_transform, tri.p0);
  std_vec_Vec3__0 p1 = std_matrix_Matrix4f_mulv(camera_transform, tri.p1);
  std_vec_Vec3__0 p2 = std_matrix_Matrix4f_mulv(camera_transform, tri.p2);
  std_image_Color c0 = vec_to_col(tri.n0, 1.000000f);
  std_image_Color c1 = vec_to_col(tri.n1, 1.000000f);
  std_image_Color c2 = vec_to_col(tri.n2, 1.000000f);
  std_vec_Vec3__0 ps[3] = {p0, p1, p2};
  std_image_Color cs[3] = {c0, c1, c2};
  u32 in_tris[3] = {0};
  u32 in_idx = 0;
  u32 out_tris[3] = {0};
  u32 out_idx = 0;
  if (p0.z < MIN_CLIP) {
    out_tris[out_idx++]=0;
  } else {
    in_tris[in_idx++]=0;
  }
  if (p1.z < MIN_CLIP) {
    out_tris[out_idx++]=1;
  } else {
    in_tris[in_idx++]=1;
  }
  if (p2.z < MIN_CLIP) {
    out_tris[out_idx++]=2;
  } else {
    in_tris[in_idx++]=2;
  }
  switch (out_idx) {
    case 0: {
      draw_triangle_camera_space(p0, p1, p2, c0, c1, c2);
    } break;
    case 1: {
      if (out_tris[0]==1) {
        swap__0(&in_tris[0], &in_tris[1]);
      }
      std_vec_Vec3__0 o_p0 = ps[out_tris[0]];
      std_image_Color o_c0 = cs[out_tris[0]];
      std_vec_Vec3__0 i_p0 = ps[in_tris[0]];
      std_vec_Vec3__0 i_p1 = ps[in_tris[1]];
      std_image_Color i_c0 = cs[in_tris[0]];
      std_image_Color i_c1 = cs[in_tris[1]];
      f32 t0 = ((MIN_CLIP - o_p0.z) / (i_p0.z - o_p0.z));
      f32 t1 = ((MIN_CLIP - o_p0.z) / (i_p1.z - o_p0.z));
      std_vec_Vec3__0 n_p0 = interp_vec(o_p0, i_p0, t0);
      std_image_Color n_c0 = interp_color(i_c0, o_c0, t0);
      std_vec_Vec3__0 n_p1 = interp_vec(o_p0, i_p1, t1);
      std_image_Color n_c1 = interp_color(i_c1, o_c0, t1);
      draw_triangle_camera_space(i_p0, i_p1, n_p0, i_c0, i_c1, n_c0);
      draw_triangle_camera_space(i_p1, n_p1, n_p0, i_c1, n_c1, n_c0);
    } break;
    case 2: {
      if (in_tris[0]==1) {
        swap__0(&out_tris[0], &out_tris[1]);
      }
      std_vec_Vec3__0 o_p0 = ps[out_tris[0]];
      std_image_Color o_c0 = cs[out_tris[0]];
      std_vec_Vec3__0 o_p1 = ps[out_tris[1]];
      std_image_Color o_c1 = cs[out_tris[1]];
      std_vec_Vec3__0 i_p0 = ps[in_tris[0]];
      std_image_Color i_c0 = cs[in_tris[0]];
      f32 t0 = ((MIN_CLIP - o_p0.z) / (i_p0.z - o_p0.z));
      f32 t1 = ((MIN_CLIP - o_p1.z) / (i_p0.z - o_p1.z));
      std_vec_Vec3__0 n_p0 = interp_vec(o_p0, i_p0, t0);
      std_image_Color n_c0 = interp_color(i_c0, o_c0, t0);
      std_vec_Vec3__0 n_p1 = interp_vec(o_p1, i_p0, t1);
      std_image_Color n_c1 = interp_color(i_c0, o_c1, t1);
      draw_triangle_camera_space(i_p0, n_p0, n_p1, i_c0, n_c0, n_c1);
    } break;
    case 3: {
    } break;
    default: {
      if(!(false)) { ae_assert_fail("src/main.oc:169:24: Assertion failed: `false`", std_format("Unreachable: in_idx=%u, out_idx=%u", in_idx, out_idx)); exit(1); }
    } break;
  }
}

i32 i32_sign(i32 this) {
  return (((i32)(this > 0)) - ((i32)(this < 0)));}

bool is_ok(i32 a, i32 b) {
  return (i32_sign(a)==i32_sign(b) || a==0);}

__attribute__((flatten))
void fill_triangle_zc(std_vec_Vec2__3 p0, std_vec_Vec2__3 p1, std_vec_Vec2__3 p2, f32 z0, f32 z1, f32 z2, std_image_Color c0, std_image_Color c1, std_image_Color c2) {
  i32 min_x = i32_max(i32_min(p0.x, i32_min(p1.x, p2.x)), 0);
  i32 min_y = i32_max(i32_min(p0.y, i32_min(p1.y, p2.y)), 0);
  i32 max_x = i32_min(i32_max(p0.x, i32_max(p1.x, p2.x)), ((i32)(image->width - 1)));
  i32 max_y = i32_min(i32_max(p0.y, i32_max(p1.y, p2.y)), ((i32)(image->height - 1)));
  i32 denom = (((p0.x - p2.x) * (p1.y - p2.y)) - ((p1.x - p2.x) * (p0.y - p2.y)));
  for (i32 x = min_x; x <= max_x; x+=1) {
    for (i32 y = min_y; y <= max_y; y+=1) {
      i32 u = (((p1.y - p2.y) * (x - p2.x)) + ((p2.x - p1.x) * (y - p2.y)));
      i32 v = (((p2.y - p0.y) * (x - p2.x)) + ((p0.x - p2.x) * (y - p2.y)));
      i32 w = ((denom - u) - v);
      if ((is_ok(u, denom) && is_ok(v, denom)) && is_ok(w, denom)) {
        f32 z = ((((z0 * ((f32)u)) + (z1 * ((f32)v))) + (z2 * ((f32)w))) / ((f32)denom));
        std_image_Color col = (std_image_Color){.r=((u8)((((((i32)c0.r) * u) + (((i32)c1.r) * v)) + (((i32)c2.r) * w)) / denom)), .g=((u8)((((((i32)c0.g) * u) + (((i32)c1.g) * v)) + (((i32)c2.g) * w)) / denom)), .b=((u8)((((((i32)c0.b) * u) + (((i32)c1.b) * v)) + (((i32)c2.b) * w)) / denom))};
        if (src_zbuffer_ZBuffer_put_if_closer(zbuffer, ((u32)x), ((u32)y), z)) {
          std_image_Image_set(image, ((u32)x), ((u32)y), col);
        }
      }
    }
  }
}

src_bounds_Bounds Triangle_bounds(Triangle this) {
  return (src_bounds_Bounds){.min=(std_vec_Vec3__0){.x=f32_min(f32_min(this.p0.x, this.p1.x), this.p2.x), .y=f32_min(f32_min(this.p0.y, this.p1.y), this.p2.y), .z=f32_min(f32_min(this.p0.z, this.p1.z), this.p2.z)}, .max=(std_vec_Vec3__0){.x=f32_max(f32_max(this.p0.x, this.p1.x), this.p2.x), .y=f32_max(f32_max(this.p0.y, this.p1.y), this.p2.y), .z=f32_max(f32_max(this.p0.z, this.p1.z), this.p2.z)}};}

Mesh Mesh_from_obj(char *filename) {
  std_buffer_Buffer file = std_fs_read_file(filename);
  std_sv_SV sv = std_buffer_Buffer_sv(file);
  std_vector_Vector__4 *vectors = ({
    std_vector_Vector__4 *_vc38 = std_vector_Vector__4_new(8);
    _vc38;});
  std_vector_Vector__4 *normals = ({
    std_vector_Vector__4 *_vc39 = std_vector_Vector__4_new(8);
    _vc39;});
  std_vector_Vector__5 *textures = ({
    std_vector_Vector__5 *_vc40 = std_vector_Vector__5_new(8);
    _vc40;});
  _ClosureTy_16 parse_vertex = ({from_obj__Closure_0Ctx *_C41 = alloca(sizeof(from_obj__Closure_0Ctx));_C41->textures = &textures;_C41->normals = &normals;_C41->vectors = &vectors;_ClosureTy_16 _ci42 = {._C=_C41, .fn=&from_obj__Closure_0};_ci42;});
  std_vector_Vector__3 *triangles = ({
    std_vector_Vector__3 *_vc43 = std_vector_Vector__3_new(8);
    _vc43;});
  for (std_sv_SVLineIterator _i1 = std_sv_SV_lines(sv); std_sv_SVLineIterator_has_value(&_i1); std_sv_SVLineIterator_next(&_i1)) {
    std_sv_SV line = std_sv_SVLineIterator_cur(&_i1);
    {
      {
        std_sv_SV __match_var_44 = std_sv_SV_chop_word(&line);
        if (std_sv_SV_eq_str(__match_var_44, "v")) {
          std_vector_Vector__4_push(vectors, (std_vec_Vec3__0){.x=std_sv_SV_chop_f32(&line), .y=std_sv_SV_chop_f32(&line), .z=std_sv_SV_chop_f32(&line)});
        } else if (std_sv_SV_eq_str(__match_var_44, "vn")) {
          std_vector_Vector__4_push(normals, (std_vec_Vec3__0){.x=std_sv_SV_chop_f32(&line), .y=std_sv_SV_chop_f32(&line), .z=std_sv_SV_chop_f32(&line)});
        } else if (std_sv_SV_eq_str(__match_var_44, "vt")) {
          std_vector_Vector__5_push(textures, (std_vec_Vec2__1){.x=std_sv_SV_chop_f32(&line), .y=std_sv_SV_chop_f32(&line)});
        } else if (std_sv_SV_eq_str(__match_var_44, "f")) {
          Vertex p0 = parse_vertex.fn(parse_vertex._C, &line);
          Vertex p1 = parse_vertex.fn(parse_vertex._C, &line);
          while (line.len > 0) {
            Vertex p2 = parse_vertex.fn(parse_vertex._C, &line);
            std_vector_Vector__3_push(triangles, (Triangle){.p0=p0.pos, .p1=p1.pos, .p2=p2.pos, .n0=p0.nor, .n1=p1.nor, .n2=p2.nor});
            p1=p2;
          }
        } else  {
        }
      }
    }
  }
  Mesh mesh = (Mesh){.triangles=triangles};
  /* defers */
  std_vector_Vector__5_free(textures);
  std_vector_Vector__4_free(normals);
  std_vector_Vector__4_free(vectors);
  std_buffer_Buffer_free(&file);
  return mesh;
}

void update_camera(std_vec_Vec3__0 *origin, std_vec_Vec3__0 *direction) {
  std_vec_Vec3__0 up = (std_vec_Vec3__0){.x=0.000000f, .y=1.000000f, .z=0.000000f};
  (*direction)=std_vec_Vec3__0_normalized((*direction));
  std_vec_Vec3__0 z = (*direction);
  std_vec_Vec3__0 x = std_vec_Vec3__0_normalized(std_vec_Vec3__0_cross(up, z));
  std_vec_Vec3__0 y = std_vec_Vec3__0_normalized(std_vec_Vec3__0_cross(z, x));
  camera_transform=std_matrix_Matrix4f_make(x.x, x.y, x.z, -std_vec_Vec3__0_dot((*origin), x), y.x, y.y, y.z, -std_vec_Vec3__0_dot((*origin), y), z.x, z.y, z.z, -std_vec_Vec3__0_dot((*origin), z), 0.000000f, 0.000000f, 0.000000f, 1.000000f);
}

std_vec_Vec3__0 rotate_vector(std_vec_Vec3__0 v, std_vec_Vec3__0 axis, f32 angle) {
  f32 cos_theta = cosf(angle);
  f32 sin_theta = sinf(angle);
  std_vec_Vec3__0 term1 = std_vec_Vec3__0_mults(v, cos_theta);
  std_vec_Vec3__0 term2 = std_vec_Vec3__0_mults(std_vec_Vec3__0_cross(axis, v), sin_theta);
  f32 dot_av = std_vec_Vec3__0_dot(axis, v);
  std_vec_Vec3__0 term3 = std_vec_Vec3__0_mults(std_vec_Vec3__0_mults(axis, dot_av), (1.000000f - cos_theta));
  return std_vec_Vec3__0_add(std_vec_Vec3__0_add(term1, term2), term3);
}

void run_ui(Mesh *mesh) {
  u32 width = image->width;
  u32 height = image->height;
  std_og_init(width, height, "Render", false);
  std_og_grab_input(true);
  std_og_show_cursor(false);
  f32 MOVE_SENSITIVITY = 5.000000f;
  f32 KEYBOARD_LOOK_SENSITIVITY = 1.500000f;
  f32 MOUSE_LOOK_SENSITIVITY = 0.200000f;
  f32 dtime = 0.000000f;
  _ClosureTy_17 rotate_camera = ({run_ui__Closure_1Ctx *_C45 = alloca(sizeof(run_ui__Closure_1Ctx));_C45->dtime = &dtime;_ClosureTy_17 _ci46 = {._C=_C45, .fn=&run_ui__Closure_1};_ci46;});
  std_compact_map_Map__0 *key_callbacks = ({
    std_compact_map_Map__0 *_mc47 = std_compact_map_Map__0_new(13);
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_W, ({run_ui__Closure_2Ctx *_C48 = alloca(sizeof(run_ui__Closure_2Ctx));_C48->dtime = &dtime;_C48->MOVE_SENSITIVITY = &MOVE_SENSITIVITY;_ClosureTy_18 _ci49 = {._C=_C48, .fn=&run_ui__Closure_2};_ci49;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_S, ({run_ui__Closure_3Ctx *_C50 = alloca(sizeof(run_ui__Closure_3Ctx));_C50->dtime = &dtime;_C50->MOVE_SENSITIVITY = &MOVE_SENSITIVITY;_ClosureTy_18 _ci51 = {._C=_C50, .fn=&run_ui__Closure_3};_ci51;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_A, ({run_ui__Closure_4Ctx *_C52 = alloca(sizeof(run_ui__Closure_4Ctx));_C52->dtime = &dtime;_C52->MOVE_SENSITIVITY = &MOVE_SENSITIVITY;_ClosureTy_18 _ci53 = {._C=_C52, .fn=&run_ui__Closure_4};_ci53;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_D, ({run_ui__Closure_5Ctx *_C54 = alloca(sizeof(run_ui__Closure_5Ctx));_C54->dtime = &dtime;_C54->MOVE_SENSITIVITY = &MOVE_SENSITIVITY;_ClosureTy_18 _ci55 = {._C=_C54, .fn=&run_ui__Closure_5};_ci55;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_Z, ({run_ui__Closure_6Ctx *_C56 = alloca(sizeof(run_ui__Closure_6Ctx));_C56->dtime = &dtime;_C56->MOVE_SENSITIVITY = &MOVE_SENSITIVITY;_ClosureTy_18 _ci57 = {._C=_C56, .fn=&run_ui__Closure_6};_ci57;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_X, ({run_ui__Closure_7Ctx *_C58 = alloca(sizeof(run_ui__Closure_7Ctx));_C58->dtime = &dtime;_C58->MOVE_SENSITIVITY = &MOVE_SENSITIVITY;_ClosureTy_18 _ci59 = {._C=_C58, .fn=&run_ui__Closure_7};_ci59;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_M, ({run_ui__Closure_8Ctx *_C60 = alloca(sizeof(run_ui__Closure_8Ctx));_ClosureTy_18 _ci61 = {._C=_C60, .fn=&run_ui__Closure_8};_ci61;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_N, ({run_ui__Closure_9Ctx *_C62 = alloca(sizeof(run_ui__Closure_9Ctx));_ClosureTy_18 _ci63 = {._C=_C62, .fn=&run_ui__Closure_9};_ci63;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_UP, ({run_ui__Closure_10Ctx *_C64 = alloca(sizeof(run_ui__Closure_10Ctx));_C64->KEYBOARD_LOOK_SENSITIVITY = &KEYBOARD_LOOK_SENSITIVITY;_C64->rotate_camera = &rotate_camera;_ClosureTy_18 _ci65 = {._C=_C64, .fn=&run_ui__Closure_10};_ci65;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_DOWN, ({run_ui__Closure_11Ctx *_C66 = alloca(sizeof(run_ui__Closure_11Ctx));_C66->KEYBOARD_LOOK_SENSITIVITY = &KEYBOARD_LOOK_SENSITIVITY;_C66->rotate_camera = &rotate_camera;_ClosureTy_18 _ci67 = {._C=_C66, .fn=&run_ui__Closure_11};_ci67;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_LEFT, ({run_ui__Closure_12Ctx *_C68 = alloca(sizeof(run_ui__Closure_12Ctx));_C68->KEYBOARD_LOOK_SENSITIVITY = &KEYBOARD_LOOK_SENSITIVITY;_C68->rotate_camera = &rotate_camera;_ClosureTy_18 _ci69 = {._C=_C68, .fn=&run_ui__Closure_12};_ci69;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_RIGHT, ({run_ui__Closure_13Ctx *_C70 = alloca(sizeof(run_ui__Closure_13Ctx));_C70->KEYBOARD_LOOK_SENSITIVITY = &KEYBOARD_LOOK_SENSITIVITY;_C70->rotate_camera = &rotate_camera;_ClosureTy_18 _ci71 = {._C=_C70, .fn=&run_ui__Closure_13};_ci71;}));
    std_compact_map_Map__0_insert(_mc47, SDL_SCANCODE_ESCAPE, ({run_ui__Closure_14Ctx *_C72 = alloca(sizeof(run_ui__Closure_14Ctx));_ClosureTy_18 _ci73 = {._C=_C72, .fn=&run_ui__Closure_14};_ci73;}));
    _mc47;});
  u32 prev_ticks = std_og_get_ticks();
  while (std_og_is_running()) {
    u32 curr_ticks = std_og_get_ticks();
    dtime=(((f32)(curr_ticks - prev_ticks)) / 1000.000000f);
    prev_ticks=curr_ticks;
    for (std_compact_map_Iterator__0 _i3 = std_compact_map_Map__0_iter(key_callbacks); std_compact_map_Iterator__0_has_value(&_i3); std_compact_map_Iterator__0_next(&_i3)) {
      std_compact_map_Item__0 it = std_compact_map_Iterator__0_cur(&_i3);
      {
        if (std_og_is_key_down(it.key)) {
          it.value.fn(it.value._C);
        }
      }
    }
    if (std_og_is_key_pressed(SDL_SCANCODE_F)) {
      std_og_toggle_fullscreen();
    }
    if (std_og_is_key_pressed(SDL_SCANCODE_O) && (depth_limit > 0)) {
      depth_limit--;
    }
    if (std_og_is_key_pressed(SDL_SCANCODE_P)) {
      depth_limit++;
    }
    if (std_og_is_key_pressed(SDL_SCANCODE_J)) {
      show_mesh=!(show_mesh);
    }
    if (std_og_is_key_pressed(SDL_SCANCODE_H)) {
      show_ray_and_hit=!(show_ray_and_hit);
    }
    if (std_og_is_key_pressed(SDL_SCANCODE_G)) {
      ray=(src_ray_Ray){.pos=camera_pos, .dir=camera_dir};
      std_vector_Vector__2_clear(hit_nodes);
      src_bvh_BVH__0_hit(bvh, &ray, hit_nodes);
    }
    std_vec_Vec2__3 mouse = std_og_get_mouse_delta();
    rotate_camera.fn(rotate_camera._C, mouse.x, -mouse.y, MOUSE_LOOK_SENSITIVITY);
    std_image_Image_clear(image);
    src_zbuffer_ZBuffer_clear(zbuffer);
    if (show_mesh) {
      for (std_vector_Iterator__3 _i4 = std_vector_Vector__3_iter(mesh->triangles); std_vector_Iterator__3_has_value(&_i4); std_vector_Iterator__3_next(&_i4)) {
        Triangle tri = std_vector_Iterator__3_cur(&_i4);
        {
          draw_triangle_clipped(tri);
        }
      }
    }
    draw_bvh(bvh, 0);
    if (show_ray_and_hit) {
      draw_ray();
      draw_hit_nodes();
    }
    std_og_display_image(image);
  }
}

void draw_line_clipped_thick(std_vec_Vec3__0 p0_w, std_vec_Vec3__0 p1_w, std_image_Color color, f32 thickness) {
  u32 RAD_PARTS = 3;
  u32 LENGTH_PARTS = u32_max(10, ((u32)std_vec_Vec3__0_length(std_vec_Vec3__0_sub(p1_w, p0_w))));
  std_vec_Vec3__0 dir = std_vec_Vec3__0_sub(p1_w, p0_w);
  std_vec_Vec3__0 axis = std_vec_Vec3__0_normalized(dir);
  _ClosureTy_20 simple_tri = ({draw_line_clipped_thick__Closure_15Ctx *_C74 = alloca(sizeof(draw_line_clipped_thick__Closure_15Ctx));_ClosureTy_20 _ci75 = {._C=_C74, .fn=&draw_line_clipped_thick__Closure_15};_ci75;});
  std_vec_Vec3__0 dir_delta = std_vec_Vec3__0_divs(dir, ((f32)LENGTH_PARTS));
  std_vec_Vec3__0 base = std_vec_Vec3__0_mults(std_vec_Vec3__0_normalized(std_vec_Vec3__0_cross(axis, (std_vec_Vec3__0){.x=1.000000f, .y=1.000000f, .z=0.000000f})), thickness);
  for (u32 i = 0; i < RAD_PARTS; i+=1) {
    std_vec_Vec3__0 s0 = std_vec_Vec3__0_rotate_axis(base, axis, (((((f32)(i + 0)) / ((f32)RAD_PARTS)) * M_PI) * 2.000000f));
    std_vec_Vec3__0 s1 = std_vec_Vec3__0_rotate_axis(base, axis, (((((f32)(i + 1)) / ((f32)RAD_PARTS)) * M_PI) * 2.000000f));
    for (u32 j = 0; j < LENGTH_PARTS; j+=1) {
      std_vec_Vec3__0 t0 = std_vec_Vec3__0_mults(dir_delta, ((f32)(j + 0)));
      std_vec_Vec3__0 t1 = std_vec_Vec3__0_mults(dir_delta, ((f32)(j + 1)));
      std_vec_Vec3__0 v00 = std_vec_Vec3__0_add(std_vec_Vec3__0_add(p0_w, s0), t0);
      std_vec_Vec3__0 v01 = std_vec_Vec3__0_add(std_vec_Vec3__0_add(p0_w, s0), t1);
      std_vec_Vec3__0 v10 = std_vec_Vec3__0_add(std_vec_Vec3__0_add(p0_w, s1), t0);
      std_vec_Vec3__0 v11 = std_vec_Vec3__0_add(std_vec_Vec3__0_add(p0_w, s1), t1);
      simple_tri.fn(simple_tri._C, v00, v10, v11);
      simple_tri.fn(simple_tri._C, v00, v11, v01);
    }
  }
}

void draw_line_clipped(std_vec_Vec3__0 p0_w, std_vec_Vec3__0 p1_w, std_image_Color color, bool ignore_z) {
  std_vec_Vec3__0 p0_c = std_matrix_Matrix4f_mulv(camera_transform, p0_w);
  std_vec_Vec3__0 p1_c = std_matrix_Matrix4f_mulv(camera_transform, p1_w);
  i32 count = (((i32)(p0_c.z < MIN_CLIP)) + ((i32)(p1_c.z < MIN_CLIP)));
  switch (count) {
    case 0: {
      std_vec_Vec2__3 p0 = camera_to_screen(p0_c);
      std_vec_Vec2__3 p1 = camera_to_screen(p1_c);
      draw_line_z(p0, p1, p0_c.z, p1_c.z, color, ignore_z);
    } break;
    case 1: {
      if (p1_c.z < p0_c.z) {
        std_vec_Vec3__0 tmp = p1_c;
        p1_c=p0_c;
        p0_c=tmp;
      }
      f32 t = ((MIN_CLIP - p0_c.z) / (p1_c.z - p0_c.z));
      std_vec_Vec3__0 n0 = interp_vec(p0_c, p1_c, t);
      std_vec_Vec2__3 p0 = camera_to_screen(p1_c);
      std_vec_Vec2__3 p1 = camera_to_screen(n0);
      draw_line_z(p0, p1, p1_c.z, n0.z, color, ignore_z);
    } break;
    case 2: {
    } break;
    default: {
      if(!(false)) { ae_assert_fail("src/main.oc:541:24: Assertion failed: `false`", "unreachable"); exit(1); }
    } break;
  }
}

void draw_line_z(std_vec_Vec2__3 p1, std_vec_Vec2__3 p2, f32 z1, f32 z2, std_image_Color color, bool ignore_z) {
  f32 x1 = ((f32)p1.x);
  f32 y1 = ((f32)p1.y);
  f32 x2 = ((f32)p2.x);
  f32 y2 = ((f32)p2.y);
  f32 dx = (x2 - x1);
  f32 dy = (y2 - y1);
  f32 dz = (z2 - z1);
  f32 xt;
  f32 yt;
  f32 zt;
  if (fabsf(dx) >= fabsf(dy)) {
    if (x2 < x1) {
      xt=x1;
      x1=x2;
      x2=xt;
      yt=y1;
      y1=y2;
      y2=yt;
      zt=z1;
      z1=z2;
      z2=zt;
    }
    f32 y = y1;
    f32 z = z1;
    f32 y_inc = ((y2 - y1) / (x2 - x1));
    f32 z_inc = ((z2 - z1) / (x2 - x1));
    for (f32 x = x1; x <= x2; x+=1.000000f) {
      if (((0 <= ((u32)x)) && (((u32)x) < image->width)) && ((0 <= ((u32)y)) && (((u32)y) < image->height))) {
        if (ignore_z || src_zbuffer_ZBuffer_put_if_closer(zbuffer, ((u32)x), ((u32)y), z)) {
          std_image_Image_set(image, ((u32)x), ((u32)y), color);
        }
      }
      y+=y_inc;
      z+=z_inc;
    }
  } else {
    if (y2 < y1) {
      xt=x1;
      x1=x2;
      x2=xt;
      yt=y1;
      y1=y2;
      y2=yt;
      zt=z1;
      z1=z2;
      z2=zt;
    }
    f32 x = x1;
    f32 z = z1;
    f32 x_inc = ((x2 - x1) / (y2 - y1));
    f32 z_inc = ((z2 - z1) / (y2 - y1));
    for (f32 y = y1; y <= y2; y+=1.000000f) {
      if (((0 <= ((u32)x)) && (((u32)x) < image->width)) && ((0 <= ((u32)y)) && (((u32)y) < image->height))) {
        if (ignore_z || src_zbuffer_ZBuffer_put_if_closer(zbuffer, ((u32)x), ((u32)y), z)) {
          std_image_Image_set(image, ((u32)x), ((u32)y), color);
        }
      }
      x+=x_inc;
      z+=z_inc;
    }
  }
}

void draw_bounds_projected(src_bounds_Bounds bounds, std_image_Color color, bool thick) {
  std_vec_Vec3__0 min = bounds.min;
  std_vec_Vec3__0 max = bounds.max;
  std_vec_Vec3__0 C[8] = {(std_vec_Vec3__0){.x=min.x, .y=min.y, .z=min.z}, (std_vec_Vec3__0){.x=max.x, .y=min.y, .z=min.z}, (std_vec_Vec3__0){.x=max.x, .y=max.y, .z=min.z}, (std_vec_Vec3__0){.x=min.x, .y=max.y, .z=min.z}, (std_vec_Vec3__0){.x=min.x, .y=min.y, .z=max.z}, (std_vec_Vec3__0){.x=max.x, .y=min.y, .z=max.z}, (std_vec_Vec3__0){.x=max.x, .y=max.y, .z=max.z}, (std_vec_Vec3__0){.x=min.x, .y=max.y, .z=max.z}};
  f32 thickness = 0.010000f;
  _ClosureTy_21 do_draw = ({draw_bounds_projected__Closure_16Ctx *_C76 = alloca(sizeof(draw_bounds_projected__Closure_16Ctx));_C76->color = &color;_C76->thick = &thick;_C76->thickness = &thickness;_ClosureTy_21 _ci77 = {._C=_C76, .fn=&draw_bounds_projected__Closure_16};_ci77;});
  do_draw.fn(do_draw._C, C[0], C[1]);
  do_draw.fn(do_draw._C, C[1], C[2]);
  do_draw.fn(do_draw._C, C[2], C[3]);
  do_draw.fn(do_draw._C, C[3], C[0]);
  do_draw.fn(do_draw._C, C[4], C[5]);
  do_draw.fn(do_draw._C, C[5], C[6]);
  do_draw.fn(do_draw._C, C[6], C[7]);
  do_draw.fn(do_draw._C, C[7], C[4]);
  do_draw.fn(do_draw._C, C[0], C[4]);
  do_draw.fn(do_draw._C, C[1], C[5]);
  do_draw.fn(do_draw._C, C[2], C[6]);
  do_draw.fn(do_draw._C, C[3], C[7]);
}

void draw_bvh(src_bvh_BVH__0 *root, u32 depth) {
  if (depth > (depth_limit - 1)) {
    return;
  }
  if (depth==(depth_limit - 1)) {
    draw_bounds_projected(root->bounds, (std_image_Color){.r=((u8)0), .g=((u8)255), .b=((u8)0)}, false);
  }
  if (!(root->is_leaf)) {
    draw_bvh(root->l, (depth + 1));
    draw_bvh(root->r, (depth + 1));
  }
}

void draw_ray(void) {
  f32 ray_length = 20.000000f;
  std_vec_Vec3__0 start = ray.pos;
  std_vec_Vec3__0 end = src_ray_Ray_at(ray, ray_length);
  draw_line_clipped_thick(start, end, (std_image_Color){.r=((u8)0), .g=((u8)0), .b=((u8)255)}, 0.020000f);
}

void draw_hit_nodes(void) {
  for (std_vector_Iterator__2 _i5 = std_vector_Vector__2_iter(hit_nodes); std_vector_Iterator__2_has_value(&_i5); std_vector_Iterator__2_next(&_i5)) {
    src_bvh_BVH__0 *node = std_vector_Iterator__2_cur(&_i5);
    {
      draw_bounds_projected(node->bounds, (std_image_Color){.r=((u8)255), .g=((u8)0), .b=((u8)0)}, true);
    }
  }
}

i32 main(i32 argc, char **argv) {
  std_argparse_Parser parser = std_argparse_Parser_make("render3d");
  char **model = std_argparse_Parser_add_str(&parser, "-o", "./assets/dragon.obj", false, "Path to the .obj file");
  char **res = std_argparse_Parser_add_str(&parser, "-r", "960x540", false, "Render resolution");
  bool *opt_bf_cull = std_argparse_Parser_add_bool(&parser, "-b", std_argparse_BoolAction_StoreFalse, "Backface culling");
  std_argparse_Parser_parse(&parser, argc, argv, true);
  std_sv_SV res_sv = std_sv_SV_from_str((*res));
  u32 width = std_sv_SV_chop_u32(&res_sv);
  u32 height = ({u32 __yv_78;
    if (std_sv_SV_is_empty(&res_sv)) {
      __yv_78 = width;
      goto _l___yv_78;
    } else {
      std_sv_SV_chop_left(&res_sv, 1);
      __yv_78 = std_sv_SV_chop_u32(&res_sv);
      goto _l___yv_78;
    }

_l___yv_78:
  __yv_78;});
  backface_culling=(*opt_bf_cull);
  aspect_ratio=(std_vec_Vec2__1){.x=(((f32)width) / ((f32)height)), .y=1.000000f};
  size_f=(std_vec_Vec2__1){.x=((f32)width), .y=((f32)height)};
  image=std_image_Image_new(width, height);
  zbuffer=src_zbuffer_ZBuffer_new(width, height);
  light_dir=std_vec_Vec3__0_normalized((std_vec_Vec3__0){.x=1.000000f, .y=-1.000000f, .z=0.000000f});
  camera_pos=(std_vec_Vec3__0){.x=0.000000f, .y=2.000000f, .z=-4.000000f};
  camera_dir=(std_vec_Vec3__0){.x=0.000000f, .y=0.000000f, .z=1.000000f};
  camera_up=(std_vec_Vec3__0){.x=0.000000f, .y=1.000000f, .z=0.000000f};
  update_camera(&camera_pos, &camera_dir);
  std_image_Color color = (std_image_Color){.r=((u8)255), .g=((u8)0), .b=((u8)0)};
  Mesh mesh = Mesh_from_obj((*model));
  bvh=src_bvh_BVH__0_create(mesh.triangles);
  hit_nodes=({
    std_vector_Vector__2 *_vc79 = std_vector_Vector__2_new(8);
    _vc79;});
  ray=(src_ray_Ray){.pos=(std_vec_Vec3__0){.x=0.000000f, .y=2.000000f, .z=-4.000000f}, .dir=(std_vec_Vec3__0){.x=0.000000f, .y=0.000000f, .z=1.000000f}};
  src_bvh_BVH__0_hit(bvh, &ray, hit_nodes);
  run_ui(&mesh);
}

src_zbuffer_ZBuffer *src_zbuffer_ZBuffer_new(u32 w, u32 h) {
  u32 size = (w * h);
  f32 *data = std_mem_alloc__14((w * h));
  for (u32 i = 0; i < size; i+=1) {
    data[i]=f32_inf();
  }
  return ({src_zbuffer_ZBuffer *_new_80 = std_mem_state_alloc_fn(std_mem_state_allocator, sizeof(src_zbuffer_ZBuffer)); *_new_80 = (src_zbuffer_ZBuffer){.width=w, .height=h, .data=data}; _new_80; });
}

void src_zbuffer_ZBuffer_clear(src_zbuffer_ZBuffer *this) {
  u32 size = (this->width * this->height);
  for (u32 i = 0; i < size; i+=1) {
    this->data[i]=f32_inf();
  }
}

bool src_zbuffer_ZBuffer_put_if_closer(src_zbuffer_ZBuffer *this, u32 x, u32 y, f32 z) {
  i32 idx = ((i32)((y * this->width) + x));
  if (z < this->data[idx]) {
    this->data[idx]=z;
    return true;
  }
  return false;
}

std_vec_Vec3__0 src_ray_Ray_at(src_ray_Ray this, f32 t) {
  return std_vec_Vec3__0_add(this.pos, std_vec_Vec3__0_multrs(t, this.dir));
}

Vertex from_obj__Closure_0(void *__C, std_sv_SV *line) {
  from_obj__Closure_0Ctx *_C = (from_obj__Closure_0Ctx *)__C;
{
  std_sv_SV part = std_sv_SV_chop_by_delim(line, ' ');
  std_vec_Vec3__0 pos = std_vector_Vector__4_at((*_C->vectors), (std_sv_SV_chop_u32(&part) - 1));
  std_sv_SV_chop_left(&part, 1);
  std_vec_Vec2__1 texcoord = std_vector_Vector__5_at((*_C->textures), (std_sv_SV_chop_u32(&part) - 1));
  std_sv_SV_chop_left(&part, 1);
  std_vec_Vec3__0 normal = std_vector_Vector__4_at((*_C->normals), (std_sv_SV_chop_u32(&part) - 1));
  std_sv_SV_trim(line);
  return (Vertex){.pos=pos, .tex=texcoord, .nor=normal};
}
}

void run_ui__Closure_1(void *__C, i32 dx, i32 dy, f32 sensitivity) {
  run_ui__Closure_1Ctx *_C = (run_ui__Closure_1Ctx *)__C;
{
  if (dx==0 && dy==0) {
    return;
  }
  f32 yaw_rad = ((((f32)dx) * sensitivity) * (*_C->dtime));
  f32 pitch_rad = ((((f32)dy) * sensitivity) * (*_C->dtime));
  camera_dir=rotate_vector(camera_dir, camera_up, yaw_rad);
  std_vec_Vec3__0 right = std_vec_Vec3__0_normalized(std_vec_Vec3__0_cross(camera_dir, camera_up));
  std_vec_Vec3__0 new_dir_after_pitch = rotate_vector(camera_dir, right, pitch_rad);
  if (fabsf(std_vec_Vec3__0_dot(new_dir_after_pitch, camera_up)) < 0.995000f) {
    camera_dir=new_dir_after_pitch;
  }
  update_camera(&camera_pos, &camera_dir);
}
}

void run_ui__Closure_2(void *__C) {
  run_ui__Closure_2Ctx *_C = (run_ui__Closure_2Ctx *)__C;
{
  camera_pos=std_vec_Vec3__0_add(camera_pos, std_vec_Vec3__0_mults(std_vec_Vec3__0_mults(camera_dir, (*_C->dtime)), (*_C->MOVE_SENSITIVITY)));
  update_camera(&camera_pos, &camera_dir);
}
}

void run_ui__Closure_3(void *__C) {
  run_ui__Closure_3Ctx *_C = (run_ui__Closure_3Ctx *)__C;
{
  camera_pos=std_vec_Vec3__0_sub(camera_pos, std_vec_Vec3__0_mults(std_vec_Vec3__0_mults(camera_dir, (*_C->dtime)), (*_C->MOVE_SENSITIVITY)));
  update_camera(&camera_pos, &camera_dir);
}
}

void run_ui__Closure_4(void *__C) {
  run_ui__Closure_4Ctx *_C = (run_ui__Closure_4Ctx *)__C;
{
  std_vec_Vec3__0 delta = std_vec_Vec3__0_mults(std_vec_Vec3__0_mults(std_vec_Vec3__0_normalized(std_vec_Vec3__0_cross(camera_dir, (std_vec_Vec3__0){.x=0.000000f, .y=1.000000f, .z=0.000000f})), (*_C->dtime)), (*_C->MOVE_SENSITIVITY));
  camera_pos=std_vec_Vec3__0_add(camera_pos, delta);
  update_camera(&camera_pos, &camera_dir);
}
}

void run_ui__Closure_5(void *__C) {
  run_ui__Closure_5Ctx *_C = (run_ui__Closure_5Ctx *)__C;
{
  std_vec_Vec3__0 delta = std_vec_Vec3__0_mults(std_vec_Vec3__0_mults(std_vec_Vec3__0_normalized(std_vec_Vec3__0_cross(camera_dir, (std_vec_Vec3__0){.x=0.000000f, .y=1.000000f, .z=0.000000f})), (*_C->dtime)), (*_C->MOVE_SENSITIVITY));
  camera_pos=std_vec_Vec3__0_sub(camera_pos, delta);
  update_camera(&camera_pos, &camera_dir);
}
}

void run_ui__Closure_6(void *__C) {
  run_ui__Closure_6Ctx *_C = (run_ui__Closure_6Ctx *)__C;
{
  camera_pos=std_vec_Vec3__0_add(camera_pos, std_vec_Vec3__0_mults(std_vec_Vec3__0_mults(camera_up, (*_C->dtime)), (*_C->MOVE_SENSITIVITY)));
  update_camera(&camera_pos, &camera_dir);
}
}

void run_ui__Closure_7(void *__C) {
  run_ui__Closure_7Ctx *_C = (run_ui__Closure_7Ctx *)__C;
{
  camera_pos=std_vec_Vec3__0_sub(camera_pos, std_vec_Vec3__0_mults(std_vec_Vec3__0_mults(camera_up, (*_C->dtime)), (*_C->MOVE_SENSITIVITY)));
  update_camera(&camera_pos, &camera_dir);
}
}

void run_ui__Closure_8(void *__C) {
  run_ui__Closure_8Ctx *_C = (run_ui__Closure_8Ctx *)__C;
{
    focal_length*=1.100000f;
}
}

void run_ui__Closure_9(void *__C) {
  run_ui__Closure_9Ctx *_C = (run_ui__Closure_9Ctx *)__C;
{
    focal_length/=1.100000f;
}
}

void run_ui__Closure_10(void *__C) {
  run_ui__Closure_10Ctx *_C = (run_ui__Closure_10Ctx *)__C;
{
    (*_C->rotate_camera).fn((*_C->rotate_camera)._C, 0, 1, (*_C->KEYBOARD_LOOK_SENSITIVITY));
}
}

void run_ui__Closure_11(void *__C) {
  run_ui__Closure_11Ctx *_C = (run_ui__Closure_11Ctx *)__C;
{
    (*_C->rotate_camera).fn((*_C->rotate_camera)._C, 0, -1, (*_C->KEYBOARD_LOOK_SENSITIVITY));
}
}

void run_ui__Closure_12(void *__C) {
  run_ui__Closure_12Ctx *_C = (run_ui__Closure_12Ctx *)__C;
{
    (*_C->rotate_camera).fn((*_C->rotate_camera)._C, -1, 0, (*_C->KEYBOARD_LOOK_SENSITIVITY));
}
}

void run_ui__Closure_13(void *__C) {
  run_ui__Closure_13Ctx *_C = (run_ui__Closure_13Ctx *)__C;
{
    (*_C->rotate_camera).fn((*_C->rotate_camera)._C, 1, 0, (*_C->KEYBOARD_LOOK_SENSITIVITY));
}
}

void run_ui__Closure_14(void *__C) {
  run_ui__Closure_14Ctx *_C = (run_ui__Closure_14Ctx *)__C;
{
  std_og_quit();
  exit(0);
}
}

void draw_line_clipped_thick__Closure_15(void *__C, std_vec_Vec3__0 p0, std_vec_Vec3__0 p1, std_vec_Vec3__0 p2) {
  draw_line_clipped_thick__Closure_15Ctx *_C = (draw_line_clipped_thick__Closure_15Ctx *)__C;
{
  std_vec_Vec3__0 norm = std_vec_Vec3__0_normalized(std_vec_Vec3__0_cross(std_vec_Vec3__0_sub(p1, p0), std_vec_Vec3__0_sub(p2, p0)));
  draw_triangle_clipped((Triangle){.p0=p0, .p1=p1, .p2=p2, .n0=norm, .n1=norm, .n2=norm});
}
}

void draw_bounds_projected__Closure_16(void *__C, std_vec_Vec3__0 p0, std_vec_Vec3__0 p1) {
  draw_bounds_projected__Closure_16Ctx *_C = (draw_bounds_projected__Closure_16Ctx *)__C;
{
  if ((*_C->thick)) {
    draw_line_clipped_thick(p0, p1, (*_C->color), (*_C->thickness));
  } else {
    draw_line_clipped(p0, p1, (*_C->color), false);
  }
}
}

void std_argparse_usage_and_exit__Closure_21(void *__C, std_argparse_Arg *arg) {
  std_argparse_usage_and_exit__Closure_21Ctx *_C = (std_argparse_usage_and_exit__Closure_21Ctx *)__C;
{
  printf("    %s%*s  %s%s""\n", arg->flags_display, ((i32)((*_C->max_len) - strlen(arg->flags_display))), "", arg->help, (arg->required ? std_format(" (%s, required)", std_argparse_ArgType_dbg(arg->type)) : std_format(" (%s)", std_argparse_ArgType_dbg(arg->type))));
}
}

bool src_bvh_split_SAH__Closure_22(void *__C, Triangle a) {
  src_bvh_split_SAH__Closure_22Ctx *_C = (src_bvh_split_SAH__Closure_22Ctx *)__C;
{
  std_vec_Vec3__0 off = src_bounds_Bounds_offset(&(*_C->bounds), src_bounds_Bounds_centroid(Triangle_bounds(a)));
  u32 bucket = ((u32)(((f32)src_bvh_NUM_BUCKETS) * std_vec_Vec3__0_index(off, (*_C->axis))));
  if (bucket==src_bvh_NUM_BUCKETS) {
    bucket=(src_bvh_NUM_BUCKETS - 1);
  }
  return bucket <= (*_C->min_bucket);
}
}

i8 src_bvh_split_equal__Closure_23(void *__C, Triangle a, Triangle b) {
  src_bvh_split_equal__Closure_23Ctx *_C = (src_bvh_split_equal__Closure_23Ctx *)__C;
{
  f32 ka = std_vec_Vec3__0_index(std_vec_Vec3__0_add(Triangle_bounds(a).min, Triangle_bounds(a).max), (*_C->axis));
  f32 kb = std_vec_Vec3__0_index(std_vec_Vec3__0_add(Triangle_bounds(b).min, Triangle_bounds(b).max), (*_C->axis));
  return f32_compare(ka, kb);
}
}

