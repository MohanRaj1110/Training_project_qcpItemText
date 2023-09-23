#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include<QMessageBox>
#include<QDebug>
#include<QtSql>
#include<QSqlDatabase>
#include<QTimer>
#include<QDateTime>
#include <QPushButton>
double a=0.0;
double b=0.0;
QString A,B;
static int opt=0;
static QString array[200]={""};
int index=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)


{
    ui->setupUi(this);
    WiFiMan=new wifimanager();
    WiFi_Timer=new QTimer();
    connect(ui->movecursorleft, &QPushButton::clicked,this,&MainWindow::on_movecursorleft_clicked);
    connect(ui->movecursorright,&QPushButton::clicked,this,&MainWindow::on_movecursorright_clicked);
    connect(WiFi_Timer,SIGNAL(timeout()),this,SLOT(WiFi_Timer_Scan()));
    WiFi_Timer->setInterval(1000);
    WiFi_Timer->start();
    QTimer *RealTime=new QTimer(this);
    connect(RealTime,SIGNAL(timeout()),this,SLOT(showTime()));
    RealTime->start();
    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot->addGraph();
    ui->plot->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(1)->setLineStyle(QCPGraph::lsImpulse);
    ui->plot->xAxis->setLabel("Time");
    ui->plot->yAxis->setLabel("mg/dl");
    ui->plot->xAxis->setRange(0,5);
    ui->plot->yAxis->setRange(0,5);
     ui->plot->setInteraction(QCP::iRangeDrag,true);
    connect(ui->plot,SIGNAL(mousePress(QMouseEvent*)),SLOT(clickedGraph(QMouseEvent*)));
    myTimer=new QTimer(this);
    connect(myTimer,&QTimer::timeout,this,&MainWindow::update_graph);
    ui->stackedWidget->setCurrentIndex(0);
    QSqlDatabase sqlitedb= QSqlDatabase::addDatabase("QSQLITE");
    sqlitedb.setDatabaseName("D:/database/userID.db");
    if(!sqlitedb.open())
        qDebug()<<"cannot open";
    else
        qDebug()<<"connected";



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::update_graph()
{
    QList<double> list1,list2;
    list1<<10<<20<<12<<23<<17<<13<<24<<19<<25;
    list2<<1.55<<2.3<<0.44<<1.26<<1.34<<1.82<<2.6<<3.45<<1.86;
    int i,j=0;
    double value=0.0,time=0.0,time1=0.0,valuelabel=0.0;
    for(i=0;i<9;i++){
        qDebug()<<"haii";
        ui->plot->update();
        ui->plot->graph(1)->setPen(QPen(Qt::red,1));
        qv_x.append(time);
        qv_y.append(5);
        ui->plot->graph(1)->setData(qv_x,qv_y);
        time++;
    }
    for(i=0;i<=9;i++){

        qDebug()<<"hello";

        if(i==j){
            if(i<=9){
        qDebug()<<"if";
        QThread::msleep(1000);
        myTimer->start(1000);
        double div=list1[i]/list2[i];
        value=log10(div);
        qDebug()<<value;
        ui->plot->graph(0)->addData(time1,value);
        ui->plot->replot();
        ui->plot->update();
        QCPItemText *textLabel = new QCPItemText(ui->plot);
        valuelabel=value+0.4;
        textLabel->position->setCoords(time1,valuelabel);// place position at center/top of axis rect
        QString valueAsString = QString::number(value);
        textLabel->setText(valueAsString);
        textLabel->setFont(QFont(font().family(), 8)); // make font a bit larger
        qDebug()<<"plotting";
        time1++;
        if(time1>4){
            ui->plot->xAxis->setRange(time1 -4,time1 +2);
        }
        }
        if(i==9){
            qDebug()<<"stopped";
            myTimer->stop();
        }
        }
        j++;
    }
}
void MainWindow::on_pushButton_clicked()
{
    QString Username=ui->lineEdit_olduser->text();
    QString Password=ui->lineEdit_oldpassword->text();
    QString string3 , string4;
    QSqlQuery qry;
    qry.prepare("select * from userID where username='"+Username+"'");
    qry.exec();
    while (qry.next())
    {
        string3=qry.value(0).toString();
        string4=qry.value(1).toString();

    }

    if(string3 == Username && string4==Password){
        QMessageBox::information(this,"Login","Logged in Successfully...");
        ui->stackedWidget->setCurrentIndex(5);
    }
    else
        QMessageBox::warning(this,"Error","wrong Username or password");


}


void MainWindow::on_pushButton_4_clicked()
{
    QString Username=ui->lineEdit_newusername->text();
    QString Password=ui->lineEdit_newpassword->text();
    QString ConPassword=ui->lineEdit_conpassword->text();
    QString string5;
    QSqlQuery qry;
    qry.prepare("select * from userID where username='"+Username+"'");
    qry.exec();
    while(qry.next()){
        string5=qry.value(0).toString();
    }
    if(Username!=string5){
        qry.prepare("insert into userID(username,password,conpassword)values('"+Username+"','"+Password+"','"+ConPassword+"')");
        qry.exec();
        QMessageBox::information(this,"Information","NewUserID Created");
        ui->stackedWidget->setCurrentIndex(0);
    }
    else
        QMessageBox::warning(this,"Information","This username already taken");

}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    qDebug()<<"next page";

}
void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_pushButton_forget_clicked()
{
    QString Usernamef=ui->lineEdit_olduser->text();
    QString string3;
    QSqlQuery qry;
    qry.prepare("select * from userID where username='"+Usernamef+"'");
    qry.exec();
    if(qry.next())
    {
        string3=qry.value(0).toString();
        ui->stackedWidget->setCurrentIndex(2);
    }
    else
        QMessageBox::warning(this,"Error","write correct Username");
}


