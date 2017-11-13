//
//  main.cpp
//  Ajedres
//
//  Created by michel lopez on 09/11/17.
//  Copyright © 2017 michel lopez. All rights reserved.
//

#include <iostream>
#include <stdlib.h>

int tabla [8][8] = { {-8,-6,-7,-9,-10,-7,-6,-8},
                     {-5,-5,-5,-5,-5,-5,-5,-5},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {5,5,5,5,5,5,5,5},
                     {8,6,7,9,10,7,6,8}};

char numeros[8]={'8','7','6','5','4','3','2','1'};
char letras[9]={' ','a','b','c','d','e','f','g','h'};


 void reset(){
    int tabla[8][8]= { {-8,-6,-7,-9,-10,-7,-6,-8},
        {-5,-5,-5,-5,-5,-5,-5,-5},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {5,5,5,5,5,5,5,5},
        {8,6,7,9,10,7,6,8}};;
    
}
int isLetra(char c){
    
    switch (c){
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case 'e': return 4;
        case 'f': return 5;
        case 'g': return 6;
        case 'h': return 7;
        default:
            return -1;
    }
}

int isNumero(char c){
    switch (c){
        case '1': return 7;
        case '2': return 6;
        case '3': return 5;
        case '4': return 4;
        case '5': return 3;
        case '6': return 2;
        case '7': return 1;
        case '8': return 0;
        default:
            return -1;
    }
}

struct Movimiento {
    int C1;
    int F1;
    int C2;
    int F2;
    
    int pieza;
    int valida1;
    bool valida;
};

Movimiento nuevaP (int c1, int f1,int c2,int f2, int pieza, int valida1, bool valida){
    Movimiento p;

    return p;
}

Movimiento analiza(std::string accion){
    
    Movimiento m;
    
    bool continua = true;
    int i=0;
    int edo=0;
    int varRetorno=0;
    char c = '0';
    
    while (continua){
        c = accion[i];
        switch (edo) {
            case 0:
                varRetorno = isLetra(c);
                
                if ( varRetorno+1 ){
                    m.C1 = varRetorno;
                }
                else{
                    std::cout << "No es letra 0";
                    continua = false;
                }
                edo=1;
                break;
            case 1:
                varRetorno = isNumero(c);
                if ( varRetorno+ 1 ){
                    m.F1 = varRetorno;
                }
                else{
                    std::cout << "No es letra 1";
                    continua=false;
                }
                edo=2;
                break;
            case 2:
                //c --> t
                if (c != 't'){
                    std::cout << "No es letra t";
                    continua=false;
                }
                edo=3;
                break;
            
            case 3:
                    if (c != 'o'){
                        std::cout << "No es letra o";
                        continua=false;
                    }
                edo=4;
                break;
                
            case 4:
                varRetorno = isLetra(c);
                
                if ( varRetorno+1 ){
                    m.C2 = varRetorno;
                }
                else{
                    std::cout << "No es letra 4";
                    continua = false;
                }
                edo=5;
                break;
                
            case 5:
                varRetorno = isNumero(c);
                if ( varRetorno+ 1 ){
                    m.F2 = varRetorno;
                }
                continua=false;
                edo=6;
                break;
                
            default:
                break;
        }
        i++;
    }
    
    if (edo == 6){
        m.valida = true;
    }
    else{
        m.valida = false;
    }
    
    return m;
}

Movimiento valiPieza(Movimiento m){
    int p;
    p = tabla[m.F1][m.C1];
    
    if (p == 0)
        std::cout<< "Error de pieza elegida";
    else
    m.pieza = p;
    
    return m;
}

void moverCaballo(Movimiento m ){
 
    int val = 0;
    
    if ( (abs(m.F2 -m.F1)== 1 && abs(m.C2 -m.C1)== 2 ) ||
        (abs(m.F2 -m.F1)== 2 && abs(m.C2 -m.C1)== 1 )  ){
        
        val = tabla[m.F2][m.C2];
        if ( val == 0 ){
            tabla[m.F2][m.C2] = m.pieza;
            tabla[m.F1][m.C1] = 0;
        }
        else{
            if (val * m.pieza < 0 ){
                tabla[m.F2][m.C2] = m.pieza;
                tabla[m.F1][m.C1] = 0;
            }
            else{
                std::cout<< "Error de pieza atacada";
            }
        }
    }
    
}

void moverPeon(Movimiento m){
    if ( ( (m.C2 - m.C1 <= 1) &&  (m.C2 - m.C1 >= -1 )  && abs(m.F2 -m.F1)== 1 ) ){
        if ( m.F1 > m.F2  && m.pieza >0 ){
            //std::cout<<"Mover peon positivo adelante";
            tabla[m.F2][m.C2] = m.pieza;
            tabla[m.F1][m.C1] = 0;
        }
        else{
            if ( m.F1 < m.F2  && m.pieza < 0 ){
                //std::cout<<"Mover peon negativo adelante";
                tabla[m.F2][m.C2] = m.pieza;
                tabla[m.F1][m.C1] = 0;
            }
        }
        
    }
}

