#include "jsonOps.hpp"

nlohmann::json json::readFromJsonFile(std::wstring path, std::wstring fileName) {
	nlohmann::json fileContent;
	try {
		std::wstring currentPath;
		std::wstring Directory = path;
		Directory = Directory + L"\\";
		currentPath = Directory.append(fileName);

		std::ifstream f(currentPath);
		fileContent = nlohmann::json::parse(f);

		f.close();
	}
	catch (nlohmann::json::parse_error& ex) {
		return 0;
	}
	catch (nlohmann::json::type_error& ex) {
		return 0;
	}
	return fileContent;
}
