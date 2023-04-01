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
    SchemaBaseClass() {}
    virtual ~SchemaBaseClass() {}

    //! Get data
    /*! Get item name */
    inline QString name() const { return name_; }

protected:
    // Data
    QString name_;

    static constexpr qint64 no_result_{-1};

private:
    //! File i/o */
    /*! Write the stats row to the spreadsheet */
    virtual void write(QXlsx::Document &xlsx, const qint32 row) const = 0;
};
} // namespace stats

#endif // SCHEMA_BASE_CLASS_H
