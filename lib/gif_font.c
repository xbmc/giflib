/*****************************************************************************
 
gif_font.c - utility font handling and simple drawing for the GIF library
 
****************************************************************************/

#include <string.h>

#include "gif_lib.h"

/*****************************************************************************
 * Ascii 8 by 8 regular font - only first 128 characters are supported.
 ****************************************************************************/

/*
 * Each array entry holds the bits for 8 horizontal scan lines, topmost
 * first.  The most significant bit of each constant is the leftmost bit of
 * the scan line.
 */
/*@+charint@*/
const unsigned char AsciiTable[][GIF_FONT_WIDTH] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /* Ascii 0 */
    {0x3c, 0x42, 0xa5, 0x81, 0xbd, 0x42, 0x3c, 0x00},    /* Ascii 1 */
    {0x3c, 0x7e, 0xdb, 0xff, 0xc3, 0x7e, 0x3c, 0x00},    /* Ascii 2 */
    {0x00, 0xee, 0xfe, 0xfe, 0x7c, 0x38, 0x10, 0x00},    /* Ascii 3 */
    {0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x38, 0x10, 0x00},    /* Ascii 4 */
    {0x00, 0x3c, 0x18, 0xff, 0xff, 0x08, 0x18, 0x00},    /* Ascii 5 */
    {0x10, 0x38, 0x7c, 0xfe, 0xfe, 0x10, 0x38, 0x00},    /* Ascii 6 */
    {0x00, 0x00, 0x18, 0x3c, 0x18, 0x00, 0x00, 0x00},    /* Ascii 7 */
    {0xff, 0xff, 0xe7, 0xc3, 0xe7, 0xff, 0xff, 0xff},    /* Ascii 8 */
    {0x00, 0x3c, 0x42, 0x81, 0x81, 0x42, 0x3c, 0x00},    /* Ascii 9 */
    {0xff, 0xc3, 0xbd, 0x7e, 0x7e, 0xbd, 0xc3, 0xff},    /* Ascii 10 */
    {0x1f, 0x07, 0x0d, 0x7c, 0xc6, 0xc6, 0x7c, 0x00},    /* Ascii 11 */
    {0x00, 0x7e, 0xc3, 0xc3, 0x7e, 0x18, 0x7e, 0x18},    /* Ascii 12 */
    {0x04, 0x06, 0x07, 0x04, 0x04, 0xfc, 0xf8, 0x00},    /* Ascii 13 */
    {0x0c, 0x0a, 0x0d, 0x0b, 0xf9, 0xf9, 0x1f, 0x1f},    /* Ascii 14 */
    {0x00, 0x92, 0x7c, 0x44, 0xc6, 0x7c, 0x92, 0x00},    /* Ascii 15 */
    {0x00, 0x00, 0x60, 0x78, 0x7e, 0x78, 0x60, 0x00},    /* Ascii 16 */
    {0x00, 0x00, 0x06, 0x1e, 0x7e, 0x1e, 0x06, 0x00},    /* Ascii 17 */
    {0x18, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x18},    /* Ascii 18 */
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x66, 0x00},    /* Ascii 19 */
    {0xff, 0xb6, 0x76, 0x36, 0x36, 0x36, 0x36, 0x00},    /* Ascii 20 */
    {0x7e, 0xc1, 0xdc, 0x22, 0x22, 0x1f, 0x83, 0x7e},    /* Ascii 21 */
    {0x00, 0x00, 0x00, 0x7e, 0x7e, 0x00, 0x00, 0x00},    /* Ascii 22 */
    {0x18, 0x7e, 0x18, 0x18, 0x7e, 0x18, 0x00, 0xff},    /* Ascii 23 */
    {0x18, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00},    /* Ascii 24 */
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x18, 0x00},    /* Ascii 25 */
    {0x00, 0x04, 0x06, 0xff, 0x06, 0x04, 0x00, 0x00},    /* Ascii 26 */
    {0x00, 0x20, 0x60, 0xff, 0x60, 0x20, 0x00, 0x00},    /* Ascii 27 */
    {0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xff, 0x00},    /* Ascii 28 */
    {0x00, 0x24, 0x66, 0xff, 0x66, 0x24, 0x00, 0x00},    /* Ascii 29 */
    {0x00, 0x00, 0x10, 0x38, 0x7c, 0xfe, 0x00, 0x00},    /* Ascii 30 */
    {0x00, 0x00, 0x00, 0xfe, 0x7c, 0x38, 0x10, 0x00},    /* Ascii 31 */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /* */
    {0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x30, 0x00},    /* ! */
    {0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /* " */
    {0x6c, 0x6c, 0xfe, 0x6c, 0xfe, 0x6c, 0x6c, 0x00},    /* # */
    {0x10, 0x7c, 0xd2, 0x7c, 0x86, 0x7c, 0x10, 0x00},    /* $ */
    {0xf0, 0x96, 0xfc, 0x18, 0x3e, 0x72, 0xde, 0x00},    /* % */
    {0x30, 0x48, 0x30, 0x78, 0xce, 0xcc, 0x78, 0x00},    /* & */
    {0x0c, 0x0c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},    /* ' */
    {0x10, 0x60, 0xc0, 0xc0, 0xc0, 0x60, 0x10, 0x00},    /* ( */
    {0x10, 0x0c, 0x06, 0x06, 0x06, 0x0c, 0x10, 0x00},    /* ) */
    {0x00, 0x54, 0x38, 0xfe, 0x38, 0x54, 0x00, 0x00},    /* * */
    {0x00, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00},    /* + */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x70},    /* , */
    {0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00},    /* - */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00},    /* . */
    {0x02, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x00},    /* / */
    {0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00},    /* 0 */
    {0x18, 0x38, 0x78, 0x18, 0x18, 0x18, 0x3c, 0x00},    /* 1 */
    {0x7c, 0xc6, 0x06, 0x0c, 0x30, 0x60, 0xfe, 0x00},    /* 2 */
    {0x7c, 0xc6, 0x06, 0x3c, 0x06, 0xc6, 0x7c, 0x00},    /* 3 */
    {0x0e, 0x1e, 0x36, 0x66, 0xfe, 0x06, 0x06, 0x00},    /* 4 */
    {0xfe, 0xc0, 0xc0, 0xfc, 0x06, 0x06, 0xfc, 0x00},    /* 5 */
    {0x7c, 0xc6, 0xc0, 0xfc, 0xc6, 0xc6, 0x7c, 0x00},    /* 6 */
    {0xfe, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x60, 0x00},    /* 7 */
    {0x7c, 0xc6, 0xc6, 0x7c, 0xc6, 0xc6, 0x7c, 0x00},    /* 8 */
    {0x7c, 0xc6, 0xc6, 0x7e, 0x06, 0xc6, 0x7c, 0x00},    /* 9 */
    {0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00},    /* : */
    {0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x20, 0x00},    /* }, */
    {0x00, 0x1c, 0x30, 0x60, 0x30, 0x1c, 0x00, 0x00},    /* < */
    {0x00, 0x00, 0x7e, 0x00, 0x7e, 0x00, 0x00, 0x00},    /* = */
    {0x00, 0x70, 0x18, 0x0c, 0x18, 0x70, 0x00, 0x00},    /* > */
    {0x7c, 0xc6, 0x0c, 0x18, 0x30, 0x00, 0x30, 0x00},    /* ? */
    {0x7c, 0x82, 0x9a, 0xaa, 0xaa, 0x9e, 0x7c, 0x00},    /* @ */
    {0x38, 0x6c, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0x00},    /* A */
    {0xfc, 0xc6, 0xc6, 0xfc, 0xc6, 0xc6, 0xfc, 0x00},    /* B */
    {0x7c, 0xc6, 0xc6, 0xc0, 0xc0, 0xc6, 0x7c, 0x00},    /* C */
    {0xf8, 0xcc, 0xc6, 0xc6, 0xc6, 0xcc, 0xf8, 0x00},    /* D */
    {0xfe, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xfe, 0x00},    /* E */
    {0xfe, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0x00},    /* F */
    {0x7c, 0xc6, 0xc0, 0xce, 0xc6, 0xc6, 0x7e, 0x00},    /* G */
    {0xc6, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0x00},    /* H */
    {0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00},    /* I */
    {0x1e, 0x06, 0x06, 0x06, 0xc6, 0xc6, 0x7c, 0x00},    /* J */
    {0xc6, 0xcc, 0xd8, 0xf0, 0xd8, 0xcc, 0xc6, 0x00},    /* K */
    {0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0x00},    /* L */
    {0xc6, 0xee, 0xfe, 0xd6, 0xc6, 0xc6, 0xc6, 0x00},    /* M */
    {0xc6, 0xe6, 0xf6, 0xde, 0xce, 0xc6, 0xc6, 0x00},    /* N */
    {0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00},    /* O */
    {0xfc, 0xc6, 0xc6, 0xfc, 0xc0, 0xc0, 0xc0, 0x00},    /* P */
    {0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x06},    /* Q */
    {0xfc, 0xc6, 0xc6, 0xfc, 0xc6, 0xc6, 0xc6, 0x00},    /* R */
    {0x78, 0xcc, 0x60, 0x30, 0x18, 0xcc, 0x78, 0x00},    /* S */
    {0xfc, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00},    /* T */
    {0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00},    /* U */
    {0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00},    /* V */
    {0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xee, 0xc6, 0x00},    /* W */
    {0xc6, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0xc6, 0x00},    /* X */
    {0xc3, 0xc3, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x00},    /* Y */
    {0xfe, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0xfe, 0x00},    /* Z */
    {0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c, 0x00},    /* [ */
    {0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x00},    /* \ */
    {0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c, 0x00},    /* ] */
    {0x00, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00},    /* ^ */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff},    /* _ */
    {0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},    /* ` */
    {0x00, 0x00, 0x7c, 0x06, 0x7e, 0xc6, 0x7e, 0x00},    /* a */
    {0xc0, 0xc0, 0xfc, 0xc6, 0xc6, 0xe6, 0xdc, 0x00},    /* b */
    {0x00, 0x00, 0x7c, 0xc6, 0xc0, 0xc0, 0x7e, 0x00},    /* c */
    {0x06, 0x06, 0x7e, 0xc6, 0xc6, 0xce, 0x76, 0x00},    /* d */
    {0x00, 0x00, 0x7c, 0xc6, 0xfe, 0xc0, 0x7e, 0x00},    /* e */
    {0x1e, 0x30, 0x7c, 0x30, 0x30, 0x30, 0x30, 0x00},    /* f */
    {0x00, 0x00, 0x7e, 0xc6, 0xce, 0x76, 0x06, 0x7c},    /* g */
    {0xc0, 0xc0, 0xfc, 0xc6, 0xc6, 0xc6, 0xc6, 0x00},    /* */
    {0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x3c, 0x00},    /* i */
    {0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0xf0},    /* j */
    {0xc0, 0xc0, 0xcc, 0xd8, 0xf0, 0xd8, 0xcc, 0x00},    /* k */
    {0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00},    /* l */
    {0x00, 0x00, 0xcc, 0xfe, 0xd6, 0xc6, 0xc6, 0x00},    /* m */
    {0x00, 0x00, 0xfc, 0xc6, 0xc6, 0xc6, 0xc6, 0x00},    /* n */
    {0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0x7c, 0x00},    /* o */
    {0x00, 0x00, 0xfc, 0xc6, 0xc6, 0xe6, 0xdc, 0xc0},    /* p */
    {0x00, 0x00, 0x7e, 0xc6, 0xc6, 0xce, 0x76, 0x06},    /* q */
    {0x00, 0x00, 0x6e, 0x70, 0x60, 0x60, 0x60, 0x00},    /* r */
    {0x00, 0x00, 0x7c, 0xc0, 0x7c, 0x06, 0xfc, 0x00},    /* s */
    {0x30, 0x30, 0x7c, 0x30, 0x30, 0x30, 0x1c, 0x00},    /* t */
    {0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0x7e, 0x00},    /* u */
    {0x00, 0x00, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00},    /* v */
    {0x00, 0x00, 0xc6, 0xc6, 0xd6, 0xfe, 0x6c, 0x00},    /* w */
    {0x00, 0x00, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0x00},    /* x */
    {0x00, 0x00, 0xc6, 0xc6, 0xce, 0x76, 0x06, 0x7c},    /* y */
    {0x00, 0x00, 0xfc, 0x18, 0x30, 0x60, 0xfc, 0x00},    /* z */
    {0x0e, 0x18, 0x18, 0x70, 0x18, 0x18, 0x0e, 0x00},    /* { */
    {0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},    /* | */
    {0xe0, 0x30, 0x30, 0x1c, 0x30, 0x30, 0xe0, 0x00},    /* } */
    {0x00, 0x00, 0x70, 0x9a, 0x0e, 0x00, 0x00, 0x00},    /* ~ */
    {0x00, 0x00, 0x18, 0x3c, 0x66, 0xff, 0x00, 0x00}    /* Ascii 127 */
};
/*@=charint@*/

