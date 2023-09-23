#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "secondwindow.h"
#include "wifimanager.h"
#include <QMainWindow>
#include <QTimer>
#include<QtSql>
#include<QSqlDatabase>
#include<qcustomplot.h>

extern QString name,A,B;
extern QStringList list1,list2;
extern double a,b;
extern int index;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void update_graph();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_forget_clicked();

    void on_pushButton_newpassupdate_clicked();

    void on_pushButton_Add_clicked();

    void on_pushButton_Update_clicked();

    void on_pushButton_Search_clicked();

    void on_comboBox_ID_Name_activated(const QString &arg1);

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_back_clicked();

    void connection();

    void on_pushButton_Delete_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_Q_3_clicked();

    void on_pushButton_D_3_clicked();

    void on_pushButton_W_3_clicked();

    void on_pushButton_E_3_clicked();

    void on_pushButton_R_3_clicked();

    void on_pushButton_T_3_clicked();

    void on_pushButton_Y_3_clicked();

    void on_pushButton_U_3_clicked();

    void on_pushButton_I_3_clicked();

    void on_pushButton_O_3_clicked();

    void on_pushButton_P_3_clicked();

    void on_pushButton_A_3_clicked();

    void on_pushButton_S_3_clicked();

    void on_pushButton_F_3_clicked();

    void on_pushButton_G_3_clicked();

    void on_pushButton_H_3_clicked();

    void on_pushButton_J_3_clicked();

    void on_pushButton_K_3_clicked();

    void on_pushButton_L_3_clicked();

    void on_pushButton_Z_3_clicked();

    void on_pushButton_X_3_clicked();

    void on_pushButton_C_3_clicked();

    void on_pushButton_V_3_clicked();

    void on_pushButton_B_3_clicked();

    void on_pushButton_N_3_clicked();

    void on_pushButton_M_3_clicked();

    void on_pushButton_commacaps_3_clicked();

    void on_pushButton_dotcaps_3_clicked();

    void on_pushButton_Patient_ID_Updataion_clicked();

    void on_pushButton_entercaps_3_clicked();

    void on_pushButton_q_4_clicked();

    void on_pushButton_w_4_clicked();

    void on_pushButton_e_4_clicked();

    void on_pushButton_r_4_clicked();

    void on_pushButton_t_4_clicked();

    void on_pushButton_y_4_clicked();

    void on_pushButton_u_4_clicked();

    void on_pushButton_i_4_clicked();

    void on_pushButton_o_4_clicked();

    void on_pushButton_p_4_clicked();

    void on_pushButton_a_4_clicked();

    void on_pushButton_s_4_clicked();

    void on_pushButton_d_4_clicked();

    void on_pushButton_f_4_clicked();

    void on_pushButton_g_4_clicked();

    void on_pushButton_h_4_clicked();

    void on_pushButton_j_4_clicked();

    void on_pushButton_k_4_clicked();

    void on_pushButton_l_4_clicked();

    void on_pushButton_z_4_clicked();

    void on_pushButton_x_4_clicked();

    void on_pushButton_c_4_clicked();

    void on_pushButton_v_4_clicked();

    void on_pushButton_b_4_clicked();

    void on_pushButton_n_4_clicked();

    void on_pushButton_m_4_clicked();

    void on_pushButton_scomma_4_clicked();

    void on_pushButton_dotsmall_4_clicked();

    void on_pushButton_no1_clicked();

    void on_pushButton_no2_clicked();

    void on_pushButton_no3_clicked();

    void on_pushButton_no4_clicked();

    void on_pushButton_no5_clicked();

    void on_pushButton_no6_clicked();

    void on_pushButton_no7_clicked();

    void on_pushButton_no8_clicked();

    void on_pushButton_no9_clicked();

    void on_pushButton_no0_clicked();

    void on_pushButton_at_clicked();

    void on_pushButton_hash_clicked();

    void on_pushButton_dollar_clicked();

    void on_pushButton_underscore_clicked();

    void on_pushButton_and_clicked();

    void on_pushButton_minus_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_lbracket_clicked();

    void on_pushButton_rbracket_clicked();

    void on_pushButton_slash_clicked();

    void on_pushButton_percent_clicked();

    void on_pushButton_star_clicked();

    void on_pushButton_dquote_clicked();

    void on_pushButton_squote_clicked();

    void on_pushButton_colon_clicked();

    void on_pushButton_semicolon_clicked();

    void on_pushButton_exclamatory_clicked();

    void on_pushButton_questionmark_clicked();

    void on_pushButton_mu_clicked();

    void on_pushButton_backspace_clicked();

    void on_pushButton_comma_clicked();

    void on_pushButton_dotno_clicked();

    void on_pushButton_LoginUsername_clicked();

    void on_pushButton_LoginPassword_clicked();

    void on_pushButton_CreateUsername_clicked();

    void on_pushButton_CreatePassword_clicked();

    void on_pushButton_CreateconPassword_clicked();

    void on_pushButton_NewPassword_clicked();

    void on_pushButton_NewconPassword_clicked();

    void on_pushButton_CPatientID_clicked();

    void on_pushButton_CPatientName_clicked();

    void on_pushButton_CAge_clicked();

    void on_pushButton_CGender_clicked();

    void on_pushButton_CAddress_clicked();

    void on_pushButton_PatientIDUpdation_clicked();

    void on_pushButton_Patient_NameUpdation_clicked();

    void on_pushButton_AgeUpdation_clicked();

    void on_pushButton_GenderUpdation_clicked();

    void on_pushButton_AddressUpdation_clicked();

    void on_pushButton_123caps_3_clicked();

    void on_pushButton_abc_clicked();

    void on_pushButton_entersmall_4_clicked();

    void on_pushButton_enter_clicked();

    void on_pushButton_spacecaps_3_clicked();

    void on_pushButton_spacesmall_4_clicked();

    void on_pushButton_space_clicked();

    void on_pushButton_backspacecaps_3_clicked();

    void on_pushButton_backspacesmall_4_clicked();

    void on_pushButton_casecaps_3_clicked();



    void on_pushButton_123s_4_clicked();

    void on_pushButton_casesmall_4_clicked();



    void on_pushButton_LoadData_clicked();
    void showTime();

    void on_pushButton_LoadData_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_back_2_clicked();

    void on_pushButton_back_3_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_back_4_clicked();

    void WiFi_Timer_Scan();

    void on_pushButton_37_clicked();

    void on_pushButton_c8_clicked();

    void on_pushButton_c1_clicked();

    void on_pushButton_c2_clicked();

    void on_pushButton_c3_clicked();

    void on_pushButton_c4_clicked();

    void on_pushButton_c5_clicked();

    void on_pushButton_c6_clicked();

    void on_pushButton_c7_clicked();

    void on_pushButton_c9_clicked();

    void on_pushButton_c0_clicked();

    void on_pushButton_cplus_clicked();

    void on_pushButton_cminus_clicked();

    void on_pushButton_cmultiply_clicked();

    void on_pushButton_cequalto_clicked();

    void on_pushButton_clog_clicked();

    void on_pushButton_cclear_clicked();

    void on_pushButton_38_clicked();


    void on_pushButton_divide_clicked();

    void on_pushButton_cdot_clicked();

    void on_pushButton_ccomma_clicked();

    void on_pushButton_allclear_clicked();

    void on_pushButton_42_clicked();


    void on_pushButton_41_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_45_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_50_clicked();

    void on_pushButton_49_clicked();

    void on_movecursorleft_clicked();

    void on_movecursorright_clicked();


    void on_pushButton_52_clicked();

    void on_pushButton_51_clicked();

    void on_CalendarWidget_clicked(const QDate &date);

    void on_pushButton_j_8_clicked();

    void on_pushButton_105_clicked();

private:
    Ui::MainWindow *ui;
    secondwindow *secondWindow;
    QVector<double> qv_x,qv_y;
      double result;
      QTimer *myTimer;
    wifimanager  *WiFiMan;
    QTimer *WiFi_Timer;
   // QPushButton *movecursorleft;
   // QPushButton *movecursorright;

};
#endif // MAINWINDOW_H
