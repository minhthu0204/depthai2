#ifndef ACTIONDECIDER_H
#define ACTIONDECIDER_H

#include <vector>
#include <QString>

class ActionDecider {
public:
    QString decideAction(const std::vector<std::vector<int>>& grid);
};

#endif // ACTIONDECIDER_H
