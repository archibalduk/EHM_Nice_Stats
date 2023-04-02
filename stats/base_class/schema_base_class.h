#ifndef SCHEMA_BASE_CLASS_H
#define SCHEMA_BASE_CLASS_H

// Qt headers
#include <QString>

// Xlsx headers
namespace QXlsx {
class Document;
}

namespace stats {
/*! The SchemaBaseClass class is a base class for Club and Player classes */
class SchemaBaseClass
{
public:
    SchemaBaseClass();
    virtual ~SchemaBaseClass();

    //! File i/o */
    /*! Write the stats row to the spreadsheet */
    void write(QXlsx::Document &xlsx, const qint32 row) const;

    //! Get data
    /*! Get column count */
    virtual qint32 columnEndPos() const = 0;
    /*! Get item name */
    inline QString name() const { return name_; }

    //! Get stats */
    virtual QVariant get(const qint32 column) const = 0;

protected:
    // Data
    QString name_;

    static constexpr qint32 first_column_id_{1}; // Xlsx indexes start at 1
    static constexpr qint64 no_result_{-1};
};
} // namespace stats

#endif // SCHEMA_BASE_CLASS_H
