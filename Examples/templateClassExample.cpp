#include <iostream>

struct Context {};

template <typename T>
concept CanDraw = requires(T t, Context context) {
  { t.draw(context) } -> std::same_as<void>;
};

template <typename T> class Shape {
public:
  Shape() { static_assert(CanDraw<T> && std::derived_from<T, Shape>); }

  void do_draw(Context context) { static_cast<T *>(this)->draw(context); }
};

class Rectangle : public Shape<Rectangle> {
public:
  void draw(Context context) { std::cout << "Rectangle::Draw\n"; } // @1
};

class Circle : public Shape<Circle> {
public:
  void draw(Context context) { std::cout << "Circle::Draw\n"; }
};

int main() {
  Shape<Rectangle> *shape1 = new Rectangle;
  Shape<Circle> *shape2 = new Circle;
  shape1->do_draw(Context{});
  shape2->do_draw(Context{});
}
