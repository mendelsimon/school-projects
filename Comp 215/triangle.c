#include <stdio.h>

#define PROMPT "Input the number of rows in the triangle > "

int get_input(int low, int high);
void draw_triangle(int height);

int main(void) {
  int height = get_input(1, 20);
  draw_triangle(height);
}

/* Get an integer input. It will keep prompting until the input is valid. Valid input 
   is input that is all digits which result in a number that is greater than or equal
   to the lower bound (low) and less than or equal to the upper bound (high). */
int get_input(int low, int high) {
  int input; // The input as an integer
  int valid; // Whether the input is valid
  printf(PROMPT);
  do {
    input = 0;
    valid = 1;
    char c = getchar();
    while(c != '\n') {
      input *= 10; // Shift the current input over one place
      input += c - '0'; // Add the new number
      if (c < '0' || c > '9') {
        valid = 0; // If the character is not a digit, it's invalid
      }
      c = getchar();
    }
    if (input > high || input < low) {
      valid = 0; // If the result is larger than the limit, it's invalid
    }
    if (!valid) {
      printf("Invalid input. Input must be a number from %d to %d (inclusive).\n%s",
             low, high, PROMPT);
    }
  } while (!valid); // Repeat until valid input
  return input;
}

/* Draws a hollow ASCII triangle of the specified height with spaces ( ) and asterisks (*) */
void draw_triangle(int height) {
  // Draw the top point
  for (int i = 0; i < height - 1; i++) {
    putchar(' ');
  }
  printf("*\n");
  if (height == 1) {
    return;
  }

  // Draw the body
  for (int line = height - 1; line > 1; line--) {
    // Draw the leading spaces
    for (int i = 0; i < line - 1; i++) {
      putchar(' ');
    }
    putchar('*');

    // Draw the middle spaces
    for (int i = 0; i < (height * 2) - (line * 2) - 1; i++) {
      putchar(' ');
    }
    printf("*\n");
  }

  // Draw the base
  for (int i = 0; i < (height * 2) - 1; i++) {
    putchar('*');
  }
}