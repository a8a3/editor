#pragma once

#include <memory>
#include <list>

// ------------------------------------------------------------------
enum class shape_type {
    unknown,
    lineseg,
    circle
};

// ------------------------------------------------------------------
class formatter {
public:
    virtual void save() = 0;
};
using formatter_ptr = std::shared_ptr<formatter>;

// ------------------------------------------------------------------
class xml_formatter final : public formatter {
friend class xml_formatters_creator;

private:
    xml_formatter() = default;
public:
    void save() override {}
};

// ------------------------------------------------------------------
class json_formatter final : public formatter{
friend class json_formatters_creator;

private:
    json_formatter() = default;
public:
    void save() override {};
};

// ------------------------------------------------------------------
class formatter_creator {
public:
    virtual formatter_ptr create_formatter() const = 0;
};
using formatter_creator_ptr = std::shared_ptr<formatter_creator>;

// ------------------------------------------------------------------
class xml_formatter_creator final : public formatter_creator{
public:
    formatter_ptr create_formatter() const override {
        return std::shared_ptr<xml_formatter>();
    }
};

// ------------------------------------------------------------------
class json_formatter_creator final: public formatter_creator {
public:
    formatter_ptr create_formatter() const override {
        return std::shared_ptr<json_formatter>();
    }
};

// ------------------------------------------------------------------
class shape {
public:    
    virtual void save(formatter_ptr) const = 0;
    virtual void load(formatter_ptr) = 0;
    virtual ~shape() = default;
};
using shape_ptr = std::shared_ptr<shape>;
using shapes    = std::list<shape_ptr>;


// ------------------------------------------------------------------
class lineseg final : public shape {
    lineseg() = default;
    friend class lineseg_creator;

public:
    void save(formatter_ptr) const override {}
    void load(formatter_ptr)       override {}
};

// ------------------------------------------------------------------
class circle final : public shape {
    circle() = default;
    friend class circle_creator;

public:
    void save(formatter_ptr) const override {}
    void load(formatter_ptr)       override {}
};

namespace {
// ------------------------------------------------------------------
class shape_creator {
public:
    virtual shape_ptr create_shape() const = 0;   
};

// ------------------------------------------------------------------
class lineseg_creator final : public shape_creator{
public:
    shape_ptr create_shape() const override {
        return std::shared_ptr<lineseg>();
    }   
};

// ------------------------------------------------------------------
class circle_creator final : shape_creator {
public:
    shape_ptr create_shape() const override{
        return std::shared_ptr<circle>();
    }   
};
} // namespace

// ------------------------------------------------------------------
class shapes_manager final {
public:    
    shapes_manager() = default;
    ~shapes_manager() = default;

    shape_ptr add_shape(shape_type type) {
        shape_ptr shape;

        switch (type)
        {   
            case shape_type::lineseg: {
                shape = lineseg_creator().create_shape();
                break;
            }
            case shape_type::circle : {
                shape = circle_creator().create_shape();
                break;
            }        
            default: throw std::logic_error("unknown shape type");
        }
        shapes_.push_back(shape);
        return shape;
    }

    void delete_shape(shape_ptr) {}
 
    void save(formatter_ptr) const {}
    void load(formatter_ptr) {}

private:
    shapes shapes_;
};
using shapes_manager_ptr = std::shared_ptr<shapes_manager>;
