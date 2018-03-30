#include "smooth.h"

Smooth::Smooth()
{

}

/**
 * @brief Smooth::LinearSmooth3
 *          3点线性平滑滤波
 * @param s         源数据
 * @param listDist  滤波后数据
 */
void Smooth::LinearSmooth3(QVector<double> s, QVector<double> &listDist)
{
    int i;
    int len = s.size();

    listDist.clear();
    if (len < 3)
    {
        for (i = 0; i < len; i++)
        {
            listDist.append(s.at(i));
        }
    }
    else
    {
        listDist.append((5.0 * s.at(0) + 2.0 * s.at(1) - s.at(2)) / 6.0);
        for (i = 1; i <= len - 2; i++)
        {
            listDist.append((s.at(i - 1) + s.at(i) + s.at(i + 1)) / 3.0);
        }
        listDist.append((5.0 * s.at(len - 1) + 2.0 * s.at(len - 2) - s.at(len - 3)) / 6.0);
    }
}

/**
 * @brief Smooth::LinearSmooth5
 *          5点线性平滑滤波
 * @param s         源数据
 * @param listDist  滤波后数据
 */
void Smooth::LinearSmooth5(QVector<double> s, QVector<double> &listDist)
{
    int i;
    int len = s.size();

    listDist.clear();
    if (len < 5)
    {
        for (i = 0; i < len; i++)
        {
            listDist.append(s.at(i));
        }
    }
    else
    {
        listDist.append((3.0 * s.at(0) + 2.0 * s.at(1) + s.at(2) - s.at(4)) / 5.0);
        listDist.append((4.0 * s.at(0) + 3.0 * s.at(1) + 2.0 * s.at(2) + s.at(3)) / 10.0);
        for (i = 2; i <= len - 3; i++)
        {
            listDist.append((s.at(i - 2) + s.at(i - 1) + s.at(i) + s.at(i + 1) + s.at(i + 2)) / 5.0);
        }
        listDist.append((4.0 * s.at(len - 1) + 3.0 * s.at(len - 2) + 2.0 * s.at(len - 3) + s.at(len - 4)) / 10.0);
        listDist.append((3.0 * s.at(len - 1) + 2.0 * s.at(len - 2) + s.at(len - 3) - s.at(len - 5)) / 5.0);
    }
}

/**
 * @brief Smooth::LinearSmooth7
 *          7点线性平滑滤波
 * @param s         源数据
 * @param listDist  滤波后数据
 */
void Smooth::LinearSmooth7(QVector<double> s, QVector<double> &listDist)
{
    int i;
    int len = s.size();

    listDist.clear();
    if (len < 7)
    {
        for (i = 0; i < len; i++)
        {
            listDist.append(s.at(i));
        }
    }
    else
    {
        listDist.append((13.0 * s.at(0) + 10.0 * s.at(1) + 7.0 * s.at(2) + 4.0 * s.at(3) + s.at(4) - 2.0 * s.at(5) - 5.0 * s.at(6)) / 28.0);
        listDist.append((5.0 * s.at(0) + 4.0 * s.at(1) + 3.0 * s.at(2) + 2.0 * s.at(3) + s.at(4) - s.at(6)) / 14.0);
        listDist.append((7.0 * s.at(0) + 6.0 * s.at(1) + 5.0 * s.at(2) + 4.0 * s.at(3) + 3.0 * s.at(4) + 2.0 * s.at(5) + s.at(6)) / 28.0);
        for (i = 3; i <= len - 4; i++)
        {
            listDist.append((s.at(i - 3) + s.at(i - 2) + s.at(i - 1) + s.at(i) + s.at(i + 1) + s.at(i + 2) + s.at(i + 3)) / 7.0);
        }
        listDist.append((7.0 * s.at(len - 1) + 6.0 * s.at(len - 2) + 5.0 * s.at(len - 3) + 4.0 * s.at(len - 4) + 3.0 * s.at(len - 5) + 2.0 * s.at(len - 6) + s.at(len - 7)) / 28.0);
        listDist.append((5.0 * s.at(len - 1) + 4.0 * s.at(len - 2) + 3.0 * s.at(len - 3) + 2.0 * s.at(len - 4) + s.at(len - 5) - s.at(len - 7)) / 14.0);
        listDist.append((13.0 * s.at(len - 1) + 10.0 * s.at(len - 2) + 7.0 * s.at(len - 3) + 4.0 * s.at(len - 4) + s.at(len - 5) - 2.0 * s.at(len - 6) - 5.0 * s.at(len - 7)) / 28.0);
    }
}

