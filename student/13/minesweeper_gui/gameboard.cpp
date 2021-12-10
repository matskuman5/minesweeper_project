#include "gameboard.hh"
#include <random>

GameBoard::GameBoard()
{
}

GameBoard::~GameBoard()
{
}

void GameBoard::init(int seed, unsigned int size)
{
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distribution(1, 100/MINE_PROBABALITY);

    board_size_ = size;

    for(unsigned int y = 0; y < board_size_; ++y)
    {
        std::vector<Square> line;
        for(unsigned int x = 0; x < board_size_; ++x)
        {
            bool hasMine = false;
            if(distribution(randomEng) == 1)
            {
                hasMine = true;
            }
            Square new_square(x, y, hasMine, this);
            line.push_back(new_square);
        }
        board_.push_back(line);
    }

    // When all the squares of the board exist, each square is asked to
    // calculate the data telling how many mines lie in the adjacent squares.
    // After that game board is ready.
    for(unsigned int y = 0; y < board_size_; ++y)
    {
        for(unsigned int x = 0; x < board_size_; ++x)
        {
            board_.at(y).at(x).countAdjacent();
        }
    }
}

void GameBoard::print(std::ostream& stream) const
{
    // Printing space after each character to make ASCII graphics clearer

    // Printing numbers of x-axis over the board
    stream << "  ";
    for(unsigned int x = 0; x < board_size_; ++x)
    {
        // Using modulo 10 to make the output fit, even if the board width
        // was more than 10
        stream << (x + 1) % 10 << ' ';
    }
    stream << std::endl;

    // Printing the board such that each line begins with y-coordinate,
    // and then each square of the line is asked to print itself
    for(unsigned int y = 0; y < board_size_; ++y)
    {
        stream << (y + 1) % 10 << ' ';
        for(unsigned int x = 0; x < board_size_; ++x)
        {
            board_.at(y).at(x).print(stream); // Replace print with debugPrint
            stream << " ";                    // to see opened squares.
        }
        stream << std::endl;
    }
}

bool GameBoard::isGameOver() const
{
    for(unsigned int y = 0; y < board_size_; ++y)
    {
        for(unsigned int x = 0; x < board_size_; ++x)
        {
            if(not board_.at(y).at(x).isReady())
            {
                return false;
            }
        }
    }
    return true;
}

int GameBoard::getSize() const
{
    return board_.size();
}

Square GameBoard::getSquare(int x, int y) const
{
    return board_.at(y).at(x);
}

void GameBoard::setSquare(Square sq, int x, int y)
{
    board_.at(y).at(x) = sq;
}

bool GameBoard::openSquare(int x, int y)
{
    return board_.at(y).at(x).open();
}

bool GameBoard::flagSquare(int x, int y)
{
    if (!board_.at(y).at(x).hasFlag()) {
        board_.at(y).at(x).addFlag();
        return true;
    } else {
        board_.at(y).at(x).removeFlag();
        return false;
    }

}
