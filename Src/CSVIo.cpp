
#include "CSVIo.h"

#include <iostream>
#include <fstream>
#include <string>

using std::ios;
using std::wstring;
using std::wifstream;



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

        while (getline(fin, str))
        {
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
    m_pParser->LoadAllData(dataMatrix);
}