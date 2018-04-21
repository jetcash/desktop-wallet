// Copyright (c) 2018, The Jetcash Project.
// Licensed under the GNU Lesser General Public License. See LICENSE for details.

#pragma once

#include <QObject>

namespace WalletGUI {

class SignalHandler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SignalHandler)

public:
    static SignalHandler& instance();

private:
    SignalHandler();
    ~SignalHandler();

    static void sigHandler(int signal);

Q_SIGNALS:
    void quitSignal();
};

}
