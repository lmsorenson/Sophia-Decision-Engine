#include <board_games/models/coordinate.h>
#include <stdexcept>
#include <cctype>

namespace sophia::board_games::models
{
    std::string Coordinate::name() const
    {
        char r = static_cast<char>('A' + row);
        char c = static_cast<char>('0' + col + 1);
        return {r, c};
    }

    Coordinate Coordinate::parse(const std::string& input)
    {
        if (input.length() < 2)
        {
            throw std::invalid_argument("Invalid coordinate format: input too short");
        }
        
        int r = std::toupper(static_cast<unsigned char>(input[0])) - 'A';
        int c = input[1] - '1';
        
        return {r, c};
    }
}
