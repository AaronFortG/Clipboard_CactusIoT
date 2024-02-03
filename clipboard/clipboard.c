#include "../libraries/global_lib.h"
#include "clipboard.h"
#include "clipboard_operations.h"

#define CLIPBOARD_PROCESSING_OPERATIONS_TEXT "Processing %d operations...\n"
#define CLIPBOARD_NO_OPERATIONS_TEXT "There are no operations to process.\n"
#define CLIPBOARD_NEXT_OPERATION_TEXT "Type in the next operation: "
#define CLIPBOARD_EXIT_OPERATION_TEXT "Thanks for using this program!"

Clipboard CLIPBOARD_newClipboard() {
    Clipboard clipboard = { .text = "", .startIndex = 0, .endIndex = 0 };
    return clipboard;
}

void CLIPBOARD_doOperation(Clipboard* clipboard, ClipboardOperation operation) {
    clipboard->startIndex = 0;
    switch (operation) {
        case CLIPBOARD_TYPE:
            break;
        case CLIPBOARD_SELECT:
            break;
        case CLIPBOARD_MOVE_CURSOR:
            break;
        case CLIPBOARD_COPY:
            break;
        case CLIPBOARD_PASTE:
            break;
        case CLIPBOARD_EXIT:
            break;
        case CLIPBOARD_INVALID_OPERATION:
            break;
    }
}

void CLIPBOARD_startClipboard(int numOperations, char* operations[]) {
    Clipboard clipboard = CLIPBOARD_newClipboard();

    if (numOperations > 0) {
        GLOBAL_printMessage(CLIPBOARD_PROCESSING_OPERATIONS_TEXT);
    }
    else {
        GLOBAL_printMessage(CLIPBOARD_NO_OPERATIONS_TEXT);
    }

    // Do all the instructions passed as parameters to the program.
    for (int i = 0; i < numOperations; i++) {
        ClipboardOperation currentOperation = CLIPBOARD_parseOperation(operations[i]);
        CLIPBOARD_doOperation(&clipboard, currentOperation);
    }

    ClipboardOperation userOperation;
    do {
        char* bufferOperation = GLOBAL_readInput(CLIPBOARD_NEXT_OPERATION_TEXT);
        userOperation = CLIPBOARD_parseOperation(bufferOperation);
    } while (userOperation != CLIPBOARD_EXIT);

    GLOBAL_printMessage(CLIPBOARD_EXIT_OPERATION_TEXT);
}