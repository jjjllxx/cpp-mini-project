#pragma once

namespace gs
{
class Point
{
public:
    Point() = default;
    Point(const int x, const int y);

    void showSquare() const;
    void showCircular() const;
    void clear() const;
    void updatePos(const int x, const int y);

    bool operator==(const Point& pt) const;
    bool operator!=(const Point& pt) const;

    int getX() const;
    int getY() const;

private:
    int x, y;
};
} // namespace gs
