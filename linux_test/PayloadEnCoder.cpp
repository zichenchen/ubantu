#pragma once
#include"PayloadEnCoder.h"
using namespace std;
int PayloadEnCoder::countwriteindex = 0;
char PayloadEnCoder::buffer[4096];

char* PayloadEnCoder::GeneratePkgBuffer(std::string command, rttr::variant obj, int countindex) {
	PayloadEnCoder::countwriteindex = countindex;
	memset(PayloadEnCoder::buffer, 0, sizeof(PayloadEnCoder::buffer));
	rttr::type obj_type = rttr::type::get_by_name(command);
	ConvData(obj_type, obj);
	char* pBuffer=new char[PayloadEnCoder::countwriteindex+1 + sizeof(int)];
	 char* obj_len = T2bytes<int>(PayloadEnCoder::countwriteindex);
	memcpy(pBuffer, obj_len, sizeof(int));
	memcpy(pBuffer + sizeof(int), PayloadEnCoder::buffer, PayloadEnCoder::countwriteindex);

	delete[]obj_len;

	return pBuffer;
}

void PayloadEnCoder::ConvData(rttr::type obj_type, rttr::variant obj) {

	for (auto& prop : obj_type.get_properties())
	{
		WriteToBuffer(&prop, obj);

	}
}

