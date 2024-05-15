#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject *parent) : QFileSystemModel(parent)
{
    setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    setRootPath(QDir::rootPath());
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return "Имя";
        case 1:
            return "Размер";
        case 2:
            return "Тип";
        case 3:
            return "Дата изменения";
        }
    }
    return QFileSystemModel::headerData(section, orientation, role);
}
