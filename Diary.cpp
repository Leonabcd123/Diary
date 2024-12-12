#include <iostream>
#include <fstream>
#include <limits>

const std::string filename = "diary.txt";

void setupDiary();
void showDiary();
void addDiary();
void editDiary();
void removeDiary();

int main(){

  int choice;
  bool running = true;

  setupDiary();

  while (running){

    std::cout << "What Would You Like To Do?\n";
    std::cout << "1. Show Entries\n";
    std::cout << "2. Add Entry\n";
    std::cout << "3. Edit Entry\n";
    std::cout << "4. Remove Entry\n";
    std::cout << "5. Quit\n";
    std::cin >> choice;

    if (std::cin.fail() || std::cin.peek() != '\n'){

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "Invalid Input.\n";
      continue;
    }

    switch(choice){

      case 1:
        showDiary();
        break;

      case 2:
        addDiary();
        break;

      case 3:
        editDiary();
        break;

      case 4:
        removeDiary();
        break;

      case 5:
        running = false;
        break;

      default:
        std::cout << "Please Enter A Valid Number (1, 2, 3, 4).\n";
        break;
    }

    }

  return 0;
}

void setupDiary(){

  std::ifstream fileIn(filename);

  if (!fileIn.is_open()){
    std::ofstream fileOut(filename);
    fileOut.close();
  }

  fileIn.close();
}

void showDiary(){

  std::ifstream fileIn(filename);

  if (!fileIn.is_open()){

    std::cerr << "File Could Not Be Opened.\n";
    return;
  }

  std::string line;
  int lineNumber = 0;

  while (std::getline(fileIn, line)){

    if (lineNumber == 0){

      std::cout << "Date: " << line << '\n';

    }

    else if (lineNumber == 1){

      std::cout << "Title: " << line << '\n';
      
    }

    else if (lineNumber == 2){

      std::cout << "Text: " << line << '\n';
      
    }

  if (line.empty()) {
    std::cout << "*****************************\n";
    lineNumber = 0;
    continue;
  }

  lineNumber++;

  }
}

void addDiary(){

  std::ofstream fileOut(filename, std::ios::app);

  if (!fileOut.is_open()){

    std::cerr << "File Could Not Be Opened.\n";
    return;
  }

  std::string date, title, text;

  std::cout << "Enter The Date (Year/Month/Day):\n";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::getline(std::cin, date);

  std::cout << "Enter The Title:\n";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::getline(std::cin, title);

  std::cout << "Enter The Text:\n";
  std::getline(std::cin, text);

  fileOut << date << '\n';
  fileOut << title << '\n';
  fileOut << text << '\n';
  fileOut << '\n';

  fileOut.close();
}
void editDiary() {
    std::ifstream fileIn(filename);
    std::ofstream fileOut("temp.txt");

    if (!fileIn.is_open() || !fileOut.is_open()) {
        std::cerr << "File Could Not Be Opened.\n";
        return;
    }

    std::string dateToEdit;
    std::cout << "Enter The Entry's Date To Edit (Year/Month/Day): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, dateToEdit);

    int choice;
    std::cout << "What Would You Like To Edit?\n";
    std::cout << "1. Date\n";
    std::cout << "2. Title\n";
    std::cout << "3. Text\n";
    std::cin >> choice;

    std::string line;
    bool found = false;
    while (std::getline(fileIn, line)) {
        if (line == dateToEdit) {
            found = true;

            if (choice == 1) {
                std::string newDate;
                std::cout << "Enter The New Date (Year/Month/Day): ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, newDate);
                fileOut << newDate << '\n';
            } else {
                fileOut << line << '\n';
            }

            std::getline(fileIn, line);
            if (choice == 2) {
                std::string newTitle;
                std::cout << "Enter The New Title: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, newTitle);
                fileOut << newTitle << '\n';
            } else {
                fileOut << line << '\n';
            }

            std::getline(fileIn, line);
            if (choice == 3) {
                std::string newText;
                std::cout << "Enter The New Text: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, newText);
                fileOut << newText << '\n';
            } else {
                fileOut << line << '\n';
            }

            std::getline(fileIn, line);
            fileOut << '\n';
        } else {
            fileOut << line << '\n';
        }
    }

    fileIn.close();
    fileOut.close();

    if (found) {
        std::remove(filename.c_str());
        std::rename("temp.txt", filename.c_str());
        std::cout << "Entry Edited Successfully.\n";
    } else {
        std::remove("temp.txt");
        std::cout << "Entry Wasn't Found.\n";
    }
}

void removeDiary(){

  std::ifstream fileIn(filename);
  std::ofstream fileOut("temp.txt");

  if (!fileIn.is_open() || !fileOut.is_open()){

    std::cerr << "File Could Not Be Opened.\n";
    return;
  }

  std::string date;
  std::cout << "Enter The Entry's Date:\n";
  std::cin >> date;

  std::string line;
  bool found = false;

  while (std::getline(fileIn, line)){

    if (line == date){
      found = true;
      std::getline(fileIn, line);
      std::getline(fileIn, line);
      std::getline(fileIn, line);
      continue; 
    }

    fileOut << line << '\n';
  }

  fileIn.close();
  fileOut.close();

  if (found){

    std::remove("diary.txt");
    std::rename("temp.txt", "diary.txt");
    std::cout << "Entry Deleted Successfully.\n";

  }

  else
  {

    std::remove("temp.txt");
    std::cout << "Entry Wasn't Found.\n";

  }
}