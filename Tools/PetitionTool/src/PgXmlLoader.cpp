#include "stdafx.h"

PgXmlLoader::PgXmlLoader(void)
{
}

PgXmlLoader::~PgXmlLoader(void)
{
}

bool PgXmlLoader::LoadXmlFile(const char* cFname)
{
	m_kStrTable.clear();
	TiXmlDocument doc;
	std::wstring kCurDir(1024, 0);
	GetCurrentDirectory(kCurDir.size(), &kCurDir[0]);
	if(!doc.LoadFile(cFname, TIXML_DEFAULT_ENCODING))
	{
		INFO_LOG( BM::LOG_LV2, _T("Xml Load Faild"));
		return false;
	}
	if(!ParseXml(doc.FirstChild()))
	{
		INFO_LOG( BM::LOG_LV2, _T("Xml Parsing Faild"));
		return false;
	}
	return true;
}

bool PgXmlLoader::ParseXml(const TiXmlNode *pkNode, void *pArg)
{
	while(pkNode)
	{
		const int iType = pkNode->Type();

		switch(iType)
		{
		case TiXmlNode::ELEMENT:
			{
				TiXmlElement *pkElement = (TiXmlElement *)pkNode;
				
				const char* pcTagName =  pkElement->Value();
 
				if(strcmp(pcTagName, "TEXT_TABLE")==0)
				{
					// 자식 노드들을 파싱한다.
					// 첫 자식만 여기서 걸어주면, 나머지는 NextSibling에 의해서 자동으로 파싱된다.
					const TiXmlNode * pkChildNode = pkNode->FirstChild();
					if(pkChildNode != 0)
					{
						if(!ParseXml(pkChildNode))
						{
							return false;
						}
					}
				}
				else if(strcmp(pcTagName, "TEXT") == 0)
				{
					const TiXmlAttribute *pkAttr = pkElement->FirstAttribute();
					unsigned long ulTextID = 0;
					const char *szText;
					const char *strScript = 0;
					while(pkAttr)
					{
						const char *pcAttrName = pkAttr->Name();
						const char *pcAttrValue = pkAttr->Value();

						if(strcmp(pcAttrName, "ID") == 0)
						{
							ulTextID = (unsigned long)atoi(pcAttrValue);
						}
						else if(strcmp(pcAttrName, "Text") == 0)
						{
							szText = pcAttrValue;
						}
						else
						{
							INFO_LOG( BM::LOG_LV2, _T("invalid attribute"));
						}

						pkAttr = pkAttr->Next();
					}		
					m_kStrTable.insert(std::make_pair(ulTextID, szText));

				}
			}
		}

		const TiXmlNode* pkNextNode = pkNode->NextSibling();
		pkNode = pkNextNode;
	}
	return	true;
}