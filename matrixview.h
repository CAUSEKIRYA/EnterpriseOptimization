#ifndef MATRIXVIEW_H
#define MATRIXVIEW_H

#include "matrix.h"

#include <QAbstractTableModel>

class MatrixView : public QAbstractTableModel
{
    Q_OBJECT

    Matrix mtData;

public:
    explicit MatrixView(Matrix & mt, QObject* parent);
    ~MatrixView() = default;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return mtData.getRows(); };
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return mtData.getColumns(); };

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
};

#endif // MATRIXVIEW_H
