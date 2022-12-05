#include <iostream> // cout, cin
#include <stdlib.h> // rand, srand, system
#include <unistd.h> // sleep
#include <time.h>   // time.now time_t
#include <conio.h>  // getch
#include <string>   //to_string, length
using namespace std;

// Functions

// Create game header
void create_game_header()
{
    cout << "\t\t***Welcome to my first Game :)****\n";
    cout << "\tVision the Shape and Calculate its Area before the time is over! \n";
}

// Get game level from the user

void get_game_level(int &level)
{
    // Show levels menu
    cout << "\nChoose the game level" << endl;
    cout << "Easy => 1" << endl;
    cout << "Medium => 2" << endl;
    cout << "Hard => 3" << endl;
    cout << "Enter the level number(1-3): ";
    cin >> level; // read game level value

    // validate the input value
    if (level != 1 && level != 2 && level != 3)
    {
        // Abort the process, if the input is not valid
        cout << "Please enter valid value" << endl;
        abort();
    }
}

// show the number of the current trial and the score value
void show_score_trial(int n_trial, int m_trial, int score = 0)
{
    cout << "\n\t\tTrial: " << n_trial << "/" << m_trial;
    cout << "\t\t Score: " << (score * 1.0 / m_trial) * 100.0 << "%" << endl;
}

// print n of Chars
void print_nchars(int n, char c)
{
    cout << string(n, c);
}

// calculate integer length
int calc_int_length(int num){
    //convert integer to string
    string num_to_string = to_string(num);
    // return the string length
    return num_to_string.length();
}

// print a waiting message with count down N Seconds
void start_after(int sec)
{
    cout << "\n\t\tStart Next in ";
    for (int i = sec; i > 0; i--)
    {
        cout << i << "s...";
        sleep(1);
        // calculate the number of backspaces
        int num_of_backspace = calc_int_length(i) + 4;
        print_nchars(num_of_backspace, '\b');
    }
}

// Main
int main()
{
    // 0a. Define Variable
    int m_trial, n_trial;
    int score, g_timeout;
    int width, length;
    int area, user_area;
    int table_size;
    int level; // game level
    time_t user_stime, user_timeout;

    // 1a. Initiate Variables
    table_size = 5;
    m_trial = 5;
    n_trial = 1;
    score = 0;

    // 0b. Change random based on time
    srand(time(0));

    // 0c. Print Game instructions
    system("cls");
    create_game_header();

    // ask the user to press any key to start the game
    cout << "\n\nPress any key to start playing ...";
    getch();

    get_game_level(level);

    system("cls");

    // calculate game timeout according to the game level
    g_timeout = 6 - level;

    do
    {
        // Create Header
        create_game_header();
        show_score_trial(n_trial, m_trial, score);

        //------Initiate Variables repeated part
        width = (2 * level) + rand() % (table_size + (level - 1) * 2);
        length = (2 * level) + rand() % (table_size + (level - 1) * 2);
        area = width * length;

        // 2b. padding top
        cout << "\n\n";

        // 2a. Draw the Rectangle
        for (int i = 0; i < length; i++)
        {
            // 2b. Padding left
            cout << "\t\t";
            for (int j = 0; j < width; j++)
            {
                cout << "# ";
            }
            cout << "\n";
        }

        // 3c. Set Start time
        user_stime = time(0);

        // 3a. Ask User
        cout << "Area = ";
        cin >> user_area;

        // 3c. Set end time and calc diff
        user_timeout = time(0) - user_stime;
        cout << "You take " << user_timeout << "s to answer!....\n";

        // 4a. Compare Answer and Give them point
        if (user_area == area && user_timeout <= g_timeout)
        {
            score++;
            cout << "\tCorrect :)\n";
        }
        else if (user_area != area)
        {
            cout << "\tWrong :( \n";
        }
        else
        {
            cout << "\tTimeout :|, try fast\n";
        }

        // 4b. Clear Screen
        sleep(3);
        system("cls");
        create_game_header();
        show_score_trial(n_trial, m_trial, score);
        // if the trial is not the last trial
        if (n_trial < m_trial)
        {
            start_after(3);
        }
        system("cls");

        n_trial++;
    }

    // 5a. Check the number of trial
    while (n_trial <= m_trial);

    // 6a. Game over and print score
    // Create Header
    create_game_header();
    cout << "\t\tGAME OVER\n";
    cout << "\t\tYour Score is :" << (score * 1.0 / m_trial) * 100.0 << "%\n";

    return 0;
}
