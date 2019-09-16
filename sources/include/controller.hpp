#pragma once

#include "document.hpp"
#include "shape.hpp"

/**
 *  \brief   Класс контроллера приложения
 *  \details Скрывает детали реализации от приложения.
 * 
 */
class application_controller final {
public:
    application_controller() = default;

    /**
     *  \brief  Функция создания нового документа
     *  \return Указатель на созданный документ
     */
    document_ptr new_document () const {
        return docs_mng_->new_document();
    }

    /**
     *  \brief Функция сохранения документа в файл
     * 
     *  \param[in] doc_name Имя файла для сохранения
     */
     void save_document(const std::string& doc_name) const {
        docs_mng_->save_document(doc_name);
    }

    /**
     *  \brief Функция загрузки документа из файла
     * 
     *  \param[in] doc_name Имя файла для загрузки
     *  \return             Указатель на загруженный документ
     */
    document_ptr load_document(const std::string& doc_name) const {
        return docs_mng_->load_document(doc_name);
    }

    /**
     *  \brief Функция добавления примитива
     * 
     *  \param[in] type Тип примитива
     */
    void add_shape(shape_type type) const {
        auto shapes_mng = docs_mng_->get_active_doc()->get_shapes_manager();
        shapes_mng->add_shape(type);
    }

     /**
     *  \brief Функция удаления примитива
     * 
     *  \param[in] shape Указатель на удаляемый примитив
     */
   void del_shape(shape_ptr shape) const {
        auto shapes_mng = docs_mng_->get_active_doc()->get_shapes_manager();
        shapes_mng->delete_shape(shape);
    }

private:
    documents_manager_ptr docs_mng_; /// Указатель на менеджер документов
};
using application_controller_ptr = std::shared_ptr<application_controller>;