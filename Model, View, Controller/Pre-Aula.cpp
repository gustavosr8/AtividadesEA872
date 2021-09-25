#include <iostream>
#include <memory>

//g++ Pre-Aula.cpp -o run -std=c++11

class Objeto{
    private:
        float Massa, Velocidade, Posicao, Aceleracao; 

    public:
        Objeto(float m, float v, float p);
        void setMassa(float m);
        void setVelocidade(float v);
        void setPosicao(float x);
        void setAceleracao(float a);

        float getMassa();
        float getPosicao();
        float getVelocidade();
        float getAceleracao();
};
Objeto::Objeto(float m, float v, float p){
    Massa=m;
    Velocidade=v;
    Posicao=p;
}

void Objeto::setMassa(float m){Massa = m;}
void Objeto::setVelocidade(float v){Velocidade = v;}
void Objeto::setPosicao(float x){Posicao=x;}
void Objeto::setAceleracao(float a){Aceleracao=a;}

float Objeto::getMassa(){return Massa;}
float Objeto::getPosicao(){return Posicao;}
float Objeto::getVelocidade(){return Velocidade;}
float Objeto::getAceleracao(){return Aceleracao;}


class Mola{
    private:
        float Ks; //coeficiente de Hook

    public:
        Mola(float k);
        void setKs(float c);
        float getKs();
};
Mola::Mola(float k){
    Ks=k;
}

void Mola::setKs(float c){Ks=c;}
float Mola::getKs(){return Ks;}


class Amortecedor{
    private:
        float B; //coeficiente de amortecimento

    public:
        Amortecedor(float b);
        void setB(float b);
        float getB();
};
Amortecedor::Amortecedor(float b){
    B=b;
}

void Amortecedor::setB(float b){B=b;}
float Amortecedor::getB(){return B;}


class Sistema{
    private:
        Objeto &obj;
        Mola &mola;
        Amortecedor &amortecedor;
        float T;

    public:
        Sistema(Objeto &obj, Mola &mola, Amortecedor &amortecedor, float t);

        void setObjeto(Objeto &o);
        void setMola(Mola &m);
        void setAmortecedor(Amortecedor &a);
        void setT(float t);

        Objeto getObjeto();
        Mola getMola();
        Amortecedor getAmortecedor();
        float getT();
        
        void Simulacao(float fi);
};
Sistema::Sistema(Objeto &obj, Mola &mola, Amortecedor &amortecedor, float t):

obj(obj),
mola(mola),
amortecedor(amortecedor)
{T=t;}

void Sistema::setObjeto(Objeto &o){obj=o;}
void Sistema::setMola(Mola &m){mola=m;}
void Sistema::setAmortecedor(Amortecedor &a){amortecedor=a;}
void Sistema::setT(float t){T=t;}

Objeto Sistema::getObjeto(){return obj;}
Mola Sistema::getMola(){return mola;}
Amortecedor Sistema::getAmortecedor(){return amortecedor;}
float Sistema::getT(){return T;}

void Sistema::Simulacao(float fi){

    float Fel = -1*getMola().getKs()*obj.getPosicao();
    float Fam = -1*getAmortecedor().getB()*obj.getVelocidade();

    obj.setAceleracao((Fel + Fam + fi)/obj.getMassa());
    obj.setVelocidade( obj.getVelocidade() + obj.getAceleracao()*getT() ); 
    obj.setPosicao(obj.getPosicao() + obj.getVelocidade()*getT());
}

class View
{
  private:
    Objeto &obj;

  public:
    View(Objeto &obj);
    void render();
};

View::View(Objeto &obj):
  obj(obj){}

void View::render() {
  std::cout <<"Posicao: " << obj.getPosicao() << " Velocidade: " << obj.getVelocidade() << std::endl;
}

int main(){

    Objeto o = Objeto(1,0,1);
    Mola m = Mola(1);
    Amortecedor a = Amortecedor(1);
    View view = View(o);
    Sistema sistema = Sistema(o,m,a,0.1);


    for(int i=0; i<100; i++){
        sistema.Simulacao(0);
        view.render();
    }
    
}