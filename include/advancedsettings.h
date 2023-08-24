#ifndef ADVANCEDSETTINGS_H
#define ADVANCEDSETTINGS_H

#include <QWidget>

namespace Ui {
class AdvancedSettings;
}

class AdvancedSettings : public QWidget
{
    Q_OBJECT

public:
    explicit AdvancedSettings(QWidget *parent = nullptr);
    ~AdvancedSettings();

    void createWidgetsConnections();

private slots:
    void on_rbMarkerBasedNormalization_toggled(bool checked);
    void on_pbOk_clicked();

signals:
    void toggledNormalization(int norm_type);

private:
    Ui::AdvancedSettings *ui;
};

#endif // ADVANCEDSETTINGS_H
