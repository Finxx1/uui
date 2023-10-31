// SPDX-License-Identifier: Zlib
// This file is released under the Zlib/libpng license. See COPYING.txt in the root directory.
// UUI: Universal User Interface
// 2023-10-26 - Created

#ifndef _UUI_DEV
#define _UUI_DEV

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef UUI_NO_BOOL // Why do you have a different bool type anyway?
#include <stdbool.h>
#endif

typedef void* uui_window;


uui_window uui_make_window(void);
bool uui_title_window(uui_window window, char* txt);
bool uui_position_window(uui_window window, int x, int y);
bool uui_size_window(uui_window window, int w, int h);
bool uui_show_window(uui_window window);
bool uui_hide_window(uui_window window);
bool uui_make_topmost_window(uui_window window);
bool uui_make_bottommost_window(uui_window window);
bool uui_hide_console(void);
bool uui_show_console(void);
void uui_run(uui_window window);
void uui_run_async(uui_window window);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !_UUI_DEV