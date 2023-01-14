#include "paraminterface.h"
#include "parammanager.h"
#include "treeitem.h"
#include "display.h"
#include <regex>
#include <QDir>
namespace{
    QString current_pm = "owl2";
}
ParamInterface::ParamInterface(QObject *parent)
    : QAbstractItemModel(parent),rootItem(nullptr) {
    setupModelData();
}
QString ParamInterface::judgeType(const QVariant& value) const{
    const static std::regex boolExp("true|false|t|f",std::regex_constants::icase);
    const static std::regex doubleExp("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$");
    const static std::regex integerExp("^(0|[1-9][0-9]*)$");
    if(std::regex_match(value.toString().toUtf8().constData(),boolExp))
        return "Bool";
    else if(std::regex_match(value.toString().toUtf8().constData(),integerExp))
        return "Int";
    else if(std::regex_match(value.toString().toUtf8().constData(),doubleExp))
        return "Double";
    else
        return "String";
}
QHash<int,QByteArray> ParamInterface::roleNames() const {
     QHash<int, QByteArray> result = QAbstractItemModel::roleNames();
     result.insert(KeyRole, QByteArrayLiteral("settingName"));
     result.insert(TypeRole, QByteArrayLiteral("settingType"));
     result.insert(ValueRole, QByteArrayLiteral("settingValue"));
     return result;
}
Qt::ItemFlags ParamInterface::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return 0;
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
bool ParamInterface::setData(const QModelIndex &index, const QVariant &value,int role){
    Q_UNUSED(role)
    if (!index.isValid()){
        qDebug() << "FUCKME!!!!!!!!";
        return false;
    }
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    item->changeData(2,value.toString());
    item->changeData(1,judgeType(value));
    if (current_pm == "cfg")
        Owl::CParamManager::Instance()->updateParam(item->parentItem()->data(0), item->data(0), value, true);
    else if (current_pm == "simulator")
        Owl::SIParamManager::Instance()->changeParam(item->parentItem()->data(0), item->data(0), value);
    else if (current_pm == "skill")
        Owl::SKParamManager::Instance()->changeParam(item->parentItem()->data(0), item->data(0), value);
    else if (current_pm == "vision")
        Owl::VParamManager::Instance()->updateParam(item->parentItem()->data(0), item->data(0), value, true);
    else
        Owl::OParamManager::Instance()->updateParam(item->parentItem()->data(0),item->data(0),value,true);
    qDebug() << item->parentItem()->data(0) << item->data(0) << value.toString();
    emit dataChanged(index, index);
    return true;
}
QVariant ParamInterface::data(const QModelIndex &index, int role) const {
//    qDebug() << role - KeyRole;
    if (index.isValid() && role >= KeyRole) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item->data(role - KeyRole);
    }
    return QVariant("Error");
}
QString ParamInterface::getType(const QModelIndex &index){
    if(index.isValid()){
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return judgeType(item->data(2));
    }
    return "Invalid";
}
void ParamInterface::reload(){
    QDialog dialog;
    QFormLayout form(&dialog);
    form.addRow(new QLabel("Choose Parameter:"));
    QComboBox* comboBox = new QComboBox(&dialog);
    QDir dir;
    dir.setCurrent(qApp->applicationDirPath() + "/../data/");
    dir.setNameFilters(QStringList() << "*.ini");
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QStringList s = fileInfo.fileName().split(".");
        QString str;
        if (s.count() > 0) str = s[0];
        comboBox->addItem(str);
    }
    comboBox->setCurrentIndex(0);
    form.addRow(comboBox);
    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    if (dialog.exec() == QDialog::Accepted) {
        current_pm = comboBox->currentText();
    }
    beginResetModel();
    if (current_pm == "cfg") {
        Owl::CParamManager::Instance()->sync();
        Owl::CParamManager::Instance()->loadParamFromFile();
    }
    else if (current_pm == "simulator")
        Owl::SIParamManager::Instance()->sync();
    else if (current_pm == "skill")
        Owl::SKParamManager::Instance()->sync();
    else if (current_pm == "vision") {
        Owl::VParamManager::Instance()->sync();
        Owl::VParamManager::Instance()->loadParamFromFile();
    }
    else {
        Owl::OParamManager::Instance()->sync();
        Owl::OParamManager::Instance()->loadParamFromFile();
    }
    setupModelData();
    endResetModel();
    this->resetInternalData();
}
QModelIndex ParamInterface::parent(const QModelIndex &index) const{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
int ParamInterface::columnCount(const QModelIndex &parent) const{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}
int ParamInterface::rowCount(const QModelIndex &parent) const{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    return parentItem->childCount();
}
QModelIndex ParamInterface::index(int row, int column,const QModelIndex &parent) const{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
void ParamInterface::setupModelData(){
    if(rootItem != nullptr){
        delete rootItem;
        rootItem = nullptr;
    }
    QList<QString> rootData;
    rootData << "settingName" << "settingType" << "settingValue";
    rootItem = new TreeItem(rootData);
    if (current_pm == "cfg")
        setParamTree(Owl::CParamManager::Instance());
    else if (current_pm == "simulator")
        setParamTree(Owl::SIParamManager::Instance());
    else if (current_pm == "skill")
        setParamTree(Owl::SKParamManager::Instance());
    else if (current_pm == "vision")
        setParamTree(Owl::VParamManager::Instance());
    else
        setParamTree(Owl::OParamManager::Instance());
}

template<typename T>
void ParamInterface::setParamTree(T pm) {
    foreach(QString groupName, pm->allGroups()) {
        QStringList value;
        value << groupName << " " << " ";
        auto* groupParent = new TreeItem(value, rootItem);
        rootItem->appendChild(groupParent);
        foreach(QString key, pm->allKeys(groupName)) {
            auto&& temp = pm->value(groupName, key).toString();
            QStringList value;
            value << key << judgeType(temp) << temp;
            groupParent->appendChild(new TreeItem(value, groupParent));
        }
    }
}
