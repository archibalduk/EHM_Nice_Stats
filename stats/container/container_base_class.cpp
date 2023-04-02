#include "container_base_class.h"

// Xlsx headers
#include "xlsxdocument.h"

using namespace stats;
ContainerBaseClass::ContainerBaseClass() {}

/* ================== */
/*      File i/o      */
/* ================== */

qint32 ContainerBaseClass::writeHeaderRow(QXlsx::Document &xlsx)
{
    const auto column_end_pos{columnEndPos()};
    auto row{1};

    for (auto column = columnStartPos(); column < column_end_pos; ++column)
        xlsx.write(row, column, columnName(column));

    return ++row; // Returns the next row id
}