void MainWindow::on_pushButton_newpassupdate_clicked()
{
    QString Updatepassword=ui->lineEdit_updatepassword->text();
    QString olduser=ui->lineEdit_olduser->text();
    QString Uconpassword=ui->lineEdit_uconpassword->text();
    QSqlQuery qry;
    if(Updatepassword==Uconpassword){
        qDebug()<<"hello";

        qry.prepare("update userID set password='"+Updatepassword+"',conpassword='"+Uconpassword+"'where username='"+olduser+"'");
        qry.exec();
        QMessageBox::information(this,"Updated Status","Password Updated Successfully");
        ui->stackedWidget->setCurrentIndex(0);

    }
    else
        QMessageBox::information(this,"Updated Status","Content Mismatch");
}


void MainWindow::on_pushButton_Add_clicked()
{
    QString Patientid=ui->lineEdit_ID->text();
    QString Patientname=ui->lineEdit_Name->text();
    QString age=ui->lineEdit_Age->text();
    QString gender=ui->lineEdit_Gender->text();
    QString address=ui->lineEdit_Address->text();
    QDateTime datetime1=QDateTime::currentDateTime();
    QString livedate1=datetime1.toString();
    QString DateOfBirth=ui->lineEdit_DOB->text();

    QSqlQuery qry1;
    if((Patientid!="")&&(Patientname!="")&&(age!="")&&(gender!="")&&(address!="")&&(DateOfBirth!=""))
    {

        qDebug()<<"if entered";
        qry1.prepare("insert into Patientdetails(Patient_ID,Patient_Name,Age,Gender,Address,DateTime,DOB)values('"+Patientid+"','"+Patientname+"','"+age+"','"+gender+"','"+address+"','"+livedate1+"','"+DateOfBirth+"')");
          qDebug()<<livedate1;
        if(qry1.exec()){
            qDebug()<<"exec";
            QMessageBox::information(this,"Status","Details Added Successfully");}
        else{
            qDebug()<<qry1.lastError().text();
            QMessageBox::warning(this,"Status","Error!!!");}
    }
    else
        QMessageBox::warning(this,"Content Error","Fill all the Fields!!!");

}


void MainWindow::on_pushButton_Update_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}



void MainWindow::on_pushButton_Search_clicked()
{
    QString Search=ui->lineEdit_IDsearch->text();
    QString Search_Combo=ui->comboBox_ID_Name->currentText();

    if(Search_Combo=="Patient ID"){
    QSqlQuery qry;
    QString StringName,StringAge,StringGender,StringAddress,StringID,StringDOB;
    qry.prepare("select * from Patientdetails where Patient_ID='"+Search+"'");
    qry.exec();
    while (qry.next())
    {
        StringID=qry.value(1).toString();
        StringName=qry.value(2).toString();
        StringAge=qry.value(3).toString();
        StringGender=qry.value(4).toString();
        StringAddress=qry.value(5).toString();
        StringDOB=qry.value(7).toString();
    }
    ui->lineEdit_SName_2->setText(StringName);
    ui->lineEdit_SID->setText(StringID);
    ui->lineEdit_SAge->setText(StringAge);
    ui->lineEdit_SGender->setText(StringGender);
    ui->lineEdit_ID_SAddress->setText(StringAddress);
    ui->lineEdit_ODOB->setText(StringDOB);
    }
    else if(Search_Combo=="Patient Name"){
    QSqlQuery qry;
    QString StringID,StringAge,StringGender,StringAddress,StringName;
    qry.prepare("select * from Patientdetails where Patient_Name='"+Search+"'");
    qry.exec();
    while (qry.next())
    {

        StringID=qry.value(1).toString();
        StringName=qry.value(2).toString();
        StringAge=qry.value(3).toString();
        StringGender=qry.value(4).toString();
        StringAddress=qry.value(5).toString();
    }
    ui->lineEdit_SName_2->setText(StringName);
    ui->lineEdit_SID->setText(StringID);
    ui->lineEdit_SAge->setText(StringAge);
    ui->lineEdit_SGender->setText(StringGender);
    ui->lineEdit_ID_SAddress->setText(StringAddress);
    }

}


void MainWindow::on_comboBox_ID_Name_activated(const QString &arg1)
{
     QString Search_Combo=ui->comboBox_ID_Name->currentText();
     if(Search_Combo=="Patient Name")
         ui->label_Change->setText("Patient Name");
     else if(Search_Combo=="Patient ID")
         ui->label_Change->setText("Patient ID");

}


