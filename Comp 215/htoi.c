#include <stdio.h>
#include "htoi.h"

int main() {
    runTestCases();
}

/** Runs all the test cases */
void runTestCases() {
    // Test 0
    test("0", 0);
    test("0x0", 0);
    test("0X0", 0);
    // Test 1
    test("1", 1);
    test("0x1", 1);
    test("0X1", 1);
    // Test a single-digit number.
    test("4", 4);
    test("0x4", 4);
    test("0X4", 4);
    // Test a single-character number.
    test("d", 13);
    test("D", 13);
    test("0xd", 13);
    test("0xD", 13);
    test("0Xd", 13);
    test("0XD", 13);
    // Test a more complex number
    test("c25b", 49755);
    test("C25B", 49755);
    test("0xc25b", 49755);
    test("0Xc25b", 49755);
    test("0xC25b", 49755);
    test("0Xc25B", 49755);
    test("0xc25b", 49755);
    // Test invalid strings
    test("x0", -1);
    test("0x", -1);
    test("0x123g", -1);
    test("10x123", -1);
    test("x", -1);
    test("X", -1);
    test("", -1);
}

/**
 * Runs htoi() on the input and compares it to the expected result.
 * This prints output in the format:
  * "0x4 | PASSED | Expected: 4 | Actual  4"
 */
void test(char input[], int expected) {
    const char *results[] = {"FAILED", "PASSED"};
    int actual = htoi(input);
    int result = actual == expected;
    printf("%8s | %s | Expected: %6d | Actual: %6d\n", 
        input, results[result], expected, actual);
}

/** 
 * This function takes a hexadecimal string as input and returns the
 * integer representation of the string as an int. The string may start
 * with an optional "0x" or "0X". The only valid characters after that are
 * 0-9, a-f, and A-F.
 * If the string is invalid, -1 will be returned.
 */
int htoi(char s[]) {
    // If the string is empty, return -1.
    if (s[0] == '\0') { return -1; }
    // If the string has more than 2 chars, skip the optional 0x/0X.
    if (len(s) > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        s += 2;
    }

    //Initialize the sum
    int sum = 0;
    while (*s != '\0') { // For each letter in the string
        if (!isValid(*s)) { return -1; } // Return -1 if invalid
        sum *= 16;
        sum += charToInt(*s);
        s++;
    }
    return sum;
}

/** Get the length of a given string */
int len(char s[]) {
    int n = 0;
    while (s[n] != '\0') { n++; }
    return n;
}

/**
 * This function checks if a character is valid: If it's within 0-9, a-f, A-F.
 */
int isValid(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

/**
 * This function returns the decimal value of an ASCII hexadecimal character.
 * This function assumes that the character is valid (0-9, a-f, A-F).
 */
int charToInt(char c) { 
    if (c >= 'a') {
        return c - 'a' + 10;
    } else if (c >= 'A') {
        return c - 'A' + 10;
    }
    return c - '0';
}