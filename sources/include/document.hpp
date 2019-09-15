#pragma once

#include <string>
#include <memory>
#include <list>

#include "shape.hpp"

// ------------------------------------------------------------------
class document final {
public:
    document() 
    : formatter_creator_(std::make_shared<xml_formatter_creator>()) {}

    void save (const std::string&) const {
        shapes_mng_->save(formatter_creator_->create_formatter());
    }

    void load(const std::string&) {
        shapes_mng_->load(formatter_creator_->create_formatter());
    }

    shapes_manager_ptr get_shapes_manager() const {return shapes_mng_;}

private:
    shapes_manager_ptr    shapes_mng_;
    formatter_creator_ptr formatter_creator_;
};
using document_ptr = std::shared_ptr<document>;

// ------------------------------------------------------------------
class documents_manager final {
public:
    documents_manager() = default;
    ~documents_manager() = default;

    document_ptr new_document () const {
        return std::make_shared<document>();
    }

    void save_document(const std::string& doc_name) const {
        get_active_doc()->save(doc_name);
    }

    document_ptr load_document(const std::string& file_name) const {
        auto doc = std::make_shared<document>();
        doc->load(file_name);
        return doc;
    }

    document_ptr get_active_doc() const {
        return std::make_shared<document>();
    }

private:
    std::list<document_ptr> documents_;    
};
using documents_manager_ptr = std::shared_ptr<documents_manager>;
