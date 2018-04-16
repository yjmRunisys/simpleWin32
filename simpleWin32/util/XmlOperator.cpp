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
����stocks.xml��
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
	int bCo = ::CoInitialize(NULL);//��ʼ��COM
}


XmlOperator::~XmlOperator(void)
{
	::CoUninitialize();//�ͷ�COM�ӿ�
}

//�ݹ��ȡxml
void XmlOperator::ReadXmlOle(string xmlName)
{
	//��ȡXML
	CComPtr<IXMLDOMDocument> spDoc; //DOM
	spDoc.CoCreateInstance(CLSID_DOMDocument);
	VARIANT_BOOL vb;
	spDoc->load(CComVariant(OLESTR("stocks.xml")), &vb); //����XML�ļ�
	CComPtr<IXMLDOMElement> spRootEle;
	spDoc->get_documentElement(&spRootEle); //���ڵ�
	CComPtr<IXMLDOMNodeList> spNodeList;
	spRootEle->get_childNodes(&spNodeList); //�ӽڵ��б�
	long nLen;
	spNodeList->get_length(&nLen); //�ӽڵ���
	// 	for (long i = 0; i != nLen; ++i) //�����ӽڵ�
	// 	{
	// 		CComPtr<IXMLDOMNode> spNode;
	// 		spNodeList->get_item(i, &spNode);
	// 		ProcessNode(spNode); //�ڵ㴦����
	// 	}
	ReadXmlOneNode(spRootEle,"/root/node2/childnode1/@attrib1");

}

//��ȡxmlĳ���ڵ�ֵ
string XmlOperator::ReadXmlOneNode(CComPtr<IXMLDOMElement> &spRootEle,string section)
{
	//CComPtr<IXMLDOMElement> &spRootEle = *(CComPtr<IXMLDOMElement>*)lpRoot;
	CComBSTR sectionCBstr = ConverString2Bstr(section);//"/root/node2/childnode1/@attrib1"
	//��ȡĳ���ڵ�
	//CComPtr<IXMLDOMNodeList> spNodeList;
	CComPtr<IXMLDOMNode> spNode;
	//spRootEle->selectNodes(OLESTR("/root/node2/*"), &spNodeList); //�õ�node2�µ������ӽڵ�
	spRootEle->selectSingleNode(sectionCBstr/*OLESTR("/root/node2/childnode1/@attrib1")*/, &spNode); //�õ�childnode1��attrib1����
	CComBSTR bsNodeName;
	spNode->get_nodeName(&bsNodeName); //�ڵ���
	string strNodeName = ConvertBstr2String(bsNodeName);
	CComVariant varVal;
	spNode->get_nodeValue(&varVal); //�ڵ�ֵ
	string strNodeValue = ConvertBstr2String(varVal.bstrVal);
	//

	return strNodeValue;

}


//дxml
void XmlOperator::WriteXmlOle(PVOID lpRoot,PVOID lpDoc,string xmlName)
{
	CComPtr<IXMLDOMDocument> spDoc = *(CComPtr<IXMLDOMDocument>*)lpDoc;
	CComPtr<IXMLDOMElement> spRootEle = *(CComPtr<IXMLDOMElement>*)lpRoot;

	//д��XML
	CComPtr<IXMLDOMNode> spNode;
	spRootEle->selectSingleNode(OLESTR("/root/node1"), &spNode);
	spNode->put_text(OLESTR("newText")); //д��text
	spRootEle->selectSingleNode(OLESTR("/root/node2/childnode1/@attrib1"), &spNode);
	spNode->put_nodeValue(CComVariant(OLESTR("newValue"))); //д��value
	CComPtr<IXMLDOMNode> spNewNode;
	spDoc->createNode(CComVariant(NODE_ELEMENT), OLESTR("childnode3"), OLESTR(""), &spNewNode); //�����½ڵ�
	spRootEle->selectSingleNode(OLESTR("/root/node2"), &spNode);
	spNode->appendChild(spNewNode, &spNewNode); //���½ڵ��Ϊnode2���ӽڵ�
	spNewNode->put_text(OLESTR("childtext2")); //д���½ڵ�text
	CComQIPtr<IXMLDOMElement> spEle = spNewNode; //ע������ʹ��CComQIPtr
	spEle->setAttribute(OLESTR("attrib1"), CComVariant(OLESTR("value1")));//���½ڵ��������
	spDoc->save(CComVariant(OLESTR("stocks.xml")));
}

