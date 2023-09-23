#include "wifimanager.h"


wifimanager::wifimanager()
{
}
void wifimanager::scan_wifi_networks()
{
    QProcess Process;
    Process.start("netsh",QStringList()<<"wlan"<<"show"<<"network");
    Process.waitForFinished();
    QByteArray RawData=Process.readAllStandardOutput();
    QString Data(RawData);
    Available_WiFi_Networks.clear();
    QStringList DataLines= Data.split('\n');
    for(const QString& line:DataLines){
        if(line.trimmed().startsWith("SSID"))
        {
            QString SSID=line.section(':',1).trimmed();
            if(SSID.isEmpty()==false){
                Available_WiFi_Networks.append(SSID);
            }
        }

    }
}

QStringList wifimanager::Get_Available_WiFi_Networks()
{
    return Available_WiFi_Networks;
}

