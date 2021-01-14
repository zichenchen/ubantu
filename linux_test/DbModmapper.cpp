#include "DbModmapper.h"
#include"CommonUtil.h"
DbModmapper::DbModmapper()
{
	dao = Dao::getInstance();
}

DbModmapper::~DbModmapper()
{
}

void DbModmapper::deluserinfoByuserinfoId(int userinfoId)
{
	string sql = "delete  from userinfo where userinfoId ="  ;
	sql.append(to_string(userinfoId));
	dao->exeSQL(sql);
	
}

void DbModmapper::adduserinfoByUser(userinfo* userinfo)
{

	string sql = "insert into userinfo(";
	rttr::variant obj = userinfo;
	rttr::type obj_type = rttr::type::get_by_name("userinfo");
	for (auto& prop : obj_type.get_properties())
	{
		sql.append(prop.get_name().to_string());
		sql.append(",");
	}
	sql.pop_back();
	sql.append(") values ('");

	for (auto& prop : obj_type.get_properties())
	{
		sql.append(prop.get_value(obj).to_string());
		sql.append("','");
	}
	sql.pop_back();
	sql.pop_back();
	sql.append(")");

	dao->exeSQL(sql);
}

void DbModmapper::deluserinfoByName(string username)
{
	string sql = "delete  from userinfo where userinfoName='" + username +"'";
	 dao->exeSQL(sql);
}

rttr::variant DbModmapper::finduserinfoByuserinfoName(string userinfoName)
{
	string sql = "select * from userinfo where userinfoName = '" + userinfoName + "'";
	MYSQL_RES* result = dao->exeSQL(sql);

	rttr::type obj_type = rttr::type::get_by_name("userinfo");
	rttr::variant obj = obj_type.create();
	rttr::property field_prop = obj_type.get_property("");
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
			field_prop = obj_type.get_property(fied->name);
			string field_value = dao->row[j];
			WirteDataByType(field_prop.get_type().get_name().to_string(), field_value, obj, field_prop);
		
		}
		cout << endl;
	}
	
	return obj;
}

list<rttr::variant> DbModmapper::findusertypelistByusertypeCode(string usertypeCode)
{
	string sql = " select * from user_type where usertypeCode = '" + usertypeCode + "'";
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
		
		}
		obj_list.push_back(obj);
	
	}


	return obj_list;
}

void DbModmapper::delwebBywebId(int webId)
{
	string sql = "  delete  from web where webId =" ;
	sql.append(to_string(webId));
	MYSQL_RES* result = dao->exeSQL(sql);
}

void DbModmapper::addwebByweb(Web* web)
{
		string sql = "insert into web (";
		rttr::variant obj = web;
		rttr::type obj_type = rttr::type::get_by_name("Web");
		for (auto& prop : obj_type.get_properties())
		{
			sql.append(prop.get_name().to_string());
			sql.append(",");
		}
		sql.pop_back();
		sql.append(") values ('");

		for (auto& prop : obj_type.get_properties())
		{
			sql.append(prop.get_value(obj).to_string());
			sql.append("','");
		}
		sql.pop_back();
		sql.pop_back();
		sql.append(")");

	 dao->exeSQL(sql);
}

void DbModmapper::delruleByruleId(int ruleId)
{
	string sql = " delete  from rule where ruleId =";
	sql.append(to_string(ruleId));
	 dao->exeSQL(sql);
}

void DbModmapper::addruleByrule(Rule* rule)
{
	string sql = "insert into rule (";
	rttr::variant obj = rule;
	rttr::type obj_type = rttr::type::get_by_name("Rule");
	for (auto& prop : obj_type.get_properties())
	{
		sql.append(prop.get_name().to_string());
		sql.append(",");
	}
	sql.pop_back();
	sql.append(") values ('");

	for (auto& prop : obj_type.get_properties())
	{
		sql.append(prop.get_value(obj).to_string());
		sql.append("','");
	}
	sql.pop_back();
	sql.pop_back();
	sql.append(")");

	 dao->exeSQL(sql);
}

void DbModmapper::modruleByruleAndruleCode(Rule* rule, string ruleCode)
{
	string sql = "update rule set ";
	rttr::variant obj = rule;
	rttr::type obj_type = rttr::type::get_by_name("Rule");
	for (auto& prop : obj_type.get_properties())
	{
		/*cout << "属性名: " << prop.get_name() << ", 属性类性: " << prop.get_type().get_name() << ", 属性值: " << prop.get_value(iaResultMessage).to_string() << endl;*/
	
		sql.append(prop.get_name().to_string());
		sql.append("='");
		sql.append(prop.get_value(obj).to_string());
		sql.append("',");
	}
	sql.pop_back();
	sql.append(" where ");
	sql.append("ruleCode='");
	sql.append(ruleCode);
	sql.append( "'");
	 dao->exeSQL(sql);
}