void MainWindow::on_pushButton_16_clicked()
{
    QString Patientid=ui->lineEdit_SID->text();
    QString Patientname=ui->lineEdit_SName_2->text();
    QString age=ui->lineEdit_SAge->text();
    QString gender=ui->lineEdit_SGender->text();
    QString address=ui->lineEdit_ID_SAddress->text();
    QSqlQuery qry;
    if((Patientid!="")&&(Patientname!="")&&(age!="")&&(gender!="")&&(address!=""))
    {
        qDebug()<<"if entered";
        qry.prepare("update Patientdetails set Patient_ID='"+Patientid+"',Patient_Name='"+Patientname+"',Age='"+age+"',Gender='"+gender+"',Address='"+address+"' where Patient_ID='"+Patientid+"'");
        if(qry.exec())
            QMessageBox::information(this,"Status","Details Updated Successfully");
        else
            QMessageBox::warning(this,"Status","Error!!!");
    }
    else
        QMessageBox::warning(this,"Content Error","Fill all the Fields!!!");

}



void MainWindow::on_pushButton_17_clicked()
{

     QString Patientid=ui->lineEdit_SID->text();
     if(Patientid!=""){
     QSqlQuery qry;
     qry.prepare("delete from Patientdetails where Patient_ID='"+Patientid+"'");
     qry.exec();
     QMessageBox::information(this,"Status","Details Deleted");
     }
     else
         QMessageBox::warning(this,"Status","ID Missing");
}


void MainWindow::on_pushButton_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_Delete_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}




void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    QSqlQuery query;
        query.prepare("SELECT username FROM userID");
        query.exec();
        int count=0;
        while(query.next())
        {
            QString s=query.value(0).toString();
            array[count]=s;
            count++;
        }
        int count1=0;
        const QSize btnSize = QSize(150, 50);
        for (int i=0;i<15 ;i++ )
        {
            for (int j=0;j<5 ;j++ )
            {
                if(count1==count)
                    break;
                else
                {
                    QPushButton *button = new QPushButton(array[count1]);
                    button->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgb(12, 68, 145), stop: 0.5 rgb(12, 68, 145),  stop:1 rgb(12, 68, 145)); color: white;");
                    QFont font = button->font();
                    font.setBold(true);
                    button->setFont(font);
                    button->setFixedSize(btnSize);
                    button->setObjectName(array[count1]);
                    connect(button, &QPushButton::clicked, this,&MainWindow::connection);
                    ui->gridLayout_2->addWidget(button,i,j);
                    count1++;
                }
    }
}
}
void MainWindow::connection(){

    ui->stackedWidget->setCurrentIndex(10);
    myTimer->start(1000);


}

void MainWindow::on_pushButton_Q_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_Q_3->text());
}


void MainWindow::on_pushButton_D_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_D_3->text());

}


void MainWindow::on_pushButton_W_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_W_3->text());
}


void MainWindow::on_pushButton_E_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_E_3->text());
}


void MainWindow::on_pushButton_R_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_R_3->text());
}


void MainWindow::on_pushButton_T_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_T_3->text());
}


void MainWindow::on_pushButton_Y_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_Y_3->text());
}


void MainWindow::on_pushButton_U_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_U_3->text());
}


void MainWindow::on_pushButton_I_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_I_3->text());
}


void MainWindow::on_pushButton_O_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_O_3->text());
}


void MainWindow::on_pushButton_P_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_P_3->text());
}


void MainWindow::on_pushButton_A_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_A_3->text());
}


void MainWindow::on_pushButton_S_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_S_3->text());
}


void MainWindow::on_pushButton_F_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_F_3->text());
}


void MainWindow::on_pushButton_G_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_G_3->text());
}


void MainWindow::on_pushButton_H_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_H_3->text());
}


void MainWindow::on_pushButton_J_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_J_3->text());
}


void MainWindow::on_pushButton_K_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_K_3->text());
}


void MainWindow::on_pushButton_L_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_L_3->text());
}


void MainWindow::on_pushButton_Z_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_Z_3->text());
}


void MainWindow::on_pushButton_X_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_X_3->text());
}


void MainWindow::on_pushButton_C_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_C_3->text());
}


void MainWindow::on_pushButton_V_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_V_3->text());
}


void MainWindow::on_pushButton_B_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_B_3->text());
}


void MainWindow::on_pushButton_N_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_N_3->text());
}


void MainWindow::on_pushButton_M_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_M_3->text());
}


void MainWindow::on_pushButton_commacaps_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_commacaps_3->text());
}


void MainWindow::on_pushButton_dotcaps_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_dotcaps_3->text());
}


void MainWindow::on_pushButton_Patient_ID_Updataion_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Patient ID");
    opt=1;
}




void MainWindow::on_pushButton_q_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_q_4->text());
}


void MainWindow::on_pushButton_w_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_w_4->text());
}


void MainWindow::on_pushButton_e_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_e_4->text());
}


void MainWindow::on_pushButton_r_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_r_4->text());
}


void MainWindow::on_pushButton_t_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_t_4->text());
}


void MainWindow::on_pushButton_y_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_y_4->text());
}


void MainWindow::on_pushButton_u_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_u_4->text());
}


void MainWindow::on_pushButton_i_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_i_4->text());
}


void MainWindow::on_pushButton_o_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_o_4->text());
}


void MainWindow::on_pushButton_p_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_p_4->text());
}


void MainWindow::on_pushButton_a_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_a_4->text());
}


void MainWindow::on_pushButton_s_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_s_4->text());
}


