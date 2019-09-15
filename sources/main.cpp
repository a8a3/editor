
/**
 *  \file
 *  \brief Точка входа в приложение.
*/

#include <iostream>

#include "include/shape.hpp"
#include "include/graphics_editor.hpp"

// ------------------------------------------------------------------
int main() {
    try {
        graphics_editor app;
        app.on_new_document();
        app.on_add_shape(shape_type::circle);
        app.on_add_shape(shape_type::lineseg);
        app.on_save_document();
    }
    catch(const std::logic_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch(...) {
        std::cout << "unknown exception" << std::endl;
        return 2;
    }
    return 0;
} 