void
GifDrawText(SavedImage * Image,
         const int x,
         const int y,
         const char *legend,
         const int color) {

    int i, j;
    int base;
    const char *cp;

    for (i = 0; i < GIF_FONT_HEIGHT; i++) {
        base = Image->ImageDesc.Width * (y + i) + x;

        for (cp = legend; *cp; cp++)
            for (j = 0; j < GIF_FONT_WIDTH; j++) {
                if (AsciiTable[(short)(*cp)][i] & (1 << (GIF_FONT_WIDTH - j)))
                    Image->RasterBits[base] = color;
                base++;
            }
    }
}

void
GifDrawBox(SavedImage * Image,
        const int x,
        const int y,
        const int w,
        const int d,
        const int color) {

    int j, base = Image->ImageDesc.Width * y + x;

    for (j = 0; j < w; j++)
        Image->RasterBits[base + j] =
            Image->RasterBits[base + (d * Image->ImageDesc.Width) + j] = color;

    for (j = 0; j < d; j++)
        Image->RasterBits[base + j * Image->ImageDesc.Width] =
            Image->RasterBits[base + j * Image->ImageDesc.Width + w] = color;
}

void
GifDrawRectangle(SavedImage * Image,
              const int x,
              const int y,
              const int w,
              const int d,
              const int color) {

    unsigned char *bp = Image->RasterBits + Image->ImageDesc.Width * y + x;
    int i;

    for (i = 0; i < d; i++)
        memset(bp + (i * Image->ImageDesc.Width), color, (size_t)w);
}

