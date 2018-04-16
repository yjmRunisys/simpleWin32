#include "StdAfx.h"
#include "XmlOperator.h"
#include "OutPut.h"

#include "atlbase.h"//CComPtr
#include "Objbase.h"//Com
#pragma comment (lib, "Ole32.lib") //Com

#include "comutil.h"
#pragma comment(lib,"comsupp.lib")//BSTR
#pragma comment(lib, "comsuppw.lib")//BSTR

#include "CodeConvert.h"
/*
例子stocks.xml：
<?xml version="1.0" encoding="utf-8"?>
<root>
<node1>text1</node1>
<node2>
<childnode1 attrib1="value1" attrib2="value2"/>
<childnode2 attrib1="value1" attrib2="value2">childtext1</childnode2>
</node2>
</root>
*/

XmlOperator::XmlOperator(void)
{
	int bCo = ::CoInitialize(NULL);//初始化COM
}


XmlOperator::~XmlOperator(void)
{
	::CoUninitialize();//释放COM接口
}

//递归读取xml
void XmlOperator::ReadXmlOle(string xmlName)
{
	//读取XML
	CComPtr<IXMLDOMDocument> spDoc; //DOM
	spDoc.CoCreateInstance(CLSID_DOMDocument);
	VARIANT_BOOL vb;
	spDoc->load(CComVariant(OLESTR("stocks.xml")), &vb); //加载XML文件
	CComPtr<IXMLDOMElement> spRootEle;
	spDoc->get_documentElement(&spRootEle); //根节点
	CComPtr<IXMLDOMNodeList> spNodeList;
	spRootEle->get_childNodes(&spNodeList); //子节点列表
	long nLen;
	spNodeList->get_length(&nLen); //子节点数
	// 	for (long i = 0; i != nLen; ++i) //遍历子节点
	// 	{
	// 		CComPtr<IXMLDOMNode> spNode;
	// 		spNodeList->get_item(i, &spNode);
	// 		ProcessNode(spNode); //节点处理函数
	// 	}
	ReadXmlOneNode(spRootEle,"/root/node2/childnode1/@attrib1");

}

//读取xml某个节点值
string XmlOperator::ReadXmlOneNode(CComPtr<IXMLDOMElement> &spRootEle,string section)
{
	//CComPtr<IXMLDOMElement> &spRootEle = *(CComPtr<IXMLDOMElement>*)lpRoot;
	CComBSTR sectionCBstr = ConverString2Bstr(section);//"/root/node2/childnode1/@attrib1"
	//读取某个节点
	//CComPtr<IXMLDOMNodeList> spNodeList;
	CComPtr<IXMLDOMNode> spNode;
	//spRootEle->selectNodes(OLESTR("/root/node2/*"), &spNodeList); //得到node2下的所有子节点
	spRootEle->selectSingleNode(sectionCBstr/*OLESTR("/root/node2/childnode1/@attrib1")*/, &spNode); //得到childnode1的attrib1属性
	CComBSTR bsNodeName;
	spNode->get_nodeName(&bsNodeName); //节点名
	string strNodeName = ConvertBstr2String(bsNodeName);
	CComVariant varVal;
	spNode->get_nodeValue(&varVal); //节点值
	string strNodeValue = ConvertBstr2String(varVal.bstrVal);
	//

	return strNodeValue;

}


//写xml
void XmlOperator::WriteXmlOle(PVOID lpRoot,PVOID lpDoc,string xmlName)
{
	CComPtr<IXMLDOMDocument> spDoc = *(CComPtr<IXMLDOMDocument>*)lpDoc;
	CComPtr<IXMLDOMElement> spRootEle = *(CComPtr<IXMLDOMElement>*)lpRoot;

	//写入XML
	CComPtr<IXMLDOMNode> spNode;
	spRootEle->selectSingleNode(OLESTR("/root/node1"), &spNode);
	spNode->put_text(OLESTR("newText")); //写入text
	spRootEle->selectSingleNode(OLESTR("/root/node2/childnode1/@attrib1"), &spNode);
	spNode->put_nodeValue(CComVariant(OLESTR("newValue"))); //写入value
	CComPtr<IXMLDOMNode> spNewNode;
	spDoc->createNode(CComVariant(NODE_ELEMENT), OLESTR("childnode3"), OLESTR(""), &spNewNode); //创建新节点
	spRootEle->selectSingleNode(OLESTR("/root/node2"), &spNode);
	spNode->appendChild(spNewNode, &spNewNode); //将新节点加为node2的子节点
	spNewNode->put_text(OLESTR("childtext2")); //写入新节点text
	CComQIPtr<IXMLDOMElement> spEle = spNewNode; //注意这里使用CComQIPtr
	spEle->setAttribute(OLESTR("attrib1"), CComVariant(OLESTR("value1")));//给新节点添加属性
	spDoc->save(CComVariant(OLESTR("stocks.xml")));
}