void MainWindow::on_pushButton_d_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_d_4->text());
}


void MainWindow::on_pushButton_f_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_f_4->text());
}


void MainWindow::on_pushButton_g_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_g_4->text());
}


void MainWindow::on_pushButton_h_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_h_4->text());
}


void MainWindow::on_pushButton_j_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_j_4->text());
}


void MainWindow::on_pushButton_k_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_k_4->text());
}


void MainWindow::on_pushButton_l_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_l_4->text());
}


void MainWindow::on_pushButton_z_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_z_4->text());
}


void MainWindow::on_pushButton_x_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_x_4->text());
}


void MainWindow::on_pushButton_c_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_c_4->text());
}


void MainWindow::on_pushButton_v_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_v_4->text());
}


void MainWindow::on_pushButton_b_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_b_4->text());
}


void MainWindow::on_pushButton_n_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_n_4->text());
}


void MainWindow::on_pushButton_m_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_m_4->text());
}


void MainWindow::on_pushButton_scomma_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_scomma_4->text());
}


void MainWindow::on_pushButton_dotsmall_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_dotsmall_4->text());
}


void MainWindow::on_pushButton_no1_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_no1->text());
}


void MainWindow::on_pushButton_no2_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_no2->text());
}


void MainWindow::on_pushButton_no3_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_no3->text());
}


void MainWindow::on_pushButton_no4_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_no4->text());
}


void MainWindow::on_pushButton_no5_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_no5->text());
}


void MainWindow::on_pushButton_no6_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_no6->text());
}


void MainWindow::on_pushButton_no7_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_no7->text());
}


void MainWindow::on_pushButton_no8_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_no8->text());
}


void MainWindow::on_pushButton_no9_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_no9->text());
}


void MainWindow::on_pushButton_no0_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_no0->text());
}


void MainWindow::on_pushButton_at_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_at->text());
}


void MainWindow::on_pushButton_hash_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_hash->text());
}


void MainWindow::on_pushButton_dollar_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_dollar->text());
}


void MainWindow::on_pushButton_underscore_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_underscore->text());
}


void MainWindow::on_pushButton_and_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+'&');
}


void MainWindow::on_pushButton_minus_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_minus->text());
}


void MainWindow::on_pushButton_plus_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_plus->text());
}


void MainWindow::on_pushButton_lbracket_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_lbracket->text());
}


void MainWindow::on_pushButton_rbracket_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_rbracket->text());
}


void MainWindow::on_pushButton_slash_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_slash->text());
}


void MainWindow::on_pushButton_percent_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_percent->text());
}


void MainWindow::on_pushButton_star_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_star->text());
}


void MainWindow::on_pushButton_dquote_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_dquote->text());
}


void MainWindow::on_pushButton_squote_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_squote->text());
}


void MainWindow::on_pushButton_colon_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_colon->text());
}


void MainWindow::on_pushButton_semicolon_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_semicolon->text());
}


void MainWindow::on_pushButton_exclamatory_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_exclamatory->text());
}


void MainWindow::on_pushButton_questionmark_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_questionmark->text());
}


void MainWindow::on_pushButton_mu_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+"µ");
}


void MainWindow::on_pushButton_backspace_clicked()
{
     ui->lineEdit_small->backspace();
}


void MainWindow::on_pushButton_comma_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_comma->text());
}


void MainWindow::on_pushButton_dotno_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+ui->pushButton_dotno->text());
}





void MainWindow::on_pushButton_LoginUsername_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Username");
    ui->lineEdit_small->setText(ui->lineEdit_olduser->text());
    opt=2;
}


void MainWindow::on_pushButton_LoginPassword_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Password");
    ui->lineEdit_small->setText(ui->lineEdit_oldpassword->text());
    opt=3;
}


void MainWindow::on_pushButton_CreateUsername_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Create Username");
    ui->lineEdit_small->setText(ui->lineEdit_newusername->text());
    opt=4;
}


void MainWindow::on_pushButton_CreatePassword_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Create Password");
    ui->lineEdit_small->setText(ui->lineEdit_newpassword->text());
    opt=5;
}


void MainWindow::on_pushButton_CreateconPassword_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Conform Password");
    ui->lineEdit_small->setText(ui->lineEdit_conpassword->text());
    opt=6;
}



void MainWindow::on_pushButton_NewPassword_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("New Password");
    ui->lineEdit_small->setText(ui->lineEdit_updatepassword->text());
    opt=7;
}


void MainWindow::on_pushButton_NewconPassword_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Conform Password");
    ui->lineEdit_small->setText(ui->lineEdit_uconpassword->text());
    opt=8;
}



void MainWindow::on_pushButton_CPatientID_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Patient ID");
    ui->lineEdit_small->setText(ui->lineEdit_ID->text());
    opt=9;
}


void MainWindow::on_pushButton_CPatientName_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Patient Name");
    ui->lineEdit_small->setText(ui->lineEdit_Name->text());
    opt=10;
}


void MainWindow::on_pushButton_CAge_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Age");
    ui->lineEdit_small->setText(ui->lineEdit_Age->text());
    opt=11;
}


void MainWindow::on_pushButton_CGender_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Gender");
    ui->lineEdit_small->setText(ui->lineEdit_Gender->text());
    opt=12;
}


