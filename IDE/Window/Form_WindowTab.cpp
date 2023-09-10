﻿#include "Form_WindowTab.h"
#include "ui_Form_WindowTab.h"
#include "QGridLayout"


Form_WindowTab::Form_WindowTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_WindowTab)
{
    ui->setupUi(this);

    //删除自身的信息，本类存在预览选项卡
    for (int i = ui->tabWidget->count() - 1; i >= 0; i--)
    {
        QWidget *page = ui->tabWidget->widget(i);
        ui->tabWidget->removeTab(i);  // 删除选项卡
        delete page;      // 删除子窗口
    }
}

Form_WindowTab::~Form_WindowTab()
{
    delete ui;
}


//添加窗体到Tab
void Form_WindowTab::addTabWidget(QString title, QWidget *form, QString sign, QIcon titeIco, bool select, PluginGlobalMsg::TabType type)
{
    QWidget* t_tab = new QWidget(ui->tabWidget);
    QGridLayout* t_layout = new QGridLayout(t_tab);
    t_layout->setContentsMargins(0,0,0,0); //设置布局边距
    t_layout->setSpacing(0); //设置组件的间距
    t_layout->addWidget(form);
    t_tab->setLayout(t_layout);
    int t_index = ui->tabWidget->addTab(t_tab,titeIco,title);
    this->tabMsgList.append({title,sign,form,t_tab,type}); //添加信息到列表
    if(select) ui->tabWidget->setCurrentIndex(t_index); //把当前窗口提升
}

bool Form_WindowTab::removeTabMsg(QWidget *form)
{
    for(int a = 0;a<this->tabMsgList.length();a++){
        if(this->tabMsgList[a].formPth == form || this->tabMsgList[a].tabWidgetPth == form){
            this->tabMsgList.removeAt(a); //删除信息
            return true;
        }
    }
    return false;
}

//根据widget指针标记删除列表信息
bool Form_WindowTab::removeTabMsg(QString sign)
{
    for(int a = 0;a<this->tabMsgList.length();a++){
        if(this->tabMsgList[a].signText == sign){
            this->tabMsgList.removeAt(a); //删除信息
            return true;
        }
    }
    return false;
}

//根据标记更改信息
bool Form_WindowTab::resetTabMsg(QString oldSign, tabMsg newMsg)
{
    for(int a = 0;a<this->tabMsgList.length();a++){
        if(this->tabMsgList[a].signText == oldSign){
            this->tabMsgList[a] = newMsg; //删除信息
            return true;
        }
    }
    return false;
}

//根据窗体指针更改信息
bool Form_WindowTab::resetTabMsg(QWidget *oldWidget, tabMsg newMsg)
{
    for(int a = 0;a<this->tabMsgList.length();a++){
        if(this->tabMsgList[a].formPth == oldWidget){
            this->tabMsgList[a] = newMsg; //删除信息
            return true;
        }
    }
    return false;
}


//根据标记查看TAB是否已经存在
bool Form_WindowTab::hasTabMsg(QString sign,bool select)
{
    for(int a = 0;a<this->tabMsgList.length();a++){ //检查是否已经存在这个Tab窗体
        if(this->tabMsgList[a].signText == sign){
            if(select) ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(this->tabMsgList[a].tabWidgetPth));
            return true;
        }
    }
    return false;
}


//根据Widgte指针查看TAB是否已经存在
bool Form_WindowTab::hasTabMsg(QWidget *widget,bool select)
{
    for(int a = 0;a<this->tabMsgList.length();a++){ //检查是否已经存在这个Tab窗体
        if(this->tabMsgList[a].formPth == widget || this->tabMsgList[a].tabWidgetPth == widget){
            if(select) ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(this->tabMsgList[a].tabWidgetPth));
            return true;
        }
    }
    return false;
}








//根据标记获取信息
Form_WindowTab::tabMsg Form_WindowTab::getMsg(QString sign)
{
    tabMsg t_msg;
    for(int a = 0;a<this->tabMsgList.length();a++){
        if(this->tabMsgList[a].signText == sign){
            t_msg = this->tabMsgList[a]; //删除信息
            break;
        }
    }
    return t_msg;
}

//根据窗体指针获取信息
Form_WindowTab::tabMsg Form_WindowTab::getMsg(QWidget *widget)
{
    tabMsg t_msg;
    for(int a = 0;a<this->tabMsgList.length();a++){
        if(this->tabMsgList[a].formPth == widget){
            t_msg = this->tabMsgList[a]; //删除信息
            break;
        }
    }
    return t_msg;
}


//获取当前顶部选项卡的标记
QString Form_WindowTab::getTopTabSign()
{
    QWidget* t_widget = ui->tabWidget->currentWidget();
    for(int a = 0;a<this->tabMsgList.length();a++){
        if(this->tabMsgList[a].tabWidgetPth == t_widget){
            return this->tabMsgList[a].signText;
        }
    }
    return "";
}


void Form_WindowTab::on_tabWidget_tabCloseRequested(int index)
{
    QWidget* t_widget = ui->tabWidget->widget(index);
    this->removeTabMsg(t_widget);
    ui->tabWidget->removeTab(index);
    delete t_widget;
}

