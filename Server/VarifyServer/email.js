/**
 * nodemailer 用于发送电子邮件的流行 Node.js 模块。通过它，你可以在应用程序中发送邮件（例如，使用 SMTP 协议通过邮件服务器发送邮件）
 * ./config 加载当前目录下的 config.js 文件
 */
const nodemailer = require('nodemailer');
const config_module = require("./config")

/**
 * 创建发送邮件的代理
 */
let transport = nodemailer.createTransport({
    host: 'smtp.163.com',
    port: 465,
    secure: true,
    auth: {
        user: config_module.email_user, // 发送方邮箱地址
        pass: config_module.email_pass // 邮箱授权码或者密码
    }
});

/**
 * 发送邮件的函数
 * @param {*} mailOptions_ 发送邮件的参数
 * @returns 
 */
function SendMail(mailOptions_){
    return new Promise(function(resolve, reject){
        transport.sendMail(mailOptions_, function(error, info){
            if (error) {
                console.log(error);
                reject(error);
            } else {
                console.log('邮件已成功发送：' + info.response);
                resolve(info.response)
            }
        });
    })
   
}

module.exports.SendMail = SendMail