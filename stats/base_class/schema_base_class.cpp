#include "schema_base_class.h"

// Xlsx headers
#include "xlsxdocument.h"

using namespace stats;

/* =========================== */
/*      Schema Base Class      */
/* =========================== */

SchemaBaseClass::SchemaBaseClass() {}

SchemaBaseClass::~SchemaBaseClass() {}

/* ================== */
/*      File i/o      */
/* ================== */

void SchemaBaseClass::write(QXlsx::Document &xlsx, const qint32 row) const
{
    const auto column_end_pos{columnEndPos()};

    for (auto i = first_column_id_; i < column_end_pos; ++i)
        xlsx.write(row, i, get(i));
}
