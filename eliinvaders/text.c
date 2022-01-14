#include "myLib.h"
#include "text.h"
#include "font.h"

void drawChar3(int col, int row, char ch, unsigned short color) {

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 6; c++) {
            if (fontdata_6x8[48*ch + OFFSET(c, r, 6)]) {
                setPixel3(col+c, row+r, color);
            }
        }
    }
}

void drawString3(int col, int row, char *str, unsigned short color) {

    while(*str != '\0') {

        drawChar3(col, row, *str, color);
        col += 6;

        str++;
    }
}
