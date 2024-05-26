// Copyright 2024-03-31 22:05:05 Lapwell/Byron.c. All rights reserved

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <time.h>

using std::string, std::endl, std::cout, std::cin;

char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
char nums[11] = "0123456789";

char getInput(char guessed[]) {
  char input;
  cout << "Input Guess: ";
  cin >> input;
  if (sizeof(input) > 1) {cout << "Too Many Chars!";}
  for (int i = 0; i < int(strlen(guessed)); i++) {
    if (input == nums[i]) {
      cout << "No Numbers!" << endl;
      getInput(guessed);
    }
    if (input == guessed[i]) {
      cout << "Already Guessed! Try Again..." << endl;
      getInput(guessed);
    }
  }
  return input;
}

// This function will generate a string that shows the correctly guessed letters
// in the correct placement. EG: PA__I_LE will be returned if the word is
// particle.
void generateDisplayWord(string word, char guessed[]) {
  string displayWord = "";
  for (size_t i = 0; i < word.length(); i++) {
    if (word.length() == 0) {
      break;
    }
    displayWord.push_back('_');
    for (int x = 0; x < int(strlen(guessed)); x++) {
      if (guessed[x] == word[i]) {
        displayWord.pop_back();
        displayWord.push_back(guessed[x]);
        continue;
      }
    }
  }
   cout << "Display Word: " << displayWord << endl;
}

int checkGuess(string word, char guessed[]) {

}

void printHangman(int misses) {
  switch (misses) {
  case 0:
    cout << "No Misses, nice!" << endl;
    break;
  case 1:
    cout << " 0" << endl;
    cout << "One miss!" << endl;
    break;
  case 2:
    cout << " 0" << endl;
    cout << " |" << endl;
    cout << "Two misses!" << endl;
    break;
  case 3:
    cout << "  0" << endl;
    cout << " /|\\" << endl;
    cout << "Three misses!" << endl;
    break;
  case 4:
    cout << " 0" << endl;
    cout << "/|\\" << endl;
    cout << " |" << endl;
    cout << "Four misses!" << endl;
    break;
  case 5:
    cout << " 0" << endl;
    cout << "/|\\" << endl;
    cout << " |" << endl;
    cout << "/ \\" << endl << endl;
    cout << "Five misses!" << endl;
    cout << "GAME OVER" << endl;
    exit(0);
    break;
  }
}

int main() {
  cin.ignore(1, '\n'); // This line tells cin to ignore any input after the initial input.
  string wordList[16] = {
      "inquisitive", "program",      "coding",  "particle",
      "freshwater",  "helldiver",    "python",  "stellarator",
      "factorio",    "assembly",     "silicon", "micrometer",
      "astronomy",   "astrophysics", "physics", "quantum"};
  srand(time(NULL));
  // sizeof() is divided by 32 because sizeof() returns the memory size.
  // Dividing by 32 (length of string type), we get the number of elements.
  int wordListSize = sizeof(wordList) / 32;
  string word = wordList[rand() % wordListSize];
  char guessedChars[26]; // All the guessed letters
  int misses = 0;
  int iter = 0;
  while (iter < 26) {
    cout << "guessed: " << guessedChars << endl;
    cout << "word: " << word << endl;
    char guess = getInput(guessedChars);
    guessedChars[iter] = guess;
    misses = checkGuess(word, guessedChars);
    generateDisplayWord(word, guessedChars);
    printHangman(misses);
    cout << endl << "----------------" << endl;
    iter++;
  }
  return 0;
}
