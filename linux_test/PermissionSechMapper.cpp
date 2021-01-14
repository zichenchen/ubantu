#include "PermissionSechMapper.h"
#include"CommonUtil.h"
#include "Rule.h"
PermissionSechMapper::PermissionSechMapper()
{
	dao = Dao::getInstance();
}

PermissionSechMapper::~PermissionSechMapper()
{
}

list<rttr::variant> PermissionSechMapper::findusertypeListByUsertypeCode(string usertypeCode)
{
	string sql = " select * from user_type where usertypeCode = '" + usertypeCode+  "'";
	MYSQL_RES* result = dao->exeSQL(sql);

	rttr::type obj_type = rttr::type::get_by_name("Usertype");
	list<rttr::variant> obj_list;

	

	// mysql_field_count()返回connection查询的列数
	for (int i = 0; i < mysql_field_count(dao->connection); ++i)
	{
		// 获取下一行
		dao->row = mysql_fetch_row(result);
		if (dao->row <= 0)
		{
			break;
		}
		rttr::variant obj = obj_type.create();
		// mysql_num_fields()返回结果集中的字段数
		for (int j = 0; j < mysql_num_fields(result); ++j)
		{
			MYSQL_FIELD* fied = mysql_fetch_field_direct(result, j);
			rttr::property field_prop = obj_type.get_property(fied->name);
			string field_value = dao->row[j];
			WirteDataByType(field_prop.get_type().get_name().to_string(), field_value, obj, field_prop);
			cout << fied->name << ":" << dao->row[j] << " ";
		}
		obj_list.push_back(obj);
		cout << endl;
	}
	

	return obj_list;
}

list<rttr::variant> PermissionSechMapper::findusertypeListByName(string username)
{
			
	string sql = "select utype.* from user_type utype, userinfo uinfo where uinfo.userinfoName ='";
	sql.append(username);
	sql.append("' and uinfo.usertypeCode = utype.usertypeCode");
	MYSQL_RES* result = dao->exeSQL(sql);

	rttr::type obj_type = rttr::type::get_by_name("Usertype");
	list<rttr::variant> obj_list;



	// mysql_field_count()返回connection查询的列数
	for (int i = 0; i < mysql_field_count(dao->connection); ++i)
	{
		// 获取下一行
		dao->row = mysql_fetch_row(result);
		if (dao->row <= 0)
		{
			break;
		}
		rttr::variant obj = obj_type.create();
		// mysql_num_fields()返回结果集中的字段数
		for (int j = 0; j < mysql_num_fields(result); ++j)
		{
			MYSQL_FIELD* fied = mysql_fetch_field_direct(result, j);
			rttr::property field_prop = obj_type.get_property(fied->name);
			string field_value = dao->row[j];
			WirteDataByType(field_prop.get_type().get_name().to_string(), field_value, obj, field_prop);
			cout << fied->name << ":" << dao->row[j] << " ";
		}
		obj_list.push_back(obj);
		cout << endl;
	}


	return obj_list;
}

rttr::variant PermissionSechMapper::findwebByWebCode(string webCode)
{
	string sql = " select * from web where webCode = '" + webCode + "'";
	MYSQL_RES* result = dao->exeSQL(sql);

	rttr::type obj_type = rttr::type::get_by_name("Web");
	rttr::variant obj = obj_type.create();
	// mysql_field_count()返回connection查询的列数
	for (int i = 0; i < mysql_field_count(dao->connection); ++i)
	{
		// 获取下一行
		dao->row = mysql_fetch_row(result);
		if (dao->row <= 0)
		{
			break;
		}
		
		// mysql_num_fields()返回结果集中的字段数
		for (int j = 0; j < mysql_num_fields(result); ++j)
		{
			MYSQL_FIELD* fied = mysql_fetch_field_direct(result, j);
			rttr::property field_prop = obj_type.get_property(fied->name);
			string field_value = dao->row[j];
			WirteDataByType(field_prop.get_type().get_name().to_string(), field_value, obj, field_prop);
			cout << fied->name << ":" << dao->row[j] << " ";
		}
	
		cout << endl;
	}


	
	return obj;
}

rttr::variant PermissionSechMapper::findruleByRuleCode(string ruleCode)
{
	string sql = " select * from rule where ruleCode = '" + ruleCode + "'";
	MYSQL_RES* result = dao->exeSQL(sql);

	rttr::type obj_type = rttr::type::get_by_name("Rule");
	rttr::variant obj = obj_type.create();
	// mysql_field_count()返回connection查询的列数
	for (int i = 0; i < mysql_field_count(dao->connection); ++i)
	{
		// 获取下一行
		dao->row = mysql_fetch_row(result);
		if (dao->row <= 0)
		{
			break;
		}

		// mysql_num_fields()返回结果集中的字段数
		for (int j = 0; j < mysql_num_fields(result); ++j)
		{
			MYSQL_FIELD* fied = mysql_fetch_field_direct(result, j);
			rttr::property field_prop = obj_type.get_property(fied->name);
			string field_value = dao->row[j];
			WirteDataByType(field_prop.get_type().get_name().to_string(), field_value, obj, field_prop);
			cout << fied->name << ":" << dao->row[j] << " ";
		}

		cout << endl;
	}

	return obj;
}

void PermissionSechMapper::moduserinfoIpAndPortByIpAndPort(string userinfoIp, int userinfoPort, string userinfoName)
{
	string sql = "update userinfo set userinfoIp ='";
	sql.append(userinfoIp);
	sql.append("', userinfoPort ='");
	sql.append(to_string(userinfoPort));
	sql.append("' where userinfoName ='");
	sql.append(userinfoName);
	sql.append("'");
	dao->exeSQL(sql);
}
