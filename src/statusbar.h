// Copyright (c) 2018, The Jetcash Project.
// Licensed under the GNU Lesser General Public License. See LICENSE for details.

#pragma once

#include <QStatusBar>

class QLabel;
class QAbstractItemModel;
class QDataWidgetMapper;

namespace WalletGUI {

class WalletModel;

class WalletStatusBar : public QStatusBar
{
    Q_OBJECT
    Q_DISABLE_COPY(WalletStatusBar)

public:
    explicit WalletStatusBar(QWidget* parent);
    virtual ~WalletStatusBar();

    void setWalletModel(WalletModel* model);

private:
    WalletModel* walletModel_;
    QLabel* m_syncStatusLabel;
    QLabel* m_syncStatusIconLabel;
//    QLabel* m_encryptionStatusIconLabel;
    QLabel* m_peerCountLabel;
    QLabel* m_walletConnectionLabel;
    QLabel* m_jetcashdConnectionLabel;
    QMovie* m_syncMovie;
    QDataWidgetMapper* stateMapper_;
    bool isSynchronized_;

    void nodeStateChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles);
    void updateStatusDescription();
    void updateSyncState();
    void updateEncryptedState(bool isEncrypted);
};

}
