#pragma once

#include <iostream>
#include <vector>
#include <iomanip>


/**
 * This class illustrates two topics:
 * <ul>
 * <li>Template classes</li>
 * <li>Operator overloading</li>
 * </ul>
 */
template <typename T>
class Matrix
{
public:
    Matrix(const unsigned int lines, const unsigned int columns) :
        m_mat(),
        m_lines(lines),
        m_columns(columns)
    {
        std::cout << "constructor (i,j) called" << std::endl;
        for (auto i = 0u; i < m_lines; i++) {
            m_mat.push_back(new T[m_columns]);
        }
    }


    virtual ~Matrix()
    {
        std::cout << "Destructor called. Nr lines = " << m_lines << std::endl;
        for (auto i = 0u; i < m_lines; i++) {
            delete[] m_mat[i];
        }
    }


    void add(unsigned int i, unsigned int j, T obj)
    {
        m_mat[i][j] = obj;
    }


    Matrix(const Matrix& other) :
        m_mat(),
        m_lines(other.m_lines),
        m_columns(other.m_columns)
    {
        std::cout << "copy constructor called" << std::endl;
        for (auto i = 0u; i < m_lines; i++) {
            m_mat.push_back(new T[m_columns]);
            for (auto j = 0u; j < m_columns; j++) {
                m_mat[i][j] = other.m_mat[i][j];
            }
        }
    }


    const Matrix& operator=(const Matrix& other)
    {
        std::cout << "assignment operator called" << std::endl;
        m_lines = other.m_lines;
        m_columns = other.m_columns;

        for (auto i = 0u; i < m_lines; i++) {
            m_mat.push_back(new T[m_columns]);
            for (auto j = 0u; j < m_columns; j++) {
                m_mat[i][j] = other.m_mat[i][j];
            }
        }

        return *this;
    }


    bool operator==(const Matrix& other)
    {
        if (m_lines != other.m_lines || m_columns != other.m_columns) {
            return false;
        }

        for (auto i = 0u; i < m_lines; i++) {
            for (auto j = 0u; j < m_columns; j++) {
                if (m_mat[i][j] != other.m_mat[i][j])
                    return false;
            }
        }

        return true;
    }


    bool operator!=(const Matrix& other) { return !operator==(other); }


    friend std::ostream& operator<<(std::ostream& out, const Matrix& m)
    {
        for (auto i = 0u; i < m.m_lines; i++) {
            for (auto j = 0u; j < m.m_columns; j++) {
                out << m.m_mat[i][j] << " ";
            }
            out << std::endl;
        }

        return out;
    }


    friend Matrix operator+(const Matrix& m1, const Matrix& m2)
    {
        if (m1.m_lines != m2.m_lines || m1.m_columns != m2.m_columns) {
            throw std::invalid_argument("The two matrices have different sizes => cannot be added");
        }
        Matrix m(m1.m_lines, m1.m_columns);
        for (auto i = 0u; i < m.m_lines; i++) {
            for (auto j = 0u; j < m.m_columns; j++) {
                m.m_mat[i][j] = m1.m_mat[i][j] + m2.m_mat[i][j];
            }
        }

        return m;
    }


    Matrix& operator+(const T& obj)
    {
        for (auto i = 0u; i < m_lines; i++) {
            for (auto j = 0u; j < m_columns; j++) {
                m_mat[i][j] = m_mat[i][j] + obj;
            }
        }

        return *this;
    }


    Matrix& operator-(const T& obj)
    {
        for (auto i = 0u; i < m_lines; i++) {
            for (auto j = 0u; j < m_columns; j++) {
                m_mat[i][j] = m_mat[i][j] - obj;
            }
        }

        return *this;
    }


    friend Matrix operator-(const Matrix& m1, const Matrix& m2)
    {
        if (m1.m_lines != m2.m_lines || m1.m_columns != m2.m_columns) {
            throw std::invalid_argument("The two matrices have different sizes => cannot be subtracted");
        }
        Matrix m(m1.m_lines, m1.m_columns);
        for (auto i = 0u; i < m1.m_lines; i++) {
            for (auto j = 0u; j < m2.m_lines; j++) {
                m.m_mat[i][j] = m1.m_mat[i][j] - m2.m_mat[i][j];
            }
        }

        return m;
    }


    Matrix& operator-=(const T& obj)
    {
        for (auto i = 0u; i < m_lines; i++) {
            for (auto j = 0u; j < m_columns; j++) {
                m_mat[i][j] = m_mat[i][j] - obj;
            }
        }

        return *this;
    }


    Matrix& operator+=(const T& obj)
    {
        for (auto i = 0u; i < m_lines; i++) {
            for (auto j = 0u; j < m_columns; j++) {
                m_mat[i][j] = m_mat[i][j] + obj;
            }
        }

        return *this;
    }


private:
    std::vector<T*> m_mat;

    unsigned int m_lines;

    unsigned int m_columns;
};
