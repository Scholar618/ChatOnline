/**
 * fs 是 Node.js 提供的一个内置模块，允许你对文件和目录进行操作，比如读取文件、写入文件、创建目录等。
 */
const fs = require('fs');

let config = JSON.parse(fs.readFileSync('config.json', 'utf8'));
let email_user = config.email.user;
let email_pass = config.email.pass;
let mysql_host = config.mysql.host;
let mysql_port = config.mysql.port;
let redis_host = config.redis.host;
let redis_port = config.redis.port;
let redis_passwd = config.redis.passwd;
let code_prefix = "code_";


module.exports = {email_pass, email_user, mysql_host, mysql_port,redis_host, redis_port, redis_passwd, code_prefix}