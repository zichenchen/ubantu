#include"IdentityAuthMapper.h"
#include"CommonUtil.h"

IdentityAuthMapper::IdentityAuthMapper()
{
	dao = Dao::getInstance();
}

IdentityAuthMapper::~IdentityAuthMapper()
{
}

rttr::variant IdentityAuthMapper::finduserinfoByNameAndPassword(string username, string password)
{
	string sql = "select * from userinfo where userinfoName ='"+username+"' and userinfopassword='" + password+"'";
	MYSQL_RES* result=dao->exeSQL(sql);
	
	rttr::type obj_type = rttr::type::get_by_name("userinfo");
	rttr::variant obj = obj_type.create();
	rttr::property field_prop=obj_type.get_property("");
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
				string field_value=dao->row[j];
				WirteDataByType(field_prop.get_type().get_name().to_string(),field_value,obj, field_prop);
				
	
			
			}
			cout << endl;
		}

	return obj;
}