void
GifDrawBoxedText(SavedImage * Image,
              const int x,
              const int y,
              const char *legend,
              const int border,
              const int bg,
              const int fg) {

    int i, j = 0, LineCount = 0, TextWidth = 0;
    const char *cp;

    /* compute size of text to box */
    for (cp = legend; *cp; cp++)
        if (*cp == '\r') {
            if (j > TextWidth)
                TextWidth = j;
            j = 0;
            LineCount++;
        } else if (*cp != '\t')
            ++j;
    LineCount++;    /* count last line */
    if (j > TextWidth)    /* last line might be longer than any previous */
        TextWidth = j;

    /* fill the box */
    GifDrawRectangle(Image, x + 1, y + 1,
                  border + TextWidth * GIF_FONT_WIDTH + border - 1,
                  border + LineCount * GIF_FONT_HEIGHT + border - 1, bg);

    /* draw the text */
    i = 0;
    cp = strtok((char *)legend, "\r\n");
    do {
        int leadspace = 0;

        if (cp[0] == '\t')
            leadspace = (TextWidth - strlen(++cp)) / 2;

        GifDrawText(Image, x + border + (leadspace * GIF_FONT_WIDTH),
                 y + border + (GIF_FONT_HEIGHT * i++), cp, fg);
        cp = strtok((char *)NULL, "\r\n");
    } while (cp);

    /* outline the box */
    GifDrawBox(Image, x, y, border + TextWidth * GIF_FONT_WIDTH + border,
            border + LineCount * GIF_FONT_HEIGHT + border, fg);
}
