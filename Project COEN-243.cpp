#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// print the board
void print_game(int* tokens, int num_heaps) {

    char pile = '1';

    for (int i = 0; i < num_heaps; ++i) {

        cout << pile++ << ": ";

        for (int j = 0; j < tokens[i]; ++j) {
            cout << "O ";
        }
        cout << "\n";
    }
}

// generate random number of tokens for each heap PC VS USER
void generate_heaps_PC(int number_heaps, int* heaps) {

    for (int i = 0; i < number_heaps; ++i) {

        int tokens = floor(10 * exp(-1 * pow((i - 5), 2) / 10.89));

        heaps[i] = tokens;
    }
}

// gnerate random number of tokens for each heap USER VS USER
void generate_heaps(int total_tokens, int number_heaps, int* heaps) {

    int remaining_tokens = total_tokens;

    for (int i = 0; i < number_heaps - 1; ++i) {

        int tokens = rand() % (remaining_tokens - (number_heaps - 1 - i)) + 1; //rand() from chapter 6 in textbook, same chapters as functions which was covered in lectures

        heaps[i] = tokens;

        remaining_tokens = remaining_tokens - tokens;
    }

    heaps[number_heaps - 1] = remaining_tokens;
}

// check if tokens=0 (game over)
int game_over(int* tokens, int num_heaps) {

    for (int i = 0; i < num_heaps; ++i) {
        if (tokens[i] > 0) return 0; //tokens of pile [i] where i is the pile number
    }

    return 1;
}

// recursive function to play the game 
void play_game_recursive(int* tokens, string player1, string player2, int current_player) {

    print_game(tokens, 5);


    int heap;
    int take_token;

    // get player's move
    if (current_player == 1) {
        cout << player1 << ", enter the heap number (1-5) and tokens to take: ";
        cin >> heap >> take_token;
    }
    else {
        cout << player2 << ", enter the heap number (1-5) and tokens to take: ";
        cin >> heap >> take_token;
    }

    while (heap < 1 || heap > 5 || tokens[heap - 1] == 0 || take_token < 1 || take_token > 2 || take_token > tokens[heap - 1]) {

        cout << "Invalid move. Trya again.\n";


        if (current_player == 1) {
            cout << player1 << ", enter the heap number (1-5) and tokens to take: ";
        }
        else {
            cout << player2 << ", enter the heap number (1-5) and tokens to take: ";
        }
        cin >> heap >> take_token;
    }

    tokens[heap - 1] = tokens[heap - 1] - take_token;

    // base case: game over
    if (game_over(tokens, 5)) {


        if (current_player == 1) {
            cout << player1 << " wins\n";
        }
        else {
            cout << player2 << " wins\n";
        }
        return;
    }

    play_game_recursive(tokens, player1, player2, 3 - current_player); // player switch (recursive case)
}


// recursive function to play the game PC VS USER
void play_game_PC(int* tokens, string name, int current_player, int num_heaps) {



    // pc's turn, the strategy is taking out tokens of all pile until there is only 1 pile where a better strategy is made
    if (current_player == 1) {

        print_game(tokens, num_heaps);
        for (int i = 0; i < num_heaps; ++i) {

            if (tokens[i] % 2 == 1 && tokens[i] != 1) { // odd tokens

                tokens[i] = tokens[i] - 2; // 2 tokens taken

                cout << "PC takes 2 tokens from pile " << (i + 1) << "\n";

                break;
            }
            else if (tokens[i] % 2 == 0 && tokens[i] > 3) { // evem tokens

                tokens[i] = tokens[i] - 1; // PC takes 1 tokens

                cout << "PC takes 1 token from pile " << (i + 1) << "\n";

                break;
            }

            else if (tokens[i] == 1) { // case when only 1 tokens left

                tokens[i] = tokens[i] - 1; // PC takes 1 tokens

                cout << "PC takes 1 token from pile " << (i + 1) << "\n";

                break;
            }


            else if (tokens[i] == 2) { // case when only 2 tokens left

                tokens[i] = tokens[i] - 2; // PC takes 1 tokens

                cout << "PC takes 2 token from pile " << (i + 1) << "\n";

                break;
            }

            else if (tokens[i] == 4) { // case when only 4 tokens left

                tokens[i] = tokens[i] - 1; // PC takes 1 tokens

                cout << "PC takes 1 token from pile " << (i + 1) << "\n";

                break;
            }



        }


    }

    // player's turn
    else {
        int user_heap;
        int user_tokens;

        print_game(tokens, num_heaps);
        cout << name << ", enter the heap number (1-" << num_heaps << ") and tokens to take: ";
        cin >> user_heap >> user_tokens;


        while (user_heap < 1 || user_heap > num_heaps || tokens[user_heap - 1] == 0 ||
            user_tokens < 1 || user_tokens > 2 || user_tokens > tokens[user_heap - 1]) {
            cout << "Invalid move. Try again.\n";

            cout << name << ", enter the heap number (1-" << num_heaps << ") and tokens to take: ";
            cin >> user_heap >> user_tokens;
        }

        tokens[user_heap - 1] = tokens[user_heap - 1] - user_tokens;
    }

    // base case: game over
    if (game_over(tokens, num_heaps)) {
        if (current_player == 1) {
            cout << "PC wins\n";
        }
        else {
            cout << name << " wins\n";
        }
        return;
    }



    // player switch recursive case
    play_game_PC(tokens, name, 3 - current_player, num_heaps);
}


int main() {
    int choice;


    cout << "select the game mode:\n";
    cout << "1. user vs user\n";
    cout << "2. pc vs user\n";
    cin >> choice;

    if (choice == 1) {
        string player1;
        string player2;

        cout << "Enter player 1 name: ";
        cin >> player1;
        cout << "Enter player 2 name: ";
        cin >> player2;

        int total_tokens;
        cout << "Enter the total number of tokens (must be equal to or over 5): ";
        cin >> total_tokens;

        while (total_tokens < 5) {
            cout << "Invalid number of tokens. Try again.";
            cin >> total_tokens;
        }

        int num_heaps = 5; // 5 heaps when user vs user
        int* heaps = new int[num_heaps];

        generate_heaps(total_tokens, num_heaps, heaps);
        play_game_recursive(heaps, player1, player2, 1);

        delete[] heaps;
    }
    else if (choice == 2) {
        string player1;

        cout << "Enter player 1 name: ";
        cin >> player1;

        int num_heaps;
        cout << "Enter the number of heaps (2 to 10): ";
        cin >> num_heaps;

        while (num_heaps < 2 || num_heaps > 10) {
            cout << "Invalid number of heaps. Try again.";
            cin >> num_heaps;
        }
        int* heaps = new int[num_heaps];

        generate_heaps_PC(num_heaps, heaps);
        play_game_PC(heaps, player1, 1, num_heaps);

        delete[] heaps;

    }
    else {
        cout << "Invalid choice. Ending the program.\n";
    }



    return 0;
}
