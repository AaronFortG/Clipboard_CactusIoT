/**
 * @file clipboard_move_cursor.c
 * @author Aaron Fort Garcia
 * @date 4th February 2024.
 * @brief Clipboard's MOVE_CURSOR operation module.
 */
#include "clipboard_move_cursor.h"
#include "../../libraries/global_lib.h"

// Texts constants regarding clipboard's MOVE_CURSOR operation
#define CLIPBOARD_MOVE_CURSOR_POSITION_TEXT "Cursor is now placed in" BHWHT " position %d " COLOR_RESET "-> "

/*************************************************
* @brief Function to move the current position of the clipboard's cursor.
* @param  clipboard clipboard's variable that will have its cursor moved.
* @return ----.
**************************************************/
void CLIPBOARD_MOVE_CURSOR_moveCursor(Clipboard* clipboard, int offset) {
    // Erase the selected area in case there was one.
    clipboard->selectionArea.selectedArea = false;

    // Move the cursor based on the offset.
    clipboard->cursorPosition += offset;    // If positive offset, sum; if negative, subtract.

    // Check if the cursor is out of the boundaries (lower than zero or greater than the maximum = 50).
    if (clipboard->cursorPosition < 0) {
        clipboard->cursorPosition = 0;
    } else if (clipboard->cursorPosition > (int)strlen(clipboard->text)) {
        clipboard->cursorPosition = strlen(clipboard->text);
    }
    GLOBAL_printMessage(CLIPBOARD_MOVE_CURSOR_POSITION_TEXT, clipboard->cursorPosition);
    CLIPBOARD_MANAGER_printTextWithCursor(*clipboard);
}