void MainWindow::on_pushButton_CAddress_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
     ui->label_small->setText("Gender");
     ui->lineEdit_small->setText(ui->lineEdit_Address->text());
    opt=13;
}



void MainWindow::on_pushButton_PatientIDUpdation_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Patient ID");
    ui->lineEdit_small->setText(ui->lineEdit_SID->text());
    opt=14;
}


void MainWindow::on_pushButton_Patient_NameUpdation_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Patient Name");
    ui->lineEdit_small->setText(ui->lineEdit_SName_2->text());
    opt=15;
}


void MainWindow::on_pushButton_AgeUpdation_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Age");
    ui->lineEdit_small->setText(ui->lineEdit_SAge->text());
    opt=16;
}


void MainWindow::on_pushButton_GenderUpdation_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Gender");
    ui->lineEdit_small->setText(ui->lineEdit_SGender->text());
    opt=17;
}


void MainWindow::on_pushButton_AddressUpdation_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->label_small->setText("Address");
    ui->lineEdit_small->setText(ui->lineEdit_ID_SAddress->text());
    opt=18;
}
void MainWindow::on_pushButton_entercaps_3_clicked()
{
    QString text=ui->lineEdit_small->text();
    if(opt==1){
         ui->lineEdit_IDsearch->setText(text);
         ui->stackedWidget->setCurrentIndex(3);

    }
    else if(opt==2){
         ui->lineEdit_olduser->setText(text);
         ui->stackedWidget->setCurrentIndex(0);
    }
    else if(opt==3){
         ui->lineEdit_oldpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(0);
    }
    else if(opt==4){
         ui->lineEdit_newusername->setText(text);
         ui->stackedWidget->setCurrentIndex(1);
    }
    else if(opt==5){
         ui->lineEdit_newpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(1);
    }
    else if(opt==6){
         ui->lineEdit_conpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(1);
    }
    else if(opt==7){
         ui->lineEdit_updatepassword->setText(text);
         ui->stackedWidget->setCurrentIndex(2);
    }
    else if(opt==8){
         ui->lineEdit_uconpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(2);
    }
    else if(opt==9){
         ui->lineEdit_ID->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==10){
         ui->lineEdit_Name->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==11){
         ui->lineEdit_Age->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==12){
         ui->lineEdit_Gender->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==13){
         ui->lineEdit_Address->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==14){
         ui->lineEdit_SID->setText(text);
         ui->stackedWidget->setCurrentIndex(5);
    }
    else if(opt==15){
         ui->lineEdit_SName_2->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
    }
    else if(opt==16){
         ui->lineEdit_SAge->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
    }
    else if(opt==17){
         ui->lineEdit_SGender->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
    }
    else if(opt==18){
         ui->lineEdit_ID_SAddress->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
    }


}


void MainWindow::on_pushButton_casecaps_3_clicked()
{
    QString text=ui->lineEdit_small->text();
    ui->stackedWidget_3->setCurrentIndex(1);
    ui->lineEdit_small->setText(text);
}


void MainWindow::on_pushButton_123s_4_clicked()
{
    QString text=ui->lineEdit_small->text();
    ui->stackedWidget_3->setCurrentIndex(0);
    ui->lineEdit_small->setText(text);

}


void MainWindow::on_pushButton_123caps_3_clicked()
{
    QString text=ui->lineEdit_small->text();
    ui->stackedWidget_3->setCurrentIndex(0);
    ui->lineEdit_small->setText(text);
    ui->lineEdit_small->setText(text);
}


void MainWindow::on_pushButton_abc_clicked()
{
    QString text=ui->lineEdit_small->text();
    ui->stackedWidget_3->setCurrentIndex(1);
    ui->lineEdit_small->setText(text);
}


void MainWindow::on_pushButton_casesmall_4_clicked()
{
    QString text=ui->lineEdit_small->text();
    ui->stackedWidget->setCurrentIndex(9);
    ui->stackedWidget_3->setCurrentIndex(2);
    ui->lineEdit_small->setText(text);
    ui->lineEdit_small->setText(text);
}


void MainWindow::on_pushButton_entersmall_4_clicked()
{
    QString text=ui->lineEdit_small->text();
    if(opt==1){
         ui->lineEdit_IDsearch->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
         ui->lineEdit_small->setText("");
    }
    else if(opt==2){
         ui->lineEdit_olduser->setText(text);
         ui->stackedWidget->setCurrentIndex(0);
         ui->lineEdit_small->setText("");
    }
    else if(opt==3){
         ui->lineEdit_oldpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(0);
         ui->lineEdit_small->setText("");
    }
    else if(opt==4){
         ui->lineEdit_newusername->setText(text);
         ui->stackedWidget->setCurrentIndex(1);
         ui->lineEdit_small->setText("");
    }
    else if(opt==5){
         ui->lineEdit_newpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(1);
         ui->lineEdit_small->setText("");
    }
    else if(opt==6){
         ui->lineEdit_conpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(1);
         ui->lineEdit_small->setText("");
    }
    else if(opt==7){
         ui->lineEdit_updatepassword->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
         ui->lineEdit_small->setText("");
    }
    else if(opt==8){
         ui->lineEdit_uconpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
         ui->lineEdit_small->setText("");
    }
    else if(opt==9){
         ui->lineEdit_ID->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
         ui->lineEdit_small->setText("");
    }
    else if(opt==10){
         ui->lineEdit_Name->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
         ui->lineEdit_small->setText("");
    }
    else if(opt==11){
         ui->lineEdit_Age->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
         ui->lineEdit_small->setText("");
    }
    else if(opt==12){
         ui->lineEdit_Gender->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
         ui->lineEdit_small->setText("");
    }
    else if(opt==13){
         ui->lineEdit_Address->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
         ui->lineEdit_small->setText("");
    }
    else if(opt==14){
         ui->lineEdit_SID->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
         ui->lineEdit_small->setText("");
    }
    else if(opt==15){
         ui->lineEdit_SName_2->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
         ui->lineEdit_small->setText("");
    }
    else if(opt==16){
         ui->lineEdit_SAge->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
         ui->lineEdit_small->setText("");
    }
    else if(opt==17){
         ui->lineEdit_SGender->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
         ui->lineEdit_small->setText("");
    }
    else if(opt==18){
         ui->lineEdit_ID_SAddress->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
         ui->lineEdit_small->setText("");
    }

}



