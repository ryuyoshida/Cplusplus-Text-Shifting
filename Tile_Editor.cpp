/*Nabil Farhan*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

const int SIZE = 80;

// this function is to get string input from the user as one line, not one word
string write(){
    string str = "";
    cin.clear(); cin.sync();
    getline(cin, str);
    return str;
}

// this is to copy everything in one array to another array
void copyArray(string a[], string b[]){
    for(int i = 0; i < SIZE; i++){
        a[i] = b[i];
    }
}

// this is to reset everything inside a string array
void resetArray(string arrayy[]){
    for(int i = 0; i < SIZE; i++){
        arrayy[i] = "";
    }
}

//this is to find one specific word inside the whole array
void findd(string words[], string clip[], string filename){
    string str = "";
    cout << "Enter text to find : ";
    str = write();

    // to store which index contains the same word
    bool found[SIZE];

    // find the word
    for(int i = 0; i < SIZE; i++){
        if (str == words[i]){
            found[i] = true;
        } else {
            found[i] = false;
        }
    }

    // this is to draw the table
    cout << filename << endl;
    cout << "Clipboard: " << endl;
    for(int i = 0; i < SIZE; i++){
        if (i == 0 && clip[i].length() < 1){
            cout << "<empty>";
            break;
        }
    }

    cout << "Table" << endl;

    int width[8];
    for(int i = 0; i < 8; i++){
        width[i] = 1;
    }

    for(int i = 0; i < SIZE; i++){
        int row = i / 8;
        int col = i % 8;
    }

    for(int row = 0; row < 10; row++){
        for(int col = 0; col < 8; col++){
            if (words[row * 8 + col].length() > width[col]){
                width[col] = words[row * 8 + col].length();
            }
        }
    }

    int i = 0;

    for(int row = 0; row < 25; row++){
        if (row % 2 == 0){ // even
            // row even 0 2 4 6 8 ....
            for (int col = -1; col < 8; col++){
                if (col < 0){
                    cout << "+----+";
                } else {
                    cout << "-";
                    for(int dash = 0; dash < width[col]; dash++){
                        cout << "-";
                    }
                    cout << "-+";
                }
            }

            cout << endl;
        } else { // odd
            if (row == 1){
                // row 1
                for (int col = - 1; col < 8; col++){
                    if (col < 0){
                        cout << "|    |";
                    } else {
                        cout << " " << col + 1;
                        for(int dash = 0; dash < width[col]; dash++){
                            cout << " ";
                        }
                        cout << "|";
                    }
                }

                cout << endl;
            } else {
                // 3 5 7 9 ...
                for(int col = -1; col < 8; col++){
                    if (col < 0){
                        if (i < 10){
                            cout << "| 0" << i << " |";
                        } else {
                            cout << "| " << i << " |";
                        }
                    } else {
                        cout << " " << words[i];

                        for(int dash = 0; dash < width[col] - words[i].length(); dash++){
                            cout << " ";
                        }

                        if (found[i] && words[i].length() > 0){
                            cout << " <";
                        } else {
                            cout << " |";
                        }
                        i++;
                    }
                }
                cout << endl;
            }
        }
    }
}

// this is to paste everything inside the clipboard and insert it into the words array
void paste(string words[], string clip[]){
    // get the tile position
    int tile;
    cout << "Tile Number ==> ";
    cin >> tile;
    // convert the tile position to 0-based index
    tile--;

    if (!(tile > -1 && tile < SIZE)){
        cout << "Tile out of bounds !" << endl;
    }

    // count how many words are there inside the clipboard
    int wordcount = 0;
    for(int i = 0; i < SIZE; i++){
        if(clip[i].length() > 0){
            wordcount++;
        } else {
            break;
        }
    }

    // shift words to the right to make space for new words
    for(int i = 0; i < wordcount; i++){
        for(int j = SIZE - 1; j > tile; j--){
            words[j] = words[j - 1];
        }
    }

    // insert the new words
    for(int i = 0; i < wordcount; i++){
        words[tile] = clip[i];
        tile++;
    }

    // clear the clipboard after pasting is done
    resetArray(clip);
}

void copyy(string words[], string clip[]){
    // get the FROM position
    int from;
    cout << "From Tile Number ==> ";
    cin >> from;
    // convert to 0-based index
    from--;


    if (!(from > -1 && from < SIZE)){
        cout << "FROM out of bounds !" << endl;
    }

    // get the TO position
    int to;
    cout << "To Tile Number ==> ";
    cin >> to;
    // convert to 0-based index
    to--;

    if (!(to > -1 && to < SIZE)){
        cout << "TO out of bounds !" << endl;
    }

    // empty the previous clip if there's any
    resetArray(clip);

    // copy words into clipboard
    int wordcount = 0;
    for(int i = from; i <= to ; i++){
        clip[wordcount] = words[i];
        wordcount++;
    }
}

void cut(string words[], string clip[]){
    // get the FROM position
    int from;
    cout << "From Tile Number ==> ";
    cin >> from;
    // convert to 0-based index
    from--;

    // get the TO position
    int to;
    cout << "To Tile Number ==> ";
    cin >> to;
    // convert to 0-based index
    to--;

    // empty the previous clip if there's any
    resetArray(clip);

    // copy words into clipboard
    int wordcount = 0;
    for(int i = from; i <= to ; i++){
        clip[wordcount] = words[i];
        wordcount++;
    }

    // shift remaining words to the left to replace the cut words
    for(int k = 0; k < wordcount; k++){
        for(int i = from; i < SIZE; i++){
            words[i] = words[i + 1];
        }
        words[SIZE - 1] = "";
    }
}

void saveFile(string words[], string &filename){
    // get the new filename
    cout << "Filename to save (yourfilename.txt): ";
    filename = write();

    ofstream f;
    f.open(filename.c_str());

    // write the contents of words into file
    for(int i = 0; i < SIZE; i++){
        f << words[i] << " ";
    }

    f.close();
}

void loadFile(string words[], string &filename){
    resetArray(words);

    // get the new filename
    cout << "Filename to load (.txt): ";
    filename = write();

    string line;
    ifstream f;
    f.open(filename.c_str());

    // store everything inside the file into LINE
    getline(f, line);
    cout << line << endl;

    // next, splitting the sentence to array of words
    string strings[SIZE]; // to store the words
    int wordCount = 0;
    int tile = 0;

    for(int i = 0; i < line.length(); i++){
        if (line[i] == ' '){
            continue;
        } else if (line[i - 1] == ' ' && line[i] != ' '){
            wordCount++;
            strings[wordCount] += line[i];
        } else {
            strings[wordCount] += line[i];
        }
    }

    // insert the new words
    for(int i = 0; i < SIZE; i++){
        if (strings[i].size() == 0){
            break;
        } else {
            words[i] = strings[i];
        }
        tile++;
    }
}

// this is to overwrite the current array of words
void over(string words[]){
    // get the tile position
    int tile;
    cout << "Tile Number ==> ";
    cin >> tile;
    // make it 0-based
    tile--;

    if(words[tile].length() < 1){
        cout << "The tile has no word to overwrite" << endl;
        return;
    }

    if (!(tile > -1 && tile < SIZE)){
        cout << "Tile out of bounds" << endl;
    }
    // get the string that the user want to overwrite with
    string str = "";
    cout << "Text ==> ";
    str = write();

    string strings[SIZE];
    int wordCount = 0;

    // splitting sentence to array of words
    for(int i = 0; i < str.length(); i++){
        if (str[i] == ' '){
            wordCount++;
        } else {
            strings[wordCount] += str[i];
        }
    }

    // insert the new words
    for(int i = 0; i < SIZE; i++){
        if (strings[i].size() == 0){
            break;
        } else {
            words[tile] = strings[i];
        }
        tile++;
    }

}

// this is to delete ONE word inside the words array
void deleteWord(string words[]){
    // get the tile position to delete the word
    int tile;
    cout << "Tile Number ==> ";
    cin >> tile;

    // make it 0-based
    tile--;

    if(words[tile].length() < 1){
        cout << "Tile is empty" << endl;
        return;
    }

    if (!(tile > -1 && tile < SIZE)){
        cout << "Tile out of bounds" << endl;
    }
    // shift the remaining words after the tile to the left
    for(int i = tile; i < SIZE; i++){
        words[i] = words[i + 1];
    }
    words[SIZE - 1] = "";
}

// this is to INSERT a sentences into the words array
void insertWord(string words[]){
    // get the tile position to insert the word
    int tile;
    cout << "Tile Number ==> ";
    cin >> tile;

    // make it 0-based
    tile--;

    if (!(tile > -1 && tile < SIZE)){
        cout << "Tile out of bounds" << endl;
        return;
    }

    // get the sentences
    string str = "";
    cout << "Text ==> ";
    str = write();

    // split the sentence to array of words
    string strings[SIZE];
    int wordCount = 0;
    for(int i = 0; i < str.length(); i++){
        if (str[i] == ' '){
            continue;
        } else if (str[i - 1] == ' ' && str[i] != ' '){
            wordCount++;
            strings[wordCount] += str[i];
        } else {
            strings[wordCount] += str[i];
        }
    }

    // shift words to the right to make space for new words
    for(int i = wordCount + 1; i > 0; i--){
        for(int j = SIZE - 1; j > tile; j--){
            words[j] = words[j - 1];
        }
    }

    // store the new words into the array
    for(int i = 0; i < SIZE; i++){
        if (strings[i].size() == 0){
            break;
        } else {
            words[tile] = strings[i];
        }
        tile++;
    }
}

// this is to create a new file
void createFile(string words[], string clip[], string before[], string &filename){
    // get the filename
    string str = "";
    cout << "New filename (yourfilename.txt): ";
    cin >> filename;
    cout << "Your filename has been input, now choose [S]ave to create and save your file." << endl;
    cout << endl;

    resetArray(words);
    resetArray(clip);
    resetArray(before);
}

// this function is to draw the boxy boxes of words based on the given array
void draw(string words[], string clip[], string filename){
    // display the current used filename
    cout << filename << endl;

    // display the content of clipboard if there's any
    cout << "Clipboard: ";
    for(int i = 0; i < SIZE; i++){
        if (i == 0 && clip[i].length() < 1){
            cout << "<empty>";
            break;
        }

        if (clip[i].length() > 0){
            cout << clip[i] << " ";
        }
    }
    cout << endl;

    // array to store the width of columns
    int width[8];

    // initialize each columns with 1
    for(int i = 0; i < 8; i++){
        width[i] = 1;
    }

    // calculate the maximum width of each column of words
    for(int row = 0; row < 10; row++){
        for(int col = 0; col < 8; col++){
            // if the current word alphabet count is bigger than the width of the column
            if (words[row * 8 + col].length() > width[col]){
                // set the new width of column
                width[col] = words[row * 8 + col].length();
            }
        }
    }

    // begin drawing the boxes to display the content of the array

    int i = 0;

    for(int row = 0; row < 23; row++){
        if (row % 2 == 0){ // even
            // row genap 0 2 4 6 8 ....
            for (int col = -1; col < 8; col++){
                if (col < 0){
                    cout << "+----+";
                } else {
                    cout << "-";
                    for(int dash = 0; dash < width[col]; dash++){
                        cout << "-";
                    }
                    cout << "-+";
                }
            }

            cout << endl;
        } else { // odd
            if (row == 1){
                // row 1
                for (int col = - 1; col < 8; col++){
                    if (col < 0){
                        cout << "|    |";
                    } else {
                        cout << " " << col + 1;
                        for(int dash = 0; dash < width[col]; dash++){
                            cout << " ";
                        }
                        cout << "|";
                    }
                }

                cout << endl;
            } else {
                // 3 5 7 9 ...
                for(int col = -1; col < 8; col++){
                    if (col < 0){
                        if (i < 10){
                            cout << "| 0" << i << " |";
                        } else {
                            cout << "| " << i << " |";
                        }
                    } else {
                        cout << " " << words[i];
                        for(int dash = 0; dash < width[col] - words[i].length(); dash++){
                            cout << " ";
                        }
                        cout << " |";
                        i++;
                    }
                }

                cout << endl;
            }
        }
    }
}

// this where user get to choose the desired operation
void choose(string words[], string clip[], string before[]){
    string filename = "null";
    char opr ='q';
    do{
        cout << "File name : " << filename << endl;
        cout << "-------------------------------------------------------------------" << endl;
        cout << "|  [N]ew   [I]nsert  [D]elete  [S]ave    [L]oad,    [O]verwrite   |" << endl;
        cout << "|  [C]opy  [X]cut    [P]aste   [F]ind    [U]ndo,    [Q]uit/Exit   |" << endl;
        cout << "-------------------------------------------------------------------" << endl;
        cout << "==> ";
        cin >> opr;

        switch (opr){

        case 'N':
        case 'n':
            createFile(words, clip, before, filename);
            break;
        case 'I':
        case 'i':
            copyArray(before, words);
            insertWord(words);
            draw(words, clip, filename);
            break;
        case 'D':
        case 'd':
            copyArray(before, words);
            deleteWord(words);
             draw(words, clip, filename);
            break;
        case 'O':
        case 'o':
            copyArray(before, words);
            over(words);
            draw(words, clip, filename);
            break;
        case 'L':
        case 'l':
            loadFile(words, filename);
            draw(words, clip, filename);
            break;
        case 'S':
        case 's':
            saveFile(words, filename);
            draw(words, clip, filename);
            break;
        case 'C':
        case 'c':
            copyArray(before, words);
            copyy(words, clip);
            draw(words, clip, filename);
            break;
        case 'X':
        case 'x':
            copyArray(before, words);
            cut(words, clip);
            draw(words, clip, filename);
            break;
        case 'P':
        case 'p':
            copyArray(before, words);
            paste(words, clip);
            draw(words, clip, filename);
            break;
        case 'F':
        case 'f':
            findd(words, clip, filename);
        break;
        case 'U':
        case 'u':
            copyArray(words, before);
            draw(words, clip, filename);
            break;
        case 'Q':
        case 'q':
            exit(0);

        default:
            cout << "Invalid input" << endl;
            break;
        }
    }while(true);
}

int main(){
    string words[SIZE];
    string clip[SIZE];
    string before[SIZE];

    resetArray(words);
    resetArray(clip);
    resetArray(before);

    choose(words, clip, before);
}
