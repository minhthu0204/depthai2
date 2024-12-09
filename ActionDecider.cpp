#include "ActionDecider.h"

static constexpr int GRID_SIZE = 5;

QString ActionDecider::decideAction(const std::vector<std::vector<int>>& grid) {
    int leftDanger = 0, rightDanger = 0, topDanger = 0, bottomDanger = 0;
    int leftSafe = 0, rightSafe = 0, topSafe = 0, bottomSafe = 0;
    int total = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            total += grid[i][j];
            if (i < GRID_SIZE - 1) topDanger += grid[i][j];
            if (i > 0) bottomDanger += grid[i][j];
            if (j < GRID_SIZE - 1) leftDanger += grid[i][j];
            if (j > 0) rightDanger += grid[i][j];

            if (i == 0) topSafe += grid[i][j];
            if (i == GRID_SIZE - 1) bottomSafe += grid[i][j];
            if (j == 0) leftSafe += grid[i][j];
            if (j == GRID_SIZE - 1) rightSafe += grid[i][j];
        }
    }

    if (total == 0) {
        return "Không có vật cản, tiếp tục bay";
    } else if (leftDanger > 0 && rightSafe == 0) {
        return "Né phải";
    } else if (rightDanger > 0 && leftSafe == 0) {
        return "Né trái";
    } else if (topDanger > 0 && bottomSafe == 0) {
        return "Bay xuống";
    } else if (bottomDanger > 0 && topSafe == 0) {
        return "Bay lên";
    } else {
        return "Lùi lại";
    }
}
