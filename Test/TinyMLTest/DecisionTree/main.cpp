
#include "../../../Src/LDecisionTree.h"
#include "../../../Src/CSVIo.h"

#include <cstdio>
#include <windows.h>

/// @brief ��ӡ����
void PrintMatrix(IN const LDataMatrix& dataMatrix)
{
    printf("Matrix Row: %u  Col: %u\n", dataMatrix.RowLen, dataMatrix.ColumnLen);
    for (unsigned int i = 0; i < dataMatrix.RowLen; i++)
    {
        for (unsigned int j = 0; j < dataMatrix.ColumnLen; j++)
        {
            printf("%.2f  ", dataMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    // �������ݼ�
    LCSVParser csvParser(L"../../../DataSet/iris.csv");
    csvParser.SetSkipHeader(true);
    LDataMatrix dataMatrix;
    csvParser.LoadAllData(dataMatrix);

    unsigned int rowLen = dataMatrix.RowLen;
    unsigned int colLen = dataMatrix.ColumnLen;

    // �����ݼ����Ϊ�������ϱ�ǩ��
    LDTCMatrix xMatrix;
    LDTCMatrix yVector;
    dataMatrix.SubMatrix(0, rowLen, 0, colLen - 1, xMatrix);
    dataMatrix.SubMatrix(0, rowLen, colLen - 1, 1, yVector);

    // ��������ֵ�ֲ�����
    double featureN[4] = 
    {
        DTC_FEATURE_CONTINUUM, 
        DTC_FEATURE_CONTINUUM, 
        DTC_FEATURE_CONTINUUM, 
        DTC_FEATURE_CONTINUUM
    };
    LDTCMatrix nVector(1, 4, featureN);

    LDecisionTreeClassifier clf;
    clf.TrainModel(xMatrix, nVector, yVector);
    //clf.PrintTree();

    double score = clf.Score(xMatrix, yVector);

    //printf("Model Score: %.2f\n", score);

    //system("pause");

    return 0;
}