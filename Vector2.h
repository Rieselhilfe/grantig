#include <cmath>
#include <string>

#ifndef MOOS_VECTOR2_H
#define MOOS_VECTOR2_H
namespace moos {
    class Vec2i {
    public:
        int x;
        int y;

        Vec2i() : x(0), y(0) {}
        explicit Vec2i(int n) : x(n), y(n) {}
        Vec2i(int x, int y) : x(x), y(y) {}

        inline Vec2i &fromOneD(int n, int wrap) {
            x = n % wrap;
            y = n / wrap;
            return *this;
        }

        [[nodiscard]] inline int distance(const Vec2i &other) const { // TODO warum?
            Vec2i delta = other - *this;
            return std::max(std::abs(delta.x), std::abs(delta.y));
        }

        [[nodiscard]] inline std::string to_string() const {
            return "("+std::to_string(x)+", "+std::to_string(y)+")";
        }

        inline Vec2i operator-() const {
            return Vec2i(-(x), -(y));
        }

        inline Vec2i operator+(const Vec2i &right) const {
            return Vec2i(x + right.x, y + right.y);
        }

        inline Vec2i operator-(const Vec2i &right) const {
            return Vec2i(x - right.x, y - right.y);
        }

        inline Vec2i operator*(const Vec2i &right) const {
            return Vec2i(x * right.x, y * right.y);
        }

        inline Vec2i operator/(const Vec2i &right) const {
            return Vec2i(x / right.x, y / right.y);
        }

        inline int operator%(int width) const { // to one dimension
            return y*width + x;
        }

        bool operator==(const Vec2i &right) const {
            return (x == right.x and y == right.y);
        }

        bool operator!=(const Vec2i &right) const {
            return (x != right.x and y != right.y);
        }

        inline void operator+=(const Vec2i &right) {
            x = x + right.x;
            y = y + right.y;
        }

        inline void operator-=(const Vec2i &right) {
            x = x - right.x;
            y = y - right.y;
        }

        inline void operator*=(const Vec2i &right) {
            x = x * right.x;
            y = y * right.y;
        }

        inline void operator/=(const Vec2i &right) {
            x = x / right.x;
            y = y / right.y;
        }
    };
} // namespace moos
#endif //MOOS_VECTOR2_H
