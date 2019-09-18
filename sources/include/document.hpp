#pragma once

/**
 *  \file
 *  \brief Реализация абстракций документа, менеджера документов.
*/


#include <string>
#include <memory>
#include <list>

#include "shape.hpp"

/**
 * \brief Класс документа
 * 
*/
class document final {
public:
    /**
     * Конструктор. 
     * \details Создает объект, ответственный за формат документа
    */
    document() 
    : formatter_(xml_formatter_creator().create_formatter()) {}
    
    /**
     * Сохранение документа
     * \param[in] file_name Имя файла для сохранения
    */
    void save (const std::string& file_name) const {
        UNUSED(file_name);
        shapes_mng_->save(formatter_);
    }

    /**
     * Загрузка документа из файла
     * \param[in] file_name Имя файла для загрузки
    */
    void load(const std::string& file_name) {
        UNUSED(file_name);
        shapes_mng_->load(formatter_);
    }

    /**
     * Метод доступа к менеджеру примитивов
     * \return Указатель на менеджер примитивов
    */
    shapes_manager_ptr get_shapes_manager() const {return shapes_mng_;}

private:
    shapes_manager_ptr shapes_mng_;  ///< Указатель на менеджер примитивов
    formatter_ptr      formatter_;   ///< Указатель на формат документа
};
using document_ptr = std::shared_ptr<document>;

/**
 * \brief   Класс менеджера документов
 * \details Содержит список открытых документов редактора.
 *          Позволяет создавать новые документы, загружать документы,
 *          сохранять документы.
*/
class documents_manager final {
public:
    documents_manager() = default;
    ~documents_manager() = default;

    /**
     * Создание нового документа
     * \return Указатель на созданный документ 
    */
    document_ptr new_document () const {
        return std::make_shared<document>();
    }

    /**
     * Сохранение текущего активного документа
     * \param[in] file_name Имя документа для сохранения
    */
    void save_document(const std::string& file_name) const {
        get_active_doc()->save(file_name);
    }

    /**
     * Загрузка документа
     * \param[in] file_name Имя документа для загрузки
     * \return              Указатель на документ
    */
    document_ptr load_document(const std::string& file_name) const {
        auto doc = std::make_shared<document>();
        doc->load(file_name);
        return doc;
    }

    /**
     * Получение текущего активного документа
     * \return Указатель на активный документ
    */
    document_ptr get_active_doc() const {
        return std::make_shared<document>();
    }

private:
    std::list<document_ptr> documents_;  ///< Список открытых документов
};
using documents_manager_ptr = std::shared_ptr<documents_manager>;
