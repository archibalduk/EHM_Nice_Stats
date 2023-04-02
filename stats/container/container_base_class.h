#ifndef CONTAINER_BASE_CLASS_H
#define CONTAINER_BASE_CLASS_H

// Qt headers
#include <QtGlobal>
class QString;
class QTextStream;

// Xlsx headers
namespace QXlsx {
class Document;
}

namespace stats {

/*! The ContainerBaseClass is a base class for stats containers */
class ContainerBaseClass
{
public:
    ContainerBaseClass();

protected:
    static constexpr qint64 no_result_{-1};

    //! File i/o */
    /*! Write header row to spreadsheet */
    qint32 writeHeaderRow(QXlsx::Document &xlsx);

private:
    //! Get data: columns */
    /*! Get column end position */
    virtual qint32 columnEndPos() const = 0;
    /*! Get column start position */
    qint32 columnStartPos() const { return 1; } // Xlsx uses 1 as the first column index
    /*! Get column heading description */
    virtual QString columnDescription(const qint32 column) const = 0;
    /*! Get column heading name */
    virtual QString columnName(const qint32 column) const = 0;

    //! Get data */
    /*! Find the file position of the stats section of a file */
    virtual qint64 findPositionInFile(QTextStream &in) = 0;
};
} // namespace stats

#endif // CONTAINER_BASE_CLASS_H
