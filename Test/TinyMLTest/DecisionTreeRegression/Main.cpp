#include "../../../Src/LDecisionTree.h"
#include "../../../Src/LCSVIo.h"
#include "../../../Src/LPreProcess.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

/// @brief ��ӡ����
void MatrixPrint(IN const LDataMatrix& dataMatrix)
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

/// @brief �������ع�
void TestDecisionTreeRegression()
{
    // �����������ݼ�
    LCSVParser dataCSVParser(L"../../../DataSet/diabetes_data.csv");
    dataCSVParser.SetDelimiter(L' ');
    LDataMatrix xMatrix;
    dataCSVParser.LoadAllData(xMatrix);
    LCSVParser targetCSVParser(L"../../../DataSet/diabetes_target.csv");
    LDataMatrix yVector;
    targetCSVParser.LoadAllData(yVector);

    // ��������ֵ�ֲ�����
    double featureN[10] =
    {
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM
    };
    LDTMatrix nVector(1, 10, featureN);


    // �������Իع����
    LDecisionTreeRegression dtReg;

    printf("Decision Tree Regression Model Train:\n");
    dtReg.TrainModel(xMatrix, nVector, yVector);
    double score = dtReg.Score(xMatrix, yVector);
    printf("Model Score: %.2f\n", score);
}


int main()
{
    TestDecisionTreeRegression();

    system("pause");

    return 0;
}
