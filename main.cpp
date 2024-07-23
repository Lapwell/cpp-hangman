// Copyright 2024-03-31 22:05:05 Lapwell/Byron.c. All rights reserved

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <time.h>

using std::string, std::endl, std::cout, std::cin, std::printf;

char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
char nums[11] = "0123456789";

char getInput(char guessed[]) {
  char input;
  cin.ignore(1, '\n');
  cout << "Input Guess: ";
  cin >> input;
  if (sizeof(input) > 1) {
    cout << "Too Many Chars!";
  }
  if (sizeof(input) == 0) {
    cout << "No input???" << endl;
    getInput(guessed);
  }
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
// in the correct placement. Eg: PA__I_LE will be returned if the word is particle.
std::tuple<int, string> checkWordProgress(string word, char guessed[26]) {
  string displayWord;
  int missCount = 0;
  int lengthOfGuessed = int(strlen(guessed));

  // Traverse each character in word and match it with each element in guessed[].
  for (size_t x = 0; x < word.length(); x++) {
    displayWord.push_back('_');
    for (int y = 0; y < lengthOfGuessed; y++) {
      if (word[x] == guessed[y]) {
        displayWord.back() = guessed[y];
      }
    }
  }
  
  for (int z = 0; z < lengthOfGuessed; z++) {
    if (displayWord.find(guessed[z])) {
      guessed[z] = '\0';
    }
  }
  // Check if there are any underscores. If there are none left, that means the player won.
  if (displayWord.find_first_of('_') == std::string::npos) {
    printf("\n--------\nYou Win!\n--------\n");
    exit(0);
  }
  std::tuple<int, string> parsed;
  parsed = make_tuple(missCount, displayWord);
  return parsed;
}

void printHangman(string word, char guessed[]) {
  cout << word << endl;
  int misses;
  string displayWord;
  std::tie(misses, displayWord) = checkWordProgress(word, guessed);
  switch (misses) {
  case 0:
    cout << "No Misses, nice!" << endl;
    cout << displayWord << endl;
    break;
  case 1:
    cout << " 0" << endl;
    cout << "One miss!" << endl;
    cout << "Progress: " << displayWord << endl;
    break;
  case 2:
    cout << " 0" << endl;
    cout << " |" << endl;
    cout << "Two misses!" << endl;
    cout << "Progress: " << displayWord << endl;
    break;
  case 3:
    cout << "  0" << endl;
    cout << " /|\\" << endl;
    cout << "Three misses!" << endl;
    cout << "Progress: " << displayWord << endl;
    break;
  case 4:
    cout << " 0" << endl;
    cout << "/|\\" << endl;
    cout << " |" << endl;
    cout << "Four misses!" << endl;
    cout << "Progress: " << displayWord << endl;
    break;
  case 5:
    cout << " 0" << endl;
    cout << "/|\\" << endl;
    cout << " |" << endl;
    cout << "/ \\" << endl << endl;
    cout << "Five misses!" << endl;
    cout << "Progress: " << displayWord << endl;
    cout << "GAME OVER" << endl;
    exit(0);
    break;
  }
}

int main() {
  cout << "----Press Enter to Start!----" << endl;
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
  char guessedChars[26] = ""; // All the guessed letters
  int iter = 0;
  while (iter < 26) {
    char guess = getInput(guessedChars);
    guessedChars[iter] = guess;
    printHangman(word, guessedChars);
    cout << endl << "----------------" << endl;
    iter++;
  }
  return 0;
}

