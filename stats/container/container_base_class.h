#ifndef CONTAINER_BASE_CLASS_H
#define CONTAINER_BASE_CLASS_H

// Qt headers
#include <QtGlobal>
class QTextStream;

namespace stats {

/*! The ContainerBaseClass is a base class for stats containers */
class ContainerBaseClass
{
public:
    ContainerBaseClass() {}

protected:
    static constexpr qint64 no_result_{-1};

private:
    virtual qint64 findPositionInFile(QTextStream &in) = 0;
};
} // namespace stats

#endif // CONTAINER_BASE_CLASS_H
