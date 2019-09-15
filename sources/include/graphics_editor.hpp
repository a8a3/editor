#pragma once

#include "shape.hpp"
#include "controller.hpp"

/**
 * \brief Класс графического редактора
 * 
 * 
 */
class graphics_editor final {
public:
    graphics_editor()  = default;
    ~graphics_editor() = default;

    /**
     * Обработчик команды создания нового файла.
    */
    void on_new_document() const {
        auto new_doc = app_controller_->new_document();
    }

    /**
     * Обработчик команды сохранения файла.
    */
    void on_save_document() const {
        app_controller_->save_document("new_doc");
    }

    /**
     * Обработчик команды загрузки файла.
    */
    void on_load_document() const {
        app_controller_->load_document("saved_doc");
    }

    /**
     * Обработчик команды добавления графического примитива.
     * \param[in] type Тип добавляемого примитива.
     */
    void on_add_shape(shape_type type) const {
        app_controller_->add_shape(type);
    }

    /**
     * Обработчик команды удаления графического файла.
     * \param[in] Указатель на удаляемый примитив.
    */
    void on_del_shape(shape_ptr shape) const {
        app_controller_->del_shape(shape);
    }

private:
    application_controller_ptr app_controller_; /// Контроллер приложения
};
