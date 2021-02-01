#include "cell.hpp"

bool operator==(const Cell &left, const Cell &right) {
    return left._id == right._id;
}

bool operator!=(const Cell &left, const Cell &right) {
    return !(left == right);
}
