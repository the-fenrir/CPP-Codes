// 15.2 — header: declaration goes here.
#pragma once

class Point {
    int m_x;
    int m_y;
public:
    Point(int x, int y);          // declared here, defined in point.cpp

    // Small accessors — defined in the class body, so implicitly inline.
    int x() const { return m_x; }
    int y() const { return m_y; }

    void print() const;           // also defined in point.cpp
};
