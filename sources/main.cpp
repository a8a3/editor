
#include <iostream>
#include <vector>
#include <memory>

#include "include/shape.hpp"
#include "include/document.hpp"
#include "include/controller.hpp"

// ------------------------------------------------------------------
class application final {
public:
    application()  = default;
    ~application() = default;

    void on_new_document() const {
        auto new_doc = app_controller_->new_document();
    }

    void on_save_document() const {
        app_controller_->save_document("new_doc");
    }

    void on_load_document() const {
        app_controller_->load_document("saved_doc");
    }

    void on_add_shape(shape_type type) const {
        app_controller_->add_shape(type);
    }

    void on_del_shape(shape_ptr shape) const {
        app_controller_->del_shape(shape);
    }

private:
    application_controller_ptr app_controller_;
};

// ------------------------------------------------------------------
int main() {
    application app;
    app.on_new_document();
    app.on_add_shape(shape_type::circle);
    app.on_add_shape(shape_type::lineseg);
    app.on_save_document();
    return 0;
} 