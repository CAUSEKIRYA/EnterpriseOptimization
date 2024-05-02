#include "matrixview.h"

MatrixView::MatrixView(Matrix & mt, QObject *parent) :
    QAbstractTableModel{parent},
    mtData(mt)
{ }

QVariant MatrixView::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole)
    {
        return static_cast<int>(Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole)
    {
        return mtData.getAt(index.row(), index.column());
    }
    else return QVariant(QVariant::Invalid);
}

Qt::ItemFlags MatrixView::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
