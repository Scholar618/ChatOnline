#pragma once
#include "const.h"
/*
 * 读取和管理配置
 * SectionInfo : 管理key和value
 * ConfigMagr : 管理SectionInfo和其内部的key与value
 */
struct SectionInfo
{
	SectionInfo() {}
	~SectionInfo() {
		_section_datas.clear();
	}

	// 拷贝
	SectionInfo(const SectionInfo& src) {
		_section_datas = src._section_datas;
	}

	// 赋值
	SectionInfo& operator = (const SectionInfo& src) {
		if (&src == this)
			return *this;
		this->_section_datas = src._section_datas;
		return *this;
	}

	std::map<std::string, std::string> _section_datas;
	// section[key] = value, 重载[]运算符
	std::string operator[](const std::string& key) {
		if (_section_datas.find(key) == _section_datas.end()) { // 没有找到
			return "";
		}
		// 这里可以添加一些边界检查  
		return _section_datas[key];
	}

};

class ConfigMgr
{
public:
	~ConfigMgr() {
		_config_map.clear();
	}

	SectionInfo operator[](const std::string& section) {
		if (_config_map.find(section) == _config_map.end()) {
			return SectionInfo();
		}
		return _config_map[section];
	}


	static ConfigMgr& Inst() {
		static ConfigMgr cfg_mgr; // 静态局部变量，确保只初始化一次
		return cfg_mgr; // 返回这个唯一实例的引用
	}


	// 拷贝
	ConfigMgr(const ConfigMgr& src) {
		_config_map = src._config_map;
	}

	// 赋值
	ConfigMgr& operator = (const ConfigMgr& src) {
		if (&src == this)
			return *this;
		this->_config_map = src._config_map;
	}

private:
	// 构造
	ConfigMgr();
	// _config_map[name] = SectionInfo
	std::map<std::string, SectionInfo> _config_map;
};

