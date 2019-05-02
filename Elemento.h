#pragma once
template<class T2>
class Elemento
{
private:
	Elemento<T2>* pProx,*pAnte;
	T2* pInfo;
public:
	Elemento() {
		pProx = NULL;
		pInfo = NULL;
		pAnte = NULL;
	}
	~Elemento() {
		pProx = NULL;
		pInfo = NULL;
		pAnte = NULL;
	}
	Elemento<T2>* getProx() const { return pProx; };
	void setProx(Elemento<T2>* pp) { pProx = pp; };
	T2* getInfo() const { return pInfo; };
	void setInfo(T2* pi) { pInfo = pi; };
	Elemento<T2>* getAnte() const{ return pAnte; };
	void setAnte(Elemento<T2>* pa) { pAnte = pa; };
};