#include "Random.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

namespace Wordlist
{
    std::vector<std::string> words{
        "broccoli",      
        "drift", "phone","hangman", "galaxy", "quantum", "keyboard", "syntax",
        "variable", "function", "pointer", "compile", "debug"
    };
}

class Session
{
private:
    int m_length = static_cast<int>(Wordlist::words.size());
    std::string m_word{Wordlist::words[Random::get(0, 12)]};
    std::vector<char> m_letters{};  // guessed letters
    std::vector<char> m_wrong{};

public:
    void push_letter(char letter) { m_letters.push_back(letter); }
    std::string get_word() const { return m_word; }

    bool has_already_guessed(char letter) const
    {
        for (char guessed : m_letters)
        {
            if (guessed == letter)
            {
                std::cout << "You have already guessed that letter. Try again!\n";
                return true;
            }
        }
        return false;
    }

    bool is_letter_guessed(char letter) const
    {
        for (char guessed : m_letters)
        {
            if (guessed == letter)
                return true;
        }
        return false;
    }

    bool is_letter_in_word(char letter) const
    {
        for (char c : m_word)
        {
            if (c == letter)
                return true;
        }
        return false;
    }

    void push_wrong(char letter) { m_wrong.push_back(letter); }

    std::vector<char> getwrong() { return m_wrong; }
};

char getinput()
{
    while (true)
    {
        char letter{};
        std::cout << "Enter the next letter: ";
        std::cin >> letter;

        letter = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));

        if (std::isalpha(static_cast<unsigned char>(letter)))
        {
            std::cout << "You have entered: " << letter << "\n";
            return letter;
        }
        else
        {
            std::cout << "You have entered wrong input. Try again.\n";
        }
    }
}

void start()
{
    Session temp{};
    int length = static_cast<int>(temp.get_word().size());

    std::cout << "The word is :";
    for (int i = 0; i < length; i++)
    {
        std::cout << "_";
    }

    std::cout << "        Wrong guesses left :";
    for (int j{0}; j <= 5; j++)
    {
        std::cout << "+";
    }
    std::cout << "\n";

    int tries = 5;

    while (tries >= 0)
    {
        char guess = getinput();

        if (temp.has_already_guessed(guess))
            continue;

        temp.push_letter(guess);

        if (temp.is_letter_in_word(guess))
        {
            std::cout << "Yes, " << guess << " is in the word.\n";
        }
        else
        {
            std::cout << "Sorry, " << guess << " is NOT in the word.\n";
            temp.push_wrong(guess);
            --tries;
        }

        // Display word with guessed letters
        for (char c : temp.get_word())
        {
            if (temp.is_letter_guessed(c))
            {
                std::cout << c;
            }
            else
            {
                std::cout << "_";
            }
        }

        std::cout << "        Wrong Guesses :";
        for (int j{0}; j <= tries; j++)
        {
            std::cout << "+";
        }

        std::vector<char> Wrongs = temp.getwrong();
        for (auto i : Wrongs)
        {
            std::cout << i;
        }

        // ✅ WIN CHECK: handles repeated letters
        bool all_guessed = true;
        for (char c : temp.get_word())
        {
            if (!temp.is_letter_guessed(c))
            {
                all_guessed = false;
                break;
            }
        }

        if (all_guessed)
        {
            std::cout << "\nYou have guessed the word   You Won!!\n";
            std::cout << "Thank You for playing my game\n";
            break;
        }

        if (tries == -1)
        {
            std::cout << "\nYou lost the game \n";
            std::cout << "The word was : " << temp.get_word() << "\n";
            std::cout << "Thank You for playing my game\n";
            break;
        }

        std::cout << "\n";
    }
}

int main()
{
    std::cout << "Welcome to C++ Man (Variant of HangMan)\n";
    std::cout << "To win guess the word       To Lose : Run Out of Pluses\n";
    start();
}
