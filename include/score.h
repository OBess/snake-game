#ifndef SCORE_H
#define SCORE_H

#include <cstdint>

class Score
{
public:
    constexpr Score(uint32_t bestScore, uint32_t currentScore = 0)
        : _bestScore(bestScore), _currentScore(currentScore)
    {
    }

    constexpr void setBestScore(uint32_t bestScore) noexcept
    {
        _bestScore = bestScore;
    }

    constexpr uint32_t bestScore() const noexcept
    {
        return _bestScore;
    }

    constexpr uint32_t currentScore() const noexcept
    {
        return _currentScore;
    }

    /// @brief Increments the current score by one and
    /// updates the best score if the current is bigger than the best score
    constexpr void incrementScore() noexcept
    {
        ++_currentScore;

        if (_currentScore > _bestScore)
            _bestScore = _currentScore;
    }

    constexpr void clearCurrentScore() noexcept
    {
        _currentScore = 0;
    }

private:
    uint32_t _bestScore;
    uint32_t _currentScore;
};

#endif // SCORE_H
