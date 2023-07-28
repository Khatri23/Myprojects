#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
#include<vector>
class matrix{
private:
    float x,y,z;
    std::vector<float>NEW;
public:
    matrix():x(0.0),y(0.0),z(0.0){}

    matrix(float x,float y,float z);

    void Setvalue()
    {
        std::cout<<"Enter the x cordinate:";
        std::cin>>x;
        std::cout<<"Enter the y-cordinate:";
        std::cin>>y;
        std::cout<<"Enter the z-cordinate:";
        std::cin>>z;
    }
    void Set_Translation_Vector()
    {
        std::vector<std::vector<float>> mat(4,std::vector<float>(4));
        int c=88;
        for(i=0;i<3;i++)
        {
        
            std::cout<<"translation value for "<<static_cast<char>(c)<<'-';
            std::cin>>mat[i][3];
            c++;
        }
        calculation(mat);
    }
    void Translated_cordinate()
    {
        int c=88;
        std::cout<<"successfully translated-"<<std::endl;
        for(auto P:NEW)
        {
            std::cout<<static_cast<char>(c)<<"- "<<P<<std::endl;
            c++;
            if(c==91)
            c=87;
        }
    }
private:
    int i,j;
    void calculation(std::vector<std::vector<float>> &);


};

matrix::matrix(float x,float y,float z)
{
    this->x=x;
    this->y=y;
    this->z=z;
}
void matrix:: calculation(std::vector<std::vector<float>> &mat)
{
    for( i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(i==j)
            mat[i][j]=1;
            else if(j<3)
            {
                mat[i][j]=0;
            } 
        }
    }
    std::vector<std::vector<float>> temp(4,std::vector<float>(1));
    temp[0][0]=x;
    temp[1][0]=y;temp[2][0]=z;temp[3][0]=1;
    
    for(i=0;i<4;i++)
    {
        for(j=0;j<1;j++)
        {
            float sum=0;
            for(int k=0;k<4;k++)
            {
                sum+=mat[i][k]*temp[k][j];
            }
            NEW.push_back(sum);
        }
    }
    
}
#endif
