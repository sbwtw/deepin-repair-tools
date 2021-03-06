#ifndef REPAIRTOOLS_H
#define REPAIRTOOLS_H

#include "toolsmodel.h"
#include "diskutils.h"

#include <QPointer>

#include <DMainWindow>

DWIDGET_USE_NAMESPACE

class RepairTools : public DMainWindow
{
    Q_OBJECT

public:
    explicit RepairTools(QWidget *parent = nullptr);

private:
    void keyPressEvent(QKeyEvent *e);

private slots:
    void onDiskInitilized();

private:
    QPointer<DiskUtils> m_diskUtils;
    QPointer<ToolsModel> m_toolsModel;
};

#endif // REPAIRTOOLS_H
