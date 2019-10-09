#pragma once

#include "transformed_object.h"

template<typename ...Rest>
class draw_container {
};

template<typename T, typename ...Rest>
class draw_container<T, Rest...> {
public:
    draw_container(const T &to_draw, const Rest &...rest) : to_draw(to_draw),
                                                            rest(rest...) {} // NOLINT(google-explicit-constructor)

    void draw() const {
        to_draw.draw();
        rest.draw();
    }

private:
    T to_draw;
    draw_container<Rest...> rest;
};

template<>
class draw_container<> {
public:
    void draw() const {}
};

template<typename ...T>
draw_container<T...> draw_all(const T &...items) {
    return {items...};
}

template<typename T, typename ...Rest>
auto multi_transform(const T &item, const Rest &...rest) {
    return draw_all(transform(item, rest)...);
}