void PayloadEnCoder::WriteToBuffer(const rttr::property* prop, rttr::variant obj) {
	std::string field_name_string = prop->get_name().to_string();
	const char* field_name_char = field_name_string.c_str();
	memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex + 20 - field_name_string.length(), field_name_char, field_name_string.length());//添加字段名称至缓存数组
	PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + 20;
	

	std::string field_type = prop->get_type().get_name().to_string();



	//根据字段类型，添加字段内容至缓存数组
	if (strcmp(field_type.c_str(), "int") == 0) {
		int field_value = 0;
		if (prop->get_value(obj) != NULL) {
		 field_value = prop->get_value(obj).to_int();
		}
		
		 char* field_value_p = T2bytes<int>(field_value);
		memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex, field_value_p, sizeof(int));
		
		PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(int);
		delete[]field_value_p;
	}
	else if (strcmp(field_type.c_str(), "std::string") == 0) {
		string field_value = "";
		if (prop->get_value(obj) != NULL) {
			field_value = prop->get_value(obj).to_string();
		}
		const char* data = field_value.c_str();
		 char* field_len_p = int2bytes(field_value.length());
	
		//添加长度
		memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex, field_len_p, 2);
		PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + 2;
		//添加数据
		if (field_value.length() > 0) {
			memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex, data, field_value.length());
			PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + field_value.length();
		}
		//释放

		delete[]field_len_p;
	}
	else if (strcmp(field_type.c_str(), "double") == 0) {
		double field_value = 0;
		if (prop->get_value(obj) != NULL) {
		 field_value = prop->get_value(obj).to_double();
		}
		 char* field_value_p = T2bytes<double>(field_value);
		memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex, field_value_p, sizeof(double));
		PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(double);
		delete[]field_value_p;
	}
	else if (strcmp(field_type.c_str(), "bool") == 0) {
		bool field_value = prop->get_value(obj).to_bool();
		 char value;
		if (!field_value) {
			value = -1;
			memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex, &value, sizeof(char));
		}
		else {
			value = 1;
			memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex, &value, sizeof(char));
		}
		PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(char);
	}
	else if (strcmp(field_type.c_str(), "float") == 0) {

		float field_value = 0;
		if (prop->get_value(obj) != NULL) {
		 field_value = prop->get_value(obj).to_float();
		}
		
	
		 char* field_value_p = T2bytes<float>(field_value);
		memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex, field_value_p, sizeof(float));
		PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(float);
		delete[]field_value_p;
	}
	else if (strcmp(field_type.c_str(), "std::map<rttr::variant,rttr::variant,cmp_key_Rule>") == 0) {
		int currentwriteindex_hashmap = PayloadEnCoder::countwriteindex;
		//field长度描述
		char* field_len_p;
		//添加长度描述（field长度所占4字节）
		PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(int);
		rttr::variant field_value_var = prop->get_value(obj);                                         
		map<rttr::variant, rttr::variant, cmp_key_Rule> field_value_obj = field_value_var.get_value<map<rttr::variant, rttr::variant, cmp_key_Rule>>();
		map<rttr::variant, rttr::variant, cmp_key_Rule>::iterator itor_map;
		for (itor_map = field_value_obj.begin(); itor_map != field_value_obj.end(); itor_map++) {
			//添加key
			rttr::variant key = itor_map->first;
			string var_key_name_string = key.get_type().get_wrapped_type().get_raw_type().get_name().to_string();
			const char* var_key_name_char = var_key_name_string.c_str();
			memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex + 20 - var_key_name_string.length(), var_key_name_char, var_key_name_string.length());//添加字段名称至缓存数组
			PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + 20;
			int currentwriteindex_key = PayloadEnCoder::countwriteindex;
			char* var_key_len_p;
			//添加长度描述（field长度所占4字节）
			PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(int);
			ConvData(key.get_type().get_wrapped_type().get_raw_type(), key);
			var_key_len_p = T2bytes<int>(PayloadEnCoder::countwriteindex - currentwriteindex_key - 4);
			//添加长度
			memcpy(PayloadEnCoder::buffer + currentwriteindex_key, var_key_len_p, sizeof(int));
			delete[]var_key_len_p;



			//添加value
			rttr::variant value = itor_map->second;;
			string var_value_name_string = value.get_type().get_wrapped_type().get_raw_type().get_name().to_string();
			const char* var_value_name_char = var_value_name_string.c_str();
			memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex + 20 - var_value_name_string.length(), var_value_name_char, var_value_name_string.length());//添加字段名称至缓存数组
			PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + 20;
			int currentwriteindex_value = PayloadEnCoder::countwriteindex;
			char* var_value_len_p;
			//添加长度描述（field长度所占4字节）
			PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(int);
			ConvData(value.get_type().get_wrapped_type().get_raw_type(), value);
			var_value_len_p = T2bytes<int>(PayloadEnCoder::countwriteindex - currentwriteindex_value - 4);
			//添加长度
			memcpy(PayloadEnCoder::buffer + currentwriteindex_value, var_value_len_p, sizeof(int));
			delete[]var_value_len_p;
		}
		field_len_p = T2bytes<int>(PayloadEnCoder::countwriteindex - currentwriteindex_hashmap - 4);
		//添加长度
		memcpy(PayloadEnCoder::buffer + currentwriteindex_hashmap, field_len_p, sizeof(int));
		delete[]field_len_p;
	}
	else if (prop->get_value(obj).is_associative_container()) {
		int currentwriteindex_hashmap = PayloadEnCoder::countwriteindex;
		//field长度描述
		 char* field_len_p;
		//添加长度描述（field长度所占4字节）
		PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(int);
		rttr::variant field_value_var = prop->get_value(obj);                                          // copies the content of my_map into var
		rttr::variant_associative_view field_value_view = field_value_var.create_associative_view();

		for (auto& item : field_value_view)                                        // iterates over all items stored in the container
		{
			//添加key
			rttr::variant key = item.first.extract_wrapped_value();
			string var_key_name_string = key.get_type().get_wrapped_type().get_raw_type().get_name().to_string();
			const char* var_key_name_char = var_key_name_string.c_str();
			memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex + 20 - var_key_name_string.length(), var_key_name_char, var_key_name_string.length());//添加字段名称至缓存数组
			PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + 20;
			int currentwriteindex_key = PayloadEnCoder::countwriteindex;
			 char* var_key_len_p;
			//添加长度描述（field长度所占4字节）
			PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(int);
			ConvData(key.get_type().get_wrapped_type().get_raw_type(), key);
			var_key_len_p = T2bytes<int>(PayloadEnCoder::countwriteindex - currentwriteindex_key - 4);
			//添加长度
			memcpy(PayloadEnCoder::buffer + currentwriteindex_key, var_key_len_p, sizeof(int));
			delete[]var_key_len_p;



			//添加value
			rttr::variant value = item.second.extract_wrapped_value();
			string var_value_name_string = value.get_type().get_wrapped_type().get_raw_type().get_name().to_string();
			const char* var_value_name_char = var_value_name_string.c_str();
			memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex + 20 - var_value_name_string.length(), var_value_name_char, var_value_name_string.length());//添加字段名称至缓存数组
			PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + 20;
			int currentwriteindex_value = PayloadEnCoder::countwriteindex;
			 char* var_value_len_p;
			//添加长度描述（field长度所占4字节）
			PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(int);
			ConvData(value.get_type().get_wrapped_type().get_raw_type(), value);
			var_value_len_p = T2bytes<int>(PayloadEnCoder::countwriteindex - currentwriteindex_value - 4);
			//添加长度
			memcpy(PayloadEnCoder::buffer + currentwriteindex_value, var_value_len_p, sizeof(int));
			delete[]var_value_len_p;
		}
		field_len_p = T2bytes<int>(PayloadEnCoder::countwriteindex - currentwriteindex_hashmap - 4);
		//添加长度
		memcpy(PayloadEnCoder::buffer + currentwriteindex_hashmap, field_len_p, sizeof(int));
		delete[]field_len_p;
	}
	else if (prop->get_value(obj).is_sequential_container()) {
		int currentwriteindex_list = PayloadEnCoder::countwriteindex;
		//field长度描述
		 char* field_len_p;
		//添加长度描述（field长度所占4字节）
		PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(int);
		rttr::variant field_value_var = prop->get_value(obj);                                          // copies the content of my_map into var
		rttr::variant_sequential_view field_value_view = field_value_var.create_sequential_view();

		for (auto& item : field_value_view)                                        // iterates over all items stored in the container
		{
			//添加entry
			rttr::variant entry = item.extract_wrapped_value();
			string var_entry_name_string = entry.get_type().get_wrapped_type().get_raw_type().get_name().to_string();
			const char* var_entry_name_char = var_entry_name_string.c_str();
			memcpy(PayloadEnCoder::buffer + PayloadEnCoder::countwriteindex + 20 - var_entry_name_string.length(), var_entry_name_char, var_entry_name_string.length());//添加字段名称至缓存数组
			PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + 20;
			int currentwriteindex_entey = PayloadEnCoder::countwriteindex;
			 char* var_entry_len_p;
			//添加长度描述（field长度所占4字节）
			PayloadEnCoder::countwriteindex = PayloadEnCoder::countwriteindex + sizeof(int);
			ConvData(entry.get_type().get_wrapped_type().get_raw_type(), entry);
			var_entry_len_p = T2bytes<int>(PayloadEnCoder::countwriteindex - currentwriteindex_entey - 4);
			//添加长度
			memcpy(PayloadEnCoder::buffer + currentwriteindex_entey, var_entry_len_p, sizeof(int));
			delete[]var_entry_len_p;
		}
		field_len_p = T2bytes<int>(PayloadEnCoder::countwriteindex - currentwriteindex_list - 4);
		//添加长度
		memcpy(PayloadEnCoder::buffer + currentwriteindex_list, field_len_p, sizeof(int));
		delete[]field_len_p;
	}
	else {
		cout << field_type.c_str() << ":不支持该数据类型" << endl;
	}
}

