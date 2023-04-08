#include "column_data.h"

using namespace stats;

ColumnData::ColumnData()
{
    
}

ColumnData::ColumnData(const qint16 column_id,
                       const QString &column_name,
                       const QString &column_description,
                       const bool maintain_a_totals_count)
    : id_(column_id)
    , name_(column_name)
    , description_(column_description)
    , maintain_a_totals_count_(maintain_a_totals_count)
{}
