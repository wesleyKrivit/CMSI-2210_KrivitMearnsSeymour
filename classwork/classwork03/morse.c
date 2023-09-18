/**
 * filename: morse.c
 * purpose: convert a word or phrase into Morse code
 * author: Jack Seymour
 * date: 2023-09-13
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define Morse code representations for each letter and digit
char* morseCode[] = {
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    "..-.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--..", // Z
    "-----", // 0
    ".----", // 1
    "..---", // 2
    "...--", // 3
    "....-", // 4
    ".....", // 5
    "-....", // 6
    "--...", // 7
    "---..", // 8
    "----."  // 9
};

void convertToMorse(const char* input) {
    for (int i = 0; input[i]; i++) {
        
        char c = toupper(input[i]); //capitalizes letter
        
        if (c >= 'A' && c <= 'Z') { //if alpha
            printf("%s ", morseCode[c - 'A']);
        } else if (c >= '0' && c <= '9') { //if numeric
            printf("%s ", morseCode[c - '0' + 26]);
        } else if (c == ' ') { //or if space
            printf("  "); // Double space
        }
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"word or phrase\"\n", argv[0]);
        return 1;
    }

    const char* input = argv[1];
    convertToMorse(input);

    return 0;
}
