#include "dpkgrepairwidget.h"
#include "dpkgrepairthread.h"

#include <QVBoxLayout>
#include <QDebug>

DPKGRepairWidget::DPKGRepairWidget(QWidget *parent)
    : QWidget(parent)

    , m_repairButton(new QPushButton)
{
    m_repairButton->setText(tr("Repair"));

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(m_repairButton);
    centralLayout->setAlignment(m_repairButton, Qt::AlignHCenter);

    setLayout(centralLayout);

    connect(m_repairButton, &QPushButton::clicked, this, &DPKGRepairWidget::onRepairClicked);
}

void DPKGRepairWidget::onRepairClicked()
{
    m_repairButton->setVisible(false);

    DPKGRepairThread *thrd = new DPKGRepairThread;

    for (const auto &info : m_toolsProxy->diskInfos())
    {
        if (info.osName.contains("deepin", Qt::CaseInsensitive))
            thrd->appendRoot(info.mountPoint);
    }

    connect(thrd, &DPKGRepairThread::finished, thrd, &DPKGRepairThread::deleteLater);
    connect(thrd, &DPKGRepairThread::finished, this, &DPKGRepairWidget::onRepairFinished);
    connect(thrd, &DPKGRepairThread::processInfo, this, [=](const QString &info) { qDebug() << info; });

    thrd->start();
}

void DPKGRepairWidget::onRepairFinished()
{
    m_repairButton->setVisible(true);
}
