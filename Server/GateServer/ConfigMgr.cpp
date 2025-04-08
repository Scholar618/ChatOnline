#include "ConfigMgr.h"
ConfigMgr::ConfigMgr() {
	// ��ȡconfig.iniĿ¼
	boost::filesystem::path currentPath = boost::filesystem::current_path();
	boost::filesystem::path configPath = currentPath / "config.ini";
	std::cout << "Config path : " << configPath << std::endl;

	// ʹ��Boost.PropertyTree����ȡINI�ļ�  
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(configPath.string(), pt);

	for (const auto& section_pair : pt) {
		const std::string sectionName = section_pair.first;
		const boost::property_tree::ptree& sectionTree = section_pair.second;

		// ����ÿһ��section��ֵ��
		// key_value_pair.second ��һ�� boost::property_tree::ptree ����
		std::map<std::string, std::string> section_config;
		for (const auto& key_value_pair : sectionTree) {
			const std::string& key = key_value_pair.first;
			const std::string& value = key_value_pair.second.get_value<std::string>();
			section_config[key] = value;
		}
		// ��section_configֵ������_section_datas��
		SectionInfo sectionInfo;
		sectionInfo._section_datas = section_config;
		_config_map[sectionName] = sectionInfo;
	}

	// ������е�section��key-value��  
	for (const auto& section_entry : _config_map) {
		const std::string& section_name = section_entry.first;
		SectionInfo section_config = section_entry.second;
		std::cout << "[" << section_name << "]" << std::endl;
		for (const auto& key_value_pair : section_config._section_datas) {
			std::cout << key_value_pair.first << "=" << key_value_pair.second << std::endl;
		}
	}
}
