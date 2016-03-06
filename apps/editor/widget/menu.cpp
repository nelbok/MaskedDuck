#include <QMessageBox>
#include <QApplication>

#include "editor/widget/tools/edit_world.hpp"
#include "editor/widget/tools/select_world.hpp"
#include "menu.hpp"

namespace editor
{

  namespace widget
  {

    menu::menu(editor_world_ptr w, QWidget* parent)
      : QMenuBar(parent)
      , world_(w)
    {
      init();
    }


    void menu::init()
    {
      QMenu* m_file = addMenu("File");
      m_file->addAction("Load", this, SLOT(do_load()));
      m_file->addAction("Save", this, SLOT(do_save()));
      m_file->addSeparator();
      m_file->addAction("Quit", qApp, SLOT(quit()));

      QMenu* m_tools = addMenu("Tools");
      m_tools->addAction("Edit world", this, SLOT(do_edit()));
      m_tools->addSeparator();
      m_tools->addAction("Generate world", this, SLOT(do_generate()));

      addAction("About Qt", qApp, SLOT(aboutQt()));
    }


    // File Menu slots

    void menu::do_load()
    {
      (new tools::select_world(world_, this))->show();
    }

    void menu::do_save()
    {
      world_->save();
      QMessageBox::information(this, "Save", "The project was saved.", QMessageBox::Ok);
    }

    // Tools Menu slots

    void menu::do_edit()
    {
      (new tools::edit_world(world_, this))->show();
    }

    void menu::do_generate()
    {
      world_->generate();
      QMessageBox::information(this, "Generate", "The project was generated.", QMessageBox::Ok);
    }

  } // namespace widget

} // namespace editor
