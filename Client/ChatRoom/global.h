#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <functional>
#include <QRegularExpression>
#include <QStyle>
#include <memory>
#include <iostream>
#include <mutex>
#include <QByteArray>
#include <QJsonObject>


extern std::function<void (QWidget *)> repolish; // 重新刷新函数实现qss


enum ReqId{
    ID_GET_VARIFY_CODE = 1001, // 获取验证码
    ID_GET_USER = 1002,        // 注册用户
};

enum Modules{
    REGISTERMOD = 0,
};

// 错误返回码
enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1, // json解析失败
    ERR_NETWORK = 2, // 网络错误
};

#endif // GLOBAL_H
