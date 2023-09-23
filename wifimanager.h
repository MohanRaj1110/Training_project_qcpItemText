#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H
#include<QtNetwork>
#include<QtWidgets>
#include<QtCore>
#include<QtGui>


class wifimanager
{
public:
    wifimanager();
public:
    void scan_wifi_networks();
    QStringList Get_Available_WiFi_Networks();
private:
    QStringList Available_WiFi_Networks;
};


#endif // WIFIMANAGER_H
