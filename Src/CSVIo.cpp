
#include "CSVIo.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::ios;
using std::wstring;
using std::wifstream;
using std::wstringstream;
using std::vector;

/// @brief �ַ����ָ�
/// @param[in] ch �ָ��ַ�
/// @param[in] srcStr Դ�ַ���
/// @param[in] strList �ָ����ַ����б�
static void WStringSplit(IN const wchar_t ch, IN const wstring& srcStr, OUT vector<wstring>& strList)
{
    strList.clear();

    size_t startPos = 0;
    size_t length = 0;

    size_t srcLen = srcStr.length();
    for (size_t i = 0; i < srcLen; i++)
    {
        if (srcStr[i] == ch)
        {
            strList.push_back(srcStr.substr(startPos, length));
            startPos = i + 1;
            length = 0;
        }
        else
        {
            length++;
        }
    }

    strList.push_back(srcStr.substr(startPos, length));
}

/// <SUMMARY>
/// �ַ����ü�
/// ȥ���ַ�����ʼ�ͽ����Ŀհ��ַ�, ��: �ո�, ����, �س�, �Ʊ��
/// </SUMMARY>
static void WStringTrimmed(INOUT wstring& str)
{
    if (str.empty())
    {
        return;
    }

    size_t i = 0;
    while (iswspace(str[i]) != 0)
    {
        i++;
    }
    str.erase(0, i);

    if (str.empty())
    {
        return;
    }

    size_t j = str.length() - 1;
    while (isspace(str[j]) != 0)
    {
        if (j <= 0)
            break;

        j--;
    }

    str.erase(j + 1);

}

/// <SUMMARY>
/// �ַ���ת��Ϊ������
/// </SUMMARY>
static double StringToDouble(IN const wstring& str)
{
    double value;
    wstringstream strStream(str);
    strStream >> value;
    return value;
}



/// @brief CSV�ļ�������
class CCSVParser
{
public:
    /// @brief ���캯��
    explicit CCSVParser(IN const wchar_t* fileName)
    {
        m_fileName = fileName;
        m_bSkipHeader = false;
    }

    /// @brief ��������
    ~CCSVParser()
    {

    }

    /// @brief �����Ƿ���������
    void SetSkipHeader(IN bool skip)
    {
        m_bSkipHeader = skip;
    }

    /// @brief ������������
    bool LoadAllData(OUT LDataMatrix& dataMatrix)
    {
        wstring str;
        wifstream fin(m_fileName, ios::in);

        // �ļ�������
        if (!fin) 
        {
            return false;
        }

        // ����Ƿ���Ҫ��������
        if (m_bSkipHeader)
            getline(fin, str);

        vector<vector<wstring>> strMatrix;
        while (getline(fin, str))
        {
            // ȥ����ͷ�ͽ�β�Ŀհ��ַ�
            WStringTrimmed(str);
            if (str.empty())
                continue;

            // �ָ��ַ���
            vector<wstring> strList;
            WStringSplit(L',', str, strList);

            // ���ÿ���ַ����Ƿ�Ϊ��
            for (auto iter = strList.begin(); iter != strList.end(); iter++)
            {
                WStringTrimmed(*iter);
                if (iter->empty())
                    return false;
            }

            strMatrix.push_back(strList);
        }

        // �г���
        size_t rowLength = strMatrix.size();
        if (rowLength < 1)
            return false;
        
        // �г���
        size_t colLength = strMatrix[0].size();
        if (colLength < 1)
            return false;

        dataMatrix.Reset((unsigned int)rowLength, (unsigned int)colLength, 0.0);

        for (size_t row = 0; row < rowLength; row++)
        {
            // ���ÿһ���е����ݳ����Ƿ�һ��
            if (strMatrix[row].size() != colLength)
            {
                dataMatrix.Reset(0, 0);
                return false;
            }

            for (size_t col = 0; col < colLength; col++)
            {
                dataMatrix[(unsigned int)row][(unsigned int)col] = StringToDouble(strMatrix[row][col]);
            }
        }

        return true;
    }

private:
    bool m_bSkipHeader; ///< ��������
    wstring m_fileName; ///< �ļ���

};

LCSVParser::LCSVParser(IN const wchar_t* fileName)
{
    m_pParser = nullptr;
    m_pParser = new CCSVParser(fileName);
}

LCSVParser::~LCSVParser()
{
    if (nullptr != m_pParser)
    {
        delete m_pParser;
        m_pParser = nullptr;
    }
}

void LCSVParser::SetSkipHeader(IN bool skip)
{
    m_pParser->SetSkipHeader(skip);
}

bool LCSVParser::LoadAllData(OUT LDataMatrix& dataMatrix)
{
    return m_pParser->LoadAllData(dataMatrix);
}
