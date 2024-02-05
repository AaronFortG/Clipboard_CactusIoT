#include "clipboard_manager.h"
#include "../libraries/global_lib.h"

#define CLIPBOARD_TYPE_OPERATION "TYPE"
#define CLIPBOARD_SELECT_OPERATION "SELECT"
#define CLIPBOARD_MOVE_CURSOR_OPERATION "MOVE_CURSOR"
#define CLIPBOARD_COPY_OPERATION "COPY"
#define CLIPBOARD_PASTE_OPERATION "PASTE"
#define CLIPBOARD_EXIT_OPERATION "EXIT"

Clipboard CLIPBOARD_MANAGER_newClipboard() {

    // Initialize all the values from the data type.
    Clipboard clipboard = {
            .text = NULL,
            .selectionArea.startIndex = 0,
            .selectionArea.endIndex = 0,
            .selectionArea.selectedArea = false,
            .cursorPosition = 0,
            .copiedText.numCopiedText = 0,
            .copiedText.copiedTextArray = NULL
    };
    return clipboard;
}

void CLIPBOARD_MANAGER_freeClipboard(Clipboard* clipboard) {

    // Free all the memory used in the clipboard.
    for (int i = 0; i < clipboard->copiedText.numCopiedText; i++) {
        CopiedText* copiedText = &(clipboard->copiedText.copiedTextArray[i]);
        GLOBAL_freePointer((void **) &copiedText->text);
    }
    GLOBAL_freePointer((void **) &clipboard->copiedText.copiedTextArray);
    GLOBAL_freePointer((void **) &clipboard->text);
}

int CLIPBOARD_MANAGER_getSelectedOffset(Clipboard* clipboard) {
    return clipboard->selectionArea.endIndex - clipboard->selectionArea.startIndex + 1;
}

void CLIPBOARD_MANAGER_eraseSelectedText(Clipboard* clipboard) {
    size_t originalLength = strlen(clipboard->text);
    char shiftOffset = originalLength - clipboard->selectionArea.endIndex;

    // Remove the string between the start and end index (substring).
    char* startString = clipboard->text + clipboard->selectionArea.startIndex;
    char* endString = clipboard->text + clipboard->selectionArea.endIndex + 1;
    GLOBAL_printMessage("Start string: %s - End string: %s.\n", startString, endString);
    memmove(startString, endString, shiftOffset);

    // Erase the duplicated text (set it to '\0' chars).
    char selectionOffset = CLIPBOARD_MANAGER_getSelectedOffset(clipboard);
    int newLength = originalLength - selectionOffset;
    char duplicatedOffset = originalLength - newLength;
    memset(startString + shiftOffset, 0, duplicatedOffset);
    clipboard->cursorPosition = clipboard->selectionArea.startIndex;    // Update the cursor to be at the beginning of the selected text.
}

// Function to parse a string and convert it to the corresponding enum Operation.
ClipboardOperation CLIPBOARD_MANAGER_parseOperation(char* operationArgument) {
    ClipboardOperation clipboardOperation = { .operation = CLIPBOARD_INVALID_OPERATION };
    char* operationBuffer;
    STRINGS_separateWords(operationArgument, &operationBuffer, &clipboardOperation.operationText, CLIPBOARD_OPERATION_SEPARATOR);

    // Check what operationBuffer was typed in.
    if (strcmp(operationBuffer, CLIPBOARD_TYPE_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_TYPE;
    } else if (strcmp(operationBuffer, CLIPBOARD_SELECT_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_SELECT;
    } else if (strcmp(operationBuffer, CLIPBOARD_MOVE_CURSOR_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_MOVE_CURSOR;
    } else if (strcmp(operationBuffer, CLIPBOARD_COPY_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_COPY;
    } else if (strcmp(operationBuffer, CLIPBOARD_PASTE_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_PASTE;
    } else if (strcmp(operationBuffer, CLIPBOARD_EXIT_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_EXIT;
    } else {
        clipboardOperation.operation = CLIPBOARD_INVALID_OPERATION;
    }

    // Free the temp's operationBuffer malloc.
    GLOBAL_freePointer((void **) &operationBuffer);

    return clipboardOperation;
}