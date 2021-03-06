#ifndef HTCSETTINGS_H
#define HTCSETTINGS_H

#include <QMainWindow>
#include <QColorDialog>
#include <QDebug>
#include <QIntValidator>
#include <QColor>
#include <QPalette>
#include <QSettings>
#include <QRect>
#include <QListWidgetItem>
#include "positioneditor.h"

namespace Ui {
class HTCSettings;
}

class HTCSettings : public QMainWindow
{
    Q_OBJECT

public:
    explicit HTCSettings(QWidget *parent = nullptr);
    ~HTCSettings();

private slots:
    void on_btnClose_clicked();

    void on_btnPenColor_clicked();

    void ListViewItemSelected();

    void on_btnResetColors_clicked();

    void on_lineXpos_editingFinished();

    void on_lineYpos_editingFinished();

    void on_lineWidth_editingFinished();

    void on_lineHeight_editingFinished();

    void on_lineSize_editingFinished();

    void on_listChartColors_currentTextChanged(const QString &currentText);

    void on_btnApply_clicked();

    void on_comboFontNames_currentIndexChanged(int index);

    void positionItemSelected(QListWidgetItem* item);

    void EditedPositionValueChanged(QString value, int itemNumber);

    void on_radioRILegendAuto_clicked();

    void on_radioRILegendFile_clicked();

    void on_radioAnimationsOn_clicked();

    void on_radioAnimationsOff_clicked();

    void on_radioHoverOn_clicked();

    void on_radioHoverOff_clicked();

    void on_linePaddingValueY_editingFinished();

    void on_comboChartPaddingY_currentIndexChanged(int index);

    // change from here down

    void on_comboRIChartPaddingX_currentIndexChanged(int index);

    void on_lineRIPaddingValueX_editingFinished();

    // to here

    void on_radioCommAutoOn_clicked();

    void on_radioCommAutoOff_clicked();



    void on_comboCIChartPaddingX_currentIndexChanged(int index);

    void on_lineCIPaddingValueX_editingFinished();

    void on_radioFolderSearchSingle_clicked();

    void on_radioFolderSearchRecursive_clicked();

private:
    Ui::HTCSettings *ui;

    void setupControls();
    QColor getColorFromPalette(QPalette pal);
    QColor getNewColor(QColor currentColor);

    void loadColorList();
    void loadFontList();
    void setControlsFont();
    void setValidators();
    void setFormValues();
    void setCombos();

    void saveSettings();
    void loadSettings();
    void setLegendOverrideSelector(bool SetOVerrideOn);
    void setFolderSearchOption(bool SetRecursiveSearchingOn);
    void setEnableChartAnimationsSelector(bool SetAnimationsOn);
    void setEnableHoverCalloutSelector(bool SetCalloutHoverOn);


    bool _EnableRecursiveFolderSearching;
    bool _OverrideLegendValue;
    bool _EnableAnimations;
    bool _EnableHoverCallout;

    bool _busy;
    QFont _formFont;

   QIntValidator *_intValidator;
   QDoubleValidator * _dblValidator;
   QPalette palLabel;
   QRect _layout;



   int _xGeoStart;
   int _yGeoStart;
   int _GeoWidth;
   int _GeoHeight;

   // ---------------------------------------- //
   //
   // Chart X/Y Padding values
   // ---------------------------------------- //
   double _ChartScalePaddingValueY;
   int _ChartPaddingValueY;
   double _ChartRIScalePaddingValueX;
   int _ChartRIPaddingValueX;
   double _ChartCIScalePaddingValueX;
   int _ChartCIPaddingValueX;


   //
   // ---------------------------------------- //
   //
   // Chart comm Check auto detect
   //
   // ---------------------------------------- //
   int _commCheckAutoDetect;
   //
   // ---------------------------------------- //

   int _ChartLegendFontSizeValue;
   int _ChartLegendFontFamilyValue;

   int _defaultXStart = 50;
   int _defaultYStart = 50;
   int _defaultWidth = 960;
   int _defaultHeight = 767;

   int _defaultChartLegendFontSizeValue = 9;
   int _defaultChartLegendFontFamilyValue = 1;

   QRect _defaultLayout = QRect(_defaultXStart, _defaultYStart, _defaultWidth, _defaultHeight);

   int _defaultFontSize = 9;



   QString _ChartPaddingValuesY[2] = {"Off","On"};
   QString _ChartPaddingValuesX[2] = {"Off","On"};
   QString _ChartLegendFontValues[3] = {"Arial","Courier New", "Times New Roman"};



    //variables
    QColor _penColors[13] = {QColor("#FF0000"), QColor("#0000FF"), QColor("#2fc50a"), QColor("#f57900"),
                             QColor("#E61994"), QColor("#4e9a06"), QColor("#204a87"), QColor("#5c3566"),
                             QColor("#8f5902"), QColor("#993faf"), QColor("#830f0f"), QColor("#ab5a50"),
                            QColor("#4e9a06") };

    QColor _penColorsReset[13] = {QColor("#FF0000"), QColor("#0000FF"), QColor("#2fc50a"), QColor("#f57900"),
                                  QColor("#E61994"), QColor("#4e9a06"), QColor("#204a87"), QColor("#5c3566"),
                                  QColor("#8f5902"), QColor("#993faf"), QColor("#830f0f"), QColor("#ab5a50"),
                                 QColor("#4e9a06")};

    // legend position string parts
    PositionEditor *pos;
    QStringList _positions;
    QStringList _defaultPositions;


    void initPositions();
    void loadPositionsList();
};

#endif // HTCSETTINGS_H
