#pragma once

/**
 *  \file
 *  \brief Реализация абстракций графического примитива, менеджера графических примитивов,
 *         формата документа.
*/


#include <memory>
#include <list>

#define UNUSED(x) ((void)x)

/**
 * \brief Тип графического примитива
*/
enum class shape_type {
    unknown, ///< Тип не известен
    lineseg, ///< Отрезок
    circle   ///< Окружность
};

/**
 * \brief Класс формата документа
 * \details Базовый класс формата документа
 * \todo    Представить интерфейс для сохранения примитивов
*/
class formatter {
public:
    /**
     * Сохранение примитива
    */
    virtual void save() = 0;
    virtual ~formatter() = default;
};
using formatter_ptr = std::shared_ptr<formatter>;

/**
 * \brief Класс xml- формата документа
*/
class xml_formatter final : public formatter {
friend class xml_formatters_creator;

private:
    xml_formatter() = default;

public:
    /**
     * Сохранение примитива
    */
    void save() override {}
};

/**
 * \brief Класс json- формата документа
*/
class json_formatter final : public formatter{
friend class json_formatters_creator;

private:
    json_formatter() = default;

public:
    /**
     * Сохранение примитива
    */
    void save() override {};
};

/**
 * \brief Класс фабрики для создания форматов документа
*/
class formatter_creator {
public:
    /**
     * Создание формата документа
     * \return Указатель на формат документа
    */
    virtual std::unique_ptr<formatter> create_formatter() const = 0;
    virtual ~formatter_creator() = default;
};
using formatter_creator_ptr = std::shared_ptr<formatter_creator>;

/**
 * \brief Класс фабрики для создания xml- формата документа
*/
class xml_formatter_creator final : public formatter_creator{
public:

    /**
     * Создание xml- формата документа
     * \return Указатель на xml- формат документа
    */
    std::unique_ptr<formatter> create_formatter() const override {
        return std::unique_ptr<xml_formatter>();
    }
};

/**
 * \brief Класс json- формата документа
*/
class json_formatter_creator final: public formatter_creator {
public:
    /**
     * Создание json- формата документа
     * \return Указатель на json- формат документа
    */
    std::unique_ptr<formatter> create_formatter() const override {
        return std::unique_ptr<json_formatter>();
    }
};

/**
 * \brief Класс графического примитива
 * \details Предоставляет интерфейс для графического примитива
*/
class shape {
public:    
    /**
     * Сохранение примитива
     * \param[in] formatter Формат документа
    */
    virtual void save(formatter_ptr formatter) const = 0;
    /**
     * Загрузка примитива
     * \param[in] formatter Формат документа
    */
    virtual void load(formatter_ptr formatter)       = 0;
    virtual ~shape() = default;
};
using shape_ptr = std::shared_ptr<shape>;
using shapes    = std::list<shape_ptr>;


/**
 * \brief Класс графического примитива 'Отрезок'
*/
class lineseg final : public shape {
    lineseg() = default;
    friend class lineseg_creator;

public:
    /**
     * Сохранение отрезка
     * \param[in] formatter Формат документа
    */
    void save(formatter_ptr) const override {}
    /**
     * Загрузка отрезка
     * \param[in] formatter Формат документа
    */
    void load(formatter_ptr)       override {}
};

/**
 * \brief Класс графического примитива 'Окружность'
*/
class circle final : public shape {
    circle() = default;
    friend class circle_creator;

public:
    /**
     * Сохранение окружности
     * \param[in] formatter Формат документа
    */
    void save(formatter_ptr) const override {}
    /**
     * Загрузка окружности
     * \param[in] formatter Формат документа
    */
    void load(formatter_ptr) override {}
};

namespace {
// ------------------------------------------------------------------
class shape_creator {
public:
    virtual std::unique_ptr<shape> create_shape() const = 0;   
    virtual ~shape_creator() = default;
};

// ------------------------------------------------------------------
class lineseg_creator final : public shape_creator{
public:
    std::unique_ptr<shape> create_shape() const override {
        return std::unique_ptr<lineseg>();
    }   
};

// ------------------------------------------------------------------
class circle_creator final : shape_creator {
public:
    std::unique_ptr<shape> create_shape() const override{
        return std::unique_ptr<circle>();
    }   
};
} // namespace

/**
 * \brief Класс менеджера графических примитивов.
*/
class shapes_manager final {
public:    
    shapes_manager() = default;
    ~shapes_manager() = default;

    /**
     * Добавить графический примитив
     * \details Создает новый графический примитив и добавляет его в список хранения.
     * \param[in] type Тип графического примитива
    */
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

    /**
     * Удалить графический примитив
     * \details Удаляет примитив из списка хранения
     * \param[in] shape Указатель на удаляемый примитив
    */
    void delete_shape(shape_ptr shape) {
        UNUSED(shape);
    }
 
    /**
     * Сохранение примитивов в заданном формате
     * \details Сохраняет документы из списка хранения
     * \param[in] formatter Формат документа 
    */
    void save(formatter_ptr formatter) const {
        UNUSED(formatter);
    }

    /**
     * Загружка примитивов в заданном формате
     * \details Загружает примитивы в список хранения
     * \param[in] formatter Формат документа 
    */
    void load(formatter_ptr formatter) {
        UNUSED(formatter);
    }

private:
    shapes shapes_; ///< Список графических примитивов
};
using shapes_manager_ptr = std::shared_ptr<shapes_manager>;