void MainWindow::on_pushButton_enter_clicked()
{
    QString text=ui->lineEdit_small->text();
    if(opt==1){
         ui->lineEdit_IDsearch->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==2){
         ui->lineEdit_olduser->setText(text);
         ui->stackedWidget->setCurrentIndex(0);
    }
    else if(opt==3){
         ui->lineEdit_oldpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(0);
    }
    else if(opt==4){
         ui->lineEdit_newusername->setText(text);
         ui->stackedWidget->setCurrentIndex(1);
    }
    else if(opt==5){
         ui->lineEdit_newpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(1);
    }
    else if(opt==6){
         ui->lineEdit_conpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(1);
    }
    else if(opt==7){
         ui->lineEdit_updatepassword->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==8){
         ui->lineEdit_uconpassword->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==9){
         ui->lineEdit_ID->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==10){
         ui->lineEdit_Name->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==11){
         ui->lineEdit_Age->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==12){
         ui->lineEdit_Gender->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==13){
         ui->lineEdit_Address->setText(text);
         ui->stackedWidget->setCurrentIndex(3);
    }
    else if(opt==14){
         ui->lineEdit_SID->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
    }
    else if(opt==15){
         ui->lineEdit_SName_2->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
    }
    else if(opt==16){
         ui->lineEdit_SAge->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
    }
    else if(opt==17){
         ui->lineEdit_SGender->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
    }
    else if(opt==18){
         ui->lineEdit_ID_SAddress->setText(text);
         ui->stackedWidget->setCurrentIndex(4);
    }

}


void MainWindow::on_pushButton_spacecaps_3_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+' ');
}


void MainWindow::on_pushButton_spacesmall_4_clicked()
{
    ui->lineEdit_small->setText(ui->lineEdit_small->text()+' ');
}


void MainWindow::on_pushButton_space_clicked()
{
     ui->lineEdit_small->setText(ui->lineEdit_small->text()+' ');
}


void MainWindow::on_pushButton_backspacecaps_3_clicked()
{
    ui->lineEdit_small->backspace();
}


void MainWindow::on_pushButton_backspacesmall_4_clicked()
{
    ui->lineEdit_small->backspace();
}



void MainWindow::on_pushButton_LoadData_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("select * from Patientdetails");
    qry.exec();
    model->setQuery(qry);
    ui->table_PatientDetails->setModel(model);
}

void MainWindow::showTime()
{


    QDateTime datetime=QDateTime::currentDateTime();
    QString livedate=datetime.toString();
    ui->label_Date->setText(livedate);



}


