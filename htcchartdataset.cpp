// ++++++++++++++++++++++++++++++++++++++++++++ //
// File: htcchartdataset.cpp
// Description: a unit that can be passed to the chart
//
//
// Date: 2019-03-07
//
//
// TODO:
//
//  Added comm check auto detect Aug 2020
//
// ++++++++++++++++++++++++++++++++++++++++++++ //

#include "htcchartdataset.h"



HTCChartDataSet::HTCChartDataSet(QObject *parent)
{
    if (!_numFilesperRangeIsGood.isEmpty())
    {
        _numFilesperRangeIsGood.clear();
    }
    for (int i = 0; i < 3; i++)
    {
        _numFilesperRangeIsGood.append(QString::number(0));
    }

    // --------------------------------- //
    //
    // --------------------------------- //
    _isCommCheckData = false;
    _testValues.append(0);
    _testValues.append(1);
    _testValues.append(2);
}

void HTCChartDataSet::SetData(QStringList data)
{
    _data = data;


}

void HTCChartDataSet::SetChartTitle(QString title)
{
    _chartTitle = title;

    // ------------------------------- //
    // this is the last dataset
    // item that gets set
    // ------------------------------- //
    SetCommCheckAutoDetect();
    // ------------------------------- //
    //
    //
    // ------------------------------- //

}

void HTCChartDataSet::SetModel(QString model)
{
    _model = model;
}

void HTCChartDataSet::SetSerial(QString serial)
{
    _serial = serial;
}

void HTCChartDataSet::SetXAxisTitle(QString title)
{
    _xAxisTitle = title;
}

void HTCChartDataSet::SetYAxisTitle(QString title)
{
    _yAxisTitle = title;
}

void HTCChartDataSet::SetXAxisScale(QString scale)
{
    _xAxisScaling = scale;
}

void HTCChartDataSet::SetYAxisScale(QString scale)
{
    _yAxisTitle = scale;
}

void HTCChartDataSet::SetSampleFileName(QString file)
{
    _sampleFileName = file;
}

void HTCChartDataSet::SetDataSetIndex(int value)
{
    _datasetIDX = value;
}

int HTCChartDataSet::getDataType()
{
    return _dataType;
}

void HTCChartDataSet::setDataType(int dataType)
{
    _dataType = dataType;
}

void HTCChartDataSet::setBaseFolder(QString baseFolder)
{
    _baseFolder = baseFolder;
}


QStringList HTCChartDataSet::GetData()
{
    return _data;
}

QString HTCChartDataSet::GetChartTitle()
{
    return _chartTitle;
}

QString HTCChartDataSet::GetModel()
{
    return _model;
}

QString HTCChartDataSet::GetSerial()
{
    return _serial;
}

QString HTCChartDataSet::GetXAxisTitle()
{
    return _xAxisTitle;
}

QString HTCChartDataSet::GetYAxisTitle()
{
    return _yAxisTitle;
}

QString HTCChartDataSet::GetXAxisScale()
{
    return _xAxisScaling;
}

QString HTCChartDataSet::GetYAxisScale()
{
    return _yAxisScaling;
}

QString HTCChartDataSet::GetSampleFileName()
{
    return _sampleFileName;
}

int HTCChartDataSet::GetDataSetIndex()
{
    return _datasetIDX;
}

bool HTCChartDataSet::GetInitializedOK()
{
    return _initializedOK;
}

QStringList HTCChartDataSet::GetFilesperRangeAreGood()
{
    return _numFilesperRangeIsGood;
}

int HTCChartDataSet::GetFilesPerRangeIsGood(int rangeID)
{
    int result = _numFilesperRangeIsGood[rangeID].toInt();

    return result;
}

void HTCChartDataSet::SetFilesPerRangeIsGood(int RangeID, int value)
{
    _numFilesperRangeIsGood[RangeID] = QString::number(value);
}

QString HTCChartDataSet::GetBaseFolder()
{
    return _baseFolder;
}

bool HTCChartDataSet::GetIsCommCheckData()
{
    return _isCommCheckData;
}




