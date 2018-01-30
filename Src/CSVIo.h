/// @file CSVIo.h
/// @brief  CSV�ļ�����ͷ�ļ�
/// 
/// Detail:
/// @author Jie_Liu  
/// @version   
/// @date 2018/01/30

#ifndef _CSVIo_H_
#define _CSVIo_H_

#include "LMatrix.h"


typedef LMatrix<double> LDataMatrix;     ///< ���ݾ���

class CCSVParser;

/// @brief CSV�ļ�������
/// ��������֧֮�ֽ�����ֵ����, ���Ҳ�����ȱʧ����
class LCSVParser
{
public:
    /// @brief ���캯��
    explicit LCSVParser(IN const wchar_t* fileName);

    /// @brief ��������
    ~LCSVParser();

    /// @brief �����Ƿ���������
    /// Ĭ�ϲ���������
    /// @param[in] skip true(����), false(������)
    void SetSkipHeader(IN bool skip);

    /// @brief ������������
    /// @param[in] dataMatrix �洢����
    bool LoadAllData(OUT LDataMatrix& dataMatrix);

private:
    CCSVParser* m_pParser; ///< CSV�ļ�������ʵ�ֶ���
};

#endif