/**
 * @brief Smooth::QuadraticSmooth5
 *          5点二次平滑滤波
 * @param s         源数据
 * @param listDist  滤波后数据
 */
void Smooth::QuadraticSmooth5(QVector<double> s, QVector<double> &listDist)
{
    int i;
    int len = s.size();

    listDist.clear();
    if (len < 5)
    {
        for (i = 0; i < len; i++)
        {
            listDist.append(s.at(i));
        }
    }
    else
    {
        listDist.append((31.0 * s.at(0) + 9.0 * s.at(1) - 3.0 * s.at(2) - 5.0 * s.at(3) + 3.0 * s.at(4)) / 35.0);
        listDist.append((9.0 * s.at(0) + 13.0 * s.at(1) + 12.0 * s.at(2) + 6.0 * s.at(3) - 5.0 * s.at(4)) / 35.0);
        for (i = 2; i <= len - 3; i++)
        {
            listDist.append((-3.0 * (s.at(i - 2) + s.at(i + 2)) + 12.0 * (s.at(i - 1) + s.at(i + 1)) + 17 * s.at(i)) / 35.0);
        }
        listDist.append((9.0 * s.at(len - 1) + 13.0 * s.at(len - 2) + 12.0 * s.at(len - 3) + 6.0 * s.at(len - 4) - 5.0 * s.at(len - 5)) / 35.0);
        listDist.append((31.0 * s.at(len - 1) + 9.0 * s.at(len - 2) - 3.0 * s.at(len - 3) - 5.0 * s.at(len - 4) + 3.0 * s.at(len - 5)) / 35.0);
    }
}

/**
 * @brief Smooth::QuadraticSmooth7
 *          7点二次平滑滤波
 * @param s         源数据
 * @param listDist  滤波后数据
 */
void Smooth::QuadraticSmooth7(QVector<double> s, QVector<double> &listDist)
{
    int i;
    int len = s.size();

    listDist.clear();
    if (len < 7)
    {
        for (i = 0; i < len; i++)
        {
            listDist.append(s.at(i));
        }
    }
    else
    {
        listDist.append((32.0 * s.at(0) + 15.0 * s.at(1) + 3.0 * s.at(2) - 4.0 * s.at(3) - 6.0 * s.at(4) - 3.0 * s.at(5) + 5.0 * s.at(6)) / 42.0);
        listDist.append((5.0 * s.at(0) + 4.0 * s.at(1) + 3.0 * s.at(2) + 2.0 * s.at(3) + s.at(4) - s.at(6)) / 14.0);
        listDist.append((1.0 * s.at(0) + 3.0 * s.at(1) + 4.0 * s.at(2) + 4.0 * s.at(3) + 3.0 * s.at(4) + 1.0 * s.at(5) - 2.0 * s.at(6)) / 14.0);
        for (i = 3; i <= len - 4; i++)
        {
            listDist.append((-2.0 * (s.at(i - 3) + s.at(i + 3)) + 3.0 * (s.at(i - 2) + s.at(i + 2)) + 6.0 * (s.at(i - 1) + s.at(i + 1)) + 7.0 * s.at(i)) / 21.0);
        }
        listDist.append((1.0 * s.at(len - 1) + 3.0 * s.at(len - 2) + 4.0 * s.at(len - 3) + 4.0 * s.at(len - 4) + 3.0 * s.at(len - 5) + 1.0 * s.at(len - 6) - 2.0 * s.at(len - 7)) / 14.0);
        listDist.append((5.0 * s.at(len - 1) + 4.0 * s.at(len - 2) + 3.0 * s.at(len - 3) + 2.0 * s.at(len - 4) + s.at(4) - s.at(len - 7)) / 14.0);
        listDist.append((32.0 * s.at(len - 1) + 15.0 * s.at(len - 2) + 3.0 * s.at(len - 3) - 4.0 * s.at(len - 4) - 6.0 * s.at(len - 5) - 3.0 * s.at(len - 6) + 5.0 * s.at(len - 7)) / 42.0);
    }
}

