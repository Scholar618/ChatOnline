#include "ConfigMgr.h"
ConfigMgr::ConfigMgr() {
	// 获取config.ini目录
	boost::filesystem::path currentPath = boost::filesystem::current_path();
	boost::filesystem::path configPath = currentPath / "config.ini";
	std::cout << "Config path : " << configPath << std::endl;

	// 使用Boost.PropertyTree来读取INI文件  
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(configPath.string(), pt);

	for (const auto& section_pair : pt) {
		const std::string sectionName = section_pair.first;
		const boost::property_tree::ptree& sectionTree = section_pair.second;

		// 遍历每一个section键值对
		// key_value_pair.second 是一个 boost::property_tree::ptree 类型
		std::map<std::string, std::string> section_config;
		for (const auto& key_value_pair : sectionTree) {
			const std::string& key = key_value_pair.first;
			const std::string& value = key_value_pair.second.get_value<std::string>();
			section_config[key] = value;
		}
		// 将section_config值保存至_section_datas中
		SectionInfo sectionInfo;
		sectionInfo._section_datas = section_config;
		_config_map[sectionName] = sectionInfo;
	}

	// 输出所有的section和key-value对  
	for (const auto& section_entry : _config_map) {
		const std::string& section_name = section_entry.first;
		SectionInfo section_config = section_entry.second;
		std::cout << "[" << section_name << "]" << std::endl;
		for (const auto& key_value_pair : section_config._section_datas) {
			std::cout << key_value_pair.first << "=" << key_value_pair.second << std::endl;
		}
	}
}