void HTCChartDataSet::setInitializedOKState()
{
    //Assume success
    _initializedOK = true;

    if (_data.isEmpty())
    {
        _initializedOK = false;
    }
    else if (_chartTitle.isEmpty())
    {
        _initializedOK = false;
    }
    else if (_model.isEmpty())
    {
        _initializedOK = false;
    }
    else if (_serial.isEmpty())
    {
        _initializedOK = false;
    }
    else if (_xAxisTitle.isEmpty())
    {
        _initializedOK = false;
    }
    else if (_yAxisTitle.isEmpty())
    {
        _initializedOK = false;
    }
    else if (_xAxisScaling.isEmpty())
    {
        _initializedOK = false;
    }
    else if (_yAxisScaling.isEmpty())
    {
        _initializedOK = false;
    }
}

void HTCChartDataSet::listThisList(QStringList list)
{
    int numItems = list.count();

    for (int i = 0; i < numItems; i++)
    {
        qDebug() << "item " << i << " : " << list[i];
    }
}

void HTCChartDataSet::SetCommCheckAutoDetect()
{
    QString del = getFileDelim();
    QStringList dataList = getMasterList();
    _isCommCheckData = IsCommCheckData(dataList);
}


double HTCChartDataSet::getMin(QList<double> values)
{
    double yMin = std::numeric_limits<double>::max();

    foreach (double i, values)
    {
        yMin = qMin(yMin, i);
    }
    // another way to do it
    //    double yMin = *std::min_element(values.begin(), values.end());

    return yMin;
}

double HTCChartDataSet::getMax(QList<double> values)
{

    double yMax = std::numeric_limits<double>::min();
    foreach (double i, values)
    {
        yMax = qMax(yMax, i);
    }

    return yMax;
}

double HTCChartDataSet::getMean(QList<double> values)
{
    double numValues = values.count();
    double result = -1;
    if (numValues > 0)
    {
        result = values[numValues/2];
    }

    return result;
}

QStringList HTCChartDataSet::getMasterList()
{
    QStringList result;

    QString del = getFileDelim();

    int numlines = _data.count();
    QStringList parts;
    QString target;
    QString newTarget;

    if (numlines > 0)
    {
        // strip off the first line
        // but do the rest
        for (int i = 1; i < numlines; i++)
        {
            target = getShortenedParts(_data[i], del);
            // qDebug() << "adding line " << target;
            result.append(target);
        }

    }

    return result;

}

QString HTCChartDataSet::getShortenedParts(QString target, QString delim)
{
    QString result;
    QStringList temp = target.split(delim);
    int numLines = temp.count();
    for (int i = 1; i < numLines; i++)
    {
        result.append(temp[i]);

        if (i < numLines -1)
        {
            result.append(delim);
        }

    }

    return result;

}

bool HTCChartDataSet::IsCommCheckData(QStringList commCkData)
{
    bool result = true;
    QString delim = ",";
    QString target;
    int numLines = commCkData.count();

    for (int i = 0; i < numLines; i++)
    {
        target = commCkData[i];
        // qDebug() << "testing line " << i << " as " << target;

        if (ThisLineIsCommCk(target,delim) == false)
        {
            // qDebug() << "I bailed becasue I found non comm check data";
            result = false;
            break;
        }

    }

    return result;
}

QString HTCChartDataSet::getFileDelim()
{
    QFileInfo info = QFileInfo(_sampleFileName);
    QString extension = info.suffix();
    QString result;

    if (extension == "txt")
    {
        result = "\t";
    }
    else
    {
        result = ",";
    }

    return result;

}

bool HTCChartDataSet::ThisLineIsCommCk(QString target, QString del)
{
    bool result = false;
    // check this method - not working correctly
    QList<double> myValues = ConvertToDoubleList(target,del);


    double min = getMin(myValues);
    double max = getMax(myValues);
    double mean = getMean(myValues);

    if(_testValues.contains(min) && _testValues.contains(max) && _testValues.contains(mean))
    {
        result = true;
    }

    return result;


}

QList<double> HTCChartDataSet::ConvertToDoubleList(QString target, QString delim)
{
    QStringList list = target.split(delim);

    int numItems = list.count();
    QList<double> l;

    std::sort(list.begin(),list.end());

    for (int i = 0; i < numItems; i++)
    {
        l.append(list[i].toDouble());
    }

    return l;
}
