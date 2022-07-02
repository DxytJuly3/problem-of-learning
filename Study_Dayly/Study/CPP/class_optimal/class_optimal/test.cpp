#include "class_optimal.h"

Widget f(Widget u)
{
    Widget v(u);
    Widget w = v;

    return w;
}

int main()
{
    Widget x;
    Widget w = f(Widget());

    return 0;
}