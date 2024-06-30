#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmgr.h"
registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
    ui->pwd_lineEdit->setEchoMode(QLineEdit::Password);
    ui->confirm_lineEdit->setEchoMode(QLineEdit::Password);

    ui->err_tip->setProperty("state", "normal"); // 设置正常属性
    repolish(ui->err_tip); // 刷新

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish,
            this, &registerDialog::slot_reg_mod_finish);

    initHttpHandlers();
}


registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::on_get_code_clicked()
{
    auto mail = ui->email_lineEdit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)"); // 正则表达式匹配邮箱
    bool match = regex.match(mail).hasMatch();
    if(match){
        // 发送http验证码
        QJsonObject json_obj;
        json_obj["email"] = mail;
        HttpMgr::GetInstance()->PostHttpReq(QUrl("http://localhost:8080/get_varifycode"),
                                            json_obj, ReqId::ID_GET_VARIFY_CODE,Modules::REGISTERMOD);

    }else{
        showTip("邮箱地址不正确！", false);
    }


}

void registerDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"), false);
        return;
    }

    // 解析JSON字符串，res转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull()){
        showTip(tr("json解析失败"), false);
        return;
    }
    // json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析失败"), false);
        return;
    }

    _handlers[id](jsonDoc.object());
    return;
}

void registerDialog::showTip(QString str, bool m_ok)
{
    if(m_ok) {
        ui->err_tip->setProperty("state", "normal");
    }else {
        ui->err_tip->setProperty("state", "err");
    }
    ui->err_tip->setText(str);
    repolish(ui->err_tip);
}

void registerDialog::initHttpHandlers()
{
    // 注册获取验证码回包逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"), false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码以及发送到邮箱，注意查收"), true);
        qDebug() << "email is" << email;
    });
}