Movimiento movimientosGeneralizados(int sign1, int sign2, Movimiento m){
    int temp1,temp2,val;
    temp1=1*sign1;
    temp2=1*sign2;
    val = tabla[m.F2][m.C2];
    while((m.F1+temp1!=m.F2)||(m.C1+temp2!=m.C2)){
        if(tabla[m.F1+temp1][m.C1+temp2]==0){
            temp1=temp1+sign1;
            temp2=temp2+sign2;
            m.valida1=1;
        }
        else{
            std::cout<< "Error de colision";
			std::cout<<"\n";
            m.valida1=0;
            
            break;
        }
    }
    if(m.valida1){
        if ( val == 0 ){
            tabla[m.F2][m.C2] = m.pieza;
            tabla[m.F1][m.C1] = 0;
        }
        else{
            if (val * m.pieza < 0 ){
                tabla[m.F2][m.C2] = m.pieza;
                tabla[m.F1][m.C1] = 0;
            }
            else{
                std::cout<< "Error de pieza atacada";
            }
        }
        
    }
    return m;
}

Movimiento moverAlfil(Movimiento m){
    int sign1,sign2;
    int val = 0;
    
    sign1 = m.F2 - m.F1;
    if(sign1!=0){
        sign1 = abs(sign1)/sign1;
    }
    sign2 = m.C2 - m.C1;
    if(sign2!=0){
        sign2 = abs(sign2)/sign2;
    }
    
    if ( abs(m.F2 - m.F1) ==  abs(m.C2 - m.C1)){
        val = tabla[m.F2][m.C2];
        movimientosGeneralizados(sign1,sign2,m);
    }
    return m;
}

Movimiento moverTorre(Movimiento m){
    int sign1,sign2;
    int val = 0;
    
    sign1 = m.F2 - m.F1;
    if(sign1!=0){
        sign1 = abs(sign1)/sign1;
    }
    sign2 = m.C2 - m.C1;
    if(sign2!=0){
        sign2 = abs(sign2)/sign2;
    }
    
    if ( (m.F2 == m.F1) ||  (m.C2 == m.C1)){
        val = tabla[m.F2][m.C2];
        movimientosGeneralizados(sign1,sign2,m);
    }
    return m;
}

Movimiento moverReina(Movimiento m){
    int sign1,sign2;
    int val = 0;
    
    sign1 = m.F2 - m.F1;
    if(sign1!=0){
        sign1 = abs(sign1)/sign1;
    }
    sign2 = m.C2 - m.C1;
    if(sign2!=0){
        sign2 = abs(sign2)/sign2;
    }
    
    
    if ( (abs(m.F2 - m.F1) ==  abs(m.C2 - m.C1))||(m.F2 == m.F1) ||  (m.C2 == m.C1)){
        val = tabla[m.F2][m.C2];
        movimientosGeneralizados(sign1,sign2,m);
    }
    return m;
}

Movimiento moverRey(Movimiento m){
    int sign1,sign2;
    int val = 0;
    
    sign1 = m.F2 - m.F1;
    if(sign1!=0){
        sign1 = abs(sign1)/sign1;
    }
    sign2 = m.C2 - m.C1;
    if(sign2!=0){
        sign2 = abs(sign2)/sign2;
    }
    if ( ((abs(m.F2-m.F1)==1||abs(m.F2-m.F1)==0))&&(abs(m.C2-m.C1)==1||abs(m.C2-m.C1)==0)){
        val = tabla[m.F2][m.C2];
        movimientosGeneralizados(sign1,sign2,m);
    }
    return m;
}

Movimiento valiMovi(Movimiento m){
    
    switch ( abs(m.pieza) ) {

        case 5:
            moverPeon(m);
            break;
        case 6:
            moverCaballo(m);
            break;
        case 7:
            moverAlfil(m);
            break;
        case 8:
            moverTorre(m);
            break;
        case 9:
            moverReina(m);
        case 10:
            moverRey(m);
        default:
            break;
    }
    return m;
}

void display()
{
    int i,j;
    for(i=0;i<8;i++)
    {
        std::cout<<numeros[i]<<"  ";
        for(j=0;j<8;j++)
            if(tabla[i][j]>=0&&tabla[i][j]<10){
                std::cout<<tabla[i][j]<<"  ";
            }
            else{
                if(tabla[i][j]==-10){
                    std::cout<<tabla[i][j];
                }
                else{
                    std::cout<<tabla[i][j]<<" ";
                }
            }
        std::cout<<std::endl;
    }
    std::cout<<"\n";
    for(i=0;i<9;i++){
        std::cout<<letras[i]<<"  ";
    }
    std::cout<<"\n";
}

void jugar(){
    reset();
    std::string  accion;
    Movimiento m1;
    display();
    while(1){
        std::getline(std::cin,accion);
        if(accion[0]=='0'){
            std::cout<<"Fin del juego";
            std::cout<<"\n";
            break;
        }
        m1 = analiza(accion);
        
        if (m1.valida){
            m1=valiPieza(m1);
            if (m1.pieza != 0 ){
                valiMovi(m1);
            }
            else{
                std::cout<<"Error de movimiento";
            }
        }
        else{
            std::cout<<"Error de entrada incorrecta";
        }
        display();
    }
}
int main(int argc, const char * argv[]) {

    jugar();
    
    return 0;
}
