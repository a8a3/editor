#pragma once

#include "document.hpp"
#include "shape.hpp"

// ------------------------------------------------------------------
class application_controller final {
public:
    application_controller() = default;

    document_ptr new_document () const {
        return docs_mng_->new_document();
    }

    void save_document(const std::string& doc_name) const {
        docs_mng_->save_document(doc_name);
    }

    document_ptr load_document(const std::string& doc_name) const {
        return docs_mng_->load_document(doc_name);
    }

    void add_shape(shape_type type) const {
        auto shapes_mng = docs_mng_->get_active_doc()->get_shapes_manager();
        shapes_mng->add_shape(type);
    }

    void del_shape(shape_ptr shape) const {
        auto shapes_mng = docs_mng_->get_active_doc()->get_shapes_manager();
        shapes_mng->delete_shape(shape);
    }

private:
    documents_manager_ptr docs_mng_;
};
using application_controller_ptr = std::shared_ptr<application_controller>;