void XmlOperator::ProcessNode(CComPtr<IXMLDOMNode>& spNode)
{
	CComBSTR bsNodeName;
	spNode->get_nodeName(&bsNodeName); //节点名	

	string strNodeName = ConvertBstr2String(bsNodeName);
	AfxInfoLog(strNodeName);
	//AfxMessageBox(COLE2CT(bsNodeName));
	CComVariant varVal;
	spNode->get_nodeValue(&varVal); //节点值

	string strNodeValue = ConvertBstr2String(varVal.bstrVal);
	AfxInfoLog(strNodeValue);
	//AfxMessageBox(COLE2CT(varVal.bstrVal));

	DOMNodeType eNodeType;
	spNode->get_nodeType(&eNodeType);
	if (eNodeType == NODE_ELEMENT) //只有NODE_ELEMENT类型才能包含有属性和子节点
	{
		//递归遍历节点属性
		CComPtr<IXMLDOMNamedNodeMap> spNameNodeMap;
		spNode->get_attributes(&spNameNodeMap);
		long nLength;
		spNameNodeMap->get_length(&nLength);
		for (long i = 0; i != nLength; ++i)
		{
			CComPtr<IXMLDOMNode> spNodeAttrib; //注意属性也是一个IXMLDOMNode
			spNameNodeMap->get_item(i, &spNodeAttrib);
			ProcessNode(spNodeAttrib);
		}

		//递归遍历子节点
		CComPtr<IXMLDOMNodeList> spNodeList;
		spNode->get_childNodes(&spNodeList);
		spNodeList->get_length(&nLength);
		for (long i = 0; i != nLength; ++i)
		{
			CComPtr<IXMLDOMNode> spChildNode;
			spNodeList->get_item(i, &spChildNode);
			ProcessNode(spChildNode);
		}
	}
}

string XmlOperator::ConvertBstr2String(BSTR bstr)
{
	string strRet;
	_bstr_t bTemp = bstr;
	wchar_t *lpsz = bTemp;
	//宽字节转窄字符
	char pChar[MAX_PATH];
	memset(pChar,0,MAX_PATH);
	CCodeConvert::cpyWide2Multi(lpsz,pChar);
	strRet = pChar;
	return strRet;
}

string XmlOperator::ConvertBstr2String2(BSTR bstr)
{
	string strRet;
	char* lpszText2 = _com_util::ConvertBSTRToString(bstr);
	strRet = lpszText2;
	delete[] lpszText2;
	return strRet;
}

BSTR XmlOperator::ConverString2Bstr(string str)
{
	wchar_t pwChar[MAX_PATH];
	CCodeConvert::cpyMulti2Wide((char*)str.c_str(),pwChar);
	BSTR bstrText = ::SysAllocString(pwChar);
	return bstrText;
}

BSTR XmlOperator::ConverString2Bstr2(string str)
{
	BSTR bstrText = _bstr_t(str.c_str());
	return bstrText;
}

BSTR XmlOperator::ConverString2Bstr3(string str)
{
	BSTR bstrText = _com_util::ConvertStringToBSTR(str.c_str());
	return bstrText;
}

BSTR XmlOperator::ConvertCString2Bstr(CString cstr)
{
	BSTR bstrText = cstr.AllocSysString();
	SysFreeString(bstrText); // 用完释放
	return bstrText;
}

CString XmlOperator::ConvertBstr2CString(BSTR bstr)
{
	CString str;
	str.Empty();
	str = bstr;
	return str;
}

CComBSTR XmlOperator::ConvertCString2Ccbstr(CString cstr)
{
	CComBSTR ccBstr = cstr.AllocSysString();
	return ccBstr;
}

/////////////////////////////////////////////////////////////// 
XmlSdk::XmlSdk()
{
	int bCo = ::CoInitialize(NULL);//初始化COM
}
XmlSdk::~XmlSdk()
{
	::CoUninitialize();//释放COM接口
}

