#ifndef HTCCHARTFOLDER_H
#define HTCCHARTFOLDER_H

#include <QObject>
#include <QDir>
#include <QDebug>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>
#include "htcchartdatafile.h"



class HTCChartFolder : public QObject
{
    Q_OBJECT
public:
    explicit HTCChartFolder(QObject *parent = nullptr);

    int init(QString folder, QString extension, int dType);
    int initSingle(QString folder, QString extension, int dType);
    int initRecursive(QString folder, QString extension, int dType);

    QStringList GetSingleList(QString path);

    QStringList GetFolderList();
    QStringList GetDataSetNames();
    QStringList GetTaggedList();

    int getDataType();


signals:
    void messageToStatusBar(QString msg);

public slots:

private:

    // new
    int RIdataType = 0;
    int CIdataType = 1;

    int _dataType = -1;
    QString BAD_FILE_DATA = "UNKNOWN-NO-DATA";

    // existing
    int _numberOfFiles;
    QStringList _folderList;
    QStringList _fileCountList;
    QStringList _sets;
    QStringList _MatchingTestCodes;
    QStringList _riMatchingTestCodes;
    QStringList _ciMatchingTestCodes;

    QStringList _TaggedList;

    bool _EnableRecursiveFolderSearching;

    void setDataType(int dataType);

    void fillTaggedList();

    int doesTypeMatch(QString testCode, int dType);
    bool areNumberOfPartsCorrect(QString fileName, QString delim, int dType);

    //QStringList CountFiles(QString path);
    int CountAllFiles(QString path);
    int CountLocalFiles(QString path);
    QStringList GetLocalFilesList(QString path);

    void listThisList(QStringList target, QString delim);
    void listThisFileList(QFileInfoList fList);

    void showBadFileDataMessage(QString fileName);
    void showBadFileDelimCountMessage(QString fileName);

    void loadSettings();

};

#endif // HTCCHARTFOLDER_H
