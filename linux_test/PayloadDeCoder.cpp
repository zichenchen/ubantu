#pragma once
#include"PayloadDeCoder.h"
#include "Rule.h"

using namespace std;
int PayloadDeCoder::countreadindex = 0;
rttr::variant  PayloadDeCoder::GenerateObj(string  command,char* buffer) {
	PayloadDeCoder::countreadindex = 0;
	rttr::type obj_type = rttr::type::get_by_name(command);
	rttr::variant obj_var = obj_type.create();

	fillData(obj_var, obj_type, buffer);
	return obj_var;
}
void PayloadDeCoder::fillData(rttr::variant& obj_var, rttr::type obj_type, char* buffer) {
	 char obj_len_p[4];
	memcpy(&obj_len_p, buffer + PayloadDeCoder::countreadindex, sizeof(int));
	int obj_len = bytes2T<int>(obj_len_p);

	PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + sizeof(int);


	int target_index = obj_len + PayloadDeCoder::countreadindex;

	char field_name[20];
	while (PayloadDeCoder::countreadindex < target_index) {
		memcpy(field_name, buffer + PayloadDeCoder::countreadindex, 20);
		PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + 20;
		del_sp(field_name, 20);
		string field_name_str(field_name);
		rttr::property field_prop = obj_type.get_property(field_name_str);
		WriteToVar(field_prop, obj_var, buffer);

	}
}
void PayloadDeCoder::WriteToVar(rttr::property prop, rttr::variant& obj_var,char* buffer)
{
	string field_type = prop.get_type().get_name().to_string();
	//�����ֶ����ͣ�����ֶ���������������
	if (strcmp(field_type.c_str(), "int") == 0) {
		 char field_value_p[sizeof(int)];
		//�ӻ�����ȡ�����ݣ�int����Ϊ�ĸ��ֽڣ�
		memcpy(field_value_p, buffer + PayloadDeCoder::countreadindex, sizeof(int));
		PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + sizeof(int);
		int field_value = bytes2T<int>(field_value_p);
		prop.set_value(obj_var, field_value);
	
	}
	else if (strcmp(field_type.c_str(), "std::string") == 0) {

		 char field_value_len_p[2];
		//ȡ���ַ������ȣ�2���ֽڴ洢��
		memcpy(field_value_len_p, buffer + PayloadDeCoder::countreadindex, 2);
		
		//���Գ���תΪint��
		int field_value_len = bytes2int(field_value_len_p);
	

		//����ַ����2
		PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + 2;
		char field_value_p[field_value_len + 1];
		//ȡ������ֵ
		memcpy(field_value_p, buffer + PayloadDeCoder::countreadindex, field_value_len);
		field_value_p[field_value_len] = '\0';
		//����ַ���Ӷ�Ӧ����
		PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + field_value_len;
		if (field_value_len > 0) {
			//����ֵתΪstring����
			string field_value_str(field_value_p);
			//�������
			prop.set_value(obj_var, field_value_str);
		}
		
	}
	else if (strcmp(field_type.c_str(), "double") == 0) {
		//�ӻ�����ȡ�����ݣ�double����Ϊ8���ֽڣ�
		 char field_value_p[sizeof(double)];
		memcpy(field_value_p, buffer+ PayloadDeCoder::countreadindex, sizeof(double));
		
		//����ַ���Ӷ�Ӧ����
		PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + sizeof(double);
		double field_value = bytes2T<double>(field_value_p);
		prop.set_value(obj_var, field_value);
	

	}
	else if (strcmp(field_type.c_str(), "bool") == 0) {
		//�ӻ�����ȡ�����ݣ�bool����Ϊ1���ֽڣ�
		 char field_value_p;
		memcpy(&field_value_p, buffer + PayloadDeCoder::countreadindex, sizeof(bool));
		//����ַ���Ӷ�Ӧ����
		PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + sizeof(bool);
		if (field_value_p == -1) {
			prop.set_value(obj_var, false);
		}
		else if (field_value_p == 1) {
			prop.set_value(obj_var, true);
		}

	}
	else if (strcmp(field_type.c_str(), "float") == 0) {
		//�ӻ�����ȡ�����ݣ�double����Ϊ8���ֽڣ�
		 char field_value_p[sizeof(float)];
		memcpy(field_value_p, buffer + PayloadDeCoder::countreadindex, sizeof(float));
	
		//����ַ���Ӷ�Ӧ����
		PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + sizeof(float);
		float field_value = bytes2T<float>(field_value_p);
		prop.set_value(obj_var, field_value);
		
	}
	else if (strcmp(field_type.c_str(), "std::map<rttr::variant,rttr::variant,cmp_key_Rule>") == 0) {
		char field_value_len_p[4];
		//ȡ�ó��ȣ�4���ֽڴ洢��
		memcpy(field_value_len_p, buffer + PayloadDeCoder::countreadindex, 4);
		//���Գ���תΪint��
		int field_value_len = bytes2T<int>(field_value_len_p);

		//����ַ����4
		PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + 4;
		int currentreadindex_hashmap = PayloadDeCoder::countreadindex;

		map<rttr::variant, rttr::variant,cmp_key_Rule> permissionMap;
		while (field_value_len > (PayloadDeCoder::countreadindex - currentreadindex_hashmap))
		{
			char key_var_name[20];
			memcpy(key_var_name, buffer + PayloadDeCoder::countreadindex, 20);
			PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + 20;
			del_sp(key_var_name, 20);
			string key_var_name_str(key_var_name);
			rttr::type key_var_type = rttr::type::get_by_name(key_var_name_str);
			rttr::variant key_var = key_var_type.create();
			fillData(key_var, key_var_type, buffer);



			char value_var_name[20];
			memcpy(value_var_name, buffer + PayloadDeCoder::countreadindex, 20);
			PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + 20;
			del_sp(value_var_name, 20);
			string value_var_name_str(value_var_name);
			rttr::type value_var_type = rttr::type::get_by_name(value_var_name_str);
			rttr::variant value_var = value_var_type.create();
			fillData(value_var, value_var_type, buffer);

			permissionMap.insert(map<rttr::variant, rttr::variant,cmp_key_Rule>::value_type(key_var, value_var));
		}
		prop.set_value(obj_var, permissionMap);
	}
	else if (prop.get_value(obj_var).is_associative_container()) {
		 char field_value_len_p[4];
		//ȡ�ó��ȣ�4���ֽڴ洢��
		memcpy(field_value_len_p, buffer + PayloadDeCoder::countreadindex, 4);
		//���Գ���תΪint��
		int field_value_len = bytes2T<int>(field_value_len_p);
		
		//����ַ����4
		PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + 4;
		int currentreadindex_hashmap = PayloadDeCoder::countreadindex;

		map<rttr::variant, rttr::variant> permissionMap;
		while (field_value_len > (PayloadDeCoder::countreadindex - currentreadindex_hashmap))
		{
			char key_var_name[20];
			memcpy(key_var_name, buffer + PayloadDeCoder::countreadindex, 20);
			PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + 20;
			del_sp(key_var_name, 20);
			string key_var_name_str(key_var_name);
			rttr::type key_var_type = rttr::type::get_by_name(key_var_name_str);
			rttr::variant key_var = key_var_type.create();
			fillData(key_var, key_var_type, buffer);
	


			char value_var_name[20];
			memcpy(value_var_name, buffer + PayloadDeCoder::countreadindex, 20);
			PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + 20;
			del_sp(value_var_name, 20);
			string value_var_name_str(value_var_name);
			rttr::type value_var_type = rttr::type::get_by_name(value_var_name_str);
			rttr::variant value_var = value_var_type.create();
			fillData(value_var, value_var_type, buffer);
		
			permissionMap.insert(map<rttr::variant, rttr::variant>::value_type(key_var, value_var));
		}
		prop.set_value(obj_var, permissionMap);
	}
	else if (prop.get_value(obj_var).is_sequential_container()) {
		 char field_value_len_p[4];
		//ȡ�ó��ȣ�4���ֽڴ洢��
		memcpy(field_value_len_p, buffer + PayloadDeCoder::countreadindex, 4);
		//���Գ���תΪint��
		int field_value_len = bytes2T<int>(field_value_len_p);
	
		//����ַ����4
		PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + 4;
		int currentreadindex_list = PayloadDeCoder::countreadindex;

		list<rttr::variant> list;
		while (field_value_len > (PayloadDeCoder::countreadindex - currentreadindex_list))
		{
			char entry_var_name [20];
			memcpy(entry_var_name, buffer+ PayloadDeCoder::countreadindex, 20);
			PayloadDeCoder::countreadindex = PayloadDeCoder::countreadindex + 20;
			del_sp(entry_var_name, 20);
			string entry_var_name_str(entry_var_name);
			rttr::type entry_var_type = rttr::type::get_by_name(entry_var_name_str);
			rttr::variant entry_var = entry_var_type.create();
			fillData(entry_var, entry_var_type, buffer);
		
			list.push_back(entry_var);
		}
		prop.set_value(obj_var, list);
	}
	else {
		cout << field_type.c_str() << ":��֧�ָ���������" << endl;
	}
}