//节点处理函数
void XmlSdk::ProcessNode(MSXML2::IXMLDOMNodePtr spNode)
{
	std::cout << "nodeName: " << spNode->nodeName;
	if (spNode->nodeType == NODE_ATTRIBUTE || spNode->nodeType == NODE_TEXT)
		std::cout << "\tnodeValue: " << _bstr_t(spNode->nodeValue);
	std::cout << std::endl;

	if (spNode->nodeType == NODE_ELEMENT)
	{
		MSXML2::IXMLDOMNamedNodeMapPtr spNameNodeMap = spNode->attributes;
		for (long i = 0; i != spNameNodeMap->length; ++i) //遍历节点属性
			ProcessNode(spNameNodeMap->item[i]);

		MSXML2::IXMLDOMNodeListPtr spNodeList = spNode->childNodes;
		for (long i = 0; i != spNodeList->length; ++i) //遍历子节点
			ProcessNode(spNodeList->item[i]);
	}
}

//读取xml
void XmlSdk::ReadXml(string xmlName)
{
	XmlOperator xo;
	//读取XML
	MSXML2::IXMLDOMDocumentPtr spXMLDoc;
	HRESULT HR = spXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	if (!SUCCEEDED(HR))  
	{  
		MessageBox(NULL,_T("faild!!"),"fail",MB_ICONERROR);  
		return;  
	}  

	spXMLDoc->put_async(VARIANT_FALSE);
	VARIANT_BOOL bhr = spXMLDoc->load(_T("stocks.xml"));
	if (bhr != VARIANT_TRUE) {
		MessageBox(NULL,_T("无法正确读取xml文件"), _T("错误"), MB_ICONERROR);
		return;
	}

	MSXML2::IXMLDOMElementPtr spRoot = spXMLDoc->documentElement; //根节点
	// 取得根节点的名字
	_variant_t strRootName = spRoot->nodeName/*nodeName*/;
	_bstr_t wstrRootName(strRootName.bstrVal);
	string strName = wstrRootName;

	MSXML2::IXMLDOMNodeListPtr spNodeList = spRoot->childNodes;
	for (long i = 0; i != spNodeList->length; ++i) //遍历子节点
		ProcessNode(spNodeList->item[i]);

	//写入XML
	spRoot->selectSingleNode(L"/root/node1")->text = L"newText";
	spRoot->selectSingleNode(L"/root/node2/childnode1/@attrib1")->nodeValue =  L"newValue";
	MSXML2::IXMLDOMNodePtr spNewNode = spRoot->selectSingleNode(L"/root/node2")->appendChild(
		spXMLDoc->createNode(_variant_t(NODE_ELEMENT), L"childnode3", L"")
		); //给node2创建新子节点childnode3
	spNewNode->text = L"childtext2";
	MSXML2::IXMLDOMElementPtr spEle = spNewNode;
	spEle->setAttribute(L"attrib1", _variant_t(L"value1")); //添加新属性
	spXMLDoc->save(_variant_t(L"stocks.xml"));

	spNewNode.Release();
	spEle.Release();
	spNodeList.Release();
	spRoot.Release();
	spXMLDoc.Release();
}

void TestXml()
{
	XmlOperator xo;
	xo.ReadXmlOle("stocks.xml");
}

/////////////////////////////////////////////////////////////
#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
using namespace std;
int CTestTinyXml::testTXml(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "usage: "<<argv[0] << " xmlfile" << endl;
		return 1;
	}
	TiXmlDocument doc(argv[1]);
	bool loadOk = doc.LoadFile();
	if (!loadOk)
	{
		cout << "could load:" << doc.ErrorDesc() << endl;
	}
	TiXmlPrinter printer;//提供的工具类,目的是将xml的数据按格式输出
	doc.Accept(&printer);
	cout  << printer.CStr() << endl;//输出

	TiXmlElement*node = doc.FirstChildElement();//获取第一个element节点
	cout << node->Value() << endl;//输出节点的值
	string t;
	node->QueryValueAttribute("type", &t);//获取节点属性
	cout << t << endl;

	doc.FirstChild()->NextSibling()->ToElement()->QueryStringAttribute("type", &t);//获取第二个子节点的数据
	cout << "2:" << t << endl;

	//使用遍历的方式进行处理
	TiXmlNode* child = NULL;
	TiXmlElement* element = NULL;
	TiXmlAttribute *attr = NULL;
	int ct;
	while(child = doc.FirstChild()->IterateChildren(child))
	{
		cout << child->ValueStr() << "\t";
		ct = child->Type();
		cout << ct << "\t";
		//根据不同的节点类型做相应处理  
		switch(ct)
		{
		case TiXmlNode::TINYXML_TEXT:
			break;
		case TiXmlNode::TINYXML_ELEMENT:
			element = child->ToElement();
			attr = element->FirstAttribute();
			while(attr)
			{
				cout << attr->NameTStr() << "=" << attr->ValueStr() << '\t';
				attr = attr->Next();
			}
			break;
		}
	}

	return 0;
}