/**
 * @brief Smooth::CubicSmooth5
 *          5点三次平滑滤波
 * @param s         源数据
 * @param listDist  滤波后数据
 */
void Smooth::CubicSmooth5(QVector<double> s, QVector<double> &listDist)
{
    int i;
    int len = s.size();

    listDist.clear();
    if (len < 5)
    {
        for (i = 0; i < len; i++)
        {
            listDist.append(s.at(i));
        }
    }
    else
    {
        listDist.append((69.0 * s.at(0) + 4.0 * s.at(1) - 6.0 * s.at(2) + 4.0 * s.at(3) - s.at(4)) / 70.0);
        listDist.append((2.0 * s.at(0) + 27.0 * s.at(1) + 12.0 * s.at(2) - 8.0 * s.at(3) + 2.0 * s.at(4)) / 35.0);
        for (i = 2; i <= len - 3; i++)
        {
            listDist.append((-3.0 * (s.at(i - 2) + s.at(i + 2)) + 12.0 * (s.at(i - 1) + s.at(i + 1)) + 17.0 * s.at(i)) / 35.0);
        }
        listDist.append((2.0 * s.at(len - 1) + 27.0 * s.at(len - 2) + 12.0 * s.at(len - 3) - 8.0 * s.at(len - 4) + 2.0 * s.at(len - 5)) / 35.0);
        listDist.append((69.0 * s.at(len - 1) + 4.0 * s.at(len - 2) - 6.0 * s.at(len - 3) + 4.0 * s.at(len - 4) - s.at(len - 5)) / 70.0);
    }
}

/**
 * @brief Smooth::CubicSmooth7
 *          7点三次平滑滤波
 * @param s         源数据
 * @param listDist  滤波后数据
 */
void Smooth::CubicSmooth7(QVector<double> s, QVector<double> &listDist)
{
    int i;
    int len = s.size();

    listDist.clear();
    if (len < 7)
    {
        for (i = 0; i < len; i++)
        {
            listDist.append(s.at(i));
        }
    }
    else
    {
        listDist.append((39.0 * s.at(0) + 8.0 * s.at(1) - 4.0 * s.at(2) - 4.0 * s.at(3) + 1.0 * s.at(4) + 4.0 * s.at(5) - 2.0 * s.at(6)) / 42.0);
        listDist.append((8.0 * s.at(0) + 19.0 * s.at(1) + 16.0 * s.at(2) + 6.0 * s.at(3) - 4.0 * s.at(4) - 7.0 * s.at(5) + 4.0 * s.at(6)) / 42.0);
        listDist.append((-4.0 * s.at(0) + 16.0 * s.at(1) + 19.0 * s.at(2) + 12.0 * s.at(3) + 2.0 * s.at(4) - 4.0 * s.at(5) + 1.0 * s.at(6)) / 42.0);
        for (i = 3; i <= len - 4; i++)
        {
            listDist.append((-2.0 * (s.at(i - 3) + s.at(i + 3)) + 3.0 * (s.at(i - 2) + s.at(i + 2)) + 6.0 * (s.at(i - 1) + s.at(i + 1)) + 7.0 * s.at(i)) / 21.0);
        }
        listDist.append((-4.0 * s.at(len - 1) + 16.0 * s.at(len - 2) + 19.0 * s.at(len - 3) + 12.0 * s.at(len - 4) + 2.0 * s.at(len - 5) - 4.0 * s.at(len - 6) + 1.0 * s.at(len - 7)) / 42.0);
        listDist.append((8.0 * s.at(len - 1) + 19.0 * s.at(len - 2) + 16.0 * s.at(len - 3) + 6.0 * s.at(len - 4) - 4.0 * s.at(len - 5) - 7.0 * s.at(len - 6) + 4.0 * s.at(len - 7)) / 42.0);
        listDist.append((39.0 * s.at(len - 1) + 8.0 * s.at(len - 2) - 4.0 * s.at(len - 3) - 4.0 * s.at(len - 4) + 1.0 * s.at(len - 5) + 4.0 * s.at(len - 6) - 2.0 * s.at(len - 7)) / 42.0);
    }
}
