#ifndef EDITOR_DATA_GENERATE_HPP
# define EDITOR_DATA_GENERATE_HPP

# include <QFile>

namespace editor
{

  namespace data
  {

    /*!
     *  Generate class.\n
     *  Core of the generated files.
     */

    class generate : public QFile
    {
      public:
        /*!
         *  List of the different context for a file.
         */
        enum type_file
        {
          PROJECT_FILE, /*!< For Qt project files, use # for the comments. */
          RCC_FILE,     /*!< For resource files, use <!-- and --> for the comments. */
          DEFAULT_FILE  /*!< For source and headers C++ files, use / * and * / for the comments. */
        };

        generate(const QString& filename);
        virtual ~generate();

        /*!
         *  Open the file and write the header in function of the type file.
         * \param t Context of the file, by default, source and headers C++ files.
         */
        void open(type_file t = DEFAULT_FILE);
        void write(const QString& data);
        void write_header(type_file t);

    };

  } // namespace data

} // namespace editor

#endif // EDITOR_DATA_GENERATE_HPP
