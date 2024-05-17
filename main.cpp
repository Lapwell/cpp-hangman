// Copyright 2024-03-31 22:05:05 Lapwell/Byron.c. All rights reserved

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using std::string, std::endl, std::cout, std::cin;

char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
char nums[11] = "0123456789";

char getInput(char guessed[]) {
  char input;
  cout << "Input Guess: ";
  cin >> input;
  for (int i = 0; i < int(strlen(guessed)); i++) {
    if (input == guessed[i]) {
      cout << "Already Guessed! Try Again..." << endl;
      getInput(guessed);
    }
    if (input == nums[i]) {
      cout << "No Numbers!" << endl;
      getInput(guessed);
    }
  }
  return input;
}

// This function will generate a string that shows the correctly guessed letters
// in the correct placement. EG: PA__I_LE will be returned if the word is Particle.
void generateDisplayWord(string word, char guessed[]) {
  cout << word << endl;
  string displayWord;
  for (int i = 0; i < int(word.length()); i++) {
    for (int n = 0; n < int(strlen(guessed)); n++) {
      if (word.at(i) == guessed[n]) {
        displayWord.append(std::to_string(guessed[n]));
        return;
      } else {
        displayWord.append("_");
      }
    }
  }
  cout << displayWord << endl;
}

void printHangman(int misses, string word) {
  switch (misses) {
  case 0:
    cout << "No Misses, nice!" << endl;
    break;
  case 1:
    cout << " 0" << endl;
    break;
  case 2:
    cout << " 0" << endl;
    cout << " |" << endl;
    break;
  case 3:
    cout << "  0" << endl;
    cout << " /|\\" << endl;
    break;
  case 4:
    cout << " 0" << endl;
    cout << "/|\\" << endl;
    cout << " |" << endl;
    break;
  case 5:
    cout << " 0" << endl;
    cout << "/|\\" << endl;
    cout << " |" << endl;
    cout << "/ \\" << endl;
    break;
  }
}

int main() {
  string wordList[16] = {
      "inquisitive", "program",      "coding",  "project",
      "freshwater",  "helldiver",    "python",  "stellarator",
      "factorio",    "assembly",     "silicon", "micrometer",
      "astronomy",   "astrophysics", "physics", "quantum"};
  srand(time(NULL));
  // sizeof() is divided by 32 because sizeof() returns the memory size.
  // Dividing by 32 (length of string type), we get the number of elements.
  int wordListSize = sizeof(wordList) / 32;
  string word = wordList[rand() % wordListSize];
  char guessedChars[26]; // All the guessed letters.
  std::vector<char> hiddenWord(word.length());
  int misses = 0;
  int iter = 0;
  while (iter < 26) {
    guessedChars[iter] = getInput(guessedChars);
    generateDisplayWord(word, guessedChars);
    printHangman(misses, word);
    iter++;
  }
  return 0;
}