void XmlOperator::ProcessNode(CComPtr<IXMLDOMNode>& spNode)
{
	CComBSTR bsNodeName;
	spNode->get_nodeName(&bsNodeName); //�ڵ���	

	string strNodeName = ConvertBstr2String(bsNodeName);
	AfxInfoLog(strNodeName);
	//AfxMessageBox(COLE2CT(bsNodeName));
	CComVariant varVal;
	spNode->get_nodeValue(&varVal); //�ڵ�ֵ

	string strNodeValue = ConvertBstr2String(varVal.bstrVal);
	AfxInfoLog(strNodeValue);
	//AfxMessageBox(COLE2CT(varVal.bstrVal));

	DOMNodeType eNodeType;
	spNode->get_nodeType(&eNodeType);
	if (eNodeType == NODE_ELEMENT) //ֻ��NODE_ELEMENT���Ͳ��ܰ��������Ժ��ӽڵ�
	{
		//�ݹ�����ڵ�����
		CComPtr<IXMLDOMNamedNodeMap> spNameNodeMap;
		spNode->get_attributes(&spNameNodeMap);
		long nLength;
		spNameNodeMap->get_length(&nLength);
		for (long i = 0; i != nLength; ++i)
		{
			CComPtr<IXMLDOMNode> spNodeAttrib; //ע������Ҳ��һ��IXMLDOMNode
			spNameNodeMap->get_item(i, &spNodeAttrib);
			ProcessNode(spNodeAttrib);
		}

		//�ݹ�����ӽڵ�
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
	//���ֽ�תխ�ַ�
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
	SysFreeString(bstrText); // �����ͷ�
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
	int bCo = ::CoInitialize(NULL);//��ʼ��COM
}
XmlSdk::~XmlSdk()
{
	::CoUninitialize();//�ͷ�COM�ӿ�
}

//�ڵ㴦����
void XmlSdk::ProcessNode(MSXML2::IXMLDOMNodePtr spNode)
{
	std::cout << "nodeName: " << spNode->nodeName;
	if (spNode->nodeType == NODE_ATTRIBUTE || spNode->nodeType == NODE_TEXT)
		std::cout << "\tnodeValue: " << _bstr_t(spNode->nodeValue);
	std::cout << std::endl;

	if (spNode->nodeType == NODE_ELEMENT)
	{
		MSXML2::IXMLDOMNamedNodeMapPtr spNameNodeMap = spNode->attributes;
		for (long i = 0; i != spNameNodeMap->length; ++i) //�����ڵ�����
			ProcessNode(spNameNodeMap->item[i]);

		MSXML2::IXMLDOMNodeListPtr spNodeList = spNode->childNodes;
		for (long i = 0; i != spNodeList->length; ++i) //�����ӽڵ�
			ProcessNode(spNodeList->item[i]);
	}
}

//��ȡxml
void XmlSdk::ReadXml(string xmlName)
{
	XmlOperator xo;
	//��ȡXML
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
		MessageBox(NULL,_T("�޷���ȷ��ȡxml�ļ�"), _T("����"), MB_ICONERROR);
		return;
	}

	MSXML2::IXMLDOMElementPtr spRoot = spXMLDoc->documentElement; //���ڵ�
	// ȡ�ø��ڵ������
	_variant_t strRootName = spRoot->nodeName/*nodeName*/;
	_bstr_t wstrRootName(strRootName.bstrVal);
	string strName = wstrRootName;

	MSXML2::IXMLDOMNodeListPtr spNodeList = spRoot->childNodes;
	for (long i = 0; i != spNodeList->length; ++i) //�����ӽڵ�
		ProcessNode(spNodeList->item[i]);

	//д��XML
	spRoot->selectSingleNode(L"/root/node1")->text = L"newText";
	spRoot->selectSingleNode(L"/root/node2/childnode1/@attrib1")->nodeValue =  L"newValue";
	MSXML2::IXMLDOMNodePtr spNewNode = spRoot->selectSingleNode(L"/root/node2")->appendChild(
		spXMLDoc->createNode(_variant_t(NODE_ELEMENT), L"childnode3", L"")
		); //��node2�������ӽڵ�childnode3
	spNewNode->text = L"childtext2";
	MSXML2::IXMLDOMElementPtr spEle = spNewNode;
	spEle->setAttribute(L"attrib1", _variant_t(L"value1")); //���������
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
	TiXmlPrinter printer;//�ṩ�Ĺ�����,Ŀ���ǽ�xml�����ݰ���ʽ���
	doc.Accept(&printer);
	cout  << printer.CStr() << endl;//���

	TiXmlElement*node = doc.FirstChildElement();//��ȡ��һ��element�ڵ�
	cout << node->Value() << endl;//����ڵ��ֵ
	string t;
	node->QueryValueAttribute("type", &t);//��ȡ�ڵ�����
	cout << t << endl;

	doc.FirstChild()->NextSibling()->ToElement()->QueryStringAttribute("type", &t);//��ȡ�ڶ����ӽڵ������
	cout << "2:" << t << endl;

	//ʹ�ñ����ķ�ʽ���д���
	TiXmlNode* child = NULL;
	TiXmlElement* element = NULL;
	TiXmlAttribute *attr = NULL;
	int ct;
	while(child = doc.FirstChild()->IterateChildren(child))
	{
		cout << child->ValueStr() << "\t";
		ct = child->Type();
		cout << ct << "\t";
		//���ݲ�ͬ�Ľڵ���������Ӧ����  
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
