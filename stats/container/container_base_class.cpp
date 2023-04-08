#include "container_base_class.h"

// Xlsx headers
#include "xlsxdocument.h"

using namespace stats;
ContainerBaseClass::ContainerBaseClass() {}

/* ===================== */
/*      Column Data      */
/* ===================== */

void ContainerBaseClass::addColumn(const ColumnData &column)
{
    columns_.push_back(std::move(column));
}

const ColumnData *ContainerBaseClass::column(const qint32 column_id) const
{
    for (const auto &itr : columns_)
        if (itr.id() == static_cast<qint16>(column_id))
            return &itr;

    return nullptr;
}

/* ================== */
/*      File i/o      */
/* ================== */

qint32 ContainerBaseClass::writeHeaderRow(QXlsx::Document &xlsx)
{
    const auto column_end_pos{columnEndPos()};
    auto row{1};

    for (auto column_id = columnStartPos(); column_id < column_end_pos; ++column_id) {
        const auto col{column(column_id)};

        if (!col)
            continue;

        xlsx.write(row, column_id, col->name());
    }

    return ++row; // Returns the next row id
}
