#include "editor/data/generate.hpp"

namespace editor
{

  namespace data
  {

    generate::generate(const QString& filename)
      : QFile(filename)
    {
    }

    generate::~generate()
    {
    }


    void generate::open(type_file t)
    {
      if (not QFile::open(QIODevice::WriteOnly | QIODevice::Text))
        Q_ASSERT(false);

      write_header(t);
    }

    void generate::write(const QString& d)
    {
      QString data = d;
      QFile::write(data.append("\n").toUtf8());
    }

    void generate::write_header(type_file t)
    {
      switch (t)
      {
        case PROJECT_FILE:
          write("#################################################################");
          write("#                                                               #");
          write("#               Generated file, do NOT modified.                #");
          write("#                                                               #");
          write("#################################################################");
          write("");
          break;
        case RCC_FILE:
          write("<!-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ -->");
          write("<!--                                                          -->");
          write("<!--            Generated file, do NOT modified.              -->");
          write("<!--                                                          -->");
          write("<!-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ -->");
          write("");
          break;
        case DEFAULT_FILE:
          write("/****************************************************************");
          write("*                                                               *");
          write("*               Generated file, do NOT modified.                *");
          write("*                                                               *");
          write("****************************************************************/");
          write("");
          break;
      }
    }

  } // namespace data

} // namespace editor