void DbModmapper::modwebBywebAndwebCode(Web* web, string webCode)
{
	string sql = "update web set ";
	rttr::variant obj = web;
	rttr::type obj_type = rttr::type::get_by_name("Web");
	for (auto& prop : obj_type.get_properties())
	{
		sql.append(prop.get_name().to_string());
		sql.append("='");
		sql.append(prop.get_value(obj).to_string());
		sql.append("',");
	}
	sql.pop_back();
	sql.append(" where ");
	sql.append("webCode='" );
	sql.append( webCode);
	sql.append("'");
	 dao->exeSQL(sql);
}

void DbModmapper::delusertypeByusertypeId(int usertypeId)
{
	string sql = " delete  from user_type where usertypeId =";
	sql.append(to_string(usertypeId));
	dao->exeSQL(sql);
}

void DbModmapper::addusertypeByusertype(Usertype* usertype)
{
	string sql = " insert into user_type (";
	rttr::variant obj = usertype;
	rttr::type obj_type = rttr::type::get_by_name("Usertype");
	for (auto& prop : obj_type.get_properties())
	{
		sql.append(prop.get_name().to_string());
		sql.append(",");
	}
	sql.pop_back();
	sql.append(") values ('");

	for (auto& prop : obj_type.get_properties())
	{
		sql.append(prop.get_value(obj).to_string());
		sql.append("','");
	}
	sql.pop_back();
	sql.pop_back();
	sql.append(")");

	dao->exeSQL(sql);
}

void DbModmapper::modexecutivestatusWithstatus(int executive_status)
{
	string sql = "update executive set executive_status =";
	sql.append(to_string(executive_status));
	dao->exeSQL(sql);
}

void DbModmapper::modexecutivestatusByIpAndPortWithstatus(string executive_ip, int executive_port, int executive_status)
{
	string sql = "update executive set executive_status ='";
	sql.append(to_string(executive_status));
	sql.append("' where executive_ip = '");
	sql.append(executive_ip);
	sql.append("' AND executive_port ='");
	sql.append(to_string(executive_port));
	sql.append("'");
	dao->exeSQL(sql);
}

void DbModmapper::modexecutivestatusByIpAndPortWithstatusAndobtime(string executive_ip, int executive_port, int executive_status, string executive_obtime)
{
	string sql = "update executive set executive_status = '";
	sql.append(to_string(executive_status));
	sql.append("', executive_obtime ='");
	sql.append(executive_obtime);
	sql.append("' where executive_ip = '");
	sql.append(executive_ip);
	sql.append("' AND executive_port ='");
	sql.append(to_string(executive_port));
	sql.append("'");
	dao->exeSQL(sql);
	
}

void DbModmapper::StatusModByuserinfoName(int Status, string username)
{
	string sql = "update userinfo set userinfoStatus ='";
	sql.append(to_string(Status));
	sql.append("'  where userinfoName = '");
	sql.append(username);
	sql.append("'");
	dao->exeSQL(sql);
}

list<rttr::variant> DbModmapper::getallexecutivelistBystatus(int executive_status)
{
	string sql = "select * from executive where executive_status = '";
	sql.append(to_string(executive_status));
	sql.append("'");
	MYSQL_RES* result = dao->exeSQL(sql);

	rttr::type obj_type = rttr::type::get_by_name("Executive");
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

rttr::variant DbModmapper::getExecutiveByIpAndPort(string executive_ip,int executive_port)
{
	string sql = "select * from executive where executive_ip = '";
	sql.append(executive_ip);
	sql.append("'");
	sql.append("' AND executive_port ='");
	sql.append(to_string(executive_port));
	sql.append("'");
	MYSQL_RES* result = dao->exeSQL(sql);

	rttr::type obj_type = rttr::type::get_by_name("Executive");
	rttr::variant obj = obj_type.create();
	rttr::property field_prop = obj_type.get_property("");


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
			field_prop = obj_type.get_property(fied->name);
			string field_value = dao->row[j];
			WirteDataByType(field_prop.get_type().get_name().to_string(), field_value, obj, field_prop);


			cout << fied->name << ":" << dao->row[j] << " ";
		}
		cout << endl;
	}

	return obj;
}
