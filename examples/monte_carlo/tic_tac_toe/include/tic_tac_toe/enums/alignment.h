#ifndef SOPHIA_TIC_TAC_TOE_ENUMS_ALIGNMENT_H
#define SOPHIA_TIC_TAC_TOE_ENUMS_ALIGNMENT_H

namespace sophia::monte_carlo::tic_tac_toe::enums
{
    /**
     * @class Alignment
     * @brief A player wins when he or she places three of their symbols (X's or O's)
     * in a straight line.  Alignment is the orientation of the line whether it be
     * Horizontal, Vertical or Diagonal.
     */
    enum class Alignment
    {
        Horizontal, ///< three in a row across any of the three rows.
        Vertical,   ///< three in a row down any of the three columns.
        Diagonal    ///< three in a row across a diagonal, either top-left to bottom-right or top-right to bottom-left.
    };
}

#endif // SOPHIA_TIC_TAC_TOE_ENUMS_ALIGNMENT_H
