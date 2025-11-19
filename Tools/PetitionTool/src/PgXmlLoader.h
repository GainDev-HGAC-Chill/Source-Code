typedef std::map<int, std::string> STRING_TABLE;

class PgXmlLoader
{
private:
	bool	ParseXml(const TiXmlNode *pkNode, void *pArg = 0);
public:
	STRING_TABLE m_kStrTable;
	bool	LoadXmlFile(const char * cFname);

	PgXmlLoader(void);
	~PgXmlLoader(void);
};

#define g_kXmlMgr Loki::SingletonHolder <PgXmlLoader>::Instance()