void MainWindow::on_pushButton_LoadData_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_back_2_clicked()
{
   ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_back_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_26_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_27_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_pushButton_25_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_22_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_23_clicked()
{
    QString Patientid=ui->lineEdit_SID->text();
    QString Patientname=ui->lineEdit_SName_2->text();
    QString age=ui->lineEdit_SAge->text();
    QString gender=ui->lineEdit_SGender->text();
    QString address=ui->lineEdit_ID_SAddress->text();
    QSqlQuery qry;
    if((Patientid!="")&&(Patientname!="")&&(age!="")&&(gender!="")&&(address!=""))
    {
        qDebug()<<"if entered";
        qry.prepare("update Patientdetails set Patient_ID='"+Patientid+"',Patient_Name='"+Patientname+"',Age='"+age+"',Gender='"+gender+"',Address='"+address+"' where Patient_ID='"+Patientid+"'");
        if(qry.exec())
            QMessageBox::information(this,"Status","Details Updated Successfully");
        else
            QMessageBox::warning(this,"Status","Error!!!");
    }
    else
        QMessageBox::warning(this,"Content Error","Fill all the Fields!!!");




}


void MainWindow::on_pushButton_24_clicked()
{
    QString Patientid=ui->lineEdit_SID->text();
    if(Patientid!=""){
    QSqlQuery qry;
    qry.prepare("delete from Patientdetails where Patient_ID='"+Patientid+"'");
    qry.exec();
    QMessageBox::information(this,"Status","Details Deleted");
    }
    else
        QMessageBox::warning(this,"Status","ID Missing");
}


void MainWindow::on_pushButton_28_clicked()
{
    QString Search=ui->lineEdit_IDsearch->text();
    QString Search_Combo=ui->comboBox_ID_Name->currentText();

    if(Search_Combo=="Patient ID"){
    QSqlQuery qry;
    QString StringName,StringAge,StringGender,StringAddress,StringID;
    qry.prepare("select * from Patientdetails where Patient_ID='"+Search+"'");
    qry.exec();
    while (qry.next())
    {
        StringID=qry.value(1).toString();
        StringName=qry.value(2).toString();
        StringAge=qry.value(3).toString();
        StringGender=qry.value(4).toString();
        StringAddress=qry.value(5).toString();
    }
    ui->lineEdit_SName_2->setText(StringName);
    ui->lineEdit_SID->setText(StringID);
    ui->lineEdit_SAge->setText(StringAge);
    ui->lineEdit_SGender->setText(StringGender);
    ui->lineEdit_ID_SAddress->setText(StringAddress);
    }
    else if(Search_Combo=="Patient Name"){
    QSqlQuery qry;
    QString StringID,StringAge,StringGender,StringAddress,StringName;
    qry.prepare("select * from Patientdetails where Patient_Name='"+Search+"'");
    qry.exec();
    while (qry.next())
    {

        StringID=qry.value(1).toString();
        StringName=qry.value(2).toString();
        StringAge=qry.value(3).toString();
        StringGender=qry.value(4).toString();
        StringAddress=qry.value(5).toString();
    }
    ui->lineEdit_SName_2->setText(StringName);
    ui->lineEdit_SID->setText(StringID);
    ui->lineEdit_SAge->setText(StringAge);
    ui->lineEdit_SGender->setText(StringGender);
    ui->lineEdit_ID_SAddress->setText(StringAddress);
    }
}


void MainWindow::on_pushButton_19_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_20_clicked()
{
    QString Patientid=ui->lineEdit_ID->text();
    QString Patientname=ui->lineEdit_Name->text();
    QString age=ui->lineEdit_Age->text();
    QString gender=ui->lineEdit_Gender->text();
    QString address=ui->lineEdit_Address->text();
    QDateTime datetime1=QDateTime::currentDateTime();
    QString livedate1=datetime1.toString();

    QSqlQuery qry1;
    if((Patientid!="")&&(Patientname!="")&&(age!="")&&(gender!="")&&(address!=""))
    {

        qDebug()<<"if entered";
        qry1.prepare("insert into Patientdetails(Patient_ID,Patient_Name,Age,Gender,Address,DateTime)values('"+Patientid+"','"+Patientname+"','"+age+"','"+gender+"','"+address+"','"+livedate1+"')");
          qDebug()<<livedate1;
        if(qry1.exec()){
            qDebug()<<"exec";
            QMessageBox::information(this,"Status","Details Added Successfully");}
        else{
            qDebug()<<qry1.lastError().text();
            QMessageBox::warning(this,"Status","Error!!!");}
    }
    else
        QMessageBox::warning(this,"Content Error","Fill all the Fields!!!");

}


void MainWindow::on_pushButton_21_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}


void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}


void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

}


void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_pushButton_29_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_back_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::WiFi_Timer_Scan()
{
  WiFiMan->scan_wifi_networks();
  QStringList wifilist=WiFiMan->Get_Available_WiFi_Networks();
  qDebug()<<wifilist;
  ui->comboBox_Wifi->clear();
  ui->comboBox_Wifi->addItems(wifilist);
}



void MainWindow::on_pushButton_37_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_c1_clicked()
{
      ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_c1->text());
}


void MainWindow::on_pushButton_c2_clicked()
{
      ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_c2->text());
}


void MainWindow::on_pushButton_c3_clicked()
{
     ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_c3->text());
}


void MainWindow::on_pushButton_c4_clicked()
{
      ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_c4->text());
}


void MainWindow::on_pushButton_c5_clicked()
{
      ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_c5->text());
}


void MainWindow::on_pushButton_c6_clicked()
{
      ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_c6->text());
}


void MainWindow::on_pushButton_c7_clicked()
{
      ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_c7->text());
}


void MainWindow::on_pushButton_c8_clicked()
{
     ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_c8->text());
}


void MainWindow::on_pushButton_c9_clicked()
{
      ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_c9->text());
}


void MainWindow::on_pushButton_c0_clicked()
{
     ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_c0->text());
}


void MainWindow::on_pushButton_cplus_clicked()
{
    ui->lineEdit_symbol->setText(ui->pushButton_cplus->text());
    A=ui->lineEdit_type->text();
    ui->lineEdit_type->setText("");
}


void MainWindow::on_pushButton_cminus_clicked()
{
      ui->lineEdit_symbol->setText(ui->pushButton_cminus->text());
      A=ui->lineEdit_type->text();
      ui->lineEdit_type->setText("");
}


void MainWindow::on_pushButton_cmultiply_clicked()
{
      ui->lineEdit_symbol->setText(ui->pushButton_cmultiply->text());
      A=ui->lineEdit_type->text();
      ui->lineEdit_type->setText("");
}


