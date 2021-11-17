cgit logo	index : qt/qtcharts.git

5.15

QtCharts module
summaryrefslogtreecommitdiffstats

log msg


path: root/examples/charts/candlestickchart/candlestickdatareader.cpp
blob: fb3dcae2fbf37c07f0ed1ac91813871fa3202dc9 (plain)
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "candlestickdatareader.h"

CandlestickDataReader::CandlestickDataReader(QIODevice *device)
    : QTextStream(device)
{
}

CandlestickDataReader::~CandlestickDataReader()
{
}

void CandlestickDataReader::readFile(QIODevice *device)
{
    QTextStream::setDevice(device);
}

QCandlestickSet *CandlestickDataReader::readCandlestickSet()
{
    //! [1]
    QString line = readLine();
    if (line.startsWith("#") || line.isEmpty())
        return 0;
    //! [1]

    //! [2]
    QStringList strList = line.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    if (strList.count() != 5)
        return 0;
    //! [2]

    //! [3]
    const qreal timestamp = strList.at(0).toDouble();
    const qreal open = strList.at(1).toDouble();
    const qreal high = strList.at(2).toDouble();
    const qreal low = strList.at(3).toDouble();
    const qreal close = strList.at(4).toDouble();
    //! [3]

    //! [4]
    QCandlestickSet *candlestickSet = new QCandlestickSet(timestamp);
    candlestickSet->setOpen(open);
    candlestickSet->setHigh(high);
    candlestickSet->setLow(low);
    candlestickSet->setClose(close);
    //! [4]

    return candlestickSet;
}
