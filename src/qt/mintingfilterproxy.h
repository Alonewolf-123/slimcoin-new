// Copyright (c) 2012-2020 The Slimcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SLIMCOIN_QT_MINTINGFILTERPROXY_H
#define SLIMCOIN_QT_MINTINGFILTERPROXY_H

#include <QSortFilterProxyModel>

class MintingFilterProxy : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit MintingFilterProxy(QObject *parent = 0);
};

#endif // SLIMCOIN_QT_MINTINGFILTERPROXY_H