void MainWindow::on_pushButton_cequalto_clicked()
{
    QString symbol=ui->lineEdit_symbol->text();
    if(symbol=="+"){
        B=ui->lineEdit_type->text();
        qDebug()<<B;
        a=A.toDouble();
        b=B.toDouble();
        double cal=a+b;
        QString answer = QString::number(cal);
        ui->lineEdit_answer->setText(answer);
        ui->lineEdit_type->setText("");
        ui->lineEdit_symbol->setText("");
        ui->lineEdit_display->setText(A+ui->pushButton_cplus->text()+B);

    }
    else if(symbol=="-"){
        B=ui->lineEdit_type->text();
        qDebug()<<B;
        a=A.toDouble();
        b=B.toDouble();
        double cal=a-b;
        QString answer = QString::number(cal);
        ui->lineEdit_answer->setText(answer);
        ui->lineEdit_type->setText("");
        ui->lineEdit_symbol->setText("");
        ui->lineEdit_display->setText(A+ui->pushButton_cminus->text()+B);

    }
    else if(symbol=="X"){
        B=ui->lineEdit_type->text();
        qDebug()<<B;
        a=A.toDouble();
        b=B.toDouble();
        double cal=a*b;
        QString answer = QString::number(cal);
        ui->lineEdit_answer->setText(answer);
        ui->lineEdit_type->setText("");
        ui->lineEdit_symbol->setText("");
        ui->lineEdit_display->setText(A+ui->pushButton_cmultiply->text()+B);

    }
    else if(symbol=="/"){
        B=ui->lineEdit_type->text();
        qDebug()<<B;
        a=A.toDouble();
        b=B.toDouble();
        double cal=a/b;
        QString answer = QString::number(cal);
        ui->lineEdit_answer->setText(answer);
        ui->lineEdit_type->setText("");
        ui->lineEdit_symbol->setText("");
        ui->lineEdit_display->setText(A+ui->pushButton_divide->text()+B);

    }
    else if(symbol=="log"){
        qDebug()<<B;
        a=A.toDouble();
        double cal=log10(a);
        QString answer = QString::number(cal);
        ui->lineEdit_answer->setText(answer);
        ui->lineEdit_type->setText("");
        ui->lineEdit_symbol->setText("");
        ui->lineEdit_display->setText(ui->pushButton_clog->text()+A);

    }

}


void MainWindow::on_pushButton_clog_clicked()
{
    ui->lineEdit_symbol->setText(ui->pushButton_clog->text());
    A=ui->lineEdit_type->text();
    ui->lineEdit_type->setText("");
}


void MainWindow::on_pushButton_cclear_clicked()
{
     ui->lineEdit_type->backspace();
}


void MainWindow::on_pushButton_38_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_pushButton_divide_clicked()
{
    ui->lineEdit_symbol->setText(ui->pushButton_divide->text());
    A=ui->lineEdit_type->text();
    ui->lineEdit_type->setText("");
}


void MainWindow::on_pushButton_cdot_clicked()
{
    ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_cdot->text());
}


void MainWindow::on_pushButton_ccomma_clicked()
{
    ui->lineEdit_type->setText(ui->lineEdit_type->text()+ui->pushButton_ccomma->text());
}


void MainWindow::on_pushButton_allclear_clicked()
{
    ui->lineEdit_type->setText("");
    ui->lineEdit_symbol->setText("");
    ui->lineEdit_answer->setText("");
    ui->lineEdit_display->setText("");
}


void MainWindow::on_pushButton_42_clicked()
{
    index=5;
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushButton_41_clicked()
{
    index=5;
    ui->stackedWidget->setCurrentIndex(11);
}


void MainWindow::on_pushButton_44_clicked()
{
    index=6;
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_43_clicked()
{
    index=6;
    ui->stackedWidget->setCurrentIndex(11);
}



void MainWindow::on_pushButton_46_clicked()
{
    index=8;
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_45_clicked()
{
    index=8;
    ui->stackedWidget->setCurrentIndex(11);
}


void MainWindow::on_pushButton_48_clicked()
{
    index=10;
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_47_clicked()
{
    index=10;
    ui->stackedWidget->setCurrentIndex(11);
}


void MainWindow::on_pushButton_50_clicked()
{
    ui->stackedWidget->setCurrentIndex(index);
}


void MainWindow::on_pushButton_49_clicked()
{
    ui->stackedWidget->setCurrentIndex(index);
}


void MainWindow::on_movecursorleft_clicked()
{
    int currentposition=ui->lineEdit_small->cursorPosition();
    if(currentposition>0){
        ui->lineEdit_small->setCursorPosition(currentposition-1);
    }
}


void MainWindow::on_movecursorright_clicked()
{
    int currentposition=ui->lineEdit_small->cursorPosition();
    if(currentposition<ui->lineEdit_small->text().length()){
        ui->lineEdit_small->setCursorPosition(currentposition+1);
    }
}


void MainWindow::on_pushButton_52_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}


void MainWindow::on_pushButton_51_clicked()
{
    index=3;
    ui->stackedWidget->setCurrentIndex(12);
}


void MainWindow::on_CalendarWidget_clicked(const QDate &date)
{

    QString  Date=date.toString();
    if(index==3)
    ui->lineEdit_DOB->setText(Date);
    else if(index==4)
      ui->lineEdit_ODOB->setText(Date);
}


void MainWindow::on_pushButton_j_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(index);
}


void MainWindow::on_pushButton_105_clicked()
{
    index=4;
    ui->stackedWidget->setCurrentIndex(12);
}

